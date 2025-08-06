#pragma once

#include "Actor/Actor.h"

class PlayerBullet : public Actor
{
    RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
    PlayerBullet(const Vector2& position);
    virtual void Tick(float deltaTime) override;

private:
    float speed = 20.0f;
    float xPosition = 0.0f;
};