#ifndef DLINKEDLIST_CPP
#define DLINKEDLIST_CPP
#include <iostream>
using namespace std;
template <class E>
class DListNode
{
public:
  DListNode();
  DListNode(E d);
  ~DListNode();
  E data;
  DListNode<E>* next;
  DListNode<E>* prev;
};
template <class E>
DListNode<E>::DListNode()
{
  data = NULL;
  next = NULL;
  prev = NULL;
}
template <class E>
DListNode<E>::DListNode(E d)
{
  data = d;
  next = NULL;
  prev = NULL;
}
template <class E>
DListNode<E>::~DListNode()
{
  delete next;                                                                  //next and prev are dynamically allocated, so we gotta delete
  delete prev;
}
template <class E>
class DLinkedList
{
public:
  DLinkedList();
  ~DLinkedList();
  void addFront(E d);
  E removeFront();
  void addBack(E d);
  E removeBack();
  void printList();
  int find(E value);
  E deleteKey(E key);
  bool isEmpty();
  unsigned int getSize();
  E getFront();
  DListNode<E>* front;
  DListNode<E>* back;
  unsigned int size;

};
template <class E>
DLinkedList<E>::DLinkedList()
{
  size = 0;
  front = NULL;
  back = NULL;
}
template <class E>
DLinkedList<E>::~DLinkedList()
{
  delete front;
  delete back;
}
template <class E>
void DLinkedList<E>::addFront(E d)
{
  DListNode<E>* node = new DListNode<E>(d);                                     //create temp node for traversal
  if(size == 0)                                                                 //if list empty
    front = back;                                                               //for a DLL with one element, it should be true that front = back
  else
  {                                                                             //if list non empty
    node->next = front;                                                         //attaching node to the front of the list
    front->prev = node;                                                         //changing old front's prev pointer to new front
  }
  front = node;                                                                 //our node is now front
  size++;                                                                       //increment size
}
template <class E>
void DLinkedList<E>::addBack(E d)
{
  DListNode<E>* node = new DListNode<E>(d);                                     //create temp node
  if(size == 0)                                                                 //if list empty
    front = node;                                                               //since we add to the back with no elements, new node will be both front and back
  else
  {                                                                             //if list non empty
    back->next = node;                                                          //attach node to be the next element form back
    node->prev = back;                                                          //update node's prev pointer to point to our old back
  }
  back = node;                                                                  //update back pointer
  size++;                                                                       //incrememnt size
}
template <class E>
E DLinkedList<E>::removeFront()
{
  DListNode<E>* node = front;                                                   //create temp pointer to front
  if(isEmpty())                                                                 //empty list
    return E();                                                                 //no such element, return default of type E
  else if(front->next == NULL)                                                  //only one element
    back = NULL;                                                                //since front = back, we set back to null
  else                                                                          //list non empty, with more than one element
    front->next->prev = NULL;                                                   //we set the second node's prev pointer to null
  front = front->next;                                                          //front pointer now points to next (will point to null for one element case)
  E temp = node->data;                                                          //temp value to store data
  node->next = NULL;                                                            //since node prev = null, we only set it's next to null
  delete node;                                                                  //delete te node after deleting its pointers
  size--;                                                                       //decrement size
  return temp;                                                                  //return the data from the deleted node
}
template <class E>
E DLinkedList<E>::removeBack()
{
  DListNode<E>* node = back;                                                    //create temp pointer to back
  if(isEmpty())                                                                 //empty list
    return E();                                                                 //no such element, return default of type E
  else if(back->prev == NULL)                                                   //only one element
    front = NULL;                                                               //since front = back, we set front to null
  else                                                                          //list non empty, with more than one element
    back->prev->next = NULL;                                                    //we set the second to last node's next pointer to null
  back = back->prev;                                                            //back pointer now points to the second to last val
  E temp = node->data;                                                          //temp value to store data
  node->prev = NULL;                                                            //since back next is null, we only set it's prev to null
  delete node;                                                                  //delete the node after deleting its pointers
  size--;                                                                       //decrement size
  return temp;                                                                  //return the data from the deleted node
}
template <class E>
void DLinkedList<E>::printList()
{
  DListNode<E> *current = front;
  while(current)
  {
    cout << current->data << endl;
    current = current->next;
  }
  delete current;
}
template <class E>
int DLinkedList<E>::find(E value)
{
  int pos = -1;
  DListNode<E> *current = front;
  while(current)
  {
    if(current->data == value)                                                  //if we find our value, stop updating
      break;
    else
      current = current->next;                                                  //iterate to next value
    pos++;                                                                      //increment position
  }
  if(current == NULL)                                                           //if not found, return -1
    pos = -1;
  delete current;
  return pos;
}
template <class E>
E DLinkedList<E>::deleteKey(E key)
{
  if(isEmpty())                                                                 //check isEmpty
    return E();                                                                 //return default of E since no element to delete
  DListNode<E> *curr = front;                                                   //create a temp pointer to the front
  while(curr->data != key)                                                      //while our key hasn't been found
  {
    curr = curr->next;                                                          //traverse the list by updating cursor pointer
    if(curr == NULL)                                                            //if we reach the end without finding the value
    {
      cout << "Value not found";
      return E();                                                              //return null since no such value
    }
  }
  if(curr == front)                                                             //if the node to delete is the front node
    front = curr->next;                                                         //update front to be the next node
  else                                                                          //if node to be deleted is in the middle of the list
    curr->prev->next = curr->next;                                              //update pointers of the prev node to be the next node
  cout << "ok" << endl;
  if(curr == back)                                                              //if the node to delete is our back node
    back = curr->prev;                                                          //basically remove back
  else
    curr->next->prev = curr->prev;                                              //update prev pointers
  curr->next = NULL;                                                            //update pointers to next and prev to be null
  curr->prev = NULL;
  size--;                                                                       //decrememnt size
  E temp = curr->data;                                                          //store data before we delete it
  delete curr;
  return temp;
}
template <class E>
bool DLinkedList<E>::isEmpty()
{
  return size == 0;
}
template <class E>
unsigned int DLinkedList<E>::getSize()
{
  return size;
}
template <class E>
E DLinkedList<E>::getFront()
{
  return front->data;
}
#endif
