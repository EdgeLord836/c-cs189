#pragma once
template <typename T>
class List
{
	struct ListNode
	{
		ListNode()
		{
		}
		T mData;
		ListNode* mPrev;
		ListNode* mNext;
	};

	ListNode* mHead;
	ListNode* mTail;
	T mUndefined;
	int mSize = 0;

public:
	List()
	{
		// Getting Head and Tail correct is not part of the Big 3.  It is hella mega required no matter what.
		//mHead = nullptr;
		//mTail = nullptr;// bleh.  Full of crash.
		mHead = new ListNode;
		mTail = new ListNode;
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;
		mTail->mPrev = mHead;// This RULES.  We always know we have 2 nodes, so we never have to check for null.
		mTail->mNext = nullptr;
	}
	List( const List& tOther )
	{
	}
	List& operator = ( const List& tRHS )
	{
	}
	~List()
	{
	}

	void PushFront( const T& tWhat )
	{
	}
	void PopFront()
	{
	}
	T& Front()
	{
		return mUndefined;
	}

	void PushBack( const T& tWhat )
	{
	}
	void PopBack()
	{
	}
	T& Back()
	{
		return mUndefined;
	}

	int Size() const
	{
		return 0;
	}
	void Clear()
	{
	}

	T& At( int tWhere ) const
	{
	}

	///////////////////////////////////////////////////////////////////
	// Iterators
	class Iterator
	{
		ListNode* mCurrent;
		T mUndefined;
	public:
		Iterator( ListNode* tStart )
		{
		}
		T& GetData()
		{
			return mUndefined;
		}
		void Next()// As in "Move to the next item please"
		{
		}
		bool IsEqual( const Iterator& rhs )
		{
			return false;
		}
	};

	Iterator Insert( Iterator tWhere, const T& tWhat )
	{
	}
	Iterator Erase( Iterator tWhere )
	{
	}
	Iterator Begin()
	{
		// First good data
		return Iterator( nullptr );
	}
	Iterator End()
	{
		// First Bad data
		return Iterator( nullptr );
	}
};

