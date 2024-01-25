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

extern const int tetrominoStartX;
extern const int tetrominoStartY;
extern int currentTetrominoX;
extern int currentTetrominoY;
extern int currentTetrominoType;
extern int currentRotation;
extern const float moveTetrominoDownTimer;
extern float timeToMoveTetrominoDown;
extern int currentColor;
extern const int startOffsetX;
extern const int startOffsetY;



int CheckCollision(const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void ResetLines(int startLineY);
void DeleteLines();
void InitSounds();
void DrawOnScreen();
void CheckInput();
void DrawCurrentGame();
