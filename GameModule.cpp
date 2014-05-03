#include <QPainter>

#include "GameModule.h"
#include "MapModule.h"
#include "Character.h"

GameModule::GameModule(void)
    : m_pMapModule(NULL)
    //m_pCharacterModule(NULL)
{
}


GameModule::~GameModule(void)
{
}

void GameModule::init()
{
    m_pMapModule = new MapModule();
    m_pMapModule->init();

    m_pGhostF = new Character();
}

QWidget* GameModule::loadMap(const QString& strMapPath)
{
    return m_pMapModule->loadMap(strMapPath);
}

void GameModule::loadMapTerrain()
{
    m_pMapModule->loadTerrain();
}

void GameModule::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    m_pGhostF->render(painter, iOffsetX, iOffsetY);
}
void GameModule::setMapSize(const unsigned int &uiGridWidth, const unsigned int &uiGridheight)
{
    m_pMapModule->setSize(uiGridWidth, uiGridheight);
}

void GameModule::setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY)
{
    if(m_pMapModule->getGrid(uiX, uiY))
    {
        m_pGhostF->setPosition(uiX, uiY);
    }
}

void GameModule::setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY)
{
    if(m_pMapModule->getGrid(uiX, uiY))
    {
        m_pGhostF->setPosition(uiX, uiY);
    }
}

unsigned int GameModule::getPlayerGridX()
{
    return m_pGhostF->getCurrentGridX();
}

unsigned int GameModule::getPlayerGridY()
{
    return m_pGhostF->getCurrentGridY();
}

Character* GameModule::getCharacterByID(int id)
{
    return m_pGhostF;
}

std::vector<int> GameModule::getAllCharacterIDs()
{
    std::vector<int> a;
    int b = 1;
    a.push_back(b);
    return a;
}