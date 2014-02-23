#include <QPainter>

#include "CharacterManager.h"

CharacterManager::CharacterManager()
    : m_pGhostF(NULL),
      m_uiX(0),
      m_uiY(0)
{
    m_pGhostF = new QImage;
    m_pGhostF->load("./Resources/Character/Ghost-F.png");
}

CharacterManager::~CharacterManager()
{

}

CharacterManager& CharacterManager::instance()
{
    static CharacterManager sCharacterManager;
    return sCharacterManager;
}

void CharacterManager::setGhostPos(const unsigned int &iX, const unsigned int &iY)
{
    m_uiX = iX;
    m_uiY = iY;
}

void CharacterManager::drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY)
{
    int PixelCoordinateX = static_cast<int>((m_uiX - 1) * 15);
    int PixelCoordinateY = static_cast<int>((m_uiY - 1) * 15);
    painter.drawImage(PixelCoordinateX - iOffsetX, PixelCoordinateY - iOffsetY , (*m_pGhostF));
}

unsigned int CharacterManager::getPlayerCharacterGridX()
{
    return m_uiX;
}

unsigned int CharacterManager::getPlayerCharacterGridY()
{
    return m_uiY;
}