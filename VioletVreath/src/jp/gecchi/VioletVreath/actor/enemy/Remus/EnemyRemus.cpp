#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyRemus::EnemyRemus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Remus", STATUS(EnemyRemus)) {
    _class_name = "EnemyRemus";
    _pActor_Base = NULL;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_   = 120;

    pCon_LaserChipDepoStore_ = connectToDepositoryManager(
             "DpCon_EnemyRemusLaserChip001DepoStore", NULL
         );
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());
    pLaserChipDepo_ = NULL;
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    wait_until_close_ = false;
    useProgress(PROG_HATCH_OPEN);
}

void EnemyRemus::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyRemus::initialize() {
    setHitAble(true);
    //_pKurokoA->setRzMvAngVelo(1000);
    //_pKurokoA->setRyMvAngVelo(500);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}

void EnemyRemus::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->set(PROG_HATCH_CLOSE);
}

void EnemyRemus::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }

            //����
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
                pLaserChipDepo_ = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch()); //���[�U�[�Z�b�g��{�؂��������݂�
                if(pLaserChipDepo_) {
                    wait_until_close_ = false;
                } else {
                    wait_until_close_ = true;
                }
            }

            //�I�[�v�����G�o������
            if (wait_until_close_ == false &&  _pMorpher->_weight[MORPHTARGET_HATCH_OPEN] > 0.5) { //���[�V�����������ȏ�܂œ��B�����Ȃ�
                if (pLaserChipDepo_) { //���[�U�[�Z�b�g���؂����ł��Ă�ꍇ
                    LaserChip* pChip = (LaserChip*)pLaserChipDepo_->dispatch();
                    if (pChip) {
                        //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾����
                        angle Rz, Ry;
                        UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                         Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
                        pChip->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
                        pChip->locateWith(this);
                    } else {
                        wait_until_close_ = true;
                    }
                }
            }

            if (_pProg->getFrameInProgress() >= frame_of_open_interval_+ frame_of_morph_interval_) {
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

void EnemyRemus::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveInTheTree()) {
//        (*(_pActor_Base->_pFunc_calcRotMvWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }


//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyRemus::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyRemus::onInactive() {
    sayonara();
}

EnemyRemus::~EnemyRemus() {
    pCon_LaserChipDepoStore_->close();
}
