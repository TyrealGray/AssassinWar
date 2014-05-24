#pragma once

#include <memory>
#include "Character.h"

class CharacterManager;
class CharacterModule
{
public:
    CharacterModule(void);
    ~CharacterModule(void);

    void init();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void addNewPlayer(const QString& name);

    int getNumberOfCharacter();

    std::shared_ptr<Character> getCharacter(const int id);
    std::shared_ptr<Character> getPlayer(const QString& name);

    void setCharacterPos(const int &id, const unsigned int &uiX, const unsigned int &uiY);
    void setCharacterPos(const QString &name, const unsigned int &uiX, const unsigned int &uiY);

    void setCharacterTargetPos(const int &id, const unsigned int &uiX, const unsigned int &uiY);
    void setCharacterTargetPos(const QString &name, const unsigned int &uiX, const unsigned int &uiY);

    void setCharacterPosture(const int &id, const int &iDirection, const int &iStep);
    void setCharacterPosture(const QString &name, const int &iDirection, const int &iStep);

private:
    CharacterManager* m_pCharacterManager;
};

