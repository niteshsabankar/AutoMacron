#ifndef RECORDMACRO_H
#define RECORDMACRO_H

#include "Macro.h"
#include <time.h>
#include <windows.h>


class RecordMacro : public Macro
{
    public:
        RecordMacro();
        RecordMacro(string name);
        void recordMacro(bool, bool, int);
        void saveMacro(string);
        void mousePos(bool, bool, bool, int&, long&);
};

#endif // RECORDMACRO_H

