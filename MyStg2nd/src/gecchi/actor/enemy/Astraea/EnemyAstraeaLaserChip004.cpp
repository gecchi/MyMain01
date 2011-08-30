#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip004::EnemyAstraeaLaserChip004(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip004)) {
    _class_name = "EnemyAstraeaLaserChip004";
    _pSplManufCon = connectSplineManufactureManager("GURUGURU");
    _pSplSeq = _pSplManufCon->use()->createSplineSequence(_pKurokoA);
}

void EnemyAstraeaLaserChip004::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleRate(5.0);
    setAlpha(0.9);
}
void EnemyAstraeaLaserChip004::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip004Status(_pStatus);

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pSplSeq->stop();
}

void EnemyAstraeaLaserChip004::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyAstraeaLaserChip004::processBehaviorHeadChip() {
    if (getActivePartFrame() == 2) {
        _pSplSeq->exec(RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    _pSplSeq->behave(); //←途中でちょんぎれたらだめじゃん
    _pKurokoA->behave();
}

void EnemyAstraeaLaserChip004::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyAstraeaLaserChip004::~EnemyAstraeaLaserChip004() {
    DELETE_IMPOSSIBLE_NULL(_pSplSeq);
    _pSplManufCon->close();
}

