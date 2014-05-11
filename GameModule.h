#pragma once

#include <memory>
#include "Character.h"

class QString;
class QWidget;
class QPainter;
class MapModule;
class CharacterModule;
class GameModule
{
public:
    GameModule(void);
    ~GameModule(void);

    void init();

    QWidget* loadMap(const QString& strMapPath);

    void loadMapTerrain();

    void addNewPlayer(const QString& name);

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void updateAllCharacterPosition();

    void setMapSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    void setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY);
    void setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY);

    unsigned int getPlayerGridX();
    unsigned int getPlayerGridY();

    std::shared_ptr<Character> getCharacterByID(const int id);
    std::shared_ptr<Character> getCharacterByName(const QString &name);
    int getNumberOfCharacter();

private:
    MapModule* m_pMapModule;
    CharacterModule* m_pCharacterModule;
};

