#include "Visualization.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void visualizeHexapod(const std::vector<std::vector<std::vector<float>>>& jointPositions) {
    for (const auto& leg : jointPositions) {
        std::vector<float> x, y, z;
        for (const auto& joint : leg) {
            x.push_back(joint[0]);
            y.push_back(joint[1]);
            z.push_back(joint[2]);
        }
        plt::plot3(x, y, z, {{"marker", "o"}, {"linewidth", "2"}, {"markersize", "8"}});
    }
    plt::xlabel("X-axis");
    plt::ylabel("Y-axis");
    plt::set_zlabel("Z-axis");
    plt::title("Hexapod Visualization");
    plt::show();
}
