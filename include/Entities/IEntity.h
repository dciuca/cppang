#pragma once

#include "raylib.h"  // Include raylib header for Vector2
#include <vector>

class IEntity
{
public:
	bool isActive;

	// Virtual destructor for proper cleanup
	virtual ~IEntity() = default;

	// Pure virtual methods (must be implemented by derived classes)
	virtual void SetActive(bool active) = 0;
	virtual Vector2 GetPosition() = 0;
	virtual void SetPosition(Vector2 position) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	bool active = false;
	Vector2 position = { 0,0 };
	Vector2 velocity = { 0,0 };
};