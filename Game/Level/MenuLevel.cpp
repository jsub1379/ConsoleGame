#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

#include <iostream>

#include<fcntl.h>
#include <io.h>

MenuLevel::MenuLevel()
{
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �Է� ó��.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// Enter Ű �Է�.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� �����ϰ� �ִ� �Լ� ȣ��.
		items[currentIndex]->onSelected();
	}

	//�޴� ��ɵ� ����
	//�޴� ȭ�鿡�� �Է�
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{

		Game::Get().ToggleMenu(MenuType::ESC_MENU);

		// �޴� �ε��� �ʱ�ȭ.
		//currentIndex = 0;
	}

	

}

void MenuLevel::Render()
{
	super::Render();

	// ���� & ��ǥ ����.
	Utils::SetConsolePosition(Vector2(0, 0));
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	//todo: SokobanGame ��� escmenu�� �ű��

	// �޴� ���� ���.
	//std::cout << "SokobanGame\n\n";
	wchar_t title[] = L"SokobanGame\n\n";
	Utils::PrintWideCharacter(title);

	// �޴� ������ ������.
	for (int ix = 0; ix < length; ++ix)
	{
		// ������ ���� Ȯ��.
		Color textColor = 
			(ix == currentIndex) ? selectedColor : unselectedColor;

		// ���� ����.
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// �޴� �ؽ�Ʈ ���.
		Utils::PrintWideCharacter(items[ix]->menuText);
		Utils::PrintWideCharacter(L"\n");
		//std::cout << items[ix]->menuText << "\n";
	}
}