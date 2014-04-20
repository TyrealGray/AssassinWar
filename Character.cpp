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

void Character::render(QPainter &painter, int &iOffsetX, int &iOffsetY)
{
    if(1 <= m_uiTargetGridX && PixelCoordinateTransfer::toPixel(m_uiTargetGridX)  > m_uiCurrentX + m_uiSpeed)
    {
        m_uiCurrentX += m_uiSpeed;
    }
    else if(1 <= m_uiTargetGridX && PixelCoordinateTransfer::toPixel(m_uiTargetGridX) < m_uiCurrentX - m_uiSpeed)
    {
        m_uiCurrentX -= m_uiSpeed;
    }

    if(1 <= m_uiTargetGridY && PixelCoordinateTransfer::toPixel(m_uiTargetGridY) > m_uiCurrentY + m_uiSpeed)
    {
        m_uiCurrentY += m_uiSpeed;
    }
    else if(1 <= m_uiTargetGridY && PixelCoordinateTransfer::toPixel(m_uiTargetGridY) < m_uiCurrentY - m_uiSpeed)
    {
        m_uiCurrentY -= m_uiSpeed;
    }

    painter.drawImage(m_uiCurrentX - iOffsetX, m_uiCurrentY - iOffsetY , (*m_pCharacter));

}

unsigned int Character::getCurrentGridX()
{
    return  PixelCoordinateTransfer::toGrid(getCurrentX_());
}

unsigned int Character::getCurrentGridY()
{
    return  PixelCoordinateTransfer::toGrid(getCurrentY_());
}

unsigned int Character::getTargetGridX()
{
    return m_uiTargetGridX;
}

unsigned int Character::getTargetGridY()
{
    return m_uiTargetGridY;
}

unsigned int Character::getCurrentX_()
{
    return m_uiCurrentX;
}

unsigned int Character::getCurrentY_()
{
    return m_uiCurrentY;
}