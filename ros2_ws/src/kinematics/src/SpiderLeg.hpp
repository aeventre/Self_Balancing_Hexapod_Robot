#ifndef SPIDER_LEG_HPP
#define SPIDER_LEG_HPP

#include <vector>
#include <string>

class SpiderLeg {
public:
    SpiderLeg(const std::string& name, float coxa, float femur, float tibia, float xOffset = 0.0f, float yOffset = 0.0f);

    void setAngles(const std::vector<float>& angles);
    std::vector<float> getAngles() const;

    std::vector<float> inverseKinematics(const std::vector<float>& target);
    std::vector<std::vector<float>> forwardKinematics();
    const std::vector<std::vector<float>>& getTarget() const;

private:
    std::string name_;
    float COXA, FEMUR, TIBIA;
    float theta1, theta2, theta3;
    float xOffset_;
    float yOffset_;
    std::vector<std::vector<float>> joints;

    float rad2deg(float radians) const;
    float deg2rad(float degrees) const;
    std::vector<float> normalizeAngles(const std::vector<float>& angles);
};

#endif // SPIDER_LEG_HPP
