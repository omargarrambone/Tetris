#include "tetris.h"
#include <string.h>

int score = 0;
float speed = 0;
extern int stage[];


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