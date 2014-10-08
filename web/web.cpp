#include "web.h"

using namespace std;

WebPage::WebPage (){

}    // constructor that creates an empty page
 WebPage::WebPage (string filename){
  _fileName = filename;
  _updateVal = 0; //Initializing the update value to 0 for pagerank
  //cout << "This is the filename: " << _fileName << endl; 
  ifstream myFile; 
  myFile.open((filename).c_str());
  if(myFile.fail()){
    throw invalid_argument("This file is not found");
  }
 string temporary;
 string linkName = ""; 

 linkExists = false;
  while(myFile.good()){
    linkName = ""; 
    getline(myFile, temporary); 
    //cout << temporary << "was read in" << endl;
    if(temporary.size() == 0){
      continue;
    }
    
    //Creating two vectors that will store the positions of the open and closed brackets I find to find links
    vector<int> openL;
    vector<int> closeL;
 
    findLink(temporary, openL, closeL);

    every += temporary;

    if(linkExists == true){
     hideLink(every);
    }//end if LinkExists = true

    every += '\n';
    
    if(myFile.fail()){ 
      cout << temporary << " is the line that failed" << endl;
       throw invalid_argument("This file cannot be read in.");
    }


    //If there is a link in there, let's treat it differently 
    for (unsigned int i = 0; i < openL.size(); i++){
      int openp = -1;
      if(linkExists == true){
        openp = closeL[i] + 1; //this will be the open parenthesis 
        openp = openp + 1; //This will be the first character after the parentehsis
        while(temporary[openp] != ')'){
          if (temporary[openp] != char(34) && temporary[openp] != char(32)){
            linkName.push_back(temporary[openp]);
          }
          openp++;
        }
        //cout << "Did I read in the link? " << linkName << endl;
        linkNames.push_back(linkName);
        linkName.clear();
        
        for(int j = closeL[i] + 1; j <= openp; j++){
          temporary[j] = char(32);
        }
        //cout << "Here is the erased version " << temporary << endl;
      }//End if link is there  
    } //end for openl 

    for(unsigned int i = 0; i < temporary.size(); i++){
      if(temporary[i] == '[' || temporary[i] == ']' || temporary[i] == '(' || temporary[i] == ')' || temporary[i] == '.'){
        temporary[i] = char(32);
      }
    }
     // Cleaning it 
     cleanUp(temporary);  
  } //END WHILE MYFILE GOOD LOOP


} 


WebPage::~WebPage (){
 
}   // destructor

Set<string> WebPage::allWords () const {
  return words;
}
        

ostream & operator<<(ostream & os, const WebPage & page){
  
  return os << page.every;
  
}

bool WebPage::operator==(const WebPage &rhs){
  if(this -> every == rhs.every){
    return true;
  }
  return false;

}


void WebPage::print(){
  cout << every << endl;
}

void WebPage::cleanUp(string &temporary){
  for(unsigned int i = 0; i < temporary.size(); i++){
  //If they're uppercase, make them lower case
      if(temporary[i] >= 65 && temporary[i] <= 90){
        temporary[i] = char(temporary[i] + 32); 
      }
      //Ignore the special characters now
      if(temporary[i] >= 0 && temporary[i] <= 47){
         if (temporary[i] == 40 || temporary[i] == 41 || temporary[i] == '.'){

        }
        else{
          temporary[i] = char(32);
        }
      }
      if(temporary[i] >= 58 && temporary[i] <= 64){
         temporary[i] = char(32); 
      }
      if(temporary[i] >= 91 && temporary[i] <= 96){
        if (temporary[i] == 91 || temporary[i] == 93){

        }
        else{
          temporary[i] = char(32);
        }
      }
      if(temporary[i] >= 123 && temporary[i] <= 127){
        temporary[i] = char(32); 
      }
   
  }//END TEMP FOR


  //Added this part, where we ignore white space and go through and grab le words.
    string aWord;
    stringstream ss(temporary);
    bool shouldIgnore;
    while (!(ss >> aWord).fail()){
      shouldIgnore = false;
      if (words.size() == 0){ 
        words.insert(aWord);
        //cout << aWord << endl;
      }
      if (aWord == *words.begin()){
            shouldIgnore = true;
      }
      else{
        if (words.size() >= 2){
          for (set<string>::iterator wordIter = words.begin(); wordIter != words.end(); ++wordIter){
            if (aWord == *wordIter){
              shouldIgnore = true;
            } //end for if word
          } //end for all words
        }//end if word size greater than two 
      }//END ELSE
      if (shouldIgnore == false){
        words.insert(aWord);
      }
    }//End string stream fail while
}
 //void WebPage::findLink(string &temporary, int &openb, int&closeb){
