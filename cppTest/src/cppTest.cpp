//============================================================================
// Name        : cppTest.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"
#define ABCDEF ABC+DEF
#define ABC 1
#define DEF 2

int main() {


	cout << ABCDEF << endl;
//	::timeBeginPeriod(1);
//
//	GgafDx9SphereRadiusVectors* srvMy = new GgafDx9SphereRadiusVectors();
//	GgafDx9Util::init();
//
//	int rZ, rY;
//	cout << "start:" << timeGetTime() << endl;
//	for (int i = 0; i < 10000; i++) {
//		srvMy->getRotAngleClosely(9890,801,1231, rZ,rY);
//	}
//	cout << "end:" << timeGetTime() << endl;
//	cout << "rZ=" << rZ << " rY=" << rY << endl;
//	double uvX, uvY, uvZ;
//	angle angRotZ, angRotY;
//	GgafDx9Util::getRotAngleZY(
//			0, 100000, 100,
//			uvX, uvY, uvZ,
//			angRotZ, angRotY
//			);
//
//	cout << "(" << uvX << "," << uvY << "," << uvZ << ")  RzRy = " << angRotZ << "/" << angRotY << endl;
//
//


//	unsigned short x,y,z;
//	int index;
//	for (int rZ = 900; rZ >= 0; rZ--) {
//		for (int rY = 0; rY <= 900; rY++) {
//			srvMy->getVectorClosely(rY,rZ,x,y,z);
//			index = (rZ*(900+1)+rY);
//			cout << "rZ=" << rZ << "/rY=" << rY << " srv[" << index << "]=" << GgafDx9SphereRadiusVectors::_sr[index].num_yzx << "(" << x << "," << y << "," << z << ")" << endl;
//		}
//	}


//	double x,y,z;
//	int index;
//	for (int rZ = 90000; rZ >= 0; rZ--) {
//		for (int rY = 0; rY <= 90000; rY++) {
//			GgafDx9Util::getNormalizeVectorZY(rZ,rY,x,y,z);
//			cout << "rZ=" << rZ << "/rY=" << rY << "(" << x*1000 << "," << y*1000 << "," << z*1000 << ")" << endl;
//			//index = (rZ*(900+1)+rY);
//			//cout << "rZ=" << rZ << "/rY=" << rY << " srv[" << index << "]=" << GgafDx9SphereRadiusVectors::_sr[index].num_yzx << "(" << x << "," << y << "," << z << ")" << endl;
//		}
//	}

//	delete srvMy;
//	::timeEndPeriod(1);//タイマー精度終了処理
	return 0;
}


