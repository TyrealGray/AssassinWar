#include <QPainter>

#include "GameModule.h"
#include "MapModule.h"
#include "CharacterModule.h"

GameModule::GameModule(void)
    : m_pMapModule(NULL),
      m_pCharacterModule(NULL)
{
}


GameModule::~GameModule(void)
{
}

void GameModule::init()
{
    m_pMapModule = new MapModule();
    m_pMapModule->init();

    m_pCharacterModule = new CharacterModule();
    m_pCharacterModule->init();
}

QWidget* GameModule::loadMap(const QString& strMapPath)
{
    return m_pMapModule->loadMap(strMapPath);
}

void GameModule::loadMapTerrain()
{
    m_pMapModule->loadTerrain();
}

void GameModule::addNewPlayer(const QString& name)
{
    m_pCharacterModule->addNewPlayer(name);
}

void GameModule::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pCharacterModule->drawAllCharacter(painter, iOffsetX, iOffsetY);
}

void GameModule::updateAllCharacterPosition()
{

}

void GameModule::setMapSize(const unsigned int &uiGridWidth, const unsigned int &uiGridheight)
{
    m_pMapModule->setSize(uiGridWidth, uiGridheight);
}

void GameModule::setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY)
{
    if(m_pMapModule->getGrid(uiX, uiY))
    {
        m_pCharacterModule->setCharacterPos(name, uiX, uiY);
    }
}

void GameModule::setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY)
{
    if(m_pMapModule->getGrid(uiX, uiY))
    {
        m_pCharacterModule->setCharacterPos(id, uiX, uiY);
    }
}

unsigned int GameModule::getPlayerGridX()
{
    return 0;
}

unsigned int GameModule::getPlayerGridY()
{
    return 0;
}

std::shared_ptr<Character> GameModule::getCharacterByID(const int id)
{
    return m_pCharacterModule->getCharacter(id);
}

std::shared_ptr<Character> GameModule::getCharacterByName(const QString &name)
{
    return m_pCharacterModule->getPlayer(name);
}

int GameModule::getNumberOfCharacter()
{
    return m_pCharacterModule->getNumberOfCharacter();
}