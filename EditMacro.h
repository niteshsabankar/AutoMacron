#ifndef EDITMACRO_H
#define EDITMACRO_H

#include <Macro.h>

class EditMacro : public Macro
{
	public:
		void saveMacro();
		void loadMacro(string);
		void recordSingle(int);
		void record(int);
		void pause();
		void resume();
		
};
