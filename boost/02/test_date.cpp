//测试日期组件
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

int main()
{
  date d1; //创建一个无效日期
  date d2(2010, 1, 1); //使用数字构造日期
  date d3(2000, Jan, 1); //使用英文指定月份
  date d4(d2); //拷贝构造

  assert(d1 == date(not_a_date_time)); //比较一个临时对象
  assert(d2 == d4); //日期之间比较操作
  assert(d3 < d4);

  date d5 = from_string("1999-12-31"); //使用工厂函数从横杠分隔的字符串产生日期
  date d6(from_string("2015/1/1")); //使用工厂函数从斜杠分隔的字符串产生日期
  date d7 = from_undelimited_string("20011118"); //使用工厂函数从无分隔字符串产生日期

  //day_clock是一个天级别的工厂类，调用静态成员函数可以返回一个当天的日期对象
  cout << day_clock::local_day() << endl; //返回本地日期
  cout << day_clock::universal_day() << endl; //返回UTC日期

  //可以利用枚举创建特殊的日期
  date d8(neg_infin); //负无限日期
  date d9(pos_infin); //正无限日期
  date d10(not_a_date_time); //无效日期
  date d11(max_date_time); //最大可能日期9999-12-31
  date d12(min_date_time); //最小可能日期1400-01-01

  cout << d1 << endl;
  cout << d2 << endl;
  cout << d3 << endl;
  cout << d4 << endl;
  cout << d5 << endl;
  cout << d6 << endl;
  cout << d7 << endl;
  cout << d8 << endl;
  cout << d9 << endl;
  cout << d10 << endl;
  cout << d11 << endl;
  cout << d12 << endl;
  
  return 0;
}
