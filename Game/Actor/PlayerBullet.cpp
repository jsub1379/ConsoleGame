#include "PlayerBullet.h"
#include "Engine.h"
#include "Input.h"
#include "Actor/Actor.h"


PlayerBullet::PlayerBullet(const Vector2& startPosition)
    : Actor('-', Color::White,startPosition) // 총알 모양은 '-'
{
    SetSortingOrder(2); // 플레이어보다 아래 레벨
}

void PlayerBullet::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    // 예: 스페이스바를 누르면 발사

        Vector2 position = Position();
        position.x += speed * deltaTime;
        SetPosition(position);
 

    //// 화면 밖이면 삭제
    //if (pos.x >= Engine::Get().Width())
    //{
    //    Destroy();
    //}
}
