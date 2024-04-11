/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.hpp
*/

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cmath>
#include <exception>

using namespace std;

void treeMedian (const std::vector<int> * instructions);

class AVLTree
{
    public:
        // ALL IMPLEMENTATIONS ARE FROM THE TEXTBOOK 
        //link: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/AvlTree.h 
        //given from ed

    struct AvlNode
    {
        int element;
        AvlNode *left;
        AvlNode *right;
        int height;
        int size;
        int count;
        AvlNode( const int & ele, AvlNode *lt, AvlNode *rt, int h = 0 ): element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        AvlNode( int && ele, AvlNode *lt, AvlNode *rt, int h = 0 ): element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };
    
    AvlNode * root = nullptr;

    AvlNode* getRoot() const {
        return root;
    }
 
    /**
    * Return the height of node t or -1 if nullptr. 3 */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    /**
    * Internal method to insert into a subtree.
    * x is the item to insert.
    * t is the node that roots the subtree.
    * Set the new root of the subtree.
    */
    void insert( const int & x, AvlNode * & t )
    {
        if(t == nullptr)
        {
            t = new AvlNode{ x, nullptr, nullptr };
        }
        else if( x < t->element )
        {
            insert( x, t->left );
        }
        else if( t->element < x )
        {
            insert( x, t->right );
        }
        else if(x == t -> element)
        {
            (t -> count)++;
        }

        t -> size = 1 + getSize(t->left) + getSize(t->right);
        balance( t );
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if(t == nullptr)
        {
            return;
        }
        
        if(height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE)
        {
            if(height( t->left->left ) >= height( t->left->right ))
            {
                rotateWithLeftChild( t );
            }
            else
            {
                doubleWithLeftChild( t );
            }
            
        }
        else 
        {
            if(height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE)
            {
                if( height( t->right->right ) >= height( t->right->left ))
                {
                    rotateWithRightChild(t);
                }
                else
                {
                    doubleWithRightChild( t );
                }
            }
        }
                
        t->height = std::max( height( t->left ), height( t->right ) ) + 1;
        //t -> size = 1 + getSize(t->left) + getSize(t->right);

    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = std::max( height( k1->left ), k2->height ) + 1;
        k2=k1;
    }

    /**
        * Rotate binary tree node with right child.
        * For AVL trees, this is a single rotation for case 4.
        * Update heights, then set new root.
    */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = std::max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
    * Double rotate binary tree node: first left child
    * with its right child; then node k3 with new left child.
    * For AVL trees, this is a double rotation for case 2.
    * Update heights, then set new root.
    */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
        * Double rotate binary tree node: first right child.
        * with its left child; then node k1 with new right child.
        * For AVL trees, this is a double rotation for case 3.
        * Update heights, then set new root.
        */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    /**
    * Internal method to remove from a subtree.
    * x is the item to remove.
    * t is the node that roots the subtree.
    * Set the new root of the subtree.
    */
    // void remove( const int & x, AvlNode * & t )
    // {
    //     if(t == nullptr )
    //     {
    //         return;   // Item not found; do nothing
    //     }

    //     if(x < t -> element)
    //     {
    //         remove(x, t -> left);
    //     }
    //     else if(t -> element < x)
    //     {
    //         remove(x, t -> right);
    //     }
    //     else if(t -> count > 1)
    //     {
    //         (t -> count)--;
    //         return;
    //     }
    //     else if( t->left != nullptr && t->right != nullptr ) // Two children
    //     {
    //         t->element = findMin( t->right )->element;
    //         remove( t->element, t->right );
    //     }
    //     else
    //     {
    //         AvlNode *oldNode = t;
    //         t = ( t->left != nullptr ) ? t->left : t->right;
    //         delete oldNode;
    //     }

    //     if(t != nullptr)
    //     {
    //         t -> size = 1 + getSize(t->left) + getSize(t->right);
    //     }

    //     balance(t);
    // }
    void remove(const int & x, AvlNode *& t) {
    if (t == nullptr) {
        return; // Item not found; do nothing
    }

    if (x < t->element) {
        remove(x, t->left);
    } else if (t->element < x) {
        remove(x, t->right);
    } else if (t->count > 1) {
        (t->count)--;
        return;
    } else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right); // Remove the successor
    } else {
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }

    if (t != nullptr) {
        t->size = 1 + getSize(t->left) + getSize(t->right);
    }

    balance(t);
}


    /**
     * * Internal method to find the smallest item in a subtree t.
    * Return node containing the smallest item.
    */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        if( t->left == nullptr )
        {
            return t;
        }  
        return findMin( t->left );
    }

    /**
        * Internal method to find the largest item in a subtree t.
        * Return node containing the largest item.
        */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            while( t->right != nullptr )
            {
                t = t->right;
            }
        }
        return t;
    }

    void preOrder(AvlNode * t)
    {
        if (t != nullptr) 
        {
            std::cout << t->element << "("<< t -> count << ")"<< " ";
            preOrder(t->left);
            preOrder(t->right);
        }
    }

    int getSize(AvlNode * t) const 
    {
    return t == nullptr ? 0 : t->size;
    }

    bool empty() const
    {
        return root == nullptr;
    }

int findMedian() const {
    if (root == nullptr) {
        std::cerr << "Tree is empty. Cannot find median." << std::endl;
        return -1; // or any other appropriate default value
    }

    int totalSize = root->size;
    int middle = totalSize / 2 + 1;

    AvlNode* current = root;
    while (current != nullptr) {
        int leftSize = (current->left != nullptr) ? current->left->size : 0;

        if (leftSize + current->count >= middle) {
            return current->element;
        } else {
            middle -= leftSize + current->count;
            current = current->right;
        }
    }

    return -1; // or any other appropriate default value
}


};

#endif