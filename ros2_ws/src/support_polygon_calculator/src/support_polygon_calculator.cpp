#include <cstdio>
#include <vector>
#include <Eigen/Dense>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <CGAL/convex_hull_2.h>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/point32.hpp"
#include "geometry_msgs/msg/polygon.hpp"
#include "geometry_msgs/msg/polygon_stamped.hpp"
#include "std_msgs/msg/float32.hpp"

class SupportPolygonNode : public rclcpp::Node
{
public:
    SupportPolygonNode()
        : Node("support_polygon_node")
    {
        // Initialize subscribers
        grounded_feet_sub_ = this->create_subscription<geometry_msgs::msg::Polygon>(
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
    void groundedFeetCallback(const geometry_msgs::msg::Polygon::SharedPtr msg)
    {
        if (msg->points.empty())
        {
            RCLCPP_WARN(this->get_logger(), "Received empty grounded foot positions.");
            return;
        }
        grounded_foot_positions_ = msg->points;
        RCLCPP_INFO(this->get_logger(), "Grounded Foot Positions Received: %zu points", msg->points.size());
        for (const auto &point : msg->points)
        {
            RCLCPP_INFO(this->get_logger(), "Point: x=%.2f, y=%.2f, z=%.2f", point.x, point.y, point.z);
        }
    }

    void comCallback(const geometry_msgs::msg::Point::SharedPtr msg)
    {
        if (msg == nullptr)
        {
            RCLCPP_WARN(this->get_logger(), "Received invalid CoM message.");
            return;
        }
        com_position_ = *msg;
        RCLCPP_INFO(this->get_logger(), "Center of Mass Received: x=%.2f, y=%.2f, z=%.2f", msg->x, msg->y, msg->z);
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

            polygon_msg.polygon.points = grounded_foot_positions_;
            polygon_pub_->publish(polygon_msg);

            RCLCPP_INFO(this->get_logger(), "Publishing Support Polygon with %zu points.", polygon_msg.polygon.points.size());
            for (const auto &point : polygon_msg.polygon.points)
            {
                RCLCPP_INFO(this->get_logger(), "Polygon Point: x=%.2f, y=%.2f, z=%.2f", point.x, point.y, point.z);
            }

            // Compute and publish the centroid
            geometry_msgs::msg::Point centroid;
            try
            {
                centroid = computePolygonCentroid(polygon_msg.polygon);
                centroid_pub_->publish(centroid);
                RCLCPP_INFO(this->get_logger(), "Computed Centroid: x=%.2f, y=%.2f, z=%.2f", centroid.x, centroid.y, centroid.z);
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

    // Construct the Boost polygon
    BoostPolygon boost_polygon;
    RCLCPP_INFO(this->get_logger(), "Constructing Boost Polygon:");
    for (const auto &pt : polygon.points)
    {
        boost_polygon.outer().emplace_back(pt.x, pt.y);
        RCLCPP_INFO(this->get_logger(), "Boost Point Added: x=%.2f, y=%.2f", pt.x, pt.y);
    }

    // Close the polygon
    if (!boost_polygon.outer().empty())
    {
        boost_polygon.outer().push_back(boost_polygon.outer().front());
        RCLCPP_INFO(this->get_logger(), "Closed the Boost Polygon.");
    }

    // Correct the polygon to ensure counter-clockwise orientation
    boost::geometry::correct(boost_polygon);
    RCLCPP_INFO(this->get_logger(), "Polygon corrected to ensure counter-clockwise orientation.");

    // Validate the polygon
    if (!boost::geometry::is_valid(boost_polygon))
    {
        RCLCPP_ERROR(this->get_logger(), "Boost Polygon is invalid!");
        return 0.0;
    }

    // Log the final Boost polygon points
    for (const auto &pt : boost_polygon.outer())
    {
        RCLCPP_INFO(this->get_logger(), "Final Boost Polygon Point: x=%.2f, y=%.2f", pt.get<0>(), pt.get<1>());
    }

    // Convert CoM to Boost point
    BoostPoint com_point(com.x, com.y);
    RCLCPP_INFO(this->get_logger(), "CoM Boost Point: x=%.2f, y=%.2f", com.x, com.y);

    // Check if CoM is inside the polygon
    if (boost::geometry::within(com_point, boost_polygon))
    {
        RCLCPP_INFO(this->get_logger(), "CoM is inside the polygon. Calculating edge distance.");
        // Calculate distance to all edges
        double min_distance = std::numeric_limits<double>::max();
        const auto &ring = boost_polygon.outer();
        for (size_t i = 0; i < ring.size() - 1; ++i)
        {
            BoostPoint p1 = ring[i];
            BoostPoint p2 = ring[i + 1];
            double edge_distance = boost::geometry::distance(com_point, boost::geometry::model::segment<BoostPoint>(p1, p2));
            min_distance = std::min(min_distance, edge_distance);
        }
        RCLCPP_INFO(this->get_logger(), "Minimum edge distance: %.2f", min_distance);
        return min_distance;
    }
    else
    {
        RCLCPP_WARN(this->get_logger(), "CoM is outside the polygon.");
        return boost::geometry::distance(com_point, boost_polygon);
    }
}


    rclcpp::Subscription<geometry_msgs::msg::Polygon>::SharedPtr grounded_feet_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr com_sub_;
    rclcpp::Publisher<geometry_msgs::msg::PolygonStamped>::SharedPtr polygon_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr stability_margin_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr centroid_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<geometry_msgs::msg::Point32> grounded_foot_positions_;
    geometry_msgs::msg::Point com_position_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SupportPolygonNode>());
    rclcpp::shutdown();
    return 0;
}
