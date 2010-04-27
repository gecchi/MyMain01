#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define MORPHTARGET_VESTA_HATCH_OPENED 1
#define VESTA_HATCH_CLOSED      0
#define VESTA_HATCH_OPENED      1

EnemyVesta::EnemyVesta(const char* prm_name)
                       : DefaultMorphMeshActor(prm_name, "1/hachi") {
    _class_name = "EnemyVesta";
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _pActor_Base = NULL;
    _iMovePatternNo = 0;
    _is_open_hatch = false;
    _frame_of_open_interval  = 3*60;
    _frame_of_close_interval = 4*60;
    _frame_of_moment_nextopen = 0;
    _frame_of_moment_nextclose = 0;
    _frame_of_morph_interval   = 60;

    _pDispatcher_Fired = NULL;
    _pDpcon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot004");

    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));

}

void EnemyVesta::onCreateModel() {
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pMover->setRzMvAngVelo(1000);
    //_pMover->setRyMvAngVelo(500);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pScaler->setScale(1000);
    _pDispatcher_Fired = _pDpcon->view();
}

void EnemyVesta::onActive() {
    MyStgUtil::resetEnemyVestaStatus(_pStatus);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _is_open_hatch = false;
    _iMovePatternNo = VESTA_HATCH_CLOSED;
    _frame_of_moment_nextopen = 60;
}

void EnemyVesta::processBehavior() {
    //�{�[���ɂ�����A�N�^�[�̃���
    //��chengeGeoFinal(); ����
    //�E_X, _Y, _Z �͍ŏI�I�ȃ��[���h���W
    //�E_RX, _RY, _RZ �͕s��B
    //�EGgafDx9GeometryMover �̒l�͏�Ƀ��[�J�����W�Ȃ̂�behave()���Ăяo���Ă͂����Ȃ��B
    //��RX,RY,RZ �͍ŏI�I�ȃ��[���h��]�l�E�E�E�ɂ��悤�Ƃ������A
    //���t���[���v�Z����͖̂��ʂł��邽�ߐݒ肳��Ă��Ȃ��B
    //�K�v�ȂƂ��ɋ��߂邱�ƂƂ���B
    //��chengeGeoLocal(); ����
    //�E_X, _Y, _Z �̓��[�J�����W
    //�E_RX, _RY, _RZ  �̓��[�J����]�l
    //�EGgafDx9GeometryMover �̒l�̓��[�J�����W
    //
    //��{�I��chengeGeoFinal()�̏�Ԃł���B
    //TODO:���݊��������ƂȂ����B

    switch (_iMovePatternNo) {
        case VESTA_HATCH_CLOSED:
            if (getPartFrame() == _frame_of_moment_nextopen-(_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, _frame_of_morph_interval);
            }
            if (getPartFrame() == _frame_of_moment_nextopen) {
                _frame_of_moment_nextclose = getPartFrame() + _frame_of_close_interval;
                _iMovePatternNo = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getPartFrame() == _frame_of_moment_nextclose - (_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, _frame_of_morph_interval);
            }
            if (getPartFrame() == _frame_of_moment_nextclose) {
                _frame_of_moment_nextopen = getPartFrame() + _frame_of_open_interval;
                _iMovePatternNo = VESTA_HATCH_CLOSED;
            }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == VESTA_HATCH_OPENED) {
        int openningFrame = getPartFrame() - _frame_of_moment_nextopen; //�J���Ă���̃t���[�����B
        //_frame_of_moment_nextopen�́A�����̏����̎��_�ł͒��߂ŃI�[�v�������t���[���ƂȂ�B
        if (openningFrame % (int)(20/_RANK_+5) == 0) {
            if (_pDispatcher_Fired) {
                GgafDx9DrawableActor* pActor = (GgafDx9DrawableActor*)_pDispatcher_Fired->employ();
                if (pActor) {
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    //�����݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���遄
                    //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
                    //���̕����x�N�g����(_Xorg,_Yorg,_Zorg)�A
                    //���[���h�ϊ��s��̐ρi_matWorldRotMv)�̐����� mat_xx�A
                    //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
                    //
                    //                      | mat_11 mat_12 mat_13 |
                    //| _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                    //                      | mat_31 mat_32 mat_33 |
                    //
                    //vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                    //vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                    //vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                    //
                    //���Ă����ŁA���X���O���̒P�ʕ����x�N�g��(1,0,0)�̏ꍇ�͂ǂ��Ȃ邩�l�����
                    //
                    //vX = _Xorg*mat_11
                    //vY = _Xorg*mat_12
                    //vZ = _Xorg*mat_13
                    //
                    //�ƂȂ�B�{�A�v���ł́A���f���͑S��(1,0,0)��O���Ƃ��Ă��邽��
                    //�ŏI�I�ȕ����x�N�g���́i_Xorg*mat_11, _Xorg*mat_12, _Xorg*mat_13) �ł���B
                    angle Rz, Ry;
                    GgafDx9Util::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                            Rz, Ry);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry);
                    pActor->activate();
                }
            }
        }
    }

    if (getPartFrame() % 10 == 0) {
        //���@�֕�����������
        //�l�����F���[�J���łǂ̕����Ɍ����Ă����΁A�ŏI�I�Ɏ��@�Ɍ������ƂɂȂ邩�����߂�
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
        int MvX = pMYSHIP->_X - _X;
        int MvY = pMYSHIP->_Y - _Y;
        int MvZ = pMYSHIP->_Z - _Z;
        //�t�s��擾
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->gatInvMatWorldRotMv();
        //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
        int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
        int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
        int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
        //�������������V�[�N�G���X�J�n
        angle angRz_Target, angRy_Target;
        GgafDx9Util::getRzRyAng(TvX, TvY, TvZ,
                                angRz_Target, angRy_Target);
        _pMover->execTagettingMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);
    }

    _pScaler->behave();
    _pMorpher->behave();
    //_pSeReflector->behave();

    //_pMover�̌v�Z�̓��[�J���ōs��
    chengeGeoLocal();
    _pMover->behave();
    chengeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActive()) {
//        (*(_pActor_Base->_pFunc_calcWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //�y�䂪�Ȃ���Ύ���������
        inactivate();
    }


//    if (isOutOfGameSpace()) {
//        inactivate();
//    }
}

void EnemyVesta::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
//    playSe3D2();
//    if (pExplo001 != NULL) {
//        pExplo001->activate();
//        pExplo001->setGeometry(this);
//    }
//
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        inactivate();
//    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    _pDpcon->close();
}
