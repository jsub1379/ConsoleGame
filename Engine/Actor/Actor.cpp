#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Math/Color.h"

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
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(position);

	// ���� ����.
	//SetConsoleTextAttribute(handle, (WORD)color);
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
	//// ������ ������Ʈ ����.
	//if (position == newPosition)
	//{
	//	return;
	//}

	//// ���� ��ġ Ȯ��.
	//Vector2 direction = newPosition - position;
	//position.x = direction.x >= 0 ? position.x : position.x + width - 1;

	// Ŀ�� �̵�.
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(position);

	//std::cout << ' ';
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

void Actor::QuitGame()
{
	Engine::Get().Quit();
}