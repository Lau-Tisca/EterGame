#pragma once
//ExplosionPatterh.h
#include <vector>
#include <utility>

class ExplosionPattern {
public:
    static std::vector<std::pair<int, int>> generateExplosionPattern(int size, int& holeCount);
    static void rotatePattern(std::vector<std::pair<int, int>>& pattern, int size);
};