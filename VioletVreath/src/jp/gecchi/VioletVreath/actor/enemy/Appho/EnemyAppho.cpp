#include "stdafx.h"
#include "EnemyAppho.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAppho::EnemyAppho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Appho", STATUS(EnemyAppho)) {
    _class_name = "EnemyAppho";
    pAFader_ = NEW GgafDxAlphaFader(this);
    _sx=_sy=_sz=100;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAppho::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAppho::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyAppho::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             setAlpha(0);
             _pKuroko->setMvVelo(0);
             _pKuroko->relateFaceWithMvAng(true);
             _pKuroko->setMvAngTwd(&hanging_pos_);
             _pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->getFrameInProgress() == 60) {
                 pAFader_->transitionLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 //�ؗ��|�C���g��GO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 _pKuroko->hlprA()->slideMvByVd(mv_velo, d,
                                        0.2, 0.8, RND(-PX_C(0.5),PX_C(0.5)), true);
             }
             //�ؗ��|�C���g�܂ňړ���
             if (_pProg->getFrameInProgress() % 32U == 0) {
                 //���傭���傭���@�����߂�
                 _pKuroko->turnFaceAngTwd(P_MYSHIP, D_ANG(0.5), 0,
                                           TURN_CLOSE_TO, true);
             }
             if (_pKuroko->hlprA()->isJustFinishSlidingMv()) {
                 _pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pKuroko->_veloMv<<","<<_pKuroko->_accMv);
             break;
         }

         case PROG_MOVE02: {
             if (_pProg->isJustChanged()) {
                 //�ړ������ƌ����̘A�g����
                 _pKuroko->relateFaceWithMvAng(false);
                 //�ؗ��|�C���g�����A�ӂ�ӂ�C�܂܂ȕ����ֈړ�������
                 _pKuroko->turnMvAngTwd(_x + RND(-PX_C(100),PX_C(100)),
                                         _y + RND(-PX_C(100),PX_C(100)),
                                         _z + RND(-PX_C(100),PX_C(100)),
                                         100, 0, TURN_CLOSE_TO, false);
                 //������莩�@�̕��֌�������
                 _pKuroko->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //�ؗ���
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 //���傭���傭���@�����߂�
                 _pKuroko->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (_pProg->getFrameInProgress() == 180) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num = RF_EnemyAppho_ShotWay(G_RANK); //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxDrawableActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         pShot->_pKuroko->setRzRyMvAng(_rz, _ry);
                         pShot->_pKuroko->setMvVelo(shot_velo);
                         pShot->_pKuroko->setMvAcce(100);
                     }
                 }
             }
             if (_pProg->getFrameInProgress() == 240) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //����Ȃ珀��
             if (_pProg->isJustChanged()) {
                 //������肳��Ȃ�|�C���g�֌�����
                 _pKuroko->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 _pKuroko->setMvAcce(10);
             }
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 _pKuroko->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!_pKuroko->isTurningMvAng()) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //����Ȃ�`
             if (_pProg->isJustChanged()) {
                 _pKuroko->turnMvAngTwd(&leave_pos_,
                                         D_ANG(1), 0, TURN_CLOSE_TO, false);
                 _pKuroko->setMvAcce(100+(G_RANK*200));
             }
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 //���傭���傭���@�����߂�
                 _pKuroko->turnFaceAngTwd(P_MYSHIP,
                                           D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }
         default:
             break;
     }
    _pKuroko->behave();
    //_pSeTx->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAppho::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
    GGAF_DELETE(pAFader_);
}
