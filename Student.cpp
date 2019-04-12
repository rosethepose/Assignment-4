#include "Student.h"
using namespace std;
Student::Student()
{
  waitTime = 0;
  timeAtWindow = 0;
}
Student::Student(int arrival, int needed)
{
  waitTime = 0;
  timeAtWindow = 0;
  arrivalTime = arrival;
  timeNeeded = needed;
}
Student::Student(const Student& other)
{
  waitTime = 0;
  timeAtWindow = 0;
  arrivalTime = other.arrivalTime;
  timeNeeded = other.timeNeeded;
}
Student::~Student() {}
