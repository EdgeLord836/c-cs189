#pragma once
template <typename T>
class List {
	struct ListNode
	{
		ListNode(){ }
		T mData; //data
		ListNode* mPrev;// who is before
		ListNode* mNext;// who is after
	};

	ListNode* mHead;// no valid or store data
	ListNode* mTail;// no valid or store data, chillin
	T mUndefined;// if you ask for stupid data, you win stupid prizes
	int mSize = 0;

public:
	List() { //default construct doesnt change
		// Getting Head and Tail correct is not part of the Big 3.  It is hella mega required no matter what.
		//mHead = nullptr;
		//mTail = nullptr;// bleh.  Full of crash.
		mHead = new ListNode; // draw new square //end cap, not null //nothing to right of tail /null
		mTail = new ListNode;// two nodes //end cap, not null //nothing to left of head //null
		mHead->mNext = mTail;//head point tails
		mHead->mPrev = nullptr;//connect them
		mTail->mPrev = mHead;//tail point heads //This RULES.  We always know we have 2 nodes, so we never have to check for null.
		mTail->mNext = nullptr; //make new private methods not public methods
	}
	List( const List& tOther ) { //my list copy of his data, my head point to my stuff

    mHead = new ListNode;
    mTail = new ListNode;
    mHead->mNext = mTail;
	  mHead->mPrev = nullptr;
		mTail->mPrev = mHead;
		mTail->mNext = nullptr;

    ListNode *temp = tOther.mHead->mNext;
    int sizeLHS = 0;
    while(temp->mNext != nullptr) {
      PushBack(temp->mData);
      sizeLHS += 1;
      temp = temp->mNext;
    }

    this->mSize = sizeLHS;
	}

	List& operator = ( const List& tRHS ) {
    this->mHead = new ListNode;
    this->mTail = new ListNode;
    this->mHead->mNext = this->mTail;
		this->mHead->mPrev = nullptr;
		this->mTail->mPrev = this->mHead;
		this->mTail->mNext = nullptr;

    ListNode *temp = tRHS.mHead->mNext;
    int sizeLHS = 0;
    while(temp->mNext != nullptr) {
      this->PushBack(temp->mData);
      sizeLHS += 1;
      temp = temp->mNext;
    }

    this->mSize = sizeLHS;
    return *this;
	}

	~List() //if you new it, you have to delete it// do not leave empty // if have 20 nodes, delte 20 nodes
	{
	}

	void PushFront( const T& tWhat ) //ad to the front, (just to the right of heads)
	{
	}
	void PopFront() //? go to head side? //insert everywhere?//
	{
	}
	T& Front() //front and back return data itself
	{
    if (mSize == 0) return mUndefined;
    return mHead->mNext->mData;
	}

	void PushBack( const T& tWhat ) { // on the left of tails
    ListNode* node = new ListNode;
    node->mNext = nullptr;
    node->mPrev = mTail;
    mTail->mNext = node;
    mTail->mData = tWhat;
    mTail = node;
    mSize += 1;
	}

	void PopBack() {
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
		return mSize;
	}
	void Clear() //get rid of data, destructor get rid of memory,
	{
	}

	T& At( int tWhere ) const //return data in here
	{
	}

	///////////////////////////////////////////////////////////////////
	// Iterators
	class Iterator //public inner class// main can use it// // for the userw
	{
		ListNode* mCurrent; //secretly, iterator is point to nodes// this is nodes
		T mUndefined;//same as before, give them undefined
	public:
		Iterator( ListNode* tStart ) //where do you want iterator to start// cant make iterator without this
		{
		}
		T& GetData()
		{
			return mUndefined;
		}
		void Next()// As in "Move to the next item please" //next get rid of, go 1 more node towards the tail
		{
		}
		bool IsEqual( const Iterator& rhs ) //replacing equal sign from normal stl
		{
			return false;
		}
	};

	Iterator Insert( Iterator tWhere, const T& tWhwt )// supposed to return something// insert new node here after tWhere
	{
	}
	Iterator Erase( Iterator tWhere ) //supposed to return something// get rid of iterator //tWhere.mCurrent no need for looping // return somethingw
	{
	}
	Iterator Begin()
	{
		// First good data // using constructor (node) change to something
		return Iterator( nullptr );//keep this dont change
	}
	Iterator End()
	{
		// First Bad data //off the edge// first bad data// // have to change .cpp file// reconnect nodes on either side, delete node too, prevent memory leak
		return Iterator( nullptr );// change which node iterator is talking about
	}
};
