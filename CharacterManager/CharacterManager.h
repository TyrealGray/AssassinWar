#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


class QImage;
class QPainter;
class CharacterManager
{
public:
    static CharacterManager& instance();

    void drawAllCharacter(QPainter &painter);
    void setGhostPos(const float &fX, const float &fY);

private:
    QImage* m_pGhostF;
    float m_fX;
    float m_fY;

    CharacterManager();
    ~CharacterManager();
};

#endif // CHARACTERMANAGER_H
