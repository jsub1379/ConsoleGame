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

//�� �� ��ü ���� ����
void SokobanLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�.
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ����ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ����: " << filename << "\n";
		__debugbreak();
		return;
	}

	// �Ľ�(Parcing, �ؼ�).
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize.\n";
	//}

	// �迭 ��ȸ�� ���� �ε��� ����.
	int index = 0;

	// ���ڿ� ���� ��.
	int size = (int)readSize;

	// x, y ��ǥ.
	Vector2 position;

	// ���� �迭 ��ȸ.
	while (index < size)
	{
		// �� ���� Ȯ��.
		char mapCharacter = buffer[index];
		++index;

		// ���� ���� ó��.
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ.
			++position.y;
			position.x = 0;

			continue;
		}

		// �� ���� ���� ó��.
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
			// ���� ���� ����.
			AddActor(new Ground(position));
			// Player ���� ����.
			AddActor(new Player(position));
			break;
		case 'e':
			// ���� ���� ����.
			AddActor(new Ground(position));
			AddActor(new Enemy(position));
			break;
		case 'z':
			AddActor(new Target(position));
			// ��ǥ ���� ���� ó��.
			++targetScore;
			//std::cout << "t";
			break;
		}

		// x ��ǥ ���� ó��.
		++position.x;
	}

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);
}

void SokobanLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// �÷��̾� ź��� ���� �浹 ó��. 
	ProcessCollisionPlayerBulletAndEnemy();

}


//���� ó�� ���� (��Ȱ��ȭ)
bool SokobanLevel::CheckGameClear()
{
	//// �ڽ��� Ÿ�� ��ġ�� ��� �Ű������� Ȯ��.
	//int currentScore = 0;

	//// Ÿ�� ���� ���Ϳ� ����.
	//std::vector<Actor*> targetActors;
	//std::vector<Actor*> enemyActors;

	//for (Actor* const actor : actors)
	//{
	//	// Ÿ�� �������� Ȯ��.
	//	if (actor->As<Target>())
	//	{
	//		targetActors.emplace_back(actor);
	//		continue;
	//	}

	//	// �ڽ� �������� Ȯ��.
	//	if (actor->As<Enemy>())
	//	{
	//		enemyActors.emplace_back(actor);
	//	}
	//}

	//// �ڽ��� Ÿ�� ���� ��ġ ��.
	//for (Actor* const targetActor : targetActors)
	//{
	//	for (Actor* const enemyActor : enemyActors)
	//	{
	//		// �� ������ ��ġ�� ������ ���� ���� ó��.
	//		if (targetActor->Position() == enemyActor->Position())
	//		{
	//			// ���� ����.
	//			++currentScore;
	//		}
	//	}
	//}
	//
	//return currentScore == targetScore;

	return false;
}


//�÷��̾� �̵� ���� ���� ó�� (��Ȱ��ȭ)?
bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition,
	const Vector2& newPosition)
{
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// ���̸� �̵� �Ұ�.
			if (actor->As<Wall>())
			{
				return false;
			}

			// �׶��� or Ÿ��.
			return true;
		}
	}


	//// ���� Ŭ���� ���� Ȯ�� �� ���� ó��.
	//if (isGameClear)
	//{
	//	return false;
	//}

	//// �ڽ� ó��.
	//std::vector<Enemy*> enemyActors;
	//for (Actor* const actor : actors)
	//{
	//	Enemy* enemy = actor->As<Enemy>();
	//	if (enemy)
	//	{
	//		enemyActors.emplace_back(enemy);
	//	}
	//}

	//// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��.
	//Enemy* searchedEnemy = nullptr;
	//for (Enemy* const enemyActor : enemyActors)
	//{
	//	// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ��ġ�� ������ ��.
	//	if (enemyActor->Position() == newPosition)
	//	{
	//		// ���� ��ġ�� �ִ� �ڽ� ���� �� ���� ����.
	//		searchedEnemy = enemyActor;
	//		break;
	//	}
	//}

	//// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��.
	//if (searchedEnemy)
	//{
	//	// #1: �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �� �ִ��� Ȯ��.
	//	Vector2 direction = newPosition - playerPosition;
	//	Vector2 nextPosition = searchedEnemy->Position() + direction;

	//	for (Enemy* const otherEnemy : enemyActors)
	//	{
	//		// ���� �ڽ��� �ǳʶٱ�.
	//		if (otherEnemy == searchedEnemy)
	//		{
	//			continue;
	//		}

	//		// �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��.
	//		if (otherEnemy->Position() == nextPosition)
	//		{
	//			// �÷��̾� �̵� ����.
	//			return false;
	//		}
	//	}

	//	for (Actor* const actor : actors)
	//	{
	//		if (actor->Position() == nextPosition)
	//		{
	//			// #2: �ڽ��� ������, ���� ���� ������ Ȯ��.
	//			if (actor->As<Wall>())
	//			{
	//				// �÷��̾� �̵� ����.
	//				return false;
	//			}

	//			// #3: �̵� ������ ���(�׶���, Ÿ��)���� �ڽ� �̵� ó��.
	//			if (actor->As<Ground>() || actor->As<Target>())
	//			{
	//				// �ڽ� �̵� ó��.
	//				searchedEnemy->SetPosition(nextPosition);

	//				// ���� Ŭ���� ���� Ȯ��.
	//				isGameClear = CheckGameClear();

	//				// �÷��̾� �̵� ����.
	//				return true;
	//			}
	//		}
	//	}
	//}

	//// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���.
	//for (Actor* const actor : actors)
	//{
	//	if (actor->Position() == newPosition)
	//	{
	//		// ���̸� �̵� �Ұ�.
	//		if (actor->As<Wall>())
	//		{
	//			return false;
	//		}

	//		// �׶��� or Ÿ��.
	//		return true;
	//	}
	//}



	// ???.
	//return false;
//return true;
}
      
//�浹       �Լ� ����        
void SokobanLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// �÷��̾� ź�� ���� �迭.
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Wall*> walls;

	// �� Ÿ���� ���͸� �˻��ؼ� �迭 ä���.
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

	// ����ó�� (���ص� ��Ȳ Ȯ��).
	if (bullets.size() == 0 /*|| enemies.size() == 0*/)
	{
		return;
	}

	// �浹 ó��.
	for (auto* bullet : bullets)
	{
		for (auto* enemy : enemies)
		{
			// �� ���Ͱ� ���� ���ƴ��� Ȯ��.
			if (bullet->TestIntersect(enemy))
			{
				enemy->Destroy();
				bullet->Destroy();

				// ������ ȹ���߱� ������ ���� ���� ó���ؾ� ��.
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

			// �� ���Ͱ� ���� ���ƴ��� Ȯ��.
			if (bullet->TestIntersect(wall))
			{
				//enemy->Destroy();
				bullet->Destroy();

				// ������ ȹ���߱� ������ ���� ���� ó���ؾ� ��.
				//score = score + 1;
				//continue;
			}
		}
	}
}