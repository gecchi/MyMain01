#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyLaser001::MyLaser001(const char* prm_name) : DefaultSpriteMyActor(prm_name, "S/Laser001") {
    _class_name = "MyLaser001";
}

void MyLaser001::initialize() {
    setAnimationMethod(ORDER_LOOP, 1);

    _pGeoMover->setMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -5000, -5000, 5000, 5000);

    _pActor_Radical = NULL;

    setBumpableAlone(true);
}

void MyLaser001::processBehavior() {
    if (switchedToActive()) {
        //�o��������
        setBumpableAlone(true);
        setGeometry(_pActor_Radical);
        _pGeoMover->setRotAngle(AXIS_Z, _pActor_Radical->_pGeoMover->_angRot[AXIS_Z]);
        _pGeoMover->setRotAngle(AXIS_Y, _pActor_Radical->_pGeoMover->_angRot[AXIS_Y]);
        _pGeoMover->setRzRyMoveAngle(_pActor_Radical->_pGeoMover->_angRot[AXIS_Z],
                                     _pActor_Radical->_pGeoMover->_angRot[AXIS_Y]);
        _X_prevFrame = _pActor_Radical->_X;
        _Y_prevFrame = _pActor_Radical->_Y;
        _Z_prevFrame = _pActor_Radical->_Z;

    } else {
        //�ʏ폈��
        nextAnimationFrame();

    }
    //���W�ɔ��f
    _pGeoMover->behave();

    _X += (_pActor_Radical->_X - _X_prevFrame);
    _Y += (_pActor_Radical->_Y - _Y_prevFrame);
    _Z += (_pActor_Radical->_Z - _Z_prevFrame);
    _X_prevFrame = _pActor_Radical->_X;
    _Y_prevFrame = _pActor_Radical->_Y;
    _Z_prevFrame = _pActor_Radical->_Z;

}

void MyLaser001::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    if (isOffScreen()) {
        inactivate();
    }
}

/*
 bool MyLaser001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
 //TRACE("MyLaser001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"��"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
 return false;
 }
 */

void MyLaser001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("MyLaser001::processOnHit �V���b�g���q�b�g���܂���");
    //_TRACE_("MyLaser001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
    //farewell();
    inactivate();
}

void MyLaser001::onInactive() {
    setBumpableAlone(false);
}

MyLaser001::~MyLaser001() {

}
