#include <QFile>
#include <QSettings>

#include "MapManager.h"


MapManager::MapManager(void)
    : m_strMapPath("./ConfigFile/MapList.ini"),
      m_mapListConfig(NULL)
{
}


MapManager::~MapManager(void)
{
    if(NULL != m_mapListConfig)
    {
        delete m_mapListConfig;
        m_mapListConfig = NULL;
    }
}

MapManager& MapManager::instance()
{
    static MapManager sMapManager;
    return sMapManager;
}

QString MapManager::getMapPath(const QString& strMapName)
{
    return "./map/" +  strMapName + ".ui";
}

QString MapManager::getMapBackground(const QString& strMapName)
{
    return "./Resources/" + strMapName + "/Background/" + strMapName + ".jpg";
}

QStringList MapManager::getMapList()
{
    QStringList MapList;

    if(QFile::exists("./ConfigFile/MapList.ini"))
    {
        if(NULL == m_mapListConfig)
        {
            m_mapListConfig = new QSettings("./ConfigFile/MapList.ini", QSettings::IniFormat);
        }

        int iMapNumber = m_mapListConfig->value("MapNumber").toInt();

        QString strMapIndex = "map0";

        for(int index = 1 ; index <= iMapNumber ; ++index)
        {
            MapList << m_mapListConfig->value(QString("MapNumber%1").arg(index)).toString();
        }

    }
    else
    {
        //do nothing
    }

    return MapList;

}