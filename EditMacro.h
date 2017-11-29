#ifndef EDITMACRO_H
#define EDITMACRO_H

#include <Macro.h>
#include <windows.h>
#include <time.h>
#include <cstdio>
#include <iostream>
#include <conio.h>
using namespace std;

class EditMacro : public Macro
{
        public:
                EditMacro();
                void saveMacro(string);
                void loadMacro(string);
                void recordSingle(bool, int);
                void recordMacro(bool, bool, int, int, int);
                void removeAction(int&);
                void changeDelay(int&, int&);
                void mousePos(bool, bool, bool, vector<int>, int&);
};

#endif
