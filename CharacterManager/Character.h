#pragma once

class QImage;
class QPainter;
class Character
{
public:
    Character(void);
    ~Character(void);

    void goTo(const unsigned int &uiX, const unsigned int &uiY);

    void render(QPainter &painter, int &iOffsetX, int &iOffsetY);

    unsigned int getCurrentGridX();

    unsigned int getCurrentGridY();

private:
    QImage* m_pCharacter;
    float m_uiSpeed;
    unsigned int m_uiCurrentX;
    unsigned int m_uiCurrentY;
    unsigned int m_uiTargetGridX;
    unsigned int m_uiTargetGridY;
};

