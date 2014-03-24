#include "stdafx.h"
#include "EnemyGlaja.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Glaja/EnemyGlajaLance001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlaja::EnemyGlaja(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Glaja", STATUS(EnemyGlaja)) {
    _class_name = "EnemyGlaja";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pConn_Shot_ = connect_DepositoryManager("GlajaLance001");
    effectBlendOne(); //���Z����
    setScaleR(0.3);
    useProgress(PROG_BANPEI);
    num_fire_ = 0;
}

void EnemyGlaja::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyGlaja::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyGlaja::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyGlaja::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setAlpha(0);
             _TRACE_("keepOnTurningFaceAngTwd keepOnTurningFaceAngTwd");
             pKuroko->keepOnTurningFaceAngTwd(pMyShip,
                                               D_ANG(2), 0, TURN_CLOSE_TO, false);
             setMorphWeight(0.0);
             UTIL::activateEntryEffectOf(this);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (pProg->getFrameInProgress() == 60) {
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
                 next_pos_.set(
                             pMyShip->_x + PX_C(300) + RND(PX_C(-100), PX_C(100)),
                             pMyShip->_y + RND(PX_C(-400), PX_C(400)),
                             pMyShip->_z + RND(PX_C(-400), PX_C(400))
                           ); //���̈ړ��ڕW���W
                 //�X�B�[����next_pos_�ֈړ�
                 pKuroko->setMvAngTwd(&next_pos_);
                 velo Vt = RF_EnemyGlaja_MvVelo(G_RANK);
                 velo Ve = 100;
                 coord D = UTIL::getDistance(this, &next_pos_);
                 pKuroko->hlprA()->slideMvByVd(Vt, D, 0.1, 0.5, Ve, true);
             }

             if (pKuroko->hlprA()->isJustFinishSlidingMv()) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE02: {
             if (pProg->isJustChanged()) {
             }
             if (pProg->getFrameInProgress() == 60) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_OPEN: {
             if (pProg->isJustChanged()) {
                 getMorpher()->transitionLinerUntil(MPH_OPEN, 1.0, 30);
             }
             if (pProg->getFrameInProgress() == 30) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_FIRE: {
             if (pProg->isJustChanged()) {
                 num_fire_ = RF_EnemyGlaja_ShotWay(G_RANK);
                 UTIL::shotWay004(
                     this,
                     pConn_Shot_->peek(),
                     PX_C(5),
                     num_fire_, D180ANG,
                     0, 0, // �������x�̓V���b�g���� onActive() �Őݒ肳���B
                     1, 0, 0.0f,
                     EnemyGlaja::onDispatchedShot
                 );

             }
             if (pProg->getFrameInProgress() >= num_fire_*5) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_CLOSE: {
             if (pProg->isJustChanged()) {
                 getMorpher()->transitionLinerUntil(MPH_OPEN, 0.0, 30);
             }
             if (pProg->getFrameInProgress() == 30) {
                 pProg->change(PROG_MOVE01); //�J��Ԃ�
             }
             break;
         }

         default:
             break;
     }
    pKuroko->behave();
    getMorpher()->behave();
    pAFader_->behave();
//_TRACE_("EnemyGlaja f:"<<getBehaveingFrame()<<"  pProg="<<pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyGlaja::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGlaja::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyGlaja::onInactive() {
}

void EnemyGlaja::onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate �㏑���Bnum_fire_*5 �� 5 �Ɠ����l�ɂ��邱��
}

EnemyGlaja::~EnemyGlaja() {
    pConn_Shot_->close();
    GGAF_DELETE(pAFader_);
}
