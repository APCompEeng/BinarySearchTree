//username ltan
//author: Adam Pesch
// avltree.cpp
// Implementation of ADT AVLTree 
//     data object: none
//     operations: create, destroy
//                 add new items and pretty display 
//                 the AVL Tree
//   associated operations: input and output
// filename avltree.cpp
// date November 20, 2018

#include "item.h"
#include "treenode.h"
#include "binarytree.h"
#include "exception.h"
#include "avltree.h"
#include <string>
#include <fstream>
using namespace std;

const int MAXHEIGHT = 15;

struct SearchPath
{
	TreeNode* path[MAXHEIGHT];
	int size;
	int pivotIndex;
	SearchPath();
};

SearchPath::SearchPath()
{
	size = 0;
	pivotIndex = -1;
	for(int i = 0; i < MAXHEIGHT; i++)
	{
		path[i] = nullptr;
	}
}

//helpers

//prints the tree to look like a computer science tree
//pre: treep points to the root of a tree. level >= 0
//post: outputs the tree as in the example below
//
//  					  bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: writePretty(root,0);
void writePretty (TreeNode* treep, int level, ostream& output)
{	
	if (treep != nullptr)
	{
		writePretty(treep -> rightChild, level += 1, output);
		if (treep -> rightChild != nullptr)
		{
			for (int j = 0;j <= level;j++)
				output << "\t\t";
			output << "/" << endl;
		}
		if (level == 1)
			output << "root ->" ;
		else	
		{			
			for (int i = 0; i < level; i++)
				output << "\t\t" ;
		}
		Key text = treep -> item;
		output << "  " << text << " :" << treep -> balance << endl;
		 if (treep -> leftChild != nullptr)
        {
            for (int i = 0; i <= level; i++)
                output << "\t\t";
            output << "\\" << endl;
			writePretty(treep -> leftChild, level, output);
		}
	}		
}

// Helper function that adds new entry to the search tree
//		and creates a search path from root to new entry
// Pre: treeptr points an AVL tree, search is empty SearchPath
//		with size zero and newItem exists. 
// Post: newItem is added to the tree and 
//		search is a search path from root to new entry
//		with appropriate size
//		If newItem is already in the search tree or
//		there was no memory for new TreeNode exception
//		is thrown.
// Usage: addNewEntryAndMakeSearchPath(newItem, root, search);
void addNewEntryAndMakeSearchPath(const Item& newItem, TreeNode*& treeptr, SearchPath& search) throw (Exception)
{
	
	if (treeptr != nullptr)
	{
		search.path[search.size] = treeptr;
		search.size += 1;
		
		if (newItem == treeptr -> item)
		{
			throw Exception("That abbreviation is already in the dictionary.");
		} else if ( newItem < treeptr -> item) {
			addNewEntryAndMakeSearchPath(newItem, treeptr -> leftChild, search);
		} else {
			addNewEntryAndMakeSearchPath(newItem, treeptr -> rightChild, search);
		}
	} else {
		treeptr = new (nothrow) TreeNode(newItem, nullptr, nullptr);
		
		search.path[search.size] = treeptr;
		search.size += 1;
	} 
   
   if ( treeptr == nullptr )
	   throw Exception("There was not enough memory to add a new abbreviation.");
  
}

// if there is a pivot sets pivotIndex and returns false, else returns true if no pivot
// pre: the search path represents the path taken with search.path[0] pointing
//   	to the root of the tree and search.size has the number of items in the path
// post: search.pivotIndex is set to the highest value index with non-zero balance
// usage: binarSearchTree.hasNoPivot(search);

bool hasNoPivot(SearchPath& search)
{
   int index = search.size - 1;
   while(index >= 0)
   {
      if(search.path[index] -> balance != 0)
	  {
		 search.pivotIndex = index;
	     return false;
	  }
	  index--;		
   }
   return true;
}

//	rebalance the tree from start index down
//	pre: Unbalanced searchPath is passed along with the pivot index.
//  post: AVL Tree that was passed has correct index balances
//  usage: fixBalances(search, pivotIndex);
void fixBalances(const SearchPath& search, int start){
	for(int i = start; i < search.size - 1; i++){
		if(search.path[i]->rightChild == search.path[i+1]){
			search.path[i]->balance++;
		} else{
			search.path[i]->balance--;
		}
	}
}

// returns whether or not the newest item has been added to the short side of the tree using a given search path
// pre: search exists and is not empty. balances have not been updated since adding a new item
// post: true has been returned if the item was added to the short side, else returns false
// usage: bool isItemAddedToShortSide = isAddedToShortSide(search);
bool isAddedToShortSide(const SearchPath& search){
	if((search.path[search.pivotIndex] -> balance < 0 ) and (search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> rightChild)) //tall left but search path goes right
		return true;
	else if((search.path[search.pivotIndex] -> balance > 0 ) and (search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> leftChild)) //tall right but search path goes left
		return true;
	else
		return false;
}

