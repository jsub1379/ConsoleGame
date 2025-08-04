#include "TestActor.h"
#include <iostream>
#include "Engine.h"
#include "Input.h"

#include <Windows.h>

TestActor::TestActor()
	: Actor('P', Color::Red)
{
}

void TestActor::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	//std::cout 
	//	<< "TestActor::Tick. FPS: " 
	//	<< (1.0f / deltaTime) 
	//	<< "\n";

	if (Input::Get().GetKey(VK_RIGHT) && Position().x < 30)
	{
		Vector2 position = Position();
		position.x += 1;
		SetPosition(position);
	}

	if (Input::Get().GetKey(VK_LEFT) && Position().x > 0)
	{
		Vector2 position = Position();
		position.x -= 1;
		SetPosition(position);
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}
}