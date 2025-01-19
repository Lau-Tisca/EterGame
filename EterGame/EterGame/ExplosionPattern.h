//ExplosionPatterh.h

#pragma once

#include "GameBoard.h"
#include <vector>
#include <utility>
#include <random>

enum class ExplosionEffect {
    RemoveCard,
    ReturnToHand,
    CreateHole
};

struct ExplosionTile {
    int x, y;
    ExplosionEffect effect;
};

class ExplosionPattern {
public:
    explicit ExplosionPattern(int gridSize);
    ExplosionPattern(std::vector<ExplosionTile> tiles);
    const std::vector<ExplosionTile>& getTiles() const;
    void applyExplosion(GameBoard& board, int centerRow, int centerCol);
    static void rotatePattern(std::vector<std::pair<int, int>>& pattern, int size);
    static std::vector<ExplosionTile> generateExplosionPattern(int gridSize, int& holeCount);
private:
    std::vector<ExplosionTile> affectedTiles;
    void generateExplosion(int gridSize);
};