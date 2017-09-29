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
}

void EditMacro::loadMacro(wstring file_name)
{
	//open a file in read mode
	//read an integer with >>, place it in the actions vector
	//read a comma, do nothing
	//repeat until eof
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
}

void EditMacro::recordSingle(int mode)
{
	//record a single key down key up. append to actions vector
	//mode determines delays just as above.
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

