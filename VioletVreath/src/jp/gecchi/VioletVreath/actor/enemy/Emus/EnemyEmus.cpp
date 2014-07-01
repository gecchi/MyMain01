#include "stdafx.h"
#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyEmus::EnemyEmus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Emus", STATUS(EnemyEmus)) {
    _class_name = "EnemyEmus";
    pScaler_ = NEW GgafDxScaler(this);
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_ = 120;

//    pConn_LaserChipDepoStore_ = connect_DepositoryManager(
//             "EnemyEmusLaserChip001DepoStore"
//         );
//    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->peek());
    pLaserChipDepo_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    is_firing_ = false;
    useProgress(PROG_BANPEI);
}

void EnemyEmus::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->forceRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyEmus::initialize() {
    setHitAble(true);
    getKuroko()->relateFaceByMvAng(true);
    getMorpher()->forceRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 200000);
    setScale(1000);
    pScaler_->forceRange(1000, 1200);
    pScaler_->beat(30, 5, 0, 20, -1);
}

void EnemyEmus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    getProgress()->reset(PROG_HATCH_CLOSE);
}

void EnemyEmus::processBehavior() {
    changeGeoLocal(); //�v�Z�̓��[�J�����W�n
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                           0.0f, frame_of_morph_interval_);
                pKuroko->setFaceAngVelo(AXIS_X, 0);
            }

            //����
            if (pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pKuroko->setFaceAngVelo(AXIS_X, 3000);
            }
            if (pProg->getFrameInProgress() == (frame_of_morph_interval_/2)) {
                //�J�����[�V�����������ȏ�܂œ��B�����Ȃ�
                pProg->change(PROG_FIRE);
            }
            break;
        }
        case PROG_FIRE: {
            if (pProg->isJustChanged()) {

                if (!pLaserChipDepo_) {
                    pLaserChipDepo_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
                }
                if(pLaserChipDepo_) {
                    is_firing_ = true; //���[�U�[�Z�b�g�̎؂����o����
                } else {
                    is_firing_ = false; //���[�U�[�Z�b�g���؂��Ȃ�����
                }
            }


            if (pProg->getFrameInProgress() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                is_firing_ = false;
                pLaserChipDepo_ = nullptr;
                pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);

    getMorpher()->behave();
    pKuroko->behave();
    changeGeoFinal();
}

void EnemyEmus::processJudgement() {
    //��΍��W���X�V����Ă���`�I�[�v�������[�U�[
    if (is_firing_) {
        LaserChip* pChip = pLaserChipDepo_->dispatch();
        if (pChip) {
            pChip->position(_x, _y, _z);
            pChip->getKuroko()->setRzRyMvAng(_rz, _ry); //��΍��W�n�ł̌���
        } else {
            is_firing_ = false;
        }
    }

    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_Base->_pFunc_calcRotMvWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }


//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyEmus::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
    GGAF_DELETE(pScaler_);
//    pConn_LaserChipDepoStore_->close();
}
