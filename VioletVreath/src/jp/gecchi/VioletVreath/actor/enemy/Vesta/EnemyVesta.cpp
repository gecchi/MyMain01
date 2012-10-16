#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_VESTA_HATCH_OPENED 1
#define VESTA_HATCH_CLOSED      0
#define VESTA_HATCH_OPENED      1

EnemyVesta::EnemyVesta(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Vesta", STATUS(EnemyVesta)) {
    _class_name = "EnemyVesta";
    _pActor_Base = NULL;
    iMovePatternNo_ = 0;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 4*60;
    frame_of_moment_nextopen_ = 0;
    frame_of_moment_nextclose_ = 0;
    frame_of_morph_interval_   = 60;

    pDepo_Fired_ = NULL;
    pDpcon_ = connectToDepositoryManager("DpCon_Atalante", NULL);

    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyVesta::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);

}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pKurokoA->setRzMvAngVelo(1000);
    //_pKurokoA->setRyMvAngVelo(500);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    pDepo_Fired_ = pDpcon_->fetch();
}

void EnemyVesta::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    is_open_hatch_ = false;
    iMovePatternNo_ = VESTA_HATCH_CLOSED;
    frame_of_moment_nextopen_ = 60;
}

void EnemyVesta::processBehavior() {
    //�{�[���ɂ�����A�N�^�[�̃���
    //_X, _Y, _Z, _RX, _RY, _RZ �ɂ��ĂQ�̍��W�n�Z�b�g��؂�ւ����K�v�Ȏd�l�ł��B
    //���ꂼ�ꃍ�[�J�����W�A�ŏI�i��΁j���W�ƌĂԂ��Ƃɂ��܂��B
    //�E�ŏI�i��΁j���W �E�E�E ���ʂ̃��[���h���W�n�̎��ł��B
    //�E���[�J�����W     �E�E�E �e�A�N�^�[�̊�_(0,0,0)����̑��ΓI�ȍ��W�n���Ӗ����܂��B
    //                          ���W�v�Z�͂�����ōs���ĉ������B
    //�����j��
    //  �@���W�v�Z�͎�Ƀ��[�J�����W�n�̌v�Z�ł���BGgafDxKurokoA �Ń��[�J�����W�n�̑�����s�����ƂƂ���B
    //    �������A�W���ؓo�^��A�����蔻���A�^�[�Q�b�g���W�ȂǁA���̃I�u�W�F�N�g���烏�[���h���W���Q�Ƃ��铙�A
    //    ��{��Ԃ͍ŏI�i��΁j���W�n�B
    //    processBehavior()�J�n���� �ŏI�i��΁j���W�n(changeGeoFinal())�̏�ԂƂȂ��Ă���B
    //  �AprocessBehavior()���ŕK�v�ɉ����� changeGeoLocal() �Ń����o�[ _X, _Y, _Z, _RX, _RY, _RZ �����[�J�����W�n��
    //    �؂�ւ��邱�Ƃ��\�B�ړ����̍��W�v�Z���s���B
    //  �B�A�� processBehavior() �𔲂���ۂɂ͕K���ŏI���W(changeGeoFinal())�̏�Ԃɖ߂��Ă������B
    //  �C�ŏI�i��΁j���W�ƁA���[�J�����W�݂͌��ɓƗ����A���͂��Ȃ����A
    //    �\�����̃��[���h�ϊ��s��쐬���A�s��ςō�������A�ŏI�I�ȕ\���ʒu�����肷��B

    //��changeGeoLocal(); ���s����
    //���[�J�����W�n�ɐؑւ��܂��B
    //�E_X, _Y, _Z     �E�E�E �́A���[�J�����W���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_X, _Y, _Z ��
    //                        ���[�J�����W�l�ɐ؂�ւ��܂��B
    //�E_RX, _RY, _RZ  �E�E�E �́A���[�J�����W�ł̎���]�l���Ӗ�����悤�ɂȂ�܂��B
    //                        changeGeoLocal(); �����s����Ǝ����I��_RX, _RY, _RZ��
    //                        ���[�J�����W����]�l�ɐ؂�ւ��܂��B

    //��changeGeoFinal(); ���s����
    //�ŏI�i��΁j���W�n�ɐ؂�ւ��܂��B
    //�E_X, _Y, _Z    �E�E�E ���t���[�� GgafDxGeometricActor::processSettlementBehavior() �Ōv�Z���ꎩ���X�V����Ă܂��B
    //                       processBehavior() �� changeGeoFinal() ���s���ƁA�P�t���[���O��_X, _Y, _Z�ɐ؂�ւ�鎖�ɂȂ�܂��B
    //                       _X, _Y, _Z �͎Q�Ɛ�p�B�l�������Ă��Ӗ����L��܂���
    //�E_RX, _RY, _RZ �E�E�E ���t���[�� GgafDxGeometricActor::processSettlementBehavior() �����������܂���I
    //                       changeGeoFinal(); �����s���Ă��A_RX, _RY, _RZ �͈ȑO�̍ŏI�i��΁j���W�n�̒l��
    //                       ������ςȂ��ŕω����܂���B
    //                       ���̃I�u�W�F�N�g����A�{�[���ɂ�����A�N�^�[���Q�Ƃ���Ƃ��A_RX, _RY, _RZ�͑S���M�p�ł��܂���B

    //�����Ӂ�
    //�EGgafDxKurokoA(_pKurokoA)�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDxKurokoA(_pKurokoA)�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    _pKurokoA->behave();
    //    changeGeoFinal();
    //TODO:���݊��������ƂȂ����B

    switch (iMovePatternNo_) {
        case VESTA_HATCH_CLOSED:
            if (getActivePartFrame() == frame_of_moment_nextopen_-(frame_of_morph_interval_/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }
            if (getActivePartFrame() == frame_of_moment_nextopen_) {
                frame_of_moment_nextclose_ = getActivePartFrame() + frame_of_close_interval_;
                iMovePatternNo_ = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getActivePartFrame() == frame_of_moment_nextclose_ - (frame_of_morph_interval_/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }
            if (getActivePartFrame() == frame_of_moment_nextclose_) {
                frame_of_moment_nextopen_ = getActivePartFrame() + frame_of_open_interval_;
                iMovePatternNo_ = VESTA_HATCH_CLOSED;
            }
            break;
        default :
            break;
    }
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�I�[�v�����G�o��
    if (iMovePatternNo_ == VESTA_HATCH_OPENED) {
        int openningFrame = getActivePartFrame() - frame_of_moment_nextopen_; //�J���Ă���̃t���[�����B
        //frame_of_moment_nextopen_�́A�����̏����̎��_�ł͒��߂ŃI�[�v�������t���[���ƂȂ�B
        if (openningFrame % (int)(RR_EnemyVesta_ShotInterval(_RANK_)) == 0) {
            if (pDepo_Fired_) {
                GgafDxDrawableActor* pActor = (GgafDxDrawableActor*)pDepo_Fired_->dispatch();
                if (pActor) {
                    pActor->locateWith(this);
                    pActor->_pKurokoA->relateFaceAngWithMvAng(true);
                    //�����݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���遄
                    //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
                    //���̕����x�N�g����(Xorg_,Yorg_,Zorg_)�A
                    //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
                    //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
                    //
                    //                      | mat_11 mat_12 mat_13 |
                    //| Xorg_ Yorg_ Zorg_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                    //                      | mat_31 mat_32 mat_33 |
                    //
                    //vX = Xorg_*mat_11 + Yorg_*mat_21 + Zorg_*mat_31
                    //vY = Xorg_*mat_12 + Yorg_*mat_22 + Zorg_*mat_32
                    //vZ = Xorg_*mat_13 + Yorg_*mat_23 + Zorg_*mat_33
                    //
                    //���Ă����ŁA���X���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�l�����
                    //
                    //vX = Xorg_*mat_11
                    //vY = Xorg_*mat_12
                    //vZ = Xorg_*mat_13
                    //
                    //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
                    //�ŏI�I�ȕ����x�N�g���́iXorg_*mat_11, Xorg_*mat_12, Xorg_*mat_13) �ł���B
                    angle Rz, Ry;
                    UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                            Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
                    pActor->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
                    pActor->reset();
                }
            }
        }
    }

    if (getActivePartFrame() % 10 == 0                   && 1 == 2) {
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
        int MvX = P_MYSHIP->_X - _X;
        int MvY = P_MYSHIP->_Y - _Y;
        int MvZ = P_MYSHIP->_Z - _Z;
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
        _pKurokoA->execTurnMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);
    }

    _pScaler->behave();
    _pMorpher->behave();
    //_pSeTxer->behave();

    //_pKurokoA�̌v�Z�̓��[�J���ōs��
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyVesta::processJudgement() {
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

void EnemyVesta::onHit(GgafActor* prm_pOtherActor) {
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

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    pDpcon_->close();
}
