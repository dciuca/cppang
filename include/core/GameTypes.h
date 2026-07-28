#pragma once

enum class ShapeType
{
    CIRCLE,
    RECTANGLE
};

enum class GameStateRequest
{
    None,
    ChangeToPlaying,
    ChangeToMenu,
    ChangeToGameOver,
    Quit
};