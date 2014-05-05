#pragma once

const int GO_UP = 0;
const int GO_DOWN = 1;
const int GO_LEFT = 2;
const int GO_RIGHT = 3;

class QImage;
class QPainter;
class Character
{
public:
    Character(void);
    Character(int id, unsigned int uiSpeed);

    virtual ~Character(void);

    void die();

    void setHide(bool isHide);

    void setPosition(const unsigned int &uiX, const unsigned int &uiY);

    void goTo(const unsigned int &uiX, const unsigned int &uiY);

    void render(QPainter &painter, int &iOffsetX, int &iOffsetY);

    unsigned int getCurrentGridX();

    unsigned int getCurrentGridY();

    unsigned int getTargetGridX();

    unsigned int getTargetGridY();

private:
    int m_id;
    QImage* m_pCharacter;
    unsigned int m_uiSpeed;
    unsigned int m_uiCurrentX;
    unsigned int m_uiCurrentY;
    unsigned int m_uiTargetGridX;
    unsigned int m_uiTargetGridY;
    int m_iDirection;
    unsigned int getCurrentX();
    unsigned int getCurrentY();
    void setCurrentX(int iX);
    void setCurrentY(int iY);
    void setDirection(int iDirection);
};

