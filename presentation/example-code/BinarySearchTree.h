#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>

#include "nodes/BSTreeNode.h"
#include "src/Comparators.cpp"
#include "exceptions/KeyUsed.h"
#include "exceptions/ItemNotFound.h"

namespace DSLib
{

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key) = less_than<Key>,
    bool (*Equality)(Key, Key) = equal_to<Key>
>
/// A binary search tree class.
/// \param T The data type.
/// \param Key The key type.
/// \param Comparator The function used to compare elements of Key.
/// \param Equality The function used to determine equality of elements of Key.
class BinarySearchTree
{
    public:
        /// Shortcut type alias for the BinarySearchTree of this type.
        typedef BinarySearchTree<T, Key, Comparator, Equality> BST;
        /// Shortcut type alias for the BSTreeNode of this type.
        typedef BSTreeNode<T, Key> BSTNode;

        // Create and destroy BST
        /// Constructs an empty BinarySearchTree.
        BinarySearchTree();
        /// Constructs a BinarySearchTree with a root.
        /// \param aValue The root value in the tree.
        BinarySearchTree(Key aKey, T aValue);
        /// Default destructor.
        ~BinarySearchTree();

        // Modify BST
        /// Add an element.
        /// \param aKey The unique identifier a node has.
        /// \param aVal The data attached to that key.
        /// \throw KeyUsed Thrown if the key has already been used.
        /// \return A reference to this.
        BST& AddElement(const Key& aKey, const T& aVal) throw (KeyUsed<Key>);
        /// Remove an element. Does nothing if key is not found.
        /// \param aKey The unique identifier a node has.
        /// \return A reference to this.
        BST& RemoveElement(const Key& aKey);

        // Check nodes
        /// Checks to see if a Key value is there.
        /// \param aValue The Key to check for.
        /// \return true if found; false otherwise.
        bool Find(const Key& aValue);
        /// Retreives a value.
        /// \param aValue The Key to search for.
        /// \throw ItemNotFound Thrown when the item is not found.
        /// \return The data attached to the key.
        T& Retreive(const Key& aValue);

        // Check state
        /// Checks if the tree is balanced.
        /// \return true if balanced, false otherwise.
        bool IsBalanced();
        /// Gets the tree's size.
        /// \return The number of nodes in the tree.
        int GetSize();

        // Other operations
        /// Clone this tree.
        /// \return A clone of this tree.
        BST Clone();

    private:
        BSTNode* mRoot;
        int mSize;
};

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key),
    bool (*Equality)(Key, Key)
>
BinarySearchTree<T, Key, Comparator, Equality>::BinarySearchTree() :
    mRoot(nullptr), mSize(0) {}

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key),
    bool (*Equality)(Key, Key)
>
BinarySearchTree<T, Key, Comparator, Equality>::
    BinarySearchTree(Key aKey, T aValue) :
    mRoot(new BSTNode(aKey, aValue)), mSize(0) {}

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key),
    bool (*Equality)(Key, Key)
>
BinarySearchTree<T, Key, Comparator, Equality>::~BinarySearchTree()
{
    if (mRoot ->GetLeft())
        mRoot ->DelTree(mRoot ->GetLeft());

    if (mRoot ->GetRight())
        mRoot ->DelTree(mRoot ->GetRight());

    mRoot ->SetLeft(nullptr);
    mRoot ->SetRight(nullptr);

    delete mRoot;
}

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key),
    bool (*Equality)(Key, Key)
>
BinarySearchTree<T, Key, Comparator, Equality>&
    BinarySearchTree<T, Key, Comparator, Equality>::AddElement(const Key& aKey,
                                                               const T& aVal)
                                                               throw (KeyUsed<Key>)
{
    BSTNode* vCurNode = mRoot;
    bool vKeepGoing = true;

    while (vKeepGoing)
    {
        if (vCurNode == nullptr)
        {
            mRoot = new BSTNode(aKey, aVal);
            mSize++;
            vKeepGoing = false;
        }

        else if ((*Comparator)(aKey, mRoot ->GetKey()))
            vCurNode = vCurNode ->GetLeft();

        else if ((*Equality)(aKey, mRoot ->GetKey()))
            throw KeyUsed<Key>(aKey);

        else
            vCurNode = vCurNode ->GetRight();

    }

    return *this;
}

template
<
    typename T,
    typename Key,
    bool (*Comparator)(Key, Key),
    bool (*Equality)(Key, Key)
>
BinarySearchTree<T, Key, Comparator, Equality>&
    BinarySearchTree<T, Key, Comparator, Equality>::RemoveElement(const Key& aKey)
{
    BSTNode* vCurNode   = mRoot;
    BSTNode* vPrev      = nullptr;
    bool vKeepGoing = true;

    while(vKeepGoing)
    {
        if (vCurNode == nullptr)
            vKeepGoing = false;

        else if ((*Equality)(aKey, vCurNode ->GetKey()))
        {
            // Find the optimal spot for deletion
            bool vSpotFound = false;
            BSTNode* vDelHere = vCurNode;

            while (vDelHere ->GetLeft())
                vDelHere = vDelHere ->GetLeft();

            // Swap the values
            T vTmpVal = vCurNode ->GetValue();
            vCurNode ->SetValue(vDelHere ->GetValue());
            vDelHere ->SetValue(vTmpVal);

            Key vTmpKey = vCurNode ->GetKey();
            vCurNode ->SetValue(vDelHere ->GetKey());
            vDelHere ->SetValue(vTmpKey);

            // Do something to the right

            mSize--;
            vKeepGoing = false;
        }

        else if (vCurNode ->GetLeft() == nullptr &&
                 vCurNode ->GetRight() == nullptr)
            vKeepGoing = false;

        else if ((*Comparator)(aKey, vCurNode ->GetKey()))
        {
            vPrev = vCurNode;
            vCurNode = vCurNode ->GetLeft();
        }

        else
        {
            vPrev = vCurNode;
            vCurNode = vCurNode ->GetRight();
        }
    }
}

} // namespace DSLib

#endif
