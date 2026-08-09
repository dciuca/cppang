#pragma once

static constexpr float BORDER_OFFSET = 22.0f;

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