#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


class QImage;
class QPainter;
class CharacterManager
{
public:
    static CharacterManager& instance();

    void drawAllCharacter(QPainter &painter);
    void setGhostPos(const int &iX, const int &iY);

private:
    QImage* m_pGhostF;
    int m_iX;
    int m_iY;

    CharacterManager();
    ~CharacterManager();
};

#endif // CHARACTERMANAGER_H
