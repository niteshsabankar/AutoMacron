#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//base macro class to be used by the others.
class Macro
{
	protected:
		vector<int> actions;
		string macro_name;

	public:
		void displayMacro();
		void setName(string);
		string getName();
		Macro();
		Macro(string);
};



#endif
