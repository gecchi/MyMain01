#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAtalante::EnemyAtalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Atalante", STATUS(EnemyAtalante)) {
    _class_name = "EnemyAtalante";
    pDepo_Shot_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    Z_ok_ = Y_ok_ = false;
    useProgress(10);
}

void EnemyAtalante::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAtalante::initialize() {
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAtalante::config(
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyAtalante::onActive() {
    _pStatus->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    _pKurokoA->setMvAcce(0);
    _pKurokoA->setMvVelo(4000);
    _pKurokoA->forceMvVeloRange(50000);
    _pProg->reset(PROG_INIT);
}

void EnemyAtalante::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->changeNext();
            break;
        }

        case PROG_MOVE01_1: {
            //ちょっとそのまま真っ直ぐ進む
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() > 60) {
                _pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (_pProg->isJustChanged()) {
            }
            MyShip* pMyShip = P_MYSHIP;
            if (Z_ok_ == false && pMyShip->_Z - PX_C(10) <= _Z && _Z <= pMyShip->_Z + PX_C(10)) {
                //Z座標揃った
                Z_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Y <= _Y) {
                    //真下へ折れる
                    _pKurokoA->turnRzRyMvAngTo(D270ANG, 0,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //真上へ折れる
                    _pKurokoA->turnRzRyMvAngTo(D90ANG, 0,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_Y - PX_C(10) <= _Y && _Y <= pMyShip->_Y + PX_C(10)) {
                //Y座標揃った
                Y_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Z <= _Z) {
                    //奥の自機の方向折れる
                    _pKurokoA->turnRzRyMvAngTo(0, D90ANG,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //手前の自機の方向折れる
                    _pKurokoA->turnRzRyMvAngTo(0, D270ANG,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (_pKurokoA->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z座標Y座標揃ったら次の動きへ
                    _pProg->changeNext();
                } else if (_pProg->getFrameInProgress() >= 480) {
                    //Z座標Y座標揃わずとも一定時間で次の動きへ
                    _pProg->changeNext();
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (_pProg->isJustChanged()) {
                //X軸方向に動く
                MyShip* pMyShip = P_MYSHIP;
                if (pMyShip->_X <= _X) {
                    //左へ折れる
                    _pKurokoA->turnRzRyMvAngTo(D180ANG, 0,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //右へ折れる
                    _pKurokoA->turnRzRyMvAngTo(0, 0,
                                               D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (_pKurokoA->isTurningMvAng() == false) {
                _pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvAcce(300);
            }
            break;
        }

    }
    _pKurokoA->behave();

    //_pSeTx->behave();
}

void EnemyAtalante::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAtalante::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActivePartFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
        //出現30フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

//        //自機側に撃たれて消滅の場合、
//        if (pOther->getKind() & KIND_MY) {
//            //アイテム出現
//            UTIL::activateItemOf(this);
//        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
    }
}

void EnemyAtalante::onInactive() {
}

EnemyAtalante::~EnemyAtalante() {
}


