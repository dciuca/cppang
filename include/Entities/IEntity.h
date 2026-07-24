#pragma once

#include <string>
#include "raylib.h"
#include <vector>

class IEntity
{
public:
	bool isActive;

	virtual ~IEntity() = default;

	// Pure virtual methods (must be implemented by derived classes)
	virtual void SetActive(bool active) = 0;
	virtual Vector2 GetPosition() = 0;
	virtual void SetPosition(Vector2 position) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetColor(Color newColor) = 0;
    virtual void SetTexture(const std::string &texturePath) = 0;

protected:
	Vector2 position = { 0,0 };
	Vector2 velocity = { 0,0 };
};