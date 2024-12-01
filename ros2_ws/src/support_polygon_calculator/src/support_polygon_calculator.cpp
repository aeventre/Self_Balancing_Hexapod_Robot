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

class SupportPolygonNode : public rclcpp::Node  // Inherit from rclcpp::Node
{
public:
    // Constructor
    SupportPolygonNode()
        : Node("support_polygon_node")  // Name of the node
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
        stability_pub_ = this->create_publisher<std_msgs::msg::Bool>("/stability_status", 10);

        // Initialize timer for periodic publishing
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),  // 10 Hz
            std::bind(&SupportPolygonNode::publishResults, this));

        RCLCPP_INFO(this->get_logger(), "Node initialized.");
    }

private:
    // Callback for grounded feet positions
    void groundedFeetCallback(const std::shared_ptr<std::vector<geometry_msgs::msg::Point>> msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received grounded foot positions.");
        grounded_foot_positions_ = *msg;  // Store the received positions
    }

    // Callback for CoM position
    void comCallback(const geometry_msgs::msg::Point::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received CoM position.");
        com_position_ = *msg;  // Store the received CoM
    }

    // Periodic task: Compute and publish results
    void publishResults()
    {
        // Placeholder for processing and publishing logic
        RCLCPP_INFO(this->get_logger(), "Publishing support polygon and stability status.");

        geometry_msgs::msg::Polygon polygon_msg;
        std_msgs::msg::Bool stability_msg;

        // Process data and populate messages (example logic)
        stability_msg.data = true;  // Example: Assume always stable
        polygon_pub_->publish(polygon_msg);
        stability_pub_->publish(stability_msg);
    }


    // Member variable declarations
    rclcpp::Subscription<std::vector<geometry_msgs::msg::Point>>::SharedPtr grounded_feet_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr com_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Polygon>::SharedPtr polygon_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr stability_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    std::vector<geometry_msgs::msg::Point> grounded_foot_positions_;  // Store latest grounded feet
    geometry_msgs::msg::Point com_position_;  // Store latest CoM
};