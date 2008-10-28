//============================================================================
// Name        : cppTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"
struct vec{
	unsigned short x;
	unsigned short z;
	unsigned short y;
};

union MyVec {
	long long yzx;
	vec v;
};


int main() {
	MyVec myvec;

	myvec.yzx = 0LL;

	cout << (myvec.yzx)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;

	myvec.v.x = 1;
	cout << (myvec.yzx)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;
	myvec.v.z = 1;
	cout << (myvec.yzx)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;
	myvec.v.y = 1;
	cout << (myvec.yzx)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;

	return 0;
}
