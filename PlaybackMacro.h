//=========================================================
//NAME: Omar Gonzalez Martinez
//DATE: 10/1/17
//Compiler:
//FILE: PlaybackMarco header file
//=========================================================
#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H

//--------Globally setting up the aliases------------------
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <vector>

using namespace std;

class PlaybackMacro : public Macro
{
private:
    vector<int> actions; //
    
public:     //prototypes to be used by client
    
    PlaybackMacro(wstring);         //Constructor
    
    //PURPOSE: Loads file contexts into vector
    //PARAMETER: Wstring tpye is the name of the file
    void loadMacro(wstring);
    
    //PURPOSE: Plays vector context
    void actionLoop();
};

#endif // !PLAYBACKMACRO_H

//With mouse movement
//=========================================================
//NAME: Omar Gonzalez Martinez
//DATE: 10/1/17
//Compiler:
//FILE: PlaybackMarco header file
//=========================================================
#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H
#pragma once

//--------Globally setting up the aliases------------------
//#include "Macro.h"  all #include will be in Macro.h
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <time.h>
//--------------------------------------------------------------
using namespace std;

class PlaybackMarco
{
	//actions will be in Macro.h
private:
	vector<int> actions;
	vector<long> mouseX;
	vector<long> mouseY;


public:     //prototypes to be used by client

	PlaybackMarco(wstring);         //Constructor

									//PURPOSE: Loads file contexts into vector
									//PARAMETER: Wstring tpye is the name of the file
	void loadMacro(wstring);

	//PURPOSE: Plays vector context

	void actionLoop();

	void actionKey(int);

	void actionMouse(int);
};
#endif // !PLAYBACKMACRO_H
