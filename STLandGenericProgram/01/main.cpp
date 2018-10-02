#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "line_iterator.hpp"

using namespace std;

int main()
{
	LineIterator::line_iterator iter(cin);
	LineIterator::line_iterator end_of_file;

	std::vector<std::string> V(iter, end_of_file);
    sort(V.begin(), V.end());
    copy(V.begin(), V.end(), ostream_iterator<string>(cout, "\n"));
    return 0;
}
