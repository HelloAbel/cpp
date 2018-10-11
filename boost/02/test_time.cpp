//测试date_time库中的时间组件
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

int main()
{
  time_duration t1(1,10,30,1000); //time_duration可以直接通过时、分、秒、微妙来构造
  time_duration t2(1,60,60,1000*1000*6+1000); //时分秒值可以是任意数量，超出限度会自动进位

  cout << t1 << endl;
  cout << t2 << endl;

  //使用time_duration的子类可以更直观的创建时间长度
  hours h1(1); //1小时
  minutes m1(10); //10分钟
  seconds s1(30); //30秒
  millisec ms1(1); //1毫秒
  microsec mis1(1000); //1000微妙

  time_duration t3 = h1+m1+s1+ms1+mis1; //子类算术操作的结果可以直接赋值给time_duration
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
  assert(t6.total_milliseconds()==t6.total_seconds()*1000+1); //total_milliseconds函数返回总的毫秒数
  assert(t6.total_microseconds()==t6.total_milliseconds()*1000); //total_microseconds函数返回总的微妙数


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
  
  return 0;
}
