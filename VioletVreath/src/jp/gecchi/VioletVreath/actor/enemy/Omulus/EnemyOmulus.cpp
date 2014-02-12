#include "stdafx.h"
#include "EnemyOmulus.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyOmulus::EnemyOmulus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Omulus", STATUS(EnemyOmulus)) {
    _class_name = "EnemyOmulus";
    pScaler_ = NEW GgafDxScaler(this);
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_ = 120;

    pDepo_Fired_ = nullptr;
    pDepoConnection_ = connect_DepositoryManager("Talante");

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyOmulus::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyOmulus::initialize() {
    setHitAble(true);
    _pKuroko->relateFaceWithMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    setScale(1000);
    pScaler_->forceRange(1000, 1200);
    pScaler_->beat(30, 5, 5, -1);
    pDepo_Fired_ = pDepoConnection_->peek();
}

void EnemyOmulus::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyOmulus::processBehavior() {
    //�{�[���ɂ�����A�N�^�[�̃���
    //_x, _y, _z, _rx, _ry, _rz �ɂ��ĂQ�̍��W�n�Z�b�g��؂�ւ����K�v�Ȏd�l�ł��B
    //���ꂼ�ꃍ�[�J�����W�A�ŏI�i��΁j���W�ƌĂԂ��Ƃɂ��܂��B
    //�E�ŏI�i��΁j���W �E�E�E ���ʂ̃��[���h���W�n�̎��ł��B
    //�E���[�J�����W     �E�E�E �e�A�N�^�[�̊�_(0,0,0)����̑��ΓI�ȍ��W�n���Ӗ����܂��B
    //                          ���W�v�Z�͂�����ōs���ĉ������B
    //�����j��
    //  �@���W�v�Z�͎�Ƀ��[�J�����W�n�̌v�Z�ł���BGgafDxKuroko �Ń��[�J�����W�n�̑�����s�����ƂƂ���B
    //    �������A�W���ؓo�^��A�����蔻���A�^�[�Q�b�g���W�ȂǁA���̃I�u�W�F�N�g���烏�[���h���W���Q�Ƃ��铙�A
    //    ��{��Ԃ͍ŏI�i��΁j���W�n�B
    //    processBehavior()�J�n���� �ŏI�i��΁j���W�n(changeGeoFinal())�̏�ԂƂȂ��Ă���B
    //  �AprocessBehavior()���ŕK�v�ɉ����� changeGeoLocal() �Ń����o�[ _x, _y, _z, _rx, _ry, _rz �����[�J�����W�n��
    //    �؂�ւ��邱�Ƃ��\�B�ړ����̍��W�v�Z���s���B
    //  �B�A�� processBehavior() �𔲂���ۂɂ͕K���ŏI���W(changeGeoFinal())�̏�Ԃɖ߂��Ă������B
    //  �C�ŏI�i��΁j���W�ƁA���[�J�����W�݂͌��ɓƗ����A���͂��Ȃ����A
    //    �\�����̃��[���h�ϊ��s��쐬���A�s��ςō�������A�ŏI�I�ȕ\���ʒu�����肷��B

    //��changeGeoLocal(); ���s����
    //���[�J�����W�n�ɐؑւ��܂��B
    //�E_x, _y, _z     �E�E�E �́A���[�J�����W���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_x, _y, _z ��
    //                        ���[�J�����W�l�ɐ؂�ւ��܂��B
    //�E_rx, _ry, _rz  �E�E�E �́A���[�J�����W�ł̎���]�l���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_rx, _ry, _rz��
    //                        ���[�J�����W����]�l�ɐ؂�ւ��܂��B

    //��changeGeoFinal(); ���s����
    //�ŏI�i��΁j���W�n�ɐ؂�ւ��܂��B
    //�E_x, _y, _z    �E�E�E ���t���[�� GgafDxGeometricActor::processSettlementBehavior() �Ōv�Z���ꎩ���X�V����Ă܂��B
    //                       processBehavior() �� changeGeoFinal() ���s���ƁA�P�t���[���O��_x, _y, _z�ɐ؂�ւ�鎖�ɂȂ�܂��B
    //                       _x, _y, _z �͎Q�Ɛ�p�B�l�������Ă��Ӗ����L��܂���
    //�E_rx, _ry, _rz �E�E�E ���t���[�� GgafDxGeometricActor::processSettlementBehavior() �����������܂���I
    //                       changeGeoFinal(); �����s���Ă��A_rx, _ry, _rz �͈ȑO�̍ŏI�i��΁j���W�n�̒l��
    //                       ������ςȂ��ŕω����܂���B
    //                       ���̃I�u�W�F�N�g����A�{�[���ɂ�����A�N�^�[���Q�Ƃ���Ƃ��A_rx, _ry, _rz�͑S���M�p�ł��܂���B

    //�����Ӂ�
    //�EGgafDxKuroko(_pKuroko)�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDxKuroko(_pKuroko)�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    _pKuroko->behave();
    //    changeGeoFinal();
    //TODO:���݊��������ƂȂ����B

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKuroko->setFaceAngVelo(AXIS_X, -3000);
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
                _pKuroko->setFaceAngVelo(AXIS_X, 0);
            }

            //�I�[�v�����G�o������
            if (_pMorpher->_weight[MORPHTARGET_HATCH_OPEN] > 0.5) { //���[�V�����������ȏ�܂œ��B�����Ȃ�
                if (_pProg->getFrameInProgress() % (frame)(RF_EnemyOmulus_ShotInterval(G_RANK)) == 0) { //�o���Ԋu
                    if (pDepo_Fired_) {
                        GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
                            //�����݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���遄
                            //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
                            //���̕����x�N�g����(x_org_,y_org_,z_org_)�A
                            //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
                            //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
                            //
                            //                          | mat_11 mat_12 mat_13 |
                            // | x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                            //                          | mat_31 mat_32 mat_33 |
                            //
                            //vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
                            //vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
                            //vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
                            //
                            //���Ă����ŁA���X���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�l�����
                            //
                            //vX = x_org_*mat_11
                            //vY = x_org_*mat_12
                            //vZ = x_org_*mat_13
                            //
                            //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
                            //�ŏI�I�ȕ����x�N�g���́ix_org_*mat_11, x_org_*mat_12, x_org_*mat_13) �ł���B
                            angle Rz, Ry;
                            UTIL::convVectorToRzRy(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                                   Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
                            pActor->_pKuroko->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
                            pActor->positionAs(this);
                            pActor->reset();
                        }
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

    if (getActiveFrame() % 10U == 0                   && 1 == 2) {
        //���@�֕�����������
        //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
        //
        //���@�ւ̌������߂̕ϊ��O��Ԃł̃^�[�Q�b�g�ʒu��(tvx, tvy, tvz) �Ƃ����A
        //�u�y��܂Łv�̍s��̐ρi_pActor_Base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
        //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(mvx, mvy, mvz) �Ƃ���ƁA
        //
        //                | b_mat_11 b_mat_12 b_mat_13 |
        //| tvx tvy tvz | | b_mat_21 b_mat_22 b_mat_23 | = | mvx mvy mvz |
        //                | b_mat_31 b_mat_32 b_mat_33 |
        //
        //�ƂȂ�B���[�J�����W��(tvx, tvy, tvz) �̕�����������ƁA
        //�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ�B
        //�t�s����|����(tvx, tvy, tvz) �����߂�Ηǂ�
        //
        //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
        // | tvx tvy tvz | = | mvx mvy mvz | | b_mat_21 b_mat_22 b_mat_23 |
        //                                   | b_mat_31 b_mat_32 b_mat_33 |
        //

        //mvx mvy mvz �����߂�
        int mvx = P_MYSHIP->_x - _x;
        int mvy = P_MYSHIP->_y - _y;
        int mvz = P_MYSHIP->_z - _z;
        //�t�s��擾
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
        //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
        int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz * pBaseInvMatRM->_31;
        int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz * pBaseInvMatRM->_32;
        int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz * pBaseInvMatRM->_33;
        //�������������V�[�N�G���X�J�n
        angle angRz_Target, angRy_Target;
        UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target);
        _pKuroko->turnRzRyMvAngTo(angRz_Target, angRy_Target,
                                   1000, 0,
                                   TURN_CLOSE_TO, false);
    }

    pScaler_->behave();
    _pMorpher->behave();

    //_pKuroko�̌v�Z�̓��[�J���ōs��
    changeGeoLocal();
    _pKuroko->behave();
    changeGeoFinal();

}

void EnemyOmulus::processJudgement() {
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

void EnemyOmulus::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyOmulus::onInactive() {
    sayonara();
}

EnemyOmulus::~EnemyOmulus() {
    pDepoConnection_->close();
    GGAF_DELETE(pScaler_);
}
