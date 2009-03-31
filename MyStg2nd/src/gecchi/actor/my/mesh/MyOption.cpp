#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOption::MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshActor(prm_name, "X/ceres") {
    _class_name = "MyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _distR = 50000;
    _angPosRotX = 0;
    _no = prm_no;
}

void MyOption::initialize() {


    _Y = _distR/2;
//    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());
//    _pChecker->useHitAreaBoxNum(1);
//    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
//    if (_no == 0) {
//        setGeometry(50000, 0, 0);
//        _pGeoMover->setMoveVelocity(3000);
//        _pGeoMover->setRzMoveAngleVelocity(2000);
//
//    } else {
//        _pGeoMover->setMoveVelocity(0);
//    }
//    //_pGeoMover->setRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
//    _pGeoMover->setRotAngleVelocity(AXIS_Y, 2000);
//    //setAlpha(0.2);

    _pGeoMover->setMoveVelocity(2000);
    //_pGeoMover->setRzRyMoveAngle(ANGLE90, 0);
    _pGeoMover->setRzMoveAngleVelocity(2000);
    //_pGeoMover->setRyMoveAngleVelocity(3000);

    _sangvelo = 0;
}

void MyOption::processBehavior() {
    _pGeoMover->addRyMoveAngle(-1*ANGLE90);
//
//    _pGeoMover->setMoveVelocity(3000);
//
//
//    float cos = GgafDx9Util::COS[_sangvelo];
//    float sin = GgafDx9Util::SIN[_sangvelo];
//
//    _sangvelo+=1;
//    if (_sangvelo >= S_ANG360) {
//        _sangvelo = 0;
//    }
//    int x = _distR*cos;
//    int y = _distR*sin;
//









//    if (_no == 0) {
//        //最初の
//        static int tmpX, tmpY, tmpZ;
//        _X = tmpX;
//        _Y = tmpY;
//        _Z = tmpZ;
//        _pGeoMover->behave();
//        tmpX = _X;
//        tmpY = _Y;
//        tmpZ = _Z;
//
//        _X += _pActor_Radical->_X;
//        _Y += _pActor_Radical->_Y - 50000;
//        _Z += _pActor_Radical->_Z;
//
//    } else {
//
//        _X = _pRing->get()->_X;
//        _Y = _pRing->get()->_Y;
//        _Z = _pRing->get()->_Z;
//        _pRing->get()->set(_pActor_Radical);
//        _pRing->next();
//
//        //ショット関連処理
//        //MyShip::transactShot(this);
//        _pGeoMover->behave();
//    }
//    //座標に反映
//    if (VB::isBeingPressed(VB_SHOT2)) {
//        //RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
//        MyLaserChip2* pLaser = (MyLaserChip2*)_pMyLaserChipRotation->obtain();
//        if (pLaser != NULL) {
//            pLaser->setRadicalActor(this);
//            //pLaser->_dwFrame_switchedToActiveFlg = _dwFrame;
//            //pLaser->activateAlone();
//        }
//    }


    _pGeoMover->behave();
}

void MyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}

MyOption::~MyOption() {
    //DELETE_IMPOSSIBLE_NULL(_pRing);
}
