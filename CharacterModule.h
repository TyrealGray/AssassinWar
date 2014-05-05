#pragma once

class QString;
class CharacterManager;
class CharacterModule
{
public:
    CharacterModule(void);
    ~CharacterModule(void);

    void init();

    void setCharacterPos(const int id, const unsigned int uiX, const unsigned int uiY);
    void setCharacterPos(const QString &name, const unsigned int uiX, const unsigned int uiY);

private:
    CharacterManager* m_pCharacterManager;
};

