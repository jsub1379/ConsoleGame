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

	// 입력 처리.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// Enter 키 입력.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장하고 있는 함수 호출.
		items[currentIndex]->onSelected();
	}

	//메뉴 기능들 구현
	//메뉴 화면에서 입력
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{

		Game::Get().ToggleMenu(MenuType::ESC_MENU);

		// 메뉴 인덱스 초기화.
		//currentIndex = 0;
	}

	

}

void MenuLevel::Render()
{
	super::Render();

	// 색상 & 좌표 정리.
	Utils::SetConsolePosition(Vector2(0, 0));
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	//todo: SokobanGame 출력 escmenu로 옮기기

	// 메뉴 제목 출력.
	//std::cout << "SokobanGame\n\n";
	wchar_t title[] = L"SokobanGame\n\n";
	Utils::PrintWideCharacter(title);

	// 메뉴 아이템 렌더링.
	for (int ix = 0; ix < length; ++ix)
	{
		// 아이템 색상 확인.
		Color textColor = 
			(ix == currentIndex) ? selectedColor : unselectedColor;

		// 색상 설정.
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// 메뉴 텍스트 출력.
		Utils::PrintWideCharacter(items[ix]->menuText);
		Utils::PrintWideCharacter(L"\n");
		//std::cout << items[ix]->menuText << "\n";
	}
}