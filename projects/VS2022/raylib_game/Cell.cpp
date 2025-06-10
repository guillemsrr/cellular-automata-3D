#include "Cell.h"
#include "raylib.h"

Cell::Cell(int x, int y, int z): CellColor(GREEN), decayTicks(MaxDecayTicks), _state(CellState::Dead), GridX(x),
                                 GridY(y), GridZ(z), Position()
{
}

int Cell::GetState() const
{
    return static_cast<int>(_state);
}

void Cell::SetState(CellState state)
{
    if (state == CellState::Decaying && _state != CellState::Decaying)
    {
        decayTicks = MaxDecayTicks;
    }

    _state = state;

    if (_state == CellState::Dead)
    {
        CellColor = {0, 0, 0, 0};
    }
    else if (_state == CellState::Decaying)
    {
        CellColor = {100, 100, 100, 255};
    }
    else if (_state == CellState::Alive)
    {
        CellColor = {0, 0, 0, 255};
    }
}

bool Cell::IsAlive() const
{
    return _state == CellState::Alive;
}

bool Cell::IsDead() const
{
    return _state == CellState::Dead;
}

bool Cell::IsDecaying() const
{
    return _state == CellState::Decaying && decayTicks > 0;
}

void Cell::Draw() const
{
    if (IsDead())
    {
        return;
    }

    Color drawColor = CellColor;

    if (IsDecaying())
    {
        float fade = static_cast<float>(decayTicks) / MaxDecayTicks;
        drawColor.a = static_cast<unsigned char>(fade * 255.f);
    }

    DrawCube(Position, Size, Size, Size, drawColor);
    DrawCubeWires(Position, Size, Size, Size, RAYWHITE);
}