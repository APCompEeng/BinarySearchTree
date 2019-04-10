// avltree.h
//Author: Adam Pesch

#ifndef AVLTREE_H
#define AVLTREE_H

#include "item.h"
#include "treenode.h"
#include "binarytree.h"
#include "exception.h"
#include "binarysearchtree.h"

struct SearchPath;

class AVLTree: public BinarySearchTree
{
	public:
	
	AVLTree();
	
	~AVLTree();
	
	void addNewEntry(const Item& newItem) throw (Exception);
	
	void prettyDisplay(ostream& output);
	
};
#endif