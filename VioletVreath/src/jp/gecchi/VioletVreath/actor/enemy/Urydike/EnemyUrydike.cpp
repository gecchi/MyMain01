#include "EnemyUrydike.h"

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
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/FormationUrydike.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyUrydike::EnemyUrydike(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Urydike", STATUS(EnemyUrydike)) {
    _class_name = "EnemyUrydike";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //�t�H�[���[�V�����I�u�W�F�N�g���ݒ肷��
    scatter_flg_ = false;
    delay_ = 0;
}

void EnemyUrydike::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyUrydike::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
}

void EnemyUrydike::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyUrydike::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
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
            }
            if (pProg->hasArrivedAt(10)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE_BEGIN: {
            if (pProg->isJustChanged()) {

            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE: {
            if (pProg->isJustChanged()) {
                getKuroko()->setMvAcce(0); //�����x������ꍇ�͐؂��Ă���
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION, 1);
            }
            pKurokoLeader_->behave(); //�X�v���C���ړ���U�镑��

            if (scatter_flg_) {
                pProg->changeNext();
            }
            break;
        }


        case PROG_SCATTER: {
            if (pProg->isJustChanged()) {
                delay_ = RND(0, 120);
            }
            if (pProg->hasArrivedAt(delay_)) {
                //�U��U��ɂȂ�
                pKurokoLeader_->stop();
                pKuroko->turnRzRyMvAngTo(RND_ABOUT(pKuroko->_ang_rz_mv, D_ANG(90)), RND_ABOUT(pKuroko->_ang_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pKuroko->setMvAcce(100);
            }

            if (pProg->hasArrivedAt(delay_ + 200)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }

    UTIL::updateEnemyRankPoint(this); //���Z�����N�|�C���g������
    pAFader_->behave();
    getKuroko()->behave();
}

void EnemyUrydike::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyUrydike::onHit(GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyUrydike::onInactive() {
    if (getBehaveingFrame() > 10) {
        //EnemyUrydikeCore�ɊǗ�����Ă���B���߂�Inactive()�ł��邽�߁B
        sayonara();
    }
}
void EnemyUrydike::scatter() {
    //Formation����w��������B
    scatter_flg_ = true;
}

EnemyUrydike::~EnemyUrydike() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
