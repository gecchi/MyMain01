#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCeres)) {
    _class_name = "EnemyCeres";
    iMovePatternNo_ = 0;
    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    X_turn_ = GgafDxCamera::_X_ScreenRight - 30000;
    Y_turn_ = -10000;
    Z_turn_ = 0;

    if (prm_pDepo_EnemyCeresShots001 == NULL) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        pDepo_EnemyCeresShots001_ = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmed(); //最初非表示
            pDepo_EnemyCeresShots001_->addSubLast(pCeresShot001);
        }
        addSubGroup(pDepo_EnemyCeresShots001_);
        createGgafActorDepository_ = true;
    } else {
        //共有の弾が指定されてるの場合
        pDepo_EnemyCeresShots001_ = prm_pDepo_EnemyCeresShots001;
        createGgafActorDepository_ = false;
    }

    pSplLineCon_ = connectToSplineLineManager("SpCon_001");
    pProgram_CeresMove_ = NEW FixedVelocitySplineSequence(_pKurokoA, pSplLineCon_->use(), 5000); //移動速度固定

//    pProgram_CeresMove_ = NEW FixedFrameSplineSequence(_pKurokoA, pSplLineCon_->use(), 600, 5000); //移動フレーム数固定
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
    iMovePatternNo_ = 0;
    frame_Active_ = 0;
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    pProgram_CeresMove_->exec(ABSOLUTE_COORD); //スプライン移動を開始
    frame_Active_ = 0;
}

void EnemyCeres::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換
    if (iMovePatternNo_ == 0 && _X > 400000) {

        angle way[32];
        //GgafDxUtil::getWayAngle2D(180000, 8, 10000, way);
        GgafDxUtil::getRadialAngle2D(0, 32, way);
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pProgram_CeresMove_->behave(); //スプライン移動を進める
    _pKurokoA->behave(); //次の座標へ移動
    //_pSeTransmitter->behave();
    frame_Active_++;
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
        GgafDxDrawableActor* pExplo001 = (GgafDxDrawableActor*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

void EnemyCeres::onInactive() {
    if (createGgafActorDepository_) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getSceneDirector()->addSubLast(pDepo_EnemyCeresShots001_->getMyGroupHead()->extract());
       pDepo_EnemyCeresShots001_->sayonara(60 * 5);//解放予約
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
    pSplLineCon_->close();
    DELETE_POSSIBLE_NULL(pProgram_CeresMove_);
}
