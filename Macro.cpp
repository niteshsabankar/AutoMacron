#include "Macro.h"

Macro::Macro()
{

}

//function displayMacro will tell you what will occur based on the contents
//of the vector named "actions"
vector<string> Macro::displayMacro()
{
   vector<string> keys;
   string word;
   ifstream file;

   file.open("C:\\Users\\Jonathan\\Dropbox\\AutoMacronQT\\AutoMacron\\keys.txt");
   if(!file.is_open())
       exit(0);
   while(file >> word)
   {
     keys.push_back(word);

   }

  vector<string> tVec;
  string dummy = "";
  int temp = 0;
  int flag = 0;

  for(int i = 0; i < actions.size(); i++) {
    if(i%2 == 0)
    {
      dummy = "Delay: " + to_string(actions[i]) + "ms";
      tVec.push_back(dummy);
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
    file.close();
  return tVec;

}

int Macro::actionSize()
{
    return actions.size();
}

vector<string> Macro::mouseInfo(char xory)
{
    vector<string> returnMe;

    if(xory == 'x')
    {
        for(int i = 0; i < mouseX.size(); i++)
            returnMe.push_back(to_string(mouseX[i]));
    }
    else if(xory == 'y')
    {
        for(int i = 0; i < mouseY.size(); i++)
            returnMe.push_back(to_string(mouseY[i]));
    }

    return returnMe;
}

int Macro::getDelayAt(int index)
{
    if(index%2 == 0)
        return actions[index];
    else
        return 0;
}

int Macro::longestDelay()
{
    int totalM = 0, totalK = 0;
    for(int i = 0; i < actions.size(); i++)
    {
        if(i%2 == 0)
            totalK += actions[i];
    }
    for(int i = 0; i < mouseX.size(); i++)
    {
        if(i%2 != 0)
            totalM += mouseX[i];
    }
    if(totalM > totalK)
        return totalM;
    else
        return totalK;
}

int Macro::matchDelay(int& index)
{
    int totalDelayK = 0, totalDelayM = 0;
    int temp = index, mouseIndex = 0;
    if(temp%2 == 0)
        temp++;

    for(int i = 0; i < temp; i++)
    {
        if(i%2 == 0)
        {
            totalDelayK += actions[i];
        }
    }


    for(int i = 0; totalDelayM < totalDelayK; i++)
    {
        if(i == mouseX.size() - 1)
            return mouseX.size() - 1;
        if(i % 2 != 0)
            totalDelayM += mouseX[i];

            mouseIndex = i;
    }
    if(mouseIndex % 2 == 0)
        mouseIndex++;

    return mouseIndex;

}

int Macro::mouseSize()
{
    return mouseX.size();
}

void Macro::clear()
{
    actions.clear();
    mouseX.clear();
    mouseY.clear();
}
