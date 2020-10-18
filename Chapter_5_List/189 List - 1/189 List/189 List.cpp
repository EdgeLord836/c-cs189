// ListStart.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<int> tSomeInts;

	tSomeInts.PushBack( 14 );
	tSomeInts.PushBack( 1 );
	tSomeInts.PushBack( 54 );
	tSomeInts.PushBack( 25 );

	List<int> tIntCopy = tSomeInts;

	tSomeInts.PopBack();

	cout << "This better say 4: " << tIntCopy.Size() << endl;
	cout << "This better say 14: " << tSomeInts.Front() << endl;
	cout << "This better say 54: " << tSomeInts.Back() << endl;

//	cout << "This better say 14 1 54" << endl;
//	for (List<int>::Iterator iter = tSomeInts.Begin(); !iter.IsEqual(tSomeInts.End()); iter.Next())
//	{
		// REMEMBER THIS LOOP!  It is the grown-up version of "for( int i = 0; i < count; i++ )"
//		cout << iter.GetData() << " " << endl;
//	}
	return 0;
}
