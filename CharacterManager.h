#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <QString>

#include "Character.h"

class CharacterManager
{

public:
    CharacterManager();
    ~CharacterManager();

    void addPlayer(const QString& playerName);

    void addCharacter();

    std::shared_ptr<Character> getCharacter(const int id);

    std::shared_ptr<Character> getPlayer(const QString& playerName);

private:
    std::map<QString, int> m_name2IDMap;
    std::vector<std::shared_ptr<Character>> m_charactersVec;

    std::shared_ptr<Character> newCharacter(int iCharacterType = 0);
};

#endif // CHARACTERMANAGER_H
