#include <stdlib.h>
#include <time.h>

#include "CivilianImgPathManager.h"

const int NUMBER_OF_CIVILIAN_IMG_CLASS = 2;
CivilianImgPathManager::CivilianImgPathManager(void)
{
}


CivilianImgPathManager::~CivilianImgPathManager(void)
{
}

const char* CivilianImgPathManager::getRandomCivilianImgPathBegin()
{
    char* pImgPathBegin = "";

    unsigned int uiType = rand() % NUMBER_OF_CIVILIAN_IMG_CLASS;

    switch(uiType)
    {
    case 0:
        pImgPathBegin = "./Resources/Character/CivilianGrandPa";
        break;
    case 1:
        pImgPathBegin = "./Resources/Character/CivilianGrandMa";
        break;
    default:
        pImgPathBegin = "./Resources/Character/CivilianGrandPa";
    }

    return pImgPathBegin;
}