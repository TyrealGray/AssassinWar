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

Character::Character(int id, unsigned int uiSpeed)
    : m_id(id), m_uiSpeed(uiSpeed),
      m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(1), m_uiTargetGridY(1),
      m_iDirection(GO_DOWN)
{

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

void Character::setPosition(const unsigned int &uiX, const unsigned int &uiY)
{
    setCurrentX(PixelCoordinateTransfer::toPixel(uiX));
    setCurrentY(PixelCoordinateTransfer::toPixel(uiY));
}

void Character::goTo(const unsigned int &uiX, const unsigned int &uiY)
{
    m_uiTargetGridX = uiX;
    m_uiTargetGridY = uiY;
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