#ifndef RECORDMACRO_H
#define RECORDMACRO_H

#include "Macro.h"

class RecordMacro : public Macro
{
	public:
		RecordMacro(string);
		void recordMacro(int);
		void mousePos();
		void saveMacro();
		void pause();
		void resume();
};

#endif
