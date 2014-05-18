#pragma once

const int GO_UP = 0;
const int GO_DOWN = 1;
const int GO_LEFT = 2;
const int GO_RIGHT = 3;

class QImage;
class QPainter;
class QReadWriteLock;
class Character
{
public:

    Character(int id, unsigned int uiSpeed);

    virtual ~Character(void);

    void init();

    void die();

    void setHide(bool isHide);

    void setPosition(const unsigned int &uiX, const unsigned int &uiY);

    void updateNextPosition();

    unsigned int getNextStepGridX();

    unsigned int getNextStepGridY();

    void goTo(const unsigned int &uiX, const unsigned int &uiY);

    void render(QPainter &painter, int &iOffsetX, int &iOffsetY);

    void setSpeed(unsigned int& uiSpeed);

    unsigned int getSpeed();

    unsigned int getCurrentGridX();

    unsigned int getCurrentGridY();

    unsigned int getTargetGridX();

    unsigned int getTargetGridY();

private:
    QImage* m_pCharacter;
    QReadWriteLock* m_pLock;
    int m_id;
    unsigned int m_uiSpeed;
    unsigned int m_uiCurrentX;
    unsigned int m_uiCurrentY;
    unsigned int m_uiTargetGridX;
    unsigned int m_uiTargetGridY;
    int m_iDirection;

    void setCurrentX(int iX);
    void setCurrentY(int iY);
    void setDirection(int iDirection);

    unsigned int getCurrentX();
    unsigned int getCurrentY();
    unsigned int getNextStepX();
    unsigned int getNextStepY();

    bool isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    bool isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
};

