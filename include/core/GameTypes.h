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
    ChangeToMenu,
    ChangeToLevelComplete,
    ChangeToNextLevel,
    ChangeToGameOver,
    PauseGame,
    ResumeGame,
    Quit
};

enum class CollectibleType
{
    None,
    Clock
};