#include "FocusedRule.h"

FocusedRule::FocusedRule()
{
    _neighboursAlive = {2, 6, 9};
    _neighboursBorn = {5, 8, 9};
}

CellState FocusedRule::GetCellState(Cell* cell)
{
    int neighborCount = 0;
    for (auto neighbor : cell->CachedNeighbors)
    {
        if (neighbor->IsAlive())
        {
            neighborCount++;
        }
    }

    if (cell->IsAlive())
    {
        if (std::find(_neighboursAlive.begin(), _neighboursAlive.end(), neighborCount) != _neighboursAlive.end())
        {
            return CellState::Alive;
        }
        return CellState::Decaying;
    }

    if (cell->IsDecaying())
    {
        if (--cell->decayTicks <= 0)
        {
            return CellState::Dead;
        }
        return CellState::Decaying;
    }

    if (std::find(_neighboursBorn.begin(), _neighboursBorn.end(), neighborCount) != _neighboursBorn.end())
    {
        return CellState::Alive;
    }

    return CellState::Dead;
}