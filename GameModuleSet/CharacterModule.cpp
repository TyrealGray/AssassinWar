#include <QPainter>

#include "CharacterModule.h"
#include "CharacterManager.h"

CharacterModule::CharacterModule(void)
    : m_pCharacterManager(NULL)
{
}


CharacterModule::~CharacterModule(void)
{
    delete m_pCharacterManager;
    m_pCharacterManager = NULL;
}

void CharacterModule::init()
{
    m_pCharacterManager = new CharacterManager();
    m_pCharacterManager->init();
}
void CharacterModule::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pCharacterManager->drawAllCharacter(painter, iOffsetX, iOffsetY);
}

void CharacterModule::addNewPlayer(const QString& name, unsigned int uiType)
{
    m_pCharacterManager->addPlayer(name, uiType);
}

void CharacterModule::addCharacter()
{
    m_pCharacterManager->addCivilian();
}

int CharacterModule::getNumberOfCharacter()
{
    return m_pCharacterManager->getNumberOfCharacter();
}

std::shared_ptr<Character> CharacterModule::getCharacter(const int id)
{
    return m_pCharacterManager->getCharacter(id);
}

std::shared_ptr<Character> CharacterModule::getPlayer(const QString& name)
{
    return m_pCharacterManager->getPlayer(name);
}

void CharacterModule::setCharacterPos(const int &id, const unsigned int &uiX, const unsigned int &uiY)
{
    m_pCharacterManager->getCharacter(id)->setPosition(uiX, uiY);
}

void CharacterModule::setCharacterPos(const QString &name, const unsigned int &uiX, const unsigned int &uiY)
{
    m_pCharacterManager->getPlayer(name)->setPosition(uiX, uiY);
}

void CharacterModule::setCharacterTargetPos(const int &id, const unsigned int &uiX, const unsigned int &uiY)
{
    m_pCharacterManager->getCharacter(id)->goTo(uiX, uiY);
}

void CharacterModule::setCharacterTargetPos(const QString &name, const unsigned int &uiX, const unsigned int &uiY)
{
    m_pCharacterManager->getPlayer(name)->goTo(uiX, uiY);
}

void CharacterModule::setCharacterPosture(const int &id, const int &iDirection, const int &iStep)
{
    m_pCharacterManager->getCharacter(id)->setPosture(iDirection, iStep);
}

void CharacterModule::setCharacterPosture(const QString &name, const int &iDirection, const int &iStep)
{
    m_pCharacterManager->getPlayer(name)->setPosture(iDirection, iStep);
}