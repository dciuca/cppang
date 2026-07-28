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
    virtual Vector2 GetDimensions() = 0;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};