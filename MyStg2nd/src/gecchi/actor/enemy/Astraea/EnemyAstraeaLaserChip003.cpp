
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip003::EnemyAstraeaLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "AstraeaLaserChip003") {
    _class_name = "EnemyAstraeaLaserChip003";
//    MyStgUtil::resetEnemyAstraeaLaserChip003Status(_pStatus);
    _pSplManufCon = connectSplineManufactureManager("ttt");
    _pSplSeq = _pSplManufCon->use()->createSplineSequence(_pKurokoA);
}

void EnemyAstraeaLaserChip003::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleRate(5.0);
    setAlpha(0.9);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyAstraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
//    MyStgUtil::resetEnemyAstraeaLaserChip003Status(_pStatus);


    _pSplSeq->exec(2); //�����������Ƀ��[���h�ϊ�
}

void EnemyAstraeaLaserChip003::processBehavior() {

    _pSplSeq->behave();
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}

void EnemyAstraeaLaserChip003::onHit(GgafActor* prm_pOtherActor) {
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
void EnemyAstraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyAstraeaLaserChip003::~EnemyAstraeaLaserChip003() {
    DELETE_IMPOSSIBLE_NULL(_pSplSeq);
    _pSplManufCon->close();
}

