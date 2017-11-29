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
        vector<long> mouseX;
        vector<long> mouseY;

    public:
        vector<string> displayMacro();
        vector<string> mouseInfo(char);
        int actionSize();
        int lastAction();
        void setName(string);
        void clear();
        int mouseSize();
        int longestDelay();
        int matchDelay(int&);
        string getName();
        int getDelayAt(int);
        Macro();
};

#endif // MACRO_H
