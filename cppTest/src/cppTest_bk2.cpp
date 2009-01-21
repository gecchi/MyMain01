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

class MeshActor;
class SpriteActor;
class MainActor;

class BaseActor {
public:
	int _type;
	int _ko;
	BaseActor(int type) {
		cout << "BaseActor::BaseActor()" << _type << endl;
		_type = type;
	};
	virtual void processDrawMain() {
		cout << "BaseActor::processDrawMain()" << _type << endl;
	};
	virtual void processBehavior()=0;

	virtual ~BaseActor() {
		cout << "BaseActor::~BaseActor()" << _type << endl;
	};
};

class MeshActor : virtual public BaseActor {

public:
	int ano;
	MeshActor(int type) : BaseActor(type) {
		if (_type == 1) {
			ano = 2;
			_ko = 100;
			cout << "MeshActor::MeshActor()" << _type << endl;
		}
	};
	virtual void processBehavior() {
		cout << "MeshActor::processBehavior()" << _type << endl;
	};
	virtual void processDrawMain() {
		cout << "MeshActor::processDrawMain()" << _type << endl;
	};
	virtual ~MeshActor() {
		cout << "MeshActor::~MeshActor()"  << _type << endl;
	};
};

class SpriteActor : virtual public BaseActor {
public:
	int ano;

	SpriteActor(int type) : BaseActor(type) {
		if (_type == 2) {
			ano = 1;
			_ko = 200;
			cout << "SpriteActor::SpriteActor()" << _type << endl;
		}
	};
	virtual void processDrawMain() {
		cout << "SpriteActor::processDrawMain()" << _type << endl;
	};
	virtual void processBehavior() {
		cout << "SpriteActor::processBehavior()" << _type << endl;
	};
	virtual ~SpriteActor() {
		cout << "SpriteActor::~MeshActor()"  << _type << endl;
	};
};


class MainActor : public SpriteActor, public MeshActor {
public:


	MainActor(int type) :  MeshActor(type), SpriteActor(type) ,BaseActor(type) {
		cout << "MainActor::MainActor()" << _type << endl;
	};
	virtual void processDrawMain() {
		cout << "さてさてMainActor::processDrawMain()" << _type << endl;
		if (_type == 1) {
			MeshActor::processDrawMain();
		} else if (_type == 2) {
			SpriteActor::processDrawMain();
		} else {
			cout << "??;" <<_type << endl;
		}


	};
	virtual void processBehavior() {
		cout << "MainActor::processBehavior()" << _type << endl;
	};
	virtual ~MainActor() {
		cout << "SpriteActor::~MeshActor()"  << _type << endl;
	};
};
//
//
//int main() {
//
//	MainActor* pActor  = new MainActor(2);
//	BaseActor* pBase = (BaseActor*)pActor;
////	MainActor* pXX = dynamic_cast<BaseActor*>pBase;
//	delete pActor;
//
//
//}
//
//



//int main() {
//
//	double _dCamZ = -1.0*((768)/(10)/2.0)/tan(PI/9);
//	cout << (tan(PI/9)) << endl;
//	cout << _dCamZ << endl;
////	::timeBeginPeriod(1);
////
////	GgafDx9SphereRadiusVectors* srvMy = new GgafDx9SphereRadiusVectors();
////	GgafDx9Util::init();
////
////	int rZ, rY;
////	cout << "start:" << timeGetTime() << endl;
////	for (int i = 0; i < 10000; i++) {
////		srvMy->getRotAngleClosely(9890,801,1231, rZ,rY);
////	}
////	cout << "end:" << timeGetTime() << endl;
////	cout << "rZ=" << rZ << " rY=" << rY << endl;
////	double uvX, uvY, uvZ;
////	angle angRotZ, angRotY;
////	GgafDx9Util::getRotAngleZY(
////			0, 100000, 100,
////			uvX, uvY, uvZ,
////			angRotZ, angRotY
////			);
////
////	cout << "(" << uvX << "," << uvY << "," << uvZ << ")  RzRy = " << angRotZ << "/" << angRotY << endl;
////
////
//
//
////	unsigned short x,y,z;
////	int index;
////	for (int rZ = 900; rZ >= 0; rZ--) {
////		for (int rY = 0; rY <= 900; rY++) {
////			srvMy->getVectorClosely(rY,rZ,x,y,z);
////			index = (rZ*(900+1)+rY);
////			cout << "rZ=" << rZ << "/rY=" << rY << " srv[" << index << "]=" << GgafDx9SphereRadiusVectors::_sr[index].num_yzx << "(" << x << "," << y << "," << z << ")" << endl;
////		}
////	}
//
//
////	double x,y,z;
////	int index;
////	for (int rZ = 90000; rZ >= 0; rZ--) {
////		for (int rY = 0; rY <= 90000; rY++) {
////			GgafDx9Util::getNormalizeVectorZY(rZ,rY,x,y,z);
////			cout << "rZ=" << rZ << "/rY=" << rY << "(" << x*1000 << "," << y*1000 << "," << z*1000 << ")" << endl;
////			//index = (rZ*(900+1)+rY);
////			//cout << "rZ=" << rZ << "/rY=" << rY << " srv[" << index << "]=" << GgafDx9SphereRadiusVectors::_sr[index].num_yzx << "(" << x << "," << y << "," << z << ")" << endl;
////		}
////	}
//
////	delete srvMy;
////	::timeEndPeriod(1);//タイマー精度終了処理
//	return 0;
//}


