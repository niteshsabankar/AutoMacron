#include "MacroInterface.h"
#include "stdafx.h"

using namespace std;


void baseInterface()
{
	int selection = 0;
	while (selection != 4)
	{
		/*GetWindowRect(console, &console_size);
		MoveWindow(console, console_size.left, console_size.top, 800, 300, TRUE);*/

		wstring mac_name = L"\\macros\\";
		wstring path_holder;
		vector<wstring> mac_list;

		HANDLE hFind;
		WIN32_FIND_DATA data;
		wchar_t buff[FILENAME_MAX];
		GetCurrentDirectory(FILENAME_MAX, buff);
		wstring file_name = wstring(buff);
		file_name += L"\\macros\\*.mcr";

		for (unsigned int i = 0; i < file_name.length(); i++)
		{
			buff[i] = file_name[i];
			if (i == file_name.size() - 1)
				buff[i + 1] = L'\0';
		}
		hFind = FindFirstFile(buff, &data);
		if (hFind != INVALID_HANDLE_VALUE) {
			do
			{
				mac_list.push_back(wstring(buff));
			} while (FindNextFile(hFind, &data));
			FindClose(hFind);

		}
		cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXX AUTOMACRON 1.0 XXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
			<< "X Welcome to AutoMacron, a Windows automation software solution.     X\n"
			<< "X Please choose desired action from the list below                   X\n"
			<< "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
			<< "	1. Record a macro\n"
			<< "   2. Run an existing macro.\n"
			<< "	3. Edit an existing macro or create a new macro from scratch.\n"
			<< "	4. Exit\n"
			<< "______________________________________________________________________\n"
			<< ">";
		cin >> selection;
		while (selection < 1 || selection > 4)
		{
			switch (selection)
			{
			case 1:

				for (int i = 0; i < 9; i++)
					cout << "\n";

				cout << "Please enter a name for this macro. adding .mcr is not advised\n";
				wcin >> path_holder;
				mac_name += path_holder;
				recordInterface(mac_name);
				break;

			case 2:

				for (int i = 0; i < 9; i++)
					cout << "\n";
				cout << "Please select a macro to open\n";
				for (int i = 0; i < mac_list.size(); i++)
					wcout << mac_list[i] << endl;
				wcin >> path_holder;
				mac_name += path_holder;
				playbackInterface(mac_name);

				break;

			case 3:
				/*
				for (int i = 0; i < 9; i++)
					cout << "\n";
				cout << "Please select a macro to open or type newmac to create a new one using the editor\n";
				for (int i = 0; i < mac_list.size(); i++)
					wcout << mac_list[i] << endl;
				cin >> mac_name;
				if (mac_name.substr(mac_name.size() - 4, 4) != L".mcr" && mac_name != L"newmac")
					mac_name += L".mcr";

				editInterface(mac_name);
			*/ cout << "edit macro is currently in development, please reselect\n";
			case 4:
				system("EXIT");
				break;

			default:


				cout << "Not a valid entry, please re-enter\n"
				    << "	1. Record a macro\n"
					<< "   2. Run an existing macro.\n"
					<< "	3. Edit an existing macro or create a new macro from scratch.\n"
					<< "	4. Exit\n";

				cin >> selection;
			}
		}
	}

}


void editInterface(wstring e_macro_name)
{
	/*if (e_macro_name == L"newmac")
		edit_me = new EditMacro();
	else
		edit_me = new EditMacro(e_macro_name);

	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX EDIT XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		 << "Please select from the options below\n"
		 << "1. Record multiple actions with delays\n"
		 << "2. Record multiple actions without delays\n"
		 << "3. Record a single action with delays\n"
		 << "4. Record a single action without delays\n"
		 << "5. Display current macro\n"
		 << "6. Save and return to main menu\n"
		 << "7. Return to main menu without saving.\n"
		 << ">";
		 */
}

void playbackInterface(wstring p_macro_name )
{
	int playSelect;
	play_me = new PlaybackMacro(p_macro_name);
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX PLAYBACK XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		 << "Please select from the options below\n"
		 << "1. Begin playback\n"
		 << "2. Display macro\n"
		 << "3. Return to main menu\n\n\n\n"
		 << "______________________________________________________________________\n"
		 << ">";
	cin >> playSelect;
	while (playSelect < 1 || playSelect > 3)
	{
		switch (playSelect)
		{
		case 1:
			play_me->actionLoop();
			break;
		case 2:
			play_me->displayMacro();
			break;
		case 3:
			delete play_me;
			play_me = NULL;
			return;
		
		default:

			cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX PLAYBACK XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
				<< "Invalid entry. Please select from the options below\n"
				<< "1. Begin playback\n"
				<< "2. Display macro\n"
				<< "3. Return to main menu\n\n\n\n"
				<< "______________________________________________________________________\n"
				<< ">";
			cin >> playSelect;
		}
	}
}			

void recordInterface(wstring r_macro_name)
{
	int recSelect;
	record_me = new RecordMacro(r_macro_name);
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX RECORD XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		 << "Please select from the options below\n"
		 << "1. Record macro with delays\n"
		 << "2. Record macro without delays"
		 << "3. Display recorded macro\n"
		 << "4. Exit and save\n"
		 << "5. Exit and do not save\n\n"
		 << "______________________________________________________________________\n"
		 << ">";

	cin >> recSelect;
	switch (recSelect)
	{
		while (recSelect < 1 || recSelect > 5 || recSelect == 3)
		{
			case 1:
				record_me->recordMacro(1);
				break;
			case 2:
				record_me->recordMacro(2);
				break;
			case 3:
				if (!record_me->isEmpty())
				{
					record_me->displayMacro();
				}
				else
				{
					cout << "Nothing here!\n";
				}
				break;
			case 4:
				record_me->saveMacro();
				delete record_me;
				record_me = NULL;
				return;
			case 5:
				delete record_me;
				record_me = NULL;
				return;
			default:
				break;
		}
	}
}
