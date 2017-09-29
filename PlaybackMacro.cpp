#include "PlaybackMacro.h"

void PlaybackMacro::PlaybackMacro(string load_me)
{
	loadMacro(load_me);
}
void PlaybackMacro::actionLoop()
{
	if (NULL == p)
	{return;}

	while (*p)
	{
	printf("%c\xDB", *p++);     // %c , *p++type one char at a time
									//\xDB cursor sim
	::Sleep(60);                // minal secs.
	printf("\b \b");            // cursor blink \b moves cursor one space pback  then space move cirsor back 
	::Sleep(60);
	}
	
	::Sleep(300); 
	//do all of the recorded things.
	//go through the vector, perform actions and sleep for delays

}

void PlaybackMacro::loadMacro(string name)
{
	char start;
	printf("PlayBack:         ");
	cin >> start;

	if (start == 'p' || start == 'P')
	{
		printf("\nBeginning playback\n");
		::Sleep(3000);

		const char* tmp = name.c_str();
		actionLoop(tmp);
	}
	else
	{
		printf("Exiting...");
		::Sleep(3000);
	}
	//SHARED WITH EDITMACRO!!!!
	//look for file named name + ".mcr" in \macros\
	//load and ask user to start (or press start macro button on the GUI when it's a GUI.)
}
