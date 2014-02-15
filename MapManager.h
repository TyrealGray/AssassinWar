#pragma once
#include <QString>
#include <QStringList>

class QSettings;
class MapManager
{
public:
    static MapManager& instance();

    QString getMapPath(const QString& strMapName);

    QString getMapBackground(const QString& strMapName);

    QStringList getMapList();

private:
    QString m_strMapPath;
    QSettings* m_mapListConfig;

    MapManager(void);
    ~MapManager(void);
};

