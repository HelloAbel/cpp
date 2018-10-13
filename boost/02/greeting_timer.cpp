//综合运用：实现一个可以根据当前时间问候的类
#include <iostream>
#include <string>
#include <map>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class work_time
{
public:
  typedef map<time_period, string> map_t;
  void init()
  {
    ptime p(day_clock::local_day());

    map_ts[time_period(p,hours(9))] = "现在还没到上班时间";
    
    p+=hours(9);
    map_ts[time_period(p,hours(3)+minutes(30))] = "现在是上午的上班时间";

    p+=hours(3)+minutes(30);
    map_ts[time_period(p,hours(1))] = "现在是午饭时间";

    p+=hours(1);
    map_ts[time_period(p,hours(4)+minutes(30))] = "现在是下午的上班时间";

    p+=hours(4)+minutes(30);
    map_ts[time_period(p,hours(6))] = "今天的班已上完";
  }
  work_time() { init(); }
  void greeting(const ptime& t = second_clock::local_time())
  {
    for(auto& x : map_ts)
      if(x.first.contains(t)) {
        cout << x.second << endl;
        break;
      }
  }
private:
  map_t map_ts;
};

int main()
{
  work_time wt;
  wt.greeting();
  
  return 0;
}
