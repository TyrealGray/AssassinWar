#ifndef MAPLOADER_GLOBAL_H
#define MAPLOADER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MAPLOADER_LIB
# define MAPLOADER_EXPORT Q_DECL_EXPORT
#else
# define MAPLOADER_EXPORT Q_DECL_IMPORT
#endif

#endif // MAPLOADER_GLOBAL_H
