#include "Enemy.h"

Enemy::Enemy(const Vector2& position)
	: Actor('E', Color::Green, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(2);
}