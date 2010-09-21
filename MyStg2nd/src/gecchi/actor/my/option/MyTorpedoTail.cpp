
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyTorpedoTail::MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pMyTorpedo) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "MyTorpedoTail";
    _pMyTorpedo = prm_pMyTorpedo;
    //MyStgUtil::resetMyTorpedoTailStatus(_pStatus);
//    _pTarget = NULL;
}

void MyTorpedoTail::initialize() {
    //registHitAreaCube(80000);
    setHitAble(false); //�����蔻�薳��
    _SX = _SY = _SZ = 6*1000;
    _fAlpha = 0.3f;
    _fBoundingSphereRadius = 5.0f;
//    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void MyTorpedoTail::onActive() {
    HomingLaserChip::onActive();

    //�X�e�[�^�X���Z�b�g
    //MyStgUtil::resetMyTorpedoTailStatus(_pStatus);
//
//    _pMover->setMvVelo(5000);
//    _pMover->setMvAcce(1000);
//    _pMover->setRzMvAngVelo(0);
//    _pMover->setRyMvAngVelo(0);
//    _pMover->setRzMvAngAcce(0);
//    _pMover->setRyMvAngAcce(0);
//    _pMover->forceMvVeloRange(1000, 80000);
//    _pMover->forceRzMvAngVeloRange(-40000, 40000);
//    _pMover->forceRyMvAngVeloRange(-40000, 40000);
//    _pMover->stopTagettingMvAngSequence();
}
void MyTorpedoTail::onInactive() {
//    if (_pChip_behind) {
//        _pChip_behind->inactivate(); //�����Y���Y�����Ə���
//                                     //�擪��inactivate()����̂�MyTorpedo�̃q�b�g�����A�̈�O�̎��̂�
//    }
    HomingLaserChip::onInactive();

}
void MyTorpedoTail::processBehaviorHeadChip() {

    setGeometry(_pMyTorpedo);
    setRotation(_pMyTorpedo);






    //������MyTorpedo�̑���̓R�R�ɂȂ�܂��B
    //MyTorpedo��MyTorpedoTail��HeadChip�ɂ������Ă��邾���ł��B
//    if (getActivePartFrame() <= 120 && getActivePartFrame() % 5 == 0) {
//        if (_pTarget) {
//            if (_pTarget->isActive())  {
//                _pMover->execTagettingMvAngSequence(
//                            _pTarget,
//                            3000, 300,
//                            TURN_CLOSE_TO, false);
//            } else {
//                //�܂�����
//                _pMover->setRzMvAngVelo(0);
//                _pMover->setRyMvAngVelo(0);
//                _pMover->setRzMvAngAcce(0);
//                _pMover->setRyMvAngAcce(0);
//            }
//        } else {
//                _pMover->execTagettingMvAngSequence(
//                            GgafDx9Universe::_X_goneRight, pMYSHIP->_Y, pMYSHIP->_Z,
//                            3000, 300,
//                            TURN_CLOSE_TO, false);
//        }
//    }
//
//    if ( getActivePartFrame() == 300) {
//        _pMover->setRzMvAngVelo(0);
//        _pMover->setRyMvAngVelo(0);
//        _pMover->setRzMvAngAcce(0);
//        _pMover->setRyMvAngAcce(0);
//    } else if ( getActivePartFrame() > 120 && getActivePartFrame() % 5 == 0)  {
//        if (_pTarget) {
//            if (_pTarget->isActive())  {
//                if (_pMover->isTagettingMvAng()) {
//
//                } else {
//                    _pMover->execTagettingMvAngSequence(
//                                _pTarget,
//                                200, 0,
//                                TURN_CLOSE_TO, false);
//                }
//            }
//        } else {
//            _pMover->setRzMvAngVelo(0);
//            _pMover->setRyMvAngVelo(0);
//            _pMover->setRzMvAngAcce(0);
//            _pMover->setRyMvAngAcce(0);
//        }
////    }
//
//
//    _pMover->behave();
}

void MyTorpedoTail::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //�q�b�g��
//    //�̗͌v�Z
//    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//    if (sta <= 0) {
//        //�q�b�g���ď��Ŏ�
//        sayonara();
//    } else {
//        //�q�b�g���Đ�����
//    }
}

MyTorpedoTail::~MyTorpedoTail() {

}

