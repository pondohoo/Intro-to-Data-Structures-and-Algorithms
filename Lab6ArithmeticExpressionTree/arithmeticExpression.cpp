
#include "arithmeticExpression.h"
#include<stack>
#include<sstream>
#include<fstream>

arithmeticExpression::arithmeticExpression(const string& s)
{
    infixExpression = s;
    root = nullptr;
}
void arithmeticExpression::buildTree()
{
    string postfixExpression = infix_to_postfix();
    TreeNode* currNode = nullptr;
    stack<TreeNode*> treeStack;
    char currChar = 'a';

    // traverses through the string, making each character a different node
    // when it finds an operator, sets children to top 2 nodes in stack
    for (unsigned int i = 0; i < postfixExpression.size(); ++i)
    {
        currNode = new TreeNode(postfixExpression.at(i), currChar + i);
        if (priority(postfixExpression.at(i)) != 0)
        {
            TreeNode* rightChild = treeStack.top();
            treeStack.pop();
            TreeNode* leftChild = treeStack.top();
            treeStack.pop();
            currNode->left = leftChild;
            currNode->right = rightChild;
        }
        treeStack.push(currNode);


    }
    root = treeStack.top();

}

int arithmeticExpression::priority(char op) {
    int priority = 0;
    if (op == '(') {
        priority = 3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}


string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for (unsigned i = 0; i < infixExpression.size(); ++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if (c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while (s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else {
                while (!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else { //c is an operand
            oss << c;
        }
    }
    while (!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}


void arithmeticExpression::infix()
{
    infix(root);
}

void arithmeticExpression::infix(TreeNode* node)
{

        //outputs the infix notation of the arithmetic expression tree
        //     by performing the inorder traversal of the tree.
        //     An opening and closing parenthesis must be added at the 
        //     beginning and ending of each expression.

    if (node != nullptr) {

        if (node->left != nullptr) 
        {
            cout << "(";        //marks beginning of expression
        }

        infix(node->left);      //recursively calls infix function w/ left node until node->left == nullptr
        cout << node->data;     //prints out each node

        infix(node->right);     //recursively calls infix function w/ right node until node->right == nullptr

        if (node->right != nullptr) 
        {
            cout << ")";        //marks end of expression
        }

    }
}

void arithmeticExpression::prefix()
{
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode* node)
{

        //      outputs the prefix notation of the arithmetic expression tree
        //     by performing the preorder traversal of the tree. 

    if (node != nullptr)
    {

        cout << node->data; //prints out node->data starting from root, its left child's left and right child, then
        prefix(node->left); //repeats process w/ root's right child
        prefix(node->right);    //this function should output the operators before the operands

    }

}

void arithmeticExpression::postfix()
{
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode* node)
{
        //outputs the postfix notation of the arithmetic expression tree
        //     by performing the postorder traversal of the tree

    if (node != nullptr)
    {

        postfix(node->left);    //opposite process of prefix, recursively calls node's left child starting from root, until
        postfix(node->right);   //leaf node is reached. this is outputted and its parent's right child. the parent node is then
        cout << node->data;     //outputted, and same process goes with the root's right child. this function should output
                                //the operator after its operands
    }


}

void arithmeticExpression::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error opening " << outputFilename << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
void arithmeticExpression::visualizeTree(ofstream& outFS, TreeNode* curr)
{
    if (curr != nullptr)
    {
        outFS << curr->key << " [color = red, peripheries=2, style = filled, label=\"key=" << curr->key << ", " << curr->data << "\"]" << endl;
    }
    if (curr->left != nullptr)
    {
        visualizeTree(outFS, curr->left);

        outFS << curr->key << " -> " << curr->left->key << endl;

    }
    if (curr->right != nullptr)
    {
        visualizeTree(outFS, curr->right);
        outFS << curr->key << " -> " << curr->right->key << endl;
    }
}