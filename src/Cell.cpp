#include "Cell.h"
#include "raylib.h"

Cell::Cell(int x, int y, int z): CellColor{AliveColor}, _decayTicks(MaxDecayTicks), _state(CellState::Dead), GridX(x),
                                 GridY(y), GridZ(z), Position()
{
}

Color Cell::AliveColor = {0, 0, 0, 255};
Color Cell::DecayingColor = {50, 50, 50, 255};
Color Cell::DiedColor = RED;
float Cell::Size = 1.f;
int Cell::MaxDecayTicks = 6;

int Cell::GetState() const
{
    return static_cast<int>(_state);
}

void Cell::SetState(CellState state)
{
    if (state == CellState::Decaying && _state != CellState::Decaying)
    {
        _decayTicks = MaxDecayTicks;
    }

    _state = state;

    if (_state == CellState::Dead)
    {
        CellColor = {0, 0, 0, 0};
    }
    else if (_state == CellState::Decaying)
    {
        CellColor = DecayingColor;
    }
    else if (_state == CellState::Alive)
    {
        CellColor = AliveColor;
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
    return _state == CellState::Decaying && _decayTicks > 0;
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
        float fade = static_cast<float>(_decayTicks) / MaxDecayTicks;
        drawColor.a = static_cast<unsigned char>(fade * 200.f);
        
        /*if (_decayTicks == 1)
        {
            drawColor = DiedColor;
        }*/
    }

    DrawCube(Position, Size, Size, Size, drawColor);
    DrawCubeWires(Position, Size, Size, Size, RAYWHITE);
}

void Cell::Update()
{
    if (IsDecaying())
    {
        _decayTicks--;
    }
}