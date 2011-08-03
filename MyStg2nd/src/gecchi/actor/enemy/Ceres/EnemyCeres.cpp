#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorStore* prm_pStore_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres") {
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



    if (prm_pStore_EnemyCeresShots001 == NULL) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        _pStore_EnemyCeresShots001 = NEW GgafActorStore("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //最初非表示
            _pStore_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        addSubGroup(_pStore_EnemyCeresShots001);
        _createGgafActorStore = true;
    } else {
        //共有の弾が指定されてるの場合
        _pStore_EnemyCeresShots001 = prm_pStore_EnemyCeresShots001;
        _createGgafActorStore = false;
    }

    _pSplineCon = (Spline3DConnection*)(P_GOD->_pSpline3DManager->getConnection("SpCon_001"));
    //_pProgram_CeresMove = NEW GgafDx9FixedVelocitySplineProgram(&EnemyCeres::_spline, 5000); //移動速度固定
    _pProgram_CeresMove = NEW GgafDx9FixedFrameSplineProgram(this, _pSplineCon->refer(), 600, 5000); //移動フレーム数固定

    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "a_shot", GgafRepeatSeq::nextVal("CH_a_shot"));
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    MyStgUtil::resetEnemyCeresStatus(_pStatus);
    _iMovePatternNo = 0;
    _frame_Active = 0;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    _pProgram_CeresMove->begin(0); //スプライン移動を開始
    _frame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDx9Util::getWayAngle2D(180000, 8, 10000, way);
        GgafDx9Util::getRadialAngle2D(0, 32, way);
        GgafDx9DrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDx9DrawableActor*)_pStore_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-ANGLE90 + way[i], ANGLE90);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDx9DrawableActor*)_pStore_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-ANGLE90 - way[i], -ANGLE90);
            }
        }

        _iMovePatternNo++;
    }
    _pProgram_CeresMove->behave(); //スプライン移動を進める
    _pKurokoA->behave(); //次の座標へ移動
    //_pSeTransmitter->behave();
    _frame_Active++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        setHitAble(false);
        _pSeTransmitter->play3D(0);
        GgafDx9DrawableActor* pExplo001 = (GgafDx9DrawableActor*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorStore) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getDirector()->addSubLast(_pStore_EnemyCeresShots001->getMyGroupHead()->extract());
       _pStore_EnemyCeresShots001->sayonara(60 * 5);//解放予約
    }
    sayonara();
}

bool EnemyCeres::isOutOfUniverse() {
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
