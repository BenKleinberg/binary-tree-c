/*
 * redblacknode.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: Benjamin Kleinberg
 */

#include"redblacknode.h"
#include"binarytreenode.h"
#include"int.h"

#include<iostream>
using std::ostream;
using namespace RedBlack;

RedBlackNode::RedBlackNode(Int nKey, int nColor) : BinaryTreeNode(nKey) {
	color = nColor;
}

RedBlackNode::~RedBlackNode() {
}

void RedBlackNode::print(ostream& out) {
	BinaryTreeNode::print(out);

	if(color == RED)
		out<< "R";
	else if(color == BLACK)
		out<< "B";
	else
		out<< "BB";
}

ostream& operator<<(ostream& out, RedBlackNode& node) {
	node.print(out);

	return out;
}
