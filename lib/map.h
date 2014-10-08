// necessary includes can go here
#ifndef MAP_H
#define MAP_H 
#include <iostream> 
#include <stdexcept> 
#include "list.h"

template <class keyType, class valueType>
struct mapEntry{
    
     keyType myKey;
     valueType myValue;
    mapEntry(keyType myK, valueType myV){
       myKey = myK;
       myValue = myV;
    }
    mapEntry(){
    }
};

template <class keyType, class valueType>
class Map
{
  public:
    Map ();  // constructor for a new empty map
    ~Map (); // destructor
    int size () const; // returns the number of key-value pairs
    void add (const keyType & key, const valueType & value); 
    void remove (const keyType & key);
    //valueType const & get (const keyType & key) const;
    //valueType & get (const keyType & key);
    valueType & get (const keyType & key) const;
    int find(const keyType & key)const;
    void printMap();
   

  private:
    List<mapEntry<keyType, valueType> > internalStorage;
   
};
//NOTE. My code IS case-sensitive for look-up
template <class keyType, class valueType>
Map<keyType, valueType>::Map (){
    
}
template <class keyType, class valueType>
Map<keyType, valueType>::~Map (){
   
}
//Just grab the list size and return it. 
template <class keyType, class valueType>
int Map<keyType, valueType>::size () const{
    return internalStorage.size();
}
//Using my list's insert to create a new item. Just place it in front because unsorted
template <class keyType, class valueType>
void Map<keyType, valueType>::add (const keyType & key, const valueType & value){
    for (int i = 0; i < internalStorage.size(); i++){
        if (internalStorage.get(i).myKey == key){
            //throw key;
            throw invalid_argument("This entry is already there for map");
        }
    }
    mapEntry<keyType, valueType> tempEntry(key, value);
    internalStorage.insert(0, tempEntry);
}
//Using list to delete an item from my list. Find it and then delete it, if there. 
template <class keyType, class valueType>
void Map<keyType, valueType>::remove (const keyType & key){
    //See if it's even in the list
    bool isThere = false;
    for (int i = 0; i < internalStorage.size(); i++){
         if (internalStorage.get(i).myKey == key){
            isThere = true;
        }
    }
    if (isThere == false){
        //throw key;
        throw invalid_argument("There is no association for that in map.h");
    }

    int dlIdx = find(key);
    internalStorage.remove(dlIdx);
}

//Grabbing the item's value
template <class keyType, class valueType>
valueType& Map<keyType, valueType>::get (const keyType & key) const{
//valueType const & Map<keyType, valueType>::get (const keyType & key) const{
    bool isThere = false;
    for (int i = 0; i < internalStorage.size(); i++){
         if (internalStorage.get(i).myKey == key){
            isThere = true;
        }
    }
    if (isThere == false){
        //throw key;
        throw invalid_argument("There is no association for that in map.h");
    }
    int idx = find(key); 
    return internalStorage.get(idx).myValue;
}

//Changable get
/*valueType & Map<keyType, valueType>::get (const keyType & key){
    bool isThere = false;
    for (int i = 0; i < internalStorage.size(); i++){
         if (internalStorage.get(i).myKey == key){
            isThere = true;
        }
    }
    if (isThere == false){
        //throw key;
        throw invalid_argument("There is no association for that in map.h");
    }
    int idx = find(key); 
    return internalStorage.get(idx).myValue;
} */

//Find the item by iterating through and comparing the keys
//Return the index found at if you find it 
template <class keyType, class valueType>
int Map<keyType, valueType>::find(const keyType & key)const{
 for (int i = 0; i < internalStorage.size(); i++){
     if (internalStorage.get(i).myKey == key){
            return i;
        }
    }
    //throw key; //this will happen if the key does not exist in the list
    throw invalid_argument("There is no association for that in map.h");
}

template <class keyType, class valueType>
void Map<keyType, valueType>::printMap(){
    for (int i = 0; i < internalStorage.size(); i++){
        cout << "I am position " << i << endl;
        cout << "My key is: ";
        cout << internalStorage.get(i).myKey << endl;
        cout << "My value is: "; 
        //cout << internalStorage.get(i).myValue << endl;
       internalStorage.get(i).myValue.print();
        cout << endl;
    }
    
}



#endif // MAP_H