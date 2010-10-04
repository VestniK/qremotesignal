/**
 * @file devicemanagertests.cpp
 * @brief DeviceManager tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Oct 2009
 */
#include <QtCore/QObject>
#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtTest/QtTest>

#include <QtCore/QtDebug>

#include "QRemoteSignal"
#include "devicemanager.h"

class DeviceManagerTests: public QObject
{
Q_OBJECT
private slots:
    void init() {
        mDevice1.setData("");
        mDevice2.setData("");
        mDevice1.open(QIODevice::ReadWrite);
        mDevice2.open(QIODevice::ReadWrite);
        mDevManager1.setDevice(&mDevice1);
        mDevManager2.setDevice(&mDevice2);
    };

    void cleanup() {
        mDevice1.close();
        mDevice2.close();
    };

    void testReadingAlreadyExistingData() {
        QByteArray msg = "Hello";
        mDevManager2.setDevice(0);

        QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
        mDevManager1.send(msg);

        sendDataToDev2(mDevice1.buffer());
        QCOMPARE(spy.count(), 0);

        mDevManager2.setDevice(&mDevice2);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.first().at(0).toByteArray(), msg);
    };

    void testSendReceive() {
        QByteArray msg = "Hello";

        QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
        mDevManager1.send(msg);

        sendDataToDev2(mDevice1.buffer());

        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.first().at(0).toByteArray(), msg);
    };

    void testRecievePart() {
        QByteArray msg = "Long message";

        QSignalSpy mDevice2ReadyReadSpy(&mDevice2,SIGNAL(readyRead()));
        QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));

        mDevManager1.send(msg);
        int splitPoint = mDevice1.buffer().size()/2;

        sendDataToDev2(mDevice1.buffer().left(splitPoint));
        QCOMPARE(mDevice2ReadyReadSpy.count(), 1);
        QCOMPARE(spy.count(), 0);

        sendDataToDev2(mDevice1.buffer().mid(splitPoint));
        QCOMPARE(mDevice2ReadyReadSpy.count(), 2);
        // Check that message was splited correctly
        QCOMPARE(mDevice1.buffer(), mDevice2.buffer());
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.first().at(0).toByteArray(), msg);
    };

    void testReceiveMultiple() {
        QByteArray msg1 = "Hello";
        QByteArray msg2 = "World";

        QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
        mDevManager1.send(msg1);
        mDevManager1.send(msg2);

        sendDataToDev2(mDevice1.buffer());

        QCOMPARE(spy.count(), 2);
        QCOMPARE(spy.at(0).at(0).toByteArray(), msg1);
        QCOMPARE(spy.at(1).at(0).toByteArray(), msg2);
    };

    void testReceiveOneAndHalf() {
        QByteArray msg1 = "Hello";
        QByteArray msg2 = "Big World";

        QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
        mDevManager1.send(msg1);
        mDevManager1.send(msg2);
        int splitPoint = mDevice1.buffer().size() - msg2.size()/2;

        sendDataToDev2(mDevice1.buffer().left(splitPoint));
        QCOMPARE(spy.count(), 1);
        sendDataToDev2(mDevice1.buffer().mid(splitPoint));
        // Check that message was splited correctly
        QCOMPARE(mDevice1.buffer(), mDevice2.buffer());
        QCOMPARE(spy.count(), 2);
        QCOMPARE(spy.at(0).at(0).toByteArray(), msg1);
        QCOMPARE(spy.at(1).at(0).toByteArray(), msg2);
    };

    /**
     * This test shouldn't cause segfault or some other unexpected critical
     * errors. It also checks that DeviceManager doesn't tries to reopen
     * device to send message.
     */
    void testDevUnexpectedlyClosed() {
        QBuffer dev;
        dev.open(QIODevice::ReadWrite);
        qrs::internals::DeviceManager devManager;
        QSignalSpy spy(&devManager,SIGNAL(deviceUnavailable()));

        devManager.setDevice(&dev);
        QCOMPARE(spy.count(), 0);
        dev.close();
        devManager.send(QByteArray("hello"));
        QCOMPARE(spy.count(), 1);
        QVERIFY(!dev.isOpen());
        QCOMPARE(dev.buffer(), QByteArray());
    }

    /**
     * This test shouldn't cause segfault or some other unexpected critical
     * errors.
     */
    void testDevUnexpectedlyDeleted() {
        QBuffer *dev = new QBuffer();
        dev->open(QIODevice::ReadWrite);
        qrs::internals::DeviceManager devManager;
        QSignalSpy spy(&devManager,SIGNAL(deviceUnavailable()));

        devManager.setDevice(dev);
        QCOMPARE(spy.count(), 0);
        delete dev;
        QCOMPARE(spy.count(), 1);
        devManager.send(QByteArray("hello"));
        QCOMPARE(spy.count(), 2);
    }

    void testSetDevice() {
        QBuffer dev;
        qrs::internals::DeviceManager devManager;
        QSignalSpy spy(&devManager,SIGNAL(deviceUnavailable()));

        // set 0 device should cause deviceUnavailable signal to be emitted
        devManager.setDevice(0);
        QCOMPARE(spy.count(), 1);
        // set not opened device should cause deviceUnavailable signal to be
        // emitted
        devManager.setDevice(&dev);
        QCOMPARE(spy.count(), 2);
        // set not writable device should cause deviceUnavailable signal to be
        // emitted
        dev.open(QIODevice::ReadOnly);
        devManager.setDevice(&dev);
        QCOMPARE(spy.count(), 3);
        dev.close();
        // set not opened readable should cause deviceUnavailable signal to be
        // emitted
        dev.open(QIODevice::WriteOnly);
        devManager.setDevice(&dev);
        QCOMPARE(spy.count(), 4);
        dev.close();
        // set device opened for read write should cause deviceUnavailable
        // signal to be emitted
        dev.open(QIODevice::ReadWrite);
        devManager.setDevice(&dev);
        QCOMPARE(spy.count(), 4);
    }
private:
    QBuffer mDevice1;
    QBuffer mDevice2;
    qrs::internals::DeviceManager mDevManager1;
    qrs::internals::DeviceManager mDevManager2;

    void sendDataToDev2(const QByteArray& data) {
        qint64 pos = mDevice2.pos();
        mDevice2.write(data);
        mDevice2.seek(pos);
        // Return to qt event loop to allow it process asincronious signals
        QTest::qWait(1);
    }
};

QTEST_MAIN(DeviceManagerTests)
#include "devicemanagertests.moc"
