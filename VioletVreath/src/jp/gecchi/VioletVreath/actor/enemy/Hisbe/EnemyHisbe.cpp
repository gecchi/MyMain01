#include "stdafx.h"
#include "EnemyHisbe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbe::EnemyHisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hisbe", STATUS(EnemyHisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/HisbeCM", STATUS(EnemyHisbe)) {

    _class_name = "EnemyHisbe";
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

//    //���t���N�V����------>
//    GgafActorDepository* pDepoEffect = NEW GgafActorDepository("HisbeLaser");
//    EffectLaserRefraction001* pEffect;
//    for (int i = 0; i < 100; i++) {
//        std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
//        pEffect = NEW EffectLaserRefraction001(name.c_str());
//        pDepoEffect->addSubLast(pEffect);
//    }
//    addSubGroup(pDepoEffect);
//
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip002["+XTOS(i)+"]";
//        EnemyHisbeLaserChip002* pChip = NEW EnemyHisbeLaserChip002(name.c_str());
//        int num_refraction = pChip->pKurokoLeader_->getPointNum();
//        pChip->config(num_refraction, 1, 1, false, pDepoEffect);
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //�z�[�~���O------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(300, 1, nullptr); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 300; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip001["+XTOS(i)+"]";
//        EnemyHisbeLaserChip001* pChip = NEW EnemyHisbeLaserChip001(name.c_str());
//        pChip->_is_fix_begin_pos = false;
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //��------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip003["+XTOS(i)+"]";
//        EnemyHisbeLaserChip003* pChip = NEW EnemyHisbeLaserChip003(name.c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------


    //�z�[�~���O(���|�W�g��)------>
//    pConn_LaserChipDepoStore_ = connect_DepositoryManager("EnemyHisbeLaserChip001DepoStore");
//    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���t���N�V����(���|�W�g��)------>
    pConn_LaserChipDepoStore_ = connect_DepositoryManager("EnemyHisbeLaserChip002DepoStore");
    pLaserChipDepo_ = nullptr;

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
}

void EnemyHisbe::onCreateModel() {
}

void EnemyHisbe::initialize() {
    getKuroko()->relateFaceWithMvAng(true);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliSphere(0, 40000);

//    if (pConn_LaserChipDepoStore_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_LaserChipDepoStore_�́A���V("<<this<<")����Ă��G�w���I")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pConn_LaserChipDepoStore_->peek()->extract()
//                );
//    }
}

void EnemyHisbe::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getProgress()->reset(PROG_WAIT);
}

void EnemyHisbe::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_) {
                if (pLaserChipDepo_->_num_chip_active == 0) {
                    pLaserChipDepo_ = nullptr;
                }
            } else {
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
            if (pProg->isJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pConn_LaserChipDepoStore_->peek()->dispatch()); //���[�U�[�Z�b�g��{�؂�܂��B
            }
            if (pLaserChipDepo_) {
                LaserChip* pLaser = pLaserChipDepo_->dispatch();
                if (pLaser) {
                    pLaser->positionAs(this);
                    pLaser->getKuroko()->setRzRyMvAng(_rz, _ry);
                                       //���[�U�[�̃X�v���C����RELATIVE_DIRECTION�̂���MvAng�̐ݒ肪�K�v�B
                    if (pLaser->_pChip_front == nullptr) {
                        getSeTx()->play3D(SE_FIRE);
                    }
                } else {
                    pProg->changeNext();
                }
            } else {
                //�؂��Ȃ������I
                pProg->changeNext();
            }
            break;
        }

        case PROG_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            getMorpher()->transitionLinerUntil(1, 0.0, 120); //����
            if (!getMorpher()->isTransitioning()) {
                //���S�ɕ�����
                pProg->change(PROG_WAIT);
            }
            break;
        }

        default:
            break;
    }
    getKuroko()->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyHisbe::processJudgement() {
    if (isOutOfUniverse()) {
        if (_x >= GgafDxUniverse::_x_gone_right) {
            //WALL������
        } else {
            sayonara();
        }
    }
}

void EnemyHisbe::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe::onInactive() {
    //sayonara();
}

EnemyHisbe::~EnemyHisbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
        pConn_LaserChipDepoStore_->close();
    //pConn_RefractionEffectDepository_->close();
}