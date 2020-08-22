#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#pragma once

#include "Account.h"

using namespace std;

class BinarySearchTree
{
public:
	//constructors
	BinarySearchTree();

	//copy constructor
	BinarySearchTree(const BinarySearchTree& other);

	~BinarySearchTree();

	//actions for the class
	bool Insert(Account*& accountPtr);
	bool Retrieve(const int&, Account*&) const;
	void Display() const;
	void Empty();
	bool isEmpty() const;
	bool Remove(const int& id);

	//overloaded assignment operator
	BinarySearchTree& operator=(const BinarySearchTree& other);

private:
	struct Node
	{
		Account* account = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;
	};
	Node* root = nullptr;

	//helper functions used for the main functions of the Tree above
	Node* Insert(Account* accountPtr, Node* rootN);
	bool Retrieve(const int& accountId, Account*& target, Node* rootN) const;
	void Empty(Node* rootN);
	void Display(Node* rootN) const;
	bool Remove(int id, Node*& node);
	Account delSmallest(Node*& node);
	void deleteNode(Node*& node);
	void copyContents(Node* currRoot, Node* otherRoot);
	void assignHelperFunc(Node* rootN);
	
};


#endif