//将字符串转化成字符表格提高效率
#ifndef STR_TAB_HPP
#define STR_TAB_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <iterator>

struct strtab_cmp {
  typedef std::vector<char>::iterator strtab_iter;
  typedef std::pair<strtab_iter, strtab_iter> strp;
  bool operator()(const strp& x, const strp& y) {
	return lexicographical_compare(x.first, x.second, y.first, y.second);
  }
};

struct strtab_print {
  std::ostream& out;

  strtab_print(std::ostream &os): out(os) {}
  strtab_print(): out(std::cout) {}

  typedef std::vector<char>::iterator strtab_iter;
  typedef std::pair<strtab_iter, strtab_iter> strp;
  void operator()(const strp& iter) const {
	copy(iter.first, iter.second, std::ostream_iterator<char>(out));
  }
};

#endif
