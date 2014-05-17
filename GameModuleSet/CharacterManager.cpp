#include <stdlib.h>
#include <time.h>


#include "CharacterManager.h"
#include "Civilian.h"
#include "Warrior.h"
#include "Ranger.h"


const int NORMAL_SPEED = 10;
const int NumberOfClass = 1;
CharacterManager::CharacterManager()
    : m_uiNumberOfCharacter(0)
{
    m_charactersVec.reserve(50);
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    for(unsigned int index = 0; index < m_charactersVec.size(); ++ index)
    {
        m_charactersVec[index]->render(painter, iOffsetX, iOffsetY);
    }
}

void CharacterManager::addPlayer(const QString& playerName)
{
    if(m_name2IDMap.end() == m_name2IDMap.find(playerName))
    {
        srand((unsigned)time(NULL));
        unsigned int uiType = (rand() % NumberOfClass) + 1;

        m_name2IDMap.insert(std::make_pair(playerName, m_uiNumberOfCharacter));

        addCharacter(uiType);
    }
}

void CharacterManager::addCivilian()
{
    addCharacter(0);
}

void CharacterManager::addCharacter(unsigned int uiType)
{
    std::shared_ptr<Character> pNewCharacter = newCharacter(uiType);

    m_charactersVec.push_back(pNewCharacter);

    ++m_uiNumberOfCharacter;
}

std::shared_ptr<Character> CharacterManager::getCharacter(const int id)
{
    std::shared_ptr<Character> pCharacter = NULL;

    if(id < m_uiNumberOfCharacter)
    {
        pCharacter = m_charactersVec[id];
    }

    return pCharacter;
}

std::shared_ptr<Character> CharacterManager::getPlayer(const QString& playerName)
{
    std::shared_ptr<Character> pCharacter = NULL;

    if(m_name2IDMap.end() != m_name2IDMap.find(playerName))
    {
        pCharacter = m_charactersVec[m_name2IDMap[playerName]];
    }

    return pCharacter;
}

unsigned int CharacterManager::getNumberOfCharacter()
{
    return m_charactersVec.size();
}

std::shared_ptr<Character> CharacterManager::newCharacter(int iCharacterType)
{
    Character* pCharacter = NULL;
    switch(iCharacterType)
    {
    case  CIVILIAN:
        pCharacter = new Civilian(m_uiNumberOfCharacter, NORMAL_SPEED);
        break;
    case  WARRIOR:
        pCharacter = new Warrior(m_uiNumberOfCharacter, NORMAL_SPEED);
        break;
    case RANGER:
        pCharacter = new Ranger(m_uiNumberOfCharacter, NORMAL_SPEED);
        break;
    default:
        break;
    }

    if(NULL != pCharacter)
    {
        pCharacter->init();
    }

    std::shared_ptr<Character> pNewCharacter(pCharacter);
    return pNewCharacter;
}