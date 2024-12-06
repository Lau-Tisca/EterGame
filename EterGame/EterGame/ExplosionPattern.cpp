//ExplosionPattern.cpp

#include "ExplosionPattern.h"
#include <vector>
#include <utility> // pentru std::pair
#include <algorithm> // pentru std::find
#include <cstdlib>   // pentru rand()
#include <ctime>     // pentru srand()

std::vector<std::pair<int, int>> ExplosionPattern::generateExplosionPattern(int size, int& holeCount) {
    std::vector<std::pair<int, int>> positions;
    int effects = (size == 3) ? (rand() % 3 + 2) : (rand() % 4 + 3); // 2-4 pentru 3x3, 3-6 pentru 4x4
    holeCount = 0;

    // Generează poziții unice pentru efectele exploziei
    while (positions.size() < effects) {
        int row = rand() % size;
        int col = rand() % size;

        std::pair<int, int> pos = { row, col };
        if (std::find(positions.begin(), positions.end(), pos) == positions.end()) {
            positions.push_back(pos);

            // Probabilitatea de 10% pentru a adăuga o groapă
            if (rand() % 10 == 0) {
                holeCount++;
            }
        }
    }

    return positions;
}

void ExplosionPattern::rotatePattern(std::vector<std::pair<int, int>>& pattern, int size) {
    for (auto& pos : pattern) {
        int temp = pos.first;
        pos.first = pos.second;
        pos.second = size - 1 - temp;
    }
}