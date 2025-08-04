#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Enemy.h"
#include "Actor/Target.h"

#include "Utils/Utils.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
	//ReadMapFile("Map.txt");
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

			// �׽�Ʈ�뵵. ���߿� �����ؾ���.
			//std::cout << "\n";
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

bool SokobanLevel::CheckGameClear()
{
	// �ڽ��� Ÿ�� ��ġ�� ��� �Ű������� Ȯ��.
	int currentScore = 0;

	// Ÿ�� ���� ���Ϳ� ����.
	std::vector<Actor*> targetActors;
	std::vector<Actor*> enemyActors;
	for (Actor* const actor : actors)
	{
		// Ÿ�� �������� Ȯ��.
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
			continue;
		}

		// �ڽ� �������� Ȯ��.
		if (actor->As<Enemy>())
		{
			enemyActors.emplace_back(actor);
		}
	}

	// �ڽ��� Ÿ�� ���� ��ġ ��.
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const enemyActor : enemyActors)
		{
			// �� ������ ��ġ�� ������ ���� ���� ó��.
			if (targetActor->Position() == enemyActor->Position())
			{
				// ���� ����.
				++currentScore;
			}
		}
	}

	return currentScore == targetScore;
}

bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition, 
	const Vector2& newPosition)
{
	// ���� Ŭ���� ���� Ȯ�� �� ���� ó��.
	if (isGameClear)
	{
		return false;
	}

	// �ڽ� ó��.
	std::vector<Enemy*> enemyActors;
	for (Actor* const actor : actors)
	{
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemyActors.emplace_back(enemy);
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��.
	Enemy* searchedEnemy = nullptr;
	for (Enemy* const enemyActor : enemyActors)
	{
		// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ��ġ�� ������ ��.
		if (enemyActor->Position() == newPosition)
		{
			// ���� ��ġ�� �ִ� �ڽ� ���� �� ���� ����.
			searchedEnemy = enemyActor;
			break;
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��.
	if (searchedEnemy)
	{
		// #1: �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �� �ִ��� Ȯ��.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextPosition = searchedEnemy->Position() + direction;

		for (Enemy* const otherEnemy : enemyActors)
		{
			// ���� �ڽ��� �ǳʶٱ�.
			if (otherEnemy == searchedEnemy)
			{
				continue;
			}

			// �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��.
			if (otherEnemy->Position() == nextPosition)
			{
				// �÷��̾� �̵� ����.
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->Position() == nextPosition)
			{
				// #2: �ڽ��� ������, ���� ���� ������ Ȯ��.
				if (actor->As<Wall>())
				{
					// �÷��̾� �̵� ����.
					return false;
				}

				// #3: �̵� ������ ���(�׶���, Ÿ��)���� �ڽ� �̵� ó��.
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// �ڽ� �̵� ó��.
					searchedEnemy->SetPosition(nextPosition);

					// ���� Ŭ���� ���� Ȯ��.
					isGameClear = CheckGameClear();

					// �÷��̾� �̵� ����.
					return true;
				}
			}
		}
	}

	// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���.
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

	// ???.
	return false;
}