/**
 * BinaryTreeNode.h
 *
 *  Created on: Apr 26, 2017
 *      Author: Benjamin Kleinberg
 */

#ifndef BINARYTREENODE_H_
#define BINARYTREENODE_H_

#include"int.h"

#include<iostream>
using std::ostream;

class BinaryTreeNode {
public:

	Int key;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode* parent;

	BinaryTreeNode(Int nKey = 0);
	virtual ~BinaryTreeNode();

	virtual void print(ostream& out);

	friend ostream& operator<<(ostream& out, BinaryTreeNode &node);
};

#endif /* BINARYTREENODE_H_ */
