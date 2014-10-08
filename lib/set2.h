#ifndef SET_H
#define SET_H
#include <iostream>
#include <stdexcept> 
#include "list.h"
#include <set> 

template <class T>
class Set: public set<T>{
  public: 

    Set (): set<T>:: set(){} 
    Set (const set<T> & other): set<T>:: set(other){}
    bool contains (const T & item) const{
      for (typename set<T>::iterator iter = this -> begin(); iter != this -> end(); ++iter){
        if (*iter == item){
          return true;
        }
      }
      return false;
    }


    Set<T> setIntersection (const Set<T> & other) const{
      Set<T> intersect; 
      for (typename set<T>::iterator iter = this -> begin(); iter != this -> end(); ++iter){
        for(typename set<T>::iterator iter2 = other.begin(); iter2 != other.end(); ++iter2){
          if(*iter2 == *iter){
            intersect.insert(*iter2);
          }
        }
      }
      return intersect;
    }
   

    Set<T> setUnion (const Set<T> & other) const{
        Set<T> unions(other);
        for (typename set<T>::iterator iter = this -> begin(); iter != this -> end(); ++iter){
          for(typename set<T>::iterator iter2 = other.begin(); iter2 != other.end(); ++iter2){
            if(*iter2 != *iter){
              unions.insert(*iter);
            }
          }
        }
        return unions;
    }
};


#endif // SET_H