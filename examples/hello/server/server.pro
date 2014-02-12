TEMPLATE = app
TARGET=server

SOURCES = server.cpp connection.cpp main.cpp
HEADERS = server.h connection.h
QRS_SERVICE_INTERFACES = ../services/hello.xml

QT -= gui
QT += network

CONFIG += console qremotesignal2
