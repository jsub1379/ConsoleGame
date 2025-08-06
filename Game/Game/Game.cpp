#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"
#include "Level/EscMenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 메인 레벨 추가.
	AddLevel(new GameLevel());

	// 메뉴 레벨 생성.
	menuLevel = new MenuLevel();
	escmenuLevel = new EscMenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu(const char* menuType = " ")
{
	// 화면 정리.
	// clear screen 명령어 실행.
	system("cls");

	// 토글 처리.
	showMenu = !showMenu;

	if (showMenu)
		//여기서 메뉴 종류 파악
	{
		// 게임 레벨을 뒤로 밀기.
		backLevel = mainLevel;

		// 메뉴 레벨을 메인 레벨로 설정.
		if (menuType=="ESC")
		{
			mainLevel = escmenuLevel;
		}
		else
		{
			mainLevel = menuLevel;
		}
	}
	else
	{
		// 게임 레벨을 메인 레벨로 설정.
		mainLevel = backLevel;
	}
}

void Game::CleanUp()
{
	// 이때는 Engine의 mainLevel이 menuLevel.
	if (showMenu)
	{
		// 게임 레벨 제거.
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//// mainLevel이 게임 레벨 -> 이때는 Engine에서 하던데로 정리하면 됨.
	//else
	//{
	//
	//}

	SafeDelete(menuLevel);
	SafeDelete(escmenuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}