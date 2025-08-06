#include "EscMenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"


EscMenuLevel::EscMenuLevel()
{
	// �޴� ������ �߰�.
	items.emplace_back(new MenuItem(
		L"Resume Game",
		[]() { Game::Get().ToggleMenu("ESC"); }
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