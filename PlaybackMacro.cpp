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
//====================================================================================
//with mouse movements
#include "stdafx.h"
#include "PlaybackMarco.h"

using namespace std;
//PURPOSE: Constructor initialize
//PARAMETER: wstring varible is the name of the file being loaded
//AlGORITHM: Use LoadMacro() function

PlaybackMacro::PlaybackMacro(wstring load_me)
{
	loadMacro(load_me);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void PlaybackMacro::actionLoop()
{
	clock_t startKey = 0, endKey = 0, startMouse, endMouse;
	int timeDif = 0, hold = 0;
	int i = 0, x = 0;

	::Sleep(5000);

	while (true)
	{
		if ((i >= actions.size()) && (x >= mouseX.size()))
		{
			cout << "done" << endl;
			break;
		}

		if (actions.size() < i)
		{
			cout << "key is done" << endl;
		}

		if (mouseX.size() < x)

		{

			cout << "mouse is done" << endl;

		}

		//Key vector is still has content

		//========================================================================================

		if (actions.size() > i)
		{

			cout << "In key input" << endl;

			//This is a key delay
			//-------------------------------------------------------------------------------
			if ((i % 2) == 0)
			{
				cout << "Key delay" << endl;
				//key delay- will do as many mouse movement as it can within the deley time
				//-------------------------------------------------------------------------------
				if (mouseX.size() > x)
				{
					cout << "first movement of key delay" << endl;
					startMouse = clock();
					actionMouse(x);
					endMouse = clock();

					x++;

					timeDif = endMouse - startMouse;

					if (timeDif <= actions[i])
					{
						hold = actions[i] - timeDif;
						i++;

						timeDif = 0;
						while (hold >= timeDif)
						{
							startMouse = clock();
							if (mouseX.size() > x)
							{
								cout << "mouse vector number " << x << endl;
								actionMouse(x);
								x++;
							}

							endMouse = clock();

							timeDif = timeDif + (endMouse - startMouse);
						}
					}
				}
				//-------------------------------------------------------------------------------

				//No more mouse movements just key delays
				else
				{
					cout << "no mouse movements just key delays" << endl;
					actionKey(i);
					i++;
				}
			}
			//not a delay do key action
			else
			{
				cout << "not a delay" << endl;
				actionKey(i);
				i++;
			}

			cout << "Out of key input" << endl;
		}
		//====================================================================================

		//Mouse vector still has content
		//====================================================================================
		if (mouseX.size() > x)
		{
			cout << "In side mouse vetcor " << x << endl;
			cout << mouseX[x] << " " << mouseY[x] << endl;

			//This is a mouse delay
			if ((x % 2) != 0)
			{
				cout << "This is a muouse delay" << endl;

				//Mouse delay - will do as many key input within the delay time
				//---------------------------------------------------------------------------------
				if (actions.size() > i)
				{
					startKey = clock();
					actionKey(i);
					endKey = clock();

					i++;

					timeDif = endKey - startKey;

					if (timeDif <= mouseX[x])
					{
						hold = mouseX[x] - timeDif;
						x++;

						timeDif = 0;

						while (hold >= timeDif)
						{
							startKey = clock();
							if (actions.size() > i)
							{
								cout << "Stuck" << endl;
								actionKey(i);
								i++;
							}
							endKey = clock();

							timeDif = timeDif + (endKey - startKey);
						}
					}
				}
				//---------------------------------------------------------------------------------
				else
				{
					cout << "in delay without key " << endl;
					actionMouse(x);

					x++;
				}
			}

			//not a delay do mouse action
			else
			{
				cout << "not delay" << endl;
				actionMouse(x);
				x++;
			}
		}
		//=====================================================================================

	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::actionKey(int i)
{
	INPUT key;
	bool flag = false;
	//+++++++++++++++++++++++++++++++++++++++++++++
	/*
	bool mouseFlag = false;
	int del = (int) clock();
	int mouseIndex = 1;
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++

	//for (int i = 0; i < actions.size(); i++)
	//{
	if (i % 2 == 0)
	{
		::Sleep(actions[i]);

		/*
		THIS DID NOT WORK AND I COULD NOT FIX
		::Sleep(actions[i]);
		int hold = (int)clock();

		cout << " actions[i] " << actions[i] << endl;
		cout << "del " << del << endl;
		cout << "+ " << actions[i] + del << endl;
		cout << " Hold " << (int)clock() << endl;

		while ((int)clock() < actions[i] + del)
		{
		cout << "In while" << endl;

		int mouseDel = mouseX[mouseIndex];

		if (((int)clock() == (hold + mouseDel)) && (!mouseFlag))
		{
		cout << "move" << endl;

		mouseIndex++;
		actionMouse(mouseIndex);
		mouseIndex++;

		mouseFlag = true;
		}

		if ((int)clock() != (hold + mouseDel) && mouseFlag)
		{
		mouseFlag = false;
		}
		}
		*/
	}

	else
	{
		if (actions[i] >= 1000)
			flag = true;

		else
			flag = false;

		key.type = INPUT_KEYBOARD;
		key.ki.wScan = 0;
		key.ki.time = 0;
		key.ki.dwExtraInfo = 0;
		key.ki.dwFlags = 0;

		if (flag)
		{
			int x = 0;
			int print = 15;

			while (actions[i] >= 1000)
			{
				actions[i] -= 1000;
				x++;
			}

			key.ki.wVk = actions[i];

			::Sleep(1000);

			while (x >= 0)
			{
				//key.ki.dwFlags = KEYEVENTF_KEYUP;

				while (print >= 0)
				{
					::Sleep(50);
					SendInput(1, &key, sizeof(INPUT));
					print -= 1;
				}
				x--;
			}
		}

		else
		{
			key.ki.wVk = actions[i];
			key.ki.dwFlags = 0;

			SendInput(1, &key, sizeof(INPUT));
		}

		/*
		if ((i + 1) != actions.size())
		{
		del = actions[i + 1];
		}
		*/
	}
	//} for loop end
}


void PlaybackMacro::actionMouse(int i)
{
	INPUT key;
	POINT positions;

	if (i % 2 != 0)
		::Sleep(mouseX[i]);

	else
	{
		key.type = INPUT_MOUSE;
		key.mi.mouseData = 0;
		key.mi.time = 0;
		key.mi.dwExtraInfo = 0;

		positions.x = mouseX[i];
		positions.y = mouseY[i];

		SetCursorPos(positions.x, positions.y);
	}
}

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::loadMacro(wstring name)
{
	fstream file;
	file.open(name.c_str());

	if (!file)
	{
		wcout << name << " File not found" << endl;
		exit(1);
	}

	else
	{
		string context;
		string tmp_hex;

		int flag;
		int num;

		string::size_type sz;

		while (file >> context)
		{
			if (context == "K")
			{
				flag = 1;
				file >> context;
			}

			else if (context == "MX")
			{
				flag = 2;
				file >> context;
			}

			else if (context == "MY")
			{
				flag = 3;
				file >> context;
			}

			for (int i = 0; i < context.length(); i++)
			{
				if (context[i] != ',')
					tmp_hex += context[i];

				else if (context[i] == ',')
				{
					num = stoi(tmp_hex, &sz);    // number base 16

					if (flag == 1)
						actions.push_back(num);

					else if (flag == 2)
						mouseX.push_back((long)num);

					else if (flag == 3)
						mouseY.push_back((long)num);

					tmp_hex = "\0";
				}
			}
		}
		actionLoop(); //remove
	}
	file.close();
}
