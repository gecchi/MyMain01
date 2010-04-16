﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "Flora") {
    _class_name = "Shot001";
    MyStgUtil::resetShot001Status(_pStatus);
    prepareSe(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
}

void Shot001::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(300, 2000);
}

void Shot001::onActive() {
    MyStgUtil::resetShot001Status(_pStatus);
    setHitAble(true);
    _pMover->setMvVelo(10000*_RANK_);             //移動速度
    _pMover->setFaceAngVelo(AXIS_X, 6000*_RANK_); //きりもみ具合
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //座標に反映
    _pMover->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        playSe3D(0);
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        inactivate();
    }
}

Shot001::~Shot001() {
}
