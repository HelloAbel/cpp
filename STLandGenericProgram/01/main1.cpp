//利用字符表格代替string提高效率
#include "strtab.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
  vector<char> vc;
  char ele;
  while(cin.get(ele))
	vc.push_back(ele);

  typedef vector<char>::iterator strtab_iter;
  vector<pair<strtab_iter, strtab_iter>> line;
  auto start = vc.begin();
  while(start!=vc.end()) {
	auto next = find(start, vc.end(), '\n');
	if(next!=vc.end())
	  ++next;
	line.push_back(make_pair(start, next));
	start = next;
  }

  sort(line.begin(), line.end(), strtab_cmp());

  for_each(line.begin(), line.end(), strtab_print());
  
  return 0;
}
