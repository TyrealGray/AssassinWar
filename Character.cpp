#include <QPainter>

#include "Character.h"
#include "PixelCoordinateTransfer.h"


Character::Character(void)
    : m_pCharacter(NULL),
      m_uiSpeed(10), m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(1), m_uiTargetGridY(1),
      m_iDirection(GO_DOWN)
{
    m_pCharacter = new QImage;
    m_pCharacter->load("./Resources/Character/Ghost-F.png");
}


Character::~Character(void)
{
}

void Character::setPosition(const unsigned int &uiX, const unsigned int &uiY)
{
    setCurrentX(PixelCoordinateTransfer::toPixel(uiX));
    setCurrentY(PixelCoordinateTransfer::toPixel(uiY));
}

void Character::goTo(const unsigned int &uiX, const unsigned int &uiY)
{
    m_lock.lockForWrite();
    m_uiTargetGridX = uiX;
    m_uiTargetGridY = uiY;
    m_lock.unlock();
}

void Character::updatePosition()
{
    m_lock.lockForWrite();
    this->updateCoord(m_uiTargetGridX, m_uiCurrentX, GO_RIGHT , GO_LEFT);
    this->updateCoord(m_uiTargetGridY, m_uiCurrentY, GO_DOWN, GO_UP);
    m_lock.unlock();
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

void Character::updateCoord(const unsigned int &uiTargetGridCoord, unsigned int &uiCurrentCoord, int iIncrease, int iDecrease)
{
    if(1 <= uiTargetGridCoord && this->isIncreaseToTargetPos(uiTargetGridCoord, uiCurrentCoord))
    {
        uiCurrentCoord += m_uiSpeed;
        setDirection(iIncrease);
    }
    else if(1 <= uiTargetGridCoord && this->isDecreaseToTargetPos(uiTargetGridCoord, uiCurrentCoord))
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

void Character::setCurrentX(int iX)
{
    m_lock.lockForWrite();
    m_uiCurrentX = iX;
    m_lock.unlock();
}

void Character::setCurrentY(int iY)
{
    m_lock.lockForWrite();
    m_uiCurrentY = iY;
    m_lock.unlock();
}

void Character::setDirection(int iDirection)
{
    m_iDirection = iDirection;

    switch(m_iDirection)
    {
    case GO_UP:
        m_pCharacter->load("./Resources/Character/Ghost-B.png");
        break;
    case GO_DOWN:
        m_pCharacter->load("./Resources/Character/Ghost-F.png");
        break;
    case GO_LEFT:
        m_pCharacter->load("./Resources/Character/Ghost-L.png");
        break;
    case GO_RIGHT:
        m_pCharacter->load("./Resources/Character/Ghost-R.png");
        break;
    default:
        break;
    }
}