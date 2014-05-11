#pragma once
#include "character.h"

class Warrior :
    public Character
{
public:
    Warrior(int id, unsigned int uiSpeed);
    virtual ~Warrior(void);
private:
};

