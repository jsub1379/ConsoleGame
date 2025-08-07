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
	Utils::SetConsolePosition(position);

	// 색상 설정.
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
	//현재는 이동 관련 설정을 player.h에서 하고 있음
	//추후에 옮길 예정, 일단 test를 위해 두기

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
	// Note: 현재 액터 구조 상 세로는 크기가 없음(크기가 1).
	//       따라서 가로의 최소/최대 위치만 더 고려하면 됨.

	// 이 액터의 x 좌표 정보.
	int xPos = position.x;
	int yPos = position.y;
	// 충돌 비교할 다른 액터의 x 좌표 정보.
	int otherxPos = other->position.x;
	int otheryPos = other->position.y;

	if (xPos == otherxPos && yPos == otheryPos) return true;
	else return false;
	//일반적으로 아래와 같이 구현하나, 1x1 크기이므로 더 간단하게 표현
	// 	// 안겹치는 조건 확인.
	//// 다른 액터의 왼쪽 좌표가 내 오른쪽 좌표보다 더 오른쪽에 있으면 안겹침.
	//if (otherXMin > xMax)
	//{
	//	return false;
	//}
	//// 다른 액터의 오른쪽 좌표가 내 왼쪽 좌표보다 더 왼쪽에 있으면 안겹침.
	//if (otherXMax < xMin)
	//{
	//	return false;
	//}

	//// y 좌표가 같은지 최종 확인.
	//return position.y == other->position.y;
}


void Actor::Destroy()
{
	// 중복 삭제 방지 처리.
	if (isExpired)
	{
		return;
	}

	// 삭제 요청 되었다고 설정.
	isExpired = true;

	// 레벨에 삭제 요청.
	owner->DestroyActor(this);
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}