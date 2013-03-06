#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArm::EnemyHermioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyHermioneArm";
    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001"); //�r�j��
    useProgress(10);
}


void EnemyHermioneArm::initialize() {
}

void EnemyHermioneArm::onActive() {
    _pStatus->reset();
    _pProg->set(PROG_INIT);
}

void EnemyHermioneArm::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_WAITING);
            break;
        }
        case PROG_WAITING: {
            if (_pProg->isJustChanged()) {
                //�{�̂���FK�Ƃ��Ēǉ����ꂽ����́A��xprocessSettlementBehavior()�����s����Ȃ���
                //���W���f����Ȃ��A���������āB�P�t���[�����PROG_WAITING�ŃG���g���G�t�F���s�s����
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PROG_NOTHING: {
            if (_pProg->getFrameInProgress() == 10) {
                _pProg->change(PROG_AIMING);
            }
            break;
        }

        case PROG_AIMING: {
            if (_pProg->isJustChanged() ) {
                //���@�֕�����������
                //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
                //
                //���@�ւ̌������߂̕ϊ��O��ԂŁA
                //���[�J�����W�Łu�����Ă����΂����̂ł͂Ȃ����v�̕����̃x�N�g����(TvX, TvY, TvZ) �Ƃ����A
                //�u�y��܂Łv�̍s��̐ρi_pActor_Base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
                //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(MvX, MvY, MvZ) �Ƃ���ƁA
                //
                //                | b_mat_11 b_mat_12 b_mat_13 |
                //| TvX TvY TvZ | | b_mat_21 b_mat_22 b_mat_23 | = | MvX MvY MvZ |
                //                | b_mat_31 b_mat_32 b_mat_33 |
                //
                //�ƂȂ�͂����B(TvX, TvY, TvZ)�ɂ��ĉ����B�t�s����|���ċ��߂�Ηǂ��B
                //
                //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
                // | TvX TvY TvZ | = | MvX MvY MvZ | | b_mat_21 b_mat_22 b_mat_23 |
                //                                   | b_mat_31 b_mat_32 b_mat_33 |
                //

                //MvX MvY MvZ �����߂�
                int MvX,MvY,MvZ;
                if (RND(1, 60) != 1) {
                    //�ʏ�̎��@��_�������x�N�g��
                    GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                    MvX = pTargetActor->_X - _X; //�����ł� _X, _Y, _Z �͐�΍��W�ł��邱�Ƃ��|�C���g
                    MvY = (pTargetActor->_Y + PX_C(50)) - _Y; //���@�̂����_��
                    MvZ = pTargetActor->_Z - _Z;
                } else {
                    //���܁`�ɋt������ڕW�ɂ��āA�G��ɓ��������v����
                    GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                    MvX = _X - pTargetActor->_X;
                    MvY = _Y - pTargetActor->_Y;
                    MvZ = _Z - pTargetActor->_Z;
                }
                //�t�s��擾
                D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
                //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
                int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
                int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
                int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
                //�������������V�[�N�G���X�J�n
                angle angRz_Target, angRy_Target;
                UTIL::getRzRyAng(TvX, TvY, TvZ,
                                 angRz_Target, angRy_Target);
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
                _pKurokoA->execTurnFaceAngSequence(
                                angRz_Target, angRy_Target,
                                aiming_ang_velo_, aiming_ang_velo_*0.05,
                                TURN_CLOSE_TO, false);
            }
            if (_pKurokoA->isRunnigTurnMvAngSequence()) {
                // �ҋ@
            } else {
                _pProg->change(PROG_NOTHING);
            }
            break;
        }

        default :
            break;
    }

    //�����Ӂ�
    //�EGgafDxKurokoA(_pKurokoA)�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDxKurokoA(_pKurokoA)�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    _pKurokoA->behave();
    //    changeGeoFinal();
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();
    //_pScaler->behave();
    if (_pActor_Base) {
        setAlpha(((GgafDxDrawableActor*)_pActor_Base)->getAlpha());
    }
}

void EnemyHermioneArm::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }
}


void EnemyHermioneArm::onInactive() {
    sayonara();
}

void EnemyHermioneArm::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if ( prm_no == EVENT_HERMIONE_SAYONARA) {
        //�{�̔j��
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);//�����G�t�F
        sayonara();
    }
    if ( prm_no == EVENT_HERMIONE_ENTRY_DONE) {
        setHitAble(true);
        _pProg->change(PROG_NOTHING);
    }


}

EnemyHermioneArm::~EnemyHermioneArm() {

}
