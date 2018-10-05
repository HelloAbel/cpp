//综合运用：计算银行卡的免息期
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <algorithm>
#include <string>

using namespace std;
using namespace boost::gregorian;

class credit_card
{
public:
  string bank_name; //银行名称
  int bill_no; //记账日
  credit_card(const char* bname, int bno):
    bank_name(bname), bill_no(bno) {}
  int calc_freeint_days(date cday = day_clock::local_day()) const;
  friend bool operator<(const credit_card& l, const credit_card& r)
  {
    return l.calc_freeint_days() < r.calc_freeint_days();
  }
};

//计算信用卡免息期
//注意：默认实参只能声明一次，故这儿不再填写默认实参
int credit_card::calc_freeint_days(date consume_day) const
{
  int free_days = 0;

  date bill_day(consume_day.year(), consume_day.month(), bill_no);

  if(bill_day<consume_day)
    bill_day+=months(1); //如果本月消费日期超过了本月记账日期，则记账日期调整为下个月

  return (bill_day-consume_day).days()+20;
}

int main()
{
  credit_card a("A bank", 25);
  credit_card b("B bank", 12);

  credit_card tmp = std::max(a,b); //比较两个信用卡哪个免息期长
  cout << "You should use " << tmp.bank_name
       << ", free days = " << tmp.calc_freeint_days() << endl;
  
  return 0;
}
