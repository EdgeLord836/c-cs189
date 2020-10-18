#include "Vector.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Remember, you have to test all template functions since if you don't call it then it gets deleted.  
	// Otherwise a week from now you'll call the one you forgot and it will crash.
	Vector<int> tTester;
	tTester.PushBack( 0 );
	tTester.PushBack( 1 );
	tTester.PushBack( 2 );
	tTester.PushBack( 3 );
	tTester.PushBack( 4 );
	tTester.PushBack( 5 );
	tTester.PushBack( 6 );
	tTester.PushBack( 7 );
	tTester.PushBack( 8 );
	tTester.PushBack( 9 );

	cout << "If any of the lines below are false, there is a bug.  This is not a comphrehensive test.  Add what you need.\n";
	cout << tTester.Size() << " == 10" << endl;// 10
	cout << tTester.At( 5 ) << " == 5" << endl;// 5
	cout << tTester.At( 0 ) << " == 0" << endl;// 0

	cout << tTester.Capacity() << " == 15" << endl; // 15
	tTester.PushBack( 11 );
	tTester.PushBack( 11 );
	tTester.PushBack( 11 );
	tTester.PushBack( 11 );
	tTester.PushBack( 11 );
	tTester.PushBack( 11 );
	tTester.PushBack( 111 );
	tTester.PushBack( 11 );
	cout << tTester.Capacity() << " == 30" << endl; // 30

	tTester.Reserve( 50 );
	cout << tTester.Capacity() << " == 50" << endl; // 50

	tTester.PopBack();
	cout << tTester.At( tTester.Size() - 1 ) << " == 111" << endl;// 111

	tTester.Clear();
	cout << tTester.Size() << " == 0" << endl;// 0

	tTester.PushBack( 0 );
	tTester.PushBack( 1 );
	tTester.PushBack( 2 );
	tTester.PushBack( 3 );
	tTester.PushBack( 4 );
	tTester.PushBack( 5 );

	Vector<int>tCopy( tTester );
	cout << tTester.Size() << " == 6" << endl;// 6
	cout << tCopy.Size() << " == 6" << endl;// 6

	tCopy.PopBack();
	cout << tTester.Size() << " == 6" << endl;// 6
	cout << tCopy.Size() << " == 5" << endl;// 5

	Vector<int> tAssign;
	tAssign.PushBack( 999 );
	tAssign = tTester; // Tricky thing, if you do an initialization (Vector<int> A = B;) even though it has a = it runs the copy constructor instead.)

	cout << tTester.Size() << " == 6" << endl;// 6
	cout << tAssign.Size() << " == 6" << endl;// 6

	tAssign.PopBack();
	cout << tTester.Size() << " == 6" << endl;// 6
	cout << tAssign.Size() << " == 5" << endl;// 5

	// The destructor will be called on each Vector when they go out of scope.  If you want to see it explicitly,
	// You need to new and delete a vector object.
}