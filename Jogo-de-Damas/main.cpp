#include <raylib.h>

int main()
{
    InitWindow(800, 450, "Jogo de Damas");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Jogo de Damas", 250, 200, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
