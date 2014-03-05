#include <QPainter>

#include "Character.h"


Character::Character(void)
    : m_pCharacter(NULL),
      m_uiSpeed(1), m_uiCurrentX(0), m_uiCurrentY(0), m_uiTargetGridX(0), m_uiTargetGridY(0)
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
    int iMoveOffsetX =  m_uiSpeed / m_uiTargetGridX + 1;
    int iMoveOffsetY =  m_uiSpeed / m_uiTargetGridY + 1;

    m_uiCurrentX += iMoveOffsetX * 15 ;

    m_uiCurrentY += iMoveOffsetY * 15;

    if(m_uiCurrentX > (m_uiTargetGridX - 1) * 15)
    {
        m_uiCurrentX = (m_uiTargetGridX - 1) * 15;
    }

    if(m_uiCurrentY > (m_uiTargetGridY - 1) * 15)
    {
        m_uiCurrentY = (m_uiTargetGridY - 1) * 15;
    }

    painter.drawImage(m_uiCurrentX - iOffsetX, m_uiCurrentY - iOffsetY , (*m_pCharacter));

}

unsigned int Character::getCurrentGridX()
{
    unsigned int uiCurrentX = m_uiCurrentX / 15;
    return uiCurrentX + 1;
}

unsigned int Character::getCurrentGridY()
{
    unsigned int uiCurrentY = m_uiCurrentY / 15;
    return uiCurrentY + 1;
}