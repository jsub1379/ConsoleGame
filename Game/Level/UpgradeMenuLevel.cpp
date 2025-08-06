#include "UpgradeMenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"


UpgradeMenuLevel::UpgradeMenuLevel()
{
	// �޴� ������ �߰�.
	//���������� ���� ��쿡 �ϴ� �۵� ����

	items.emplace_back(new MenuItem(
		L"Upgrade speed",
		[]() { /*�۵��� ����*/ }
	));

	items.emplace_back(new MenuItem(
		L"Upgrade damage",
		[]() {/*�۵��� ����*/ }
	));

	// ������ �� �̸� ����.
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