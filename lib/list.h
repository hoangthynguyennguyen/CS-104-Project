// necessary includes can go here
#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdexcept> 

using namespace std;

template <class T>
struct Item
{
  T value;
  Item<T> *prev, *next;
};

template <class T>
class List
{
  public:
    List ();   // constructor
    ~List ();  // destructor
    int size () const;  // returns the number of elements in the list
    void insert (int position, const T & val);
    void remove (int position);
    void set (int position, const T & val);
    T& get (int position) const;
    void print ();
    void clear();
    List (const List<T> & other);
  // A copy constructor which performs a deep copy.
    List<T> & operator= (const List<T> & other);
  // An assignment operators.

  private:
    Item<T> *head;
    Item<T> *tail; 
    int _size; 
};
//Initiailizing size, something I added, to 0 that empty lists have size 0
template <class T>
List<T>::List(){
  _size = 0;
  head = NULL;
  tail = NULL;
}
//Using clear to delete things I don't want
template <class T>
 List<T>::~List (){
  clear();
 }

template <class T>
int List<T>::size () const{  // returns the number of elements in the list
  return _size;
}
//Insert a new item 
template <class T>
void List<T>::insert (int position, const T & val){
      if (position < 0 || position > _size){
          //throw position; 
        throw out_of_range("Not within list size for list.h");
        }
      Item<T>* temp = head; 
      Item<T>* myItem = new Item<T>; 
      myItem -> value = val;

      //If there's nothing in the list yet 
      if (temp == NULL){
        myItem -> next = NULL;
        myItem -> prev = NULL;
        head = myItem; 
        tail = myItem;  
        _size++;
        return;
      }
      //First item in list 
      if (position == 0){
        myItem -> prev = NULL; 
        myItem -> next = head; 
        head -> prev = myItem; 
        head = myItem;
          _size++;
        return; 

      }
      //Inserting an item at the end 
      if (position == _size){
        myItem -> next = NULL; 
        myItem -> prev= tail;
        tail -> next = myItem;
        tail = myItem; 
          _size++;
      
        return;
      }
      //Inserting things to the middle 
    else{
       for (int i=0; i < position-1; i++){ 
          temp = temp -> next;
        }
        myItem -> prev = temp; //Set the new item's previous to the thing before it 
        myItem -> next = temp -> next; //Set the new item's next to the thing before its next
        temp -> next -> prev = myItem; //Set the previous field of the item that comes after new item to new item... 
        temp -> next = myItem;
          _size++;

        return;
    }
}
     
template <class T>
void List<T>::remove (int position){
     if (position < 0 || position >= _size){
          //throw position;
          throw out_of_range("Not within list size for list.h"); 
        }
      Item<T>* temp = head;
      for (int i = 0; i < position; i++){
        temp = temp -> next;
      }
      //If there's nothing for me to remove 
      if (_size == 0){
        cout << "There is nothing left to remove." << endl;
        return; 
       }
       //If you're removing from the front 
       if (position == 0){
        if (temp -> next != NULL){
          temp -> next -> prev = NULL;
          head = temp -> next;
          tail = temp -> next; 
          delete temp;
          _size--;
        }
        else{
          head = NULL;
          tail = NULL;
          delete temp;
          _size--;
        }
        return;
       }
      
       if (temp -> next != NULL){
          temp -> prev -> next = temp -> next;
          temp -> next -> prev = temp -> prev;
           delete temp;
           _size--;
           return;
       }
       else{
          temp -> prev -> next = NULL;
          tail = temp -> prev;
          delete temp;
          _size--;
          return;
        }
}

template <class T>
void List<T>::set (int position, const T & val){
        if (position < 0 || position >= _size){
          //throw position; 
          throw out_of_range("Not within list size for list.h");
        }
        //Replacing the value of the item at the position given 
        Item<T>* temp = head; 
        for (int i=0; i < position; i++){
          temp = temp -> next;
        }

        temp -> value = val; 
}

template <class T>
T& List<T>::get (int position) const{
        if (position < 0 || position >= _size){
          //throw position; 
          throw out_of_range("Not within list size for list.h");
        }
        //Iterating to the item and then obtaining it's value
        Item<T>* temp = head;
        for (int i=0; i < position; i++){
          temp = temp -> next;
        }
        return temp->value; 
}

template <class T>
void List<T>::print (){
  cout << "My list size is " << _size << endl;
  for (int i = 0; i < _size; i++){
      cout << "Position " << i << ": ";  
      cout << get(i) << endl;
    } 
}
template <class T>
void List<T>::clear(){
  Item<T>* tempPter;
  while (head != NULL){
    tempPter = head; 
    head = head -> next;
    //tempPter -> next = NULL; 
    delete tempPter;
  }
    tempPter = NULL;
    _size = 0;
}
template <class T>
List<T>::List(const List<T> & other)
{
  head = NULL;
  tail = NULL;
  _size = 0;
  for (int i = 0; i < other.size(); i++){
    List::insert(i, other.get(i));
  }
}
  // A copy constructor which performs a deep copy.
template <class T>
List<T>& List<T>::operator=(const List<T> & other){
  if (this == &other){
    //cout << "I worked" << endl;
    return *this;
  }
  if (this != &other){
    this -> clear(); 
    //cout << "COME ON SON. " << endl;
    //cout << _size << endl;
    for (int i= 0; i < other.size(); i++){
      T val = other.get(i);
      List::insert(i, val);

    }
  }
  return *this;
}


#endif // LIST_H