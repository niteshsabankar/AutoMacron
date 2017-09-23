/*Macro implementation file
Includes constructors for Macro class as well as methods*/
#include "Macro.h"

Macro::Macro()
{
	//ask user for input of name
	//setName("Placeholder");
}

Macro::Macro(string name)
{
	macro_name = name;
}

//function displayMacro will tell you what will occur based on the contents
//of the vector named "actions"
Macro::displayMacro()
{
	//Pseudocode
		//for(int i = 0; i < actions.size(); i++)
	  //if(i%2 != 0)
		//translator.toAction(action[i])
	//else
	//"wait " + toString(action[i]);
}

string Macro::getName()
{
	return macro_name;
}

Macro::setName(string set_me)
{
	macro_name = set_me;
}