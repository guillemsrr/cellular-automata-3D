#include "InfiniteRule.h"

InfiniteRule::InfiniteRule()
{
    _neighboursAlive = {6, 7, 8, 9};
    _neighboursBorn = {4, 6, 9};
}

CellState InfiniteRule::GetCellState(Cell* cell)
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
        if (cell->GetDecayTicks() <= 0)
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