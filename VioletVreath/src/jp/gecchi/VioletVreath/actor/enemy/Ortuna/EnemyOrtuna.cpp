#include "stdafx.h"
#include "EnemyOrtuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOrtuna::EnemyOrtuna(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ortuna", STATUS(EnemyOrtuna)) {
    _class_name = "EnemyOrtuna";
    _sx=_sy=_sz=100;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(_BANPEI_-1);
}

void EnemyOrtuna::onCreateModel() {
//    _pModel->setSpecular(5.0, 1.0);
}

void EnemyOrtuna::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyOrtuna::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyOrtuna::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             _pAFader->setAlpha(0);
             _pKurokoA->setMvVelo(0);
             _pKurokoA->relateFaceWithMvAng(true);
             _pKurokoA->setMvAngTwd(&hanging_pos_);
             velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
             _pKurokoA->setFaceAngVelo(AXIS_X, mv_velo); //���邮��`
             _pMorpher->setWeight(0.0);
             UTIL::activateEntryEffectOf(this);
             _pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->fadeLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (_pProg->isJustChanged()) {
                 //�܂�Ԃ��|�C���g��GO!
                 //velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
                 velo mv_velo = PX_C(20);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 _pKurokoA->setMvVelo(mv_velo);//�����悭�|�[����
                 hanging_pos_frames_ = _pKurokoA->setMvAcceByD(d, PX_C(1));
             }

             _pKurokoA->setFaceAngVelo(AXIS_X, _pKurokoA->_veloMv); //�����ɔ�Ⴕ�Ă��邮��`

             if (_pProg->getFrameInProgress() > hanging_pos_frames_) {
                 _pKurokoA->setMvVelo(PX_C(1));
                 _pKurokoA->setMvAcce(0);
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE02: {
             if (_pProg->isJustChanged()) {
                 //�����]��
                 //������莩�@�̕��֌�������
                 _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                         D_ANG(3), 0, TURN_CLOSE_TO, true);
                 _pMorpher->morphLinerUntil(MPH_OPEN, 1.0, 60);
             }
             //�ؗ���
             if (_pProg->getFrameInProgress() % 16U == 0) {
                 if (_pKurokoA->isTurningMvAng()) {
                     //���傭���傭���@�����߂�
                     _pKurokoA->turnFaceAngTwd(P_MYSHIP,
                                               D_ANG(1), 0, TURN_CLOSE_TO, true);
                 }
             }

             if (_pProg->getFrameInProgress() == 60) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num = RF_EnemyOrtuna_ShotWay(G_RANK); //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyOrtuna_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxDrawableActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         pShot->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z],
                                                        _pKurokoA->_angFace[AXIS_Y]);
                         pShot->_pKurokoA->setMvVelo(shot_velo);
                         pShot->_pKurokoA->setMvAcce(100);
                     }
                 }
             }
             if (_pProg->getFrameInProgress() == 60) {
                 _pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //����Ȃ�`
             if (_pProg->isJustChanged()) {
                 _pKurokoA->setMvVelo(PX_C(4));
                 _pKurokoA->setMvAcce(100);
             }
             break;
         }

         default:
             break;
     }

    _pKurokoA->behave();
    _pMorpher->behave();
    //_pSeTx->behave();
}

void EnemyOrtuna::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOrtuna::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyOrtuna::onInactive() {
    sayonara();
}

EnemyOrtuna::~EnemyOrtuna() {
}
