#pragma once
#include <list>
#include <iostream> // For debugging

template <typename T>
class Tree
{
	struct TreeNode
	{
		enum BalanceType
		{
			AVL_OK,
			AVL_LEFT_LEFT,
			AVL_LEFT_RIGHT,
			AVL_RIGHT_RIGHT,
			AVL_RIGHT_LEFT
		};
		T mData;
		TreeNode* mLeft;
		TreeNode* mRight;
		TreeNode* mParent;
		int mHeight;

		TreeNode()
		{
			mLeft = nullptr;
			mRight = nullptr;
			mParent = nullptr;
			mHeight = 0;
		}
		TreeNode( T tData ) : TreeNode()
		{
			mData = tData;
			mLeft = nullptr;
			mRight = nullptr;
			mParent = nullptr;
			mHeight = 0;
		}
		BalanceType GetBalanceType()
		{
			int tLeft = mLeft?mLeft->mHeight:-1;
			int tRight = mRight?mRight->mHeight:-1;

			if( tRight - tLeft >= 2 )
			{
				//Right...
				int tRightLeft = mRight->mLeft?mRight->mLeft->mHeight:-1;
				int tRightRight = mRight->mRight?mRight->mRight->mHeight:-1;

				if( tRightLeft > tRightRight )
					return TreeNode::AVL_RIGHT_LEFT;
				else
					return TreeNode::AVL_RIGHT_RIGHT;
			}
			else if( tLeft - tRight >= 2 )
			{
				int tLeftLeft = mLeft->mLeft?mLeft->mLeft->mHeight:-1;
				int tLeftRight = mLeft->mRight?mLeft->mRight->mHeight:-1;

				if( tLeftLeft > tLeftRight )
					return TreeNode::AVL_LEFT_LEFT;
				else
					return TreeNode::AVL_LEFT_RIGHT;
			}

			return TreeNode::AVL_OK;
		}
	};
	TreeNode* mHead;
	bool mDebugOn = false; // Used to add couts to Dump.

	void MasterRebalance()
	{
		// This is the easy version where instead of tracking the exact path we need to check, we just hit everything
		// This is bad because it turns our operations in to O(n) instead of O(log n)
		MeasureTree( mHead );
		BalanceTree( mHead );
		MeasureTree( mHead );

		// Part two of the balance homework gets rid of this function entirely since updating is done in the Add, Rotate, and Remove themselves.
	}

	void MeasureTree( TreeNode* tNode )
	{
		// Set my left height, set my right height, determine my height
		if( tNode == nullptr )
			return;
		if( tNode->mLeft )
			MeasureTree( tNode->mLeft );
		if( tNode->mRight )
			MeasureTree( tNode->mRight );

		int tLeft = tNode->mLeft?tNode->mLeft->mHeight:-1;
		int tRight = tNode->mRight?tNode->mRight->mHeight:-1;
		tNode->mHeight = tLeft > tRight?tLeft + 1:tRight + 1;

		// This whole function is gone in part 2 of the rebalance homework
	}

	// The balance code works.  You are just changing what node you are passing in.  Every node, or one of a list of nodes
	// I'd recomend changing the name of this to BalanceNode
	bool BalanceTree( TreeNode* tNode )
	{
		if( tNode == nullptr )
			return false;

		// Part one of the homework changes that arg to the full path.  This function becomes no longer recursive.  Instead of recurssing left and right, just loop through the stack.

		// Part two of the homework updates this so that the heights of the nodes you process are updated as you go (and in the rotate code)

// vvvvvvvvvvvvvvvvvvvvvvvvvvvv Delete this
		// To balance a tree means to balance my left, balance my right, and only if nothing happened below us do we keep going.
		// This is a common pattern too.  An early exit from an exhaustive search.
		bool tSuccess = BalanceTree( tNode->mLeft );
		if( !tSuccess )
			tSuccess = BalanceTree( tNode->mRight );
		if( !tSuccess )
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		{
			typename TreeNode::BalanceType tCheck = tNode->GetBalanceType();
			if( tCheck != TreeNode::AVL_OK )
			{
				bool tHeadCheck = mHead == tNode;

				if( tCheck == TreeNode::AVL_LEFT_LEFT )
					tNode = RotateLeftUp( tNode );
				else if( tCheck == TreeNode::AVL_LEFT_RIGHT )
				{
					tNode->mLeft = RotateRightUp( tNode->mLeft );
					tNode = RotateLeftUp( tNode );
				}
				else if( tCheck == TreeNode::AVL_RIGHT_RIGHT )
					tNode = RotateRightUp( tNode );
				else if( tCheck == TreeNode::AVL_RIGHT_LEFT )
				{
					tNode->mRight = RotateLeftUp( tNode->mLeft );
					tNode = RotateRightUp( tNode );
				}
				if( tHeadCheck )
					mHead = tNode;

				return true;
			}

			return false;
		}
		return false;
	}

