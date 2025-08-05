#include "PlayerBullet.h"
#include "Engine.h"

#include "Input.h"
#include "Level/Level.h"


PlayerBullet::PlayerBullet(const Vector2& position)
    : Actor('-', Color::White, position) // 총알 모양은 '-'
{
    SetSortingOrder(2); // 플레이어보다 아래 레벨
}

void PlayerBullet::Tick(float deltaTime)
{
    //super::Tick(deltaTime);

    // 오른쪽으로 이동
    Vector2 position = Position();
    position.x += speed * deltaTime;
    SetPosition(position);

    // 화면 밖이면 삭제
    if (position.x >= (30,30))
    {
        Destroy();
    }
}
