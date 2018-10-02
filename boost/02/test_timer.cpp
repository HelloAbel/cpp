//测试boost中的timer库

#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int main()
{
    timer t;        //声明一个计时器对象，对象一旦创立就开始计时
    progress_timer t2;  
    
    cout << "max timespan:" //可度量的最大时间，以小时为单位
         << t.elapsed_max()/3600 << "h" << endl;
    cout << "min timespan:" //可度量的最小时间，以秒为单位
         << t.elapsed_min() << "s" << endl;
    cout << "now time elapsed:" //输出已经流逝的时间
         << t.elapsed() << "s" << endl;
    
    //离开main函数作用域时，progress_timer自动输出已经流逝的时间
    {
      //如果要在一个程序中测量多个时间，可以使用大括号限定progress_timer的生命周期
      progress_timer t3;
    }
    {
      progress_timer t4;
    }
    return 0;
    
}
