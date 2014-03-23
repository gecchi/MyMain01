#include "stdafx.h"
#include "EnemyErmioneArm.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyErmioneArm::EnemyErmioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyErmioneArm";

    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001"); //�r�j��
    useProgress(PROG_BANPEI);
    behave_frames_ = 0;
}


void EnemyErmioneArm::initialize() {
}

void EnemyErmioneArm::onActive() {
    _pStatus->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErmioneArm::processBehavior() {

    changeGeoLocal(); //���[�J�����W�̑���Ƃ���B
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_WAITING);
            break;
        }
        case PROG_WAITING: {
            if (pProg->isJustChanged()) {
                //�{�̂���FK�Ƃ��Ēǉ����ꂽ����́A��xprocessSettlementBehavior()�����s����Ȃ���
                //���W���f����Ȃ��A���������āB�P�t���[�����PROG_WAITING�ŃG���g���G�t�F���s�s����
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PROG_NOTHING: {
            if (pProg->isJustChanged() ) {
                behave_frames_ = RND(30, 60);
            }
            if (pProg->getFrameInProgress() == behave_frames_) {
                pProg->change(PROG_AIMING);
            }
            break;
        }

        case PROG_AIMING: {
            if (pProg->isJustChanged() ) {
                if (aiming_movable_limit_ang_ > 0) {
                    //���@�֕�����������
                    //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
                    //
                    //���@�ւ̌������߂̕ϊ��O��ԂŁA
                    //���[�J�����W�Łu�����Ă����΂����̂ł͂Ȃ����v�̕����̃x�N�g����(tvx, tvy, tvz) �Ƃ����A
                    //�u�y��܂Łv�̍s��̐ρi_pActor_Base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
                    //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(mvx, mvy, mvz) �Ƃ���ƁA
                    //
                    //                | b_mat_11 b_mat_12 b_mat_13 |
                    //| tvx tvy tvz | | b_mat_21 b_mat_22 b_mat_23 | = | mvx mvy mvz |
                    //                | b_mat_31 b_mat_32 b_mat_33 |
                    //
                    //�ƂȂ�͂����B(tvx, tvy, tvz)�ɂ��ĉ����B�t�s����|���ċ��߂�Ηǂ��B
                    //
                    //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
                    // | tvx tvy tvz | = | mvx mvy mvz | | b_mat_21 b_mat_22 b_mat_23 |
                    //                                   | b_mat_31 b_mat_32 b_mat_33 |
                    //
                    //mvx mvy mvz �����߂�
                    int mvx,mvy,mvz;
                    if (RND(1, 100) < 96) {
                        //��΍��W�n�Œʏ�̎��@��_�������x�N�g��
                        GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                        mvx = pTargetActor->_x - _x_final; //�����Ŏ��g�� _x, _y, _z �͐�΍��W(_x_final)�ł��邱�Ƃ��|�C���g
                        mvy = (pTargetActor->_y + PX_C(50)) - _y_final; //���@�̂����_��
                        mvz = pTargetActor->_z - _z_final;
                    } else {
                        //���܁`�ɋt������ڕW�ɂ��āA�G��ɓ��������v����
                        GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                        mvx = _x_final - pTargetActor->_x;
                        mvy = _y_final - pTargetActor->_y;
                        mvz = _z_final - pTargetActor->_z;
                    }
                    //�t�s��擾
                    D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
                    //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
                    int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz * pBaseInvMatRM->_31;
                    int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz * pBaseInvMatRM->_32;
                    int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz * pBaseInvMatRM->_33;
                    //�������������V�[�N�G���X�J�n
                    angle angRz_Target, angRy_Target;
                    UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target);
                    //�v�Z�̌��ʁAangRz_Target angRy_Target �Ɍ����΁A���@�Ɍ�����

                    //angRz_Target�AangRy_Target ���͈͓��ɐ�������
                    if (aiming_movable_limit_ang_ <= angRz_Target && angRz_Target <= D180ANG) {
                        angRz_Target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= angRz_Target && angRz_Target <= D360ANG - aiming_movable_limit_ang_) {
                        angRz_Target = D360ANG - aiming_movable_limit_ang_;
                    }
                    if (aiming_movable_limit_ang_ <= angRy_Target && angRy_Target <= D180ANG) {
                        angRy_Target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= angRy_Target && angRy_Target <= D360ANG - aiming_movable_limit_ang_) {
                        angRy_Target = D360ANG - aiming_movable_limit_ang_;
                    }

                    pKuroko->turnRzRyFaceAngTo(
                                    angRz_Target, angRy_Target,
                                    aiming_ang_velo_, aiming_ang_velo_*0.04,
                                    TURN_CLOSE_TO, false);
                }
            }
            if (pKuroko->isTurningFaceAng()) {
                // �ҋ@
            } else {
                pProg->change(PROG_NOTHING);
            }

            break;
        }

        default :
            break;
    }

    pKuroko->behave();
    changeGeoFinal();
    //pScaler_->behave();
    if (_pActor_Base) {
        setAlpha(((GgafDxDrawableActor*)_pActor_Base)->getAlpha());
    }
}

void EnemyErmioneArm::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }
}


void EnemyErmioneArm::onInactive() {
    sayonara();
}

void EnemyErmioneArm::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if ( prm_no == EVENT_ERMIONE_SAYONARA) {
        //�{�̔j��
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);//�����G�t�F
        sayonara();
    }
    if ( prm_no == EVENT_ERMIONE_ENTRY_DONE) {
        setHitAble(true);
        getProgress()->change(PROG_NOTHING);
    }
}

EnemyErmioneArm::~EnemyErmioneArm() {
}