// decides whether or not the tree needs a single right rotation
// pre: SearchPath exists and pivotIndex has been found
// post: returns whether true if a single rotation to the right is needed
//       and returns false if not needed.
// usage: tree.isSingleRotateRight(search)
bool isSingleRotateRight(const SearchPath& search)
{
	
	
	if(search.path[search.pivotIndex] -> leftChild == search.path[search.pivotIndex + 1] &&
       search.path[search.pivotIndex + 1] -> leftChild == search.path[search.pivotIndex + 2])
		return true;
    else
		return false;

 
}

// from the pivot node, if the search path goes right and then goes right again, returns true
// pre: object of type SearchPath exists
// post: returns true if search path goes right twice, false otherwise
// usage: isSingleRotateLeft(search)
bool isSingleRotateLeft(const SearchPath& search)
{
    if(search.path[search.pivotIndex] -> rightChild == search.path[search.pivotIndex + 1] &&
       search.path[search.pivotIndex + 1] -> rightChild == search.path[search.pivotIndex + 2])
        return true;
    else
        return false;
}

//pre search exists and was created and filled by AddNewEntry
//post search is unchanged
//		return true if the AVL tree goes left and then right
//		otherwise returns false
//usage isDoubleRotateLeftRight(search)
bool isDoubleRotateLeftRight (const SearchPath& search)
{
	if(search.path[search.pivotIndex] -> leftChild == search.path[search.pivotIndex + 1] && search.path[search.pivotIndex] -> leftChild -> rightChild == search.path[search.pivotIndex + 2])
	{
		return true;
	}else{
		return false; 
	}
}

//does the single left rotation for the AVL tree
//pre search path and treep points to AVL tree
//post checks if pivot is root, leftchild or rightchild
//     rotates the unbalanced tree to the left
//     the AVL tree is balanced
//usage singleLeftRotation(search, root);
void singleLeftRotation(SearchPath& search, TreeNode*& treep)
{
	//if pivot is root
	if (search.pivotIndex == 0)
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		
		pointerToPivot -> rightChild = nullptr;
		pointerToChild -> leftChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance -= 2;
		
		treep = pointerToChild;
	}
	//if pivot is a leftChild
	else if (search.path[search.pivotIndex -1] -> leftChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		TreeNode* pointerToTreeFromChild = search.path[search.pivotIndex + 1] -> leftChild;
		
		search.path[search.pivotIndex -1] -> leftChild = pointerToChild;
		pointerToPivot -> rightChild = pointerToTreeFromChild;
		pointerToChild -> leftChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance = 0;
	}
	//if pivot is a rightChild
	else if (search.path[search.pivotIndex -1] -> rightChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		TreeNode* pointerToTreeFromChild = search.path[search.pivotIndex + 1] -> leftChild;
		
		search.path[search.pivotIndex -1] -> rightChild = pointerToChild;
		pointerToPivot -> rightChild = pointerToTreeFromChild;
		pointerToChild -> leftChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance = 0;
	}
	
}

//does the single right rotation for the AVL tree
//pre search path and treep points to AVL tree
//post checks if pivot is root, leftchild or rightchild
//     rotates the unbalanced tree to the right
//     the AVL tree is balanced
//usage singleRightRotation(search, root);
void singleRightRotation(SearchPath& search, TreeNode*& treep)
{
	
    //if pivot is a root
	if (search.pivotIndex == 0)
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		
		pointerToPivot -> leftChild = nullptr;
		pointerToChild -> rightChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance += 2;
		
		treep = pointerToChild;

	}
	//if pivot is a leftChild
	else if (search.path[search.pivotIndex -1] -> leftChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		TreeNode* pointerToTreeFromChild = search.path[search.pivotIndex + 1] -> rightChild;
		
		search.path[search.pivotIndex -1] -> leftChild = pointerToChild;
		pointerToPivot -> leftChild = pointerToTreeFromChild;
		pointerToChild -> rightChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance = 0;
	}
	//if pivot is a rightChild
	else if (search.path[search.pivotIndex -1] -> rightChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = search.path[search.pivotIndex + 1];
		TreeNode* pointerToTreeFromChild = search.path[search.pivotIndex + 1] -> rightChild;
		
		search.path[search.pivotIndex -1] -> rightChild = pointerToChild;
		pointerToPivot -> leftChild = pointerToTreeFromChild;
		pointerToChild -> rightChild = pointerToPivot;
		search.path[search.pivotIndex] -> balance = 0;
	}
}

