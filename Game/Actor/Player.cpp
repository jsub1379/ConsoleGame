#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"

#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include "Actor/PlayerBullet.h"

#include <iostream>

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{
	// 그릴 때 사용할 정렬 순서 설정.
	SetSortingOrder(3);
	xPosition = (float)position.x;
	yPosition = (float)position.y;
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// 인터페이스 얻어오기.
	if (GetOwner())
	{
		canPlayerMoveInterface 
			= dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// ESC: 메뉴 진입.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu(MenuType::ESC_MENU);
		return;
	}

	// 입력처리.

	// 이동 로직 - 이동하기 전에 이동할 위치로 갈 수 있는지 판단 후 이동.
	if (Input::Get().GetKey(VK_RIGHT))
	{
		// 이동 전에 이동 가능한지 확인.
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2((int)Position().x + 1, Position().y)))
		{
			xPosition += xspeed * deltaTime;
			SetPosition(Vector2((int)xPosition, (int)yPosition));
		}
	}

	if (Input::Get().GetKey(VK_LEFT))
	{
		if(canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2((int)Position().x - 1, Position().y)))
		{
			xPosition -= xspeed * deltaTime;
			SetPosition(Vector2((int)xPosition, (int)yPosition));
		}
	}

	if (Input::Get().GetKey(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, (int)Position().y - 1)))
		{
			yPosition -= yspeed * deltaTime;
			SetPosition(Vector2((int)xPosition, (int)yPosition));
		}
	}

	if (Input::Get().GetKey(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, (int)Position().y + 1)))
		{
			yPosition += yspeed * deltaTime;
			SetPosition(Vector2((int)xPosition, (int)yPosition));
		}
	}

	//총알 발사
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		Vector2 position = Position();
		owner->AddActor(new PlayerBullet(position));
	}
}