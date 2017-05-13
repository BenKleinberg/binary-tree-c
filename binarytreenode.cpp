/*
 * BinaryTreeNode.cpp
 *
 *  Created on: Apr 26, 2017
 *      Author: Benjamin Kleinberg
 */

#include "binarytreenode.h"

#include<iostream>
using std::ostream;

BinaryTreeNode::BinaryTreeNode(Int nKey) {
	key = nKey;
	left = 0;
	right = 0;
	parent = 0;
}

BinaryTreeNode::~BinaryTreeNode() {
	delete left;
	delete right;
	delete parent;
}

void BinaryTreeNode::print(ostream& out) {
	out<< key;
}

ostream& operator<<(ostream& out, BinaryTreeNode &node) {
	node.print(out);

	return out;
}
