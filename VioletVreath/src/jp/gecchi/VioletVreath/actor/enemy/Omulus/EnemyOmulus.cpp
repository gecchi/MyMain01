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
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyOmulus::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->forceRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOmulus::initialize() {
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
    pDepo_Fired_ = pDepoConnection_->peek();
}

void EnemyOmulus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    getProgress()->reset(PROG_HATCH_CLOSE);
}

void EnemyOmulus::processBehavior() {
    //���[�J���Ōv�Z���s��
    changeGeoLocal();

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
    //�EGgafDxKuroko(getKuroko())�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDxKuroko(getKuroko())�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    pKuroko->behave();
    //    changeGeoFinal();
    //TODO:���݊��������ƂȂ����B
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
                pKuroko->setFaceAngVelo(AXIS_X, -3000);
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
                pKuroko->setFaceAngVelo(AXIS_X, 0);
            }
            //processJudgement()�ŃV���b�g����
            if (pProg->getFrameInProgress() >= frame_of_open_interval_+ frame_of_morph_interval_) {
                pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);

//    if (getActiveFrame() % 10U == 0                   && 1 == 2) {
//        //���@�֕�����������
//        //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
//        //
//        //���@�ւ̌������߂̕ϊ��O��Ԃł̃^�[�Q�b�g�ʒu��(tvx, tvy, tvz) �Ƃ����A
//        //�u�y��܂Łv�̍s��̐ρi_pActor_base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
//        //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(mvx, mvy, mvz) �Ƃ���ƁA
//        //
//        //                | b_mat_11 b_mat_12 b_mat_13 |
//        //| tvx tvy tvz | | b_mat_21 b_mat_22 b_mat_23 | = | mvx mvy mvz |
//        //                | b_mat_31 b_mat_32 b_mat_33 |
//        //
//        //�ƂȂ�B���[�J�����W��(tvx, tvy, tvz) �̕�����������ƁA
//        //�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ�B
//        //�t�s����|����(tvx, tvy, tvz) �����߂�Ηǂ�
//        //
//        //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
//        // | tvx tvy tvz | = | mvx mvy mvz | | b_mat_21 b_mat_22 b_mat_23 |
//        //                                   | b_mat_31 b_mat_32 b_mat_33 |
//        //
//
//        //mvx mvy mvz �����߂�
//        int mvx = P_MYSHIP->_x - _x;
//        int mvy = P_MYSHIP->_y - _y;
//        int mvz = P_MYSHIP->_z - _z;
//        //�t�s��擾
//        D3DXMATRIX* pBaseInvMatRM = getBaseActor()->getInvMatWorldRotMv();
//        //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
//        int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz * pBaseInvMatRM->_31;
//        int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz * pBaseInvMatRM->_32;
//        int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz * pBaseInvMatRM->_33;
//        //�������������V�[�N�G���X�J�n
//        angle angRz_Target, angRy_Target;
//        UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target);
//        pKuroko->turnRzRyMvAngTo(angRz_Target, angRy_Target,
//                                   1000, 0,
//                                   TURN_CLOSE_TO, false);
//    }

    pScaler_->behave();
    getMorpher()->behave();

    pKuroko->behave();
    changeGeoFinal();
}

void EnemyOmulus::processJudgement() {
    //��΍��W���X�V����Ă���`
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_HATCH_OPEN: {
            //�I�[�v�����G�o������
            if (getMorphWeight(MORPHTARGET_HATCH_OPEN) > 0.5) { //���[�V�����������ȏ�܂œ��B�����Ȃ�
                if (pProg->getFrameInProgress() % (frame)(RF_EnemyOmulus_ShotInterval(G_RANK)) == 0) { //�o���Ԋu
                    if (pDepo_Fired_) {
                        GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
                            pActor->getKuroko()->setRzRyMvAng(_rz, _ry); //��΍��W�n�ł̌���
                            pActor->position(_x, _y, _z);
                            pActor->reset();
                        }
                    }
                }
            }
            break;
        }
        default :
            break;
    }


    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_base->_pFunc_calc_rot_mv_world_matrix))(_pActor_base, _matWorld);
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
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyOmulus::onInactive() {
    sayonara();
}

EnemyOmulus::~EnemyOmulus() {
    pDepoConnection_->close();
    GGAF_DELETE(pScaler_);
}
