#ifndef SMPP_GLOBAL_H
#define SMPP_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(SMPP_EXPORTS)
#  define SMPP_EXPORT Q_DECL_EXPORT
#elif defined(SMPP_IMPORTS)
#  define SMPP_EXPORT Q_DECL_IMPORT
#else
#  define SMPP_EXPORT
#endif

#endif // SMPP_GLOBAL_H
