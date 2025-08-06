#pragma once
#include "MenuLevel.h"

class EscMenuLevel : public MenuLevel
{
    RTTI_DECLARATIONS(EscMenuLevel, MenuLevel)

public:
    EscMenuLevel();
    //virtual ~EscMenuLevel() = default;
    ~EscMenuLevel();

    //virtual void BeginPlay() override;
    //virtual void Tick(float deltaTime) override;

protected:
    //virtual void OnMenuAction(int selectedIndex) override;
};
