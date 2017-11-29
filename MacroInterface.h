#ifndef MACROINTERFACE_H
#define MACROINTERFACE_H

#include "EditMacro.h"
#include "PlaybackMacro.h"
#include "RecordMacro.h"
#include <iostream> //temporary for command line interface
#include <Windows.h>
#include <string>

HWND console = GetConsoleWindow();
RECT console_size;


EditMacro *edit_me;
PlaybackMacro *play_me;
RecordMacro *record_me;

void baseInterface();
void editInterface(wstring);
void playbackInterface(wstring);
void recordInterface(wstring);

#endif

