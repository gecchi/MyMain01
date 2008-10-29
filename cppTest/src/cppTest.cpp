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

	angle rZ, rY;
	cout << "start:" << timeGetTime() << endl;
	for (int i = 0; i < 10; i++) {
		srvMy->getRotAngleClosely(1489,1780,1332, rZ, rY);
	}
	cout << "end:" << timeGetTime() << endl;
	cout << "rZ=" << rZ << " rY=" << rY << endl;

	delete srvMy;
	::timeEndPeriod(1);//タイマー精度終了処理
	return 0;
}


