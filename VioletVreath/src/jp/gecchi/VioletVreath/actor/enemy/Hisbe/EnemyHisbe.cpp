#include "EnemyHisbe.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectLaserRefraction001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hisbe/EnemyHisbeLaserChip002.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbe::EnemyHisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hisbe", STATUS(EnemyHisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/HisbeCM", STATUS(EnemyHisbe)) {

    _class_name = "EnemyHisbe";
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

//    //���t���N�V����------>
//    GgafActorDepository* pDepoEffect = NEW GgafActorDepository("HisbeLaser");
//    EffectLaserRefraction001* pEffect;
//    for (int i = 0; i < 100; i++) {
//        std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
//        pEffect = NEW EffectLaserRefraction001(name.c_str());
//        pDepoEffect->put(pEffect);
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
//        pLaserChipDepo_->put(pChip);
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
    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyHisbeLaserChip001DepoStore");
    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���t���N�V����(���|�W�g��)------>
//    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyHisbeLaserChip002DepoStore");
//    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���ʂ̃��[�U�[


    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSe->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
}

void EnemyHisbe::onCreateModel() {
}

void EnemyHisbe::initialize() {
//    getKuroko()->linkFaceAngByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 40000);

//    if (pConn_pDepoStore_laser_set->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_pDepoStore_laser_set�́A���V"<<NODE_INFO<<"����Ă��G�w���I")
//        getPlatformScene()->bringDirector()->addSubGroup(
//                pConn_pDepoStore_laser_set->peek()->extract()
//                );
//    }
}

void EnemyHisbe::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getProgress()->reset(PROG_WAIT);
}

void EnemyHisbe::processBehavior() {
    GgafProgress* const pProg = getProgress();
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
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinerUntil(1, 1.0, 120);
            }
            if (!getMorpher()->isTransitioning()) {
                //���S�ɊJ������
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (pProg->hasJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pConn_pDepoStore_laser_set->peek()->dispatch()); //���[�U�[�Z�b�g��{�؂�܂��B
            }
            if (pLaserChipDepo_) {
                LaserChip* pLaser = pLaserChipDepo_->dispatch();
                if (pLaser) {
                    pLaser->placeAs(this);
                    pLaser->setFaceAngAs(this); //���[�U�[�̃X�v���C����RELATIVE_COORD_DIRECTION�̂��ߌ����ݒ肪�K�v�B
                    if (pLaser->getInfrontChip() == nullptr) {
                        getSeTransmitter()->play3D(SE_FIRE);
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

        case PROG_CLOSE: { //�P�T�C�N�����[�U�[�ł��؂���
            if (pProg->hasJustChanged()) {
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
    getKuroko()->behave();
    getMorpher()->behave();
    getSeTransmitter()->behave();
}

void EnemyHisbe::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbe::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe::onInactive() {
    //sayonara();
}

EnemyHisbe::~EnemyHisbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pConn_pDepoStore_laser_set->close();
    //pConn_pRefractionEffectDepository_->close();
}
