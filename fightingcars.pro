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
INCLUDEPATH += $$PWD/src/GameEngine
INCLUDEPATH += $$PWD/src
#########################

TEMPLATE = app
TARGET = FightingCars
#####################

QT += core gui network widgets
CONFIG += static console
########################

RESOURCES +=    resources/resources.qrc
FORMS +=        src/UserInterface/userinterface.ui
####################################


HEADERS +=      src/UserInterface/userinterface.h

SOURCES +=      src/main.cpp \
                src/UserInterface/userinterface.cpp
#############################
