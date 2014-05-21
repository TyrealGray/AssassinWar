#include <QPainter>

#include "GameModule.h"
#include "MapModule.h"
#include "CharacterModule.h"

GameModule::GameModule(QObject * parent /*= 0*/)
    : QObject(parent),
      m_pMapModule(NULL), m_pCharacterModule(NULL)
{
}


GameModule::~GameModule(void)
{
    delete m_pMapModule;
    m_pMapModule = NULL;

    delete m_pCharacterModule;
    m_pCharacterModule = NULL;
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

void GameModule::updateCharactersStatus()
{
    m_pCharacterModule->updateCharactersStatus();
}

void GameModule::setMapSize(const unsigned int &uiGridWidth, const unsigned int &uiGridheight)
{
    m_pMapModule->setSize(uiGridWidth, uiGridheight);
}

void GameModule::setCharacterStatus(const int &id , const unsigned int uiX, const unsigned int uiY, const int iDirection, const int iStep)
{
    setCharacterTargetPos(id, uiX, uiY);
    setCharacterPosture(id, iDirection, iStep);
}

void GameModule::setCharacterStatus(const QString &name , const unsigned int uiX, const unsigned int uiY, const int iDirection, const int iStep)
{
    setCharacterTargetPos(name, uiX, uiY);
    setCharacterPosture(name, iDirection, iStep);
}

void GameModule::setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY)
{
    m_pCharacterModule->setCharacterPos(name, uiX, uiY);
}

void GameModule::setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY)
{
    m_pCharacterModule->setCharacterPos(id, uiX, uiY);
}

void GameModule::setCharacterPosture(const int &id, const int &iDirection, const int &iStep)
{
    m_pCharacterModule->setCharacterPosture(id, iDirection, iStep);
}

void GameModule::setCharacterPosture(const QString &name, const int &iDirection, const int &iStep)
{
    m_pCharacterModule->setCharacterPosture(name, iDirection, iStep);
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

void GameModule::setCharacterTargetPos(const int &id, const unsigned int uiX, const unsigned int uiY)
{
    m_pCharacterModule->setCharacterTargetPos(id, uiX, uiY);
}

void GameModule::setCharacterTargetPos(const QString &name, const unsigned int uiX, const unsigned int uiY)
{
    m_pCharacterModule->setCharacterTargetPos(name, uiX, uiY);
}