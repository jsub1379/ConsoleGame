#include "Target.h"

Target::Target(const Vector2& position)
	: Actor('Z', Color::Blue, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(1);
}