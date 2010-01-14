#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "vic2") {
    _class_name = "EnemyMeshShot001";

    inactivateTree();

    /** �o�����̏��� */
    _iMoveVelocity_1st = 10000;
    /** �o�����̉����x�i���Œx���Ȃ�j */
    _iMoveAcceleration_1st = -150;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    _dwFrame_TurnBegin = 50;
    /** �ړ����x��� */
    _iMoveVelocity_Top = 30000;
    /** �Œ�ۏ؈ړ����x */
    _iMoveVelocity_Bottom = 0;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    _dwFrameInterval_Turn = 400;
    /** �����]�����̊p���x�A���O���l(���̒l) */
    _angVelocity_Turn = 7000;
    /** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
    _iMoveAcceleration_2nd = 100;

    _frame_on_change_to_active_flg = 0;
}

void EnemyMeshShot001::initialize() {
    _pMover->setVxMoveVeloRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    setBumpable(true);
    useSe1("bomb1");
}

void EnemyMeshShot001::processBehavior() {
    if (onChangeToActive()) {
        //�o����
        _pMover->setMoveVelocity(_iMoveVelocity_1st);
        _pMover->setMoveVeloAcceleration(_iMoveAcceleration_1st);

        _frame_on_change_to_active_flg = 0;
        setBumpable(true);
    } else {


        _frame_on_change_to_active_flg++;
        //�����]���J�n
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin) {

            _pMover->executeTagettingMoveAngleSequence(GameGlobal::_pMyShip, _angVelocity_Turn, TURN_CLOSE_TO);
            _pMover->setMoveVeloAcceleration(_iMoveAcceleration_2nd);
        }

        //�����]���I��
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin + _dwFrameInterval_Turn) {
            _pMover->setRzMoveAngleVelocity(0);
            _pMover->setRyMoveAngleVelocity(0);
            _pMover->_move_angle_ry_target_flg = false;
            _pMover->_move_angle_rz_target_flg = false;
        }

    }

    //addNextAnimationFrame();
    //���W�ɔ��f
    _pMover->behave();

}

void EnemyMeshShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
        //adios();
    }
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyMeshShot001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
    //adios();
    playSe1();
    setBumpable(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

EnemyMeshShot001::~EnemyMeshShot001() {
}
