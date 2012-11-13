#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip001", STATUS(EnemyThisbeLaserChip001)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufCon_ = connectToSplineManufactureManager("EnemyThisbeLaserChip002"); //ヒルベルト曲線
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
    setMiddleColliAble(true); //チップ間当たり判定自動発生
    end_active_frame_ = 0;
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
    _pKurokoA->relateFaceAngWithMvAng(true);
    end_active_frame_ = (_frame_standstill_refraction * _num_refraction     ) +
                        (_frame_between_refraction    * (_num_refraction-1) ) +
                        1; //

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
        //prm_num_refraction = 0 は、発射口→pSplSeq_->_point_index = 0 の点への移動直前処理
    }
    if (pSplSeq_->isExecuting()) {
        if (prm_num_refraction == 0) {
            _pKurokoA->setMvVelo(pSplSeq_->_distace_to_begin);
        } else {
            _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[prm_num_refraction]);
        }
    } else {
        //最後のリフレクションだった場合
        _pKurokoA->setMvVelo(0); //ちょっと sayonara() まで待機
    }
    //pSplSeq_->behave(); 内部で pKurokoA->_veloMv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pSplSeq_->behave(); の前に pKurokoA->setMvVelo() で設定しなければいけない。
    pSplSeq_->behave();
    _pKurokoA->behave();
}

void EnemyThisbeLaserChip002::processBehavior() {
    RefractionLaserChip::processBehavior();
    if (getActivePartFrame() == end_active_frame_+5) {
        sayonara();
    }
}


void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
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


