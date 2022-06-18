#include <iostream>
#include "BSTree.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void run_tests() {
    cout << "Constructing BS Tree...";
    BSTree bst = BSTree();
    cout << "complete." << endl;

    int totalTests = 0,failedTests = 0;
    totalTests++;
    cout << "Test: testing largest on empty tree...";
    if (bst.largest() == "") {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    totalTests++;
    cout << "Test: testing smallest on empty tree...";
    if (bst.smallest() == "") {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    /* Test insert (assume search works) */
    totalTests++;
    cout << "Test: testing insert and search...";
    string test_input = "Hello";
    bst.insert(test_input);
    if (bst.search(test_input)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert second word and search first and second...";
    string test_input2 = "World";
    bst.insert(test_input2);
    if (bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing insert duplicate and search first (duplicate) and second...";
    string test_input_duplicate = "Hello";
    bst.insert(test_input_duplicate);
    if (bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    cout << "Test: testing smallest on non-empty tree...";
    if (bst.smallest() == "") {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    cout << "Test: testing largest on non-empty tree...";
    if (bst.largest() == "") {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing remove duplicate and search first (duplicate) second...";
    bst.remove(test_input);
    if (bst.search(test_input)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing remove first (now gone)...";
    bst.remove(test_input);
    if (!bst.search(test_input) && bst.search(test_input2)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    // TODO: Add tests for largest and smallest on non-empty trees
    // TODO: Add tests for insert and remove on larger trees
    totalTests++;
    cout << "Test: Inserting a ton of words and searching randomly...";
    string test_input3 = "Parenthesis";
    string test_input4 = "Exponent";
    string test_input5 = "Multiplication";
    string test_input6 = "Division";
    string test_input7 = "Subtraction";
    bst.insert(test_input3);
    bst.insert(test_input4);
    bst.insert(test_input5);
    bst.insert(test_input6);
    bst.insert(test_input7);
    if (bst.search(test_input3) && bst.search(test_input4) && bst.search(test_input6)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }

    totalTests++;
    cout << "Test: testing removing root on larger tree...";
    bst.remove(test_input2);
    if (bst.search(test_input4)) {
        cerr << "Passed" << endl;
    } else {
        cerr << "Failed" << endl;
        failedTests++;
    }
    // TODO: Add tests for height of nodes (empty and larger trees)
    // Manually inspect pre post and inorder traversals
    cout << "Test: testing preOrder...Should be:" << endl;
    cout << "S P E D M" << endl;
    cout << "Result:" << endl;
    bst.preOrder();
    cout  << endl;
    
    cout << "Test: testing postOrder...Should be:" << endl;
    cout << "D M E P S" << endl;
    cout << "Result:" << endl;
    bst.postOrder();
cout  << endl;

    cout << "Test: testing inOrder...Should be:" << endl;
    cout << "D E M P S" << endl;
    cout << "Result:" << endl;
    bst.inOrder();
    cout  << endl;

    cout << "Passed " << totalTests - failedTests << " / " << totalTests << " tests." << endl;
}