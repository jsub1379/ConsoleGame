#pragma once

#include "Engine.h"
#include <unordered_map>

class Level;
class Game : public Engine
{
public:
	Game();
	~Game();

	// �޴� ��ȯ �Լ�.
	void ToggleMenu(const char* menuType);

	virtual void CleanUp() override;

	static Game& Get();

private:

	// �޴� ����.
	Level* menuLevel = nullptr;
	Level* escmenuLevel = nullptr;

	// ȭ�鿡 �Ⱥ��̴� ����.
	Level* backLevel = nullptr;

	// ���� �޴� ������ �����ְ� �ִ����� ��Ÿ��.
	bool showMenu = false;

	static Game* instance;
};