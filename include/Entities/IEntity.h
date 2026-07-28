#pragma once

#include <string>
#include "raylib.h"

class IEntity
{
public:
    bool isActive;
    Vector2 position = {0, 0};
    Vector2 velocity = {0, 0};
    float speed = 0.0f;

public:
    virtual ~IEntity() = default;

    virtual void SetActive(bool active) = 0;
    virtual void SetColor(Color newColor) = 0;
    virtual void SetTexture(const std::string &texturePath) = 0;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

// class IEntity {
// public:
//     virtual ~IEntity() = default;

//     // === Stato ===
//     virtual bool IsActive() const = 0;
//     virtual void SetActive(bool active) = 0;

//     // === Posizione ===
//     virtual Vector2 GetPosition() const = 0;
//     virtual void SetPosition(const Vector2& position) = 0;

//     // === Velocità ===
//     virtual Vector2 GetVelocity() const = 0;
//     virtual void SetVelocity(const Vector2& velocity) = 0;

//     // === Velocità massima ===
//     virtual float GetSpeed() const = 0;
//     virtual void SetSpeed(float speed) = 0;

//     // === Grafica ===
//     virtual Color GetColor() const = 0;
//     virtual void SetColor(Color color) = 0;

//     virtual std::string GetTexturePath() const = 0;
//     virtual void SetTexture(const std::string& texturePath) = 0;

//     // === Game Loop ===
//     virtual void Update(float deltaTime) = 0;  // Passa il delta time!
//     virtual void Draw() const = 0;             // const!
// };