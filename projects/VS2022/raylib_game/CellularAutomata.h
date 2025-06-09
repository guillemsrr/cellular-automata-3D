// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "Grid.h"
#include "Rules/IRule.h"
#include <memory>

class CellularAutomata
{
public:
    CellularAutomata();
    void SetRule(std::shared_ptr<IRule> rule);
    void Randomize(float probability = 0.2f);
    void Update();
    void Draw() const;

    void SetGrid(Grid* grid);

private:
    Grid* _grid;
    std::shared_ptr<IRule> rule;
};