#include "Box.h"

Box::Box(const Vector2& position)
	: Actor('E', Color::Green, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(2);
}