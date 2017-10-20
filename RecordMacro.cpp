#include "RecordMacro.h"

RecordMacro::RecordMacro(string name)
{
	//interface will ask user for the name.
	macro_name = name + ".mcr";
}

vector<int> RecordMacro::recordMacro(int mode)
{
///////////////////////////////////////////////////////////Keyboard/////////////////////////////////////////////////////////////////////	
	bool flags[256];				//Flag for every key
	int delay = 0;					//Time delay between key events
	clock_t timer = clock();			//
	clock_t timer2 = clock();			//
	//int i=0;					//If you want no delay before first press
	
	for (int i = 0; i < 255; i++)			//Set all flags to false
	{
		flags[i] = false;
	}
	
	if(mode==1)					//With Delays
	{	
		while (!flags[VK_SCROLL])								//Keep going until scroll key is pressed
		{		
			for (int key = 8; key <= 255; key++)
			{
		
				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
					{	
					flags[key] = true;
					timer = clock();
					//if(i==0)
					//{
					//delay= 0;							//If you want no delay before first press
					//}	
					//else
					delay = (int)((timer-timer2) / (CLOCKS_PER_SEC / 1000));
					//i++;	
					timer2 = clock();
					actions.push_back(delay);
					actions.push_back(key);
					cout << delay <<"\t"<< key << endl;
			
					}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
					{
					timer = clock();
					delay = (int)((timer-timer2) / (CLOCKS_PER_SEC / 1000));
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << delay <<"\t"<< key+1000 << endl;
					timer2 = clock();
					}
			}	
		}
	}
	else if(mode==2)	//No Delays
	{
		while (!flags[VK_SCROLL])								//Keep going until scroll key is pressed
		{		
			for (int key = 8; key <= 255; key++)
			{
		
				if (GetAsyncKeyState(key) == -32767 && flags[key] == false)		//If the key is pressed down and hasn't been flagged
					{	
					flags[key] = true;
					actions.push_back(delay);
					actions.push_back(key);
					cout << delay <<"\t"<< key << endl;
			
					}
				else if (GetAsyncKeyState(key) == 0 && flags[key] == true)		//If the key is released after being flagged 
					{
					actions.push_back(delay);
					actions.push_back(key + 1000);
					flags[key] = false;
					cout << delay <<"\t"<< key+1000 << endl;
					}
			}	
		}	
	}
	else
		return 0;
///////////////////////////////////////////////////////////////Mouse/////////////////////////////////////////////////////////////////////
	
	//NOTE: this code section is to be shared with the EditMacro file
	//loop until scroll lock is hit VK_SCROLL/0x91
	//if mode is 1, delays are recorded
	//if mode is 2, delays are not recorded
	//basically while it's waiting between keys, it will count the milliseconds
	//with a native time function. once a key is pressed, it will record the delay
	//and append it to the vector with push_back along with the new event;
	//if in mode 2, push a 0 between each event into the vector.
}

RecordMacro::saveMacro()
{
	vector<char>hex;
	long int remainder, quotient;
	int temp;

	ofstream outputFile;
	outputFile.open("macro_name ");

	for (int i = 0; i < actions.size(); i++)
	{
		quotient = actions[i];

		while (quotient != 0)
		{
			temp = quotient % 16;

			if (temp < 10)
				temp = temp + 48;
			else
				temp = temp + 55;
				hex.insert(hex.begin(), temp);
				quotient = quotient / 16;
		}
		for (int i = 0; i <hex.size(); i++)
		{
			outputFile << hex[i];
		}
		outputFile << " ";
		hex.clear();
	}
	outputFile.close();
	
	//SHARED CODE FROM EDITMACRO
	////open a file named \macros\macro_name in write mode
	//for(int i =0; i < actions.size(); i++)
	//file << actions[i]
	//file << ',' or ' ';
}

RecordMacro::pause()
{
	
}

RecordMacro::resume()
{
	
}
