//测试date_time库中的时间组件
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG //定义纳秒精度宏，时间精度由微妙变为纳秒
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main()
{
  time_duration t1(1,10,30,1000); //time_duration可以直接通过时、分、秒、微妙来构造，如果定义了纳秒精度宏，则由时分秒和纳秒构造
  time_duration t2(1,60,60,1000*1000*6+1000); //时分秒值可以是任意数量，超出限度会自动进位

  cout << t1 << endl;
  cout << t2 << endl;

  //使用time_duration的子类可以更直观的创建时间长度
  hours h1(1); //1小时
  minutes m1(10); //10分钟
  seconds s1(30); //30秒
  millisec ms1(1); //1毫秒
  microsec mis1(1000); //1000微妙
  nanosec ns(1000000); //1000000纳秒
  
  time_duration t3 = h1+m1+s1+ms1+mis1+ns; //子类算术操作的结果可以直接赋值给time_duration
  time_duration t4 = hours(4)+seconds(10); //也可以直接赋值

  cout << h1 << endl;
  cout << m1 << endl;
  cout << s1 << endl;
  cout << ms1 << endl;
  cout << t3 << endl;
  cout << t4 << endl;

  time_duration t5 = duration_from_string("1:10:30:001"); //使用工厂函数从字符串创建，时分秒微妙之间用:相隔
  time_duration t6(1,10,30,1000);

  assert(t6.hours()==1 && t6.minutes()==10 && t6.seconds()==30); //利用成员函数返回相应的时分秒数
  assert(t6.total_seconds()==1*3600+10*60+30); //total_seconds函数返回时间长度的总秒数
  assert(t6.total_milliseconds()==t6.total_seconds()*1000); //total_milliseconds函数返回总的毫秒数
  assert(t6.total_microseconds()==t6.total_milliseconds()*1000+1); //total_microseconds函数返回总的微妙数


  hours h2(-10); //时间长度可以取负值
  assert(h2.is_negative()); //判断是否为负值

  time_duration t7 = h2.invert_sign(); //将时间长度改变后生成一个新的时间长度
  assert(!t7.is_negative() && t7.hours()==10);

  time_duration t8(not_a_date_time); //与日期一样，也可以赋特殊值
  assert(t8.is_special() && t8.is_not_a_date_time()); //检测是否为特殊值，也有其他pos_infin、neg_infin等用法与日期类似


  //time_duration支持完整的比较操作和四则运算
  time_duration t9 = hours(1);
  time_duration t10 = hours(2)+minutes(30);
  assert(t9<t10);
  assert((t9+t10).hours()==3);
  assert((t9-t10).is_negative());
  assert(t9*5==t10*2);
  assert((t9/2).minutes()==t10.minutes());


  time_duration t11(1,10,30,1000);
  cout << to_simple_string(t11) << endl; //输出HH:MM:SS.fffffffff形式的时间字符串
  cout << to_iso_string(t11) << endl; //输出HHMMSS,fffffffff形式的时间字符串

  assert(time_duration::unit()*1000*1000*1000==seconds(1)); //unit静态成员函数返回一个time_duration计量的最小单位
  assert(time_duration::resolution()==boost::date_time::nano); //静态成员函数resolution返回一个枚举值time_resolutions表示时间长度
  assert(time_duration::num_fractional_digits()==9); //静态成员函数num_fractional_digits返回秒的小数部分的位数，微秒6位，纳秒9位

  //ticks_per_second是C中的宏CLOCKS_PER_SEC的强化，它返回每秒的tick数，可以使用它来编写与时间精度无关的代码
  time_duration::tick_type my_millisec = time_duration::ticks_per_second()/1000; //自定义毫秒单位
  time_duration t12(1,10,30,10*my_millisec); //10毫秒，即0.01秒
  cout << t12 << endl;


  ptime p1(date(2017,7,7), hours(1)); //2017年7月7日凌晨一点，如果不加time_duration参数，则默认为当天的零点
  ptime p2 = time_from_string("2017-7-7 01:00:00"); //利用工厂函数从字符串产生时间点
  ptime p3 = from_iso_string("20170707T010000"); //T分隔日期和时间
  ptime p4 = second_clock::local_time(); //秒精度的当地时间
  ptime p5 = microsec_clock::universal_time(); //微秒精度的UTC时间
  ptime p6(not_a_date_time); //无效时间
  ptime p7(pos_infin); //正无限时间

  cout << p1 << endl;
  cout << p2 << endl;
  cout << p3 << endl;
  cout << p4 << endl;
  cout << p5 << endl;
  assert(p6.is_not_a_date_time());
  assert(p7.is_special() && p7.is_pos_infinity());

  
  date d1 = p1.date(); //date()获取时间点的日期
  time_duration t13 = p1.time_of_day(); //time_of_day获取时间长度
  assert(d1.month()==7 && d1.day()==7);
  assert(t13.total_seconds()==3600);

  ptime p8 = p1+hours(3); //2017年7月7日凌晨四点
  assert(p1<p8);
  assert(p8-p1==hours(3));
  p8 += months(1);
  assert(p8.date().month()==8);

  cout << to_simple_string(p8) << endl; //转换为YYYY-mmm-DD HH:MM:SS.ffffff格式
  cout << to_iso_string(p8) << endl; //转换为YYYYMMDDTHHMMSS,ffffff格式
  cout << to_iso_extended_string(p8) << endl; //转换为YYYY-MM-DDTHH:MM:SS,ffffff格式



  tm t = to_tm(p8); //转换为C语言中的tm结构
  assert(t.tm_year==117 && t.tm_hour==4);
  assert(ptime_from_tm(t)==p8); //将tm结构转为ptime结构

  //函数from_time_t和to_time_t可以在time_t和ptime之间互相转换
  ptime p9 = from_time_t(std::time(0));
  cout << p9 << endl;
  assert(p9.date()==day_clock::universal_day());
  cout << to_time_t(p9) << endl;



  //时间迭代器
  for(time_iterator t_iter(p9,minutes(10)); //以十分钟为步长
      t_iter<p9+hours(1); ++t_iter)
    cout << *t_iter << endl;
  
  return 0;
}
