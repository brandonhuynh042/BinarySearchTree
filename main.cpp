#include <iostream>
#include <fstream>
#include <cstring>
#include "BTree.h"

using namespace std;
BTree* add(BTree* root, int addInput);
void remove(BTree* parent, int remInput, BTree* &root);
void vPrintTree(BTree* root, int depth);
void searchTree(BTree* root, int searchInput);

/* This program creates a Binary Search Tree with add, print, delete, and search functions.
   /* Brandon Huynh, last edited 3/10/2025 */
int main() {
  bool quit = false;
  char input[30];
  BTree* root = NULL;
  do {
    // what do they want to do?
    cout << "You can: \'ADD\' \'PRINT\' \'DELETE\' \'SEARCH\' \'QUIT\'" << endl;
    cin >> input;
    // leave
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    // add
    else if (strcmp(input, "ADD") == 0) {
      // which way do they want to add?
      cout << "You can add: \'MANUAL\' \'FILE\'" << endl;
      char choiceInput[8];
      cin >> choiceInput;
      if (strcmp(choiceInput, "MANUAL") == 0) {
	// take input, add.
	cout << "What is the number you'd like to add?" << endl;
	int addInput;
	cin >> addInput;
	root = add(root, addInput);
      }
      else if (strcmp(choiceInput, "FILE") == 0) {
	// read in file, add one number at a time
	ifstream sequence("number.txt");
	int number;
	while (sequence >> number) {
	  root = add(root, number);
	}
      }
    }
    // delete
    else if (strcmp(input, "DELETE") == 0) {
      // find number they want to delete, delete.
      cout << "What is the number you'd like to delete?" << endl;
      int remInput;
      cin >> remInput;
      remove(root, remInput, root);
    }
    // print
    else if (strcmp(input, "PRINT") == 0) {
      vPrintTree(root, 0);
    }
    // search
    else if (strcmp(input, "SEARCH") == 0) {
      // find number they want to search for, search.
      cout << "What number are you looking for?" << endl;
      int searchInput;
      cin >> searchInput;
      searchTree(root, searchInput);
    }
  } while (quit != true);
  return 0;
}

BTree* add(BTree* root, int addInput) {
  // if the node is empty (reached a leaf, or root is empty), add it here!
  if (!root) {
    root = new BTree(addInput);
  }
  // recurse left if it's smaller
  else if (root->getValue() > addInput) {
    root->setLeft(add(root->getLeft(), addInput));
  }
  // recurse right if it's bigger
  else {
    root->setRight(add(root->getRight(), addInput));
  }
  return root;
}

void vPrintTree(BTree* root, int depth) {
  // recurse through right children
  if (root->getRight() != NULL) {
    vPrintTree(root->getRight(), depth+1);
  }
  // tab through to display depth
  for (int i = 0; i < depth; i++) {
    cout << '\t';
  }
  cout << root->getValue() << endl;
  // recurse through left children
  if (root->getLeft() != NULL) {
    vPrintTree(root->getLeft(), depth+1);
  }
}
void searchTree(BTree* root, int searchInput) {
  // reached a leaf (or empty), value isn't there
  if (root == NULL) {
    cout << "This value is not in the tree." << endl;
    return;
  }
  // hit the value, it's in the tree.
  if (root->getValue() == searchInput) {
    cout << "This value is in the tree." << endl;
    return;
  }
  // recurse left if it's smaller
  if (root->getValue() > searchInput) {
    searchTree(root->getLeft(), searchInput);
  }
  // recurse right if it's bigger
  else {
    searchTree(root->getRight(), searchInput);
  }
}

