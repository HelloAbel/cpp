//测试日期组件
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctime>

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

  date d13(2017,6,1);
  //通过成员函数分别返回年月日
  assert(d13.year() == 2017);
  assert(d13.month() == 6);
  assert(d13.day() == 1);

  //通过ymd_type结构一次性获取年月日
  date::ymd_type ymd = d13.year_month_day();
  assert(ymd.year == 2017);
  assert(ymd.month == 6);
  assert(ymd.day == 1);

  cout << d13.day_of_week() << endl; //day_of_week返回星期几
  cout << d13.day_of_year() << endl; //day_of_year返回当年的第几天
  assert(d13.end_of_month() == date(2017,6,30)); //end_of_month返回当月的最后一天的date对象
  cout << date(2015,1,10).week_number() << endl; //week_number返回当周是当年第几周

  assert(date(pos_infin).is_infinity()); //is_infinity判断是否是一个无限日期
  assert(date(pos_infin).is_pos_infinity()); //is_pos_infinity判断是否是一个正无限日期
  assert(date(neg_infin).is_neg_infinity()); //is_neg_infinity判断是否是一个负无限日期
  assert(date(not_a_date_time).is_not_a_date()); //is_not_a_date判断是否是一个无效日期
  assert(date(not_a_date_time).is_special()); //is_special判断是否是任意一个特殊日期

  date d14(2018,10,4);

  cout << to_simple_string(d14) << endl; //to_simple_string将日期转换为YYYY-MMM-DD格式的字符串，其中MMM为三字符的英文月份名
  cout << to_iso_string(d14) << endl; //to_iso_string将日期转换为YYYYMMDD格式的数字字符串
  cout << to_iso_extended_string(d14) << endl; //to_iso_extended_string将日期转换为YYYY-MM-DD格式的数字字符串
  cout << d14 << endl;

  //cin >> d14; //输入时只能通过YYYY-MMM-DD形式输入，MMM为三字符的英文月份名
  //cout << d14 << endl;


  date d15(2017,5,20);

  tm t = to_tm(d15); //将date变量转换为C标准库中tm格式，tm中的时分秒被设为0,夏令时标志tm_isdst被设为-1，表示未知
  assert(t.tm_hour ==0 && t.tm_min == 0);
  assert(t.tm_year == 117 && t.tm_mday == 20);


  date d16 = date_from_tm(t); //将tm格式的日期转换为date格式，除了年月日其他成员被忽略
  assert(d15 == d16);

  cout << d15 << endl;
  cout << d16 << endl;


  //测试日期长度
  days dd1(10), dd2(-100), dd3(255);

  assert(dd1 > dd2 && dd1 < dd3);
  assert(dd1 + dd2 == days(-90));
  assert((dd1 + dd3).days() == 265);
  assert(dd3 / 5 == days(51));

  weeks w(3);
  assert(w.days() == 21);

  months m(5);
  years y(2);

  months m2 = y + m; //2年零5个月
  assert(m2.number_of_months() == 29);
  assert((y*2).number_of_years() == 4);


  //日期运算
  date d17(2000,1,1), d18(2018,10,4);

  cout << d18-d17 << endl; //输出两个日期之间的天数
  assert(d17+(d18-d17)==d18);

  d17+=days(10); //d17的日期往后推10天
  assert(d17.day()==11);
  d17+=months(2); //日期往后推两个月
  assert(d17.month()==3 && d17.day()==11);
  d17-=weeks(1); //日期往前提一周
  assert(d17.day()==4);
  d17-=years(10); //日期往前提10年
  assert(d17.year()==1990);

  date d19(2017,1,1);
  
  date d20 = d19+days(pos_infin); //日期加上特殊日期长度是特殊日期
  assert(d20.is_pos_infinity());
  
  d20 = d19+days(not_a_date_time);
  assert(d20.is_not_a_date());

  d20 = date(neg_infin);
  days dd = d19-d20;
  assert(dd.is_special() && !dd.is_negative());

  date d21(2017,3,30);
  d21-=months(1); //变为月末，2017-2-28，原来30的信息丢失
  d21-=months(1); //2017-1-31
  d21+=months(2); //2017-3-31，与原来的2017-3-30不相等
  assert(d21.day()==31);
  
  return 0;
}
