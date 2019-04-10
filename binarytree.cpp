
//file binarytree.cpp
//author Adam Pesch
//date October 16, 2018

//data object: a binary tree which is YOU DO
//data structure: a linked binary tree
//operations: (a scaled-down version)
//            create, destroy, copy, operator=,
//            traversals (preorder, inorder, postorder)
// Contract: Assumes the this class can access private data members of class Node.
//    Those data members are: Item item, Node* leftptr, Node* rightptr.
//    There is a constructor that allows caller to give item, left and right ptrs.

#include "binarytree.h"
#include <iostream>
#include <fstream>
using namespace std;

// ***************** recursive helpers *****************

//Copies one binary tree to another
//pre oldtreep points to the root of a binary tree
//post: newtreep points to the root of a binary tree
//  that has copies of the nodes of oldtreep's tree
//usage: copyTree (newptr, oldptr);
void copyTree (TreeNode*& newtreep, TreeNode* oldtreep) throw (Exception)
{	
    Item item;
	
	if(oldtreep == nullptr)
	{
		
	}
	else
	{
		newtreep = new (nothrow) TreeNode(item, nullptr, nullptr);
        if (newtreep == nullptr)
	{
		throw Exception("no memory in the heap for new tree");
	}		
		newtreep -> item = oldtreep -> item;
		copyTree(newtreep -> leftChild, oldtreep -> leftChild);
		copyTree(newtreep -> rightChild, oldtreep -> rightChild);
	}

}

//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyTree (mroot);
void destroyTree (TreeNode*& treep)
{
	//post order traversal
	if(treep != nullptr)
	{
		destroyTree(treep -> leftChild);
		destroyTree(treep -> rightChild);
		delete treep;
		treep = nullptr;
	}
}

// recursive helper for prettyDisplay
//pre: treep points to the root of a binary tree, level indicates 
//	  what level of the tree we're on
//post: prints the tree in an easy to read fashion
//usage: writePretty(root, 0);
void writePretty (TreeNode* treep, int level)
{
	if (treep != nullptr)
	{
		writePretty(treep -> rightChild, level += 1);
		if (treep -> rightChild != nullptr)
		{
			for (int j = 0 ;j <= level; j++)
				cout << '\t';
			cout << "/" << endl;
		}
		if (level == 1)
			cout << "root ->" ;
		else	
		{			
			for (int i = 0; i < level; i++)
				cout << '\t' ;
		}
		Key text = treep -> item;
		cout << "  " << text << endl;
		 if (treep -> leftChild != nullptr)
        {
            for (int i = 0; i <= level; i++)
                cout << '\t';
            cout << "\\" << endl;
			writePretty(treep -> leftChild, level);
		}
	}		

}

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     preorder order. the items are separated by commas
//usage: preorder (mroot);   
void preorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		cout << treep -> item << endl;
		preorder(treep -> leftChild);
		preorder(treep -> rightChild);
	}
}

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     inorder order. the items are separated by commas
//usage: inorder (mroot);   
void inorder (TreeNode* treep, ostream& output)
{
	if (treep != nullptr)
	{
		inorder(treep -> leftChild, output);
		output << treep -> item << endl;
		inorder(treep -> rightChild, output);
	}
}

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     postorder order. the items are separated by commas
//usage: postorder (mroot); 
void postorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		postorder(treep -> leftChild);
		postorder(treep -> rightChild);
		cout << treep -> item << endl;
	}
}

// **************************public methods************************

//creates an empty binary tree
//post: object is an empty binary tree
//usage: BinaryTree zags;
BinaryTree::BinaryTree()
{
   root = nullptr;
}

//creates a new binary tree that is a copy of an existing tree
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: BinaryTree zags (bulldog);
BinaryTree::BinaryTree(const BinaryTree& rightHandSideTree) throw (Exception)
{
   root = nullptr;
   copyTree(root, rightHandSideTree.root);
}

//releases the memory of a binary tree
//pre: object exists
//post: memory for the object has been released. object theoretically does not exist
//       but in practice, it is empty.
BinaryTree::~BinaryTree()
{
   destroyTree(root);
}

// ******************** member functions ********************************************
//@pre: binary tree object exists
// **********************************************************************************

