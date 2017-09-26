#include "RecordMacro.h"

RecordMacro::RecordMacro(string name)
{
	//interface will ask user for the name.
	macro_name = name + ".mcr";
}

vector<int> RecordMacro::recordMacro(int mode)
{
	//NOTE: this code section is to be shared with the EditMacro file
	//loop until scroll lock is hit VK_SCROLL/0x91
	//if mode is 1, delays are recorded
	//if mode is 2, delays are not recorded
	//basically while it's waiting between keys, it will count the milliseconds
	//with a native time function. once a key is pressed, it will record the delay
	//and append it to the vector with push_back along with the new event;
	//if in mode 2, push a 0 between each event into the vector.
}

RecordMacro::saveMacro()
{
	//SHARED CODE FROM EDITMACRO
	////open a file named \macros\macro_name in write mode
	//for(int i =0; i < actions.size(); i++)
	//file << actions[i]
	//file << ',' or ' ';
}

RecordMacro::pause()
{
	
}

RecordMacro::resume()
{
	
}
