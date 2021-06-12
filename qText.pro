QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cc \
    src/mainwindow.cc

HEADERS += \
    src/mainwindow.hh

FORMS += \
    src/ui/mainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
unix: target.path = /usr/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources.qrc
