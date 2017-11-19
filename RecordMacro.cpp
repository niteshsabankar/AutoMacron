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
	bool tic = false;				//Flag to check if MousePos happened in clock tick
	bool noMouse = false;				//If user doesn't want Mouse positions
	bool noKey = false;				//If user doesn't want Key delays
	int delay = 0;					//Time delay between key events
	int index =0;					//Holds last mouse click if no delays
	clock_t timer = clock();			//Timer to record delays
	clock_t timer2 = clock();			//Timer to record delays

for (int i = 0; i < 255; i++)	//Set all flags to false
{
	flags[i] = false;
}
//////////////////////////////////////////////////////MOUSE POS////////////////////////////////////////////////////////////////////////
	while (!flags[VK_PRIOR])				//Keep going until PgUp key is pressed
	{
		if(noKey == true)				//Not recording key delays don't check mouse positions
		{ }
		else						//Record mouse position 
		{
			if (noMouse == false)   		//Record mouse movement
			{
				if (clock() % 20 == 0)
				{
					if (tic == false)	//flag is set ignore
					{
						mousePos(tic, noKey, noMouse, actions, index);
					}
					else {}			//Already checked this tic
				}
				else
				{
					tic = false;		//Reset flag to record in next tic
				}
			}
			else {}					//Don't record mouse movement	
		}
//////////////////////////////////////////////////////ACTIONS/////////////////////////////////////////////////////////////////////////
		for (int key = 1; key <= 255; key++)
		{
//////////////////////////////////////////////////////KEY  DOWN///////////////////////////////////////////////////////////////////////
			if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
			{	
				flags[key] = true;
				timer = clock();											
				if (noKey == true)
				{
					delay = 2;
				}
				else
				{
					delay = (int)(timer - timer2);
				}
				timer2 = clock();											
				actions.push_back(delay);
				actions.push_back(key);
				cout << delay << "  milliseconds" << "\t" << key << endl;
				if (key == 1  && noKey == true)               //If Left Click or Right Click are the input and no delays are wanted 
				{
					mousePos(tic, noKey, noMouse, actions, index);
				}
			}
////////////////////////////////////////////////////////KEY UP////////////////////////////////////////////////////////////////////////			
			else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged
			{
				timer = clock();												
				if (noKey == true)
				{
					delay = 2;
				}
				else
				{
					delay = (int)(timer - timer2);
				}
				actions.push_back(delay);
				actions.push_back(key + 1000);
				flags[key] = false;
				cout << delay << "  milliseconds" << "\t" << key + 1000 << endl;
				timer2 = clock();											
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

void mousePos(bool tic, bool noKey, bool noMouse, vector <int> actions,int& index)
{
	POINT point;
	long delay=0;

		GetCursorPos(&point);
		if (noKey == true)    //Change mouse position delays to when click occurs
		{
			delay = actions.size() - index;
			mousex.push_back(point.x);
			mousex.push_back(delay);
			mousey.push_back(point.y);
			mousey.push_back(delay);
			index = actions.size();
		}
		else if (noKey == false) //Record normally
		{
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

