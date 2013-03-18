#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySappho::EnemySappho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Sappho", STATUS(EnemySappho)) {
    _class_name = "EnemySappho";
    _SX=_SY=_SZ=100;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(10);
}

void EnemySappho::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemySappho::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemySappho::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemySappho::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             locate(entry_pos_._X, entry_pos_._Y, entry_pos_._Z);
             _pAFader->setAlpha(0);
             _pKurokoA->setMvVelo(0);
             _pKurokoA->relateFaceAngWithMvAng(false);
             _pKurokoA->setMvAngTwd(hanging_pos_._X, hanging_pos_._Y, hanging_pos_._Z);
             _pKurokoA->setFaceAngTwd(hanging_pos_._X, hanging_pos_._Y, hanging_pos_._Z);
             _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(2));
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->intoTargetAlphaLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 coord d = UTIL::getDistance(_X, _Y, _Z,
                                             hanging_pos_._X, hanging_pos_._Y, hanging_pos_._Z);
                 _pKurokoA->execSmoothMvVeloSequenceD(
                              ((FormationSappho001*)getFormation())->velo_mv_,
                              RND(-PX_C(0.01), PX_C(0.01)),
                              d,
                              0.2, 0.2, false);
             }
             if (_pProg->getFrameInProgress() % 20 == 0) {
                 _pKurokoA->execTurnFaceAngSequenceTwd(P_MYSHIP,
                                                       D_ANG(1), 0,
                                                       TURN_CLOSE_TO, false);
             }
             if (_pKurokoA->isJustFinishSmoothMvVeloSequence()) {
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_MOVE02: {
             //滞留中
             if (_pProg->getFrameInProgress() % 20 == 0) {
                 _pKurokoA->execTurnFaceAngSequenceTwd(P_MYSHIP,
                                                       D_ANG(1), 0,
                                                       TURN_CLOSE_TO, false);
             }
             if (_pProg->getFrameInProgress() == 300) {
                 //敵弾発射
                 int way = RR_EnemySappho_ShotWay(_RANK_); //TODO:ショットWAY数

                 GgafDxDrawableActor* pShot = UTIL::activateShotOf(this);
                 if (pShot) {
                     pShot->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z],
                                                    _pKurokoA->_angFace[AXIS_Y]);
                     pShot->_pKurokoA->setMvVelo(PX_C(2));
                     pShot->_pKurokoA->setMvAcce(100);
                 }
             }
             if (_pProg->getFrameInProgress() == 600) {
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_MOVE03: {
             //さよなら準備
             if (_pProg->isJustChanged()) {
                 _pKurokoA->execTurnMvAngSequenceTwd(leave_pos_._X, leave_pos_._Y, leave_pos_._Z,
                                                     D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(10);
             }
             if (_pProg->getFrameInProgress() % 20 == 0) {
                 _pKurokoA->execTurnFaceAngSequenceTwd(P_MYSHIP, D_ANG(1), 0,
                                                       TURN_CLOSE_TO, false);
             }
             if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                 _pProg->changeNext();
             }

             break;
         }

         case PROG_MOVE04: {
             //さよなら～
             if (_pProg->isJustChanged()) {
                 _pKurokoA->execTurnMvAngSequenceTwd(leave_pos_._X, leave_pos_._Y, leave_pos_._Z,
                                                     D_ANG(10), 0, TURN_CLOSE_TO, false);
                 _pKurokoA->setMvAcce(100);
             }
             if (_pProg->getFrameInProgress() % 20 == 0) {
                 _pKurokoA->execTurnFaceAngSequenceTwd(P_MYSHIP, D_ANG(1), 0,
                                                       TURN_CLOSE_TO, false);
             }
             break;
         }
         default:
             break;
     }


    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemySappho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemySappho::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    }
}

void EnemySappho::onInactive() {
    sayonara();
}

EnemySappho::~EnemySappho() {
}
