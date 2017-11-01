#ifndef RECORDMACRO_H
#define RECORDMACRO_H

#include "Macro.h"

class RecordMacro : public Macro
{
	public:
		RecordMacro(string);
		void recordMacro(int);
		void saveMacro();
		void mousePos();
		void pause();
		void resume();
};

#endif
