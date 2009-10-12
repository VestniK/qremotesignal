/**
 * @file messagetesttools.h
 * @brief qrs::Message comparision and debug printing operators
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 13 Oct 2009
 */
#ifndef _MessageTestTools_H
#define _MessageTestTools_H

#include <QtCore>
#include <QtTest>

#include "QRemoteSignal"

/**
 * @brief qrs::Message comparision
 *
 * This operator defined to simplify tests there is no necesity to move it to the
 * class qrs::Message itself.
 */
bool operator== (const qrs::Message& msg1, const qrs::Message& msg2);

void printParam(const QVariant& param, int indent, QTextStream& out);
void printMapParam(const QVariantMap& param, int indent, QTextStream& out);
void printListParam(const QVariantList& param, int indent, QTextStream& out);

namespace QTest {
   /**
    * @brief qrs::Message textual representation for debug printing
    */
   char* toString (const qrs::Message& msg);
}

#endif
