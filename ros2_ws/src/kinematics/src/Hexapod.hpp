#ifndef HEXAPOD_HPP
#define HEXAPOD_HPP

#include <vector>
#include <string>
#include "SpiderLeg.hpp"

class Hexapod {
public:
    Hexapod();
    
    // Set a target for a specific leg
    void setTargetForLeg(int legIndex, const std::vector<float>& target);

    // Set targets for all legs
    void setTargetsForAllLegs(const std::vector<std::vector<float>>& targets);

    // Get joint positions for all legs
    std::vector<std::vector<std::vector<float>>> getAllJointPositions();

    // Visualize the hexapod's current joint positions
    void visualize();

private:
    std::vector<SpiderLeg> legs_;
};

#endif
