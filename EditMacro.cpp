#include "EditMacro.h"

EditMacro::EditMacro()
{
}

void EditMacro::saveMacro(string fileName)
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

void EditMacro::loadMacro(string file_name)
{
    ifstream file;
    file.open(file_name.c_str());
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

void EditMacro::changeDelay(int& vectIndex, int& newValue)
{
    actions[vectIndex] = newValue;
}

void EditMacro::removeAction(int& vectIndex)
{
    std::vector<int>::const_iterator i = actions.begin() + vectIndex;
    if(vectIndex % 2 == 0)
    {
        actions.erase(i);
        actions.erase(i);
    }
    else
    {
        actions.erase(i);
        actions.erase(i-1);
    }
}
void EditMacro::recordMacro(bool delays, bool positions, int vectIndex, int mvectIndex, int clean)
{
    bool flags[256];				//Flag for every key
    bool tic = false;				//Flag to check if MousePos happened in clock tick
    int delay = 0;					//Time delay between key events
    int index = 0;					//Holds last mouse click if no delays
    vector<int> tempActions;
    vector<long> tempMousex, tempMousey;
    clock_t timer = clock();			//Timer to record delays
    clock_t timer2 = clock();			//Timer to record delays

    for (int i = 0; i < 255; i++)	//Set all flags to false
    {
        flags[i] = false;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copy vector items after given vector index in a temporary vector.
    if(vectIndex < actions.size() -1)
    {
        for (std::vector<int>::const_iterator i = actions.begin() + vectIndex; i != actions.end(); ++i)
            tempActions.push_back(*i);

        actions.resize(vectIndex);
    }
    if(mvectIndex < mouseX.size() - 1)
    {
        for (std::vector<long>::const_iterator i = mouseX.begin() + mvectIndex; i != mouseX.end(); ++i)
            tempMousex.push_back(*i);

            mouseX.resize(mvectIndex);

        for (std::vector<long>::const_iterator i = mouseY.begin() + mvectIndex; i != mouseY.end(); ++i)
            tempMousey.push_back(*i);

            mouseY.resize(mvectIndex);
    }

//////////////////////////////////////////////////////MOUSE POS///////////////////////////////////////////////////////////////
    while (true)				//Keep going until PgUp key is pressed
    {
        if (!delays)				//Not recording key delays don't check mouse positions
        {
        }
        else						//Record mouse position
        {
            if (positions)   		//Record mouse movement
            {
                if (clock() % 20 == 0)
                {
                    if (tic == false)	//flag is set ignore
                    {
                        mousePos(tic, delays, positions, actions, index);
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
                if(flags[VK_PRIOR] || flags[VK_SCROLL])
                {
                    return;
                }
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
                if (key == 1 && !delays)               //If Left Click or Right Click are the input and no delays are wanted
                {
                    mousePos(tic, delays, positions, actions, index);							// Need to change vectIndex
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// push back temporary vector data into main vector
    if(vectIndex < actions.size() -1)
    {
        for (std::vector<int>::const_iterator i = tempActions.begin(); i != tempActions.end(); ++i)
            actions.push_back(*i);

        tempActions.clear(); // clear temporary vector
    }
    if(mvectIndex < mouseX.size() - 1)
    {
        for (std::vector<long>::const_iterator i = tempMousex.begin(); i != tempMousex.end(); ++i)
            mouseX.push_back(*i);

        tempMousex.clear();

        for (std::vector<long>::const_iterator i = tempMousey.begin(); i != tempMousey.end(); ++i)
            mouseY.push_back(*i);

        tempMousey.clear();
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void EditMacro::mousePos(bool tic, bool delays, bool positions, vector <int> actions, int& index)
{
    POINT point;
    long delay = 0;


    GetCursorPos(&point);
    if (!delays)    //Change mouse position delays to when click occurs
    {
        delay = actions.size() - index;
        mouseX.push_back(point.x);
        mouseX.push_back(delay);
        mouseY.push_back(point.y);
        mouseY.push_back(delay);

        index = actions.size();
    }
    else if (delays) //Record normally
    {
        if (mouseX.empty() || point.x != mouseX[mouseX.size() - 2])
        {
            delay += 20;
            mouseX.push_back(point.x);
            mouseX.push_back(delay);
            mouseY.push_back(point.y);
            mouseY.push_back(delay);

            delay = 0;
        }
        else
        {
            delay += 20;
        }
    }
}


void EditMacro::recordSingle(bool delays, int vectIndex)
{
    //record a single key down key up. append to actions vector
    //mode determines delays just as above.
    //reuires 3 argument: mode, delay, and vectorIndex where action to be inserted
    bool flags[256];					//Flag for every key
    int delay = 0;
    int time1 = (int)clock(), time2 = (int)clock();

    for (int i = 0; i < 255; i++)			//Set all flags to false
    {
        flags[i] = false;
    }

    {
        while (true)							//Wait for single keystroke, requires <conio.h>
        {
                for (int key = 0; key <= 255; key++)
                {

                    if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
                    {
                        flags[key] = true;
                        if (!delays)                                                  //Record without delays
                        {
                            delay = 2;
                        }
                        else
                        {
                            time2 = (int)clock();
                            delay = time2 - time1;
                        }
                        actions.insert(actions.begin() + vectIndex, delay);
                        vectIndex++;
                        actions.insert(actions.begin() + vectIndex, key);
                        vectIndex++;


                    }
                    else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged
                    {
                        if (!delays)
                        {
                            delay = 2;
                        }
                        else
                        {
                            time1 = (int)clock();
                            delay = time1 - time2;
                        }
                        actions.insert(actions.begin() + vectIndex, delay);
                        vectIndex++;
                        actions.insert(actions.begin() + vectIndex, key + 1000);
                        vectIndex++;
                        flags[key] = false;
                        return;
                    }
                }
            }
        }

}


