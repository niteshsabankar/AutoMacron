//=========================================================
//NAME: Omar Gonzalez Martinez
//DATE: 10/1/17
//Compiler:
//FILE: PlaybackMarco header file
//=========================================================
#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H

#include <fstream> //All includes will be in the macro.h
#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <time.h>
#include "macro.h"

using namespace std;

class PlaybackMacro : public Macro
{

public:     //prototypes to be used by client

    PlaybackMacro();         //Constructor

    //PURPOSE: Loads file contexts into vector
    //PARAMETER: Wstring tpye is the name of the file
    void loadMacro(string);

    //PURPOSE: Plays vector context
    void actionLoop(int&, int, int);
};

#endif // PLAYBACKMACRO_H
