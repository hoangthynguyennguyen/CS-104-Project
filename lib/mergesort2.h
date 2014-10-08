#ifndef MERGESORT2_H
#define MERGESORT2_H

#include <iostream>
#include <vector>
#include <string>

using namespace std; 
//template <class Comparator>
//template <class T, class Comparator>
template <class T>
struct AlphaStrComp 
{
   		
   bool operator()(const T& lhs, const T& rhs) 
   { 
		string nameleft, nameright; 
		nameleft = lhs -> filename();
		nameright = rhs -> filename(); 

		return nameleft < nameright;
		} 

};

template <class T>
struct pageRank
{
	
	bool operator()(const T& lhs, const T& rhs)
	{
		double leftval, rightval;
		leftval = lhs -> _pageValue();
		rightval = rhs -> _pageValue(); 
		return leftval < rightval; 
	}
};
template <class T>
struct bidRank
{
	bool operator()(const T& lhs, const T& rhs)
	{
		double leftval, rightval;
		leftval = lhs -> getScore();
		rightval = rhs -> getScore(); 
		return leftval < rightval; 
	}
};



template <class T, class Comparator>
class mergeSort
{

public:	
void merge_sort(vector<T> &list, Comparator c);
void msort(vector<T> &list, Comparator c, vector<T> &sorted_list );
//void merge(vector<T> &list, int start, int end1, int start2, int end2, Comparator c, vector<T> &sorted_list);
void merge(vector<T> &rightList, vector<T> &leftList, Comparator c, vector<T> &sorted_list);
};



template <class T, class Comparator>
void mergeSort<T,Comparator>::merge_sort(vector<T> &list, Comparator c) 
{
	vector<T> sorted_list; 
	msort(list, c, sorted_list);

	for (unsigned int i = 0 ; i < sorted_list.size() ; i ++)
	{
		list [i] = sorted_list[i];
	}
	/*for(unsigned int i = 0; i < list.size(); i++){
		cout << "Sorted list " << list[i] -> filename() << endl;
	}*/
}



template <class T, class Comparator>
void mergeSort<T,Comparator>::msort (vector<T> &list, Comparator c, vector<T> &sorted_list)
{

	int length = list.size();
	if (length < 2){
		return; 
	}
	int mid = length/2;
	vector<T> leftList; 
	for(int i = 0; i < mid; i++){
		leftList.push_back(list[i]);
	}
	vector<T> rightList;
	for(int i = mid; i < length; i++){
		rightList.push_back(list[i]);
	}
	msort(leftList, c, sorted_list);
	msort(rightList, c, sorted_list);


	merge(leftList, rightList, c, list);
}


template <class T, class Comparator>
void mergeSort<T,Comparator>::merge(vector<T> &rightList, vector<T> &leftList, Comparator c, vector<T> &sorted_list)
{
	/*for (unsigned int i = 0; i < leftList.size(); i++){
		cout << "This is in left list " << leftList[i] -> filename() << endl; 

	}
	for (unsigned int i = 0; i < rightList.size(); i++){
		cout << "This is in right list " << rightList[i] -> filename() << endl; 
	} */

	int rightLength = rightList.size();
	int leftLength = leftList.size();
	int i = 0; //right
	int j = 0; //left
	int k = 0;
	while (i < rightLength && j < leftLength){
		if(c(leftList[j], rightList[i])){
			//cout << "Seg fault because left small" << endl;
			//sorted_list.push_back(leftList[j]);
			sorted_list[k] = leftList[j];
			//cout << "Adding this to sorted " << sorted_list.back() -> filename() << endl;
			k++;
			j++;
		}
		else{
			sorted_list[k] = rightList[i];
			//cout << "Adding this to sorted " << sorted_list.back() -> filename() << endl;
			k++;
			i++;
		}
	}

	//Check leftovers
	while (i < rightLength){
		//cout << "Adding this to sorted " << rightList[i] -> filename() << endl;
		sorted_list[k] = rightList[i];
		k++;
		i++;
	}
	while(j < leftLength){
		//cout << "Adding this to sorted " << leftList[j] -> filename() << endl;
		sorted_list[k] = leftList[j];
		k++;
		j++;
	}

	/* for(unsigned int i = 0; i < sorted_list.size(); i++){
		cout << "Currently sorted list " << sorted_list[i] -> filename() << endl;
	} */
	    
}

#endif //MERGESORT2_H
