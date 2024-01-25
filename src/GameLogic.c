#include "tetris.h"
#include <string.h>

int score = 0;
float speed = 0;
extern int stage[];
extern const int *tetrominoTypes[7][4];


void ResetLines(int startLineY)
{
    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int offset_below = (y + 1) * STAGE_WIDTH + x;

            if (stage[offset_below] == 0 && stage[offset] > 0)
            {
                stage[offset_below] = stage[offset];
                stage[offset] = 0;
            }
        }
    }   
}

void DeleteLines()
{
    Sound LineClearSFX = LoadSound("Sounds/SFX_SpecialLineClearTriple.ogg");

    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;

        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
                checkLine = 0;
                break;
            }
        }

        if(checkLine)
        {
            const int offset = y * STAGE_WIDTH + 1;            
            memset(stage + offset, 0, (STAGE_WIDTH-2) * sizeof(int)); //set all the bit of the line to 0
            PlaySound(LineClearSFX);
            ResetLines(y);
            score += 100;
            if(speed == 0.8f)
            {
                speed = 0.8f;
            }
            else
            {
                speed += 0.1;
            }            
        }
    }

    UnloadSound(LineClearSFX);
}


void CheckInput()
{
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
}