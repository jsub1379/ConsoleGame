#pragma once

#include "Engine.h"
#include <unordered_map>

class Level;
class Game : public Engine
{
public:
	Game();
	~Game();

	// 메뉴 전환 함수.
	void ToggleMenu(const char* menuType);

	virtual void CleanUp() override;

	static Game& Get();

private:

	// 메뉴 레벨.
	Level* menuLevel = nullptr;
	Level* escmenuLevel = nullptr;

	// 화면에 안보이는 레벨.
	Level* backLevel = nullptr;

	// 현재 메뉴 레벨을 보여주고 있는지를 나타냄.
	bool showMenu = false;

	static Game* instance;
};