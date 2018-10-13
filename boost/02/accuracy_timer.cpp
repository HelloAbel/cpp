//综合运用：使用ptime实现高精度计时器
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

template <typename clock = microsec_clock> //默认使用微秒级的时钟类，也可以指定second_clock
class basic_ptimer
{
public:
  basic_ptimer() { restart(); }
  void restart() { _start_time=clock::local_time(); }
  void elapsed(ostream &os = cout) const { os << clock::local_time()-_start_time << endl; }
  ~basic_ptimer() { elapsed(); }
private:
  ptime _start_time;
};

typedef basic_ptimer<microsec_clock> ptimer;
typedef basic_ptimer<second_clock> sptimer;

int main()
{
  ptimer p;

  p.elapsed();

  return 0;
}
