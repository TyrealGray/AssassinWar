#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <map>
#include <vector>
#include <memory>

#include "Character.h"

class CharacterManager
{

public:
    CharacterManager();
    ~CharacterManager();

    void init();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void addPlayer(const QString& playerName, unsigned int uiType);

    void addCivilian();

    std::shared_ptr<Character> getCharacter(const int id);

    std::shared_ptr<Character> getPlayer(const QString& playerName);

    unsigned int getNumberOfCharacter();

private:
    QReadWriteLock* m_pLock;
    unsigned int m_uiNumberOfCharacter;
    std::map<QString, int> m_name2IDMap;
    std::vector<std::shared_ptr<Character>> m_charactersVec;

    void addCharacter(unsigned int uiType);
    std::shared_ptr<Character> newCharacter(int iCharacterType);
};

#endif // CHARACTERMANAGER_H
