#ifndef WINDOW_H
#define WINDOW_H
#include "Student.h"
#include "DLinkedList.cpp"
using namespace std;
class Window
{
public:
  Window();
  Window(int time);
  ~Window();
  void openWindow(); //for when the student leaves and we reopen the window
  int idleTime;
  bool inUse;
  DLinkedList<int>* times;
  Student* currentStudent;
};
#endif
