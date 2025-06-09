#pragma once
#include <vector>
#include "raylib.h"

enum class CellState
{
    Dead,
    Alive,
    Decaying
};

class Cell
{
public:
    Cell() = default;

    Cell(int x, int y, int z);

    int GetState() const;
    void SetState(CellState state);
    bool IsAlive();
    bool IsDead();

    int GridX;
    int GridY;
    int GridZ;

    Vector3 Position;
    float Size = 0.9f;
    Color CellColor;
    std::vector<Cell*> CachedNeighbors;

    void Draw();

private:
    CellState _state;
};