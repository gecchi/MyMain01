//============================================================================
// Name        : cppTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"


int main() {
	::timeBeginPeriod(1);

	GgafDx9SphereRadiusVectors* srvMy = new GgafDx9SphereRadiusVectors();

	int rZ, rY;
	cout << "start:" << timeGetTime() << endl;
	for (int i = 0; i < 10000; i++) {
		srvMy->getRotAngleClosely(9890,801,1231, rZ,rY);
	}
	cout << "end:" << timeGetTime() << endl;
	cout << "rZ=" << rZ << " rY=" << rY << endl;

	unsigned short x,y,z;

	srvMy->getVectorClosely(46,246,x,y,z);
	cout << "(" << x << "," << y << "," << z << ")" << endl;


	delete srvMy;
	::timeEndPeriod(1);//タイマー精度終了処理
	return 0;
}


