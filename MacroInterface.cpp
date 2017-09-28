#include "MacroInterface.h"




void baseInterface()
{
	int selection = 0;
	while (selection != 4)
	{
		GetWindowRect(console, &console_size);
		MoveWindow(console, console_size.left, console_size.top, 800, 300, TRUE);

		wstring mac_name;
		vector<wstring> mac_list;

		HANDLE hFind;
		WIN32_FIND_DATA data;
		wchar_t buff[FILENAME_MAX];
		GetCurrentDirectory(FILENAME_MAX, buff);
		wstring file_name = wstring(buff);
		file_name += L"\\macros\\*.mcr";

		for (unsigned int i = 0; i < fileName.size(); i++)
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
			 << "    2. Run an existing macro.\n"
			 << "	3. Edit an existing macro or create a new macro from scratch.\n"
			 << "	4. Exit\n"
			 << "______________________________________________________________________\n"
			 << ">";
		cin >> selection;
		switch (selection)
		{
		case 1:
			
			for (int i = 0; i < 9; i++)
				cout << "\n";

			cout << "Please enter a name for this macro.\n";
			cin >> mac_name;
			mac_name += L".mcr"
				recordInterface(mac_name);
			break;
		
		case 2:
			
			for (int i = 0; i < 9; i++)
				cout << "\n";
			cout << "Please select a macro to open\n";
			for (int i = 0; i < mac_list.size(); i++)
				wcout << mac_list[i] << endl;
			cin >> mac_name;
			if (mac_name.substr(mac_name.size() - 4, 4) != L".mcr")
				mac_name += L".mcr";
			playbackInterface(mac_name);
			break;
		
		case 3:
			
			for (int i = 0; i < 9; i++)
				cout << "\n";
			cout << "Please select a macro to open or type newmac to create a new one using the editor\n";
			for (int i = 0; i < mac_list.size(); i++)
				wcout << mac_list[i] << endl;
			cin >> mac_name;
			if (mac_name.substr(mac_name.size() - 4, 4) != L".mcr" && mac_name != L"newmac")
				mac_name += L".mcr";
			
			editInterface(mac_name);
		
		case 4:
			system("EXIT");
			break;
		
		default:
				cout << "Not a valid entry, please re-enter\n";
					 << "	1. Record a macro\n"
					 << "   2. Run an existing macro.\n"
					 << "	3. Edit an existing macro or create a new macro from scratch.\n"
					 << "	4. Exit\n";
					 
				cin >> selection;

		}
	}

}

void editInterface(wstring e_macro_name)
{
	if (e_macro_name == L"newmac")
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
}

void playbackInterface(wstring p_macro_name )
{
	play_me = new PlaybackMacro(p_macro_name);
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX PLAYBACK XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		 << "Please select from the options below\n"
		 << "1. Begin playback\n"
		 << "2. Display macro\n"
		 << "3. Return to main menu\n\n\n\n"
		 << "______________________________________________________________________\n"
		 << ">";
}

void recordInterface(wstring r_macro_name)
{
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
}