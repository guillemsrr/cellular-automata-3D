// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "Grid.h"
#include "Rules/IRule.h"
#include <memory>

class CellularAutomata
{
public:
    CellularAutomata();
    void Initialize();
    void SetRule(std::shared_ptr<IRule> rule);
    void SetDefault();
    void Randomize();
    void Update();
    void Draw() const;

    Vector3 GetDimensions() const;
    void SetAliveProbability(float probability);
    void SetDimensions(int x, int y, int z);
    void AddDimensions(int x, int y, int z);
    IRule* GetRule();

private:
    float _probability;
    Grid* _grid;
    std::shared_ptr<IRule> _rule;
};