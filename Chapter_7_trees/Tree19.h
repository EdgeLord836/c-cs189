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
	void CopyTree(TreeNode *tNode)
	{
		if (tNode != nullptr)
		{
		}

	}

	// Pack this list with the data from that node down, small to large
	void DumpTree(std::list<T> *tLeftToRight, TreeNode *tNode)
	{
		if (tNode != nullptr)
		{
		}
	}

	// Delete that node and everything under it.
	void DeleteTree(TreeNode *tNode)
	{
		if (tNode != nullptr)
		{
		}
	}

	// Return either the node holding that data, 
	// or the node that would be the parent of that data if it isn't here.
	// This is a single path, so it is a loop.
	TreeNode *PrivateFind(const T &tWhat)
	{
		return nullptr;
	}

public:
	Tree()
	{
		mHead = nullptr;
	}
	Tree(const Tree &other) : Tree()
	{
		CopyTree(other.mHead);
	}
	Tree & operator= (const Tree & other)
	{
		if (this != &other)
			CopyTree(other.mHead);

		DeleteTree(mHead);
		mHead = nullptr;

		return *this;
	}
	~Tree()
	{
		DeleteTree(mHead);
	}

	void Add(T tWhat)
	{
		if (mHead == nullptr)
		{
			mHead = new TreeNode(tWhat);
			return;
		}

		TreeNode *tWalker = mHead;
		while (true)
		{
			if (tWalker->mData == tWhat)
			{
				tWalker->mIsDead = false;// Might already be false.  Don't care.
				break;
			}
			else if (tWalker->mData > tWhat)// I want to go left
			{
				if (tWalker->mLeft == nullptr)// But I'm at the end so I'll just put this there.
				{
					tWalker->mLeft = new TreeNode(tWhat);
					tWalker->mLeft->mParent = tWalker;
					break;
				}
				else
					tWalker = tWalker->mLeft;
			}
			else
				if (tWalker->mRight == nullptr)
				{
					tWalker->mRight = new TreeNode(tWhat);
					tWalker->mRight->mParent = tWalker;
					break;
				}
				else
					tWalker = tWalker->mRight;
		}
	}

	void Remove(T tWhat)
	{
		if (mHead == nullptr)
			return;
		if (mHead->mData == tWhat)
		{
			mHead->mIsDead = true;
		}

		TreeNode *tWalker = mHead;
		while (true)
		{
			if (tWalker->mData > tWhat)// I want to go left
			{
				if (tWalker->mLeft == nullptr)// But I can't
					break;
				else if (tWalker->mLeft->mData == tWhat)// ...or I don't need to because it's right there
				{
					tWalker->mLeft->mIsDead = true;
					break;
				}
				else
					tWalker = tWalker->mLeft;// I'll go left and keep looking
			}
			else
			{
				if (tWalker->mRight == nullptr)
					break;
				else if (tWalker->mRight->mData == tWhat)
				{
					tWalker->mRight->mIsDead = true;
					break;
				}
				else
					tWalker = tWalker->mRight;
			}
		}
	}

	bool Contains(T tWhat)
	{
		if (mHead == nullptr)
			return false;
		TreeNode *tWalker = mHead;
		while (true)
		{
			if (tWalker->mData == tWhat)
			{
				return !tWalker->mIsDead;
			}
			else if (tWalker->mData > tWhat)
			{
				if (tWalker->mLeft == nullptr)
					return false;
				else
					tWalker = tWalker->mLeft;
			}
			else
			{
				if (tWalker->mRight == nullptr)
					return false;
				else
					tWalker = tWalker->mRight;
			}

		}
		return false;
	}
	void Dump(std::list<T> *tLeftToRight)
	{
		DumpTree(tLeftToRight, mHead);
	}
};

