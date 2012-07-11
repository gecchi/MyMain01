#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip001", STATUS(EnemyThisbeLaserChip001)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufCon_ = connectSplineManufactureManager("EnemyThisbeLaserChip002"); //ヒルベルト曲線
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
}

void EnemyThisbeLaserChip002::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyThisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    //_pKurokoA->setMvAcce(300);
    //_pKurokoA->forceRyMvAngVeloRange(-90000, 90000);
    _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[1]);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyThisbeLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}


void EnemyThisbeLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyThisbeLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
        _pKurokoA->setMvVelo(pSplSeq_->_distace_to_begin);
    } else if (prm_num_refraction > 0) {
        _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[pSplSeq_->_point_index]);
    }
    pSplSeq_->behave();
    _pKurokoA->behave();
}

void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyThisbeLaserChip002::~EnemyThisbeLaserChip002() {
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplManufCon_->close();
}


