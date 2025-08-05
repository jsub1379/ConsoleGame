#include "PlayerBullet.h"
#include "Engine.h"
#include "Input.h"
#include "Actor/Actor.h"


PlayerBullet::PlayerBullet(const Vector2& startPosition)
    : Actor('-', Color::White,startPosition) // �Ѿ� ����� '-'
{
    SetSortingOrder(2); // �÷��̾�� �Ʒ� ����
}

void PlayerBullet::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    // ��: �����̽��ٸ� ������ �߻�

        Vector2 position = Position();
        position.x += speed * deltaTime;
        SetPosition(position);
 

    //// ȭ�� ���̸� ����
    //if (pos.x >= Engine::Get().Width())
    //{
    //    Destroy();
    //}
}
