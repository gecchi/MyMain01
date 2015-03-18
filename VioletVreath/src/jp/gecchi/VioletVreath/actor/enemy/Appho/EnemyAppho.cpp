#include "EnemyAppho.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAppho::EnemyAppho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Appho", STATUS(EnemyAppho)) {
    _class_name = "EnemyAppho";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAppho::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    setScale(100);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAppho::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAppho::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {

         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             setAlpha(0);
             pKuroko->setMvVelo(0);
             pKuroko->relateFaceByMvAng(true);
             pKuroko->setMvAngTwd(&hanging_pos_);
             pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
             UTIL::activateEntryEffectOf(this);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (pProg->hasArrivedAt(60)) {
                 pAFader_->transitionLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (pProg->isJustChanged()) {
                 //�ؗ��|�C���g��GO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 pKuroko->asstA()->slideMvByVd(mv_velo, d,
                                               0.2, 0.8, 200, true);
             }
             //�ؗ��|�C���g�܂ňړ���
             if (pProg->getFrame() % 32U == 0) {
                 //���傭���傭���@�����߂�
                 pKuroko->turnFaceAngTwd(P_MYSHIP, D_ANG(0.5), 0,
                                         TURN_CLOSE_TO, true);
             }
             if (pKuroko->asstA()->isJustFinishSlidingMv()) {
                 pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pKuroko->_velo_mv<<","<<_pKuroko->_acc_mv);
             break;
         }

         case PROG_MOVE02: {
             if (pProg->isJustChanged()) {
                 //�ړ������ƌ����̘A�g����
                 pKuroko->relateFaceByMvAng(false);
                 //�ؗ��|�C���g�����A���@�����փW�����ړ�������
                 pKuroko->turnMvAngTwd(P_MYSHIP,
                                       100, 0, TURN_CLOSE_TO, false);
                 //������莩�@�̕��֌�������
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //�ؗ���
             if (pProg->getFrame() % 16U == 0) {
                 //���傭���傭���@�����߂�
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (pProg->hasArrivedAt(180)) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num   = RF_EnemyAppho_ShotWay(G_RANK);    //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxFigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                         pShot_pKuroko->setRzRyMvAng(_rz, _ry);
                         pShot_pKuroko->setMvVelo(shot_velo);
                         pShot_pKuroko->setMvAcce(100);
                     }
                 }
             }
             if (pProg->hasArrivedAt(240)) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //����Ȃ珀��
             if (pProg->isJustChanged()) {
                 //������肳��Ȃ�|�C���g�֌�����
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(10);
             }
             if (pProg->getFrame() % 16U == 0) {
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!pKuroko->isTurningMvAng()) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //����Ȃ�`
             if (pProg->isJustChanged()) {
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(100+(G_RANK*200));
             }
             if (pProg->getFrame() % 16U == 0) {
                 //���傭���傭���@�����߂�
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }

         default: {
             break;
         }
     }
    pKuroko->behave();
    pAFader_->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAppho::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
    GGAF_DELETE(pAFader_);
}
