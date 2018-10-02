//测试c++差错码和差错状态
#include "exception.hpp"

using namespace std;

int main()
{
  try {
	throw system_error(make_error_code(std::errc::invalid_argument),
					   "argument ... is not valid");
  }
  catch(...) {
	processException();
  }
  return 0;
}
