#include "PlayerBullet.h"
#include "Engine.h"

#include "Input.h"
#include "Level/Level.h"


PlayerBullet::PlayerBullet(const Vector2& position, const Vector2& direction)
    : Actor('-', Color::White, position) // 총알 모양은 '-'
{
    SetSortingOrder(2); // 플레이어보다 아래 레벨

    if (direction.x == 0 && direction.y == 0)//처음 시작위치인경우
    {
        return;
    }
    else
    {
        xDirection = direction.x;
        yDirection = direction.y;
    }
    if (position.x == 0 && position.y == 0)//처음 시작위치인경우
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
    // 이동
    xPosition += xDirection* speed* deltaTime;
    yPosition += yDirection * speed * deltaTime;
    SetPosition(Vector2((int)xPosition, (int)yPosition));

    // 화면 밖이면 삭제
    if (position.x >= 30)
    {
        Destroy();
    }
}
