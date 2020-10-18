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
		ListNode* mPrev = nullptr;
		ListNode* mNext = nullptr;
	};

	ListNode* mHead = nullptr;
	ListNode* mTail = nullptr;
	mutable T mUndefined;
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
		*this = tOther;
	}
	List& operator = ( const List& tRHS )
	{
		if( this == &tRHS )
			return *this;

		for( int i = 0; i < tRHS.Size(); i++ )
			PushBack( tRHS.At( i ) );
	
		return *this;
	}
	~List()
	{
		Clear();
		delete mHead;
		delete mTail;
	}

	void PushFront( const T& tWhat )
	{
		Insert( Begin(), tWhat );// Totally stealing this
	}
	void PopFront()
	{
		Erase( Begin() );
	}
	T& Front()
	{
		return mHead->mNext->mData; // At( 0 );
	}

	void PushBack( const T& tWhat )
	{
		Insert( End(), tWhat );
	}
	void PopBack()
	{
		Erase( Iterator( mTail->mPrev ) );
	}
	T& Back()
	{
		return mTail->mPrev->mData;// At( Size() - 1 ) would just be slow
	}

	int Size() const
	{
		return mSize;
	}
	void Clear()
	{
		while( Size() > 0 )
			PopBack();
	}

	T& At( int tWhere ) const
	{
		if( tWhere >= Size() )
			return mUndefined;

		ListNode* tWalker = mHead->mNext;
		for( int i = 0; i < tWhere; i++ )
			tWalker = tWalker->mNext;
		return tWalker->mData;
	}

	///////////////////////////////////////////////////////////////////
	// Iterators
	class Iterator
	{
		friend List;

		ListNode* mCurrent = nullptr;
		T mUndefined;
	public:
		Iterator( ListNode* tStart )
		{
			mCurrent = tStart;
		}
		T& GetData()
		{
			return mCurrent->mData;
		}
		void Next()// As in "Move to the next item please"
		{
			mCurrent = mCurrent->mNext;
		}
		bool IsEqual( const Iterator& rhs )
		{
			return mCurrent == rhs.mCurrent;
		}
	};

	Iterator Insert( Iterator tWhere, const T& tWhat )
	{// Insert before tWhere, return iterator to first new node
		ListNode* tNewGuy = new ListNode;
		tNewGuy->mData = tWhat;

		tNewGuy->mPrev = tWhere.mCurrent->mPrev;
		tWhere.mCurrent->mPrev->mNext = tNewGuy;

		tNewGuy->mNext = tWhere.mCurrent;
		tWhere.mCurrent->mPrev = tNewGuy;

		mSize++;
		return Iterator( tNewGuy );
	}
	Iterator Erase( Iterator tWhere )
	{// Erase this one, return iterator to one after the departed
		if( tWhere.mCurrent == mTail || tWhere.mCurrent == mHead )
			return End();

		tWhere.mCurrent->mPrev->mNext = tWhere.mCurrent->mNext;
		tWhere.mCurrent->mNext->mPrev = tWhere.mCurrent->mPrev;

		ListNode* tToReturn = tWhere.mCurrent->mNext;
		delete tWhere.mCurrent;
		mSize--;
		return Iterator( tToReturn );
	}
	Iterator Begin()
	{
		// First good data
		return Iterator( mHead->mNext );
	}
	Iterator End()
	{
		// First Bad data
		return Iterator( mTail );
	}
};