//checks for an empty tree
//pre: binary tree object exists
//post: returns true if the object is empty; else returns false
//usage: if (tree.isEmpty())
bool BinaryTree::isEmpty() const
{
   return (root == nullptr);
}

//copies one tree to another
//pre: rightHandSideTree is an assigned tree.
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: atree = btree = ctree;
BinaryTree& BinaryTree::operator=(const BinaryTree& rightHandSideTree) throw (Exception)
{
	destroyTree(root);
	root = nullptr;
	copyTree(root, rightHandSideTree.root);
	
	return *this;
}

//prints the tree to look like a computer science tree
//post: outputs the tree as in the example below
//
//                        bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: tree.prettyDisplay();
void BinaryTree::prettyDisplay()
{
	cout << endl;
	writePretty(root, 0);
	cout << endl;
}

//pre: binary tree object exists
//post: prints the objects in the tree in preorder
//usage: tree.preorderTraverse();  
void BinaryTree::preorderTraverse ()
{
	preorder(root);
}

//pre: binary tree object exists
//post: prints the objects in the tree in inorder
//usage: tree.preorderTraverse();  
void BinaryTree::inorderTraverse(ostream& output)
{
	inorder(root, output);
}

//pre: binary tree object exists
//post: prints the objects in the tree in postorder
//usage: tree.preorderTraverse(); 
void BinaryTree::postorderTraverse()
{
	postorder(root);
}

//makes a full binary tree of height 2
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a full binary tree of height 2
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: makeFullTreeHeight2(mytree, infile);
void BinaryTree::makeFullTreeHeight2(istream& input) throw (Exception)
{
   Item newguy;
   
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr); 
   
   if(root == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the root of the tree");
   }
   
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
}

//makes a full binary tree of height 3
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a full binary tree of height 3
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: makeFullTreeHeight3(mytree, infile);
void BinaryTree::makeFullTreeHeight3(istream& input) throw (Exception)
{
   Item newguy;
   
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr); 
   
   if(root == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the root of the tree");
   }
   
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
   
   input >> newguy;
   root -> leftChild -> leftChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> leftChild -> rightChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
   
   input >> newguy;
   root -> rightChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
}

//makes a complete but not full binary tree of height 3 
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a complete tree of height 3
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: makeCompleteTreeHeight3(mytree, infile);
void BinaryTree::makeCompleteTreeHeight3(istream& input) throw (Exception)
{
   Item newguy;
   
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr); 
   
   if(root == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the root of the tree");
   }
   
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
   
   input >> newguy;
   root -> leftChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of left child of the tree");
   }   
   else
   {
	   throw Exception("I am throwing an exception at you, Dr. Y. Do you have your catcher's mitt ready?");
   }
   
}

//makes a complete but not full binary tree of height 4 
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a complete tree of height 4
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: makeCompleteTreeHeight3(mytree, infile);
void BinaryTree::makeCompleteTreeHeight4(istream& input) throw (Exception)
{
   Item newguy;
   
   //level 1
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr); 
   
   if(root == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the root of the tree");
   }
   
   // level 2
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the tree");
   }   
   
   //level 3
   input >> newguy;
   root -> leftChild -> leftChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the left child of the tree");
   }
   
   input >> newguy;
   root -> leftChild -> rightChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the right child of the left child of the tree");
   }
   
   input >> newguy;
   root -> rightChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the right child of the tree");
   }   
   
   input >> newguy;
   root -> rightChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> rightChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the right child of the right child of the tree");
   }
   
   //level 4
   
   input >> newguy;
   root -> leftChild -> leftChild -> leftChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the left child of the left child of the tree");
   }
   
   input >> newguy;
   root -> leftChild -> leftChild -> rightChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the right child of the left child of the left child of the tree");
   }
   
   input >> newguy;
   root -> leftChild -> rightChild -> leftChild= new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if(root -> leftChild == nullptr)
   {
	   throw Exception("BinaryTree: no memory in the heap for the left child of the right child of the left child of the tree");
   }
   else
   {
	   throw Exception("I am throwing an exception at you, Dr. Y. Do you have your catcher's mitt ready?");
   }
   
}
