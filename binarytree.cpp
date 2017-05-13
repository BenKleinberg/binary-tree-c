/*
 * binarytree.cpp
 *
 *  Created on: Apr 26, 2017
 *      Author: Benjamin Kleinberg
 */

#include "binarytree.h"

using std::bad_alloc;


BinaryTreeNode* BinaryTree::__savedNodes = 0;

/**
 * Returns a node with the given key value.
 * If there is a node saved, then one is pulled from the list.
 * Otherwise, a new node is created.
 *
 * @param val the key value for the new node
 *
 * @return a pointer to the node that was made
 */
BinaryTreeNode* BinaryTree::makeNode(Int val) {
	BinaryTreeNode* node = 0;

	if(__savedNodes) {
		node = __savedNodes;
		__savedNodes = __savedNodes->parent;
		node->key = val;
		node->parent = 0;
	}

	else {
		try {
			node = new BinaryTreeNode(val);

		} catch(bad_alloc &ex) {
			node = 0;
		}
	}

	return node;
}

/**
 * Saves the given node into the list of nodes.
 *
 * @param node the node to save
 */
void BinaryTree::saveNode(BinaryTreeNode* node) {
	if(node) {
		node->key = Int::NAN;
		node->left = 0;
		node->right = 0;
		node->parent = __savedNodes;
		__savedNodes = node;
	}
}

/**
 * Deletes all the nodes saved for later insertions to free space.
 */
void BinaryTree::deleteSavedNodes() {
	delete __savedNodes;
	__savedNodes = 0;
}

/**
 * Counts the number of saved nodes and returns the count.
 */
int BinaryTree::numSavedNodes() {
	int count = 0;
	BinaryTreeNode* curr = __savedNodes;
	while(curr) {
		curr = curr->parent;
		count++;
	}

	return count;
}



/**
 * Basic constructor
 */
BinaryTree::BinaryTree() {
	_root = 0;
}

/**
 * Destructor to save all the nodes the tree used.
 */
BinaryTree::~BinaryTree() {
	saveTree(_root);
	_root = 0;
}

/**
 * Saves the entire subtree into the list of nodes.
 * Recursively calls itself to save all nodes in the subtree.
 *
 * @param root a pointer to the root of the subtree to save
 */
void BinaryTree::saveTree(BinaryTreeNode* root) {
	if(root) {
		saveTree(root->left);
		saveTree(root->right);
		saveNode(root);
	}
}

/**
 * Finds the node with the given key value and returns it.
 *
 * @param val the key value to search for
 *
 * @return a pointer to the node with the given key
 * @return null if the key does not exist in the tree
 */
