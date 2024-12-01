#include "SpiderLeg.hpp"
#include <iostream>

SpiderLeg::SpiderLeg(const std::string& name, float coxa, float femur, float tibia)
    : COXA(coxa), FEMUR(femur), TIBIA(tibia) {}

std::vector<float> SpiderLeg::forwardKinematics(const std::vector<float>& angles) {
    float theta1 = deg2rad(angles[0]);
    float theta2 = deg2rad(angles[1]);
    float theta3 = deg2rad(angles[2]);

    float x = (COXA + FEMUR * cos(theta2) + TIBIA * cos(theta2 + theta3)) * cos(theta1);
    float y = (COXA + FEMUR * cos(theta2) + TIBIA * cos(theta2 + theta3)) * sin(theta1);
    float z = FEMUR * sin(theta2) + TIBIA * sin(theta2 + theta3);

    return {x, y, z};
}

std::vector<float> SpiderLeg::inverseKinematics(const std::vector<float>& target) {
    // Extract the target coordinates
    float x = target[0];
    float y = target[1];
    float z = target[2];

    // Calculate COXA angle (theta1)
    float theta1 = atan2(y, x);

    // Adjust the target for the FEMUR-TIBIA plane
    float horizontal_distance = sqrt(x * x + y * y) - COXA;  // Horizontal distance from FEMUR base

    // Calculate the distance to the target
    float H = sqrt(horizontal_distance * horizontal_distance + z * z);

    // Check if the target is reachable
    if (H > (FEMUR + TIBIA)) {
        throw std::runtime_error("Target out of reach");
    }

    // Calculate FEMUR and TIBIA angles (theta2 and theta3)
    float phi1 = atan2(z, horizontal_distance); // Angle between the FEMUR base and the target
    float phi2 = acos((FEMUR * FEMUR + H * H - TIBIA * TIBIA) / (2 * FEMUR * H));
    float phi3 = acos((FEMUR * FEMUR + TIBIA * TIBIA - H * H) / (2 * FEMUR * TIBIA));

    float theta2 = phi1 + phi2;          // FEMUR angle
    float theta3 = M_PI - phi3;          // TIBIA angle (convert to positive rotation)

    return {rad2deg(theta1), rad2deg(theta2), rad2deg(theta3)};

}

float SpiderLeg::rad2deg(float radians) const {
    return radians * 180.0 / M_PI;
}

float SpiderLeg::deg2rad(float degrees) const {
    return degrees * M_PI / 180.0;
}