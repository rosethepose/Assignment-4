#ifndef REGISTRAR_H
#define REGISTRAR_H
#include "Window.h"
#include "Student.h"
#include "GenQueue.cpp"
using namespace std;
class Registrar
{
public:
  Registrar();
  Registrar(int num);
  void add(int arrival, int needed);
  ~Registrar();
  Window* getWindow();
  bool isEmpty();
  void openWindow(int index, int clockTime);
  void updateWindows(int clockTime);
  void getIdleTimes();
  double meanWaitTime();
  int medianWaitTime();
  int longestWaitTime();
  int studentsWaitingOver10();
  double meanIdleTime();
  int longestIdleTime();
  int windowsIdleOver5();
  int getMin(DLinkedList<int>* list);
  int getMax(DLinkedList<int>* list);

  int numWindows;
  GenQueue<Student>* students;
  Window** windows;
  DLinkedList<int>* waitTimes;
  DLinkedList<int>* idleTimes;
};
#endif
