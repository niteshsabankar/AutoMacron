#include "RecordMacro.h"

RecordMacro::RecordMacro()
{

}


void RecordMacro::recordMacro(bool delays, bool positions, int clean)
{
    bool flags[256];				//Flag for every key
    bool tic = false;				//Flag to check if MousePos happened in clock tick
    long mdelay = 0;
    int delay = 0;					//Time delay between key events
    int index =0;					//Holds last mouse click if no delays
    clock_t timer = clock();			//Timer to record delays
    clock_t timer2 = clock();			//Timer to record delays

for (int i = 0; i < 255; i++)	//Set all flags to false
{
    flags[i] = false;
}
//////////////////////////////////////////////////////MOUSE POS////////////////////////////////////////////////////////////////////////
    while (true)				//Keep going until PgUp key is pressed
    {
        if(!delays)				//Not recording key delays don't check mouse positions
        { }
        else						//Record mouse position
        {
            if (positions)   		//Record mouse movement
            {
                if (clock() % 20 == 0)
                {
                    if (tic == false)	//flag is set ignore
                    {
                        mousePos(tic, delays, positions, index, mdelay);
                        tic = true;
                    }
                    else {}			//Already checked this tic
                }
                else
                {
                    tic = false;		//Reset flag to record in next tic
                }
            }
            else {}					//Don't record mouse movement
        }
//////////////////////////////////////////////////////ACTIONS/////////////////////////////////////////////////////////////////////////
        for (int key = 1; key <= 255; key++)
        {
//////////////////////////////////////////////////////KEY  DOWN///////////////////////////////////////////////////////////////////////
            if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
            {
                flags[key] = true;
                    if(flags[VK_SCROLL] || flags[VK_PRIOR])
                        return;

                    else
                        timer = clock();
                if (!delays)
                {
                    delay = 2;
                }
                else
                {
                    delay = (int)(timer - timer2);
                }
                timer2 = clock();
                actions.push_back(delay);
                actions.push_back(key);

                if (key < 3  && key > 0 && !delays)               //If Left Click or Right Click are the input and no delays are wanted
                {
                    mousePos(tic, delays, positions, index, mdelay);
                }
            }
////////////////////////////////////////////////////////KEY UP////////////////////////////////////////////////////////////////////////
            else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged
            {
                timer = clock();
                if (!delays)
                {
                    delay = 2;
                }
                else
                {
                    delay = (int)(timer - timer2);
                }
                actions.push_back(delay);
                actions.push_back(key + 1000);
                flags[key] = false;
                timer2 = clock();
            }
        }
    }


}

void RecordMacro::saveMacro(string fileName)
{
    ofstream outputFile;
    outputFile.open(fileName.c_str());
    outputFile << "K\n";

    for (int i = 0; i < actions.size(); i++)
    {
        outputFile << actions[i] << ",";
    }

    outputFile << endl;
    outputFile << "MX\n";

    for (int i = 0; i < mouseX.size(); i++)
    {
        outputFile << mouseX[i] << ",";
    }
    outputFile << endl;
    outputFile << "MY\n";
    for (int i = 0; i < mouseY.size(); i++)
    {
        outputFile << mouseY[i] << ",";
    }
    outputFile << endl;

    outputFile.close();
}

void RecordMacro::mousePos(bool tic, bool delays, bool positions, int& index, long& mdlay)
{
    POINT point;


        GetCursorPos(&point);
        if (!delays)    //Change mouse position delays to when click occurs
        {
            long delay = actions.size() - index;
            mouseX.push_back(delay);
            mouseX.push_back(point.x);
            mouseY.push_back(delay);
            mouseY.push_back(point.y);
            index = actions.size() - 1;
        }
        else if (delays) //Record normally
        {
            if (mouseX.empty() || point.x != mouseX[mouseX.size() - 2] || point.y != mouseY[mouseY.size() - 2])
            {
                mdlay += 20;
                mouseX.push_back(point.x);
                mouseX.push_back(mdlay);
                mouseY.push_back(point.y);
                mouseY.push_back(mdlay);
                mdlay = 0;
            }
            else
            {
                mdlay += 20;
            }
        }
}
