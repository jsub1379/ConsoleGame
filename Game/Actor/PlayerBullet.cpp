#include "PlayerBullet.h"
#include "Engine.h"

#include "Input.h"
#include "Level/Level.h"


PlayerBullet::PlayerBullet(const Vector2& position, const Vector2& direction)
    : Actor('-', Color::White, position) // �Ѿ� ����� '-'
{
    SetSortingOrder(2); // �÷��̾�� �Ʒ� ����

    if (direction.x == 0 && direction.y == 0)//ó�� ������ġ�ΰ��
    {
        return;
    }
    else
    {
        xDirection = direction.x;
        yDirection = direction.y;
    }
    if (position.x == 0 && position.y == 0)//ó�� ������ġ�ΰ��
    {
        return;
    }
    else
    {
        xPosition = (float)position.x;
        yPosition = (float)position.y;
    }
}

void PlayerBullet::Tick(float deltaTime)
{
    super::Tick(deltaTime);
    // �̵�
    xPosition += xDirection* speed* deltaTime;
    yPosition += yDirection * speed * deltaTime;
    SetPosition(Vector2((int)xPosition, (int)yPosition));

    // ȭ�� ���̸� ����
    if (position.x >= 30)
    {
        Destroy();
    }
}
