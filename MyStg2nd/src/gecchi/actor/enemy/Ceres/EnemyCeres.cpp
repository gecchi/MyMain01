#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D EnemyCeres::_spline;

EnemyCeres::EnemyCeres(const char* prm_name, ActorDispatcher* prm_pDispatcher_EnemyCeresShots001) :
    DefaultMeshEnemyActor(prm_name, "Ceres") {
    _class_name = "EnemyCeres";

    _iMovePatternNo = 0;
    _pStgChecker->_iScorePoint = 100;

    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    _X_turn = GgafDx9Camera::_X_ScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;


    if (prm_pDispatcher_EnemyCeresShots001 == NULL) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        _pDispatcher_EnemyCeresShots001 = NEW ActorDispatcher("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        accept(KIND_ENEMY_SHOT_GU, _pDispatcher_EnemyCeresShots001);
        _createActorDispatcher = true;
    } else {
        //共有の弾が指定されてるの場合
        _pDispatcher_EnemyCeresShots001 = prm_pDispatcher_EnemyCeresShots001;
        _createActorDispatcher = false;
    }

    //ケレス用スプライン移動の定義
    if (EnemyCeres::_spline._num_basepoint == 0) { //ケレスクラスで１回だけ作成
        double p[][3] = { //        X ,        Y ,       Z
                           { -1024000 ,  -300000 ,  680000 },
                           {  -800000 ,   300000 ,  480000 },
                           {  -200000 ,  -300000 ,  200000 },
                           {   200000 ,   300000 ,  100000 },
                           {   400000 ,        0 ,       0 },
                           {   300000 ,        0 ,       0 },
                           {   200000 ,   200000 ,       0 },
                           {   100000 ,        0 ,  200000 },
                           {        0 ,  -200000 ,       0 },
                           {  -100000 ,        0 , -200000 },
                           {   300000 ,        0 ,       0 },
                           {        0 ,   300000 ,       0 },
                           {        0 ,        0 ,  300000 },
                           {  -300000 ,        0 ,       0 },
                           {        0 ,  -300000 ,       0 },
                           {        0 ,        0 , -300000 },
                           {  -800000 ,        0 ,       0 }
                        };
        EnemyCeres::_spline.init(p, 17, 0.2);
    }

    //Mover に渡すプログラムオブジェクトを生成しておく
    //_pProgram_CeresMove = NEW GgafDx9FixedVelocitySplineProgram(&EnemyCeres::_spline, 5000); //移動速度固定
    _pProgram_CeresMove = NEW GgafDx9FixedFrameSplineProgram(&EnemyCeres::_spline, 600, 5000); //移動フレーム数固定
    _dwFrame_Active = 0;
    useSe("a_shot");
}

void EnemyCeres::initialize() {
    setBumpable(true);
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
    _pMover->setFaceAngleVelocity(AXIS_X, 6000);
    _pMover->setMoveVelocity(8000);

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 1, 1, 1);

    _pMover->executeSplineMoveProgram(_pProgram_CeresMove, 0); //スプライン移動をプログラムしておく
}

void EnemyCeres::onActive() {

    _dwFrame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //方向転換
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadiationAngle2D(0, 32, way);
        EnemyCeresShot001* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (EnemyCeresShot001*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMoveAngle(-ANGLE90 + way[i], ANGLE90);
                pTama->activate();
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (EnemyCeresShot001*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMoveAngle(-ANGLE90 - way[i], -ANGLE90);
                pTama->activate();
            }
        }

        _iMovePatternNo++;
    }

    _pMover->behave(); //次の座標へ移動
    _dwFrame_Active++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfGameSpace()) {
        if (_createActorDispatcher) {
            //弾は遅れて開放させるように、動きを継続させるため移動
            getLordActor()->addSubLast(_pDispatcher_EnemyCeresShots001->getHeadActor()->extract());
           _pDispatcher_EnemyCeresShots001->adios(60 * 5);//解放予約
        }

        adios();
    }
}



void EnemyCeres::onInactive() {

}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9GeometricActor* pActor_Opponent = (GgafDx9GeometricActor*)prm_pActor_Opponent;
    setBumpable(false);
    playSe();

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pStgChecker->_iScorePoint;
    }


    if (_createActorDispatcher) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getLordActor()->addSubLast(getSubHeadActor(KIND_ENEMY_SHOT_GU)->extract());
       _pDispatcher_EnemyCeresShots001->adios(60 * 5);//解放予約
    } else {

    }

    adios(); //TODO:さよなら

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

int EnemyCeres::isOutOfGameSpace() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    DELETE_POSSIBLE_NULL(_pProgram_CeresMove);
}
