#include "RecordMacro.h"

RecordMacro::RecordMacro()
{
	macro_name = L"default.mcr";
}

RecordMacro::RecordMacro(string name)
{
	//interface will ask user for the name.
	macro_name = name + L".mcr";
}

vector<int> RecordMacro::recordMacro(int mode)
{
	bool flags[256];				//Flag for every key
	int delay = 0;					//Time delay between key events
	clock_t timer = clock();			//
	clock_t timer2 = clock();			//
	
	for (int i = 0; i < 255; i++)			//Set all flags to false
	{
		flags[i] = false;
	}
	
	{	
		while (!flags[VK_SCROLL])								//Keep going until scroll key is pressed
		{		
			if (clock() % 20 >= 0 && clock() % 20 <= 3)
				mousePos();
			for (int key = 8; key <= 255; key++)
			{
		
				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
					{	
					flags[key] = true;
					timer = clock();
					if (mode == 0)                                                  //Record without delays
					{
						delay = 0;
					}
					else
					{
						delay = (int)(timer - timer2);
					}
					delay = (int)((timer-timer2) / (CLOCKS_PER_SEC / 1000));
					timer2 = clock();
					actions.push_back(delay);
					actions.push_back(key);
					cout << delay <<"\t"<< key << endl;
			
					}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
					{
					timer = clock();
					if (mode == 0)
					{
						delay = 0;
					}
					else
					{
						delay = (int)(timer - timer2);
					}
					delay = (int)((timer-timer2) / (CLOCKS_PER_SEC / 1000));
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << delay <<"\t"<< key+1000 << endl;
					timer2 = clock();
					}
			}	
		}
	}
}

void RecordMacro::saveMacro()
{
	ofstream outputFile;
	outputFile.open(macro_name.c_str());

	for (int i = 0; i < actions.size(); i++)
	{
		outputFile << actions[i] << " " << endl;	
	}

	for (int i = 0; i < mousex.size(); i++)
	{
		outputFile << mousex[i] << " " << endl;
	}

	for (int i = 0; i < mousey.size(); i++)
	{
		outputFile << mousey[i] << " " << endl;
	}
	outputFile.close();
}

void RecordMacro::mousePos()
{
	vector<long> mousex;
	vector<long> mousey;
	POINT point;
	long delay = 0;
	if (clock() % 19 == 0)
	{
		Sleep(1);
		GetCursorPos(&point);
		if (mousex.empty() || point.x != mousex[mousex.size() - 2])
		{
			delay += 20;
			mousex.push_back(point.x);
			mousex.push_back(delay);
			mousey.push_back(point.y);
			mousey.push_back(delay);
			delay = 0;
		}
		else
		{
			delay += 20;
		}

	}
}

RecordMacro::pause()
{
	
}

RecordMacro::resume()
{
	
}
