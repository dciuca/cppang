#pragma once

#include <string>
#include "IEntity.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(
        float x = 400.0f,
        float y = 550.0f,
        float width = 20.0f,
        float height = 50.0f,
        Color color = BLUE,
        const std::string &texturePath = "",
        float speed = 300.0f);
    ~Player() = default;

    // Implementation of pure virtual methods from IEntity
    void SetActive(bool active) override;
    Vector2 GetPosition() override;
    void SetPosition(Vector2 position) override;
    void SetColor(Color newColor) override;
    void SetTexture(const std::string &texturePath) override;
    void Update() override;
    void Draw() override;

    // Implementation of specific methods for Player
    void HandleInput();
    void ClampToScreen(int screenWidth);

private:
    float speed;
    float width;
    float height;
    Color color;
    Texture2D texture;
    bool useTexture;
};