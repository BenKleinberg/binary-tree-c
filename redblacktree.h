/*
 * redblacktree.h
 *
 *  Created on: Apr 27, 2017
 *      Author: Benjamin Kleinberg
 *
 *  This is a red black tree structure that inherits from a binary search tree.
 *  A red black tree has the following properties:
 *  1) All the nodes are red or black
 *  2) The root node is black
 *  3) The null leaf nodes are black
 *  4) All red nodes have two black children
 *  5) Every simple path from a node to a null leaf has the same number of black nodes
 *
 *  These properties make the tree approximately balanced, which results in a height
 *  of O(log(n)), where n is the number of elements in the tree.
 */

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include"binarytree.h"
#include"redblacknode.h"
#include"int.h"

class RedBlackTree : public BinaryTree {
private:
	static RedBlackNode* makeNode(Int val, int color);


	virtual void insertNode(RedBlackNode* node);
	void deleteFixup(RedBlackNode* parent, RedBlackNode* error);
	void insertFixup(RedBlackNode* parent, RedBlackNode* error);

public:
	RedBlackTree();
	virtual ~RedBlackTree();

	RedBlackNode* rotateLeft(RedBlackNode* node);
	RedBlackNode* rotateRight(RedBlackNode* node);
	void rotateEdge(RedBlackNode* parent, RedBlackNode* child);

	virtual int insertVal(Int val);
	virtual int deleteVal(Int val);
};

#endif /* REDBLACKTREE_H_ */
