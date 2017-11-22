#include "EditMacro.h"

EditMacro::EditMacro(wstring file_name)
{
	loadMacro(file_name);
}

EditMacro::EditMacro()
{
	
	//pseudocode
	//ask user for input of macro name
	//macro_name = input
}

void RecordMacro::saveMacro()
{
	ofstream outputFile;
	outputFile.open(macro_name.c_str());
	
	for (int i = 0; i < actions.size(); i++)
		{
			outputFile << to_string(actions[i]) << ",";
		}

	outputFile.close();
}

void EditMacro::loadMacro(wstring file_name)
{
	cout << "in load macro" << endl;
	fstream file;
	file.open(name.c_str());

	if (!file)	//Error file does not exist exit program
	{
		cout << name << " File not found" << endl;
		exit(1);
	}
	else
	{
		//-------Local variables------------------------------------------------------------------------
		string context;      //Holds one content of the file
		string tmp_num;      //Holds one char of the file
		int flag;            //Flag for which vector to input
		int num;             //Convet string input to int

		string::size_type sz;

		while (file >> context)
		{
			if (context == "K")  //Flag one key stroke input
			{
				flag = 1;
				file >> context;
			}

			else if (context == "MX")  //Flag 2 mouse X point
			{
				flag = 2;
				file >> context;
			}

			else if (context == "MY")  //Flag 3 mouse Y point
			{
				flag = 3;
				file >> context;
			}

			//For go throuht each char in the file if char add to context if "," add to vector
			//--------------------------------------------------------------------
			for (int i = 0; i < context.length(); i++)
			{
				if (context[i] != ',')
					tmp_num += context[i];

				else if (context[i] == ',')
				{
					num = stoi(tmp_num, &sz);    // number base 16

					if (flag == 1)
						actions.push_back(num);

					else if (flag == 2)
						mousex.push_back((long)num);

					else if (flag == 3)
						mousey.push_back((long)num);

					tmp_num = "\0";   //Restart context
				}
			}
		}
	}

	file.close();  //Close file
}

void RecordMacro::recordMacro(int mode, int vectIndex)
{
	bool flags[256];				//Flag for every key
	bool tic = false;				//Flag to check if MousePos happened in clock tick
	bool noMouse = false;				//If user doesn't want Mouse positions
	bool noKey = false;				//If user doesn't want Key delays
	int delay = 0;					//Time delay between key events
	int index = 0;					//Holds last mouse click if no delays
	clock_t timer = clock();			//Timer to record delays
	clock_t timer2 = clock();			//Timer to record delays

	for (int i = 0; i < 255; i++)	//Set all flags to false
	{
		flags[i] = false;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copy vector items after given vector index in a temporary vector.
	for (std::vector<int>::const_iterator i = actions.begin() + vectIndex; i != actions.end(); ++i)
		tempActions.push_back(*i);

	for (std::vector<int>::const_iterator i = mousex.begin() + vectIndex; i != mousex.end(); ++i)
		tempMousex.push_back(*i);

	for (std::vector<int>::const_iterator i = mousey.begin() + vectIndex; i != mousey.end(); ++i)
		tempMousey.push_back(*i);

// delete vector items which comes after given vector index
	actions.resize(vectIndex);

	mousex.resize(vectIndex);

	mousey.resize(vectIndex);
//////////////////////////////////////////////////////MOUSE POS///////////////////////////////////////////////////////////////
	while (!flags[VK_PRIOR])				//Keep going until PgUp key is pressed
	{
		if (noKey == true)				//Not recording key delays don't check mouse positions
		{
		}
		else						//Record mouse position
		{
			if (noMouse == false)   		//Record mouse movement
			{
				if (clock() % 20 == 0)
				{
					if (tic == false)	//flag is set ignore
					{
						mousePos(tic, noKey, noMouse, actions, index);					// Need to change vectIndex
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
				if (key == 1 && noKey == true)               //If Left Click or Right Click are the input and no delays are wanted
				{
					mousePos(tic, noKey, noMouse, actions, index);							// Need to change vectIndex
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
// push back temporary vector data into main vector 
	for (std::vector<int>::const_iterator i = tempActions.begin(); i != tempActions.end(); ++i)
		actions.push_back(*i);

	tempActions.clear(); // clear temporary vector

	for (std::vector<int>::const_iterator i = tempMousex.begin(); i != tempMousex.end(); ++i)
		mousex.push_back(*i);

	tempMousex.clear();

	for (std::vector<int>::const_iterator i = tempMousey.begin(); i != tempMousey.end(); ++i)
		mousey.push_back(*i);

	tempMousey.clear();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void mousePos(bool tic, bool noKey, bool noMouse, vector <int> actions, int& index)
{
	POINT point;
	long delay = 0;


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


void EditMacro::recordSingle(int mode, int delay, int vectIndex)
{
	//record a single key down key up. append to actions vector
	//mode determines delays just as above.
	//reuires 3 argument: mode, delay, and vectorIndex where action to be inserted
	bool flags[256];						//Flag for every key

	for (int i = 0; i < 255; i++)			//Set all flags to false
	{
		flags[i] = false;
	}

	{
		while (!flags[VK_PRIOR])							//Wait for single keystroke, requires <conio.h>
		{
			if (_kbhit())
			{
				for (int key = 8; key <= 255; key++)
				{

					if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
					{
						flags[key] = true;
						if (mode == 0)                                                  //Record without delays
						{
							delay = 0;
						}
						actions.insert(actions.begin() + vectIndex, delay);
						vectIndex++;
						actions.insert(actions.begin() + vectIndex, key);
						vectIndex++;
						cout << delay << "\t" << key << endl;

					}
					else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
					{
						if (mode == 0)
						{
							delay = 0;
						}
						actions.insert(actions.begin() + vectIndex, delay);
						vectIndex++;
						actions.insert(actions.begin() + vectIndex, key + 1000);
						vectIndex++;
						flags[key] = false;
						cout << delay << "\t" << key + 1000 << endl;
					}
				}
				break;
			}
		}
	}
}

void EditMacro::pause();
{
	//will pause in the middle of creating a macro. activated by pause break button
}

void EditMacro::resume()
{
	//will resume if paused...probably the pause break button

}
