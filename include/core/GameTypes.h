#pragma once

enum class ShapeType
{
    CIRCLE,
    RECTANGLE
};

enum class GameStateRequest
{
    None,
    ChangeToNextLevel,
    ChangeToMenu,
    ChangeToGameOver,
    PauseGame,
    ResumeGame,
    Quit
};