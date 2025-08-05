#include "GameLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Enemy.h"
#include "Actor/Target.h"
#include "Actor/PlayerBullet.h"

#include "Utils/Utils.h"

#include <iostream>

GameLevel::GameLevel()
{
	ReadMapFile("Map_Stage1.txt");
}

void GameLevel::Render()
{
	super::Render();

	if (isGameClear)
	{

		Utils::SetConsolePosition(Vector2(2, 0));

		Utils::SetConsoleTextColor(
			static_cast<WORD>(Color::White)
		);

		std::wcout << L"Game Clear!";
	}
}

//맵 및 객체 생성 로직
void GameLevel::ReadMapFile(const char* filename)
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


	// 배열 순회를 위한 인덱스 변수.
	int index = 0;

	// 문자열 길이 값.
	int size = (int)readSize;

	// x, y 좌표.
	Vector2 position(0, 2);

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
			++targetEnemy;
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

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// 플레이어 탄약과 적의 충돌 처리. 
	ProcessCollisionPlayerBulletAndEnemy();

}


//점수 처리 로직
bool GameLevel::CheckGameClear()
{
	if (targetEnemy == 0)
		return true;
	else
		return false;
}


//플레이어 이동 가능 여부 처리
bool GameLevel::CanPlayerMove(
	const Vector2& playerPosition,
	const Vector2& newPosition)
{
	if (isGameClear)
		return false;

	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// 벽이면 이동 불가.
			if (actor->As<Wall>())
			{
				return false;
			}
			return true;
		}
	}

}
      
//충돌 함수 구현        
void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// 플레이어 탄약 액터 배열.
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Wall*> walls;
	std::vector<Target*> targets;
	Player* player = nullptr;

	// 두 타입의 액터를 검색해서 배열 채우기.
	for (Actor* const actor : actors)
	{
		// 플레이어 저장
		if (Player* p = actor->As<Player>())
		{
			player = p;
			continue;
		}

		//총알 저장
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		//적 저장
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.emplace_back(enemy);
			continue;
		}

		//벽 저장
		Wall* wall = actor->As<Wall>();
		if (wall)
		{
			walls.emplace_back(wall);
		}
		Target* target = actor->As<Target>();
		if (target)
		{
			targets.emplace_back(target);
		}
	}


	// 총알의 충돌 처리.
	for (auto* bullet : bullets)
	{
		//벽과 플레이어 총알 충돌
		for (auto* wall : walls)
		{
			if (bullet->TestIntersect(wall))
			{
				bullet->Destroy();
			}
		}

		//적과 플레이어 총알 충돌
		for (auto* enemy : enemies)
		{
			if (bullet->TestIntersect(enemy))
			{
				bullet->Destroy();
				enemy->Destroy();
				--targetEnemy;
				continue;
			}
		}
	}

	//플레이어의 충돌 처리

	//플레이어와 목표 충돌

	for (auto* target : targets)
	{
		if (player->TestIntersect(target))
		{
			//마지막 target 이 아닌 경우
			if (targetEnemy != 1)
				target->Destroy();

			if (CheckGameClear())
				isGameClear = true;
		}
	}

}