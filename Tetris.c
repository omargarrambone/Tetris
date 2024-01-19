#include <time.h>
#include "tetris.h"
#include "stage.h"
#define WINDOW_WIDHT 600
#define WINDOW_HEIGHT 700


int main(int argc, char** argv, char** environ)
{
    const int startOffsetX = (WINDOW_WIDHT / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
    const int startOffsetY = (WINDOW_HEIGHT / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

    const int tetrominoStartX = STAGE_WIDTH / 2;
    const int tetrominoStartY = 0;

    int currentTetrominoX = tetrominoStartX;
    int currentTetrominoY = tetrominoStartY;

    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    int currentTetrominoType = GetRandomValue(0, 6);
    int currentRotation = 0;

    const float moveTetrominoDownTimer = 1.f;
    float timeToMoveTetrominoDown = moveTetrominoDownTimer;
    int currentColor = GetRandomValue(0, 7);

    TraceLog(LOG_INFO, "Number of arguments : %d", argc);

    for(int i = 0; i < argc; i++)
    {
        TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    }

    while(*environ != 0)
    {
        TraceLog(LOG_INFO, "Argument : %s", *environ);
        environ++;
    }

    InitWindow(WINDOW_WIDHT, WINDOW_HEIGHT, "Title");

    InitAudioDevice();
    
    MainTheme.looping = true;
    PlayMusicStream(MainTheme);
    SetMusicVolume(MainTheme, 0.1f);

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        DrawText(TextFormat("Score: %08i", score), 400, 10, 20, RED);
        DrawText(TextFormat("speed: %0.1f", speed), 10, 10, 20, RED);
        UpdateMusicStream(MainTheme);
        timeToMoveTetrominoDown -= GetFrameTime();

        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = currentRotation;

            currentRotation++;

            if (currentRotation > 3)
            {
                currentRotation = 0;
            }

            if (CheckCollision(currentTetrominoX,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                PlaySound(PieceRotateFailSFX);
                currentRotation = lastRotation;
            }
            else
                PlaySound(PieceRotateRSFX);
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX+1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                PlaySound(PieceMoveSFX);
                currentTetrominoX++;
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX-1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                PlaySound(PieceMoveSFX);
                currentTetrominoX--;
            }
        }

        if(timeToMoveTetrominoDown - speed <= 0 || IsKeyPressed(KEY_DOWN))
        {            
            if(!CheckCollision(currentTetrominoX,currentTetrominoY+1,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                PlaySound(PieceMoveSFX);
                currentTetrominoY++;
                timeToMoveTetrominoDown = moveTetrominoDownTimer;
            }

            else
            {
                for(int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for(int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;

                        const int *tetromino = tetrominoTypes[currentTetrominoType][currentRotation];

                        if(tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + currentTetrominoY) * STAGE_WIDTH + (x + currentTetrominoX);

                            stage[offset_stage] = currentColor + 1;
                            PlaySound(PieceTouchDownSFX);
                        }
                    }
                }

                DeleteLines();

                currentTetrominoX = tetrominoStartX;
                currentTetrominoY = tetrominoStartY;

                currentTetrominoType = GetRandomValue(0, 6);
                currentRotation = 0;
                currentColor = GetRandomValue(0, 7);
                score += 10;
            }
        }

        BeginDrawing();
        ClearBackground(GRAY);

        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            for(int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;
                const int color = stage[offset];

                if(stage[offset] != 0)
                {
                    DrawRectangle(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color-1]);
                }

                DrawRectangleLines(x * TILE_SIZE + startOffsetX, y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, BLACK);
            }
        }
        
        drawTetromino(colorTypes[currentColor], startOffsetX, startOffsetY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);    

        EndDrawing();
    }

    UnloadMusicStream(MainTheme);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}