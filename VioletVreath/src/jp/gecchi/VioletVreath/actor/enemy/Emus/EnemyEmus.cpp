#include "stdafx.h"
#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
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
    _pActor_Base = nullptr;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_   = 120;

    pConn_LaserChipDepoStore_ = connect_DepositoryManager(
             "EnemyEmusLaserChip001DepoStore"
         );
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->peek());
    pLaserChipDepo_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    is_firing_ = false;
    useProgress(_BANPEI_-1);
}

void EnemyEmus::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEmus::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceWithMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}

void EnemyEmus::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyEmus::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }

            //����
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 3000);
            }
            if (_pProg->getFrameInProgress() == (frame_of_morph_interval_/2)) {
                //�J�����[�V�����������ȏ�܂œ��B�����Ȃ�
                _pProg->change(PROG_FIRE);
            }
            break;
        }
        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch()); //���[�U�[�Z�b�g��{�؂��������݂�
                if(pLaserChipDepo_) {
                    is_firing_ = true; //���[�U�[�Z�b�g�̎؂����o����
                } else {
                    is_firing_ = false; //���[�U�[�Z�b�g���؂��Ȃ�����
                }
            }
            //�I�[�v�������[�U�[
            if (is_firing_) {
                LaserChip* pChip = pLaserChipDepo_->dispatch();
                if (pChip) {
                    pChip->positionAs(this);
                    angle Rz, Ry;  //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾����
                    UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                           Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
                    pChip->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
                } else {
                    is_firing_ = false;
                }
            }

            if (_pProg->getFrameInProgress() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                is_firing_ = false;
                _pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    _pMorpher->behave();
    //_pKurokoA�̌v�Z�̓��[�J���ōs��
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyEmus::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
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
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
    pConn_LaserChipDepoStore_->close();
}
