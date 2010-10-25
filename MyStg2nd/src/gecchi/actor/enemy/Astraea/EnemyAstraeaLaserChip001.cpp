
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip001::EnemyAstraeaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "EnemyAstraeaLaserChip001";
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);
}

void EnemyAstraeaLaserChip001::initialize() {
    registHitAreaCube(15000);
    setHitAble(true);
    _SX = _SY = _SZ = 5*1000;
    _fAlpha = 0.9f;
    _fBoundingSphereRadius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void EnemyAstraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);

    _pMover->setMvVelo(10000);
    _pMover->setMvAcce(400);
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void EnemyAstraeaLaserChip001::processBehaviorHeadChip() {
    if (getActivePartFrame() == 40) {
        _pMover->execTagettingMvAngSequence(
                    pMYSHIP,
                    7000, 0,
                    TURN_ANTICLOSE_TO, false);
    }


    if (_pMover->_mv_ang_ry_target_flg == false && _pMover->_mv_ang_rz_target_flg == false) {
        _pMover->execTagettingMvAngSequence(
                    pMYSHIP,
                    100, 0,
                    TURN_CLOSE_TO, false);
    }
//
//    if (_frame_of_behaving_from_onActive == 35) {
//        _pMover->execTagettingMvAngSequence(
//                    pMYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}

void EnemyAstraeaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�q�b�g��
    //�̗͌v�Z
    int sta = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    if (sta <= 0) {
        //�q�b�g���ď��Ŏ�
        sayonara();
    } else {
        //�q�b�g���Đ�����
    }
}

EnemyAstraeaLaserChip001::~EnemyAstraeaLaserChip001() {

}

