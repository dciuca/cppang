#pragma once

#include <string>
#include "raylib.h"
#include "GameTypes.h"

class IEntity
{
public:
    Vector2 position = {0, 0};
    Vector2 velocity = {0, 0};
    float speed = 0.0f;

public:
    virtual ~IEntity() = default;

    // default implementations
    void SetActive(bool active) { this->isActive = active; };
    bool IsActive() const { return isActive; };
    void SetTexture(const Texture2D &t)
    {
        texture = t;
        useTexture = true;
    };
    Texture2D GetTexture() const { return texture; };

    // pure virtual
    virtual Vector2 GetDimensions() const = 0;
    virtual void SetColor(const Color &newColor) = 0;
    virtual ShapeType GetShapeType() const = 0;
    virtual void Update() = 0;
    virtual void Draw() const = 0;

private:
    bool isActive = false;

protected:
    bool useTexture = false;
    Texture2D texture;
};