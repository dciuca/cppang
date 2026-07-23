#include "Player.h"
#include "raylib.h"

Player::Player(float x, float y) : speed(300.0f), width(20.0f), height(50.0f) {
    position = { x, y };
    velocity = { 0, 0 };
    isActive = true;
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

    // Reset velocity for next frame
    velocity = { 0, 0 };
}

void Player::Draw() {
    if (!isActive) return;

    DrawRectangle(position.x, position.y, width, height, BLUE);
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