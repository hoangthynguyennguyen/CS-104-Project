#ifndef WEB_H
#define WEB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> 
#include "../lib/set2.h"
//#include "list.h"
//#include "map.h"
#include <map>
#include <vector>

using namespace std;

class WebPage {
  public:
    WebPage ();    // constructor that creates an empty page
    WebPage (string filename);

    ~WebPage ();   // destructor

    Set<string> allWords () const;
    string allString ();
       
    friend ostream & operator<< (ostream & os, const WebPage & page);
     
    bool operator==(const WebPage &rhs);
    void print();
    bool hasLink();
    vector<string>& _linkNames();
    Set<WebPage*> allOutgoingLinks () const; 
    Set<WebPage*> allIncomingLinks () const;
    string filename () const;
    void parse (WebPage*); 
    void addIncomingLink (WebPage* start);
    void addOutgoingLink (WebPage* target); 
    double _pageValue();
    void setPageValue(double newVal);
    int viewIndex();
    void setIndex(int _index);
    void updateVal(double addVal);
    double returnUpdate();
    bool linkExists;


  private:
    // you get to decide what goes here.
    Set<string> words;
    string every;
    string _fileName;
    Set<WebPage*> linkedP; //if a link is in the file, I'll delete it using linkExists bool
    Set<WebPage*> iLinks; //links that point to me? 
    vector<string> linkNames;
    vector <string> anchors; 
    // bool linkExists;
    void cleanUp(string&);
    void findLink(string&, vector<int>&, vector<int>&);
    void hideLink (string& );
    void addAnchor(string& anchor);
    double pageValue;
    double _updateVal; //individual update value per iteration 
    int indexVal; //keep track of where it is 

};

//Implementation is inside of web.cpp

#endif // WEB_H