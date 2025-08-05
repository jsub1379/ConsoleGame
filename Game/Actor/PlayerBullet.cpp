#include "PlayerBullet.h"
#include "Engine.h"

#include "Input.h"
#include "Level/Level.h"


PlayerBullet::PlayerBullet(const Vector2& position)
    : Actor('-', Color::White, position) // �Ѿ� ����� '-'
{
    SetSortingOrder(2); // �÷��̾�� �Ʒ� ����

    xPosition = (float)position.x;
}

void PlayerBullet::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    // ���������� �̵�
    xPosition += speed * deltaTime;
    
    //Vector2 position = Position();
    //position.x += speed * deltaTime;
    //position.x = (int)xPosition;
    SetPosition(Vector2((int)xPosition, position.y));

    // ȭ�� ���̸� ����
    if (position.x >= 30)
    {
        Destroy();
    }
}
