//============================================================================
// Name        : cppTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"
struct vec{
  short x;
  short y;
  short z;
};

union MyVec {
	long long xyz;
	vec v;
};


int main() {
	MyVec myvec;

	myvec.xyz = 272889206077488LL;

	cout << (myvec.xyz)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;

	myvec.v.x = -2000;
	cout << (myvec.xyz)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;
	myvec.v.y = -2000;
	cout << (myvec.xyz)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;
	myvec.v.z = -2000;
	cout << (myvec.xyz)  << "(" << (myvec.v.x) << "," << (myvec.v.y) << "," << (myvec.v.z) << ")" << endl;

	return 0;
}
