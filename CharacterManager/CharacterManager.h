#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


class QImage;
class QPainter;
class CharacterManager
{
public:
    static CharacterManager& instance();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);
    void setGhostPos(const unsigned int &iX, const unsigned int &iY);

private:
    QImage* m_pGhostF;
    unsigned int m_uiX;
    unsigned int m_uiY;

    CharacterManager();
    ~CharacterManager();
};

#endif // CHARACTERMANAGER_H
