#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOption::MyOption(const char* prm_name, const char* prm_model) : DefaultMeshActor(prm_name, prm_model, "DefaultMeshTechnique") {
    _class_name = "MyOption";

    _pRing = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 50; i++) {
        _pRing->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
//	GeometryChain* pFirst = NEW GeometryChain(GameGlobal::_pMyShip);
//	_pGeoElmActive
//	GeometryChain* pWork = pFirst;
//	GeometryChain* pTemp = NULL;
//	//for (DWORD i = 0; i < prm_dwBufferFrame-1; i++) {
//	for (DWORD i = 0; i < 50-1; i++) {
//		pTemp = NEW GeometryChain(GameGlobal::_pMyShip);
//		pWork->_next = pTemp;
//		pWork = pTemp;
//	}
//	pTemp->_next = pFirst;
//	_pGeoChainRingActive = pFirst;


    _pMyLaserChipRotation = NEW MyLaserChipRotationActor("ROTLaser");
    addSubLast(_pMyLaserChipRotation);

//
//    _pMyLaserChipRotation = NEW RotationActor("RotLaser001");
//    addSubLast(_pMyLaserChipRotation);//仮所属
//
//    MyLaserChip2* pChip;
//    for (int i = 0; i < 40; i++) { //レーザーストック
//        pChip = NEW MyLaserChip2("MY_Laser", "laserchip9");
//        pChip->inactImmediatelyAlone();
//        _pMyLaserChipRotation->addSubLast(pChip);
//        Sleep(1);
//    }

    _iMyNo = 0;
}

void MyOption::initialize() {
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    if (_iMyNo == 0) {
        setGeometry(50000, 0, 0);
        _pGeoMover->setMoveVelocity(3000);
        _pGeoMover->setRzMoveAngleVelocity(2000);

    } else {
        _pGeoMover->setMoveVelocity(0);
    }
    //_pGeoMover->setRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
    _pGeoMover->setRotAngleVelocity(AXIS_Y, 2000);
    //setAlpha(0.2);
}

void MyOption::processBehavior() {
    if (_iMyNo == 0) {
        //最初の
        static int tmpX, tmpY, tmpZ;
        _X = tmpX;
        _Y = tmpY;
        _Z = tmpZ;
        _pGeoMover->behave();
        tmpX = _X;
        tmpY = _Y;
        tmpZ = _Z;

        _X += _pActor_Radical->_X;
        _Y += _pActor_Radical->_Y - 50000;
        _Z += _pActor_Radical->_Z;

    } else {

        _X = _pRing->get()->_X;
        _Y = _pRing->get()->_Y;
        _Z = _pRing->get()->_Z;
        _pRing->get()->set(_pActor_Radical);
        _pRing->next();

        //ショット関連処理
        //MyShip::transactShot(this);
        _pGeoMover->behave();
    }
    //座標に反映
    if (VB::isBeingPressed(VB_SHOT2)) {
        //RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
        MyLaserChip2* pLaser = (MyLaserChip2*)_pMyLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->setRadicalActor(this);
            //pLaser->_dwFrame_switchedToActFlg = _dwFrame;
            //pLaser->actAlone();
        }
    }
}

void MyOption::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyOption::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}

MyOption::~MyOption() {
    DELETE_IMPOSSIBLE_NULL(_pRing);
}
