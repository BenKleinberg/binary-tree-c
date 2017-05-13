/*
 * redblacknode.h
 *
 *  Created on: Apr 27, 2017
 *      Author: Benjamin Kleinberg
 */

#ifndef REDBLACKNODE_H_
#define REDBLACKNODE_H_

#include"int.h"
#include"binarytreenode.h"

#include<iostream>
using std::ostream;

class RedBlackNode : public BinaryTreeNode {
public:
	int color;

	RedBlackNode(Int key, int nColor = 0);
	virtual ~RedBlackNode();

	virtual void print(ostream& out);

	friend ostream& operator<<(ostream& out, RedBlackNode& node);
};

namespace RedBlack {

	static const int RED = 0;
	static const int BLACK = 1;
	static const int BLACK_BLACK = 2;

}

#endif /* REDBLACKNODE_H_ */
