#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "SpiderLeg.hpp"

class InverseKinematicsNode : public rclcpp::Node {
public:
    InverseKinematicsNode() : Node("inverse_kinematics_node") {
        leg_commands_sub_ = this->create_subscription<std_msgs::msg::Float32MultiArray>( 
            "leg_commands", 10, std::bind(&InverseKinematicsNode::legCommandsCallback, this, std::placeholders::_1));
        joint_angles_pub_ = this->create_publisher<std_msgs::msg::FLoat32MultiArray>("joint_angles", 10);

        for (int i = 0; i < 6; ++i) {
            spider_legs_.emplace_back("Leg" + std::to_string(i + 1), 10.0f, 20.0f, 30.0f);
        }
    }

private:
    void legCommandsCallback(const std_msgs::msg::FLoat32MultiArray::SharedPtr msg) {
        if (msg->data.size() != 18) {
            RCLCPP_ERROR(this->get_logger(), "Invalid leg_commands size. Expected 18 elements.");
            return;
        }

        std::vector<std::vector<float>> targets;
        for (size_t i = 0; i < msg->data.size(); i += 3) {
            targets.emplace_back(std::vector<float>{msg->data[i], msg->data[i + 1], msg->data[i+2]});
        }

        std_msgs::msg::Float32MultiArray joint_angles_msg;
        for (size_t i = 0; i < spider_legs_.size(); ++i) {
            std::vector<float> angles = spider_legs_[i].inverseKinematics(targets[i]);
            joint_angles_msg.data.insert(joint_angles_msg.data.end(), angles.begin(), angles.end());
        }

        joint_angles_pub_->publish(joint_angles_msg);

    } 

    std::vector<SpiderLeg> spider_legs_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr leg_commands_sub_;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr joint_angles_pub_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<InverseKinematicsNode>());
    rclcpp::shutdown();
    return 0;
}