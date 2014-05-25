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
    return "./Map/" +  strMapName + ".ui";
}

QString MapManager::getMapBackground(const QString& strMapName)
{
    return "./Resources/" + strMapName + "/Background/" + strMapName + ".jpg";
}

QStringList MapManager::getMapList()
{
    QStringList MapList;

    if(QFile::exists(m_strMapPath))
    {
        if(NULL == m_mapListConfig)
        {
            m_mapListConfig = new QSettings(m_strMapPath, QSettings::IniFormat);
        }

        int iMapNumber = m_mapListConfig->value("MapNumber").toInt();

        for(int index = 1 ; index <= iMapNumber ; ++index)
        {
            MapList << m_mapListConfig->value(QString("No%1").arg(index)).toString();
        }

    }
    else
    {
        //do nothing
    }

    return MapList;

}