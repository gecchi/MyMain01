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
                       : DefaultMorphMeshActor(prm_name, "1/Vesta") {
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
    _pDpcon = (DispatcherConnection*)(P_GOD->_pDispatcherManager->getConnection("DpCon_Shot004"));

    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "explos3", GgafRepeatSeq::nextVal("CH_explos3"));
    setAlpha(1.0);
}

void EnemyVesta::onCreateModel() {
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyVesta::initialize() {
    setHitAble(true);
    //_pKuroko->setRzMvAngVelo(1000);
    //_pKuroko->setRyMvAngVelo(500);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_VESTA_HATCH_OPENED, 0.0f);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    _pDispatcher_Fired = _pDpcon->refer();
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
    //_X, _Y, _Z, _RX, _RY, _RZ �ɂ��ĂQ�̍��W�n�Z�b�g��؂�ւ����K�v�Ȏd�l�ł��B
    //���ꂼ�ꃍ�[�J�����W�A�ŏI�i��΁j���W�ƌĂԂ��Ƃɂ��܂��B
    //�E�ŏI�i��΁j���W �E�E�E ���ʂ̃��[���h���W�n�̎��ł��B
    //�E���[�J�����W     �E�E�E �e�A�N�^�[�̊�_(0,0,0)����̑��ΓI�ȍ��W�n���Ӗ����܂��B
    //                          ���W�v�Z�͂�����ōs���ĉ������B
    //�����j��
    //  �@���W�v�Z�͎�Ƀ��[�J�����W�n�̌v�Z�ł���BGgafDx9Kuroko �Ń��[�J�����W�n�̑�����s�����ƂƂ���B
    //    �������A�W���ؓo�^��A�����蔻���A�^�[�Q�b�g���W�ȂǁA���̃I�u�W�F�N�g���烏�[���h���W���Q�Ƃ��邱�Ƃ��������߁B
    //    ��{�I��processBehavior()�J�n���� �ŏI�i��΁j���W�n(changeGeoFinal())�̏�ԂƂ���B
    //  �AprocessBehavior()���ŕK�v�ɉ����� changeGeoLocal() �� _X, _Y, _Z, _RX, _RY, _RZ �̐؂�ւ����s�����W�v�Z���s���B
    //  �B�A�� processBehavior() �𔲂���ۂɂ͕K���ŏI���W(changeGeoFinal())�̏�Ԃɖ߂��Ă������B
    //  �C�I�u�W�F�N�g���̂̃��[���h�ϊ��s��́A���[�J�����W�n�̍s��ςŕϊ��s�񂪍쐬�����B

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
    //�E_X, _Y, _Z    �E�E�E ���t���[�� GgafDx9GeometricActor::processSettlementBehavior() �Ōv�Z���ꎩ���X�V����Ă܂��B
    //                       processBehavior() �� changeGeoFinal() ���s���ƁA�P�t���[���O��_X, _Y, _Z�ɐ؂�ւ�鎖�ɂȂ�܂��B
    //                       _X, _Y, _Z �͎Q�Ɛ�p�B�l�������Ă��Ӗ����L��܂���
    //�E_RX, _RY, _RZ �E�E�E ���t���[�� GgafDx9GeometricActor::processSettlementBehavior() �����������܂���I
    //                       changeGeoFinal(); �����s���Ă��A_RX, _RY, _RZ �͈ȑO�̍ŏI�i��΁j���W�n�̒l��
    //                       ������ςȂ��ŕω����܂���B
    //                       ���̃I�u�W�F�N�g����A�{�[���ɂ�����A�N�^�[���Q�Ƃ���Ƃ��A_RX, _RY, _RZ�͑S���M�p�ł��܂���B

    //�����Ӂ�
    //�EGgafDx9Kuroko(_pKuroko)�� behave() �ȊO���\�b�h�́A��Ƀ��[�J�����W�̑���Ƃ���B
    //  behave()�ȊO���\�b�h�͎��ۂɍ��W�v�Z���Ă���킯�ł͂Ȃ��̂ŁA
    //  changeGeoFinal()���AchangeGeoLocal()���Ɋ֌W�Ȃ��A�Ăяo���\�B
    //�EGgafDx9Kuroko(_pKuroko)�� behave() ���\�b�h�͍��W���P�t���[����̏�Ԃɂ���v�Z���s���B
    //  ���������āA���̂悤�� ���[�J�����W��(changeGeoLocal()��)�ŌĂяo�����Ƃ���B
    //    changeGeoLocal();
    //    _pKuroko->behave();
    //    changeGeoFinal();
    //TODO:���݊��������ƂȂ����B

    switch (_iMovePatternNo) {
        case VESTA_HATCH_CLOSED:
            if (getActivePartFrame() == _frame_of_moment_nextopen-(_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                1.0f, _frame_of_morph_interval);
            }
            if (getActivePartFrame() == _frame_of_moment_nextopen) {
                _frame_of_moment_nextclose = getActivePartFrame() + _frame_of_close_interval;
                _iMovePatternNo = VESTA_HATCH_OPENED;
            }
            break;
        case VESTA_HATCH_OPENED:
            if (getActivePartFrame() == _frame_of_moment_nextclose - (_frame_of_morph_interval/2)) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_VESTA_HATCH_OPENED,
                                                0.0f, _frame_of_morph_interval);
            }
            if (getActivePartFrame() == _frame_of_moment_nextclose) {
                _frame_of_moment_nextopen = getActivePartFrame() + _frame_of_open_interval;
                _iMovePatternNo = VESTA_HATCH_CLOSED;
            }
        default :
            break;
    }
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�I�[�v�����G�o��
    if (_iMovePatternNo == VESTA_HATCH_OPENED) {
        int openningFrame = getActivePartFrame() - _frame_of_moment_nextopen; //�J���Ă���̃t���[�����B
        //_frame_of_moment_nextopen�́A�����̏����̎��_�ł͒��߂ŃI�[�v�������t���[���ƂȂ�B
        if (openningFrame % (int)(25-_RANK_*5) == 0) {
            if (_pDispatcher_Fired) {
                GgafDx9DrawableActor* pActor = (GgafDx9DrawableActor*)_pDispatcher_Fired->employ();
                if (pActor) {
                    pActor->locateAs(this);
                    pActor->_pKuroko->relateRzRyFaceAngToMvAng(true);
                    //�����݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾���遄
                    //�����x�N�g���̓��[���h�ϊ��s��̐ρi_matWorldRotMv)�ŕϊ�����A���݂̍ŏI�I�Ȍ����Ɍ����B
                    //���̕����x�N�g����(_Xorg,_Yorg,_Zorg)�A
                    //���[���h�ϊ��s��̉�]�����̐ρi_matWorldRotMv)�̐����� mat_xx�A
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
                                            Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾�I
                    pActor->_pKuroko->setRzRyMvAng(Rz, Ry); //RzRy��Mover�ɐݒ�
                    pActor->reset();
                    pActor->activate();
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
        D3DXMATRIX* pBaseInvMatRM = _pActor_Base->gatInvMatWorldRotMv();
        //���[�J�����W�ł̃^�[�Q�b�g�ƂȂ�����x�N�g���v�Z
        int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
        int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
        int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
        //�������������V�[�N�G���X�J�n
        angle angRz_Target, angRy_Target;
        GgafDx9Util::getRzRyAng(TvX, TvY, TvZ,
                                angRz_Target, angRy_Target);
        _pKuroko->orderTagettingMvAngSequence(angRz_Target, angRy_Target,
                                           1000, 0,
                                           TURN_CLOSE_TO);
    }

    _pScaler->behave();
    _pMorpher->behave();
    //_pSeTransmitter->behave();

    //_pKuroko�̌v�Z�̓��[�J���ōs��
    changeGeoLocal();
    _pKuroko->behave();
    changeGeoFinal();

}

void EnemyVesta::processJudgement() {
    if (_pActor_Base != NULL && _pActor_Base->isActiveActor()) {
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
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��

    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();

    if (pExplo001) {
        pExplo001->activate();
        pExplo001->locateAs(this);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeTransmitter->play3D(0);
        sayonara();
    }
}

void EnemyVesta::onInactive() {
    sayonara();
}

EnemyVesta::~EnemyVesta() {
    _pDpcon->close();
}
