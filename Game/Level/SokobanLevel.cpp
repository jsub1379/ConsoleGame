#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Enemy.h"
#include "Actor/Target.h"
#include "Actor/PlayerBullet.h"

#include "Utils/Utils.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map_Stage1.txt");
}

void SokobanLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition(Vector2(30, 0));
		Utils::SetConsoleTextColor(
			static_cast<WORD>(Color::White)
		);

		std::cout << "Game Clear!";
	}
}

//맵 및 객체 생성 로직
void SokobanLevel::ReadMapFile(const char* filename)
{
	// 최종 애셋 경로 완성.
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// 예외처리.
	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패: " << filename << "\n";
		__debugbreak();
		return;
	}

	// 파싱(Parcing, 해석).
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize.\n";
	//}

	// 배열 순회를 위한 인덱스 변수.
	int index = 0;

	// 문자열 길이 값.
	int size = (int)readSize;

	// x, y 좌표.
	Vector2 position;

	// 문자 배열 순회.
	while (index < size)
	{
		// 맵 문자 확인.
		char mapCharacter = buffer[index];
		++index;

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			// 다음 줄로 넘기면서, x 좌표 초기화.
			++position.y;
			position.x = 0;

			continue;
		}

		// 각 문자 별로 처리.
		switch (mapCharacter)
		{
		case '#':
		case '1':
			AddActor(new Wall(position));
			break;
		case '.':
			AddActor(new Ground(position));
			break;
		case 'p':
			// 땅도 같이 생성.
			AddActor(new Ground(position));
			// Player 액터 생성.
			AddActor(new Player(position));
			break;
		case 'e':
			// 땅도 같이 생성.
			AddActor(new Ground(position));
			AddActor(new Enemy(position));
			break;
		case 'z':
			AddActor(new Target(position));
			// 목표 점수 증가 처리.
			++targetScore;
			//std::cout << "t";
			break;
		}

		// x 좌표 증가 처리.
		++position.x;
	}

	// 버퍼 해제.
	delete[] buffer;

	// 파일 닫기.
	fclose(file);
}

void SokobanLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// 플레이어 탄약과 적의 충돌 처리. 
	ProcessCollisionPlayerBulletAndEnemy();

}


//점수 처리 로직 (비활성화)
bool SokobanLevel::CheckGameClear()
{
	//// 박스가 타겟 위치에 모두 옮겨졌는지 확인.
	//int currentScore = 0;

	//// 타겟 액터 벡터에 저장.
	//std::vector<Actor*> targetActors;
	//std::vector<Actor*> enemyActors;

	//for (Actor* const actor : actors)
	//{
	//	// 타겟 액터인지 확인.
	//	if (actor->As<Target>())
	//	{
	//		targetActors.emplace_back(actor);
	//		continue;
	//	}

	//	// 박스 액터인지 확인.
	//	if (actor->As<Enemy>())
	//	{
	//		enemyActors.emplace_back(actor);
	//	}
	//}

	//// 박스와 타겟 액터 위치 비교.
	//for (Actor* const targetActor : targetActors)
	//{
	//	for (Actor* const enemyActor : enemyActors)
	//	{
	//		// 두 액터의 위치가 같으면 점수 증가 처리.
	//		if (targetActor->Position() == enemyActor->Position())
	//		{
	//			// 점수 증가.
	//			++currentScore;
	//		}
	//	}
	//}
	//
	//return currentScore == targetScore;

	return false;
}


