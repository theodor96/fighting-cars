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
QMAKE_TARGET_DESCRIPTION = Two players game application
QMAKE_TARGET_COPYRIGHT = Copyright 2016
#######################################

TEMPLATE = app
TARGET = FightingCars
#####################

QT += core gui network widgets
CONFIG += static console
########################

SOURCES += main.cpp
RESOURCES += resources/resources.qrc
####################################
