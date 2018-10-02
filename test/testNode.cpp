#include <iostream>

using namespace std;

class Node {
public:
	Node() { cout << "first" << endl; };
	Node(const Node&) { cout << "second" << endl; }
	Node(const Node&, const Node&) { cout << "three" << endl; }
};

int main()
{
	Node n1;
	Node n2(n1);
	Node n3(n1, n2);

	return 0;
}
