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
   vector<string> keys;
	
   ifstream file;
   file.open("keys.txt");
   if(!file.is_open()) return;
   while(file >> word)
   {
     keys.push_back(word);
   }

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
       
      if(flag == 1) 
	dummy = keys[temp-1] + " up";   //-1 because vec keys starts at index 0, not 1
      else 
        dummy = keys[temp-1] + " down";

      tVec.push_back(dummy); 
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
