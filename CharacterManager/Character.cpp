#include <QPainter>

#include "Character.h"


Character::Character(void)
    : m_pCharacter(NULL),
      m_uiSpeed(10), m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(0), m_uiTargetGridY(0),
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
    if((m_uiTargetGridX - 1) * 15 > m_uiCurrentX + m_uiSpeed)
    {
        m_uiCurrentX += m_uiSpeed;
    }
    else if((m_uiTargetGridX - 1) * 15 < m_uiCurrentX - m_uiSpeed)
    {
        m_uiCurrentX -= m_uiSpeed;
    }

    if((m_uiTargetGridY - 1) * 15 > m_uiCurrentY + m_uiSpeed)
    {
        m_uiCurrentY += m_uiSpeed;
    }
    else if((m_uiTargetGridY - 1) * 15 < m_uiCurrentY - m_uiSpeed)
    {
        m_uiCurrentY -= m_uiSpeed;
    }

    painter.drawImage(m_uiCurrentX - iOffsetX, m_uiCurrentY - iOffsetY , (*m_pCharacter));

}

unsigned int Character::getCurrentGridX()
{
    unsigned int uiCurrentX = getCurrentX_() / 15;
    return uiCurrentX + 1;
}

unsigned int Character::getCurrentGridY()
{
    unsigned int uiCurrentY = getCurrentY_() / 15;
    return uiCurrentY + 1;
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