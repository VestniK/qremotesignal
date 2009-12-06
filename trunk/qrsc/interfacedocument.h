/**
 * @file interfacedocument.h
 * @brief InterfaceDocument class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Aug 2009
 */
#ifndef InterfaceDocument_H
#define InterfaceDocument_H

#include <QtCore/QString>
#include <QtCore/QIODevice>
#include <QtCore/QObject>

class InterfaceDocument: public QObject {
   Q_OBJECT
   public:
      InterfaceDocument(const QString& path);
      ~InterfaceDocument() {delete mInterfaceFile;}

      QIODevice* getIODevice() {return mInterfaceFile;}
      const QString &sourceName() {return mSourceName;}
      const QString &name() const {return mName;}

      const QString &serviceHeader() const {return mServiceHeader;}
      void setServiceHeader(const QString& val) {mServiceHeader = val;}

      const QString &serviceSource() const {return mServiceSource;}
      void setServiceSource(const QString& val) {mServiceSource = val;}

      const QString &clientHeader() const {return mClientHeader;}
      void setClientHeader(const QString& val) {mClientHeader = val;}

      const QString &clientSource() const {return mClientSource;}
      void setClientSource(const QString& val) {mClientSource = val;}

      bool isValid() const {return mValid;}
      const QString &error() const {return mError;}

      /**
       * Updates current document to the latest version
       */
      void update();
   private:
      QIODevice* mInterfaceFile;
      QString mSourceName;
      QString mName;
      QString mServiceHeader,mServiceSource;
      QString mClientHeader,mClientSource;
      bool mValid;
      QString mError;
};

#endif
