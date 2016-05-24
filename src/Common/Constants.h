#ifndef CONSTANTS_H
#define CONSTANTS_H

const quint16 MAIN_WINDOW_WIDTH = 650;
const quint16 MAIN_WINDOW_HEIGHT = 650;
const quint16 ABOUT_POPUP_WIDTH = 200;
const quint16 ABOUT_POPUP_HEIGHT = 200;
const quint16 WAIT_POPUP_WIDTH = 200;
const quint16 WAIT_POPUP_HEIGHT = 200;
const quint16 CONNECT_POPUP_WIDTH = 200;
const quint16 CONNECT_POPUP_HEIGHT = 200;

const quint8 MESSAGE_TYPE_CONNECTION = 1;
const quint8 MESSAGE_TYPE_CONNECTION_INITIATE = 1;
const quint8 MESSAGE_TYPE_CONNECTION_CANCEL = 4;

const quint32 PEER_PORT = 49000;

const quint8 USERNAME_MIN_CHARACTERS = 5;

const char* const WINDOW_TITLE = "FightingCars";
const char* const STR_ASK_EXIT = "Are you sure you want to exit the game?";
const char* const STR_ASK_PLAY = "Do you want to play versus ";

#endif // CONSTANTS_H
