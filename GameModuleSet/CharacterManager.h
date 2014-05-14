#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <QString>

#include "Character.h"

const unsigned int CIVILIAN = 0;
const unsigned int WARRIOR = 1;
const unsigned int RANGER = 2;

class CharacterManager
{

public:
    CharacterManager();
    ~CharacterManager();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void addPlayer(const QString& playerName);

    void addCharacter();

    std::shared_ptr<Character> getCharacter(const int id);

    std::shared_ptr<Character> getPlayer(const QString& playerName);

    unsigned int getNumberOfCharacter();

private:
    unsigned int m_uiNumberOfCharacter;
    std::map<QString, int> m_name2IDMap;
    std::vector<std::shared_ptr<Character>> m_charactersVec;

    std::shared_ptr<Character> newCharacter(int iCharacterType = 0);
};

#endif // CHARACTERMANAGER_H
