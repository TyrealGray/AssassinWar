#pragma once

enum Direction {GO_UP, GO_DOWN, GO_LEFT, GO_RIGHT};

class QImage;
class QPainter;
class Character
{
public:
    Character(void);
    ~Character(void);

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
    Direction m_eDirection;
    unsigned int getCurrentX();
    unsigned int getCurrentY();
    void updateCoord(const unsigned int &uiTargetGridCoord, unsigned int &uiCurrentCoord, Direction eIncrease, Direction eDecrease);
    bool isDecreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    bool isIncreaseToTargetPos(const unsigned int &uiTargetGridCoord, const unsigned int &uiCurrentCoord);
    void setDirection(Direction eDirection);
};

