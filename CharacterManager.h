#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <QObject>

class QTimer;
class QImage;
class QPainter;
class Character;
class CharacterManager : public QObject
{
    Q_OBJECT

public:
    CharacterManager();
    ~CharacterManager();

    void addPlayer();

    void addCharacter();

    void addNpc();

    unsigned int getPlayerGridX();
    unsigned int getPlayerGridY();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);
    void setPlayerPos(const unsigned int &iX, const unsigned int &iY);

private slots:
    void updateAllCharacterPos();

private:
    QTimer* m_pUpdateTimer;
    Character* m_pGhostF;

    void initUpdateTimer();
};

#endif // CHARACTERMANAGER_H