//does the double left right rotation for the AVL tree
//pre search path and treep points to AVL tree
//post checks if pivot is root, leftchild or rightchild
//     rotates the unbalanced tree to the left and then right
//     the AVL tree is balanced
//usage doubleLeftRightRotation(search, root);
void doubleLeftRightRotation(SearchPath& search, TreeNode*& treep)
{
	//if pivot is root
	if (search.pivotIndex == 0)
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> leftChild;
		TreeNode* pointerToGrandChild = pointerToChild -> rightChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		treep = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToChild;
		pointerToGrandChild -> rightChild = pointerToPivot;
		pointerToChild -> rightChild = pointerToLeftGrandChild;
		pointerToPivot -> leftChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance += 2;
	}
	 //if pivot is a leftChild
	else if (search.path[search.pivotIndex -1] -> leftChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> leftChild;
		TreeNode* pointerToGrandChild = pointerToChild -> rightChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		search.path[search.pivotIndex - 1] -> leftChild = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToChild;
		pointerToGrandChild -> rightChild = pointerToPivot;
		pointerToChild -> rightChild = pointerToLeftGrandChild;
		pointerToPivot -> leftChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance += 2;
	}		
	
	//if pivot is a rightChild
	else if (search.path[search.pivotIndex -1] -> rightChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> leftChild;
		TreeNode* pointerToGrandChild = pointerToChild -> rightChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		search.path[search.pivotIndex - 1] -> rightChild = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToChild;
		pointerToGrandChild -> rightChild = pointerToPivot;
		pointerToChild -> rightChild = pointerToLeftGrandChild;
		pointerToPivot -> leftChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance += 2;
	}
}

//does the double right left rotation for the AVL tree
//pre search path and treep points to AVL tree
//post checks if pivot is root, leftchild or rightchild
//     rotates the unbalanced tree to the right and then left
//     the AVL tree is balanced
//usage doubleRightLeftRotation(search, root);
void doubleRightLeftRotation(SearchPath& search, TreeNode*& treep)
{
	//if pivot is root
	if (search.pivotIndex == 0)
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> rightChild;
		TreeNode* pointerToGrandChild = pointerToChild -> leftChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		treep = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToPivot;
		pointerToGrandChild -> rightChild = pointerToChild;
		pointerToChild -> leftChild = pointerToLeftGrandChild;
		pointerToPivot -> rightChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance -= 2;
	}
	 //if pivot is a leftChild
	else if (search.path[search.pivotIndex -1] -> leftChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> rightChild;
		TreeNode* pointerToGrandChild = pointerToChild -> leftChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		search.path[search.pivotIndex - 1] -> leftChild = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToPivot;
		pointerToGrandChild -> rightChild = pointerToChild;
		pointerToChild -> leftChild = pointerToLeftGrandChild;
		pointerToPivot -> rightChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance -= 2;
	}		
	
	//if pivot is a rightChild
	else if (search.path[search.pivotIndex -1] -> rightChild == search.path[search.pivotIndex])
	{
		TreeNode* pointerToPivot = search.path[search.pivotIndex];
		TreeNode* pointerToChild = pointerToPivot -> rightChild;
		TreeNode* pointerToGrandChild = pointerToChild -> leftChild;
		TreeNode* pointerToLeftGrandChild = pointerToGrandChild -> leftChild;
		TreeNode* pointerToRightGrandChild = pointerToGrandChild -> rightChild;
		
		search.path[search.pivotIndex - 1] -> rightChild = pointerToGrandChild;
		pointerToGrandChild -> leftChild = pointerToPivot;
		pointerToGrandChild -> rightChild = pointerToChild;
		pointerToChild -> leftChild = pointerToLeftGrandChild;
		pointerToPivot -> rightChild = pointerToRightGrandChild;
		search.path[search.pivotIndex] -> balance -= 2;
	}
}

//constructor for AVL Tree
//pre none
//post AVL Tree exists
//usage AVL mytree;
AVLTree::AVLTree()
{
		
}

//destructor for AVL Tree
//pre AVL Tree exists
//post memory has been freed
//usage will call automatically 
AVLTree::~AVLTree()
{
		
}


//adds new item to the AVL tree
//pre item is assigned 
//post item is added to the AVL tree 
//     search path has been made
//     checks to see which case AVL tree belongs
//     item is added to AVL tree
//     tree is balanced
//usage mytree.addNewEntry(anItem);
void AVLTree::addNewEntry(const Item& newItem) throw (Exception)
{
		SearchPath search;
		
		addNewEntryAndMakeSearchPath(newItem, root, search);
		
		if(hasNoPivot(search))
		{
			fixBalances(search, 0);
		}			
		else if (isAddedToShortSide(search))
		{
			fixBalances(search, search.pivotIndex);
		}	
		else if (isSingleRotateLeft(search))
		{
			singleLeftRotation(search, root);
			fixBalances(search, search.pivotIndex + 2);
		}
		else if (isSingleRotateRight(search))
		{
			singleRightRotation(search, root);
			fixBalances(search, search.pivotIndex + 2);
		}
			
		else if (isDoubleRotateLeftRight(search))
		{
			doubleLeftRightRotation(search, root);
			fixBalances(search, search.pivotIndex + 3);
		}
			
		else
		{
			doubleRightLeftRotation(search, root);
			fixBalances(search, search.pivotIndex + 3);
		}
			
}

//prints the AVL tree in a pretty display
//pre AVL tree exists
//post AVL tree is printed in a pretty manner
//usage mytree.prettyDisplay(outfile);
void AVLTree::prettyDisplay(ostream& output)
{
		output << endl;
		writePretty(root, 0, output);
		output << endl;
}

