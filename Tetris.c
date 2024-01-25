#include <time.h>
#include "tetris.h"
#include "stage.h"
#define WINDOW_WIDHT 600
#define WINDOW_HEIGHT 700

const int startOffsetX = (WINDOW_WIDHT / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
const int startOffsetY = (WINDOW_HEIGHT / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

const int tetrominoStartX = STAGE_WIDTH / 2;
const int tetrominoStartY = 0;

int currentTetrominoX = tetrominoStartX;
int currentTetrominoY = tetrominoStartY;

int currentTetrominoType;
int currentRotation = 0;

const float moveTetrominoDownTimer = 1.f;
float timeToMoveTetrominoDown = moveTetrominoDownTimer;
int currentColor;

int main(int argc, char** argv, char** environ)
{

    currentTetrominoType = GetRandomValue(0, 6);
    
    currentColor = GetRandomValue(0, 7);

    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    InitWindow(WINDOW_WIDHT, WINDOW_HEIGHT, "Title");

    InitAudioDevice();
    
    InitSounds();

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        DrawOnScreen();
        UpdateMusicStream(MainTheme);
        timeToMoveTetrominoDown -= GetFrameTime();

        CheckInput();

        BeginDrawing();
        ClearBackground(GRAY);

        DrawCurrentGame();

        EndDrawing();
    }

    UnloadMusicStream(MainTheme);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}