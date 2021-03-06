//测试c++11中的初值列使用方法，这种方法可以帮助
//初始化基础类型但未被显式初始化的局部变量
#include <iostream>

using namespace std;

void testInitList()
{  
  int i;
  int j{};
  int *p;
  int *q{};
  //注意这种初值列的方法不适用于出现窄化
  //即数值精度或表示范围被降低的时候
  //这里还有一个问题，判断窄化时，编译器
  //不会仅仅只依赖于表面的类型来判断，如果
  //数值可被给定类型精确表示则不算窄化，
  //但是浮点数向整数的转化永远是窄化
  //int m{6.5};
  
  if(i==0)
	cout << "i is initied" << endl;
  if(j==0)
	cout << "j is initied" << endl;
  if(p==nullptr)
	cout << "p is initied" << endl;
  if(q==nullptr)
	cout << "q is initied" << endl;

}

int main()
{
  testInitList();
  return 0;
}
