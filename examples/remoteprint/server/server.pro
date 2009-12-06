TEMPLATE = app
TARGET = server

SOURCES = main.cpp server.cpp
HEADERS=server.h
QRS_SERVICE_INTERFACES = '../common/print.xml'

QT = core network
CONFIG += console qremotesignal
