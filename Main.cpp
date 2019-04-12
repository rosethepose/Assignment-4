#include <iostream>
#include <fstream>
#include <string>
#include "Registrar.h"
#include "Student.h"
using namespace std;
int main(int argc, char** argv)
{
  if(argc >= 2)
  {
    string fileName = argv[1];
    ifstream file;
    file.open(fileName, ifstream::in);
    string line;
    if(file.eof())
      cerr << "window read";
    getline(file, line);//number of windows open
    Registrar* reg = new Registrar(stoi(line));
    int clockTime = 0;
    if(file.eof())
      cerr << "first clock tick";
    getline(file, line);
    int nextTick = stoi(line); //first clock tick
    int firstTick = nextTick;
    int totalTime = 0;
    while(true)
    {
      if(!file.eof())
      {
        if(clockTime == nextTick)
        {
          if(file.eof())
            cerr << "num students";
          getline(file, line); //number of students that arrive
          int i = 0;
          int numStudents = stoi(line);
          while(i < numStudents)
          {
            if(file.eof())
              cerr << "time at window";
            getline(file, line); //student time at window
            totalTime += stoi(line);
            reg->add(clockTime, stoi(line));
            cout << "Student Added, Clock Time: " << clockTime << " Time Needed: " << line << endl;
            i++;
          }
          //get next clock tick
          if(!file.eof())
            getline(file, line);
          nextTick = stoi(line);
        }
      }
      reg->updateWindows(clockTime);

      if((clockTime > firstTick || clockTime > totalTime) && reg->isEmpty())
        break;
      clockTime++;
    }
    file.close();
    reg->getIdleTimes();
    cout << "Mean Wait Time: " << reg->meanWaitTime() << endl;
    cout << "Longest Wait Time: " << reg->longestWaitTime() << endl;
    cout << "Students Waiting Over 10 mins: " << reg->studentsWaitingOver10() << endl;
    cout << "Median Wait Time: " << reg->medianWaitTime() << endl;
    cout << "Mean Idle Time: " << reg->meanIdleTime() << endl;
    cout << "Longest Idle Time: " << reg->longestIdleTime() << endl;
    cout << "Windows Idle Over 5 mins: " << reg->windowsIdleOver5() << endl;

  }
  return 0;
}
