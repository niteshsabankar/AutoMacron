#include "stdafx.h"
#include "PlaybackMacro.h"

//PURPOSE: Constructor
//PARAMETER: wstring file name being upload
PlaybackMacro::PlaybackMacro(wstring load_me)
{
	loadMacro(load_me);
}

//PURPOSE: Load the file content in the vectors
//PARAMETER: wstring( name of the file being uploaded
//AlGORITHM: if does not file exist 
//		else countine with the uplaod with for loop
void PlaybackMacro::loadMacro(wstring name)
{
	fstream file;
	file.open(name.c_str());

	if (!file)	//Error file does not exist exit program
	{
		wcout << name << " File not found" << endl;
		exit(1);
	}
	else
	{
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
	}
	file.close();  //Close file
}

//PURPOSE: Play key and mouse actions until no more events
//AlGORITHM: While loop coutines until mouse and key vector has no events
//     if Key delay do as many mouse movements and delays possible within given time
//        else normal key input
//     if Mouse delay do as many key inputs and dealys as possible with goven time 
//        else normal mouse movement
void PlaybackMacro::actionLoop()
{
	//-----------Local variables---------------------------------------------------
	clock_t start, end;
	int timeDif = 0, hold = 0, timeReturn = 0;
	int i = 0, x = 0, howMany = 0;
	bool flag;

	::Sleep(5000);

	while (true)
	{
		if ((i >= actions.size()) && (x >= mouseX.size()))
		{
			break;
		}

		flag = false;
		//Key vector is still has content
		//==============================================================================================
		if (actions.size() > i)
		{
			//This is a key delay
			//------------------------------------------------------------------------------------------
			if ((i % 2) == 0)
			{
				//key delay- will do as many mouse movement as it can within the deley time
				//--------------------------------------------------------------------------------------
				if (mouseX.size() > x) 
				{
					//Next mouse event is a delay, but delay time is bigger than key delay
					//--------------------------------------------------------------------------------
					if ((mouseX[x] >= actions[i]) && ((x % 2) != 0))
					{
						mouseX[x] = mouseX[x] - actions[i];
						actionKey(i, timeDif);
						i++; 
					}
					//-------------Mouse event was a delay that was to big----------------------------

					//Next mouse event is a either delay or event that can be done within given key delay time
					//----------------------------------------------------------------------------------------
					else
					{
						actionMouse(x, timeDif);
						x++;

						//timeDif allows for more events to be done during this key delay
						//------------------------------------------------------------------------------------
						if (timeDif < actions[i])
						{
							hold = actions[i] - timeDif;

							i++;
							timeDif = 0;

							//while loop do as many evenst
							//---------------------------------------------------------------------------------
							while (hold > timeDif)
							{
								start = clock();
								//Still events in the mouse vector
								//--------------------------------------------------------------------------
								if (mouseX.size() > x)
								{
									
									if ((mouseX[x] >= hold) && ((x % 2) != 0)) //
									{
										mouseX[x] = mouseX[x] - timeDif;
										timeReturn = mouseX[x];
										::Sleep(hold);
										x--;
									}
									else
									{
										actionMouse(x, timeReturn);
									}
									x++;
									timeDif += timeReturn;
								}
								//----End of event---------------------------------------------------------

								//No more mouse event
								//--------------------------------------------------------------------------
								else
								{
									end = clock();
									timeDif = timeDif +((int)end - (int)start);
								}
								//----Stay in while loop unitl delay is over-------------------------------
							}
							//---End of while loop ------------------------------------------------------------
						}
						//---------------End of mouse events within given delay--------------------------------
					}
					//------------------End of key delay with X number of mouse events done --------------------
				}
				//----------------------End of key delay with possible mouse movements--------------------------

				//No more mouse movements just key delays
				//-------------------------------------------------------------------------------------
				else
				{
					actionKey(i, timeDif);
					i++;
				}
				//----------------------End of Key delay without mouse movement------------------------		
			}
			//-------End of key delay-------------------------------------------------------------------

			//------------------------------------------------------------------------------------------
			//not a delay do key action
			else
			{
				actionKey(i, timeDif);
				i++;
			}
			//-------End of key action------------------------------------------------------------------
		}
		//End of Key event
		//===============================================================================================

		//Mouse vector still has content
		//===============================================================================================
		if (mouseX.size() > x)
		{
			//This is a mouse delay
			//-------------------------------------------------------------------------------
			if ((x % 2) != 0)
			{
				//mouse delay- will do as many key inputs as it can within the deley time
				//-------------------------------------------------------------------------------
				if (actions.size() > i)
				{
					//Next key event is a delay, but delay time is bigger than mouse delay
					if ((actions[i] >= mouseX[x]) && ((i % 2) == 0))
					{
						actions[i] = actions[i] - mouseX[x];
						actionMouse(x, timeDif);
						x++;
					}

					//Next key event is a either delay or event that can be done within given mouse delay time
					else
					{
						actionKey(i, timeDif);
						i++;

						//timeDif allows for more events to be done during this mouse delay
						if (timeDif < mouseX[x])
						{
							hold = mouseX[x] - timeDif;
							x++;
							timeDif = 0;
							//start of while loop
							//-----------------------------------------------------------------------------
							while (hold >= timeDif)
							{
								start = clock();
								//Still events in the mouse vector
								//--------------------------------------------------------------------------
								if (actions.size() > i)
								{

									if ((actions[i] >= hold) && ((i % 2) == 0)) //
									{
										actions[i] = actions[i] - timeDif;
										timeReturn = actions[i];
										::Sleep(hold);
										i--;
									}
									else
									{
										actionKey(i, timeReturn);
									}
									i++;
									timeDif += timeReturn;
								}
								//----End of event---------------------------------------------------------

								//No more mouse event
								//--------------------------------------------------------------------------
								else
								{
									end = clock();
									timeDif = timeDif + ((int)end - (int)start);
								}
								//----Stay in while loop unitl delay is over-------------------------------
							}
							//---End of while loop ------------------------------------------------------------
						}
					}
				}
				//-------------------------------------------------------------------------------

				//No more mouse movements just key delays
				else
				{
					actionMouse(x, timeDif);
					x++;
				}
			}
			//not a delay do key action
			else
			{
				actionMouse(x, timeDif);
				x++;
			}
		}
		//====================================================================================
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::actionKey(int i, int& timeDif)
{
	INPUT key;
	bool flag = false;
	clock_t start, end;

	start = clock();

	if (i % 2 == 0)
		::Sleep(actions[i]);

	else
	{
		if (actions[i] >= 1000)
			flag = true;

		else
			flag = false;
			
		key.type = INPUT_KEYBOARD;
		key.ki.wScan = 0;
		key.ki.time = 0;
		key.ki.dwExtraInfo = 0;
		key.ki.dwFlags = 0;

		if (flag)
		{
			int x = 0;
			int print = 15;

			while (actions[i] >= 1000)
			{
				actions[i] -= 1000;
				x++;
			}

			key.ki.wVk = actions[i];

			::Sleep(1000);

			while (x >= 0)
			{
				//key.ki.dwFlags = KEYEVENTF_KEYUP;
				while (print >= 0)
				{
					::Sleep(50);
					SendInput(1, &key, sizeof(INPUT));
					print -= 1;
				}
				x--;
			}
		}
		
		else
		{
			key.ki.wVk = actions[i];
			key.ki.dwFlags = 0;
			
			SendInput(1, &key, sizeof(INPUT));
		}
	}

	end = clock();
	timeDif = (int)end - (int)start;
}

//PURPOSE:
//PARAMETER:
//AlGORITHM:
void PlaybackMacro::actionMouse(int i, int& timeDif)
{
	INPUT key;
	POINT positions;
	clock_t start, end;

	start = clock();

	if (i % 2 != 0)
	{
		::Sleep(mouseX[i]);
	}

	else
	{
		key.type = INPUT_MOUSE;
		key.mi.mouseData = 0;
		key.mi.time = 0;
		key.mi.dwExtraInfo = 0;

		positions.x = mouseX[i];
		positions.y = mouseY[i];

		SetCursorPos(positions.x, positions.y);
	}
	end = clock();
	timeDif =(int)end - (int)start;

}
