#include <QReadWriteLock>

#include "CharacterManager.h"


const int NORMAL_SPEED = 10;

CharacterManager::CharacterManager()
    : m_pLock(NULL), m_uiNumberOfCharacter(0)
{

}

CharacterManager::~CharacterManager()
{
    delete m_pLock;
    m_pLock = NULL;
}

void CharacterManager::init()
{
    m_pLock = new QReadWriteLock();
    m_charactersVec.reserve(50);
}

void CharacterManager::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pLock->lockForRead();

    for(unsigned int index = 0; index < m_charactersVec.size(); ++ index)
    {
        m_charactersVec[index]->render(painter, iOffsetX, iOffsetY);
    }

    m_pLock->unlock();
}

void CharacterManager::addPlayer(const QString& playerName, unsigned int uiType)
{
    if(m_name2IDMap.end() == m_name2IDMap.find(playerName))
    {
        m_pLock->lockForWrite();

        m_name2IDMap.insert(std::make_pair(playerName, m_uiNumberOfCharacter));

        m_pLock->unlock();

        addCharacter(uiType);
    }
}

void CharacterManager::addCivilian()
{
    addCharacter(0);
}

void CharacterManager::addCharacter(unsigned int uiType)
{
    m_pLock->lockForWrite();

    std::shared_ptr<Character> pNewCharacter = newCharacter(uiType);

    m_charactersVec.push_back(pNewCharacter);

    ++m_uiNumberOfCharacter;

    m_pLock->unlock();
}

std::shared_ptr<Character> CharacterManager::getCharacter(const int id)
{
    std::shared_ptr<Character> pCharacter = NULL;

    if(id < m_uiNumberOfCharacter)
    {
        m_pLock->lockForRead();

        pCharacter = m_charactersVec[id];

        m_pLock->unlock();
    }

    return pCharacter;
}

std::shared_ptr<Character> CharacterManager::getPlayer(const QString& playerName)
{
    std::shared_ptr<Character> pCharacter = NULL;

    if(m_name2IDMap.end() != m_name2IDMap.find(playerName))
    {
        m_pLock->lockForRead();

        pCharacter = m_charactersVec[m_name2IDMap[playerName]];

        m_pLock->unlock();
    }

    return pCharacter;
}

unsigned int CharacterManager::getNumberOfCharacter()
{
    return m_charactersVec.size();
}

std::shared_ptr<Character> CharacterManager::newCharacter(int iCharacterType)
{
    Character* pCharacter = new Character(m_uiNumberOfCharacter, NORMAL_SPEED, iCharacterType);

    pCharacter->init();

    std::shared_ptr<Character> pNewCharacter(pCharacter);
    return pNewCharacter;
}