#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
class Student
{
public:
  Student();
  Student(int arrival, int needed);
  Student(const Student& other);
  ~Student();
  int timeAtWindow;
  int waitTime;
  int arrivalTime;
  int timeNeeded;
};
#endif
