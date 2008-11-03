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

//	int rZ, rY;
//	cout << "start:" << timeGetTime() << endl;
//	for (int i = 0; i < 10000; i++) {
//		srvMy->getRotAngleClosely(9890,801,1231, rZ,rY);
//	}
//	cout << "end:" << timeGetTime() << endl;
//	cout << "rZ=" << rZ << " rY=" << rY << endl;
	unsigned short x,y,z;
	int index;
	for (int rZ = 0; rZ <= 900; rZ++) {
		for (int rY = 0; rY <= 900; rY++) {
			srvMy->getVectorClosely(rY,rZ,x,y,z);
			index = (rZ*(900+1)+rY);
			cout << "rZ=" << rZ << "/rY=" << rY << " srv[" << index << "]=" << GgafDx9SphereRadiusVectors::_sr[index].num_yzx << "(" << x << "," << y << "," << z << ")" << endl;
		}
	}


	delete srvMy;
	::timeEndPeriod(1);//タイマー精度終了処理
	return 0;
}


