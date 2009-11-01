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
    _dwFrameInterval_Turn = 100;
    /** �����]�����̊p���x�A���O���l */
    _angVelocity_Turn = 5000;
    /** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
    _iMoveAcceleration_2nd = 300;

    _frame_on_change_to_active_flg = 0;
}

void EnemyMeshShot001::initialize() {
    _pMover->setVxMoveVelocityRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
    _pMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    setBumpable(true);
    useSe("bomb1");
}

void EnemyMeshShot001::processBehavior() {
    if (onChangeToActive()) {
        //�o����
        _pMover->setMoveVelocity(_iMoveVelocity_1st);
        _pMover->setMoveAcceleration(_iMoveAcceleration_1st);

        _frame_on_change_to_active_flg = 0;
        setBumpable(true);
    } else {

        //		_pMover->setMoveAngle(
        //				GameGlobal::_pMyShip->_X,
        //				GameGlobal::_pMyShip->_Y,
        //				GameGlobal::_pMyShip->_Z
        //				);

        //		angle angRz_Target;
        //		angle angRy_Target;
        //		double dummy1,dummy2,dummy3;
        //		GgafDx9Util::getRotAngleZY(
        //				GameGlobal::_pMyShip->_X - _X,
        //				GameGlobal::_pMyShip->_Y - _Y,
        //				GameGlobal::_pMyShip->_Z - _Z,
        //				angRz_Target,
        //				angRy_Target
        //				);
        //		_pMover->setRzMoveAngle(angRz_Target);
        //		_pMover->setRyMoveAngle(angRy_Target);

        _frame_on_change_to_active_flg++;
        //�����]���J�n
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin) {
            static angle angRz_Target;
            static angle angRy_Target;
            GgafDx9Util::getRotAngleZY(GameGlobal::_pMyShip->_X - _X, GameGlobal::_pMyShip->_Y - _Y,
                                       GameGlobal::_pMyShip->_Z - _Z, angRz_Target, angRy_Target);
            if (_pMover->getDifferenceFromRzMoveAngleTo(angRz_Target, TURN_CLOSE_TO) > 0) {
                _pMover->setRzMoveAngleVelocity(_angVelocity_Turn);
            } else {
                _pMover->setRzMoveAngleVelocity(-1 * _angVelocity_Turn);
            }
            if (_pMover->getDifferenceFromRyMoveAngleTo(angRy_Target, TURN_CLOSE_TO) > 0) {
                _pMover->setRyMoveAngleVelocity(_angVelocity_Turn);
            } else {
                _pMover->setRyMoveAngleVelocity(-1 * _angVelocity_Turn);
            }
            _pMover->setSuspendTargetRyMoveAngle(angRy_Target);
            _pMover->setSuspendTargetRzMoveAngle(angRz_Target);

            _pMover->setMoveAcceleration(_iMoveAcceleration_2nd);
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
    if (wasGone()) {
        inactivateTree();
        //adios();
    }
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("EnemyMeshShot001�q�b�g���܂����B("<<_X<<","<<_Y<<")");
    //adios();
    playSe();
    setBumpable(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activateTree();
    }
}

EnemyMeshShot001::~EnemyMeshShot001() {
}
