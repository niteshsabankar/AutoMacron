#include "PlaybackMacro.h"

//PURPOSE: Constructor
//PARAMETER: wstring file name being upload
PlaybackMacro::PlaybackMacro()
{

}

//PURPOSE: Load the file content in the vectors
//PARAMETER: wstring( name of the file being uploaded
//AlGORITHM: if does not file exist
//		else countine with the uplaod with for loop
void PlaybackMacro::loadMacro(string name)
{
    fstream file;
    file.open(name.c_str());

        //-------Local variables------------------------------------------------------------------------
        string context;      //Holds one content of the file
        string tmp_num;      //Holds one char of the file
        int flag;            //Flag for which vector to input
        int num;             //Convet string input to int

        string::size_type sz;

        while (file >> context)
        {
            if (context == "K")  //Flag one key stroke input
            {
                flag = 1;
                file >> context;
            }

            else if (context == "MX")  //Flag 2 mouse X point
            {
                flag = 2;
                file >> context;
            }

            else if (context == "MY")  //Flag 3 mouse Y point
            {
                flag = 3;
                file >> context;
            }

            //For go throuht each char in the file if char add to context if "," add to vector
            //--------------------------------------------------------------------
            for (int i = 0; i < context.length(); i++)
            {
                if (context[i] != ',')
                    tmp_num += context[i];

                else if (context[i] == ',')
                {
                    num = stoi(tmp_num, &sz);    // number base 16

                    if (flag == 1)
                        actions.push_back(num);

                    else if (flag == 2)
                        mouseX.push_back((long)num);

                    else if (flag == 3)
                        mouseY.push_back((long)num);

                    tmp_num = "\0";   //Restart context
                }
            }
    }
    file.close();  //Close file
}

//PURPOSE: Play key and mouse actions until no more events
//AlGORITHM: While loop coutines until mouse and key vector has no events
//     if Key delay do as many mouse movements and delays possible within given time
//        else normal key input
//     if Mouse delay do as many key inputs and dealys as possible with goven time
//        else normal mouse movement
void PlaybackMacro::actionLoop(int& wait, int loops, int clean)
{

    INPUT key;
    int start,
        numLoops = loops,
        total,
        keyWait,
        mouseWait,
        next,
        actionDelay = 0,
        actionIndex = 0,
        mouseIndex = 2,
        keyHolder = 0;

    key.type = INPUT_KEYBOARD;
    key.ki.wScan = 0;
    key.ki.time = 0;
    key.ki.dwExtraInfo = 0;
    key.ki.dwFlags = 0;

    total = longestDelay() + 5;
    ::Sleep(wait);
    while(numLoops > 0)
    {
        actionIndex = 0;
        mouseIndex = 2;
        keyHolder = 0;
        actionDelay = 0;
        if(!mouseX.empty())
        {
            SetCursorPos(mouseX[0], mouseY[0]);
            mouseWait = mouseX[1];
        }
        start = (int)clock();
        next = (int)clock() + mouseWait;

        while((int)clock() < start + total)
        {
            if(actionIndex % 2 == 0)
            {
                actionDelay = actions[actionIndex];
                keyWait = (int)clock();
                while((int)clock() < keyWait + actionDelay)
                {
                    if((int)clock() == next && mouseIndex < mouseX.size())
                    {
                    SetCursorPos(mouseX[mouseIndex], mouseY[mouseIndex]);
                    mouseIndex++;
                    next = (int)clock() + mouseX[mouseIndex];
                    mouseIndex++;
                    }
                }
            actionIndex++;
            }
            else
            {
                keyHolder = actions[actionIndex];
                if(actions[actionIndex] >= 1000)
                {
                    keyHolder -= 1000;
                    key.ki.wVk = keyHolder;
                    key.ki.dwFlags = KEYEVENTF_KEYUP;
                    actionIndex++;
                }
                else
                {
                    key.ki.wVk = keyHolder;
                    key.ki.dwFlags = 0;
                    actionIndex++;
                }

            SendInput(1, &key, sizeof(INPUT));

            if((int)clock() == next && mouseIndex < mouseX.size())
            {
                 SetCursorPos(mouseX[mouseIndex], mouseY[mouseIndex]);
                 mouseIndex++;
                 next = (int)clock() + mouseX[mouseIndex];
                 mouseIndex++;
            }

        }
     }
     numLoops--;
   }
    return;

}

