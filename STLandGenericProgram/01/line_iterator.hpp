#ifndef __LINE_ITERATOR_
#define __LINE_ITERATOR_

#include <string>
#include <iostream>
#include <iterator>
namespace LineIterator {
class line_iterator {
	bool is_valid;
	std::string line;
	std::istream *in;
	void read() {
		if (*in)
			getline(*in, line);
		is_valid = (*in) ? true : false;
	}
public:
	typedef std::input_iterator_tag iterator_category;
	typedef std::string value_type;
	typedef std::ptrdiff_t difference_type;
	typedef const std::string* pointer;
	typedef const std::string& reference;
	line_iterator() : in(&std::cin), is_valid(false) {}
	line_iterator(std::istream &is) : in(&is) { read(); }
	std::string operator*() { return line; }
	std::string *operator->() { return &line; }
	line_iterator operator++() {
		read();
		return *this;
	}
	line_iterator operator++(int) {
		line_iterator tmp = *this;
		read();
		return tmp;
	}
	bool operator==(const line_iterator &il) {
		return ((is_valid==il.is_valid && in==il.in) ||
				(is_valid==false && il.is_valid==false));
	}
	bool operator!=(const line_iterator &il) {
		return !(*this==il);
	}
};
}
#endif
