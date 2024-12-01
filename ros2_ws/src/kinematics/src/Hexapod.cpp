#include "Hexapod.hpp"

Hexapod::Hexapod() {
    // Initialize the six legs of the hexapod with example dimensions
    legs_ = {
        SpiderLeg("FrontLeft", 10.0f, 20.0f, 30.0f),
        SpiderLeg("FrontRight", 10.0f, 20.0f, 30.0f),
        SpiderLeg("MiddleLeft", 10.0f, 20.0f, 30.0f),
        SpiderLeg("MiddleRight", 10.0f, 20.0f, 30.0f),
        SpiderLeg("BackLeft", 10.0f, 20.0f, 30.0f),
        SpiderLeg("BackRight", 10.0f, 20.0f, 30.0f)
    };
}
std::vector<std::vector<float>> Hexapod::computeFowardKinematics(const std::vector<std::vector<float>>& joint_angles) {
    std::vector<std::vector<float>> foot_positions;
    for (size_t i = 0; i < legs_.size(); ++i) {
        foot_positions.push_back(legs_[i].forwardKinematics(joint_angles[i]));
    }
    return foot_positions;
}

std::vector<std::vector<float>> Hexapod::computeInverseKinematics(const std::vector<std::vector<float>>& foot_positions) {
    std::vector<std::vector<float>> joint_angles;
    for (size_t i = 0; i < legs_.size(); ++i) {
        joint_angles.push_back(legs_[i].inverseKinematics(foot_positions[i]));
    }
    return joint_angles;
}