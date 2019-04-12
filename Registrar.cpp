#include "Registrar.h"
#include "Student.h"
#include "Window.h"
#include <stddef.h>
#include <iostream>
using namespace std;
Registrar::Registrar()
{
  windows = new Window*[10];
  for(int i = 0; i < 10; i++)
    windows[i] = new Window();
  students = new GenQueue<Student>();
  numWindows = 10;
  waitTimes = new DLinkedList<int>();
  idleTimes = new DLinkedList<int>();
}
Registrar::Registrar(int num)
{
  windows = new Window*[num];
  for(int i = 0; i < num; i++)
    windows[i] = new Window();
  students = new GenQueue<Student>();
  numWindows = num;
  waitTimes = new DLinkedList<int>();
  idleTimes = new DLinkedList<int>();
}
Registrar::~Registrar()
{
  delete students;
  delete[] windows;
  delete waitTimes;
  delete idleTimes;
}
void Registrar::add(int arrival, int needed)
{
  students->enqueue(Student(arrival, needed)); //add student to list
  Window* w = getWindow(); //get first availble Window
  if(w != NULL)
  {
    w->inUse = true;
    w->currentStudent = new Student(students->dequeue());
    waitTimes->addFront(0); //student didnt need to wait
    if(w->idleTime != 0)
    {
      idleTimes->addFront(w->idleTime);
      w->idleTime = 0; //reset idle time
    }
  }
}
void Registrar::updateWindows(int clockTime)  //go thru all windows, if in use, update times, if idle, update idle time
{
  for(int i = 0; i < numWindows; ++i)
  {
    if(windows[i]->inUse)
    {
      Student* s = windows[i]->currentStudent;
      s->timeAtWindow++;
      if(s->timeAtWindow == s->timeNeeded) //if student's time at window is over
        openWindow(i, clockTime); //reopen the window for new student
    }
    else//window is idle
      windows[i]->idleTime++;
  }
}
Window* Registrar::getWindow() //get first avialble window to add a student
{
  int index = 0;
  while(index < numWindows && windows[index]->inUse)
    index++;
  if(index >= numWindows)
    return NULL; //null if no available window
  return windows[index];
}
void Registrar::openWindow(int index, int clockTime)
{
  windows[index]->openWindow(); //free up a window
  if(!students->isEmpty()) //if students still in line, put them on
  {
    windows[index]->currentStudent = new Student(students->dequeue());
    windows[index]->inUse = true;
    windows[index]->currentStudent->waitTime = clockTime - windows[index]->currentStudent->arrivalTime + 1;
    idleTimes->addFront(windows[index]->idleTime);
    windows[index]->idleTime = 0; //reset idle time
    waitTimes->addFront(windows[index]->currentStudent->waitTime);
  }
}
bool Registrar::isEmpty()
{
  for(int i = 0; i < numWindows; i++)
    if(windows[i]->inUse)
      return false;
  return true;
}
void Registrar::getIdleTimes()
{
  for(int i = 0; i < numWindows; ++i)
    if(windows[i]->idleTime > 0)
      idleTimes->addFront(windows[i]->idleTime);
}
double Registrar::meanWaitTime()
{
  int sum = 0;
  DListNode<int>* cursor = waitTimes->front;
  while(cursor != NULL)
  {
    sum += cursor->data;
    cursor = cursor->next;
  }
  return (double)sum / waitTimes->getSize();
}
int Registrar::medianWaitTime()
{
  DListNode<int>* cursor = waitTimes->front;
  for(int i = 0; i < waitTimes->getSize()/2; i++)
    cursor = cursor->next;
  return cursor->data;
}
int Registrar::getMin(DLinkedList<int>* list)
{
  int min = list->front->data;
  DListNode<int>* cursor = list->front;
  while(cursor != NULL)
  {
    if(min > cursor->data)
      min = cursor->data;
    cursor = cursor->next;
  }
  return min;
}
int Registrar::getMax(DLinkedList<int>* list)
{
  int max = list->front->data;
  DListNode<int>* cursor = list->front;
  while(cursor != NULL)
  {
    if(max < cursor->data)
      max = cursor->data;
    cursor = cursor->next;
  }
  return max;
}
int Registrar::longestWaitTime()
{
  getMax(waitTimes);
}
int Registrar::studentsWaitingOver10()
{
  int count = 0;
  DListNode<int>* cursor = waitTimes->front;
  while(cursor != NULL)
  {
    if(cursor->data > 10)
      count++;
    cursor = cursor->next;
  }
  return count;
}
double Registrar::meanIdleTime()
{
  int sum = 0;
  DListNode<int>* cursor = idleTimes->front;
  while(cursor != NULL)
  {
    sum += cursor->data;
    cursor = cursor->next;
  }
  return (double)sum / idleTimes->getSize();
}
int Registrar::longestIdleTime()
{
  getMax(idleTimes);
}
int Registrar::windowsIdleOver5()
{
  int count = 0;
  DListNode<int>* cursor = idleTimes->front;
  while(cursor != NULL)
  {
    if(cursor->data > 10)
      count++;
    cursor = cursor->next;
  }
  return count;
}
