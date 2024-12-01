#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "Hexapod.hpp"

class ForwardKinematicsNode : public rclcpp::Node {
public:
    ForwardKinematicsNode() : Node("forward_kinematics_node") {
        joint_angles_sub_ = this->create_subscription<std_msgs::msg::Float32MultiArray>( 
            "joint_angles", 10, std::bind(&ForwardKinematicsNode::computeFootPositions, this, std::placeholders::_1));
        foot_positions_pub_ = this->create_publisher<std_msgs::msg::FLoat32MultiArray>("foot_positions", 10);
    }

private:
    void computeFootPositions(const std_msgs::msg::FLoat32MultiArray::SharedPtr msg) {
        std::vector<std::vector<float>> joint_angles;
        for (size_t i = 0; i < msg->data.size(); i += 3) {
            joint_angles.push_back({msg->data[i], msg->data[i + 1], msg->data[i+2]});
        }

        auto foot_positions = hexapod_.computeForwardKinematics(joint_angles);

        std_msgs::msg::Float32MultiArray foot_positions_msg;
        for (const auto& position : foot_positions) {
            foot_positions_msg.data.insert(foot_positions_msg.data.end(), position.begin(), position.end());
        }

        foot_positions_pub_->publish(foot_positions_msg);
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