#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "Hexapod.hpp"

class InverseKinematicsNode : public rclcpp::Node {
public:
    InverseKinematicsNode() : Node("inverse_kinematics_node") {
        foot_positions_sub_ = this->create_subscription<std_msgs::msg::Float32MultiArray>( 
            foot_positions", 10, std::bind(&InverseKinematicsNode::computeJointAngles, this, std::placeholders::_1));
        joint_angles_pub_ = this->create_publisher<std_msgs::msg::FLoat32MultiArray>("joint_angles", 10);
    }

private:
    void computeJointAngles(const std_msgs::msg::FLoat32MultiArray::SharedPtr msg) {
        std::vector<std::vector<float>> foor_positions;
        for (size_t i = 0; i < msg->data.size(); i += 3) {
            foot_positions.push_back({msg->data[i], msg->data[i + 1], msg->data[i+2]});
        }

        auto joint_angles = hexapod_.computeInverseKinematics(foot_positions);

        std_msgs::msg::Float32MultiArray joint_angles_msg;
        for (const auto& position : joint_angles) {
            joint_angles_msg.data.insert(joint_angles_msg.data.end(), angles.begin(), angles.end());
        }

        joint_angles_pub_->publish(joint_angles_msg);
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Inverse kinematics error: %s", e.what());
        }

    Hexapod hexapod_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr joint_angles_sub_;
    rclcpp:Publisher<std_msgs::msg::FLoat32MultiArray>SharedPtr foot_positions_pub_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ForwardKinematicsNode>());
    rclcpp::shutdown();
    return 0;
}