/*
 * binarytree.h
 *
 *  Created on: Apr 26, 2017
 *      Author: Benjamin Kleinberg
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include"binarytreenode.h"

#include<iostream>
using std::ostream;

class BinaryTree {
protected:
	//Linked list of tree nodes to save on deletion. Follows the parent link.
	static BinaryTreeNode* __savedNodes;

	static void saveNode(BinaryTreeNode* node);
	static BinaryTreeNode* makeNode(Int val);


	BinaryTreeNode* _root;

	BinaryTreeNode* min(BinaryTreeNode* root);
	BinaryTreeNode* max(BinaryTreeNode* root);
	virtual void insertNode(BinaryTreeNode* node);
	BinaryTreeNode* deleteNode(BinaryTreeNode* node);
	void saveTree(BinaryTreeNode* root);
	void printSubtreeInOrder(BinaryTreeNode* root, ostream &out);
	int printDepth(BinaryTreeNode* root, int depth, ostream &out);

public:
	static void deleteSavedNodes();
	static int numSavedNodes();


	BinaryTree();
	virtual ~BinaryTree();

	BinaryTreeNode* search(Int val);
	BinaryTreeNode* min();
	BinaryTreeNode* max();
	BinaryTreeNode* successor(BinaryTreeNode* node);
	BinaryTreeNode* predecessor(BinaryTreeNode* node);
	virtual int insertVal(Int val);
	virtual int deleteVal(Int val);
	void printTreeInOrder(ostream& out);
	void printTree(ostream& out);

};

#endif /* BINARYTREE_H_ */
