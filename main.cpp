#include <iostream>
#include <fstream>
#include <cstring>
#include "BTree.h"

using namespace std;
BTree* add(BTree* root, int addInput);
void remove(BTree* parent, int remInput, BTree* &root);
void printTree(BTree* root);
void searchTree(BTree* root, int searchInput);
int main() {
  bool quit = false;
  char input[30];
  BTree* root = NULL;
  do {
    cout << "You can: \'ADD\' \'PRINT\' \'DELETE\' \'SEARCH\' \'QUIT\'" << endl;
    cin >> input;
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    else if (strcmp(input, "ADD") == 0) {
      cout << "You can add: \'MANUAL\' \'FILE\'" << endl;
      char choiceInput[8];
      cin >> choiceInput;
      if (strcmp(choiceInput, "MANUAL") == 0) {
	cout << "What is the number you'd like to add?" << endl;
	int addInput;
	cin >> addInput;
	root = add(root, addInput);
      }
      else if (strcmp(choiceInput, "FILE") == 0) {
	ifstream sequence("number.txt");
	int number;
	while (sequence >> number) {
	  root = add(root, number);
	}
      }
    }
    else if (strcmp(input, "DELETE") == 0) {
      cout << "What is the number you'd like to delete?" << endl;
      int remInput;
      cin >> remInput;
      remove(root, remInput, root);
      cout << "The root is " << root->getValue() << endl;
    }
    else if (strcmp(input, "PRINT") == 0) {
      printTree(root);
      cout << endl;
    }
    else if (strcmp(input, "SEARCH") == 0) {
      cout << "What number are you looking for?" << endl;
      int searchInput;
      cin >> searchInput;
      searchTree(root, searchInput);
    }
  } while (quit != true);
  return 0;
}

BTree* add(BTree* root, int addInput) {
  if (!root) {
    root = new BTree(addInput);
  }
  else if (root->getValue() > addInput) {
    root->setLeft(add(root->getLeft(), addInput));
  }
  else {
    root->setRight(add(root->getRight(), addInput));
  }
  return root;
}

void printTree(BTree* root) {
  if (root == NULL) {
    return;
  }
  printTree(root->getLeft());
  cout << root->getValue() << " ";
  printTree(root->getRight());
}

void searchTree(BTree* root, int searchInput) {
  if (root == NULL) {
    cout << "This value is not in the tree." << endl;
    return;
  }
  if (root->getValue() == searchInput) {
    cout << "This value is in the tree." << endl;
    return;
  }
  if (root->getValue() > searchInput) {
    searchTree(root->getLeft(), searchInput);
  }
  else {
    searchTree(root->getRight(), searchInput);
  }
}

void remove(BTree* parent, int delInput, BTree* &root) {
  if (parent == NULL) {
    cout << "Empty tree!" << endl;
    return;
  }
  if (parent->getValue() == delInput) {
    if (parent->getRight() == NULL && parent->getLeft() == NULL) {
      BTree* temp = root;
      root = NULL;
      delete temp;
      return;
    }
    if (parent->getRight() == NULL) {
      BTree* temp = root;
      root = parent->getLeft();
      delete temp;
      return;
    }
    if (parent->getLeft() == NULL) {
      BTree* temp = root;
      root = parent->getRight();
      delete temp;
      return;
    }
    else {
      BTree* temp = parent->getRight();
      if (temp->getLeft() == NULL) {
	root->setValue(temp->getValue());
	if (temp->getRight() != NULL) {
	  root->setRight(temp->getRight());
	}
	else {
	  root->setRight(NULL);
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
  if (parent->getLeft() != NULL) { 
  if (parent->getLeft()->getValue() == delInput) {
    if (parent->getLeft()->getLeft() == NULL && parent->getLeft()->getRight() == NULL) {
      BTree* temp = parent->getLeft();
      parent->setLeft(NULL);
      delete temp;
      return;
    }
    if (parent->getLeft()->getLeft() == NULL) {
      BTree* temp = parent->getLeft()->getRight();
      parent->setLeft(temp);
      delete temp;
      return;
    }
    else if (parent->getLeft()->getRight() == NULL) {
      BTree* temp = parent->getLeft()->getLeft();
      parent->setLeft(temp);
      delete temp;
      return;
    }
    BTree* temp = parent->getLeft()->getRight();
    if (temp->getLeft() == NULL) {
      cout << "here" << endl;
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
    BTree* pTemp = temp;
    temp = temp->getLeft();
    while (temp->getLeft() != NULL) {
      pTemp = temp;
      temp = temp->getLeft();
    }
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
  if (parent->getRight() != NULL) {
  if (parent->getRight()->getValue() == delInput) {
    if (parent->getRight()->getLeft() == NULL && parent->getRight()->getRight() == NULL) {
      BTree* temp = parent->getRight();
      parent->setRight(NULL);
      delete temp;
      return;
    }
    if (parent->getRight()->getLeft() == NULL) {
      BTree* temp = parent->getRight()->getRight();
      parent->setRight(temp);
      delete temp;
      return;
    }
    else if (parent->getRight()->getRight() == NULL) {
      BTree* temp = parent->getRight()->getLeft();
      parent->setRight(temp);
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
  }
  if (parent->getValue() > delInput) {
    remove(parent->getLeft(), delInput, root);
  }
  else {
    remove(parent->getRight(), delInput, root);
  }
}
