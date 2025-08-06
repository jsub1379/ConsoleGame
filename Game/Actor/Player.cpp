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
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(3);
	xPosition = (float)position.x;
	yPosition = (float)position.y;
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// �������̽� ������.
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

	// ESC: �޴� ����.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu(MenuType::ESC_MENU);
		return;
	}

	// �Է�ó��.

	// �̵� ���� - �̵��ϱ� ���� �̵��� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�.
	if (Input::Get().GetKey(VK_RIGHT))
	{
		// �̵� ���� �̵� �������� Ȯ��.
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

	//�Ѿ� �߻�
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		Vector2 position = Position();
		owner->AddActor(new PlayerBullet(position));
	}
}