	// Part two of the balance homework needs you to update the heights of the nodes when you do these rotations.
	TreeNode* RotateRightUp( TreeNode* tNode )
	{
		// Using variable names from book pg 257 to make easier to read:
		TreeNode* P = tNode;
		TreeNode* Q = P->mRight;

		P->mRight = Q->mLeft;
		Q->mLeft = P;

		Q->mParent = P->mParent;
		P->mParent = Q;

		return Q;
	}

	TreeNode* RotateLeftUp( TreeNode* tNode )
	{
		TreeNode* P = tNode;
		TreeNode* Q = P->mLeft;

		P->mLeft = Q->mRight;
		Q->mRight = P;

		Q->mParent = P->mParent;
		P->mParent = Q;

		return Q;
	}

	void CopyTree( TreeNode* tNode )
	{
		if( tNode != nullptr )
		{
			Add( tNode->mData );
			CopyTree( tNode->mLeft );
			CopyTree( tNode->mRight );
		}

	}
	void DeleteTree( TreeNode* tNode )
	{
		if( tNode != nullptr )
		{
			DeleteTree( tNode->mLeft );
			DeleteTree( tNode->mRight );
			delete tNode;
		}
	}
	void DumpTree( std::list<T>* tLeftToRight, TreeNode* tNode ) const
	{
		if( tNode != nullptr )
		{
			if( tNode->mLeft )
			{
				if( mDebugOn )
					std::cout << "L ";
				DumpTree( tLeftToRight, tNode->mLeft );
			}

			// To help debug avl balancing, I'm going to make this thing output.  THis is generally a naughty thing to do outside of main because it makes a dependency between your code and the console.
			if( mDebugOn )
				std::cout << tNode->mData << "(" << tNode->mHeight << ")" << " ";

			if( tLeftToRight )
				tLeftToRight->push_back( tNode->mData ); // Without the extra couts, this is the real part of recursive dump

			if( tNode->mRight )
			{
				if( mDebugOn )
					std::cout << "R ";
				DumpTree( tLeftToRight, tNode->mRight );
			}
			if( mDebugOn )
				std::cout << "^ ";
		}
	}


	// Add, contain, and remove all want to know the same thing.  Where they should activate.
	// Add wants to know what the new node should attach to, contains just wants to see if it is there, and remove wants to know who to mark dead.

	// So all I did was copy the duplicated code here, remove the add/contain specific code, and return the node.

