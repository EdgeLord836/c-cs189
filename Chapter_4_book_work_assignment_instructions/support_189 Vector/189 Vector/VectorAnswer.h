#pragma once
// I am going to match the names that STL uses so you don't get confused in the real world.  I'm skipping operator [] for a specific reason that
// doesn't come up for a few weeks.

template<typename T> // Whatever main puts in the <> gets find-replaced to every "T"
class Vector
{
	T* mData;
	int mSize; // Size is how much data.  Capacity is how much memory.
	int mCapacity;// For testing purposes, initialize this to 15.  Whenever you allocate new memory, double it.

	T mUndefined;// Lots of STL functions say that doing something naughty gets "undefined behavior".  It could throw, crash, make you eggs, or return nonsense.
				// Return this undefined one if anybody ever tries to go out of bounds. 
				// I've also seen this done with a static.  I'll do that in List later

public:
	Vector()// O(1)
	{
		mSize = 0;
		mData = nullptr;
		Reserve( 15 ); // If you put a new in here, you'd be duplicating the reserve code.  Feel free to call non-virtual methods of your own here.
		// (You can't call a virtual method because the whole object isn't finished constructing yet.)
	}
	// Big 3
	~Vector()
	{
		// Free all memory
		delete[] mData; // You new with [], you delete with []
	}
	Vector( const Vector<T>& tOther ) : Vector()// O(n)
	{
		*this = tOther;// Told you it was sneaky.  Calling = from copy does make me nervous though.  I don't know if it would hold up if something inherited from Vector
	}
	// There is a sneaky way to combine assignment and copy by having one call the other.  They are 90% the same.
	Vector& operator =( const Vector<T>& tRHS )// O(n)
	{
		// I didn't take off for this, and next time I'll put it in the template.  It keeps me from assigning myself to myself.  
		// Which would crash as I deleted my own memory to make space for my own memory
		if( &tRHS == this )
			return *this;

		Clear();
		for( int i = 0; i < tRHS.mSize; i++ ) // Size should be const, but I said not to change things.
			PushBack( tRHS.mData[i] );
		// Always call your own code instead of duplicating it

		return *this; // This line is weird so I'm just giving it to ya.  It has to be the last line.  It's just the definition of an =
	}
	void PushBack( const T& tItem )// O(1)
	{
		if( mSize == mCapacity )
			Reserve( 2 * mCapacity );// If I need more space, get it first

		mData[mSize] = tItem;
		mSize++;
	}
	void PopBack()// O(1)
	{
		mSize--;
	}
	T& At( int tWhere )// O(1)
	{
		if( tWhere < 0 || tWhere >= mSize )// Always range check
			return mUndefined;

		return mData[tWhere];
	}
	void Clear()// O(1)
	{
		mSize = 0;// At start, my memory is full of junk.  Who cares if it is now full of junk that looks like it used to be data?  Still junk.
	}
	int Size()// O(1)
	{
		return mSize;
	}
	void Reserve( int tCount )// O(n)
	{
		// This is the hard one.  The rest are 1-4 lines.  I'm not saying reducing line count is something anybody cares about,
		// I'm just pointing out the scope.  Sometimes people get to fifty lines on something and then complain it's too hard.

		// I was torn on if asking for less memory than you had already would shrink you.  So I looked it up.
		// "In all other cases, the function call does not cause a reallocation and the vector capacity is not affected."
		if( tCount <= mCapacity )
			return;

		T* tNewMem = new T[tCount];
		for( int i = 0; i < mSize; i++ )
			tNewMem[i] = mData[i];

		if( mData )// good to always check
			delete[] mData;
		mData = tNewMem;
		mCapacity = tCount;
	}
	int Capacity()// O(1)
	{
		return mCapacity;
	}
};