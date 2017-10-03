/*Macro implementation file
Includes constructors for Macro class as well as methods*/
#include "Macro.h"

Macro::Macro()
{
	string name = "";
	//ask user for input of name
	cout << "Please enter a name for your Macro: ";
	getline(cin, name);
	//setName("Placeholder");
	setName(name);
}

Macro::Macro(string name)
{
	macro_name = name;
}

//function displayMacro will tell you what will occur based on the contents
//of the vector named "actions"
Macro::displayMacro()
{
	vector<string> tVec;
  string dummy = "";
  int temp = 0;
  int flag = 0;
  //Pseudocode
  for(int i = 0; i < actions.size(); i++) {
    if(i%2 == 0) {
      dummy = "Delay " + to_string(actions[i]) + "ms";
      tVec.push_back(dummy);
      //cout << dummy;
    }
    else {

      temp = actions[i];
  
      if(temp > 1000) {
	flag = 1;
	temp = temp - 1000;
      }
      else
	flag = 0;
      
      switch(temp) {
      case 1 : 
	dummy = "Left Mouse ";
	if(flag == 1)
	  dummy = dummy + "up";
	else 
	  dummy = dummy + "down";
	tVec.push_back(dummy);
	break;
      case 2 :
	dummy = "Right Mouse ";
	if(flag == 1)
	  dummy = dummy + "up";
	else
	  dummy = dummy + "down";
	tVec.push_back(dummy);
	break;
      case 3 :
        dummy = "Control-break processing ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 4 :
        dummy = "Middle Mouse Button ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 5 :
        dummy = "X1 Mouse Button ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 6 :
        dummy = "X2 Mouse Button ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 8 :
        dummy = "Backspace ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 9 :
        dummy = "Tab ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 12 :
        dummy = "Clear ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 13 :
        dummy = "Enter ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 16 :
        dummy = "Shift ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 17 :
        dummy = "Ctrl ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 18 :
        dummy = "Alt ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
	break;
      case 19 :
        dummy = "Pause ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 20 :
        dummy = "Caps Lock ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 27 :
        dummy = "Esc ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 32 :
        dummy = "Spacebar ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
	tVec.push_back(dummy);
        break;
      case 33 :
        dummy = "Page Up ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 34 :
        dummy = "Page Down ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 35 :
        dummy = "End ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 36 :
        dummy = "Home ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 37 :
        dummy = "Left Arrow ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 38 :
        dummy = "Up Arrow ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 39 :
        dummy = "Right Arrow ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 40 :
        dummy = "Down Arrow ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 41 :
        dummy = "Select ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 42 :
        dummy = "Print ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 43 :
        dummy = "Execute ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 44 :
        dummy = "Print Screen ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 45 :
        dummy = "Ins ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 46 :
        dummy = "Del ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 47 :
        dummy = "Help ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 48 :
        dummy = "0 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 49 :
        dummy = "1 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 50 :
        dummy = "2 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 51 :
        dummy = "3 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 52 :
        dummy = "4 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 53 :
        dummy = "5 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 54 :
        dummy = "6 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 55 :
        dummy = "7 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 56 :
        dummy = "8 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 57 :
        dummy = "9 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 65 :
        dummy = "A ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 66 :
        dummy = "B ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 67 :
        dummy = "C ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 68 :
        dummy = "D ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 69 :
        dummy = "E ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 70 :
        dummy = "F ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 71 :
        dummy = "G ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 72 :
        dummy = "H ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 73 :
        dummy = "I ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 74 :
        dummy = "J ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 75 :
        dummy = "K ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 76 :
        dummy = "L ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 77 :
        dummy = "M ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 78 :
        dummy = "N ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 79 :
        dummy = "O ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 80 :
        dummy = "P ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 81 :
        dummy = "Q ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 82 :
        dummy = "R ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 83 :
        dummy = "S ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 84 :
        dummy = "T ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 85 :
        dummy = "U ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 86 :
        dummy = "V ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 87 :
        dummy = "W ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 88 :
        dummy = "X ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 89 :
        dummy = "Y ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 90 :
        dummy = "Z ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 91 :
        dummy = "Left Windows Key ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 92 :
        dummy = "Right Windows Key ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 93 :
        dummy = "Applications Key ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 95 :
        dummy = "Sleep ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 96 :
        dummy = "Num Pad 0 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 97 :
        dummy = "Num Pad 1 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 98 :
        dummy = "Num Pad 2 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 99 :
        dummy = "Num Pad 3 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 100 :
        dummy = "Num Pad 4 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 101 :
        dummy = "Num Pad 5 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 102 :
        dummy = "Num Pad 6 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 103 :
        dummy = "Num Pad 7 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 104 :
        dummy = "Num Pad 8 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 105 :
        dummy = "Num Pad 9 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 106 :
        dummy = "Multiply ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 107 :
        dummy = "Add ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 108 :
        dummy = "Separator ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 109 :
        dummy = "Subtract ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 110 :
        dummy = "Decimal ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 111 :
        dummy = "Divide ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 112 :
        dummy = "F1 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 113 :
        dummy = "F2 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 114 :
        dummy = "F3 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 115 :
        dummy = "F4 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 116 :
        dummy = "F5 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 117 :
        dummy = "F6 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 118 :
        dummy = "F7 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 119 :
        dummy = "F8 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 120 :
        dummy = "F9 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 121 :
        dummy = "F10 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 122 :
        dummy = "F11 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 123 :
        dummy = "F12 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 124 :
        dummy = "F13 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 125 :
        dummy = "F14 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 126 :
        dummy = "F15 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 127 :
        dummy = "F16 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 128 :
        dummy = "F17 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 129 :
        dummy = "F18 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 130 :
        dummy = "F19 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 131 :
        dummy = "F20 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 132 :
        dummy = "F21 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 133 :
        dummy = "F22 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 134 :
        dummy = "F23 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 135 :
        dummy = "F24 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 144 :
        dummy = "Num Lock ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 145 :
        dummy = "Scroll Lock ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 160 :
        dummy = "Left Shift ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 161 :
        dummy = "Right Shift ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 162 :
        dummy = "Left Control ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 163 :
        dummy = "Right Control ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 164 :
        dummy = "Left Menu ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 165 :
        dummy = "Right Menu ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 166 :
        dummy = "Browser Back ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 167 :
        dummy = "Browser Forward ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 168 :
        dummy = "Browser Refresh ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 169 :
        dummy = "Browser Stop ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 170 :
        dummy = "Browser Search ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 171 :
        dummy = "Browser Favorites ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 172 :
        dummy = "Browser Start and Home ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 173 :
        dummy = "Volume Mute ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 174 :
        dummy = "Volume Down ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 175 :
        dummy = "Volume Up ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 176 :
        dummy = "Next Track ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 177 :
        dummy = "Previous Track ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 178 :
        dummy = "Stop Media ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 179 :
        dummy = "Play/Pause Media ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 180 :
        dummy = "Start Mail ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 181 :
        dummy = "Select Media ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 182 :
        dummy = "Start Application 1 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 183 :
        dummy = "Start Application 2 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 186 :
        dummy = "; ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 187 :
        dummy = "+ ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 188 :
        dummy = ", ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 189 :
        dummy = "- ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 190 :
        dummy = ". ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 191 :
        dummy = "/ ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 192 :
        dummy = "` ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 219 :
        dummy = "[ ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 220 :
        dummy = "\ ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 221 :
        dummy = "] ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 222 :
        dummy = "' ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 246 :
        dummy = "Attn ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 247 :
        dummy = "CrSel ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 248 :
        dummy = "ExSel ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 249 :
        dummy = "Erase EOF ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 250 :
        dummy = "Play ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break; 
      case 251 :
        dummy = "Zoom ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 253 :
        dummy = "PA1 ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      case 254 :
        dummy = "Clear ";
        if(flag == 1)
          dummy = dummy + "up";
        else
          dummy = dummy + "down";
        tVec.push_back(dummy);
        break;
      }
    }
  }
  for(int j = 0; j < tVec.size(); j++) {
    cout << "*****Macro Contents******" << endl;
    cout << "Index " << to_string(j) << ": " << tVec[j] << endl;
  }

}

string Macro::getName()
{
	return macro_name;
}

Macro::setName(string set_me)
{
	macro_name = set_me;
}