//플레이어 이동 가능 여부 처리 (비활성화)?
bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition,
	const Vector2& newPosition)
{
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// 벽이면 이동 불가.
			if (actor->As<Wall>())
			{
				return false;
			}

			// 그라운드 or 타겟.
			return true;
		}
	}


	//// 게임 클리어 여부 확인 및 종료 처리.
	//if (isGameClear)
	//{
	//	return false;
	//}

	//// 박스 처리.
	//std::vector<Enemy*> enemyActors;
	//for (Actor* const actor : actors)
	//{
	//	Enemy* enemy = actor->As<Enemy>();
	//	if (enemy)
	//	{
	//		enemyActors.emplace_back(enemy);
	//	}
	//}

	//// 이동하려는 위치에 박스가 있는지 확인.
	//Enemy* searchedEnemy = nullptr;
	//for (Enemy* const enemyActor : enemyActors)
	//{
	//	// 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교.
	//	if (enemyActor->Position() == newPosition)
	//	{
	//		// 같은 위치에 있는 박스 저장 후 루프 종료.
	//		searchedEnemy = enemyActor;
	//		break;
	//	}
	//}

	//// 이동하려는 위치에 박스가 있는 경우 처리.
	//if (searchedEnemy)
	//{
	//	// #1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인.
	//	Vector2 direction = newPosition - playerPosition;
	//	Vector2 nextPosition = searchedEnemy->Position() + direction;

	//	for (Enemy* const otherEnemy : enemyActors)
	//	{
	//		// 같은 박스는 건너뛰기.
	//		if (otherEnemy == searchedEnemy)
	//		{
	//			continue;
	//		}

	//		// 박스를 이동시키려는 위치에 다른 박스가 있는지 확인.
	//		if (otherEnemy->Position() == nextPosition)
	//		{
	//			// 플레이어 이동 못함.
	//			return false;
	//		}
	//	}

	//	for (Actor* const actor : actors)
	//	{
	//		if (actor->Position() == nextPosition)
	//		{
	//			// #2: 박스는 없지만, 벽이 있지 않은지 확인.
	//			if (actor->As<Wall>())
	//			{
	//				// 플레이어 이동 못함.
	//				return false;
	//			}

	//			// #3: 이동 가능한 경우(그라우드, 타겟)에는 박스 이동 처리.
	//			if (actor->As<Ground>() || actor->As<Target>())
	//			{
	//				// 박스 이동 처리.
	//				searchedEnemy->SetPosition(nextPosition);

	//				// 게임 클리어 여부 확인.
	//				isGameClear = CheckGameClear();

	//				// 플레이어 이동 가능.
	//				return true;
	//			}
	//		}
	//	}
	//}

	//// 플레이어가 이동하려는 위치에 박스가 없는 경우.
	//for (Actor* const actor : actors)
	//{
	//	if (actor->Position() == newPosition)
	//	{
	//		// 벽이면 이동 불가.
	//		if (actor->As<Wall>())
	//		{
	//			return false;
	//		}

	//		// 그라운드 or 타겟.
	//		return true;
	//	}
	//}



	// ???.
	//return false;
//return true;
}
      
//충돌       함수 구현        
void SokobanLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// 플레이어 탄약 액터 배열.
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Wall*> walls;

	// 두 타입의 액터를 검색해서 배열 채우기.
	for (Actor* const actor : actors)
	{
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.emplace_back(enemy);
			continue;
		}

		Wall* wall = actor->As<Wall>();
		if (wall)
		{
			walls.emplace_back(wall);
		}
	}

	// 예외처리 (안해도 상황 확인).
	if (bullets.size() == 0 /*|| enemies.size() == 0*/)
	{
		return;
	}

	// 충돌 처리.
	for (auto* bullet : bullets)
	{
		for (auto* enemy : enemies)
		{
			// 두 액터가 서로 겹쳤는지 확인.
			if (bullet->TestIntersect(enemy))
			{
				enemy->Destroy();
				bullet->Destroy();

				// 점수를 획득했기 때문에 점수 증가 처리해야 함.
				//score = score + 1;
				continue;
			}
		}
		
		for (auto* wall : walls)
		{
			//char test[100] = {};
			//sprintf_s(test, 100, "Collision Test, bulletPos: (%d, %d) | wallPos: (%d, %d), result: %s \n",
			//	bullet->Position().x, bullet->Position().y, wall->Position().x, wall->Position().y,
			//	(bullet->TestIntersect(wall) ? "True" : "False"));
			//OutputDebugStringA(test);

			// 두 액터가 서로 겹쳤는지 확인.
			if (bullet->TestIntersect(wall))
			{
				//enemy->Destroy();
				bullet->Destroy();

				// 점수를 획득했기 때문에 점수 증가 처리해야 함.
				//score = score + 1;
				//continue;
			}
		}
	}
}