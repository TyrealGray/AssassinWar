#include <QDataStream>
#include <QTimer>

#include "ServerBlockType.h"
#include "GameNetwork.h"
#include "GameModule.h"

const bool RECEIVE = true;
const unsigned short PACKAGE_END = 0x55aa;
GameNetwork::GameNetwork(const QString& name, GameModule* gameModule, QObject *parent /* = 0*/)
    : QTcpSocket(parent),
      m_pUpdateTimer(NULL), m_pGameModule(gameModule),
      m_bIsInit(false), m_name(name), m_nextBlockSize(0)
{
}


GameNetwork::~GameNetwork(void)
{
}

void GameNetwork::connectRoomIP(const QString& ipAddress)
{
    connectToServer(ipAddress);

    connect(this, SIGNAL(connected()), this, SLOT(initNetworkRequest()));

    connect(this, SIGNAL(readyRead()), this, SLOT(updateGame()));
}

void GameNetwork::initUpdateTimer()
{
    m_pUpdateTimer = new QTimer(this);
    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(sendUpdateRequest()));
    m_pUpdateTimer->start(100);
}

void GameNetwork::initNetworkRequest()
{
    disconnect(this, SIGNAL(connected()), this, SLOT(initNetworkRequest()));

    addPlayer();

    initUpdateTimer();

    emit networkConnected();
}

void GameNetwork::connectToServer(const QString& ipAddress)
{
    this->connectToHost(ipAddress, 8126);
}

void GameNetwork::addPlayer()
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);

    blockControl << quint16(0) << quint8(ADD_PLAYER) << m_name ;

    blockControl.device()->seek(0);
    blockControl << quint16(block.size() - sizeof(quint16));

    this->write(block);
}

void GameNetwork::setPlayerPos(const unsigned int &uiX, const unsigned int &uiY)
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);

    blockControl << quint16(0) << quint8(SET_PLAY_POSITION) << m_name << quint32(uiX) << quint32(uiY);

    blockControl.device()->seek(0);
    blockControl << quint16(block.size() - sizeof(quint16));

    this->write(block);
}

void GameNetwork::updateGame()
{
    QDataStream serverBlock(this);
    serverBlock.setVersion(QDataStream::Qt_4_8);

    while(RECEIVE)
    {
        if(0 == m_nextBlockSize)
        {
            if(isAvailablePackageSizeSmallThan(sizeof(m_nextBlockSize)))
            {
                break;
            }

            serverBlock >> m_nextBlockSize;
        }

        if(PACKAGE_END == m_nextBlockSize)
        {
            break;
        }

        if(isAvailablePackageSizeSmallThan(m_nextBlockSize))
        {
            break;
        }

        quint8 blockType;

        serverBlock >> blockType;

        if(UPDATA_POSITION == blockType)
        {
            qint32 iNumberOfCharacter = 0;
            qint32 characterID = 0;
            quint32 uiCharacterX = 0;
            quint32 uiCharacterY = 0;

            serverBlock >> iNumberOfCharacter;

            for(int index = 0 ; index < iNumberOfCharacter; ++index)
            {
                serverBlock >> characterID >> uiCharacterX >> uiCharacterY;
                m_pGameModule->setCharacterPos(characterID, uiCharacterX, uiCharacterY);
            }
        }
        else
        {
            //to do other thing
        }

        m_nextBlockSize = 0;
    }
}

void GameNetwork::sendUpdateRequest()
{
    sendUpdatePositionRequest();
}

void GameNetwork::sendUpdatePositionRequest()
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);
    unsigned short blockSize = 0;

    blockControl << quint16(0) << quint8(UPDATA_POSITION);

    blockControl.device()->seek(0);
    blockControl << quint16(block.size() - sizeof(quint16));

    this->write(block);
}

bool GameNetwork::isAvailablePackageSizeSmallThan(quint16 size)
{
    return (this->bytesAvailable() < size);
}