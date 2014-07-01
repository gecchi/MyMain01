#include "stdafx.h"
#include "EnemyHisbe002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hisbe/EnemyHisbeLaserChip003.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbe002::EnemyHisbe002(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hisbe002", STATUS(EnemyHisbe002)) {
        //CubeMapMorphMeshActor(prm_name, "1/HisbeCM", STATUS(EnemyHisbe002)) {

    _class_name = "EnemyHisbe002";
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
    EnemyHisbeLaserChip003* pChip;
    for (int i = 0; i < 240; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  "EnemyHisbeLaserChip003[" << i << "]";
        pChip = NEW EnemyHisbeLaserChip003(name.str().c_str());
        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(240, 1, nullptr); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    addSubGroup(pLaserChipDepo_);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
}

void EnemyHisbe002::onCreateModel() {
}

void EnemyHisbe002::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Y, 500);
    pKuroko->relateFaceByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 40000);
}

void EnemyHisbe002::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getProgress()->reset(PROG_WAIT);
}

void EnemyHisbe002::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_->_num_chip_active == 0) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_OPEN: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(1, 1.0, 120);
            }
            if (!getMorpher()->isTransitioning()) {
                //���S�ɊJ������
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->positionAs(this);
                pLaser->getKuroko()->setRzRyMvAng(_rz, _ry);
                                   //���[�U�[�̃X�v���C����RELATIVE_DIRECTION�̂���MvAng�̐ݒ肪�K�v�B
                if (pLaser->getFrontChip() == nullptr) {
                    getSeTx()->play3D(SE_FIRE);
                }
            } else {
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: { //�P�T�C�N�����[�U�[�ł��؂���
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(1, 0.0, 120); //����
            }
            if (!getMorpher()->isTransitioning()) {
                //���S�ɕ�����
                pProg->change(PROG_WAIT);
            }
            break;
        }

        default: {
            break;
        }
    }

    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyHisbe002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHisbe002::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe002::onInactive() {
    //sayonara();
}

EnemyHisbe002::~EnemyHisbe002() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
