#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D EnemyIris::_spIris_A;
GgafDx9Spline3D EnemyIris::_spIris_B;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    _iMovePatternNo = 0;

    //イリス用スプライン移動の定義(全イリスで１回だけ作成)
    if (EnemyIris::_spIris_A._num_basepoint == 0) {
        //後方から
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::_lim_behaind - 100000 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
           {      MyShip::_lim_front * 0.5 , MyShip::_lim_top * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 1.2 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
           {      MyShip::_lim_front * 1.0 , MyShip::_lim_top * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 0.5 ,                    0.0 ,                       0.0 }
        };
        EnemyIris::_spIris_A.init(p, 5, 0.2);
    }
    _pProgram_IrisMoveA = NEW GgafDx9FixedVelocitySplineProgram(&EnemyIris::_spIris_A, 5000); //移動速度固定

    if (EnemyIris::_spIris_B._num_basepoint == 0) {
        double p[][3] = { //           X  ,                          Y ,                         Z
           { MyShip::_lim_behaind - 100000 ,                         0 , MyShip::_lim_zright * 0.8 },
           {      MyShip::_lim_front * 0.5 , MyShip::_lim_bottom * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 1.2 , MyShip::_lim_bottom * 0.5 ,  MyShip::_lim_zleft * 0.3 },
           {      MyShip::_lim_front * 1.0 , MyShip::_lim_bottom * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 0.5 ,                       0.0 ,                       0.0 }
        };
        EnemyIris::_spIris_B.init(p, 5, 0.2);
    }
    _pProgram_IrisMoveB = NEW GgafDx9FixedVelocitySplineProgram(&EnemyIris::_spIris_B, 5000); //移動速度固定
}

void EnemyIris::initialize() {
    setBumpable(true);

    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    pRndGen->changeSeed(GameGlobal::_pSceneGame->_frame_of_life);

    _X = MyShip::_lim_behaind - 100000;
    _Y = 0;
    _Z = 0;

    _pMover->setMoveVelocity(5000);
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 99999, 99999, 99999);
    useSe1("yume_shototsu");
}

void EnemyIris::onActive() {
    _pMover->executeSplineMoveProgram(_pProgram_IrisMoveA, 0); //スプライン移動をプログラムしておく
}

void EnemyIris::processBehavior() {
    //座標に反映
    _pMover->behave();
}

void EnemyIris::processJudgement() {
//    if (isOutOfGameSpace()) {
//        adios();
//    }
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
