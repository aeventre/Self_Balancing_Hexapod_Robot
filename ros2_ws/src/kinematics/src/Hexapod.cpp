#include "Hexapod.hpp"
#include "Visualization.hpp"
#include <stdexcept>

Hexapod::Hexapod() {
    // Initialize the six legs of the hexapod with example dimensions
    legs_ = {
        SpiderLeg("FrontLeft", 10.0f, 20.0f, 30.0f, 10.0f, 10.0f),
        SpiderLeg("FrontRight", 10.0f, 20.0f, 30.0f, 10.0f, -10.0f),
        SpiderLeg("MiddleLeft", 10.0f, 20.0f, 30.0f, 0.0f, 10.0f),
        SpiderLeg("MiddleRight", 10.0f, 20.0f, 30.0f, 0.0f, -10.0f),
        SpiderLeg("BackLeft", 10.0f, 20.0f, 30.0f, -10.0f, 10.0f),
        SpiderLeg("BackRight", 10.0f, 20.0f, 30.0f, -10.0f, -10.0f)
    };
}

void Hexapod::setTargetForLeg(int legIndex, const std::vector<float>& target) {
    if (legIndex < 0 || legIndex >= legs_.size()) {
        throw std::out_of_range("Invalid leg index");
    }
    legs_[legIndex].inverseKinematics(target);
}

void Hexapod::setTargetsForAllLegs(const std::vector<std::vector<float>>& targets) {
    if (targets.size() != legs_.size()) {
        throw std::invalid_argument("Number of targets must match the number of legs");
    }
    for (size_t i = 0; i < legs_.size(); ++i) {
        legs_[i].inverseKinematics(targets[i]);
    }
}

std::vector<std::vector<std::vector<float>>> Hexapod::getAllJointPositions() {
    std::vector<std::vector<std::vector<float>>> allJointPositions;
    for (const auto& leg : legs_) {
        allJointPositions.push_back(leg.getTarget());
    }
    return allJointPositions;
}

void Hexapod::visualize() {
    auto allJointPositions = getAllJointPositions();
    visualizeHexapod(allJointPositions);
}
