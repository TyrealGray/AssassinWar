#pragma once
#include <QString>

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

    Character(int id, unsigned int uiSpeed, unsigned int uiType);

    virtual ~Character(void);

    void init();

    void die();

    void setHide(bool isHide);

    void setPosition(const unsigned int &uiX, const unsigned int &uiY);

    void updateNextPosture();

    void updateNextCharacterImg();

    unsigned int getNextStepGridX();

    unsigned int getNextStepGridY();

    void goTo(const unsigned int &uiX, const unsigned int &uiY);

    void render(QPainter &painter, int &iOffsetX, int &iOffsetY);

    void setSpeed(unsigned int& uiSpeed);

    void setPosture(const int &iDirection, const int &iStep);

    unsigned int getSpeed();

    unsigned int getCurrentGridX();

    unsigned int getCurrentGridY();

    unsigned int getTargetGridX();

    unsigned int getTargetGridY();

    int getDirection();

    int getStep();

private:
    QImage* m_pCharacter;
    QReadWriteLock* m_pLock;
    int m_id;
    unsigned int m_uiSpeed;
    unsigned int m_uiType;
    unsigned int m_uiCurrentX;
    unsigned int m_uiCurrentY;
    unsigned int m_uiTargetGridX;
    unsigned int m_uiTargetGridY;
    int m_iDirection;
    int m_iLastTimeDirection;
    int m_iStep;
    int m_iFpsStep;
    QString m_imgPathBegin;

    void setCurrentX(int iX);
    void setCurrentY(int iY);
    void setDirection(int iDirection);
    void setImgPathBegin(const QString& imgPath);

    unsigned int getCurrentX();
    unsigned int getCurrentY();
    unsigned int getNextStepX();
    unsigned int getNextStepY();
    QString getImgPathBegin();

    bool isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    bool isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
};

