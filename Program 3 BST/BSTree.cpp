#include "BSTree.h"
#include <iostream>

BSTree::BSTree()
{

	root = nullptr;

}

BSTree::~BSTree()
{
	while (root != nullptr)
	{
		remove(root->getPhrase());
	}
}

void BSTree::insert(const string& newString)
{

	Node* newNode = new Node(newString);
	newNode->setCount(1);

	if (root == nullptr)	//if tree is empty, assign newString to root
	{
		root = newNode;
		root->setLeft(nullptr);
		root->setRight(nullptr);

	}
	else
	{
		Node* curr = root;

		while (curr != nullptr)
		{
			if (newNode->getPhrase() < curr->getPhrase())	//going to left child
			{

				if (curr->getLeft() == nullptr)	//found space to insert node
				{
					curr->setLeft(newNode);
					return;
				}
				else
				{
					curr = curr->getLeft();	// proceed to left child
				}

			}

			if (newNode->getPhrase() > curr->getPhrase())	//going to right child
			{

				if (curr->getRight() == nullptr)	//found space to insert node
				{
					curr->setRight(newNode);
					return;
				}

				else
				{
					curr = curr->getRight();	//proceed to right child
				}
			}

			if (curr->getPhrase() == newNode->getPhrase())	//if found duplicate, increment count
			{
				curr->setCount(curr->getCount() + 1);
				return;
			}
		}
	}
}

void BSTree::remove(const string& key)
{
	Node* curr = root;
	if (curr != nullptr)
	{
		remove(key, curr);
	}
}
void BSTree::remove(const string& key, Node* curr)
{
	if (root->getPhrase() == key)
	{
		if (curr->getCount() > 1)
		{
			// no need to mess with nodes if count is greater than 1
			curr->setCount(curr->getCount() - 1);
		}
		// root has no parent so different case
		else if (curr->getLeft() != nullptr)
		{
			// find the largest node in the left subtree
			Node* largestLeft = curr->getLeft();
			Node* largestLeftParent = nullptr;
			Node* largestLeftRight = largestLeft;
			Node* largestLeftRightParent = nullptr;
			while (largestLeft->getRight() != nullptr)
			{
				// there exists at least 1 node in the left subtree's right subtree
				largestLeftParent = largestLeft;
				largestLeft = largestLeft->getRight();
			}
			if (largestLeftParent != nullptr)
			{
				// case that there was at least 1 node in the left subtree's right subtree
				largestLeftParent->setRight(nullptr);
				largestLeft->setLeft(curr->getLeft());
			}

			if (largestLeft->getLeft() != nullptr)
			{
				largestLeftRight = largestLeft->getLeft();
				while (largestLeftRight->getRight() != nullptr)
				{
					largestLeftRightParent = largestLeftRight;
					largestLeftRight = largestLeftRight->getRight();
				}
				if (largestLeftRightParent != nullptr)
				{
					largestLeftRightParent->setRight(nullptr);
				}
			}

			if (largestLeftRight->getLeft() != nullptr && largestLeftRightParent != nullptr)
			{
				largestLeftRightParent->setRight(largestLeftRight->getLeft());
			}

			if (largestLeftRight != largestLeft)
			{
				largestLeftRight->setLeft(largestLeft->getLeft());
				largestLeftRight->setRight(largestLeft->getRight());
				largestLeft->setLeft(largestLeftRight);
			}

			largestLeft->setRight(curr->getRight());
			if (curr == root)
			{
				root = largestLeft;
			}
			delete curr;
		}
		else if (curr->getRight() != nullptr)
		{
			// if no left subtree, find smallest node in right subtree
			Node* smallestRight = curr->getRight();
			Node* smallestRightParent = nullptr;
			while (smallestRight->getLeft() != nullptr)
			{
				// there exists at least 1 node in the right subtree's left subtree
				smallestRightParent = smallestRight;
				smallestRight = smallestRight->getLeft();
			}
			if (smallestRightParent != nullptr)
			{
				// case that there was at least 1 node in the right subtree's left subtree
				smallestRightParent->setLeft(smallestRight->getRight());
				smallestRight->setRight(curr->getRight());
			}
			smallestRight->setLeft(curr->getLeft());
			if (curr == root)
			{
				root = smallestRight;
			}
			delete curr;
		}
		else
		{
			delete curr;
			root = nullptr;
		}
	}

	else if (key < curr->getPhrase() && curr->getLeft() != nullptr)
	{
		if (curr->getLeft()->getPhrase() == key)
		{
			if (curr->getLeft()->getCount() > 1)
			{
				// no need to mess with nodes if count is greater than 1
				curr->getLeft()->setCount(curr->getLeft()->getCount() - 1);
			}
			else
			{
				// if the left child has the key
				removeFound(curr, curr->getLeft(), true);
			}
		}
		else
		{
			//check left subtree
			remove(key, curr->getLeft());
		}
	}
	else if (key > curr->getPhrase() && curr->getRight() != nullptr)
	{
		if (curr->getRight()->getPhrase() == key)
		{
			if (curr->getRight()->getCount() > 1)
			{
				curr->getRight()->setCount(curr->getRight()->getCount() - 1);
			}
			else
			{
				//if the right child has the key
				removeFound(curr, curr->getRight(), false);
			}
		}
		else
		{
			//check right subtree
			remove(key, curr->getRight());
		}
	}
}
void BSTree::removeFound(Node* parent, Node* curr, bool childIsLeft)
{
	if (curr->getLeft() != nullptr)
	{
		// find the largest node in the left subtree
		Node* largestLeft = curr->getLeft();
		Node* largestLeftParent = nullptr;
		while (largestLeft->getRight() != nullptr)
		{
			// there exists at least 1 node in the left subtree's right subtree
			largestLeftParent = largestLeft;
			largestLeft = largestLeft->getRight();
		}
		if (largestLeftParent != nullptr)
		{
			// case that there was at least 1 node in the left subtree's right subtree
			largestLeftParent->setRight(largestLeft->getLeft());
			largestLeft->setLeft(curr->getLeft());
		}
		largestLeft->setRight(curr->getRight());
		if (childIsLeft)
		{
			parent->setLeft(largestLeft);
		}
		else
		{
			parent->setRight(largestLeft);
		}

		if (curr == root)
		{
			root = largestLeft;
		}
		delete curr;
	}
	else if (curr->getRight() != nullptr)
	{
		// if no left subtree, find smallest node in right subtree
		Node* smallestRight = curr->getRight();
		Node* smallestRightParent = nullptr;
		while (smallestRight->getLeft() != nullptr)
		{
			// there exists at least 1 node in the right subtree's left subtree
			smallestRightParent = smallestRight;
			smallestRight = smallestRight->getLeft();
		}
		if (smallestRightParent != nullptr)
		{
			// case that there was at least 1 node in the right subtree's left subtree
			smallestRightParent->setLeft(smallestRight->getRight());
			smallestRight->setRight(curr->getRight());
		}
		smallestRight->setLeft(curr->getLeft());
		if (childIsLeft)
		{
			parent->setLeft(smallestRight);
		}
		else
		{
			parent->setRight(smallestRight);
		}
		if (curr == root)
		{
			root = smallestRight;
		}
		delete curr;
	}
	else
	{
		delete curr;
		if (childIsLeft)
		{
			parent->setLeft(nullptr);
		}
		else parent->setRight(nullptr);
	}
}



