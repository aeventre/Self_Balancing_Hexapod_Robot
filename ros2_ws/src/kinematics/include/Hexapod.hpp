#ifndef HEXAPOD_HPP
#define HEXAPOD_HPP

#include <vector>
#include "SpiderLeg.hpp"

class Hexapod {
public:
    Hexapod();
    
    std::vector<std::vector<float>> computeForwardKinematics(const std::vector<std::vector<float>>& joint_angles);
    std::vector<std::vector<float>> computeInverseKinematics(const std::vector<std::vector<float>>& foot_positions);

private:
    std::vector<SpiderLeg> legs_;
};

#endif
