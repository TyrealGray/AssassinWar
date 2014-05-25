#include <stdlib.h>
#include <time.h>

#include <QPainter>

#include "GameModule.h"
#include "MapModule.h"
#include "CharacterModule.h"

const int NUMBER_OF_CLASSES = 1;
GameModule::GameModule(QObject * parent /*= 0*/)
    : QObject(parent),
      m_pMapModule(NULL), m_pCharacterModule(NULL),
      m_bIsGameRun(false), m_playerName("")
{
}


GameModule::~GameModule(void)
{
    release();
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
    srand((unsigned)time(NULL));

    unsigned int uiType = (rand() % NUMBER_OF_CLASSES) + 1;

    m_pCharacterModule->addNewPlayer(name, uiType);

    unsigned int uiX = 0;
    unsigned int uiY = 0;

    do
    {
        uiX = (rand() % m_pMapModule->getWidth()) + 1;
        uiY = (rand() % m_pMapModule->getHeight()) + 1;
    }
    while(0 == uiX || 0 == uiY || !m_pMapModule->getGrid(uiX, uiY));

    m_pCharacterModule->setCharacterPos(name, uiX, uiY);

    m_pMapModule->setGrid(uiX, uiY, false);
}

void GameModule::addNewCharacter(unsigned int number /* = 1 */)
{
    srand((unsigned)time(NULL));

    unsigned int uiX = 0;
    unsigned int uiY = 0;

    for(unsigned int index = 0 ; index < number; ++index)
    {
        m_pCharacterModule->addCharacter();

        do
        {
            uiX = (rand() % m_pMapModule->getWidth()) + 1;
            uiY = (rand() % m_pMapModule->getHeight()) + 1;
        }
        while(0 == uiX || 0 == uiY || !m_pMapModule->getGrid(uiX, uiY));

        m_pCharacterModule->setCharacterPos(getNumberOfCharacter() - 1 , uiX, uiY);

        m_pMapModule->setGrid(uiX, uiY, false);
    }

}

void GameModule::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pCharacterModule->drawAllCharacter(painter, iOffsetX, iOffsetY);
}
void GameModule::setGameIsRun(bool bIsRun)
{
    m_bIsGameRun = bIsRun;
}

void GameModule::setPlayerName(const QString& name)
{
    m_playerName = name;
}

void GameModule::updateCharactersStatus()
{
    if(!m_bIsGameRun)
    {
        return;
    }

    unsigned int uiGridX = 0;
    unsigned int uiGridY = 0;
    unsigned int curGridX = 0;
    unsigned int curGridY = 0;
    std::shared_ptr<Character> pCharacter = NULL;

    for(unsigned int index = 0 ; index < m_pCharacterModule->getNumberOfCharacter(); ++index)
    {
        pCharacter = m_pCharacterModule->getCharacter(index);

        curGridX = pCharacter->getCurrentGridX();
        curGridY = pCharacter->getCurrentGridY();

        m_pMapModule->setGrid(curGridX, curGridY, true);

        uiGridX = pCharacter->getNextStepGridX();
        uiGridY = pCharacter->getNextStepGridY();

        if(m_pMapModule->getGrid(uiGridX, uiGridY))
        {
            m_pCharacterModule->getCharacter(index)->updateNextPosture();
            m_pMapModule->setGrid(uiGridX, uiGridY, false);
        }

        curGridX = pCharacter->getCurrentGridX();
        curGridY = pCharacter->getCurrentGridY();

        m_pMapModule->setGrid(curGridX, curGridY, true);

    }
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
    return NULL != getCharacterByName(m_playerName) ? getCharacterByName(m_playerName)->getCurrentGridX() : 1;
}

unsigned int GameModule::getPlayerGridY()
{
    return NULL != getCharacterByName(m_playerName) ? getCharacterByName(m_playerName)->getCurrentGridY() : 1;
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

bool GameModule::isGameRun()
{
    return m_bIsGameRun;
};

void GameModule::clear()
{
    release();
    init();
}

void GameModule::release()
{
    delete m_pMapModule;
    m_pMapModule = NULL;

    delete m_pCharacterModule;
    m_pCharacterModule = NULL;
}
