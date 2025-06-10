// Copyright (c) Guillem Serra. All Rights Reserved.

#include <raylib.h>
#include <raymath.h>
#include <memory>

#include "CellularAutomata.h"

#include "Rules/InfiniteRule.h"
#include "Rules/GameOfLifeRule.h"
#include "Rules/ExpandingRule.h"
#include "Rules/FocusedRule.h"

float lastUpdateTime = 0.f;
const float updateInterval = 0.2f;
float probability = 0.2f;

bool ShouldUpdate()
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= updateInterval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

void Reset(CellularAutomata& cellularAutomata)
{
    lastUpdateTime = GetTime();
    cellularAutomata.Randomize(probability);
}

int main()
{
    int width = 30;
    int height = 30;
    int depth = width;
    int addition = 5;
    bool autoUpdate = true;

    CellularAutomata cellularAutomata;
    Grid grid;
    grid.SetDimensions(width, height, depth);
    cellularAutomata.SetGrid(&grid);

    cellularAutomata.SetRule(std::make_shared<InfiniteRule>());
    cellularAutomata.Randomize(probability);

    int window = 800;
    //window = 2000;
    InitWindow(window, window, "Cellular Automata");
    SetTargetFPS(60);

    Camera camera;
    camera.target = {0.0f, height / 2.f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    float angleYaw = 0.0f;
    float anglePitch = 20.0f * DEG2RAD;
    float camDistance = width * 3.f;

    Vector2 lastMouse = GetMousePosition();

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        Vector2 delta = Vector2Subtract(mouse, lastMouse);
        lastMouse = mouse;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            angleYaw -= delta.x * 0.01f;
            anglePitch -= delta.y * 0.01f;
            anglePitch = Clamp(anglePitch, -PI / 2 + 0.01f, PI / 2 - 0.01f);
        }

        camDistance -= GetMouseWheelMove();
        camDistance = Clamp(camDistance, 2.0f, width * 100.f);

        float x = camDistance * cosf(anglePitch) * sinf(angleYaw);
        float y = height / 2.f + camDistance * sinf(anglePitch);
        float z = camDistance * cosf(anglePitch) * cosf(angleYaw);

        camera.position = Vector3{x, y, z};

        if (IsKeyPressed(KEY_R))
        {
            Reset(cellularAutomata);
        }

        if (IsKeyPressed(KEY_ONE))
        {
            probability = 0.2f;
            cellularAutomata.SetRule(std::make_shared<InfiniteRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            probability = 0.3f;
            cellularAutomata.SetRule(std::make_shared<GameOfLifeRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            probability = 0.065f;
            cellularAutomata.SetRule(std::make_shared<ExpandingRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            probability = 0.055f;
            cellularAutomata.SetRule(std::make_shared<FocusedRule>());
            Reset(cellularAutomata);
        }

        if (autoUpdate)
        {
            if (ShouldUpdate())
            {
                cellularAutomata.Update();
            }
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                cellularAutomata.Update();
            }
        }

        if (IsKeyPressed(KEY_UP))
        {
            width += addition;
            height += addition;
            depth += addition;
            grid.SetDimensions(width, height, depth);
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            width -= addition;
            height -= addition;
            depth -= addition;
            grid.SetDimensions(width, height, depth);
            Reset(cellularAutomata);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        cellularAutomata.Draw();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}