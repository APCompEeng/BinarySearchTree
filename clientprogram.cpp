//file clientprogram.cpp
author Adam Pesch
//date October 8, 2018

#include "binarysearchtree.h"
#include "avltree.h"
#include "exception.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile, string filename);

//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openOutputFile(infile, filename);
void openOutputFile(ofstream& inputFile, string filename);

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except);

void printNewLines(int lines, ofstream& outfile);

void checkNoPivotCase(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void checkDoubleLeftRightCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkDoubleLeftRightCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkDoubleLeftRightCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree);


void checkDoubleRightLeftCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkDoubleRightLeftCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkDoubleRightLeftCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void printsAVLTree(AVLTree& mytree, ofstream& outfile);

void checkSingleLeftRotationCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkSingleLeftRotationCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkSingleLeftRotationCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void checkSingleRightRotationCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkSingleRightRotationCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree);
void checkSingleRightRotationCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void checkisAddedToShortSideCase(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void noPivotEmptyCase(ifstream& infile, ofstream& outfile, AVLTree& mytree);

void checkNoPivotCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree);

int main()
{
	ifstream infile;
	ofstream outfile;
	AVLTree tree0, tree1, tree2, tree3, tree4, tree5;
	
	AVLTree tree6, tree7, tree8, tree9, tree10;
	
	AVLTree tree11, tree12, tree13, tree;
	
	Item anItem;
	
	openInputFile(infile, "in.dat");
	
	openOutputFile(outfile, "avl.dat");
	
	noPivotEmptyCase(infile, outfile, tree0);
	
	checkNoPivotCaseTwo(infile, outfile, tree);
	
	checkNoPivotCase(infile, outfile, tree1);
	
	checkisAddedToShortSideCase(infile, outfile, tree1);
	
	checkNoPivotCase(infile, outfile, tree2);
	
	checkSingleLeftRotationCaseOne(infile, outfile, tree2);
	
	checkNoPivotCase(infile, outfile, tree3);
	
	checkSingleLeftRotationCaseTwo(infile, outfile, tree3);
	
	checkNoPivotCase(infile, outfile, tree4);
	
	checkSingleLeftRotationCaseThree(infile, outfile, tree4);
	
	checkNoPivotCase(infile, outfile, tree5);
	
	checkSingleRightRotationCaseOne(infile, outfile, tree5);
	
	checkNoPivotCase(infile, outfile, tree6);
	
	checkSingleRightRotationCaseTwo(infile, outfile, tree6);
	
	checkNoPivotCase(infile, outfile, tree7);
	
	checkSingleRightRotationCaseThree(infile, outfile, tree7);
	
	checkNoPivotCase(infile, outfile, tree8);

	checkDoubleLeftRightCaseOne(infile, outfile, tree8);
	
	checkNoPivotCase(infile, outfile, tree9);

	checkDoubleLeftRightCaseTwo(infile, outfile, tree9);
	
	checkNoPivotCase(infile, outfile, tree10);

	checkDoubleLeftRightCaseThree(infile, outfile, tree10);
	
	checkNoPivotCase(infile, outfile, tree11);

	checkDoubleRightLeftCaseOne(infile, outfile, tree11);
	
	checkNoPivotCase(infile, outfile, tree12);

	checkDoubleRightLeftCaseTwo(infile, outfile, tree12);
	
	checkNoPivotCase(infile, outfile, tree13);

	checkDoubleRightLeftCaseThree(infile, outfile, tree13);
	
	

   return 0;
}