void remove(BTree* parent, int delInput, BTree* &root) {
  // empty tree
  if (root == NULL) {
    cout << "Empty tree!" << endl;
    return;
  }
  // the value to delete is the root
  if (parent->getValue() == delInput) {
    // no children, delete the root
    if (parent->getRight() == NULL && parent->getLeft() == NULL) {
      delete root;
      root = NULL;
      return;
    }
    // only left child, right child becomes new root
    if (parent->getRight() == NULL) {
      BTree* temp = root;
      root = parent->getLeft();
      delete temp;
      return;
    }
    // only right child, left child becomes new root
    if (parent->getLeft() == NULL) {
      BTree* temp = root;
      root = parent->getRight();
      delete temp;
      return;
    }
    // two children, find the successor
    else {
      BTree* temp = parent->getRight();
      // right child doesn't have a left to search through so it just becomes the new root
      if (temp->getLeft() == NULL) {
	root->setValue(temp->getValue());
	  root->setRight(temp->getRight());
	delete temp;
	return;
      }
      // otherwise, traverse until the leftmost child of the right child
    BTree* pTemp = temp;
    temp = temp->getLeft();
    while (temp->getLeft() != NULL) {
      pTemp = temp;
      temp = temp->getLeft();
    }
    // this becomes the new root, delete the leaf
    root->setValue(temp->getValue());
    if (temp->getRight() != NULL) {
      pTemp->setLeft(temp->getRight());
    }
    else {
      pTemp->setLeft(NULL);
    }
    delete temp;
    return;

    }
  }
  // checking left child
  if (parent->getLeft() != NULL) {
    // left child is value to delete
  if (parent->getLeft()->getValue() == delInput) {
    // no children, remove the link to parent and free memory
    if (parent->getLeft()->getLeft() == NULL && parent->getLeft()->getRight() == NULL) {
      BTree* temp = parent->getLeft();
      parent->setLeft(NULL);
      delete temp;
      return;
    }
    // only right child, that replaces it's parent
    if (parent->getLeft()->getLeft() == NULL) {
      BTree* temp = parent->getLeft();
      parent->setLeft(temp->getRight());
      delete temp;
      return;
    }
    // only left child, that replaces it's parent
    else if (parent->getLeft()->getRight() == NULL) {
      BTree* temp = parent->getLeft();
      parent->setLeft(temp->getLeft());
      delete temp;
      return;
    }
    // two children, begin looking for successor
    BTree* temp = parent->getLeft()->getRight();
    // if the right child doesn't have a left child, it's value goes to the parent and the child gets deleted.
    if (temp->getLeft() == NULL) {
      parent->getLeft()->setValue(temp->getValue());
      if (temp->getRight() != NULL) {
        parent->getLeft()->setRight(temp->getRight());
      }
      else {
        parent->getLeft()->setRight(NULL);
      }
      delete temp;
      return;
    }
    // otherwise, traverse through until the leftmost child of the right child is found
    BTree* pTemp = temp;
    temp = temp->getLeft();
    while (temp->getLeft() != NULL) {
      pTemp = temp;
      temp = temp->getLeft();
    }
    // replace the place to delete's value with the successor, delete the former successor
    parent->getLeft()->setValue(temp->getValue());
    if (temp->getRight() != NULL) {
      pTemp->setLeft(temp->getRight());
    }
    else {
      pTemp->setLeft(NULL);
    }
    delete temp;
    return;
  }
  }
  // same as the chunk above, but searching through the right child instead.
  if (parent->getRight() != NULL) {
  if (parent->getRight()->getValue() == delInput) {
    if (parent->getRight()->getLeft() == NULL && parent->getRight()->getRight() == NULL) {
      BTree* temp = parent->getRight();
      parent->setRight(NULL);
      delete temp;
      return;
    }
    if (parent->getRight()->getLeft() == NULL) {
      BTree* temp = parent->getRight();
      parent->setRight(temp->getRight());
      delete temp;
      return;
    }
    else if (parent->getRight()->getRight() == NULL) {
      BTree* temp = parent->getRight();
      parent->setRight(temp->getLeft());
      delete temp;
      return;
    }
    BTree* temp = parent->getRight()->getRight();
    if (temp->getLeft() == NULL) {
      parent->getRight()->setValue(temp->getValue());
      if (temp->getRight() != NULL) {
	parent->getRight()->setRight(temp->getRight());
      }
      else {
	parent->getRight()->setRight(NULL);
      }
      delete temp;
      return;
    }
    BTree* pTemp = temp;
    temp = temp->getLeft();
    while (temp->getLeft() != NULL) {
      pTemp = temp;
      temp = temp->getLeft();
    }
    parent->getRight()->setValue(temp->getValue());
    if (temp->getRight() != NULL) {
      pTemp->setLeft(temp->getRight());
    }
    else {
      pTemp->setLeft(NULL);
    }

    delete temp;
    return;
  }
  }
  if (parent->getLeft() == NULL && parent->getRight() == NULL) {
    cout << "Value not found!" << endl;
    return;
  }
  // recurse left if it's smaller
  if (parent->getValue() > delInput) {
    remove(parent->getLeft(), delInput, root);
  }
  // recurse right if it's bigger
  else {
    remove(parent->getRight(), delInput, root);
  }
}
