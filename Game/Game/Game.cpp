#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/GameLevel.h"
#include "Level/EscMenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// ���� ���� �߰�.
	AddLevel(new GameLevel());

	// �޴� ���� ����.
	menuLevel = new MenuLevel();
	escmenuLevel = new EscMenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu(const char* menuType = " ")
{
	// ȭ�� ����.
	// clear screen ��ɾ� ����.
	system("cls");

	// ��� ó��.
	showMenu = !showMenu;

	if (showMenu)
		//���⼭ �޴� ���� �ľ�
	{
		// ���� ������ �ڷ� �б�.
		backLevel = mainLevel;

		// �޴� ������ ���� ������ ����.
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
		// ���� ������ ���� ������ ����.
		mainLevel = backLevel;
	}
}

void Game::CleanUp()
{
	// �̶��� Engine�� mainLevel�� menuLevel.
	if (showMenu)
	{
		// ���� ���� ����.
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//// mainLevel�� ���� ���� -> �̶��� Engine���� �ϴ����� �����ϸ� ��.
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