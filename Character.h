#pragma once
#include <QReadWriteLock>

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
    ~Character(void);

    void setPosition(const unsigned int &uiX, const unsigned int &uiY);

    void goTo(const unsigned int &uiX, const unsigned int &uiY);

    void updatePosition();

    void render(QPainter &painter, int &iOffsetX, int &iOffsetY);



    unsigned int getCurrentGridX();

    unsigned int getCurrentGridY();

    unsigned int getTargetGridX();

    unsigned int getTargetGridY();

private:
    QImage* m_pCharacter;
    float m_uiSpeed;
    unsigned int m_uiCurrentX;
    unsigned int m_uiCurrentY;
    unsigned int m_uiTargetGridX;
    unsigned int m_uiTargetGridY;
    int m_iDirection;
    QReadWriteLock m_lock;
    void updateCoord(const unsigned int &uiTargetGridCoord, unsigned int &uiCurrentCoord, int iIncrease, int iDecrease);
    bool isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    bool isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    unsigned int getCurrentX();
    unsigned int getCurrentY();
    void setCurrentX(int iX);
    void setCurrentY(int iY);
    void setDirection(int iDirection);
};