	// For the balance homework, maybe add a stack pointer arg?  Or since PrivateFind isn't part of the balance homework, you can just leave the code in add and remove
	// Stacks are kinda limiting even if thematically correct.  I'd probably pass a list in like I did with dump
	TreeNode* PrivateFind( T tWhat )
	{
		if( mHead == nullptr )
			return nullptr;

		TreeNode* tWalker = mHead;
		while( true )
		{
			if( tWalker->mData == tWhat )
				return tWalker;
			else if( tWalker->mData > tWhat )
			{
				if( tWalker->mLeft == nullptr )
					return tWalker;
				else
					tWalker = tWalker->mLeft;
			}
			else
			{
				if( tWalker->mRight == nullptr )
					return tWalker;
				else
					tWalker = tWalker->mRight;
			}
		}
	}

public:
	Tree()
	{
		mHead = nullptr;
		mDebugOn = true;
	}
	Tree( const Tree& tOther ) : Tree()
	{
		std::list<T> tAllNodes;
		tOther.Dump( &tAllNodes );// I'm using dump instead of copy to intentionally force balances to happen in a reliable order.  Just for grading balances.

		for( auto iter = tAllNodes.begin(); iter != tAllNodes.end(); ++iter )
			Add( *iter );
	}
	Tree& operator= ( const Tree& tRHS )
	{
		DeleteTree( mHead );
		mHead = nullptr;

		std::list<T> tAllNodes;
		tRHS.Dump( &tAllNodes );

		for( auto iter = tAllNodes.begin(); iter != tAllNodes.end(); ++iter )
			Add( *iter );

		return *this;
	}
	~Tree()
	{
		DeleteTree( mHead );
	}

	void SetDebug( bool tOn )
	{
		mDebugOn = tOn;
	}

	void Add( T tWhat )
	{
		if( mHead == nullptr )
		{
			mHead = new TreeNode( tWhat );
			return;
		}

		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound->mData == tWhat )
			return;// no dupes
		else if( tFound->mData > tWhat )
		{
			tFound->mLeft = new TreeNode( tWhat );
			tFound->mLeft->mParent = tFound;
		}
		else
		{
			tFound->mRight = new TreeNode( tWhat );
			tFound->mRight->mParent = tFound;
		}

		MasterRebalance();
	}

	bool Contains( T tWhat )
	{
		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound != nullptr && tFound->mData == tWhat )
			return true;

		return false;
	}

	void Remove( T tWhat )
	{
		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound == nullptr || tFound->mData != tWhat )
			return;
		if( mHead == nullptr )
			return;

		bool tHeadRemoval = false;
		if( mHead == tFound )
			tHeadRemoval = true;

		if( tFound->mRight == nullptr && tFound->mLeft == nullptr ) // 0 child
		{
			if( tHeadRemoval )// no parent
			{
				delete mHead;
				mHead = nullptr;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = nullptr;
				else
					tFound->mParent->mRight = nullptr;
				delete tFound;
			}
		}
		else if( tFound->mLeft != nullptr && tFound->mRight == nullptr )// left child
		{
			if( tHeadRemoval )
			{
				TreeNode* tOldHead = mHead;
				delete tOldHead;
				mHead = tOldHead->mLeft;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = tFound->mLeft;
				else
					tFound->mParent->mRight = tFound->mLeft;
				tFound->mLeft->mParent = tFound->mParent;
				delete tFound;
			}
		}
		else if( tFound->mLeft == nullptr && tFound->mRight != nullptr )// right child
		{
			if( tHeadRemoval )
			{
				TreeNode* tOldHead = mHead;
				delete tOldHead;
				mHead = tOldHead->mRight;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = tFound->mRight;
				else
					tFound->mParent->mRight = tFound->mRight;
				tFound->mRight->mParent = tFound->mParent;
				delete tFound;
			}
		}
		else // two child (No special head case since the head node doesn't change in a two child)
		{
			TreeNode* tWalker = tFound;
			tWalker = tWalker->mRight;
			while( tWalker->mLeft != nullptr )
				tWalker = tWalker->mLeft;

			T tTransplant = tWalker->mData;
			tFound->mData = tTransplant;
			if( tWalker->mRight != nullptr )// End of the walk to the left had a right (we know it doesn't have a left)
			{
				if( tWalker->mParent == tFound )
					tWalker->mParent->mRight = tWalker->mRight;
				else
					tWalker->mParent->mLeft = tWalker->mRight;
				tWalker->mRight->mParent = tWalker->mParent;
			}

			delete tWalker;
		}

		MasterRebalance();
	}

	void Dump( std::list<T>* tLeftToRight ) const
	{
		DumpTree( tLeftToRight, mHead );
		std::cout << std::endl;// Naughty to have output in utility class, but need to debug
	}
};

