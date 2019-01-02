#ifndef BINARYSEARCHTREE_CPP
#define BINARYSEARCHTREE_CPP

#include "BinarySearchTree.h"
//#include "BinaryNodeTree.h"
#include <cmath>
#include <string>

using namespace std;

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: insertInorder(BinaryNode<ItemType>* subTreePtr,
																	BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
	{
		return newNodePtr;
	}

	else if (subTreePtr->getItem() > newNodePtr->getItem())
	{
		newNodePtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(newNodePtr);
		return subTreePtr;
	}

	else
	{
		newNodePtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(newNodePtr);
		return subTreePtr;
	}
}

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: removeValue(BinaryNode<ItemType>* subTreePtr,
																const ItemType target,
																bool& success)
{
	BinaryNode <ItemType>* tempPtr = nullptr;
	
	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}

	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else if (subTreePtr->getItem() > target)
	{
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
	else if (subTreePtr->getItem() > target)
	{
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
	else
	{
		tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}
}

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: removeNode(BinaryNode<ItemType>* nodePtr)
{
	BinaryNode <ItemType>* tempPtr = nullptr;
	BinaryNode <ItemType>* nodeToConnectPtr = nullptr;
	ItemType newNodeValue;
	if (nodePtr->isLeaf())
	{
		// Remove leaf from the tree
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}

	else if (nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() != nullptr)
	{
		tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}

	else
	{
		if (nodePtr->getLeftChildPtr() != nullptr)
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		else
			nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}	
}

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
																		ItemType& inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		// This is the node you want; it has no left child, but it might have a right subtree
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
    {
        nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), 
													inorderSuccessor));
        return nodePtr;
    }

}

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: findNode(BinaryNode<ItemType>* treePtr,
																const ItemType& target) const
{
	if (treePtr == nullptr)
		return nullptr;
	else if (target == treePtr->getItem())
		return treePtr;
	else if (target < treePtr->getItem())
		return findNode(treePtr->getLeftChildPtr(), target);
	else
		return findNode(treePtr->getRightChildPtr(), target);
}
   
template <class ItemType>
BinarySearchTree<ItemType> :: BinarySearchTree() : rootPtr(nullptr)
{
}
 
template <class ItemType>
BinarySearchTree<ItemType> :: BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}

template <class ItemType>
BinarySearchTree<ItemType> ::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr);
}

template <class ItemType>
BinarySearchTree<ItemType> :: ~BinarySearchTree()
{
	clear();
}

template <class ItemType>
bool BinarySearchTree<ItemType> ::isEmpty() const
{
	return rootPtr == nullptr;
}

template <class ItemType>
int BinarySearchTree<ItemType> ::getHeight() const
{
    return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
}

template <class ItemType>
int BinarySearchTree<ItemType> ::getNumberOfNodes() const
{
	return BinaryNodeTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType> ::getRootData() const
{
	return rootPtr->getItem();
}

template <class ItemType>
void BinarySearchTree<ItemType> ::setRootData(const ItemType& newData) const
{
	rootPtr->setItem(newData);
}

template <class ItemType>
bool BinarySearchTree<ItemType> ::add(const ItemType& newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = insertInorder(rootPtr, newNodePtr);
	return true;
}

template <class ItemType>
bool BinarySearchTree<ItemType> ::remove(const ItemType& anEntry)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, anEntry, success);
	return success;
}

template <class ItemType>
void BinarySearchTree<ItemType> ::clear()
{

}

template <class ItemType>
ItemType BinarySearchTree<ItemType> ::getEntry(const ItemType& anEntry) const
{
	return findNode(rootPtr, anEntry)->getItem();
}

template <class ItemType>
bool BinarySearchTree<ItemType> ::contains(const ItemType& anEntry) const
{
	if (findNode(rootPtr, anEntry) != nullptr)
		return true;
	else
		return false;
}

template <class ItemType>
void BinarySearchTree<ItemType> ::preorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::preorder(visit, rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType> ::inorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::inorder(visit, rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType> ::postorderTraverse(void visit(ItemType&)) const
{
	BinaryNodeTree<ItemType>::postorder(visit, rootPtr);
}

template <class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType> ::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{

}

template<class ItemType>
void BinarySearchTree<ItemType>::display(BinaryNode<ItemType>* ptr, int level)
{
    int i;

    
    if (ptr != nullptr)
    {
        display(ptr->getRightChildPtr(), level + 1);
        printf("\n");
        if (ptr == rootPtr)
            cout << "Root->";
        for (i = 0; i < level && ptr != rootPtr; i++)
            cout << "          ";
        
        string name = ptr->getItem();
        for(int i = 0; i < 2; i++){
            cout << name[i];
        }
        
        display(ptr->getLeftChildPtr(), level + 1);
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::displayTree()
{
    display(rootPtr, 0);
    cout << endl;
}

#endif
