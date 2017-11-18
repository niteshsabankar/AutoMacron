//=========================================================
//NAME: Omar Gonzalez Martinez
//DATE: 10/1/17
//Compiler:
//FILE: PlaybackMarco header file
//=========================================================
#ifndef PLAYBACKMACRO_H
#define PLAYBACKMACRO_H

//--------Globally setting up the aliases------------------
#include <fstream> //All includes will be in the macro.h
#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <time.h>

using namespace std;

class PlaybackMacro
{
private:
	vector<int> actions; //These will be in the marco.h
	vector<long> mouseX;
	vector<long> mouseY;

public:     //prototypes to be used by client

	PlaybackMacro(wstring);         //Constructor

	//PURPOSE: Loads file contexts into vector
	//PARAMETER: Wstring tpye is the name of the file
	void loadMacro(wstring);

	//PURPOSE: Plays vector context
	void actionLoop();

	//PURPOSE: Play a key event
	//PARAMETER: One int type - the index of the vector
	void actionKey(int, int&);

	//PURPOSE: Play a mouse event
	//PARAMETER: One int type - the index of the vector
	void actionMouse(int, int&);

	
};

#endif // !PLAYBACKMACRO_H
