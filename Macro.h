#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct MousePos 
{
	POINT position; 
	int mdelay;
};
//base macro class to be used by the others.
class Macro
{
	protected:
		vector<int> actions;
		vector<long> mousex;
		vector<long> mousey;
		string macro_name;
		vector<MousePos> mActions;

	public:
		void displayMacro();
		void setName(string);
		string getName();
		Macro();
		Macro(string);
};



#endif
