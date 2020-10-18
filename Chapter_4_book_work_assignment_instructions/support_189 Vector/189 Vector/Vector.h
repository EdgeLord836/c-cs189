#pragma once
// I am going to match the names that STL uses so you don't get confused in the real world.  I'm skipping operator [] for a specific reason that
// doesn't come up for a few weeks.

template<typename T> // Whatever main puts in the <> gets find-replaced to every "T"
class Vector
{
	T* mData;
	int mSize; // Size is how much data.  Capacity is how much memory.
	int mCapacity;// For testing purposes, initialize this to 15.  Whenever you allocate new m1emory, double it.

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
	}
	Vector( const Vector<T>& tOther ) : Vector()// O(n)
	{
	}
	// There is a sneaky way to combine assignment and copy by having one call the other.  They are 90% the same.
	Vector& operator =( const Vector<T>& tRHS )// O(n)
	{
		return *this; // This line is weird so I'm just giving it to ya.  It has to be the last line.  It's just the definition of an =
	}
	void PushBack( const T& tItem )// O(1)
	{
	}
	void PopBack()// O(1)
	{
	}
	T& At( int tWhere )// O(1)
	{
		return mUndefined;
	}
	void Clear()// O(1)
	{
	}
	int Size()// O(1)
	{
		return 0;
	}
	void Reserve( int tCount )// O(n)
	{
		// This is the hard one.  The rest are 1-4 lines.  I'm not saying reducing line count is something anybody cares about,
		// I'm just pointing out the scope.  Sometimes people get to fifty lines on something and then complain it's too hard.
	}
	int Capacity()// O(1)
	{
		return 0;
	}
};
