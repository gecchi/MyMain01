#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D EnemyCeres::_spline;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDispatcher* prm_pDispatcher_EnemyCeresShots001) :
    DefaultMeshEnemyActor(prm_name, "Ceres") {
    _class_name = "EnemyCeres";
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
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
        _pDispatcher_EnemyCeresShots001 = NEW GgafActorDispatcher("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        addSubGroup(_pDispatcher_EnemyCeresShots001);
        _createGgafActorDispatcher = true;
    } else {
        //共有の弾が指定されてるの場合
        _pDispatcher_EnemyCeresShots001 = prm_pDispatcher_EnemyCeresShots001;
        _createGgafActorDispatcher = false;
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

    useSe1("a_shot");
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
    _dwFrame_Active = 0;
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setFaceAngVelo(AXIS_X, 6000);
    _pMover->setMvVelo(8000);
    _pMover->executeSplineMoveProgram(_pProgram_CeresMove, 0); //スプライン移動をプログラムしておく
    _dwFrame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadiationAngle2D(0, 32, way);
        GgafDx9DrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDx9DrawableActor*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMvAng(-ANGLE90 + way[i], ANGLE90);
                pTama->activate();
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDx9DrawableActor*)_pDispatcher_EnemyCeresShots001->employ();
            if (pTama != NULL) {
                pTama->setGeometry(_X, _Y, _Z);
                pTama->_pMover->setRzRyMvAng(-ANGLE90 - way[i], -ANGLE90);
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
        inactivate();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        setHitAble(false);
        playSe1();
        inactivate(); //TODO:さよなら
        GgafDx9DrawableActor* pExplo001 = (GgafDx9DrawableActor*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorDispatcher) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getLordActor()->addSubLast(_pDispatcher_EnemyCeresShots001->getGroupActor()->becomeIndependent());
       _pDispatcher_EnemyCeresShots001->sayonara(60 * 5);//解放予約
    }
    sayonara();
}

bool EnemyCeres::isOutOfGameSpace() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    //staticなので最初の１回だけ解放したい
    DELETE_POSSIBLE_NULL(_pProgram_CeresMove);
}