void WebPage::findLink(string &temporary, vector<int> &openL, vector<int> &closeL){
    linkExists = false;
    //Ints to store the positions of the open and close brackets
    int openb;
    int closeb;
    for (unsigned int i = 0; i < temporary.size(); i++){
      if(temporary[i] == '['){
        linkExists = true;
        openb = i;
        openL.push_back(openb);

      }
      if(temporary[i] == ']'){
        closeb = i;
        closeL.push_back(closeb);
      }
    }// finding where anchor text exists, if it all
 }

void WebPage::hideLink (string& every){
  //Vectors to store positions of all open and close bracket in every so I can find the () and hide them
  vector<int> everyOpen;
  vector<int> everyClose;
  for(unsigned int i = 0; i < every.size(); i++){
    if(every[i] == '['){
      everyOpen.push_back(i);
    }
    if (every[i] == ']'){
      everyClose.push_back(i);
    }
  }
  
    for (unsigned int j = 0; j < everyOpen.size(); j++){
      //Changing brackets to space 
      string anchorN = "";
      for (int i = everyOpen[j] + 1; i < everyClose[j]; i++){
        anchorN.push_back(every[i]);
        //This is the anchor from hideLink, because I feel I'll need it eventually
      }
      this -> addAnchor(anchorN);
      
      every[everyOpen[j]] = char(32);
      every[everyClose[j]] = char(32);
      int paren = everyClose[j] + 1; //open parenthesis AFTER A LINK.
      int moveUp = paren;
      //white out all link and parenthesis
      while(every[moveUp] != ')'){
        every[moveUp] = char(32);
        moveUp++;
      }
      every[moveUp] = char(32);
    }
}

void WebPage::addAnchor(string& anchor){
  if(linkExists == true){
    anchors.push_back(anchor);
  }
}

bool WebPage::hasLink(){
  return linkExists;
}

vector<string>& WebPage::_linkNames(){
  return linkNames;
}

Set<WebPage*> WebPage::allOutgoingLinks () const{
   return linkedP;
}
       

Set<WebPage*> WebPage::allIncomingLinks () const{
  return iLinks;
}
  
string WebPage::filename () const{
 
  return _fileName;
}
    


void WebPage::parse (WebPage* tempLink){
    
    WebPage* temporary = this; 
    //Add what I'm on right now to the passed in's incoming
    tempLink -> addIncomingLink(temporary);

    //Add what was passed in to what I'm on right now's outgoing
    this -> addOutgoingLink(tempLink);
}
      

void WebPage::addIncomingLink (WebPage* start){
  this -> iLinks.insert(start);
}
      

void WebPage::addOutgoingLink (WebPage* target){
  this -> linkedP.insert(target);
}

string WebPage::allString (){
  return every;
}
double WebPage::_pageValue(){
  return pageValue;
}
void WebPage::setPageValue(double newVal){
  pageValue = newVal;
}
int WebPage::viewIndex(){
  return indexVal;
}
void WebPage::setIndex(int _index){
  indexVal = _index;
}
void WebPage::updateVal(double addVal){
  _updateVal += addVal;
}
double WebPage::returnUpdate(){
  return _updateVal;
}