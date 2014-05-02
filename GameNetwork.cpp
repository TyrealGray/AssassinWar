#include <QDataStream>

#include "ServerBlockType.h"
#include "GameNetwork.h"

const bool RECEIVE = true;
const unsigned short PACKAGE_END = 0x55aa;
GameNetwork::GameNetwork(const QString& name, QObject *parent /* = 0*/)
    : QTcpSocket(parent),
      m_name(name),
      m_nextBlockSize(0)
{
}


GameNetwork::~GameNetwork(void)
{
}

void GameNetwork::connectToServer(const QString& ipAddress)
{
    this->connectToHost(ipAddress, 8126);
}

void GameNetwork::setPlayerPos(const unsigned int &uiX, const unsigned int &uiY)
{
    QByteArray block;
    QDataStream blockControl(&block, QIODevice::WriteOnly);
    blockControl.setVersion(QDataStream::Qt_4_8);
    unsigned short blockSize = 0;

    blockControl << blockSize << SET_PLAY_POSITION << m_name << uiX << uiY;

    blockControl.device()->seek(0);
    blockControl << (block.size() - sizeof(unsigned short));

    this->write(block);
}

void GameNetwork::update()
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

        unsigned char blockType;

        serverBlock >> blockType;

        if(UPDATA_POSITION == blockType)
        {
            int iNumberOfCharacter = 0;
            int characterID = 0;
            unsigned int uiCharacterX = 0;
            unsigned int uiCharacterY = 0;

            serverBlock >> iNumberOfCharacter;

            for(int index = 0 ; index < iNumberOfCharacter; ++index)
            {
                serverBlock >> characterID >> uiCharacterX >> uiCharacterY;
                emit characterPositionChange(characterID, uiCharacterX, uiCharacterY);
            }
        }
        else
        {
            //to do other thing
        }

        m_nextBlockSize = 0;
    }
}

bool GameNetwork::isAvailablePackageSizeSmallThan(const unsigned int& uiSize)
{
    return (this->bytesAvailable() < uiSize);
}