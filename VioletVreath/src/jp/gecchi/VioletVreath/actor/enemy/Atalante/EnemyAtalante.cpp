#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAtalante::EnemyAtalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Atalante", STATUS(EnemyAtalante)) {
    _class_name = "EnemyAtalante";
    pDepo_Shot_ = NULL;
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    Z_ok_ = Y_ok_ = false;
    useProgress(10);
}

void EnemyAtalante::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAtalante::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(false); //falseです！
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
    _pProg->set(PROG_INIT);
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
            if (_pProg->hasJustChanged()) {
            }
            if (_pProg->getFrameInProgress() > 60) {
                _pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (_pProg->hasJustChanged()) {
            }
            MyShip* pMyShip = P_MYSHIP;
            if (Z_ok_ == false && pMyShip->_Z - PX_C(10) <= _Z && _Z <= pMyShip->_Z + PX_C(10)) {
                //Z座標揃った
                Z_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Y <= _Y) {
                    //真下へ折れる
                    _pKurokoA->execTurnMvAngSequence(D270ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //真上へ折れる
                    _pKurokoA->execTurnMvAngSequence(D90ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_Y - PX_C(10) <= _Y && _Y <= pMyShip->_Y + PX_C(10)) {
                //Y座標揃った
                Y_ok_ = true;
                _pKurokoA->addMvVelo(2000);
                if (pMyShip->_Z <= _Z) {
                    //奥の自機の方向折れる
                    _pKurokoA->execTurnMvAngSequence(0, D90ANG,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //手前の自機の方向折れる
                    _pKurokoA->execTurnMvAngSequence(0, D270ANG,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (_pKurokoA->isRunnigTurnMvAngSequence() == false) {
                if (Y_ok_ && Z_ok_) {
                    _pProg->changeNext(); //次の動きへ
                }
                if (_pProg->getFrameInProgress() >= 480) {
                    _pProg->changeNext(); //次の動きへ
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (_pProg->hasJustChanged()) {
                //X軸方向に動く
                MyShip* pMyShip = P_MYSHIP;
                if (pMyShip->_X <= _X) {
                    //左へ折れる
                    _pKurokoA->execTurnMvAngSequence(D180ANG, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //右へ折れる
                    _pKurokoA->execTurnMvAngSequence(0, 0,
                                                     D_ANG(6), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (_pKurokoA->isRunnigTurnMvAngSequence() == false) {
                _pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (_pProg->hasJustChanged()) {
                _pKurokoA->setMvAcce(300);
            }
            break;
        }

    }
    _pKurokoA->behave();

    //_pSeTxer->behave();
}

void EnemyAtalante::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAtalante::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActivePartFrame() < 50 && (pOther->getKind() & KIND_CHIKEI)) {
        //出現50フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

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


