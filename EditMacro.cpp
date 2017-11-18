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
	//open a file in read mode
	//read an integer with >>, place it in the actions vector
	//read a comma, do nothing
	//repeat until eof
	
	ifstream infile;
	infile.open(file_name);
	int i;

	string str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());  // copy file contents in string
	
	stringstream ss(str);

	while (ss >> i)
	{
		actions.push_back(i);

		if (ss.peek() == ',')			// check for comma
			ss.ignore();
	}

	infile.close();
}

void RecordMacro::recordMacro(int mode, int vectIndex)
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
		while (!flags[VK_PRIOR])								//Keep going until scroll key is pressed
		{
			if (clock() % 20 >= 0 && clock() % 20 <= 3)
			//	mousePos();
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
					delay = (int)((timer - timer2) / (CLOCKS_PER_SEC / 1000));
					timer2 = clock();
					actions.insert(actions.begin() + vectIndex, delay);
					vectIndex++;
					actions.insert(actions.begin() + vectIndex, key);
					vectIndex++;
					cout << delay << "\t" << key << endl;

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
					delay = (int)((timer - timer2) / (CLOCKS_PER_SEC / 1000));
					actions.insert(actions.begin() + vectIndex, delay);
					vectIndex++;
					actions.insert(actions.begin() + vectIndex, key + 1000);
					vectIndex++;
					flags[key] = false;
					cout << delay << "\t" << key + 1000 << endl;
					timer2 = clock();
				}
			}
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
