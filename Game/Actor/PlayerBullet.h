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
//    float speed = 10.0f; // ���������� �ʴ� 10ĭ
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
    // �������̽� ���� ����.
    class ICanPlayerMove* canPlayerMoveInterface = nullptr;
    float speed = 70.0f;
};