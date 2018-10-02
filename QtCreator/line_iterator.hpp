#ifndef __LINE_ITERATOR_
#define __LINE_ITERATOR_

#include <iostream>
#include <string>

class line_iterator {
	std::istream *in;
	bool is_valid;
	std::string line;
	void read() {
		if(*in)
			getline(*in, line);
		is_valid = (*in) ? true : false;
	}
public:
	line_iterator() : is_valid(false), in(&std::cin) {}
	line_iterator(std::istream &is) : is_valid(false), in(&is) {}
	line_iterator(const line_iterator &li) :
		is_valid(li.is_valid), in(li.in) {}
	std::string operator*() {
		return line;
	}
	std::string *operator->() {
		return &line;
	}
	line_iterator operator++() {
		read();
		return *this;
	}
	line_iterator operator++(int) {
		auto tmp = *this;
		read();
		return tmp;
	}
	bool operator==(const line_iterator &li) {
		return (((is_valid==li.is_valid)&&(in==li.in))||
				((is_valid==false)&&(li.is_valid==false)));
	}
	bool operator!=(const line_iterator &li) {
		return !(*this==li);
	}
};

#endif
