#ifndef RECORDMACRO_H
#define RECORDMACRO_H

#include "Macro.h"

class RecordMacro : public Macro
{
	public:
		RecordMacro(wstring name);
		void recordMacro(bool noMouse, bool noKey);
		void saveMacro();
		void mousePos(bool tic, bool noKey, bool noMouse, vector <int> actions, int& index);
};

#endif
