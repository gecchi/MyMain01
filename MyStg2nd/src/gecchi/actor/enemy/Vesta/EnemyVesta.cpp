#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyVesta::EnemyVesta(const char* prm_name) : DefaultMeshActor(prm_name, "Vesta") {
    _class_name = "EnemyVesta";
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _width_X = 220*2*LEN_UNIT;
    _height_Z = 220*2*LEN_UNIT;
    _depth_Y = 36*2*LEN_UNIT;
    _iMovePatternNo = 0;
}

void EnemyVesta::initialize() {
    int nArea = 0;
    for (int i = 0; i < (_width_X - _depth_Y) ; i+= _depth_Y) {
        nArea++;
    }
    _pStgChecker->useHitAreaBoxNum(nArea);
    for (int i = 0, n = 0; i < (_width_X - _depth_Y)  ; i+= _depth_Y, n++) {
        _pStgChecker->setHitAreaBox(n, i - ((_depth_Y/2.0)/1.5)-(_width_X/2 - _depth_Y/2.0), -((_depth_Y/2.0)/1.5), -(_height_Z/2.0),
                                       i + ((_depth_Y/2.0)/1.5)-(_width_X/2 - _depth_Y/2.0),  ((_depth_Y/2.0)/1.5),  (_height_Z/2.0),
                                       false, false, true
                                   );
    }
    _pStgChecker->setStatus(100, 99999, 99999, 99999);
    useSe1("yume_shototsu");
    useSe2("bomb1");     //爆発
}

void EnemyVesta::onActive() {
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _iMovePatternNo = 0;

    _pMover->setMoveVelocity(0);
    _pMover->setVxMoveVelocity(-5000);
    _pMover->setFaceAngleVelocity(AXIS_Z, 1000);

    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    pRndGen->changeSeed(GameGlobal::_pSceneGame->_frame_of_active);
    DWORD appearances_renge_Z = (MyShip::_lim_zleft - MyShip::_lim_zright) * 3;
    DWORD appearances_renge_Y = (MyShip::_lim_top - MyShip::_lim_bottom) * 3;
    _X = GgafDx9Camera::_X_ScreenRight + 3200000;
    _Y = (pRndGen->genrand_int32() % (appearances_renge_Y)) - (appearances_renge_Y/2);
    _Z = (pRndGen->genrand_int32() % (appearances_renge_Z)) - (appearances_renge_Z/2);
    setBumpable(true);
}

void EnemyVesta::processBehavior() {
    //座標に反映
    _pMover->behave();
}

void EnemyVesta::processJudgement() {
    if (isOutOfGameSpace()) {
        adios();
    }
}

void EnemyVesta::processOnHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    setTechniqueTemporarily("Flush", 2); //フラッシュ
    playSe1();
        //ここに消滅エフェクト
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
        pExplo001->activate();
    }
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここに消滅エフェクト
        EffectExplosion001* pExplo001_2 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        playSe2();
        if (pExplo001_2 != NULL) {
            pExplo001_2->setGeometry((GgafDx9GeometricActor*)prm_pOtherActor);
            pExplo001_2->activate();
        }
        inactivate();
    }
}

void EnemyVesta::onInctive() {
    adios();
}
EnemyVesta::~EnemyVesta() {
}
