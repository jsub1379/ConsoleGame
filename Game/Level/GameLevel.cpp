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

//�� �� ��ü ���� ����
void GameLevel::ReadMapFile(const char* filename)
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


	// �迭 ��ȸ�� ���� �ε��� ����.
	int index = 0;

	// ���ڿ� ���� ��.
	int size = (int)readSize;

	// x, y ��ǥ.
	Vector2 position(0, 2);

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
			++targetEnemy;
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

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// �÷��̾� ź��� ���� �浹 ó��. 
	ProcessCollisionPlayerBulletAndEnemy();

}


//���� ó�� ����
bool GameLevel::CheckGameClear()
{
	if (targetEnemy == 0)
		return true;
	else
		return false;
}


//�÷��̾� �̵� ���� ���� ó��
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
			// ���̸� �̵� �Ұ�.
			if (actor->As<Wall>())
			{
				return false;
			}
			return true;
		}
	}

}
      
//�浹 �Լ� ����        
void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// �÷��̾� ź�� ���� �迭.
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<Wall*> walls;
	std::vector<Target*> targets;
	Player* player = nullptr;

	// �� Ÿ���� ���͸� �˻��ؼ� �迭 ä���.
	for (Actor* const actor : actors)
	{
		// �÷��̾� ����
		if (Player* p = actor->As<Player>())
		{
			player = p;
			continue;
		}

		//�Ѿ� ����
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		//�� ����
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.emplace_back(enemy);
			continue;
		}

		//�� ����
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


	// �Ѿ��� �浹 ó��.
	for (auto* bullet : bullets)
	{
		//���� �÷��̾� �Ѿ� �浹
		for (auto* wall : walls)
		{
			if (bullet->TestIntersect(wall))
			{
				bullet->Destroy();
			}
		}

		//���� �÷��̾� �Ѿ� �浹
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

	//�÷��̾��� �浹 ó��

	//�÷��̾�� ��ǥ �浹

	for (auto* target : targets)
	{
		if (player->TestIntersect(target))
		{
			//������ target �� �ƴ� ���
			if (targetEnemy != 1)
				target->Destroy();

			if (CheckGameClear())
				isGameClear = true;
		}
	}

}