bool BSTree::search(const string& key) const
{
	Node* curr = root;

	while (curr != nullptr)
	{
		if (curr->getPhrase() == key)
		{
			return true;
		}
		if (key < curr->getPhrase())
		{
			curr = curr->getLeft();
		}
		else if (key > curr->getPhrase())
		{
			curr = curr->getRight();
		}
	}
	return false;

}

string BSTree::largest() const
{

	Node* curr = root;

	if (curr != nullptr)
	{
		while (curr->getRight() != nullptr)
		{
			curr = curr->getRight();
		}
		return curr->getPhrase();
	}
	else
	{
		return "";
	}

}

string BSTree::smallest() const
{

	Node* curr = root;

	if (curr != nullptr)
	{
		while (curr->getLeft() != nullptr)
		{
			curr = curr->getLeft();
		}
		return curr->getPhrase();
	}
	else
	{
		return "";
	}

}



int BSTree::height(const string& key) const {

	Node* curr = root;

	while (curr != nullptr)
	{
		if (curr->getPhrase() == key)
		{
			break;
		}
		if (key < curr->getPhrase())
		{
			curr = curr->getLeft();
		}
		else if (key > curr->getPhrase())
		{
			curr = curr->getRight();
		}
	}
	return heightRecursive(curr);
}
int BSTree::heightRecursive(Node* curr) const
{

	//from program2
	if (curr == nullptr)
	{
		return -1;
	}
	else if (curr->getLeft() == nullptr && curr->getRight() == nullptr)
	{
		return 0;
	}
	int leftTreeHeight = heightRecursive(curr->getLeft());
	int rightTreeHeight = heightRecursive(curr->getRight());
	if (leftTreeHeight > rightTreeHeight)
	{
		return leftTreeHeight + 1;
	}
	else return rightTreeHeight + 1;
	return 0;


}


//printing
void BSTree::preOrder() const
{
	if (root != nullptr)
	{
		preOrder(root);
	}
}
void BSTree::preOrder(Node* curr) const
{
	cout << curr->getPhrase() << "(" << curr->getCount() << "), ";
	if (curr->getLeft() != nullptr)
	{
		preOrder(curr->getLeft());
	}
	if (curr->getRight() != nullptr)
	{
		preOrder(curr->getRight());
	}
}
void BSTree::postOrder() const
{
	if (root != nullptr)
	{
		postOrder(root);
	}
}
void BSTree::postOrder(Node* curr) const
{
	if (curr->getLeft() != nullptr)
	{
		postOrder(curr->getLeft());
	}
	if (curr->getRight() != nullptr)
	{
		postOrder(curr->getRight());
	}
	cout << curr->getPhrase() << "(" << curr->getCount() << "), ";
}
void BSTree::inOrder() const
{
	if (root != nullptr)
	{
		inOrder(root);
	}
}
void BSTree::inOrder(Node* curr) const
{
	if (curr->getLeft() != nullptr)
	{
		inOrder(curr->getLeft());
	}
	cout << curr->getPhrase() << "(" << curr->getCount() << "), ";
	if (curr->getRight() != nullptr)
	{
		inOrder(curr->getRight());
	}
}