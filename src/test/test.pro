include(../../smpp.pri)
include(../lib/lib.pri)

TEMPLATE = app

TARGET = $$APP_TARGET

DESTDIR = $$APP_PATH

CONFIG += console

QT      -= gui
QT      += core network

TEMPLATE = app

SOURCES  += \
  test_server.cpp \
  test_client.cpp \
  main.cpp

HEADERS += \
  test_client.h \
  test_server.h \
  global.h

unix: {
  INSTALLS += /usr/bin
}
