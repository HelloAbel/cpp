//高级特性：测试本地时间功能
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;

int main()
{
  tz_database tz_db; //时区数据库对象

  //libs/date_time/date_time_zonespec.csv包含了世界上所有国家的时区信息
  tz_db.load_from_file("/home/johanan/code/sourceCode/boost_1_68_0/libs/date_time/data/date_time_zonespec.csv");

  //使用字符串Asia/Shanghai获取上海时区，即北京时间
  time_zone_ptr shz = tz_db.time_zone_from_region("Asia/Shanghai");

  //使用字符串Amerian/Los_Angeles获取旧金山所在的洛杉矶时区
  time_zone_ptr sfz = tz_db.time_zone_from_region("America/Los_Angeles");

  cout << shz->has_dst() << endl; //上海时区无夏令时
  cout << shz->std_zone_name() << endl; //上海时区的名称为CST

  local_date_time dt_bj(date(2014,3,6), hours(16), shz, false); //北京时间2014-3-6下午16点，上海时区，无夏令时
  cout << dt_bj << endl;

  time_duration flight_time = hours(12); //飞行12小时
  dt_bj += flight_time; //到达的北京时间
  cout << dt_bj << endl;
  local_date_time dt_sf = dt_bj.local_time_in(sfz); //旧金山当地时间
  cout << dt_sf << endl;
  
  return 0;
}
