#ifndef SPIDER_LEG_HPP
#define SPIDER_LEG_HPP

#include <vector>
#include <string>
#include <cmath>

class SpiderLeg {
public:
    SpiderLeg(const std::string& name, float coxa, float femur, float tibia);

    std::vector<float> forwardKinematics(const std::vector<float>& angles);
    std::vector<float> inverseKinematics(const std::vector<float>& target);

private:
    float COXA, FEMUR, TIBIA;

    float rad2deg(float radians) const;
    float deg2rad(float degrees) const;
};

#endif // SPIDER_LEG_HPP
