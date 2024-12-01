// Standard headers
#include <cstdio>
#include <vector>

// Eigen for numerical computations and transformations
#include <Eigen/Dense>
#include <Eigen/Geometry>

// Boost.Geometry for geometric calculations
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>

// CGAL for convex hull computation
#include <CGAL/convex_hull_2.h>

// ROS2 core and message types
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "geometry_msgs/msg/polygon.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float32.hpp"

class SupportPolygonNode : public rclcpp::Node
{
public:
    // Class constructor
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
        polygon_pub_ = this->create_publisher<geometry_msgs::msg::Polygon>("/support_polygon", 10);
        stability_margin_pub_ = this->create_publisher<std_msgs::msg::Float32>("/stability_margin", 10);
        centroid_pub_ = this->create_publisher<geometry_msgs::msg::Point>("/polygon_centroid", 10);

        // Initialize timer for periodic publishing
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100), // 10 Hz
            std::bind(&SupportPolygonNode::publishResults, this));

        RCLCPP_INFO(this->get_logger(), "SupportPolygonNode initialized.");
    }

private:
    // Callback for grounded feet positions
    void groundedFeetCallback(const std::shared_ptr<std::vector<geometry_msgs::msg::Point>> msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received grounded foot positions.");
        grounded_foot_positions_ = *msg; // Store the received positions
    }

    // Callback for CoM position
    void comCallback(const geometry_msgs::msg::Point::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received CoM position.");
        com_position_ = *msg; // Store the received CoM
    }

    // Compute and publish results periodically
    void publishResults()
    {
        if (grounded_foot_positions_.empty())
        {
            RCLCPP_WARN(this->get_logger(), "No grounded foot positions available.");
            return;
        }

        // Construct the support polygon
        geometry_msgs::msg::Polygon polygon_msg;
        for (const auto &foot : grounded_foot_positions_)
        {
            geometry_msgs::msg::Point32 point;
            point.x = foot.x;
            point.y = foot.y;
            point.z = foot.z;
            polygon_msg.points.push_back(point);
        }

        // Publish the support polygon
        polygon_pub_->publish(polygon_msg);

        // Compute and publish the centroid
        auto centroid = computePolygonCentroid(polygon_msg);
        centroid_pub_->publish(centroid);

        // Compute and publish the stability margin
        auto margin = computeStabilityMargin(polygon_msg, com_position_);
        std_msgs::msg::Float32 margin_msg;
        margin_msg.data = static_cast<float>(margin); // Cast to float
        stability_margin_pub_->publish(margin_msg);

        RCLCPP_INFO(this->get_logger(), "Published support polygon, centroid, and stability margin.");
    }

    // Helper function for computing the polygon centroid
    geometry_msgs::msg::Point computePolygonCentroid(const geometry_msgs::msg::Polygon &polygon)
    {
        geometry_msgs::msg::Point centroid;
        double x_sum = 0.0, y_sum = 0.0;
        size_t n = polygon.points.size();

        if (n == 0)
        {
            RCLCPP_WARN(this->get_logger(), "Polygon has no points. Returning default centroid.");
            return centroid;
        }

        for (const auto &point : polygon.points)
        {
            x_sum += point.x;
            y_sum += point.y;
        }

        centroid.x = x_sum / n;
        centroid.y = y_sum / n;
        centroid.z = 0.0; // Assume polygon is in the XY plane
        return centroid;
    }

    // Helper function for computing the stability margin
    double computeStabilityMargin(const geometry_msgs::msg::Polygon &polygon, const geometry_msgs::msg::Point &com)
    {
        using BoostPoint = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
        using BoostPolygon = boost::geometry::model::polygon<BoostPoint>;

        BoostPolygon boost_polygon;
        for (const auto &pt : polygon.points)
        {
            boost_polygon.outer().emplace_back(pt.x, pt.y);
        }

        BoostPoint com_point(com.x, com.y);
        return boost::geometry::distance(com_point, boost_polygon);
    }

    // Member variables
    rclcpp::Subscription<std::vector<geometry_msgs::msg::Point>>::SharedPtr grounded_feet_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr com_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Polygon>::SharedPtr polygon_pub_;
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
