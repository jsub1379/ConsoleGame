#include "EscMenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"


EscMenuLevel::EscMenuLevel()
{
	// �޴� ������ �߰�.
	//esc�� ���� ��쿡 �ϴ� �۵� ����

	items.emplace_back(new MenuItem(
		L"Resume Game",
		[]() { Game::Get().ToggleMenu(MenuType::RETURN_MENU); }
	));

	items.emplace_back(new MenuItem(
		L"Quit Game",
		[]() { Game::Get().Quit(); }
	));

	// ������ �� �̸� ����.
	length = static_cast<int>(items.size());
}

EscMenuLevel::~EscMenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}