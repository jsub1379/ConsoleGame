#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

//#include<fcntl.h>
#include <io.h>

Actor::Actor(const char image, Color color, const Vector2& position)
	: image(image), color(color), position(position)
{
}

Actor::~Actor()
{
}

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Actor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
void Actor::Render()
{

	// Ŀ�� �̵�.
	Utils::SetConsolePosition(position);

	// ���� ����.
	Utils::SetConsoleTextColor(color);

	//�����ڵ� ���ڷ� ����
	const wchar_t* outChar = Utils::ConvertToWideChar(image);

	// �׸���.
	Utils::PrintWideCharacter(outChar);
	//std::wcout << outChar;
	
	//std::cout << image;

}	


void Actor::SetPosition(const Vector2& newPosition)
{
	//����� �̵� ���� ������ player.h���� �ϰ� ����
	//���Ŀ� �ű� ����, �ϴ� test�� ���� �α�

	Utils::SetConsolePosition(position);

	Utils::PrintWideCharacter(L" ");

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

bool Actor::TestIntersect(const Actor* const other)
{
	// AABB(Axis Aligned Bounding Box).
	// Note: ���� ���� ���� �� ���δ� ũ�Ⱑ ����(ũ�Ⱑ 1).
	//       ���� ������ �ּ�/�ִ� ��ġ�� �� ����ϸ� ��.

	// �� ������ x ��ǥ ����.
	int xPos = position.x;
	int yPos = position.y;
	// �浹 ���� �ٸ� ������ x ��ǥ ����.
	int otherxPos = other->position.x;
	int otheryPos = other->position.y;

	if (xPos == otherxPos && yPos == otheryPos) return true;
	else return false;
	//�Ϲ������� �Ʒ��� ���� �����ϳ�, 1x1 ũ���̹Ƿ� �� �����ϰ� ǥ��
	// 	// �Ȱ�ġ�� ���� Ȯ��.
	//// �ٸ� ������ ���� ��ǥ�� �� ������ ��ǥ���� �� �����ʿ� ������ �Ȱ�ħ.
	//if (otherXMin > xMax)
	//{
	//	return false;
	//}
	//// �ٸ� ������ ������ ��ǥ�� �� ���� ��ǥ���� �� ���ʿ� ������ �Ȱ�ħ.
	//if (otherXMax < xMin)
	//{
	//	return false;
	//}

	//// y ��ǥ�� ������ ���� Ȯ��.
	//return position.y == other->position.y;
}


void Actor::Destroy()
{
	// �ߺ� ���� ���� ó��.
	if (isExpired)
	{
		return;
	}

	// ���� ��û �Ǿ��ٰ� ����.
	isExpired = true;

	// ������ ���� ��û.
	owner->DestroyActor(this);
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}