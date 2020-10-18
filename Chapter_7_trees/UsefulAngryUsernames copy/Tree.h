#pragma once
#include <list>
#include <iostream> // For debugging.  Only main should have cout for real

template <typename T>
class Tree
{
	struct TreeNode
	{
		T mData;
		TreeNode *mLeft = nullptr;
		TreeNode *mRight = nullptr;
		TreeNode *mParent = nullptr;

		bool mIsDead = false;

		TreeNode()
		{
		}
		TreeNode(T tData) : TreeNode()
		{
			mData = tData;
		}
	};
	TreeNode *mHead;

	// This tree wants a copy of that node and all beneath it
	TreeNode *CopyTree(TreeNode *src) {
		if (src == nullptr) return nullptr;
    TreeNode *node = new TreeNode(src->mData);
    node->mLeft = CopyTree(src->mLeft);
    node->mRight = CopyTree(src->mRight);
    return node;
	}

	// Pack this list with the data from that node down, small to large
	void DumpTree(std::list<T> *tLeftToRight, TreeNode *tNode) {
		if (tNode == nullptr) return;
    DumpTree(tLeftToRight, tNode->mLeft);
    tLeftToRight->push_back(tNode->mData);
    DumpTree(tLeftToRight, tNode->mRight);
	}

	// Delete that node and everything under it.
	void DeleteTree(TreeNode *tNode) {
		if (tNode == nullptr) return;
    DeleteTree(tNode->mLeft);
    DeleteTree(tNode->mRight);
    delete tNode;
	}

	// Return either the node holding that data, 
	// or the node that would be the parent of that data if it isn't here.
	// This is a single path, so it is a loop.
	TreeNode *PrivateFind(const T &tWhat) {
		if (mHead == nullptr)
			return nullptr;
		TreeNode *tWalker = mHead;
		while (true) {
			if (tWalker->mData == tWhat)
				return tWalker;
			else if (tWalker->mData > tWhat) {
				if (tWalker->mLeft == nullptr)
					return tWalker;
				else
					tWalker = tWalker->mLeft;
			} else {
				if (tWalker->mRight == nullptr)
					return tWalker;
				else
					tWalker = tWalker->mRight;
			}
    }
	}

public:
	Tree() {
		mHead = nullptr;
	}

	Tree(const Tree &other) : Tree() {
		mHead = CopyTree(other.mHead);
	}

	Tree & operator= (const Tree & other) {
		if (this != &other) {
      DeleteTree(this->mHead);
      this->mHead = CopyTree(other.mHead);
    }
    return *this;
	}

	~Tree() {
		DeleteTree(mHead);
	}

	void Add(T tWhat) {
    TreeNode *node = PrivateFind(tWhat);
		if (node == nullptr) {
			mHead = new TreeNode(tWhat);
			return;
		}
    if (node->mData == tWhat) return;
    if (node->mData > tWhat) {
      node->mLeft = new TreeNode(tWhat);
      node->mLeft->mParent = node;
    }
		else {
      node->mRight = new TreeNode(tWhat);
      node->mRight->mParent = node;
    }
	}

	void Remove(T tWhat) {
		TreeNode *node = PrivateFind(tWhat);
		if (node == nullptr) return;
    if (node->mData == tWhat) {
      TreeNode *node_to_delete = node;
      if (node == node->mParent->mLeft)
        node->mParent->mLeft = nullptr;
      else
        node->mParent->mRight = nullptr;
      std::list<int> children;      
      DumpTree(&children, node_to_delete->mLeft);
      DumpTree(&children, node_to_delete->mRight);
      for(std::list<int>::iterator i = children.begin(); i != children.end(); ++i)
        Add(*i);
      DeleteTree(node_to_delete);
    }
	}

	bool Contains(T tWhat) {
		TreeNode *node = PrivateFind(tWhat);
		if (node == nullptr) return false;
    return node->mData == tWhat;
	}

	void Dump(std::list<T> *tLeftToRight) {
		DumpTree(tLeftToRight, mHead);
	}
};