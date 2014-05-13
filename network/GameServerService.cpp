#include "ServerBlockType.h"

#include "GameServerService.h"
#include "GameModule.h"
#include "Character.h"

const unsigned short PACKAGE_END = 0x55aa;
GameServerService::GameServerService(int iSicketID, GameModule* gameModule, QObject *parent)
    : QThread(parent),
      m_pTcpSocket(NULL),
      m_pGameModule(gameModule),
      m_iSocketID(iSicketID),
      m_nextBlockSize(0)
{

}


GameServerService::~GameServerService(void)
{
    exit();
    wait();
}

void GameServerService::run()
{
    m_pTcpSocket = new QTcpSocket();

    if(!m_pTcpSocket->setSocketDescriptor(m_iSocketID))
    {
        emit error(m_pTcpSocket->error());
        return;
    }

    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readInComeRequest()), Qt::DirectConnection);
    connect(m_pTcpSocket , SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()), Qt::DirectConnection);

    exec();
}

void GameServerService::readInComeRequest()
{
    QDataStream inComeRequest(m_pTcpSocket);
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
    else if(ADD_PLAYER == blockType)
    {
        QString name;

        inComeRequest >> name ;
        m_pGameModule->addNewPlayer(name);
    }

    m_nextBlockSize = 0;
}

void GameServerService::sendCharacterPositionData()
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);

    blockControl << quint16(0) << quint8(UPDATA_POSITION);

    int iNumberOfCharacter = m_pGameModule->getNumberOfCharacter();

    qint32 id = 0;
    quint32 uiCharacterX = 0;
    quint32 uiCharacterY = 0;

    blockControl << qint32(iNumberOfCharacter);

    for(int index = 0; index < iNumberOfCharacter; ++index)
    {
        uiCharacterX = m_pGameModule->getCharacterByID(index)->getCurrentGridX();
        uiCharacterY = m_pGameModule->getCharacterByID(index)->getCurrentGridY();

        blockControl << id << uiCharacterX << uiCharacterY;
    }

    blockControl.device()->seek(0);
    blockControl << quint16(block.size() - sizeof(quint16));

    m_pTcpSocket->write(block);

    QDataStream end(m_pTcpSocket);
    end << quint16(PACKAGE_END);
}

bool GameServerService::isAvailablePackageSizeSmallThan(quint16 size)
{
    return (m_pTcpSocket->bytesAvailable() < size);
}