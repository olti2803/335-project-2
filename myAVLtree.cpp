/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.cpp
*/

#include "myAVLtree.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cmath>

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clearTree(this->root);
}

void AVLTree::clearTree(AVLNode* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

int AVLTree::height(AVLNode* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int AVLTree::getBalance(AVLNode* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

AVLNode* AVLTree::insertRecursive(AVLNode* node, int value) {
    if (node == nullptr)
        return(new AVLNode(value));

    if (value < node->value)
        node->left = insertRecursive(node->left, value);
    else if (value > node->value)
        node->right = insertRecursive(node->right, value);
    else { // Equal values are handled as duplicates
        node->count++;
        return node;
    }

    // Update height of this ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get the balance factor
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

void AVLTree::insert(int value) {
    this->root = insertRecursive(this->root, value);
}

// This function to find and delete the node with a given value will be used for popMedian
AVLNode* AVLTree::deleteNode(AVLNode* root, int key) {
    // Base case
    if (root == nullptr)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if ( key < root->value )
        root->left = deleteNode(root->left, key);
    else if( key > root->value )
        root->right = deleteNode(root->right, key);
    else {
        // node with only one child or no child
        if( (root->left == nullptr) || (root->right == nullptr) ) {
            AVLNode *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of
                               // the non-empty child
            delete temp;
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVLNode* temp = root->right;
            while (temp->left != nullptr)
                temp = temp->left;

            // Copy the inorder successor's
            // data to this node
            root->value = temp->value;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->value);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + std::max(height(root->left),
                                height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int AVLTree::getMedianValueAndRebalance() {
    if (root == nullptr) {
        throw std::runtime_error("The tree is empty. Cannot get median.");
    }

    // Find the median node
    AVLNode* medianNode = findMedianNode(root);

    // Get the median value before removing the node
    int medianValue = medianNode->value;

    // Remove the median node from the tree
    root = removeNode(root, medianValue);

    return medianValue;
}


//function we are testing for
void AVLTree::treeMedian(const std::vector<int>& instructions) {
    AVLTree avl; // Instantiate your AVL tree
    std::vector<int> medians; // To store and later print all popped medians

    try {
        for (int inst : instructions) {
            if (inst == -1) {
                // Pop median instruction
                int median = avl.popMedian(); // Assuming this method exists and returns the median
                medians.push_back(median);
            } else {
                // Insert instruction
                avl.insert(inst); // Assuming this method exists to insert values
            }
        }

        // Output all medians after processing instructions
        for (int median : medians) {
            std::cout << median << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}


// util function to update the height and size of a node
void AVLTree::updateNode(AVLNode* node) {
    if (node == nullptr) {
        return;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    node->count = 1 + (node->left ? node->left->count : 0) + (node->right ? node->right->count : 0);
}

// util function to find the inorder successor of a node
AVLNode* AVLTree::findSuccessor(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// util function to balance a node
AVLNode* AVLTree::balanceNode(AVLNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    int balance = height(node->left) - height(node->right);

    // Left heavy
    if (balance > 1) {
        // Left-Left case
        if (height(node->left->left) >= height(node->left->right)) {
            return rightRotate(node);
        }
        // Left-Right case
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Right heavy
    else if (balance < -1) {
        // Right-Right case
        if (height(node->right->right) >= height(node->right->left)) {
            return leftRotate(node);
        }
        // Right-Left case
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // Node is already balanced
    return node;
}

AVLNode* AVLTree::removeNode(AVLNode* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        // Node to be removed found

        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = (node->left != nullptr) ? node->left : node->right;

            // No child case
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp; // Copy the contents of the non-empty child
            }

            delete temp;
        } else {
            // Node has two children
            AVLNode* successor = findSuccessor(node->right);
            node->value = successor->value;
            node->right = removeNode(node->right, successor->value);
        }
    }

    // Update height and size
    updateNode(node);

    // Balance the tree
    return balanceNode(node);
}


int AVLTree::popMedian() {
    if (root == nullptr) {
        throw std::runtime_error("The tree is empty. Cannot pop median.");
    }

    // Find the median node
    AVLNode* medianNode = findMedianNode(root);

    // Get the median value before removing the node
    int medianValue = medianNode->value;

    // Remove the median node from the tree
    root = removeNode(root, medianValue);

    return medianValue;
}

AVLNode* AVLTree::findMedianNode(AVLNode* node) {
    if (node == nullptr) {
        throw std::runtime_error("The tree is empty. Cannot find median node.");
    }

    int leftSize = (node->left != nullptr) ? node->left->count : 0;
    int rightSize = (node->right != nullptr) ? node->right->count : 0;
    int totalSize = leftSize + rightSize + 1; // Size of the subtree rooted at 'node' including itself

    int medianIndex = totalSize / 2; // Index of the median node (zero-based)

    // If the left subtree size is equal to the median index, the current node is the median
    if (leftSize == medianIndex) {
        return node;
    }
    // If the left subtree size is greater than the median index, recurse into the left subtree
    else if (leftSize > medianIndex) {
        return findMedianNode(node->left);
    }
    // If the left subtree size is less than the median index, recurse into the right subtree
    else {
        // Adjust the median index for the right subtree
        medianIndex -= (leftSize + 1);
        return findMedianNode(node->right);
    }
}
