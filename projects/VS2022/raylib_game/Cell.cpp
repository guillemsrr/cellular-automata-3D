#include "Cell.h"
#include "raylib.h"

Cell::Cell(int x, int y, int z): CellColor(GREEN), _state(CellState::Dead), GridX(x), GridY(y), GridZ(z), Position()
{
}

int Cell::GetState() const
{
    return static_cast<int>(_state);
}

void Cell::SetState(CellState state)
{
    _state = state;
    if (_state == CellState::Dead)
    {
        CellColor = {0, 0, 0, 0}; // Fully transparent
    }
    else if (_state == CellState::Decaying)
    {
        CellColor = {0, 220, 0, 128};
    }
    else if (_state == CellState::Alive)
    {
        CellColor = {0, 255, 0, 200};
    }
}

bool Cell::IsAlive()
{
    return _state == CellState::Alive;
}

bool Cell::IsDead()
{
    return _state == CellState::Dead;
}

void Cell::Draw()
{
    if (IsDead())
    {
        return;
    }
    DrawCube(Position, Size, Size, Size, CellColor);
    DrawCubeWires(Position, Size, Size, Size, BLACK);
}