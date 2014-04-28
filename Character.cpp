#include <QPainter>

#include "Character.h"
#include "PixelCoordinateTransfer.h"


Character::Character(void)
    : m_pCharacter(NULL),
      m_uiSpeed(10), m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(1), m_uiTargetGridY(1),
      m_eDirection(GO_DOWN)
{
    m_pCharacter = new QImage;
    m_pCharacter->load("./Resources/Character/Ghost-F.png");
}


Character::~Character(void)
{
}

void Character::goTo(const unsigned int &uiX, const unsigned int &uiY)
{
    m_uiTargetGridX = uiX;
    m_uiTargetGridY = uiY;
}

void Character::updatePosition()
{

    this->updateCoord(m_uiTargetGridX, m_uiCurrentX);

    this->updateCoord(m_uiTargetGridY, m_uiCurrentY);

}

void Character::render(QPainter &painter, int &iOffsetX, int &iOffsetY)
{
    painter.drawImage(m_uiCurrentX - iOffsetX, m_uiCurrentY - iOffsetY , (*m_pCharacter));
}

unsigned int Character::getCurrentGridX()
{
    return  PixelCoordinateTransfer::toGrid(getCurrentX());
}

unsigned int Character::getCurrentGridY()
{
    return  PixelCoordinateTransfer::toGrid(getCurrentY());
}

unsigned int Character::getTargetGridX()
{
    return m_uiTargetGridX;
}

unsigned int Character::getTargetGridY()
{
    return m_uiTargetGridY;
}

unsigned int Character::getCurrentX()
{
    return m_uiCurrentX;
}

unsigned int Character::getCurrentY()
{
    return m_uiCurrentY;
}

void Character::updateCoord(const unsigned int &uiTargetGridCoord, unsigned int &uiCurrentCoord)
{
    if(1 <= uiTargetGridCoord && this->shouldMoveDownToTargetPos(uiTargetGridCoord, uiCurrentCoord))
    {
        uiCurrentCoord += m_uiSpeed;
    }
    else if(1 <= uiTargetGridCoord && this->shouldMoveUpToTargetPos(uiTargetGridCoord, uiCurrentCoord))
    {
        uiCurrentCoord -= m_uiSpeed;
    }
}

bool Character::shouldMoveUpToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) < uiCurrentCoord - m_uiSpeed;
}

bool Character::shouldMoveDownToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) > uiCurrentCoord + m_uiSpeed;
}