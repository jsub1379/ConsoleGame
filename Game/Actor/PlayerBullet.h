#pragma once

#include "Actor/Actor.h"

/*
* 플레이어가 발사하는 탄약.
* - 화면 위로 이동.
*   - 속력(빠르기, 초 단위), 위 방향
*/
class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet, Actor)

public:
	PlayerBullet(const Vector2& startPosition);

	virtual void Tick(float deltaTime) override;

private:
	// 초당 5칸.
	float speed = 100.0f;

};