#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "line_iterator.hpp"

using namespace std;

int main()
{
    line_iterator iter(cin);
    line_iterator end;

    vector<string> V(iter, end);
    sort(V.begin(), V.end());
    copy(V.begin(), V.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}
