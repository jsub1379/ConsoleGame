#pragma once

#include "Engine.h"
#include <unordered_map>

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

	// �޴� ��ȯ �Լ�.
	void ToggleMenu(int menuType);

	virtual void CleanUp() override;

	static Game& Get();

private:

	// �޴� ����.
	Level* menuLevel = nullptr;
	Level* escmenuLevel = nullptr;
	Level* upgrademenuLevel = nullptr;

	// ȭ�鿡 �Ⱥ��̴� ����.
	Level* backLevel = nullptr;

	// ���� �޴� ������ �����ְ� �ִ����� ��Ÿ��.
	bool showMenu = false;

	static Game* instance;
};