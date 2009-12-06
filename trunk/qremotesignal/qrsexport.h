/**
 * @file qrsexport.h
 * @brief QRS_EXPORT macro definition
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 15 Oct 2009
 */
#ifndef _QRS_EXPORT_H
#define _QRS_EXPORT_H

#include <QtCore/QtGlobal>

#ifdef BUILD_QRS_SHARED_LIB
// we are building shared library
#define QRS_EXPORT Q_DECL_EXPORT
#else
// we are using shared library
#define QRS_EXPORT Q_DECL_IMPORT
#endif

#endif
