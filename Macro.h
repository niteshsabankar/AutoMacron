#ifndef MACRO_H
#define MACRO_H

#include <vector>

using namespace std;

class Macro
{
	protected:
		vector<int> actions;
		string macro_name;

	public:
		void displayMacro();
		void setName();
};



#endif
