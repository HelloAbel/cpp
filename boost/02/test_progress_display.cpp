//实验progress_display类
#include <iostream>
#include <boost/progress.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
using namespace boost;

int main()
{
  vector<string> v(100, "aabb");
  ofstream fs("./text.txt");

  progress_display pd(v.size());

  for(auto& x : v) {
    fs << x << endl;
    sleep(1);
    ++pd;
  }
  return 0;
}
