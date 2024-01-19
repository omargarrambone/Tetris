#include "raylib.h"
#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 24
#define TETROMINO_SIZE 4


extern int score;
extern float speed;
extern Sound PieceMoveSFX;
extern Sound PieceRotateRSFX;
extern Sound PieceRotateFailSFX;
extern Sound PieceTouchDownSFX;
extern Music MainTheme;

int CheckCollision(const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void ResetLines(int startLineY);
void DeleteLines();
