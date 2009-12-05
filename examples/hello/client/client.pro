TEMPLATE = app
TARGET=client

SOURCES = client.cpp main.cpp
HEADERS = client.h
QRS_CLIENT_INTERFACES = ../services/hello.xml

QT -= gui
QT += network

CONFIG += console qremotesignal
