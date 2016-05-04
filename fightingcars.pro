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

INCLUDEPATH += $$PWD/src/UserInterface
INCLUDEPATH += $$PWD/src/Common
INCLUDEPATH += $$PWD/src/GameEngine
INCLUDEPATH += $$PWD/src
#########################

TEMPLATE = app
TARGET = FightingCars
#####################

QT += core gui network widgets
CONFIG += static console
########################

RESOURCES +=    resources/Resources.qrc
FORMS +=        src/UserInterface/UserInterface.ui
####################################


HEADERS +=      src/UserInterface/UserInterface.h \
                src/Common/Constants.h

SOURCES +=      src/main.cpp \
                src/UserInterface/UserInterface.cpp
#############################