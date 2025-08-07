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
	//AddLevel(new GameLevel());

	// 메뉴 레벨 생성.
	//menuLevel = new MenuLevel();
	//escMenuLevel = new EscMenuLevel();
	//upgrademenuLevel = new UpgradeMenuLevel();
	currentStageIndex = 1;
	GameStart();
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

	// 메뉴를 앞에 보여줘야 할 때.
	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	// 게임 레벨을 앞에 보여줘야 할 때.
	else
	{
		mainLevel = backLevel;
		backLevel = menuLevel;
	}
}

void Game::CleanUp()
{
	SafeDelete(gameLevel);
	SafeDelete(menuLevel);
	mainLevel = nullptr;

	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}

void Game::GameStart()
{

	gameLevel = new GameLevel();
	menuLevel = new EscMenuLevel();
	AddLevel(gameLevel);
}

void Game::StageClear()
{
	gameLevel = new UpgradeMenuLevel();
	ChangeLevel(gameLevel);
	showMenu = false;
}

void Game::GameEnd()
{
	Quit();
}

//다음 스테이지로 넘어가는 함수
void Game::MoveToNextStage()
{
	SetStageIndex();
	gameLevel = new GameLevel();
	ChangeLevel(gameLevel);
	showMenu = false;

}