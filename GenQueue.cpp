#ifndef GENQUEUE_CPP
#define GENQUEUE_CPP
#include <iostream>
#include "DLinkedList.cpp"
using namespace std;
template <class E>
class GenQueue
{
public:
  GenQueue();
  GenQueue(GenQueue<E>* other);
  ~GenQueue();
  void enqueue(E e);
  E dequeue();
  E front();
  bool isEmpty();
  int getSize();
private:
  DLinkedList<E>* myQueue;                                                      //doubly linked list holding queue values
};
template <class E>
GenQueue<E>::GenQueue()
{
  myQueue = new DLinkedList<E>();
}
template <class E>
GenQueue<E>::GenQueue(GenQueue<E>* other)
{
  myQueue = new DLinkedList<E>();
  while(!other->isEmpty())
    myQueue->addBack(other->dequeue());
}
template <class E>
GenQueue<E>::~GenQueue()
{
  delete myQueue;                                                               //myQueue is dynamically allocated, so we delete
}
template <class E>
void GenQueue<E>::enqueue(E e)
{
  myQueue->addBack(e);                                                          //since queue is FIFO, enqueue is synonymmous with adding to back
}
template <class E>
E GenQueue<E>::dequeue()
{
  if(!isEmpty())
    return myQueue->removeFront();                                              //queue is FIFO so dequeue means removing from front
}
template <class E>
E GenQueue<E>::front()                                                          //just translating methods
{                                                                               //is there a better way to do this?
  if(!isEmpty())
    return myQueue->getFront();
}
template <class E>
bool GenQueue<E>::isEmpty()
{
  return myQueue->isEmpty();
}
template <class E>
int GenQueue<E>::getSize()
{
  return myQueue->getSize();
}
#endif
