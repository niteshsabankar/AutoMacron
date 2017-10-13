//===============================================================
//NAME: Omar Gonzalez Martinez
//Date: 10/1/17
//Complier:
//File type: PlaybackMarcro implementaion file
//===============================================================
#include "stdafx.h"
#include "PlaybackMacro.h"

//PURPOSE: Constructor initialize
//PARAMETER: wstring varible is the name of the file being loaded
//AlGORITHM: Use LoadMacro() function
PlaybackMacro::PlaybackMacro(wstring load_me)
{
	loadMacro(load_me);
}

void PlaybackMacro::actionLoop()
{
	int code;
	bool flag = false;

	INPUT key;
	::Sleep(5000);
    
	for (int i = 0; i < actions.size(); i++)
	{
		if (i % 2 == 0)
		{
			clock_t wait;
			wait = clock() + (((float)actions[i] / 1000.0) * CLOCKS_PER_SEC);
			while (clock() < wait);
		}
		else
		{
			code = actions[i];
			if (code >= 1000)
			{
				code -= 1000;
				flag = true;
			}
			else
			{flag = false;}

			key.type = INPUT_KEYBOARD;
			key.ki.wScan = 0;
			key.ki.time = 0;
			key.ki.dwExtraInfo = 0;

			key.ki.wVk = code;
			
			if (flag)
			{
				key.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &key, sizeof(INPUT));
			}
			else
			{
				key.ki.dwFlags = 1;//0
				SendInput(1, &key, sizeof(INPUT));
			}
			
		}
	}
}
		
void PlaybackMacro::loadMacro(wstring name)
{
	fstream file;
	file.open(name);

	if (!file)
	{
		wcout << name << " File not found" << endl;
		exit(1);
	}
	else
	{
		string context;
		string tmp;
		int num;

		file >> context;
		while (file)
		{
			for (int i = 0; i < context.length(); i++)
			{
				if (context[i] != ',')
				{
					tmp += context[i];
				}
				else if (context[i] == ',')
				{
					const char* dec = tmp.c_str();
					num = (int)strtol(dec, NULL, 10);       // number base 16

					actions.push_back(num);
					

					tmp = "\0";
				}
			}
			file >> context;
		}
		file.close();

		actionLoop();	
	}
}