void checkisAddedToShortSideCase(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	printNewLines(1, outfile);
	outfile << "	CASE OF ADD TO SHORT SIDE" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	

	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkNoPivotCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	Item anItem;
	int numberOfEntries;
    
	infile >> numberOfEntries;
	for (int i = 0; i < numberOfEntries; i++)
	{
		infile >> anItem;
		outfile << "Key " << anItem << " is inserted" << endl;
		
		try
		{
			mytree.addNewEntry(anItem);
		}
		
		catch(Exception except)
		{
			
			printExceptionMessage(except);
		}
	}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkNoPivotCase(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	Item anItem;
	int numberOfEntries;
    
	infile >> numberOfEntries;
	for (int i = 0; i < numberOfEntries-1; i++)
	{
		infile >> anItem;
		
		try
		{
			mytree.addNewEntry(anItem);
		}
		
		catch(Exception except)
		{
			
			printExceptionMessage(except);
		}
	}

}


//START OF SINGLE LEFT ROTATION CASES
//
//
//
//

void checkSingleLeftRotationCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{ 
    outfile << "	CASE OF SINGLE LEFT ROTATION" << endl;
	printNewLines(1, outfile);
	outfile << "Test 1: IF PIVOT IS THE ROOT" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkSingleLeftRotationCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 2: IF PIVOT IS THE LEFT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkSingleLeftRotationCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 3: IF PIVOT IS THE RIGHT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

//START OF SINGLE RIGHT ROTATION CASES
//
//
//
//

void checkSingleRightRotationCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{ 
	outfile << "	CASE OF SINGLE RIGHT ROTATION" << endl;
	printNewLines(1, outfile);
	outfile << "Test 1: IF PIVOT IS ROOT" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkSingleRightRotationCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 2: IF PIVOT IS LEFT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkSingleRightRotationCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	printNewLines(1, outfile);
	outfile << "Test 3: IF PIVOT IS RIGHT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printNewLines(2, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

//START OF DOUBLE LEFT RIGHT ROTATION CASES
//
//
//
//

void checkDoubleLeftRightCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "	CASE OF DOUBLE LEFT RIGHT ROTATION" << endl;
	printNewLines(1, outfile);
	outfile << "Test 1: IF PIVOT IS ROOT" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkDoubleLeftRightCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 2: IF PIVOT IS LEFTCHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}

	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkDoubleLeftRightCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 3: IF PIVOT IS RIGHT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

//START OF DOUBLE RIGHT LEFT ROTATION CASES
//
//
//
//

void checkDoubleRightLeftCaseOne(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "	CASE OF DOUBLE RIGHT LEFT ROTATION" << endl;
	printNewLines(1, outfile);
	outfile << "Test 1: IF PIVOT IS ROOT" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printNewLines(2, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkDoubleRightLeftCaseTwo(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 2: IF PIVOT IS LEFT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}

void checkDoubleRightLeftCaseThree(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "Test 3: IF PIVOT IS RIGHT CHILD" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);
	
	try
		{
			mytree.addNewEntry(anItem);
		}
		
   catch(Exception except)
		{
			printExceptionMessage(except);
		}
	
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
}


void printsAVLTree(AVLTree& mytree, ofstream& outfile)
{
	mytree.prettyDisplay(outfile);	
}

void noPivotEmptyCase(ifstream& infile, ofstream& outfile, AVLTree& mytree)
{
	outfile << "	CASE OF NO PIVOT" << endl;
	outfile << "Test 1: CASE OF EMPTY TREE" << endl;
	printNewLines(1, outfile);
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	Item anItem;
	infile >> anItem;
	outfile << "Key " << anItem << " is inserted" << endl;
	printNewLines(1, outfile);
	outfile << "post tree" << endl;
	printNewLines(1, outfile);

		try
		{
			mytree.addNewEntry(anItem);
		}
		
		catch(Exception except)
		{
			
			printExceptionMessage(except);
		}
		
	printsAVLTree(mytree, outfile);
	printNewLines(1, outfile);
	
	outfile << "Test 2: CASE OF TREE HEIGHT 2" << endl;
	printNewLines(1, outfile);
}

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile, string filename) 
{
	inputFile.open(filename);

	if (inputFile.fail())
	{
	  cout << "Input file failed to open, closing program." << endl;
	  exit(1);
	}
	
}

//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openOutputFile(infile, filename);
void openOutputFile(ofstream& outputFile, string filename)
{
	outputFile.open(filename);
	
	if ( outputFile.fail())
	{
	  cout << "Output file failed to open, closing program." << endl;
	  exit(1);
	}
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except)
{
   cout << endl;
   cout << except.what();
   cout << endl;
}

void printNewLines(int lines, ofstream& outfile)
{
	for (int i = 0; i < lines; i++)
	{
		outfile << endl;
	}
}
