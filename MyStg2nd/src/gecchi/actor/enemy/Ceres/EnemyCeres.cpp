#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCeres)) {
    _class_name = "EnemyCeres";
    _iMovePatternNo = 0;
    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    _X_turn = GgafDxCamera::_X_ScreenRight - 30000;
    _Y_turn = -10000;
    _Z_turn = 0;
    _veloBegin = 5000;



    if (prm_pDepo_EnemyCeresShots001 == NULL) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        _pDepo_EnemyCeresShots001 = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmediately(); //最初非表示
            _pDepo_EnemyCeresShots001->addSubLast(pCeresShot001);
        }
        addSubGroup(_pDepo_EnemyCeresShots001);
        _createGgafActorDepository = true;
    } else {
        //共有の弾が指定されてるの場合
        _pDepo_EnemyCeresShots001 = prm_pDepo_EnemyCeresShots001;
        _createGgafActorDepository = false;
    }

    _pSplLineCon = connectSplineLineManager("SpCon_001");
    _pProgram_CeresMove = NEW FixedVelocitySplineSequence(_pKurokoA, _pSplLineCon->use(), 5000); //移動速度固定

//    _pProgram_CeresMove = NEW FixedFrameSplineSequence(_pKurokoA, _pSplLineCon->use(), 600, 5000); //移動フレーム数固定
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "a_shot", GgafRepeatSeq::nextVal("CH_a_shot"));
}

void EnemyCeres::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    _pStatus->reset();
    _iMovePatternNo = 0;
    _frame_Active = 0;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    _pProgram_CeresMove->exec(ABSOLUTE_COORD); //スプライン移動を開始
    _frame_Active = 0;
}

void EnemyCeres::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換
    if (_iMovePatternNo == 0 && _X > 400000) {

        angle way[32];
        //GgafDxUtil::getWayAngle2D(180000, 8, 10000, way);
        GgafDxUtil::getRadialAngle2D(0, 32, way);
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)_pDepo_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)_pDepo_EnemyCeresShots001->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        setHitAble(false);
        _pSeTransmitter->play3D(0);
        GgafDxDrawableActor* pExplo001 = (GgafDxDrawableActor*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (_createGgafActorDepository) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getSceneDirector()->addSubLast(_pDepo_EnemyCeresShots001->getMyGroupHead()->extract());
       _pDepo_EnemyCeresShots001->sayonara(60 * 5);//解放予約
    }
    sayonara();
}

bool EnemyCeres::isOutOfUniverse() {
    if (_X < GgafDxCamera::_X_ScreenLeft - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    //staticなので最初の１回だけ解放したい
    _pSplLineCon->close();
    DELETE_POSSIBLE_NULL(_pProgram_CeresMove);
}
