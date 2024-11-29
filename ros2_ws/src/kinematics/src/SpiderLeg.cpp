#include "SpiderLeg.hpp"
#include <cmath>
#include <iostream>

SpiderLeg::SpiderLeg(const std::string& name, float coxa, float femur, float tibia, float xOffset, float yOffset)
    : name_(name), COXA(coxa), FEMUR(femur), TIBIA(tibia), xOffset_(xOffset), yOffset_(yOffset), theta1(0), theta2(0), theta3(0) {
    forwardKinematics();
}


void SpiderLeg::setAngles(const std::vector<float>& angles) {
    std::vector<float> normalized_angles = normalizeAngles(angles);
    theta1 = normalized_angles[0];
    theta2 = normalized_angles[1];
    theta3 = normalized_angles[2];
}

std::vector<float> SpiderLeg::getAngles() const {
    return {theta1, theta2, theta3};
}

std::vector<float> SpiderLeg::inverseKinematics(const std::vector<float>& target) {
    // Extract the target coordinates
    float x = target[0];
    float y = target[1];
    float z = target[2];

    // Calculate COXA angle (theta1)
    float theta1 = atan2(y, x);

    // Adjust the target for the FEMUR-TIBIA plane
    float Xb = sqrt(x * x + y * y) - COXA;  // Horizontal distance from FEMUR base
    float Zb = z;                           // Vertical distance from FEMUR base

    // Calculate the distance to the target
    float H = sqrt(Xb * Xb + Zb * Zb);

    // Check if the target is reachable
    if (H > (FEMUR + TIBIA)) {
        std::cerr << "Target out of reach. Scaling back to reachable position." << std::endl;
        float scale = (FEMUR + TIBIA) / H;
        Xb *= scale;
        Zb *= scale;
        H = FEMUR + TIBIA; // Update to maximum reachable distance
    }

    // Calculate FEMUR and TIBIA angles (theta2 and theta3)
    float phi1 = atan2(Zb, Xb); // Angle between the FEMUR base and the target
    float phi2 = acos((FEMUR * FEMUR + H * H - TIBIA * TIBIA) / (2 * FEMUR * H));
    float phi3 = acos((FEMUR * FEMUR + TIBIA * TIBIA - H * H) / (2 * FEMUR * TIBIA));

    float theta2 = phi1 + phi2;          // FEMUR angle
    float theta3 = M_PI - phi3;          // TIBIA angle (convert to positive rotation)

    // Convert to degrees
    std::vector<float> angles = {
        rad2deg(theta1),
        rad2deg(theta2),
        rad2deg(theta3)
    };

    // Set the angles and perform forward kinematics
    setAngles(angles);
    forwardKinematics();

    // Return the calculated joint angles
    return angles;
}

std::vector<std::vector<float>> SpiderLeg::forwardKinematics() {
    float rad_theta1 = deg2rad(theta1);
    float rad_theta2 = deg2rad(theta2);
    float rad_theta3 = deg2rad(theta3);

    float Xa = COXA * cos(rad_theta1);
    float Ya = COXA * sin(rad_theta1);
    float G2 = sin(rad_theta2) * FEMUR;
    float P1 = cos(rad_theta2) * FEMUR;
    float Xc = cos(rad_theta1) * P1;
    float Yc = sin(rad_theta1) * P1;

    float H = sqrt(TIBIA * TIBIA + FEMUR * FEMUR - (2 * TIBIA * FEMUR * cos(M_PI - rad_theta3)));
    float phi1 = acos((FEMUR * FEMUR + H * H - TIBIA * TIBIA) / (2 * FEMUR * H));
    float phi3 = phi1 - rad_theta2;
    float Pp = cos(phi3) * H;
    float P2 = Pp - P1;
    float Yb = sin(rad_theta1) * Pp;
    float Xb = cos(rad_theta1) * Pp;
    float G1 = -sin(phi3) * H;

    joints = {
        {0, 0, 0},
        {Xa, Ya, 0},
        {Xa + Xc, Ya + Yc, G2},
        {Xa + Xb, Ya + Yb, G1}
    };

    return joints;
}

const std::vector<std::vector<float>>& SpiderLeg::getTarget() const {
    return joints;
}

float SpiderLeg::rad2deg(float radians) const {
    return radians * 180.0 / M_PI;
}

float SpiderLeg::deg2rad(float degrees) const {
    return degrees * M_PI / 180.0;
}

std::vector<float> SpiderLeg::normalizeAngles(const std::vector<float>& angles) {
    std::vector<float> normalized = angles;
    for (size_t i = 0; i < normalized.size(); ++i) {
        float ang = normalized[i];
        float sign = (ang < 0) ? -1 : 1;
        normalized[i] = sign * fmod(fabs(ang), 360.0f);
        if (fabs(normalized[i]) > 180.0f) {
            normalized[i] -= 360.0f * sign;
        }
    }
    return normalized;
}
