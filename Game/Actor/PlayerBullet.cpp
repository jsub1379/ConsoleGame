//#include "PlayerBullet.h"
//#include "Engine.h"
//
//PlayerBullet::PlayerBullet(const Vector2& position)
//    : Actor('-', Color::Yellow, position) // �Ѿ� ����� '-'
//{
//    SetSortingOrder(2); // �÷��̾�� �Ʒ� ����
//}
//
//void PlayerBullet::Tick(float deltaTime)
//{
//    super::Tick(deltaTime);
//
//    // ���������� �̵�
//    Vector2 pos = Position();
//    pos.x += speed * deltaTime;
//    SetPosition(pos);
//
//    // ȭ�� ���̸� ����
//    if (pos.x >= Engine::Get().Width())
//    {
//        Destroy();
//    }
//}
