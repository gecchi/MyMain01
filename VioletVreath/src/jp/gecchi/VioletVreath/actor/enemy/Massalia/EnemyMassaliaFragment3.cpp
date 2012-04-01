#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment3::EnemyMassaliaFragment3(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment3)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassaliaFragment3::onCreateModel() {
}

void EnemyMassaliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PXCO(20));
    _pKurokoA->setFaceAngVelo(DANG(0), DANG(10), DANG(0));
}

void EnemyMassaliaFragment3::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyMassaliaFragment3Status(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment3::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment3::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment3::onHit(GgafActor* prm_pOtherActor) {
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locatedBy(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();
        //アイテム出現
        Item* pItem = employFromCommon(MagicPointItem001);
        if (pItem) {
            pItem->locatedBy(this);
        }
    }
}


void EnemyMassaliaFragment3::onInactive() {
    sayonara();
}


EnemyMassaliaFragment3::~EnemyMassaliaFragment3() {
}
