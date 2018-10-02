//实验boost
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <iostream>

using namespace std;

int main()
{
  cout << BOOST_VERSION << endl; //Boost版本号
  cout << BOOST_LIB_VERSION << endl; //Boost字符串形式版本号
  cout << BOOST_PLATFORM << endl; //操作系统
  cout << BOOST_COMPILER << endl; //编译器
  cout << BOOST_STDLIB << endl; //标准库
}
