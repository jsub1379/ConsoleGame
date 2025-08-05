//#pragma once
//#include "Actor/Actor.h"
//
//class PlayerBullet : public Actor
//{
//public:
//    PlayerBullet(const Vector2& position);
//
//    virtual void Tick(float deltaTime) override;
//
//private:
//    float speed = 10.0f; // 오른쪽으로 초당 10칸
//};
#pragma once

#include "Actor/Actor.h"

class PlayerBullet : public Actor
{
    RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
    PlayerBullet(const Vector2& position);
    virtual void Tick(float deltaTime) override;

private:
    // 인터페이스 참조 변수.
    class ICanPlayerMove* canPlayerMoveInterface = nullptr;
    float speed = 70.0f;
};