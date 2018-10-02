//测试复数的运算
#include <iostream>
#include <complex>

using namespace std;

int main()
{
    complex<float> z(1.3, 2.4), z2;
    complex<int> y(1, 2), y2;
    
//    z2 = 2*z;
//    cout << z2 << endl;
//    z2 = 2.0*z;
//    cout << z2 << endl;
    z2 = 2.0f*z;
    cout << z2 << endl;
    return 0;
}
