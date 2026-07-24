#include "Player.h"
#include "raylib.h"

Player::Player(
    float x, 
    float y, 
    float width, 
    float height,
    Color color,
    const std::string& texturePath, 
    float speed
) : width(width), height(height), color(color), speed(speed), texture({0}), useTexture(false)
{
    position = { x, y };
    velocity = { 0, 0 };
    isActive = true;
    
    // Load texture if a path is provided
    if (!texturePath.empty()) {
        texture = LoadTexture(texturePath.c_str());
        useTexture = true;
    }
}

void Player::SetActive(bool active) {
    isActive = active;
}

Vector2 Player::GetPosition() {
    return position;
}

void Player::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

void Player::Update() {
    if (!isActive) return;

    HandleInput();

    // Update position based on velocity
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    // Clamp to screen
    ClampToScreen(GetScreenWidth());

    // Reset velocity for next frame
    velocity = { 0, 0 };
}

void Player::Draw() {
    if (!isActive) return;

    if (useTexture) {
        DrawTexture(texture, position.x, position.y, color);
    } else {
        DrawRectangle(position.x, position.y, width, height, color);
    }
}

void Player::HandleInput() {
    // Simple keyboard input handling
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocity.x = -speed;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocity.x = speed;
    }
}

void Player::ClampToScreen(int screenWidth) {
    if (position.x < 0) position.x = 0;
    if (position.x + width > screenWidth) position.x = screenWidth - width;
}

void Player::SetColor(Color newColor) {
    color = newColor;
}

void Player::SetTexture(const std::string& texturePath) {
    // Unload previous texture if it exists
    if (useTexture) {
        UnloadTexture(texture);
    }
    
    texture = LoadTexture(texturePath.c_str());
    useTexture = true;
}