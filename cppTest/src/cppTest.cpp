//============================================================================
// Name        : cppTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"

class Actor2 {
public:
	char* _nameA;
	char* _nameB;
	Actor2(char*  name) {
		_nameA = name;
	};

	char* getnameA() {
		return _nameA;
	};

	char* getnameB() {
		return _nameB;
	};
};

int main() {
	Actor2* xxx;
	{
		xxx = new Actor2("cccccccc");
	}
	xxx->_nameA = "jjj";
	xxx->_nameB = "sss";

	xxx->_nameA = xxx->_nameB;
	xxx->_nameA = "xxxxxx";
	delete xxx;
	cout << xxx->_nameB << endl;

}

