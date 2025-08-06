#include "EscMenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"


EscMenuLevel::EscMenuLevel()
{
	// 메뉴 아이템 추가.
	//esc를 누른 경우에 하는 작동 구현

	items.emplace_back(new MenuItem(
		L"Resume Game",
		[]() { Game::Get().ToggleMenu(MenuType::RETURN_MENU); }
	));

	items.emplace_back(new MenuItem(
		L"Quit Game",
		[]() { Game::Get().Quit(); }
	));

	// 아이템 수 미리 저장.
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