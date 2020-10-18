#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <iterator>

using namespace std;

class Student 
{
public:
	string name;
	double StudentDebt;
	double GPA;
	Student() {}
	Student(string a, double b, double c)
	{
		name = a;
		GPA = b;
		StudentDebt = c;
	}
	void print()
	{
		cout << name << " " << GPA << " " << StudentDebt << endl;
	}

};

// operator < overloading
bool operator < (const Student& p1, const Student& p2)
{
	// this will return true when second Student
	// has greater GPA.
	return p1.GPA < p2.GPA;
}

///to compare StudentDebt
class Comparator 
{
public:
	bool operator()(const Student* a, const Student* b)
	{
		return (a->StudentDebt > b->StudentDebt);
	}
};
//--------------------------------------------
int main()
{
	///declare list of int
	
	list<int> intList;
	///add integers to list at backward
	 
	for (int i = 0;i < 5;i++)
		intList.push_back(i);

	///add integers to front of list
	for (int i = 5;i < 10;i++)
		intList.push_front(i);

	///declare iterator to display output
	cout << " List = ";
	list <int> ::iterator it;

	for (it = intList.begin(); it != intList.end(); ++it)
		cout << " " << *it;


	/// 3. create vector of Students
	vector<Student> studentVector;

	///adding student objects into it
	studentVector.push_back(Student("John", 7.8, 1000));
	studentVector.push_back(Student("Mark", 8.8, 1200));
	studentVector.push_back(Student("Tomm", 5.1, 1500));
	studentVector.push_back(Student("Arya", 5.6, 2100));
	studentVector.push_back(Student("Martyn", 8.9, 7100));

	///display contents of vector
	cout << " vector =";
	cout << " Name GPA Debt ";
	for (int i = 0;i < studentVector.size();i++)
	{
		studentVector.at(i).print();
	}

	/// 4. Stack of Student pointers
	stack<Student*> studentStack;
	///add student pointers dynamically
	studentStack.push(new Student("John", 7.8, 1000));
	studentStack.push(new Student("Mark", 8.8, 1200));
	studentStack.push(new Student("Tomm", 5.1, 1500));
	studentStack.push(new Student("Arya", 5.6, 2100));
	studentStack.push(new Student("Martyn", 8.9, 7100));

	///display Stack
	cout << " Stack Contents ";
	while (!studentStack.empty())
	{
		studentStack.top()->print();
		studentStack.pop();
	}
	cout << ' ';

	
	// 5 set of ints
	set <int> intSet;
	set <int>::iterator intSetIterator;

	intSet.insert(1);
	intSet.insert(2);
	intSet.insert(2); //2 will be inserted only once
	intSet.insert(3);
	intSet.insert(4);

	cout << " intSet contains:";
	for (intSetIterator = intSet.begin(); intSetIterator != intSet.end(); ++intSetIterator)
		cout << ' ' << *intSetIterator;


	/// 6) .Map string(movieName) to int (year)
	map<string, int> movieMap;
	map<string, int>::iterator movieItarator;

	movieMap.insert(pair<string, int>("KGF", 2018));
	movieMap.insert(pair<string, int>("Aquaman", 2018));
	movieMap.insert(pair<string, int>("Escape Room", 2019));
	movieMap.insert(pair<string, int>("Captian Marvel", 2019));
	movieMap.insert(pair<string, int>("War room", 2015));

	cout << " Movie Map contains: ";
	cout << " Movie year";
	for (movieItarator = movieMap.begin(); movieItarator != movieMap.end(); movieItarator++)
	{
		cout << " " << movieItarator->first;
		cout << " " << movieItarator->second;
	}

	//uncomment Unordered Map
	/*
	/// 7 Unordered map
	unordered_map<string, int> movie;
	unordered_map<string, int>::iterator movieItr;
	// inserting values by using [] operator
	movie["KGF"] = 2018;
	movie["Aquaman"]=2018;
	movie["Escape room"]=2019;
	movie["captian Marvel"]=2019;
	movie["war room"]=2015;

	for(movieItr=movie.begin() ; movieItr!=movie.end() ; movieItr++)
	{
	cout<<" "<<movieItr->first;
	cout<<" "<<movieItr->second;
	}
	*/

	/// Priority Queue
	priority_queue <Student> studentPQ;
	///add students into PQ
	studentPQ.push(Student("John", 7.8, 1000));
	studentPQ.push(Student("Mark", 8.8, 1200));
	studentPQ.push(Student("Tomm", 5.1, 1500));
	studentPQ.push(Student("Arya", 5.6, 2100));
	studentPQ.push(Student("Merry", 8.9, 7100));

	///display PQ in descending order of GPA
	cout << " Contents of Student Priority Queue (priority=GPA ---descending order) ";
	cout << " student GPA Debt ";
	while (!studentPQ.empty()) {
		Student p = studentPQ.top();
		studentPQ.pop();
		p.print();
	}

	/// Priority Queue for Student Pointers using comaparator to compare Debt of student
	priority_queue <Student*, vector<Student*>, Comparator> studentPtrPQ;

	/// insert Student pointers into PQ
	studentPtrPQ.push(new Student("John", 7.8, 1000));
	studentPtrPQ.push(new Student("Mark", 8.8, 1200));
	studentPtrPQ.push(new Student("Tomm", 5.1, 1500));
	studentPtrPQ.push(new Student("Arya", 5.6, 2100));
	studentPtrPQ.push(new Student("Merry", 8.9, 7100));
	///display PQ in ascending order of Debt
	cout << " Contents of Student Priority Queue (priority= Debt -- ascending order)";
	cout << " student GPA Debt ";
	while (!studentPtrPQ.empty()) {
		Student* p = studentPtrPQ.top();
		studentPtrPQ.pop();
		p->print();
	}

	return 0;
}