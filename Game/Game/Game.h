#pragma once

#include "Engine.h"
#include <unordered_map>

// 메뉴 레벨 (다시 게임 진행/종료).
// 게임 레벨
// 게임 종료 후 레벨 업그레이드 

namespace MenuType
{
	const int ESC_MENU = 0;
	const int RETURN_MENU = 1;
	const int UPGRADE_MENU = 100;
}

class Level;
class Game : public Engine
{
public:
	Game();
	~Game();

	// 메뉴 전환 함수.
	void ToggleMenu(int menuType);

	virtual void CleanUp() override;

	static Game& Get();

	void GameStart();
	void GameClear();
	void GameEnd();
	

private:

	// 메뉴 레벨.
	Level* menuLevel = nullptr;
	//Level* escMenuLevel = nullptr;
	//Level* upgrademenuLevel = nullptr;
	Level* gameLevel = nullptr;

	// 화면에 안보이는 레벨.
	Level* backLevel = nullptr;

	// 현재 메뉴 레벨을 보여주고 있는지를 나타냄.
	bool showMenu = false;

	static Game* instance;
};