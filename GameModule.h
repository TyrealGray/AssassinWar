#pragma once
#include<vector>

class QString;
class QWidget;
class QPainter;
class Character;
class MapModule;
//class CharacterModule;
class GameModule
{
public:
    GameModule(void);
    ~GameModule(void);

    void init();

    QWidget* loadMap(const QString& strMapPath);

    void loadMapTerrain();

    void drawAllCharacter(QPainter &painter, int iOffsetX, int iOffsetY);

    void setMapSize(const unsigned int &uiGridWidth, const  unsigned int &uiGridheight);

    void setCharacterPos(const int &id, const unsigned int uiX, const unsigned int uiY);
    void setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY);

    unsigned int getPlayerGridX();
    unsigned int getPlayerGridY();

    Character* getCharacterByID(int id);
    std::vector<int> getAllCharacterIDs();

private:
    MapModule* m_pMapModule;
    //CharacterModule* m_pCharacterModule;
    Character* m_pGhostF;
};

