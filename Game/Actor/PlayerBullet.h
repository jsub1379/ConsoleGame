#pragma once

#include "Actor/Actor.h"

class PlayerBullet : public Actor
{
    RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
    PlayerBullet(const Vector2& position, const Vector2& direction);
    virtual void Tick(float deltaTime) override;

private:
    float speed = 20.0f;
    float xPosition = 1.0f;
    float yPosition = 3.0f;
    int xDirection = 1;
    int yDirection = 0;
};