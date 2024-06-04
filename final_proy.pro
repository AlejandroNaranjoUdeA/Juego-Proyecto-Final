QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    disparo.cpp \
    ecenario.cpp \
    enemigos.cpp \
    main.cpp \
    mina.cpp \
    regla_juego.cpp \
    rocas.cpp \
    sprites.cpp \
    ventanas.cpp \
    canon.cpp

HEADERS += \
    disparo.h \
    ecenario.h \
    enemigos.h \
    mina.h \
    regla_juego.h \
    rocas.h \
    sprites.h \
    ventanas.h \
    canon.h

FORMS += \
    ventanas.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
