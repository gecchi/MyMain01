#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyHermioneArmBody::EnemyHermioneArmBody(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "HermioneArmBody", STATUS(EnemyHermioneArmBody)) {
    _class_name = "EnemyHermioneArmBody";
    _pActor_Base = NULL;
    aim_ang_velo_ = 0;
    aim_movable_limit_ang_ = 0;

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    useProgress(10);
}

void EnemyHermioneArmBody::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyHermioneArmBody::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}

void EnemyHermioneArmBody::onActive() {
    _pStatus->reset();
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->set(PROG_INIT);
}

void EnemyHermioneArmBody::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_AIMING);
            break;
        }
        case PROG_AIMING: {
            if (_pProg->hasJustChanged() ) {
                //���@�֕�����������
                //�l�����F���[�J�����W�n�ŗ\�߂ǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
                //
                //���@�ւ̌������߂̕ϊ��O��Ԃł̃^�[�Q�b�g�ʒu��(TvX, TvY, TvZ) �Ƃ����A
                //�u�y��܂Łv�̍s��̐ρi_pActor_Base->_matWorldRotMv) �� b_mat_xx �Ƃ���B
                //���݂̍ŏI���W���玩�@�ւ̌����̃x�N�g�����A(MvX, MvY, MvZ) �Ƃ���ƁA
                //
                //                | b_mat_11 b_mat_12 b_mat_13 |
                //| TvX TvY TvZ | | b_mat_21 b_mat_22 b_mat_23 | = | MvX MvY MvZ |
                //                | b_mat_31 b_mat_32 b_mat_33 |
                //
                //�ƂȂ�B���[�J�����W��(TvX, TvY, TvZ) �̕�����������ƁA
                //�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ�B
                //�t�s����|����(TvX, TvY, TvZ) �����߂�Ηǂ�
                //
                //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
                // | TvX TvY TvZ | = | MvX MvY MvZ | | b_mat_21 b_mat_22 b_mat_23 |
                //                                   | b_mat_31 b_mat_32 b_mat_33 |
                //

                //MvX MvY MvZ �����߂�
                MyShip* pMyShip = P_MYSHIP;
                int MvX = pMyShip->_X - _X; //�����ł� _X, _Y, _Z �͐�΍��W�ł��邱�Ƃ��|�C���g
                int MvY = pMyShip->_Y - _Y;
                int MvZ = pMyShip->_Z - _Z;
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
                if (aim_movable_limit_ang_ <= angRz_Target && angRz_Target <= D180ANG) {
                    angRz_Target = aim_movable_limit_ang_;
                } else if (D180ANG <= angRz_Target && angRz_Target <= D360ANG - aim_movable_limit_ang_) {
                    angRz_Target = D360ANG - aim_movable_limit_ang_;
                }
                if (aim_movable_limit_ang_ <= angRy_Target && angRy_Target <= D180ANG) {
                    angRy_Target = aim_movable_limit_ang_;
                } else if (D180ANG <= angRy_Target && angRy_Target <= D360ANG - aim_movable_limit_ang_) {
                    angRy_Target = D360ANG - aim_movable_limit_ang_;
                }
                _pKurokoA->execTurnMvAngSequence(angRz_Target, angRy_Target,
                                                 aim_ang_velo_, 0,
                                                 TURN_CLOSE_TO);

            }
            if (_pKurokoA->isRunnigTurnMvAngSequence()) {
                // �ҋ@
            } else {
                _pProg->change(PROG_NOTHING);
            }
            break;
        }
        case PROG_NOTHING: {
            _pProg->change(PROG_AIMING);
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

}

void EnemyHermioneArmBody::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveInTheTree()) {
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }
}

void EnemyHermioneArmBody::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //��������
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTxer->play3D(SE_EXPLOSION);
//
//        //���@���Ɍ�����ď��ł̏ꍇ�A
//        if (pOther->getKind() & KIND_MY) {
//            //�A�C�e���o��
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //��j��
//        effectFlush(2); //�t���b�V��
//        _pSeTxer->play3D(SE_DAMAGED);
//    }
}

void EnemyHermioneArmBody::onInactive() {
    sayonara();
}

EnemyHermioneArmBody::~EnemyHermioneArmBody() {
    
}
