#include <QPainter>
#include <QReadWriteLock>

#include "Character.h"
#include "PixelCoordinateTransfer.h"

Character::Character(int id, unsigned int uiSpeed)
    : m_pCharacter(NULL), m_pLock(NULL),
      m_id(id), m_uiSpeed(uiSpeed),
      m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(1), m_uiTargetGridY(1),
      m_iDirection(GO_DOWN)
{
    m_pLock = new QReadWriteLock();
}

Character::~Character(void)
{
    delete m_pCharacter;
    m_pCharacter = NULL;

    delete m_pLock;
    m_pLock = NULL;
}

void Character::init()
{
    m_pCharacter = new QImage();
    m_pCharacter->load("./Resources/Character/Ghost-F.png");

    m_pLock = new QReadWriteLock();
}

void Character::die()
{

}

void Character::setHide(bool isHide)
{

}

void Character::render(QPainter &painter, int &iOffsetX, int &iOffsetY)
{
    m_pLock->lockForRead();
    painter.drawImage(getCurrentX() - iOffsetX, getCurrentY() - iOffsetY , (*m_pCharacter));
    m_pLock->unlock();
}

void Character::setPosition(const unsigned int &uiX, const unsigned int &uiY)
{
    setCurrentX(PixelCoordinateTransfer::toPixel(uiX));
    setCurrentY(PixelCoordinateTransfer::toPixel(uiY));
}

void Character::updateNextPosition()
{
    if(getNextStepX() > getCurrentX())
    {
        setCurrentX(getNextStepX());
        setDirection(GO_RIGHT);
    }
    else if(getNextStepX() < getCurrentX())
    {
        setCurrentX(getNextStepX());
        setDirection(GO_LEFT);
    }

    if(getNextStepY() > getCurrentY())
    {
        setCurrentY(getNextStepY());
        setDirection(GO_DOWN);
    }
    else if(getNextStepY() < getCurrentY())
    {
        setCurrentY(getNextStepY());
        setDirection(GO_UP);
    }
}

void Character::setSpeed(unsigned int& uiSpeed)
{
    m_pLock->lockForWrite();
    m_uiSpeed = uiSpeed;
    m_pLock->unlock();
}

unsigned int Character::getNextStepGridX()
{
    return PixelCoordinateTransfer::toGrid(getNextStepX());
}

unsigned int Character::getNextStepGridY()
{
    return PixelCoordinateTransfer::toGrid(getNextStepY());
}

unsigned int Character::getNextStepX()
{
    m_pLock->lockForRead();

    unsigned int iNextStepX = getCurrentX();

    if(getTargetGridX() && isIncreaseToTargetPos(getTargetGridX(), getCurrentX()))
    {
        iNextStepX += getSpeed();
    }
    else if(getTargetGridX() && isDecreaseToTargetPos(getTargetGridX(), getCurrentX()))
    {
        iNextStepX -= getSpeed();
    }
    m_pLock->unlock();

    return iNextStepX;
}

unsigned int Character::getNextStepY()
{
    m_pLock->lockForRead();

    unsigned int iNextStepY = getCurrentY();

    if(getTargetGridY() && isIncreaseToTargetPos(getTargetGridY(), getCurrentY()))
    {
        iNextStepY += getSpeed();
    }
    else if(getTargetGridY() && isDecreaseToTargetPos(getTargetGridY(), getCurrentY()))
    {
        iNextStepY -= getSpeed();
    }

    m_pLock->unlock();

    return iNextStepY;
}

void Character::goTo(const unsigned int &uiX, const unsigned int &uiY)
{
    m_pLock->lockForWrite();
    m_uiTargetGridX = uiX;
    m_uiTargetGridY = uiY;
    m_pLock->unlock();
}


unsigned int Character::getSpeed()
{
    return m_uiSpeed;
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
    m_pLock->lockForWrite();
    m_uiCurrentX = iX;
    m_pLock->unlock();
}

void Character::setCurrentY(int iY)
{
    m_pLock->lockForWrite();
    m_uiCurrentY = iY;
    m_pLock->unlock();
}

void Character::setDirection(int iDirection)
{
    m_pLock->lockForWrite();
    m_iDirection = iDirection;
    m_pLock->unlock();
}

bool Character::isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) < uiCurrentCoord - m_uiSpeed;
}

bool Character::isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord)
{
    return PixelCoordinateTransfer::toPixel(uiTargetGridCoord) > uiCurrentCoord + m_uiSpeed;
}