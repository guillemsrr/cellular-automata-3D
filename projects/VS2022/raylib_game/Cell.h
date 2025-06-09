#pragma once
#include <vector>
#include "raylib.h"

enum class CellState
{
    Alive,
    Decaying,
    Dead
};

static constexpr float Size = 1.f;
static constexpr int MaxDecayTicks = 6;

class Cell
{
public:
    Cell() = default;
    Cell(int x, int y, int z);

    int GetState() const;
    void SetState(CellState state);
    bool IsAlive() const;
    bool IsDead() const;
    bool IsDecaying() const;

    int GridX;
    int GridY;
    int GridZ;

    Vector3 Position;
    Color CellColor;
    std::vector<Cell*> CachedNeighbors;

    int decayTicks = 0;

    void Draw() const;

private:
    CellState _state;
};