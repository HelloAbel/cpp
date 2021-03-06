//date_time库的一些高级特性
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

//c++新增标准允许自定义字面值，通过重载""操作符实现
//自定义后缀必须以下划线开始，无下划线留给c++自身
days operator"" _D(unsigned long long n)
{
  return days(n);
}

weeks operator"" _W(unsigned long long n)
{
  return weeks(n);
}

date operator"" _YMD(const char* s, std::size_t)
{
  return from_string(s);
}


int main()
{
  auto d = 100_D; //100天
  auto w = 1_W; //1周

  assert(d.days()==100);
  assert(w.days()==(7_D).days()); //可以直接用字面值变量

  auto today = "2018/10/13"_YMD; //字符串转换为日期
  cout << today << endl;

  //自定义日期时间格式
  date d1(2014,1,3);
  date_facet* dfacet = new date_facet("%Y年%m月%d日");
  cout.imbue(locale(cout.getloc(), dfacet));
  cout << d1 << endl;

  time_facet *tfacet = new time_facet("%Y年%m月%d日%H点%M分%S%F秒");
  cout.imbue(locale(cout.getloc(), tfacet));
  cout << ptime(d1,hours(21)+minutes(30)+millisec(105)) << endl;
  
  return 0;
}
