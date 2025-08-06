#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class GameLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();
	virtual void Tick(float deltaTime) override;
	// Inherited via ICanPlayerMove.
	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;

	// ������ ��.
private:
	virtual void Render() override;

private:
	
	// �� ������ �о ���� ��ü �����ϴ� �Լ�.
	void ReadMapFile(const char* filename);

	// ���� Ŭ���� Ȯ���ϴ� �Լ�.
	bool CheckStageClear();
	void ProcessCollisionPlayerBulletAndEnemy();
private:
	// ���� Ŭ��� ���� ����.
	int targetEnemy = 0;
	
	// ���� Ŭ���� ���� Ȯ�� ����.
	bool isStageClear = false;
};