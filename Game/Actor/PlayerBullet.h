#pragma once

#include "Actor/Actor.h"

/*
* �÷��̾ �߻��ϴ� ź��.
* - ȭ�� ���� �̵�.
*   - �ӷ�(������, �� ����), �� ����
*/
class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
	PlayerBullet(const Vector2& startPosition);

	virtual void Tick(float deltaTime) override;

private:
	// �ʴ� 5ĭ.
	float speed = 100.0f;

};