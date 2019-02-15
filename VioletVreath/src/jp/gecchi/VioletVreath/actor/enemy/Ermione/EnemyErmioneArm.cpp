#include "EnemyErmioneArm.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/KurokoFaceAngAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArm::EnemyErmioneArm(const char* prm_name, const char* prm_model) :
        DefaultMeshSetActor(prm_name, prm_model) {
    _class_name = "EnemyErmioneArm";

    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001"); //�r�j��
    useProgress(PROG_BANPEI);
    behave_frames_ = 0;
    arm_no_ = 0;
    arm_part_no_ = 0;
}


void EnemyErmioneArm::initialize() {
}

void EnemyErmioneArm::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErmioneArm::processBehavior() {

    changeGeoLocal(); //���[�J�����W�̑���Ƃ���B
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_WAITING);
            break;
        }
        case PROG_WAITING: {
            if (pProg->hasJustChanged()) {
                //�{�̂���FK�Ƃ��Ēǉ����ꂽ����́A��xprocessSettlementBehavior()�����s����Ȃ���
                //���W���f����Ȃ��A���������āB�P�t���[�����PROG_WAITING�ŃG���g���G�t�F���s�s����
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PROG_NOTHING: {
            if (pProg->hasJustChanged() ) {
                behave_frames_ = RND(1, 10);
            }
            if (pProg->hasArrivedAt(behave_frames_)) {
                pProg->change(PROG_AIMING);
            }
            break;
        }

        case PROG_AIMING: {
            if (pProg->hasJustChanged() ) {
                if (aiming_movable_limit_ang_ > 0) {
                    //���@�֕�����������
                    //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
                    //
                    //���@�ւ̌������߂̕ϊ��O��ԂŁA
                    //���[�J�����W�Łu�����Ă����΂����̂ł͂Ȃ����v�̕����̃x�N�g����(tvx, tvy, tvz) �Ƃ����A
                    //�u�y��܂Łv�̍s��̐ρi_pActor_base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
                    //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(mvx, mvy, mvz) �Ƃ���ƁA
                    //
                    // | b_mat_11 b_mat_12 b_mat_13 | |tvx|   |mvx|
                    // | b_mat_21 b_mat_22 b_mat_23 | |tvy| = |mvy|
                    // | b_mat_31 b_mat_32 b_mat_33 | |tvz|   |mvz|
                    //
                    //�ƂȂ�͂����B(tvx, tvy, tvz)�ɂ��ĉ����B�t�s����|���ċ��߂�Ηǂ��B
                    //
                    // |tvx|   | b_mat_11 b_mat_12 b_mat_13 | -1  |mvx|
                    // |tvy| = | b_mat_21 b_mat_22 b_mat_23 |     |mvy|
                    // |tvz|   | b_mat_31 b_mat_32 b_mat_33 |     |mvz|
                    //
                    //mvx mvy mvz �́A���@�ւ̕����x�N�g���ł���
                    int mvx,mvy,mvz;
                    if (RND(1, 1000) < 960 || arm_part_no_ >= 9) {
                        //��΍��W�n�Œʏ�̎��@��_�������x�N�g��
                        GgafDx::GeometricActor* pTargetActor = pMYSHIP;
                        mvx = pTargetActor->_x - _x_final; //�����Ŏ��g�� _x, _y, _z �͐�΍��W(_x_final)�ł��邱�Ƃ��|�C���g
                        mvy = (pTargetActor->_y + PX_C(50)) - _y_final; //���@�̂����_��
                        mvz = pTargetActor->_z - _z_final;
                    } else {
                        //���܁`�ɋt������ڕW�ɂ��āA�G��ɓ��������v����
                        GgafDx::GeometricActor* pTargetActor = pMYSHIP;
                        mvx = _x_final - pTargetActor->_x;
                        mvy = _y_final - pTargetActor->_y;
                        mvz = _z_final - pTargetActor->_z;
                    }
                    //�t�s��擾
                    D3DXMATRIX* pBaseInvMatRM = getBaseActor()->getInvMatWorldRotMv();
                    //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
                    int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz*pBaseInvMatRM->_31;
                    int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz*pBaseInvMatRM->_32;
                    int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz*pBaseInvMatRM->_33;
                    //�������������V�[�N�G���X�J�n
                    angle rz_target, ry_target;
                    UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target);
                    //�v�Z�̌��ʁArz_target ry_target �Ɍ����΁A���@�Ɍ�����

                    //rz_target�Ary_target ���͈͓��ɐ�������
                    if (aiming_movable_limit_ang_ <= rz_target && rz_target <= D180ANG) {
                        rz_target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= rz_target && rz_target <= D360ANG - aiming_movable_limit_ang_) {
                        rz_target = D360ANG - aiming_movable_limit_ang_;
                    }
                    if (aiming_movable_limit_ang_ <= ry_target && ry_target <= D180ANG) {
                        ry_target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= ry_target && ry_target <= D360ANG - aiming_movable_limit_ang_) {
                        ry_target = D360ANG - aiming_movable_limit_ang_;
                    }

                    pKuroko->turnRzRyFaceAngTo(
                                    rz_target, ry_target,
                                    aiming_ang_velo_, aiming_ang_velo_*0.01,
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
    if (_pActor_base) {
        setAlpha(((GgafDx::FigureActor*)_pActor_base)->getAlpha());
    }
}

void EnemyErmioneArm::processJudgement() {
    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
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
