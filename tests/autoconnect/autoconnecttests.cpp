/**
 * @file autoconnect.cpp
 * @brief Autoconnect feature tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 25 Jun 2010
 */

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QtGlobal>

#include <QtTest/QTest>

#include <servicesmanager.h>

#include "autoconnectservice.h"
#include "autoconnectclient.h"

/**
 * Helper class to be autoconnected with autoconnect service
 */
class AutoconnectServiceImpl: public QObject {
    Q_OBJECT
    public:
        explicit AutoconnectServiceImpl(QObject *parent = 0):
                    QObject(parent),
                    listSlotCount(0) {}

        void emitEmptySig() {emit emptySig();}
        void emitIntSig(quint16 num) {emit intSig(num);}

        int listSlotCount;
        QList< QList<QString> > receivedLists;
    public slots:
        void listSlot(QList<QString> list) {
            listSlotCount++;
            receivedLists.append(list);
        }
    signals:
        void emptySig();
        void intSig(quint16 num);
};

/**
 * Helper class to be autoconnected with autoconnect client
 */
class AutoconnectClientImpl: public QObject {
    Q_OBJECT
    public:
        explicit AutoconnectClientImpl(QObject *parent = 0):
                    QObject(parent),
                    emptySigCount(0),
                    intSigCount(0) {}

        void emitList(const QList<QString> &list) {emit listSlot(list);}

        int emptySigCount;
        int intSigCount;
        QList<quint16> receivedInts;
    public slots:
        void emptySig() {
            emptySigCount++;
        }
        void intSig(quint16 num) {
            intSigCount++;
            receivedInts.append(num);
        }
    signals:
        void listSlot(QList<QString> list);
};

/**
 * Helper class to check that AbsService::autoconnect returns false if not all
 * signals and slots can be connected.
 */
class IncompleteServiceImpl: public QObject {
    Q_OBJECT
    public:
        explicit IncompleteServiceImpl(QObject *parent = 0):
                            QObject(parent),
                            listSlotCount(0) {}

        void emitEmptySig() {emit emptySig();}

        int listSlotCount;
        QList< QList<QString> > receivedLists;
    public slots:
        void listSlot(QList<QString> list) {
            listSlotCount++;
            receivedLists.append(list);
        }
    signals:
        void emptySig();
};

/**
 * Helper class to check that AbsService::autoconnect returns false if not all
 * signals and slots can be connected.
 */
class IncompleteClientImpl: public QObject {
    Q_OBJECT
    public:
        explicit IncompleteClientImpl(QObject *parent = 0):
                    QObject(parent),
                    emptySigCount(0) {}

        void emitList(const QList<QString> &list) {emit listSlot(list);}

        int emptySigCount;
    public slots:
        void emptySig() {
            emptySigCount++;
        }
    signals:
        void listSlot(QList<QString> list);
};

class AutoconnctTests: public QObject {
    Q_OBJECT
    private slots:
        void init() {
            mServerManager = new qrs::ServicesManager;
            mService = new qrs::AutoconnectService(mServerManager);

            mClientManager = new qrs::ServicesManager;
            mClient = new qrs::AutoconnectClient(mClientManager);

            connect( mServerManager,SIGNAL(send(QByteArray)),
                     mClientManager,SLOT(receive(QByteArray)) );
            connect( mClientManager,SIGNAL(send(QByteArray)),
                     mServerManager,SLOT(receive(QByteArray)) );
        }

        void cleanup() {
            delete mServerManager;
            delete mClientManager;
        }

        void autoconnect() {
            AutoconnectServiceImpl service;
            AutoconnectClientImpl client;
            QVERIFY(mService->autoconnect(&service));
            QVERIFY(mClient->autoconnect(&client));

            // Sending from client to service
            QList<QString> list;
            list << "qwe" << "asd" << "zxc";
            QCOMPARE(service.listSlotCount, 0);
            client.emitList(list);
            QCOMPARE(service.listSlotCount, 1);
            QCOMPARE(service.receivedLists.size(), 1);
            QCOMPARE(service.receivedLists.at(0), list);

            // Sending from service to client
            QCOMPARE(client.emptySigCount, 0);
            service.emitEmptySig();
            QCOMPARE(client.emptySigCount, 1);

            quint16 val = 123;
            QCOMPARE(client.intSigCount, 0);
            service.emitIntSig(val);
            QCOMPARE(client.intSigCount, 1);
            QCOMPARE(client.receivedInts.at(0), val);
        }

        void incompleteClient() {
            AutoconnectServiceImpl service;
            IncompleteClientImpl client;
            QVERIFY(mService->autoconnect(&service));
            QVERIFY(!mClient->autoconnect(&client));

            // Sending from client to service
            QList<QString> list;
            list << "qwe" << "asd" << "zxc";
            QCOMPARE(service.listSlotCount, 0);
            client.emitList(list);
            QCOMPARE(service.listSlotCount, 1);
            QCOMPARE(service.receivedLists.size(), 1);
            QCOMPARE(service.receivedLists.at(0), list);

            // Sending from service to client
            QCOMPARE(client.emptySigCount, 0);
            service.emitEmptySig();
            QCOMPARE(client.emptySigCount, 1);
        }

        void incompleteService() {
            IncompleteServiceImpl service;
            AutoconnectClientImpl client;
            QVERIFY(!mService->autoconnect(&service));
            QVERIFY(mClient->autoconnect(&client));

            // Sending from client to service
            QList<QString> list;
            list << "qwe" << "asd" << "zxc";
            QCOMPARE(service.listSlotCount, 0);
            client.emitList(list);
            QCOMPARE(service.listSlotCount, 1);
            QCOMPARE(service.receivedLists.at(0), list);

            // Sending from service to client
            QCOMPARE(client.emptySigCount, 0);
            service.emitEmptySig();
            QCOMPARE(client.emptySigCount, 1);

            QCOMPARE(client.intSigCount, 0);
            QVERIFY(client.receivedInts.isEmpty());
        }
    private:
        qrs::ServicesManager *mServerManager;
        qrs::ServicesManager *mClientManager;
        qrs::AutoconnectService *mService;
        qrs::AutoconnectClient *mClient;
};

#include "autoconnecttests.moc"

QTEST_MAIN(AutoconnctTests);
