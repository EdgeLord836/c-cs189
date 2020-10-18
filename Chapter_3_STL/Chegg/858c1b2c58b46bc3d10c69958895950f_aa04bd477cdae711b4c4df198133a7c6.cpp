#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

class Student
{
public:
  string Name;
  double StudentDebt;
  double GPA;

  Student() {}
  Student( string a, double b, double c )
  {
    Name = a;
    GPA = b;
    StudentDebt = c;
  }
  void print()
  {
    cout << Name << " " << GPA << " " << StudentDebt << " " << endl;
  }

};

bool operator < (const Student& p1, const Student& p2)
{
  return p1.GPA < p2.GPA;
}

class Comparator
{
public:
  bool operator()(const Student* a, const Student* b)
  {
    return (a->StudentDebt > b->StudentDebt);
  }
};

int main()
{
  //declare list of int
  list< int > intList;

  //add integers to front of list
  for ( int i = 0; i < 10; i++ )
    intList.push_front(i);

  list < int > ::iterator it;

  for ( it = intList.begin(); it != intList.end(); ++it )
    cout << " " << *it;

  // 3. create vector of Students
  vector<Student> studentVector;

  //adding student objects into it
  studentVector.push_back(Student("Leandro,", 2.8, 12500));
  studentVector.push_back(Student("Alice,", 3.8, 8000));
  studentVector.push_back(Student("Frankenstein,", 1.1, 6660));


  //display contents of vector
  cout << endl;
  cout << endl;
  cout << "Student's Name, GPA, Debt " << endl;

  for (int i = 0; i < studentVector.size(); i++)
  {
    studentVector.at(i).print();
  }

  stack<Student*> studentStack;

  //add student pointers dynamically using a loop

  for (int i = 0; i < 10; i++)
  {
    // creating a unique name for all
    string name = "Name" + to_string(i);
    // creating student object
    Student* student = new Student(name, i + 1, i + 100);
    // pushing to stack
    studentStack.push(student);
  }

  //display Stack
  cout << endl;
  cout << "Student Stack " << endl;

  // loop to diplay the stack and pop and delete elements in it
  while (!studentStack.empty())
  {
    // get the top student object
    Student* student = studentStack.top();
    // print
    student->print();
    // pop the object from the stack
    studentStack.pop();
    // delete the student object
    delete student;
  }

  cout << "Stack size after delete is "<<studentStack.size()<<endl;

  cout << ' ';

  set <int> intSet;
  set <int>::iterator intSetIterator;

  intSet.insert(1);
  intSet.insert(2);
  intSet.insert(3);
  intSet.insert(4);

  cout << endl;

  cout << "Movie Name, Year Released" << endl;

  // 7) Do #6 w/ Unordered map
  unordered_map< string, int > movie;
  unordered_map< string, int > ::iterator movieItr;

  movie["Fight Club,"] = 1999;
  movie["The Matrix,"] = 1999;
  movie["American Pie,"] = 1999;
  movie["Eyes Wide Shut,"] = 1999;

  for (movieItr = movie.begin(); movieItr != movie.end(); movieItr++)
  {
    cout << " " << movieItr->first;
    cout << " " << movieItr->second << endl;
  }

  // Priority Queue
  priority_queue <Student> studentPQ;

  ///add students into PQ
  studentPQ.push(Student("Leandro", 2.8, 1000));
  studentPQ.push(Student("Alice", 3.8, 1200));
  studentPQ.push(Student("Frankenstein", 1.1, 1500));

  //display Priority Queue in descending order of GPA
  cout << endl;
  cout << "Student w/ Highest GPA" << endl;
  cout << "Starting from Highest to Least GPA" << endl;

  while (!studentPQ.empty())
  {
    Student p = studentPQ.top();
    studentPQ.pop();
    p.print();
  }

  // Priority Queue for Student Pointers using comaparator to compare Debt of student
  priority_queue <Student*, vector<Student*>, Comparator> studentPtrPQ;

  // insert Student pointers into PQ
  studentPtrPQ.push(new Student("Leandro,", 2.8, 12500));
  studentPtrPQ.push(new Student("Alice,", 3.8, 8000));
  studentPtrPQ.push(new Student("Frankenstein,", 1.1, 6660));

  //display Priority Queue in ascending order of Debt
  cout << endl;
  cout << "Student w/ Least Debt" << endl;
  cout << "Starting From Least to Highest Debt" << endl;

  while (!studentPtrPQ.empty())
  {
    Student* p = studentPtrPQ.top();
    studentPtrPQ.pop();
    p->print();
  }

  return 0;
}
