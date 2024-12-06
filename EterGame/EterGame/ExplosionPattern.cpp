//ExplosionPattern.cpp

#include "ExplosionPattern.h"
#include <vector>
#include <utility> // pentru std::pair
#include <algorithm> // pentru std::find
#include <cstdlib>   // pentru rand()
#include <ctime>     // pentru srand()

void ExplosionPattern::rotatePattern(std::vector<std::pair<int, int>>& pattern, int size) {
    for (auto& pos : pattern) {
        int temp = pos.first;
        pos.first = pos.second;
        pos.second = size - 1 - temp;
    }
}