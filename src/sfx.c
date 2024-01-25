#include "raylib.h"

Sound PieceMoveSFX;
Sound PieceRotateRSFX;
Sound PieceRotateFailSFX;
Sound PieceTouchDownSFX;
Music MainTheme;

void InitSounds()
{

    PieceMoveSFX = LoadSound("Sounds/SFX_PieceMoveLR.ogg");
    PieceRotateRSFX = LoadSound("Sounds/SFX_PieceRotateLR.ogg");
    PieceRotateFailSFX = LoadSound("Sounds/SFX_PieceRotateFail.ogg");
    PieceTouchDownSFX = LoadSound("Sounds/SFX_PieceTouchDown.ogg");
    MainTheme = LoadMusicStream("Sounds/MainTheme.mp3");
    MainTheme.looping = true;
    PlayMusicStream(MainTheme);
    SetMusicVolume(MainTheme, 0.1f);
}
