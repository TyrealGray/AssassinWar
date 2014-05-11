#include <QPainter>

#include "Character.h"
#include "PixelCoordinateTransfer.h"

Character::Character(int id, unsigned int uiSpeed)
    : m_id(id), m_pCharacter(NULL),
      m_uiSpeed(uiSpeed),
      m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(1), m_uiTargetGridY(1),
      m_iDirection(GO_DOWN)
{
    m_pCharacter = new QImage();
    m_pCharacter->load("./Resources/Character/Ghost-F.png");
}

Character::~Character(void)
{
}

void Character::die()
{

}

void Character::setHide(bool isHide)
{

}

void Character::render(QPainter &painter, int &iOffsetX, int &iOffsetY)
{
    painter.drawImage(getCurrentX() - iOffsetX, getCurrentY() - iOffsetY , (*m_pCharacter));
}

void Character::setPosition(const unsigned int &uiX, const unsigned int &uiY)
{
    setCurrentX(PixelCoordinateTransfer::toPixel(uiX));
    setCurrentY(PixelCoordinateTransfer::toPixel(uiY));
}

void Character::updateNextPosition()
{
    updateCoord(m_uiTargetGridX, m_uiCurrentX, GO_RIGHT , GO_LEFT);
    updateCoord(m_uiTargetGridY, m_uiCurrentY, GO_DOWN, GO_UP);
}

void Character::updateCoord(const unsigned int &uiTargetGridCoord, unsigned int &uiCurrentCoord, int iIncrease, int iDecrease)
{
    if(1 <= uiTargetGridCoord && isIncreaseToTargetPos(uiTargetGridCoord, uiCurrentCoord))
    {
        uiCurrentCoord += m_uiSpeed;
        setDirection(iIncrease);
    }
    else if(1 <= uiTargetGridCoord && isDecreaseToTargetPos(uiTargetGridCoord, uiCurrentCoord))
    {
        uiCurrentCoord -= m_uiSpeed;
        setDirection(iDecrease);
    }
}

bool Character::isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) < uiCurrentCoord - m_uiSpeed;
}

bool Character::isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) > uiCurrentCoord + m_uiSpeed;
}

unsigned int Character::getNextStepGridX()
{
    unsigned int iNextStepX = m_uiCurrentX;

    if(1 <= m_uiTargetGridX && this->isIncreaseToTargetPos(m_uiTargetGridX, m_uiCurrentX))
    {
        iNextStepX += m_uiSpeed;
    }
    else if(1 <= m_uiTargetGridX && this->isDecreaseToTargetPos(m_uiTargetGridX, m_uiCurrentX))
    {
        iNextStepX -= m_uiSpeed;
    }

    return PixelCoordinateTransfer::toGrid(iNextStepX);
}

unsigned int Character::getNextStepGridY()
{
    unsigned int iNextStepY = m_uiCurrentY;

    if(1 <= m_uiTargetGridY && this->isIncreaseToTargetPos(m_uiTargetGridY, m_uiCurrentY))
    {
        iNextStepY += m_uiSpeed;
    }
    else if(1 <= m_uiTargetGridY && this->isDecreaseToTargetPos(m_uiTargetGridY, m_uiCurrentY))
    {
        iNextStepY -= m_uiSpeed;
    }

    return PixelCoordinateTransfer::toGrid(iNextStepY);
}

void Character::goTo(const unsigned int &uiX, const unsigned int &uiY)
{
    m_uiTargetGridX = uiX;
    m_uiTargetGridY = uiY;
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

void Character::setCurrentX(int iX)
{
    m_uiCurrentX = iX;
}

void Character::setCurrentY(int iY)
{
    m_uiCurrentY = iY;
}

void Character::setDirection(int iDirection)
{
    m_iDirection = iDirection;
}