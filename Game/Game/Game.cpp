#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"
#include "Level/EscMenuLevel.h"
#include "Level/UpgradeMenuLevel.h"


Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// ���� ���� �߰�.
	//AddLevel(new GameLevel());

	// �޴� ���� ����.
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
	// ȭ�� ����.
	// clear screen ��ɾ� ����.
	system("cls");

	// ��� ó��.
	showMenu = !showMenu;

	// �޴��� �տ� ������� �� ��.
	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	// ���� ������ �տ� ������� �� ��.
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

//���� ���������� �Ѿ�� �Լ�
void Game::MoveToNextStage()
{
	SetStageIndex();
	gameLevel = new GameLevel();
	ChangeLevel(gameLevel);
	showMenu = false;

}