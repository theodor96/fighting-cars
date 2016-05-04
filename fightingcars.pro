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
QMAKE_TARGET_DESCRIPTION = 2Player FightingsCars
QMAKE_TARGET_COPYRIGHT = Copyright 2016
RC_ICONS = resources/img/icon.ico
RC_LANG = ENGLISH
#################

TEMPLATE = app
TARGET = FightingCars
#####################

QT += core gui network widgets
CONFIG += static console
########################

FORMS += userinterface.ui
RESOURCES += resources/resources.qrc
####################################


HEADERS +=  userinterface.h
SOURCES +=  main.cpp \
            userinterface.cpp
#############################
