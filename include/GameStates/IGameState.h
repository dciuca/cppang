#pragma once
#include "GameTypes.h"
#include "raylib.h"

class IGameState
{
public:
    virtual ~IGameState() = default;

    virtual void HandleInput() = 0;
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Cleanup() {};
    virtual void Draw() const = 0;
    virtual void Exit() = 0;

public:
    GameStateRequest GetGameStateRequest() const
    {
        return gameStateRequest;
    }

protected:
    void RequestStateChange(GameStateRequest request)
    {
        gameStateRequest = request;
    }

    GameStateRequest gameStateRequest = GameStateRequest::None;

protected:
    Font customFont = LoadFont("assets/fonts/spicysale.ttf");
};