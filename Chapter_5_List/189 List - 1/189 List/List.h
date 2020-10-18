#pragma once
template <typename T>
class List
{
	struct ListNode
	{
		ListNode() { }
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

	List(const List& tOther)
	{
		mHead = new ListNode;
		mTail = new ListNode;

		mHead->mNext = mTail;
		mHead->mPrev = nullptr;
		mTail->mPrev = mHead;
		mTail->mNext = nullptr;

		ListNode *temp = tOther.mHead->mNext;
		int sizeLHS = 0;
		while (temp->mNext != nullptr)
		{
			PushBack(temp->mData);
			sizeLHS += 1;
			temp = temp->mNext;
		}

		this->mSize = sizeLHS;
	}

	List& operator = ( const List& tRHS )
	{
		Clear();

		this->mHead = new ListNode;
		this->mTail = new ListNode;
		this->mHead->mNext = this->mTail;
			this->mHead->mPrev = nullptr;
			this->mTail->mPrev = this->mHead;
			this->mTail->mNext = nullptr;

		ListNode *temp = tRHS.mHead->mNext;
		int sizeLHS = 0;
		while (temp->mNext != nullptr)
		{
			this->PushBack(temp->mData);
			sizeLHS += 1;
			temp = temp->mNext;
		}
			
		this->mSize = sizeLHS;
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
		ListNode* tNewBaby = new ListNode;
		ListNode* tNextHead = mHead->mNext;

		tNewBaby->mData = tWhat;
		tNewBaby->mNext = tNextHead;
		tNewBaby->mPrev = mHead;

		tNextHead->mPrev = tNewBaby;
		mHead->mNext = tNewBaby;
	}

	void PopFront()
	{
		if (mSize == 0) return;

		ListNode* tDeath = mHead->mNext;
		ListNode* tNextDeath = tDeath->mNext;

		delete tDeath;

		tNextDeath->mPrev = mHead;
		mHead->mNext = tNextDeath;
	}

	T& Front()
	{
		if (mSize == 0) return mUndefined;
		return mHead->mNext->mData;
	}

	void PushBack( const T& tWhat )
	{
		ListNode* node = new ListNode;

		node->mNext = nullptr;
		node->mPrev = mTail;

		mTail->mNext = node;
		mTail->mData = tWhat;
		mTail = node;
		mSize += 1;
	}

	void PopBack()
	{
		if (mSize == 0) return;

		mTail = mTail->mPrev;
		delete mTail->mNext;
		mTail->mNext = nullptr;
		mSize -= 1;
	}

	T& Back()
	{
		if (mSize == 0) return mUndefined;
		return mTail->mPrev->mData;
	}

	int Size() const
	{
		int tAmount = 0;
		ListNode* temp = mHead->mNext;
		while (temp != mTail)
		{
			tAmount++;
			temp = temp->mNext;
		}
		return tAmount;
	}

	void Clear()
	{
		while (mSize != 0)
			PopBack();
	}

	T& At( int tWhere ) const
	{
		int tSearch = 0;
		ListNode* temp = mHead->mNext;
		while (temp != mTail)
		{
			if (tSearch == tWhere)
				return temp->mData;
			temp = temp->mNext;
			tSearch++;
		}
		return mTail->mData;
	}

	///////////////////////////////////////////////////////////////////
	// Iterators
	class Iterator
	{
		friend List;// friends function

		ListNode* mCurrent;
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
	{
		ListNode* tCool = tWhere.mCurrent;
		ListNode* tFresh = new ListNode;

		tFresh->mData = tWhat;
		tFresh->mNext = tCool->mNext;
		tFresh->mPrev = tCool;

		tCool->mNext = tFresh;
		tFresh->mNext->mPrev = tFresh;
		return Iterator(tFresh);
	}
	Iterator Erase( Iterator tWhere )
	{
		if (mSize == 0)
			return tWhere;
		ListNode* tDeath = tWhere.mCurrent;
		tDeath->mPrev->mNext = tDeath->mNext;
		tDeath->mNext->mPrev = tDeath->mPrev;

		ListNode* tBoomerang = tDeath->mNext;
		delete tDeath;
		return Iterator(tBoomerang);
	}

	Iterator Begin()
	{
		// First good data
		return Iterator(mHead->mNext);
	}
	Iterator End()
	{
		// First Bad data
		return Iterator(mTail);
	}
};