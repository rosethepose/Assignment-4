#include "Window.h"
#include <stddef.h>
using namespace std;
Window::Window()
{
  idleTime = 0;
  inUse = false;
  times = new DLinkedList<int>();
  currentStudent = new Student();
}
Window::Window(int time)
{
  idleTime = time;
  inUse = false;
  times = new DLinkedList<int>();
  currentStudent = new Student();
}
Window::~Window()
{
  delete times;
  delete currentStudent;
}
void Window::openWindow()
{
  currentStudent = NULL; //window no longer holds a student
  inUse = false;
  times->addBack(idleTime); //add the idle time from before the window was in use
  idleTime = 0; //reset idle time
}
