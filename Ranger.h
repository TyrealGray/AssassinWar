#pragma once
#include "character.h"

class Ranger :
    public Character
{
public:
    Ranger(void);
    ~Ranger(void);

private:
    QImage* m_pCharacter;
};