BinaryTreeNode* BinaryTree::search(Int val) {
	BinaryTreeNode* node = _root;

	while(node && node->key != val) {
		if(val < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

/**
 * Finds the node with the minimum key value and returns it.
 *
 * @return a pointer to the node with the minimum key
 * @return null if the tree is empty
 */
BinaryTreeNode* BinaryTree::min() {
	return min(_root);
}

/**
 * From the given subtree,
 * finds the node with the minimum key value and returns it.
 *
 * @param root a pointer to the node the subtree is rooted at
 *
 * @return a pointer to the node with the minimum key
 * @return null if the subtree is null
 */
BinaryTreeNode* BinaryTree::min(BinaryTreeNode* root) {
	while(root && root->left)
		root = root->left;

	return root;
}

/**
 * Finds the node with the maximum key value and returns it.
 *
 * @return a pointer to the node with the maximum key
 * @return null if the tree is empty
 */
BinaryTreeNode* BinaryTree::max() {
	return max(_root);
}

/**
 * From the given subtree,
 * finds the node with the maximum key value and returns it.
 *
 * @param root a pointer to the node the subtree is rooted at
 *
 * @return a pointer to the node with the maximum key
 * @return null if the subtree is null
 */
BinaryTreeNode* BinaryTree::max(BinaryTreeNode* root) {
	while(root && root->right)
		root = root->right;

	return root;
}

/**
 * Finds the successor of the given node and returns it.
 *
 * @param node a pointer to the node to find the successor of
 *
 * @return a pointer to the node that is the successor of the given node
 * @return null if the given node is null
 * @return null if there is no successor
 */
BinaryTreeNode* BinaryTree::successor(BinaryTreeNode* node) {
	BinaryTreeNode* succ = 0;

	if(node) {
		//If there is a right child, the minimum node in its subtree is the successor
		if(node->right)
			succ = min(node->right);

		//Otherwise, trace the tree up until the node is its parent's left child
		//The parent node is the successor
		//If null is reached, the node has no successor
		else {
			succ = node->parent;

			while(succ && node == succ->right) {
				node = succ;
				succ = succ->parent;
			}
		}
	}

	return succ;
}

/**
 * Finds the predecessor of the given node and returns it.
 *
 * @param node a pointer to the node to find the predecessor of
 *
 * @return a pointer to the node that is the predecessor of the given node
 * @return null if the given node is null
 * @return null if there is no predecessor
 */
BinaryTreeNode* BinaryTree::predecessor(BinaryTreeNode* node) {
	BinaryTreeNode* pred = 0;

	if(node) {
		//If there is a left child, the maximum node in its subtree is the predecessor
		if(node->left)
			pred = max(node->left);

		else {
			pred = node->parent;

			//Otherwise, trace the tree up until the node is its parent's right child
			//The parent node is the predecessor
			//If null is reached, the node has no predecessor
			while(pred && node == pred->left) {
				node = pred;
				pred = pred->parent;
			}
		}
	}

	return pred;
}

/**
 * Inserts the given value into the tree and returns whether it succeeds.
 *
 * @param val the key value to insert into the tree
 *
 * @return boolean value for whether the value was successfully inserted
 * 		0 is failure, 1 is success
 */
int BinaryTree::insertVal(Int val) {
	int success = 0;
	BinaryTreeNode* node = makeNode(val);

	if(node) {
		insertNode(node);
		success = 1;
	}

	return success;
}

/**
 * Inserts the given node into the tree.
 *
 * @param node a pointer to the node to insert into the tree
 */
void BinaryTree::insertNode(BinaryTreeNode* node) {
	BinaryTreeNode* search = _root;
	BinaryTreeNode* parent = 0;

	if(node) {
		//If there is no root, make the node the root
		if(_root == 0)
			_root = node;

		//Otherwise, trace down the tree until null is found
		else {
			while(search) {
				parent = search;

				if(node->key < search->key)
					search = search->left;
				else
					search = search->right;
			}

			//Update the pointers for the appropriate location
			node->parent = parent;
			if(node->key < parent->key)
				parent->left = node;
			else
				parent->right = node;
		}
	}

}

/**
 * Deletes the given key value from the tree and returns whether it was found.
 *
 * @param val the key value of the node to delete
 *
 * @return boolean value for whether a node was found and deleted
 * 		0 is failure, 1 is success
 */
int BinaryTree::deleteVal(Int val) {
	int success = 0;
	BinaryTreeNode* node = search(val);

	if(node) {
		saveNode(deleteNode(node));
		success = 1;
	}

	return success;
}

/**
 * Deletes the given node from the tree and saves it for later insertions.
 *
 * @param node the node to be removed from the tree
 *
 * @return the node that was actually removed from the tree
 */
BinaryTreeNode* BinaryTree::deleteNode(BinaryTreeNode* node) {
	BinaryTreeNode* removed = 0;
	BinaryTreeNode* replacement = 0;

	if(node) {
		//If the node has both children, then the node to be removed is its successor
		//Otherwise, the node itself is removed
		if(node->left == 0 || node->right == 0)
			removed = node;
		else
			removed = successor(node);

		//The replacement node should be whichever child exists
		if(removed->left)
			replacement = removed->left;
		else
			replacement = removed->right;
		//If the child exists, set its parent to the removed node's parent
		if(replacement)
			replacement->parent = removed->parent;

		//If the removed node is the root, set the root to the replacement node
		if(removed->parent == 0)
			_root = replacement;
		//Otherwise, set the parent's appropriate child to be the replacement node
		else {
			if(removed == removed->parent->left)
				removed->parent->left = replacement;
			else
				removed->parent->right = replacement;
		}

		//If the node that was removed was not the original node, set the node's
		//key to be that of the removed node
		if(removed != node)
			node->key = removed->key;
	}

	return removed;
}

/**
 * Prints the tree to the given ostream using in-order traversal.
 *
 * @param out the ostream to print the tree to
 */
void BinaryTree::printTreeInOrder(ostream& out) {
	printSubtreeInOrder(_root, out);
	out<< "\n";
}

/**
 * Prints the subtree tree at the given root to the given ostream using in-order traversal
 * Recursively calls itself to reach the leaves.
 *
 * @param root a pointer to the subtree to print
 * @param out the ostream to print to
 */
void BinaryTree::printSubtreeInOrder(BinaryTreeNode* root, ostream &out) {
	if(root) {
		if(root->left) {
			printSubtreeInOrder(root->left, out);
			out<< " ";
		}
		root->print(out);
		if(root->right) {
			out<< " ";
			printSubtreeInOrder(root->right, out);
		}
	}
}

/**
 * Prints the tree to the given ostream.
 * Uses a '/' to represent null nodes.
 *
 * @param out the ostream to print the tree to
 */
void BinaryTree::printTree(ostream &out) {
	int depth = 0;
	int count = 0;

	//Print the tree one level at a time until a level is empty
	do {
		count = printDepth(_root, depth, out);
		out<< "\n";
		depth++;
	} while(count);
}

/**
 * Prints the subtree rooted at the given node at the given depth to the given ostream,
 * and returns how many children to be printed.
 * Recursively calls itself to reach the correct depth.
 *
 * @param root the root of the subtree to print
 * @param depth how many levels down to be printed
 * @param out the ostream to print to
 *
 * @return the number of children to be printed
 */
int BinaryTree::printDepth(BinaryTreeNode* root, int depth, ostream &out) {
	int count = 0;

	//If the root exists, recursively print its children
	if(root) {
		if(depth) {
			count += printDepth(root->left, depth - 1, out);
			count += printDepth(root->right, depth - 1, out);
		}
		else {
			root->print(out);
			out<< " ";
			count = (root->left ? 1 : 0) + (root->right ? 1 : 0);
		}
	}

	//Otherwise, print a null character if this is the desired depth
	else if(depth == 0)
		out<< "/ ";

	return count;
}
