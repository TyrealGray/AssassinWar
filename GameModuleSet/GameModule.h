#pragma once
#include <QObject>
#include <memory>

#include "Character.h"

class QWidget;
class QPainter;
class MapModule;
class CharacterModule;
class GameModule : public QObject
{
    Q_OBJECT

public:
    GameModule(QObject * parent = 0);
    ~GameModule(void);

    void init();

    QWidget* loadMap(const QString& strMapPath);

    void loadMapTerrain();

    void addNewPlayer(const QString& name);

    void addNewCharacter(unsigned int number = 1);

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void setGameIsRun(bool bIsRun);

    void setMirror(bool bIsMirror);

    void setPlayerName(const QString& name);

    void setMapSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    void setCharacterStatus(const int &id , const unsigned int uiX, const unsigned int uiY, const int iDirection, const int iStep);
    void setCharacterStatus(const QString &name , const unsigned int uiX, const unsigned int uiY, const int iDirection, const int iStep);

    void setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY);
    void setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY);

    void setCharacterPosture(const int &id, const int &iDirection, const int &iStep);
    void setCharacterPosture(const QString &name, const int &iDirection, const int &iStep);

    void setCharacterTargetPos(const int &id, const unsigned int uiX, const unsigned int uiY);
    void setCharacterTargetPos(const QString &name, const unsigned int uiX, const unsigned int uiY);

    unsigned int getPlayerGridX();
    unsigned int getPlayerGridY();

    std::shared_ptr<Character> getCharacterByID(const int id);
    std::shared_ptr<Character> getCharacterByName(const QString &name);

    int getNumberOfCharacter();

    bool isGameRun();

    void clear();

private slots:

    void updateCharactersStatus();

private:
    MapModule* m_pMapModule;
    CharacterModule* m_pCharacterModule;
    bool m_bIsGameRun;
    QString m_playerName;
    void release();
};

