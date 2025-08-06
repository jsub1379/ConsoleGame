#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"
#include "Level/EscMenuLevel.h"
#include "Level/UpgradeMenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 메인 레벨 추가.
	AddLevel(new GameLevel());

	// 메뉴 레벨 생성.
	menuLevel = new MenuLevel();
	escmenuLevel = new EscMenuLevel();
	upgrademenuLevel = new UpgradeMenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu(int menu)
{
	// 화면 정리.
	// clear screen 명령어 실행.
	system("cls");

	// 토글 처리.
	showMenu = !showMenu;

	if (showMenu)
		//여기서 메뉴 종류 파악
	{
		// 현재 레벨을 뒤로 밀기.
		backLevel = mainLevel;

		//ESC 메뉴
		if (menu == MenuType::ESC_MENU)
		{
			mainLevel = escmenuLevel;
		}
		//게임 레벨로 RETURN 
		else if (menu == MenuType::RETURN_MENU)
		{
			mainLevel = backLevel;
		}
		//스테이지 끝난 업데이트 창 메뉴
		else if (menu == MenuType::UPGRADE_MENU)
		{
			mainLevel = upgrademenuLevel;
		}

		//??
		else
		{
			mainLevel = menuLevel;
		}


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
	SafeDelete(upgrademenuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}