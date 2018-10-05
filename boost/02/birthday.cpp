//综合运用：计算十八岁生日时的相关信息
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;
typedef gregorian_calendar gre_cal;

int main()
{
  date d18;

  cout << "Please input your date of birth: YYYY-mmm-DD" << endl;
  cin >> d18;

  d18 += years(18);

  //计算18岁生日那月有多少个星期天
  int count = 0;
  for(day_iterator d_iter(date(d18.year(), d18.month(), 1));
      d_iter!=(d18.end_of_month()+days(1)); ++d_iter) {
    if(d_iter->day_of_week()==Sunday)
      ++count;
  }

  cout << "Your 18's birthday is: " << d18 << endl;
  cout << "It's " << d18.day_of_week() << endl;
  cout << "There are " << count << " Sunday in this month" << endl;
  cout << "This year have " << (gre_cal::is_leap_year(d18.year())?366:365) << " days" << endl;
  
  return 0;
}
