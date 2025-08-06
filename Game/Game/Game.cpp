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
	AddLevel(new GameLevel());

	// �޴� ���� ����.
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

		//ESC �޴�
		if (menu == MenuType::ESC_MENU)
		{
			mainLevel = escmenuLevel;
		}
		//���� ������ RETURN 
		else if (menu == MenuType::RETURN_MENU)
		{
			mainLevel = backLevel;
		}
		//�������� ���� ������Ʈ â �޴�
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
	SafeDelete(upgrademenuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}