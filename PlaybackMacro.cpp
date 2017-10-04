//===============================================================
//NAME: Omar Gonzalez Martinez
//Date: 10/1/17
//Complier:
//File type: PlaybackMarcro implementaion file
//===============================================================
#include "stdafx.h"
#include "PlaybackMacro.h"

//PURPOSE: Constructor initialize
//PARAMETER: wstring varible is the name of the file being loaded
//AlGORITHM: Use LoadMacro() function
PlaybackMacro::PlaybackMacro(wstring load_me)
{
    loadMacro(load_me);
}

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::actionLoop()
{
    int code;
    INPUT key;
    
    reverse(actions.begin(), actions.end());
    ::Sleep(5000);
    
    while (!actions.empty())
    {
        ::Sleep(500)
        code = actions.front();
        actions.pop_back();
        
        key.type = INPUT_KEYBOARD;
        key.ki.wScan = 0;
        key.ki.time = 0;
        key.ki.dwExtraInfo = 0;
        
        key.ki.wVk = code;
        key.ki.dwFlags = 0;
        SendInput(1, &key, sizeof(INPUT));
        
        key.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &key, sizeof(INPUT));
    }
}

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::loadMacro(wstring name)
{
    fstream file;
    file.open(name);
    
    if (!file)
    {
        wcout << name << " File not found" << endl;
        exit(1);
    }
    else
    {
        string context;
        string tmp_hex;
        int num;
        
        file >> context;
        
        for (int i = 0; i < context.length(); i++)
        {
            if (context[i] != ',')
            {
                tmp_hex += context[i];
            }
            else if(context[i] == ',')
            {        
                const char* hex = tmp_hex.c_str();
                num = (int)strtol(hex, NULL, 16);       // number base 16
                
                actions.push_back(num);
                tmp_hex = "\0";
            }
        }
        file.close();
        
        actionLoop();	
    }
}
