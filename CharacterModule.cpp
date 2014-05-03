#include "CharacterModule.h"
#include "CharacterManager.h"

CharacterModule::CharacterModule(void)
    : m_pCharacterManager(NULL)
{
}


CharacterModule::~CharacterModule(void)
{
}

void CharacterModule::init()
{
    m_pCharacterManager = new CharacterManager();
}