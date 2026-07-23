#pragma once

#include <string>
#include "IEntity.h"
#include "raylib.h"

class Player : public IEntity
{
public:
    Player(
        float x, 
        float y,
        float width = 20.0f, 
        float height = 50.0f, 
        Color color = BLUE,
        const std::string& texturePath = "",
        float speed = 300.0f
    );
    ~Player() = default;

    // Implementation of pure virtual methods from IEntity
    void SetActive(bool active) override;
    Vector2 GetPosition() override;
    void SetPosition(Vector2 position) override;
    void Update() override;
    void Draw() override;

    // Player-specific methods
    void HandleInput();
    void ClampToScreen(int screenWidth);
    void SetColor(Color newColor);
    void SetTexture(const std::string& texturePath);

private:
    float speed;
    float width;
    float height;
    Color color;
    Texture2D texture;
    bool useTexture;
};