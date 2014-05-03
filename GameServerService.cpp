#include <vector>

#include "ServerBlockType.h"

#include "GameServerService.h"
#include "GameModule.h"
#include "Character.h"

const unsigned short PACKAGE_END = 0x55aa;
GameServerService::GameServerService(GameModule* gameModule, QObject *parent)
    : QTcpSocket(parent),
      m_pGameModule(gameModule),
      m_nextBlockSize(0)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readInComeRequest()));
    connect(this , SIGNAL(disconnected()), this, SLOT(deleteLater()));
}


GameServerService::~GameServerService(void)
{
}

void GameServerService::readInComeRequest()
{
    QDataStream inComeRequest(this);
    inComeRequest.setVersion(QDataStream::Qt_4_8);

    if(0 == m_nextBlockSize)
    {
        if(isAvailablePackageSizeSmallThan(sizeof(quint16)))
        {
            return;
        }
        inComeRequest >> m_nextBlockSize;
    }

    if(isAvailablePackageSizeSmallThan(m_nextBlockSize))
    {
        return;
    }

    quint8 blockType;

    inComeRequest >> blockType;

    if(SET_PLAY_POSITION == blockType)
    {
        QString name;
        quint32 uiCharacterX = 0;
        quint32 uiCharacterY = 0;

        inComeRequest >> name >> uiCharacterX >> uiCharacterY;
        m_pGameModule->setCharacterPos(name, uiCharacterX, uiCharacterY);
    }
    else if(UPDATA_POSITION == blockType)
    {
        sendCharacterPositionData();
    }
    else
    {

    }

    m_nextBlockSize = 0;
}

void GameServerService::sendCharacterPositionData()
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);

    blockControl << quint16(0) << quint8(UPDATA_POSITION);

    std::vector<int>ids = m_pGameModule->getAllCharacterIDs();
    qint32 id = 0;
    quint32 uiCharacterX = 0;
    quint32 uiCharacterY = 0;

    blockControl << qint32(ids.size());

    for(int index = 0; index < ids.size(); ++index)
    {
        id = ids[index];

        uiCharacterX = m_pGameModule->getCharacterByID(ids[index])->getCurrentGridX();
        uiCharacterY = m_pGameModule->getCharacterByID(ids[index])->getCurrentGridY();

        blockControl << id << uiCharacterX << uiCharacterY;
    }

    blockControl.device()->seek(0);
    blockControl << quint16(block.size() - sizeof(quint16));

    this->write(block);

    QDataStream end(this);
    end << quint16(PACKAGE_END);
}

bool GameServerService::isAvailablePackageSizeSmallThan(quint16 size)
{
    return (this->bytesAvailable() < size);
}