#include "Hexapod.hpp"

int main() {
    Hexapod hexapod;

    // Example targets for each leg
    std::vector<std::vector<float>> targets = {
        {15.0f, 25.0f, -10.0f},  // FrontLeft
        {10.0f, 20.0f, -15.0f},  // FrontRight
        {20.0f, 30.0f, -5.0f},   // MiddleLeft
        {25.0f, 35.0f, -10.0f},  // MiddleRight
        {15.0f, 15.0f, -10.0f},  // BackLeft
        {20.0f, 10.0f, -15.0f}   // BackRight
    };

    // Set targets for all legs
    hexapod.setTargetsForAllLegs(targets);

    // Visualize the hexapod
    hexapod.visualize();

    return 0;
}
