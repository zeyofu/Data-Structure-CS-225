/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <iostream>

using namespace std;

/**
 *  This class creates a DisjointSets object that uses up-tree structure.
 **/
class DisjointSets{

private:

	vector<int> table;

public:

	/**
	 *  This function finds root of a given element and compresses the path.
	 **/
	int find(int elem);
	
	/**
	 *  This function creates n unconnected root nodes at the end of the vector.
	 **/
	void addelements(int num);

	/**
	 *  This function unions two sets by size.
	 **/
	void setunion(int a, int b);

};

#endif
