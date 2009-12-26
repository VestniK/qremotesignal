TEMPLATE=app
TARGET=client

SOURCES=client.cpp
QRS_CLIENT_INTERFACES='../services/print.xml'

QT = core network
CONFIG += console qremotesignal