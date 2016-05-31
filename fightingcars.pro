######################################################
#
# Qt: 5.6
# Project: FightingCars
# Author: Theodor Serbana
# Copyright: 2016
#
#######################################################

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = THEODOR SERBANA
QMAKE_TARGET_PRODUCT = FightingCars
QMAKE_TARGET_DESCRIPTION = 2Player FightingCars
QMAKE_TARGET_COPYRIGHT = Copyright 2016
RC_ICONS = resources/img/icon.ico
RC_LANG = ENGLISH
#################

INCLUDEPATH += $$PWD/src
#########################

TEMPLATE = app
TARGET = FightingCars
#####################

QT += core gui network widgets
CONFIG += static
########################

RESOURCES +=    resources/Resources.qrc
FORMS +=    src/UserInterface/MainWindow.ui \
            src/UserInterface/AboutPopup.ui \
            src/UserInterface/ConnectPopup.ui \
            src/UserInterface/WaitPopup.ui \
####################################

HEADERS +=  src/Common/Constants.h \
            src/UserInterface/MainWindow.h \
            src/UserInterface/AboutPopup.h \
            src/UserInterface/ConnectPopup.h \
            src/UserInterface/WaitPopup.h \
            src/Network/PacketManager.h \
            src/Network/PacketReader.h \
            src/Network/PacketWriter.h \
            src/GameEngine/GameEngine.h \
            src/GameEngine/Player.h \
            src/GameEngine/Bullet.h \
            src/GameEngine/Bonus.h \

SOURCES +=  src/Common/main.cpp \
            src/UserInterface/MainWindow.cpp \
            src/UserInterface/AboutPopup.cpp \
            src/UserInterface/ConnectPopup.cpp \
            src/UserInterface/WaitPopup.cpp \
            src/Network/PacketManager.cpp \
            src/Network/PacketReader.cpp \
            src/Network/PacketWriter.cpp \
            src/GameEngine/GameEngine.cpp \
            src/GameEngine/Player.cpp \
            src/GameEngine/Bullet.cpp \
            src/GameEngine/Bonus.cpp \
###################################################
