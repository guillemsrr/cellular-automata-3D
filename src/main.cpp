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
const float updateInterval = 0.1f;
bool autoUpdate = true;
Camera camera;
const int fontSize = 20;

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
    cellularAutomata.Randomize();
    camera.target = {0.0f, cellularAutomata.GetDimensions().y / 2.f, 0.0f};
}

int main()
{
    int addition = 5;

    CellularAutomata cellularAutomata;
    cellularAutomata.Initialize();
    cellularAutomata.SetRule(std::make_shared<InfiniteRule>());

    int window = 800;
    //window = 2000;
    InitWindow(window, window, "Cellular Automata");
    SetTargetFPS(60);

    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    float angleYaw = 0.0f;
    float anglePitch = 20.0f * DEG2RAD;
    float camDistance = cellularAutomata.GetDimensions().x * 3.f;

    Vector2 lastMouse = GetMousePosition();

    Reset(cellularAutomata);

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
        camDistance = Clamp(camDistance, 2.0f, cellularAutomata.GetDimensions().x * 100.f);

        float x = camDistance * cosf(anglePitch) * sinf(angleYaw);
        float y = cellularAutomata.GetDimensions().y / 2.f + camDistance * sinf(anglePitch);
        float z = camDistance * cosf(anglePitch) * cosf(angleYaw);

        camera.position = Vector3{x, y, z};

        if (IsKeyPressed(KEY_R))
        {
            Reset(cellularAutomata);
        }

        if (IsKeyPressed(KEY_ONE))
        {
            cellularAutomata.SetDefault();
            cellularAutomata.SetRule(std::make_shared<InfiniteRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            cellularAutomata.SetDefault();
            cellularAutomata.SetAliveProbability(0.5f);
            cellularAutomata.SetDimensions(60, 60, 1);
            cellularAutomata.SetRule(std::make_shared<GameOfLifeRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            cellularAutomata.SetDefault();
            cellularAutomata.SetAliveProbability(0.065f);
            cellularAutomata.SetRule(std::make_shared<ExpandingRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            cellularAutomata.SetDefault();
            cellularAutomata.SetAliveProbability(0.055f);
            cellularAutomata.SetRule(std::make_shared<FocusedRule>());
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_FIVE))
        {
            cellularAutomata.SetDefault();
            cellularAutomata.SetAliveProbability(0.055f);
            cellularAutomata.SetRule(std::make_shared<InfiniteRule>());
            Reset(cellularAutomata);
        }

        if (IsKeyPressed(KEY_C))
        {
            Cell::AliveColor = DARKGREEN;
            Cell::DecayingColor = GREEN;
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
            cellularAutomata.AddDimensions(addition, addition, addition);
            Reset(cellularAutomata);
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            cellularAutomata.AddDimensions(-addition, -addition, -addition);
            Reset(cellularAutomata);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        cellularAutomata.Draw();
        EndMode3D();

        const char* ruleText = TextFormat("Rule: %s", cellularAutomata.GetRule()->GetName());
        const char* dimensionUpText = "Dimension ++: Arrow up";
        const char* dimensionDownText = "Dimension --: Arrow down";
        DrawText(ruleText, 10, 10, fontSize, BLACK);
        DrawText(dimensionUpText, 10, 40, fontSize, BLACK);
        DrawText(dimensionDownText, 10, 80, fontSize, BLACK);
        DrawFPS(window - 100, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}