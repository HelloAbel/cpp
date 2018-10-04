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


  //日期区间
  date_period dp1(date(2017,1,1), days(20)); //从2017-1-1开始的20天的一个区间

  assert(!dp1.is_null()); //如果构造时使用了左大右小的端点或者日期长度为0,那么is_null返回true
  assert(dp1.begin().day()==1); //begin返回构造时左边的日期
  assert(dp1.last().day()==20); //last返回截止日期
  assert(dp1.end().day()==21); //end返回last后一天
  assert(dp1.length().days() == 20); //length返回日期区间的长度，以天为单位

  cout << dp1 << endl; //默认输入输出格式为[YYYY-mmm-DD/YYYY-mmm-DD]形式的字符串

  dp1.shift(days(3)); //将日期区间平移3天，长度不变
  assert(dp1.begin().day()==4);
  assert(dp1.length().days()==20);

  dp1.expand(days(3)); //将日期区间向两端延伸3天，相当于区间长度加6天
  assert(dp1.begin().day()==1);
  assert(dp1.length().days()==26);

  assert(dp1.is_after(date(2009,12,1))); //判断区间是否在某个日期后面
  assert(dp1.is_before(date(2018,10,4))); //判断区间是否在某个日期前面
  assert(dp1.contains(date(2017,1,10))); //判断区间是否包含另一个区间或日期

  date_period dp2(date(2017,1,5), days(10));

  assert(dp1.intersects(dp2)); //判断两个区间是否有交集
  assert(dp1.intersection(dp2)==dp2); //intersection返回两个区间的交集，如果无交集返回一个无效区间

  date_period dp3(date(2017,1,27), days(5));

  assert(dp1.is_adjacent(dp3)); //判断两个区间是否相邻


  date_period dp4(date(2010,1,1), days(20));
  date_period dp5(date(2010,1,5), days(10));
  date_period dp6(date(2010,2,1), days(5));
  date_period dp7(date(2010,1,15), days(10));

  assert(dp1.contains(dp2) && dp1.merge(dp2)==dp1); //merge取两个区间的并集，如果区间无交集或者不相邻则返回无效区间
  assert(dp1.span(dp3).end()==dp3.end()); //span合并两个区间及两者间的间隔，相当于广义的merge



  //日期迭代器
  date d22(2007,9,28);
  day_iterator d_iter(d22); //增减步长默认为1天

  assert(d_iter==d22); //不需要解引用就可以直接与日期进行比较
  ++d_iter;
  assert(d_iter==date(2007,9,29));

  year_iterator y_iter(*d_iter, 10); //增减步长为10年，解引用day_iterator可以得到日期
  assert(y_iter==d22+days(1));
  ++y_iter;
  assert(y_iter->year()==2017);



  //其他功能
  typedef gregorian_calendar gre_cal; //格里高利历法

  cout << "Y2017 is"
       << (gre_cal::is_leap_year(2017)?"":"not")
       << " a leap year." << endl; //静态函数is_leap_year判断是否是闰年
  assert(gre_cal::end_of_month_day(2017,2)==28); //end_of_month_day给定年份和月份，返回月末最后一天
  
  return 0;
}
