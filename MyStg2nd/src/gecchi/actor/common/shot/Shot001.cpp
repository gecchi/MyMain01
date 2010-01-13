#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/ball_2") {
    _class_name = "Shot001";
    MyStgUtil::resetShot001Status(this);
}

void Shot001::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(1000);
    _pScaler->setScaleRange(300, 2000);
    useSe1("break_glass01");
}

void Shot001::onActive() {
    MyStgUtil::resetShot001Status(this);
    setBumpable(true);
    _pMover->setMoveVelocity(10000*_RANK_);             //�ړ����x
    _pMover->setFaceAngleVelocity(AXIS_X, 6000*_RANK_); //������݋
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //���W�ɔ��f
    _pMover->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe1();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
    inactivate();
}

Shot001::~Shot001() {
}
