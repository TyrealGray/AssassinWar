#pragma once
#include "character.h"

class Civilian :
    public Character
{
public:
    Civilian(int id, unsigned int uiSpeed);
    virtual ~Civilian(void);
};

