//综合运用：打印月历
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

using namespace std;
using namespace boost::gregorian;

int main()
{
  date d;

  cout << "Input a date: YYYY-mmm-DD" << endl;
  cin >> d;

  date d_start(d.year(), d.month(), 1); //当月的开始
  date d_end = d.end_of_month(); //当月的最后一天

  cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;
  for(int i=0; i!=d_start.day_of_week(); ++i)
    cout << "    ";
  for(day_iterator d_iter(d_start);
      d_iter<=d_end; ++d_iter) {
    string s(d_iter->day()<10 ? "   " : "  ");
    cout << d_iter->day() << s;
    if(d_iter->day_of_week()==6)
      cout << endl;
  }
  cout << endl;
  
  return 0;
}
