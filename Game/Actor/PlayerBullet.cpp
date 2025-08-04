//#include "PlayerBullet.h"
//#include "Engine.h"
//
//PlayerBullet::PlayerBullet(const Vector2& position)
//    : Actor('-', Color::Yellow, position) // 총알 모양은 '-'
//{
//    SetSortingOrder(2); // 플레이어보다 아래 레벨
//}
//
//void PlayerBullet::Tick(float deltaTime)
//{
//    super::Tick(deltaTime);
//
//    // 오른쪽으로 이동
//    Vector2 pos = Position();
//    pos.x += speed * deltaTime;
//    SetPosition(pos);
//
//    // 화면 밖이면 삭제
//    if (pos.x >= Engine::Get().Width())
//    {
//        Destroy();
//    }
//}
