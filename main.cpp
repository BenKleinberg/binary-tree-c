/*
 * main.cpp
 *
 *  Created on: Apr 26, 2017
 *      Author: Benjamin Kleinberg
 */

#include"binarytree.h"
#include"redblacktree.h"
#include"command.h"

#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

void assertInt(BinaryTreeNode* node, Int val) {
	assert(node != 0);
	assert(node->key == val);
	cout<< val << " found" << endl;
}

int main() {

	RedBlackTree myTree;
	BinaryTreeNode* node;
	int loop = 1;
	string input;
	Command cmd;

	cout<< "Red Black Tree Tester" << endl << endl;

	while(loop) {
		cout<< ">";
		getline(cin, input);

		if(cmd.readCommand(input.c_str())) {

			switch(cmd.flag) {

			case 'R':
				if(cmd.num < 1)
					cout<< "An integer is needed to rotate a node right." << endl;
				else {
					RedBlackNode* node = dynamic_cast<RedBlackNode*>(myTree.search(cmd.arguments[0]));

					if(node)
						myTree.rotateRight(node);
					else
						cout<< "Could not find " << cmd.arguments[0] << "." << endl;
				}
				break;

			case 'L':
				if(cmd.num < 1)
					cout<< "An integer is needed to rotate a node left." << endl;
				else {
					RedBlackNode* node = dynamic_cast<RedBlackNode*>(myTree.search(cmd.arguments[0]));

					if(node)
						myTree.rotateLeft(node);
					else
						cout<< "Could not find " << cmd.arguments[0] << "." << endl;
				}
				break;

			case 'I':
				if(cmd.num < 1)
					cout<< "An integer is needed to insert into the tree." << endl;
				else
					myTree.insertVal(cmd.arguments[0]);
				break;

			case 'D':
				if(cmd.num < 1)
					cout<< "An integer is needed to delete from the tree." << endl;
				else {
					if(myTree.deleteVal(cmd.arguments[0]))
						cout<< cmd.arguments[0] << " successfully deleted." << endl;
					else
						cout<< "Could not find " << cmd.arguments[0] << "." << endl;
				}
				break;

			case 'S':
				if(cmd.num < 1)
					cout<< "An integer is needed to search the tree." << endl;
				else {
					if(myTree.search(cmd.arguments[0]))
						cout<< cmd.arguments[0] << " found." << endl;
					else
						cout<< cmd.arguments[0] << " not found." << endl;
				}
				break;

			case 'M':
				node = myTree.max();
				if(node)
					cout<< "The maximum value in the tree is " << node->key << endl;
				else
					cout<< "The tree is empty." << endl;
				break;

			case 'm':
				node = myTree.min();
				if(node)
					cout<< "The minimum value in the tree is " << node->key << endl;
				else
					cout<< "The tree is empty." << endl;
				break;

			case 'P':
				myTree.printTree(cout);
				break;

			case 'p':
				myTree.printTreeInOrder(cout);
				break;

			case 'Q':
				loop = 0;
				break;

			default:
				cout<< "Command not found." << endl;
			}
		}

		else
			cout<< "Invalid command. Error on argument " << -cmd.num << "." << endl;
	}


	return 0;
}


