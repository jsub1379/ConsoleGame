#include "PlayerBullet.h"
#include "Engine.h"

#include "Input.h"
#include "Level/Level.h"


PlayerBullet::PlayerBullet(const Vector2& position)
    : Actor('-', Color::White, position) // �Ѿ� ����� '-'
{
    SetSortingOrder(2); // �÷��̾�� �Ʒ� ����
}

void PlayerBullet::Tick(float deltaTime)
{
    //super::Tick(deltaTime);

    // ���������� �̵�
    Vector2 position = Position();
    position.x += speed * deltaTime;
    SetPosition(position);

    // ȭ�� ���̸� ����
    if (position.x >= (30,30))
    {
        Destroy();
    }
}
