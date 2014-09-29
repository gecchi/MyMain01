#include "EnemyOebius.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyOebius::EnemyOebius(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Oebius", STATUS(EnemyOebius)) {
    _class_name = "EnemyOebius";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //�t�H�[���[�V�����I�u�W�F�N�g���ݒ肷��
}

void EnemyOebius::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebius::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyOebius::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOebius::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(1.0, 30);
                pKuroko->setSpinAngVelo(D_ANG(3));
                pKuroko->setMvVelo(PX_C(3));
            }
            if (pProg->getFrameInProgress() == 10) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE_BEGIN: {
            if (pProg->isJustChanged()) {

            }
            if (pProg->getFrameInProgress() == 30) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE: {
            if (pProg->isJustChanged()) {
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION, 4);
            }
            pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��

            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE_AFTER: {
            if (pProg->isJustChanged()) {
                position(pKurokoLeader_->_x_start, pKurokoLeader_->_y_start, pKurokoLeader_->_z_start);

                pKuroko->setRzRyMvAng(pKurokoLeader_->_ang_rz_mv_start, pKurokoLeader_->_ang_ry_mv_start);
                pKuroko->setMvVelo(PX_C(8));
                pKuroko->setRzRyMvAngVelo(0,0);
                pKuroko->turnRzMvAngTo(pKuroko->_ang_rz_mv + D_ANG(35), D_ANG(2), 0, TURN_CLOSE_TO);
            }
            if (!pKuroko->isTurningMvAng()) {
                pProg->change(PROG_MOVE_BEGIN);
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->getFrameInProgress() == 60) {
                sayonara();
                pProg->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);

    pAFader_->behave();
    getKuroko()->behave();
}

void EnemyOebius::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOebius::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyOebius::onInactive() {
    sayonara();
}

EnemyOebius::~EnemyOebius() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
