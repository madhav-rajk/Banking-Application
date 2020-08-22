#include "BinarySearchTree.h"

//no-arg constructor does nothing
BinarySearchTree::BinarySearchTree()
{

}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
{
	if (other.root == nullptr)
	{
		root = nullptr;
	}
	else
	{
		copyContents(this->root, other.root);
	}
}

//removes all the elements in the tree, by calling the Empty method
BinarySearchTree::~BinarySearchTree()
{
	Empty();
}

/*
Purpose is to insert the particular account into the BS Tree. If the root 
is empty, then just adds a Node at the root, else calls the recursive helper
method, and then later returns false. 
*/
bool BinarySearchTree::Insert(Account*& accountPtr)
{
	if (root == nullptr)
	{
		Node* temp = new Node();
		temp->account = accountPtr;
		root = temp;
		return true;
	}
	else
	{
		Insert(accountPtr, root);
	}
	return false;
}

/*
Recursive helper method for inserting. First, if the given root is null, 
then just adds a Node at the root, else, checks if the given account's ID
is less than the ID of account at the root, then go left recursively, else
go right. Then, at the end of the if/else, returns the rootN.
*/
BinarySearchTree::Node* BinarySearchTree::Insert(Account* accountPtr, 
													Node* rootN)
{
	if (rootN == nullptr)
	{
		Node* temp = new Node();
		temp->account = accountPtr;
		temp->left = nullptr;
		temp->right = nullptr;
		rootN = temp;
		return temp;
	}
	else
	{
		if (accountPtr->getId() < rootN->account->getId())
		{
			rootN->left = Insert(accountPtr, rootN->left);
		}
		else
		{
			rootN->right = Insert(accountPtr, rootN->right);
		}
	}

	return rootN;
}

/*
Given the particular account ID and the target account to change, we make a 
temp Node which represents the root, and then we call the recursive helper 
method, which takes the ID, Account to change and the temp representing the 
root.
*/
bool BinarySearchTree::Retrieve(const int& accountId, Account*& target) const
{
	Node* temp = root;
	return Retrieve(accountId, target, temp);
}


/*
If the given parameter's root is not empty, then if the first account's ID
is equal to the ID at the root, then we take that account as the target 
account that is set. If not, then if the ID is less than root's ID, then 
go recursively left else go recursively right. Set the target to nullptr
and return false, since clearly the retrieval was not successful.
*/
bool BinarySearchTree::Retrieve(const int& accountId, Account*& target,
								Node* rootN) const
{
	if (rootN != nullptr)
	{
		if (accountId == rootN->account->getId())
		{
			target = rootN->account;
			return true;
		}
		else if (accountId < rootN->account->getId())
		{
			return Retrieve(accountId, target, rootN->left);
		}
		else
		{
			return Retrieve(accountId, target, rootN->right);
		}
	}

	target = nullptr;
	return false;
}

/*
Calls the recursive display method which takes the root and prints the account
at the root.
*/
void BinarySearchTree::Display() const
{
	Display(root);
}

/*
if the root is not null, then calls the method recursively left, then 
we know that when we reach a not null root, then we will go to the next 
step where prints the account details, then we call the method recursively
right. 
*/
void BinarySearchTree::Display(Node* rootN) const
{
	if (rootN != nullptr)
	{
		Display(rootN->left);
		cout << *rootN->account << endl;
		Display(rootN->right);
	}
}

/*
calls the empty recursive method, which will reomve all the content from 
the Tree.
*/
void BinarySearchTree::Empty()
{
	Empty(root);
}

/*
Takes the root through the parameter and if the root is not null, then
Empty recursively left, then right, and then deletes the account at the 
root, and also deletes the root object. 
*/
void BinarySearchTree::Empty(Node* rootN)
{
	if (rootN != nullptr)
	{
		Empty(rootN->left);
		Empty(rootN->right);
		delete rootN->account;
		delete rootN;
	}
}

//returns if tree is empty, by checking if root is null
bool BinarySearchTree::isEmpty() const
{
	return (root == nullptr);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
	if (this != &other)
	{
		this->Empty();
		Node* temp = other.root;
		assignHelperFunc(temp);
	}
	return *this;
}

//transfers all the account object content from the other node to this Node,
//making sure the Node is not null. If not null, then we first insert the 
//account, then recursively call left and right to add account there 
//accordingly.
void BinarySearchTree::assignHelperFunc(Node* rootN)
{
	if (rootN != nullptr)
	{
		this->Insert(rootN->account);
		assignHelperFunc(rootN->left);
		assignHelperFunc(rootN->right);
	}
}

/*
Takes the ID as the parameter and calls the recursive helper method to look
for the ID and remove it from the given Node root when we find the ID.
*/
bool BinarySearchTree::Remove(const int& id)
{
	return Remove(id, root);
}

/*
Checks if the node is null then returns false, else checks if the given ID
is equal to the ID of the Node, and if so, then returns true and deletes 
the Node, else goes left or right recursively based on the condition.
*/
bool BinarySearchTree::Remove(int id, Node*& node)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->account->getId() == id)
	{
		deleteNode(node);
		return true;
	}
	if (node->account->getId() > id)
	{
		return Remove(id, node->left);
	}
	else
	{
		return Remove(id, node->right);
	}

}

/*
Checks to see if both left and right side of the node are null, then deletes
the account and the actual node and sets the node to nullptr. Then, checks 
if the left and right side of the node are null and if so, then deletes the
appropriate nodes. Then, sets the account at the current node to the smallest
node that is to be deleted.
*/
void BinarySearchTree::deleteNode(Node*& node)
{
	if ((node->left == nullptr) && (node->right == nullptr))
	{
		delete node->account;
		delete node;
		node = nullptr;
		return;
	}
	if (node->left == nullptr)
	{
		Node* temp = node;
		node = node->right;
		delete temp->account;
		delete temp;
		return;
	}
	if (node->right == nullptr)
	{
		Node* temp = node;
		node = node->left;
		delete temp->account;
		delete temp;
		return;
	}
	*node->account = delSmallest(node->right);
}

/*
Searches through to find the smallest node to replace the node that we will
delete.
*/
Account BinarySearchTree::delSmallest(Node*& node)
{
	if (node->left == nullptr)
	{
		Node* temp = node;
		node = node->right;
		Account acc = *temp->account;
		delete temp->account;
		delete temp;
		return acc;
	}
	return delSmallest(node->left);
}

//copies all the account and the left right from the current node to the 
//other node
void BinarySearchTree::copyContents(Node* currRoot, Node* otherRoot)
{
	if (otherRoot == nullptr)
	{
		currRoot = nullptr;
	}
	else
	{
		currRoot = new Node();
		currRoot->account = otherRoot->account;
		copyContents(currRoot->left, otherRoot->left);
		copyContents(currRoot->right, otherRoot->right);
	}
}
