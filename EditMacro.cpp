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

void RecordMacro::recordMacro(int mode)
{
	///////////////////////////////////////////////////////////Keyboard/////////////////////////////////////////////////////////////////////	
	bool flags[256];				//Flag for every key
	int delay = 1;					//Time delay between key events
	clock_t timer = clock();			//
	clock_t timer2 = clock();

	for (int i = 0; i < 255; i++)			//Set all flags to false
	{ 
		flags[i] = false;
	}

	if (mode == 1)					//With Delays
	{
		while (!flags[VK_SCROLL] && (!flags[VK_LSHIFT] && !flags[VK_END]))								//Keep going until scroll key is pressed
		{
			
			
			for (int key = 8; key <= 255; key++)
			{

				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
				{
					flags[key] = true;
					timer = clock();
					//if(i==0)
					//{
					//delay= 0;							//If you want no delay before first press
					//}	
					//else
					delay = (int)((timer - timer2) / (CLOCKS_PER_SEC / 1000));
					//i++;	
					timer2 = clock();
					actions.push_back(delay);
					actions.push_back(key);
					cout << delay << "\t" << key << endl;

				}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
				{
					timer = clock();
					delay = (int)((timer - timer2) / (CLOCKS_PER_SEC / 1000));
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					timer2 = clock();
					cout << delay << "\t" << key + 1000 << endl;
				}
			}
		}
			//system("CLS");
			saveMacro();
			

	}

	else if (mode == 2)	//No Delays
	{
		while (!flags[VK_SCROLL])								//Keep going until scroll key is pressed
		{
			for (int key = 8; key <= 255; key++)
			{

				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
				{
					flags[key] = true;
					actions.push_back(delay);
					actions.push_back(key);
				}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
				{
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << delay << "\t" << key + 1000 << endl;
				}
			}
		}
	}
		cin.clear();
		return;

}

void EditMacro::recordSingle(int mode, int delay)
{
	//record a single key down key up. append to actions vector
	//mode determines delays just as above.
	//reuires argument delay from user 
	
	bool flags[256];				//Flag for every key

	for (int i = 0; i < 255; i++)			//Set all flags to false
	{
		flags[i] = false;
	}

	if (mode == 1)					//With Delays
	{
		while (!_kbhit())								//Wait for single keystroke, requires <conio.h>
		{
			for (int key = 8; key <= 255; key++)
			{

				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
				{
					flags[key] = true;
					actions.push_back(delay);
					actions.push_back(key);
					cout << "delay = " << delay << "\t" << "key = " << key << endl;

				}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
				{
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << "delay = " << delay << "\t" << "key = " << key + 1000 << endl;
				}
			}
		}
	}
	else if (mode == 2)	//No Delays
	{
		delay = 0;
		while (!_kbhit())								//Wait for single keystroke, requires <conio.h>
		{
			for (int key = 8; key <= 255; key++)
			{

				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
				{
					flags[key] = true;
					actions.push_back(delay);
					actions.push_back(key);
					cout << delay << "\t" << key << endl;

				}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
				{
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << delay << "\t" << key + 1000 << endl;
				}
			}
		}
	}
	else
		exit;
}

void EditMacro::pause();
{
	//will pause in the middle of creating a macro. activated by pause break button
}

void EditMacro::resume()
{
	//will resume if paused...probably the pause break button

}
