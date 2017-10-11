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

EditMacro::saveMacro()
{
	//open a file named \macros\macro_name in write mode
	//for(int i =0; i < actions.size(); i++)
	//file << actions[i]
	//file << ',';
	
	ofstream outputFile;
	outputFile.open("macro_name");

	for (int i = 0; i < actions.size(); i++)
	{
		outputFile << actions[i] << " " << endl;
	}
	outputFile.close();
	
}

vector<int> EditMacro::loadMacro(wstring file_name)
{
	//open a file in read mode
	//read an integer with >>, place it in the actions vector
	//read a comma, do nothing
	//repeat until eof
	
	ifstream infile;
	infile.open(macro_name);
	vector<int> holder;
	int i;

	string str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());  // copy file contents in string
	
	stringstream ss(str);

	while (ss >> i)
	{
		holder.push_back(i);

		if (ss.peek() == ',')			// check for comma
			ss.ignore();
	}

	infile.close();
	return holder;
}

void EditMacro::record(int mode)
{
	//loop until scroll lock is hit VK_SCROLL/0x91
	//if mode is 1, delays are recorded
	//if mode is 2, delays are not recorded
	//basically while it's waiting between keys, it will count the milliseconds
	//with a native time function. once a key is pressed, it will record the delay
	//and append it to the vector with push_back along with the new event;
	//if in mode 2, push a 0 between each event into the vector.
	
///////////////////////////////////////////////////////////Keyboard/////////////////////////////////////////////////////////////////////	
	if(mode==1)		//With Delays
	{	
		int delay = 0;
		time_t end = 0; 
			while (true)
			{
				for (int key = 8; key <= 255; key++)
				{
					if (GetAsyncKeyState(key) == -32767)
					{		
					time_t start = time(0);
					actions.push_back(key);
					delay = start-end;
					cout << key << " " << delay << endl;
					actions.push_back(delay);
					end = time(0);
					}
				}
			}
	}
	
	else if(mode==2)	//No Delays
	{	
		while (true)
		{
			for(int key=8; key<=255; key++)
			{ 
				if (GetAsyncKeyState(key) == -32767)
				{	
					actions.push_back(key);
					actions.push_back(0);
				}
			}
		}
	}
	
	else
		return 0;
///////////////////////////////////////////////////////////////Mouse/////////////////////////////////////////////////////////////////////
	
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EditMacro::EditMacro()
{
	ofstream myfile;
	string macro_name;
	string input;
	char chars;

	cout << "Please enter macro name to edit: ";
	getline(cin, macro_name);
	myfile.open(macro_name, std::ios_base::app);

	cout << "write to the macro: ";
	getline(cin, input);
	myfile << input << endl;
	
	myfile.close();
	system("pause");
	return 0;
}

