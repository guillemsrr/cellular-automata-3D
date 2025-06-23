// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <vector>
#include "raylib.h"

enum class CellState
{
    Alive,
    Decaying,
    Dead
};

class Cell
{
public:
    Cell() = default;
    Cell(int x, int y, int z);

    static Color AliveColor;
    static Color DecayingColor;
    static Color DiedColor;
    static float Size;
    static int MaxDecayTicks;

    int GridX;
    int GridY;
    int GridZ;

    Vector3 Position;

    Color CellColor;
    std::vector<Cell*> CachedNeighbors;

    int GetState() const;
    void SetState(CellState state);
    bool IsAlive() const;
    bool IsDead() const;
    bool IsDecaying() const;
    void Draw() const;

    int GetDecayTicks() const
    {
        return _decayTicks;
    }

    void Update();

private:
    CellState _state;
    int _decayTicks;
};