#pragma once

#include "Level/Level.h"
#include <vector>
#include "Actor/Actor.h"

struct MenuItem
{
	// �Լ� ������ ����.
	typedef void (*OnSelected)();
	//using OnSelected = void (*)();

	MenuItem(const wchar_t* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		// �޴� �ؽ�Ʈ ���ڿ� ����.
		size_t length = wcslen(text) + 1;
		menuText = new wchar_t[length];
		wcscpy_s(menuText, length, text);

		menuTextLength = (unsigned int)length - 1;
	}

	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}

	// �޴� �ؽ�Ʈ.
	wchar_t* menuText = nullptr;

	unsigned int menuTextLength = 0;

	// �޴� ���� �� ������ ����.
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

protected:

	// ���� ���õ� �������� �ε���.
	int currentIndex = 0;

	// ������ ���� ����.
	Color selectedColor = Color::Green;

	// ������ ���� �ȵ��� �� ����.
	Color unselectedColor = Color::White;

	// ������ �迭.
	std::vector<MenuItem*> items;

	// �޴� ������ ��.
	int length = 0;
};