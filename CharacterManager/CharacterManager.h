#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


class QImage;
class QPainter;
class Character;
class CharacterManager
{
public:
    static CharacterManager& instance();

    unsigned int getPlayerCharacterGridX();
    unsigned int getPlayerCharacterGridY();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);
    void setGhostPos(const unsigned int &iX, const unsigned int &iY);

private:
    Character* m_pGhostF;

    CharacterManager();
    ~CharacterManager();
};

#endif // CHARACTERMANAGER_H
