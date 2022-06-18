#include "AVLTree.h"
#include<fstream>

AVLTree::AVLTree()
{
    root = nullptr;
}
void AVLTree::insert(const string &newString)
{
    //reused from program 2 but we have to rework it to auto-balance
    //change balanceFactor when you add a node

    Node* newNode = new Node(newString);

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
					break;
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
					break;
				}

				else
				{
					curr = curr->getRight();	//proceed to right child
				}
			}
            else if (newNode->getPhrase() == curr->getPhrase())
            {
                return;
            }

		}
        //rebalance tree
        Node* unbalancedNode = findUnbalancedNode(newNode, root);
        if (unbalancedNode != nullptr)
        {
            Node* parent = root;
            //find parent for unbalancedNode
            if (unbalancedNode != root)
            {
                while(parent->getLeft() != unbalancedNode && parent->getRight() != unbalancedNode)
                {
                    if (parent->getPhrase() > unbalancedNode->getPhrase())
                    {
                        parent = parent->getLeft();
                    }
                    if (parent->getPhrase() < unbalancedNode->getPhrase())
                    {
                        parent = parent->getRight();
                    }

                }
            }
            // fix the imbalance at unbalancedNode
            rotate(unbalancedNode, parent);
        }
	}
}
void AVLTree::printBalanceFactors()
{
    printBalanceFactorsRecursive(root);
    cout << endl;
}

void AVLTree::printBalanceFactorsRecursive(Node* curr)
{
    if (curr != nullptr)
    {
        printBalanceFactorsRecursive(curr->getLeft());
        cout << curr->getPhrase() << "(" << balanceFactor(curr) << "), ";
        printBalanceFactorsRecursive(curr->getRight());
    }
}

int AVLTree::balanceFactor(Node* curr)
{
    if (curr->getLeft() != nullptr && curr->getRight() != nullptr)
    {
        return height(curr->getLeft()->getPhrase()) - height(curr->getRight()->getPhrase());
    }
    else if (curr->getLeft()!= nullptr)
    {
        return height(curr->getLeft()->getPhrase()) - (-1);
    }
    else if (curr->getRight() != nullptr)
    {
        int heightToSubtract = height(curr->getRight()->getPhrase());
        return -1 - heightToSubtract;
    }
    return 0;
}
int AVLTree::height(const string& key) const {

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
    return height(curr);
}
int AVLTree::height(Node* curr) const
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
    int leftTreeHeight = height(curr->getLeft());
    int rightTreeHeight = height(curr->getRight());
    if (leftTreeHeight > rightTreeHeight)
    {
        return leftTreeHeight + 1;
    }
    else return rightTreeHeight + 1;
    return 0;


}

Node* AVLTree::findUnbalancedNode(Node* insertedNode, Node* curr)
{

    // base cases; end of tree either is unbalanced or not
    Node* closestNode = nullptr;
    if (balanceFactor(curr) >= 2 || balanceFactor(curr) <= -2)
    {
        closestNode = curr;
    }
    // must check for closer unbalanced option
    if (curr->getLeft() != nullptr && (insertedNode->getPhrase() < curr->getPhrase()))
    {
        Node* leftSearch = findUnbalancedNode(insertedNode, curr->getLeft());
        if (leftSearch != nullptr)
        {
            closestNode = leftSearch;
        }
    }
    // insertedNode is either in the left subtree or right, not both
    else if (curr->getRight() != nullptr && (insertedNode->getPhrase() > curr->getPhrase()))
    {
        Node* rightSearch = findUnbalancedNode(insertedNode, curr->getRight());
        if (rightSearch != nullptr)
        {
            closestNode = rightSearch;
        }
    }
    return closestNode;

}


void AVLTree::rotate(Node*curr, Node*parent)
{
    bool childIsLeft = false;
    bool isRoot = false;
    Node* subTreeRoot = nullptr;
    Node* extraChild = nullptr;
    if (curr != parent)
    {
        if (parent->getLeft() == curr)
        {
            childIsLeft = true;
        }
    }
    else
    {
        isRoot = true;
    }
    
    //four imbalance cases
    // balance > 1; left-heavy
        // 1. rotate right
        if (balanceFactor(curr) > 1)
        {
            if (balanceFactor(curr->getLeft()) > 0)
            {
                subTreeRoot = rotateRight(curr);
            }
            else
            {
                // 2. left-right rotation
                //extra child case
                if(curr->getLeft()->getRight() != nullptr)
                {
                    if (curr->getLeft()->getRight()->getRight())
                    {
                    extraChild = curr->getLeft()->getRight()->getRight();
                    }
                }
                subTreeRoot = rotateLeft(curr->getLeft());
                curr->setLeft(subTreeRoot);
                subTreeRoot = rotateRight(curr);
                if (extraChild != nullptr)
                {
                    curr->setLeft(extraChild);
                }
            }
        }
        // also update parent of newSubRoot


        // do a right rotation at newSubRoot's parent

    

    // balance < -1; right-heavy
        // 3. rotate left
        if (balanceFactor(curr) < -1)
        {
            if (balanceFactor(curr->getRight()) < 0)
            {
                subTreeRoot = rotateLeft(curr);
            }
            else
            {
                // 4. right-left rotation
                //extra child case
                if(curr->getRight()->getLeft() != nullptr)
                {
                    if (curr->getRight()->getLeft()->getLeft())
                    {
                    extraChild = curr->getRight()->getLeft()->getLeft();
                    }
                }
                subTreeRoot = rotateRight(curr->getRight());

                curr->setRight(subTreeRoot);
                subTreeRoot = rotateLeft(curr);
                if (extraChild != nullptr)
                {
                    curr->setRight(extraChild);
                }
            }
        }
        // also update parent of newSubRoot


        if (!isRoot)
                {
                    if (childIsLeft)
                    {
                        parent->setLeft(subTreeRoot);
                    }
                    else parent->setRight(subTreeRoot);
                }
                else
                {
                    root = subTreeRoot;
                }

}
Node* AVLTree::rotateLeft(Node*curr)
{
    // curr becomes left child of its right child
    Node* newSubRoot = curr->getRight();
    newSubRoot->setLeft(curr);
    curr->setRight(nullptr);
    return newSubRoot;
}
Node * AVLTree::rotateRight(Node*curr)
{
    // curr becomes right child of its left child
    Node* newSubRoot = curr->getLeft();
    newSubRoot->setRight(curr);
    curr->setLeft(nullptr);
    return newSubRoot;
}



void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeft()){
            visualizeTree(outFS,n->getLeft());
            outFS<<n->getPhrase() <<" -> " <<n->getLeft()->getPhrase()<<";"<<endl;    
        }

        if(n->getRight()){
            visualizeTree(outFS,n->getRight());
            outFS<<n->getPhrase() <<" -> " <<n->getRight()->getPhrase()<<";"<<endl;    
        }
    }
}
