#include "QPainter"

#include "CharacterManager.h"

CharacterManager::CharacterManager()
    : m_pGhostF(NULL),
      m_iX(-1),
      m_iY(-1)
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

void CharacterManager::setGhostPos(const int &iX, const int &iY)
{
    m_iX = iX;
    m_iY = iY;
}

void CharacterManager::drawAllCharacter(QPainter &painter)
{
    painter.drawImage((m_iX - 10), (m_iY - 10) , (*m_pGhostF));
}