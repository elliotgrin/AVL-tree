#define TIME_TEST

#include "AVL.h"
#include <iostream>
#include <set>
#include <ctime>

using std::set;
using std::cout;
using std::cin;
using std::endl;

int AVL<int>::count = 0;

int main()
{
	
	cout << "TIME TESTS: " << endl << endl;

	AVL<int> t;
	set<int> s;

	cout << "Tree insertion" << endl;
	time_t start = clock();
	for (int i{ 0 }; i != 10000000; ++i)
		t.insert(i);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n\n";

	cout << "Set insortion" << endl;
	start = clock();
	for (int i{ 0 }; i != 10000000; ++i)
		s.insert(i);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";

	cout << endl << "=================================" << endl << endl;

	cout << "Tree removing" << endl;
	start = clock();
	for (int i{ 0 }; i != 10000000; ++i)
		t.remove(i);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n\n";

	cout << "Set removing" << endl;
	start = clock();
	for (int i{ 0 }; i != 10000000; ++i)
		s.erase(i);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";

	cout << endl << "=================================" << endl << endl;
	
	cout << "Tree searching" << endl;
	start = clock();
	for (int i{ 0 }; i != 100000000; ++i)
		t.find(1 + rand() % 1000000);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n\n";

	cout << "Set searching" << endl;
	start = clock();
	for (int i{ 0 }; i != 100000000; ++i)
		s.find(1 + rand() % 1000000);
	cout << "Time : " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";
	

	/*
	AVL<int> tree;

	tree.insert(5);
	tree.insert(15);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	tree.insert(6);
	tree.insert(9);

	tree.print();
	cout << "Depth of the tree is : " << tree.getDepth() << '\n';
	cout << "begin() is " << *(tree.begin()) << endl << endl;

	tree.remove(5);
	tree.remove(15);
	tree.remove(2);

	cout << "Elements 5, 15, 2 were removed. " << endl;
	tree.print();

	cout << endl << "Lets find elem 6 in tree and make an iterator " << endl;
	AVL<int>::iterator<int> it{ tree.find(6) };
	++it;
	std::cout << "Next element is " << *it << '\n';
	--it;
	--it;
	std::cout << "Preveous element is " << *it << '\n' << '\n';

	tree.saveInFile("tree.txt");

	AVL<int> tree1;
	tree1.loadFromFile("tree.txt");

	cout << endl << "New tree was loaded from file : " << endl << endl;
	tree1.print();
	*/
}