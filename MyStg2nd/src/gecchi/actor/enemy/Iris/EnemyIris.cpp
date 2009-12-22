#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    _width_X = 220*2*LEN_UNIT;
    _height_Z = 220*2*LEN_UNIT;
    _depth_Y = 36*2*LEN_UNIT;
    _iMovePatternNo = 0;
}

void EnemyIris::initialize() {
    setBumpable(true);

    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    pRndGen->changeSeed(GameGlobal::_pSceneGame->_frame_of_life);
    DWORD appearances_renge_Z = (GameGlobal::_lim_MyShip_zleft - GameGlobal::_lim_MyShip_zright) * 3;
    DWORD appearances_renge_Y = (GameGlobal::_lim_MyShip_top - GameGlobal::_lim_MyShip_bottom) * 3;

    _X = GgafDx9Camera::_X_ScreenRight + 3200000;
    _Y = (pRndGen->genrand_int32() % (appearances_renge_Y)) - (appearances_renge_Y/2);
    _Z = (pRndGen->genrand_int32() % (appearances_renge_Z)) - (appearances_renge_Z/2);

    _pMover->setMoveVelocity(0);
    _pMover->setVxMoveVelocity(-5000);
    _pMover->setFaceAngleVelocity(AXIS_Z, 1000);

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
}

void EnemyIris::processBehavior() {
    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyIris::processJudgement() {
    if (isOutOfGameSpace()) {
        adios();
    }
}

void EnemyIris::processOnHit(GgafActor* prm_pActor_Opponent) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe1();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry((GgafDx9GeometricActor*)prm_pActor_Opponent);
        pExplo001->activate();
    }
}


EnemyIris::~EnemyIris() {
}
