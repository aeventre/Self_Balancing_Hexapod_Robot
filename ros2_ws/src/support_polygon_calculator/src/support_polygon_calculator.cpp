#include <cstdio>
#include <vector>
#include <Eigen/Dense>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <CGAL/convex_hull_2.h>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/polygon_stamped.hpp"
#include "std_msgs/msg/float32.hpp"

class SupportPolygonNode : public rclcpp::Node
{
public:
    SupportPolygonNode()
        : Node("support_polygon_node")
    {
        // Initialize subscribers
        grounded_feet_sub_ = this->create_subscription<std::vector<geometry_msgs::msg::Point>>(
            "/grounded_foot_positions", 10,
            std::bind(&SupportPolygonNode::groundedFeetCallback, this, std::placeholders::_1));

        com_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
            "/center_of_mass", 10,
            std::bind(&SupportPolygonNode::comCallback, this, std::placeholders::_1));

        // Initialize publishers
        polygon_pub_ = this->create_publisher<geometry_msgs::msg::PolygonStamped>("/support_polygon", 10);
        stability_margin_pub_ = this->create_publisher<std_msgs::msg::Float32>("/stability_margin", 10);
        centroid_pub_ = this->create_publisher<geometry_msgs::msg::Point>("/polygon_centroid", 10);

        // Initialize timer for periodic publishing
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&SupportPolygonNode::publishResults, this));

        RCLCPP_INFO(this->get_logger(), "SupportPolygonNode initialized.");
    }

private:
    void groundedFeetCallback(const std::shared_ptr<std::vector<geometry_msgs::msg::Point>> msg)
    {
        if (msg->empty())
        {
            RCLCPP_WARN(this->get_logger(), "Received empty grounded foot positions.");
            return;
        }
        grounded_foot_positions_ = *msg;
        RCLCPP_INFO(this->get_logger(), "Grounded foot positions updated.");
    }

    void comCallback(const geometry_msgs::msg::Point::SharedPtr msg)
    {
        if (msg == nullptr)
        {
            RCLCPP_WARN(this->get_logger(), "Received invalid CoM message.");
            return;
        }
        com_position_ = *msg;
        RCLCPP_INFO(this->get_logger(), "Center of Mass updated: x=%.2f, y=%.2f, z=%.2f", msg->x, msg->y, msg->z);
    }

    void publishResults()
    {
        try
        {
            // Check if grounded foot positions are available
            if (grounded_foot_positions_.empty())
            {
                RCLCPP_WARN(this->get_logger(), "No grounded foot positions available. Skipping calculations.");
                return;
            }

            // Construct the support polygon
            geometry_msgs::msg::PolygonStamped polygon_msg;
            polygon_msg.header.stamp = this->now();
            polygon_msg.header.frame_id = "base_link";

            for (const auto &foot : grounded_foot_positions_)
            {
                geometry_msgs::msg::Point32 point;
                point.x = foot.x;
                point.y = foot.y;
                point.z = foot.z;
                polygon_msg.polygon.points.push_back(point);
            }

            polygon_pub_->publish(polygon_msg);

            // Compute and publish the centroid
            geometry_msgs::msg::Point centroid;
            try
            {
                centroid = computePolygonCentroid(polygon_msg.polygon);
                centroid_pub_->publish(centroid);
                RCLCPP_INFO(this->get_logger(), "Centroid: x=%.2f, y=%.2f, z=%.2f", centroid.x, centroid.y, centroid.z);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "Error computing centroid: %s", e.what());
            }

            // Compute and publish the stability margin
            try
            {
                double margin = computeStabilityMargin(polygon_msg.polygon, com_position_);
                std_msgs::msg::Float32 margin_msg;
                margin_msg.data = static_cast<float>(margin);
                stability_margin_pub_->publish(margin_msg);
                RCLCPP_INFO(this->get_logger(), "Stability Margin: %.2f", margin);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(this->get_logger(), "Error computing stability margin: %s", e.what());
            }
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Unexpected error in publishResults: %s", e.what());
        }
    }

    geometry_msgs::msg::Point computePolygonCentroid(const geometry_msgs::msg::Polygon &polygon)
    {
        geometry_msgs::msg::Point centroid;
        double x_sum = 0.0, y_sum = 0.0;
        size_t n = polygon.points.size();

        if (n == 0)
        {
            throw std::runtime_error("Polygon has no points. Cannot compute centroid.");
        }

        for (const auto &point : polygon.points)
        {
            x_sum += point.x;
            y_sum += point.y;
        }

        centroid.x = x_sum / n;
        centroid.y = y_sum / n;
        centroid.z = 0.0;
        return centroid;
    }

    double computeStabilityMargin(const geometry_msgs::msg::Polygon &polygon, const geometry_msgs::msg::Point &com)
    {
        using BoostPoint = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
        using BoostPolygon = boost::geometry::model::polygon<BoostPoint>;

        if (polygon.points.empty())
        {
            throw std::runtime_error("Polygon has no points. Cannot compute stability margin.");
        }

        BoostPolygon boost_polygon;
        for (const auto &pt : polygon.points)
        {
            boost_polygon.outer().emplace_back(pt.x, pt.y);
        }

        BoostPoint com_point(com.x, com.y);
        return boost::geometry::distance(com_point, boost_polygon);
    }

    rclcpp::Subscription<std::vector<geometry_msgs::msg::Point>>::SharedPtr grounded_feet_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr com_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PolygonStamped>::SharedPtr polygon_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr stability_margin_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr centroid_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<geometry_msgs::msg::Point> grounded_foot_positions_;
    geometry_msgs::msg::Point com_position_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SupportPolygonNode>());
    rclcpp::shutdown();
    return 0;
}
