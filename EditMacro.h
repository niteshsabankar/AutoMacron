#ifndef EDITMACRO_H
#define EDITMACRO_H

#include <Macro.h>

class EditMacro : public Macro
{
	public:
		vector<int> saveMacro();
		void loadMacro(string);
		void recordSingle();
		void record();
};