#include <vector>
#include <array>

std::array<double, 3> calculate_com(const std::vector<double>& masses, const std::vector<std::array<double, 3>>& positions) {
    double total_mass = 0.0;
    std::array<double, 3> com = {0.0, 0.0, 0.0};

    for (size_t i = 0; i < masses.size(); ++i) {
        total_mass += masses[i];
        for (int j = 0; j < 3; ++j) {
            com[j] += masses[i] * positions[i][j];
        }
    }

    for (int j = 0; j < 3; ++j) {
        com[j] /= total_mass;
    }

    return com;
}
