#include "UpgradeMenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"


UpgradeMenuLevel::UpgradeMenuLevel()
{
	// 메뉴 아이템 추가.
	//스테이지가 끝난 경우에 하는 작동 구현

	items.emplace_back(new MenuItem(
		L"Upgrade speed",
		[]() { /*작동부 구현*/ }
	));

	items.emplace_back(new MenuItem(
		L"Upgrade damage",
		[]() {/*작동부 구현*/ }
	));

	// 아이템 수 미리 저장.
	length = static_cast<int>(items.size());



}

UpgradeMenuLevel::~UpgradeMenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}