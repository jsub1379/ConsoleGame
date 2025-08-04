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

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
void Actor::Tick(float deltaTime)
{
}

// 그리기 함수.
void Actor::Render()
{

	// 커서 이동.
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(position);

	// 색상 설정.
	//SetConsoleTextAttribute(handle, (WORD)color);
	Utils::SetConsoleTextColor(color);

	//유니코드 문자로 변경
	const wchar_t* outChar = Utils::ConvertToWideChar(image);

	// 그리기.
	Utils::PrintWideCharacter(outChar);
	//std::wcout << outChar;
	
	//std::cout << image;

}	
void Actor::SetPosition(const Vector2& newPosition)
{
	//// 같으면 업데이트 안함.
	//if (position == newPosition)
	//{
	//	return;
	//}

	//// 지울 위치 확인.
	//Vector2 direction = newPosition - position;
	//position.x = direction.x >= 0 ? position.x : position.x + width - 1;

	// 커서 이동.
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