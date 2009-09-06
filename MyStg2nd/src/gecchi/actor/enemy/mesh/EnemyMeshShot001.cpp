#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "vic2") {
    _class_name = "EnemyMeshShot001";

    inactivateTree();

    /** 出現時の初速 */
    _iMoveVelocity_1st = 10000;
    /** 出現時の加速度（負で遅くなる） */
    _iMoveAcceleration_1st = -150;
    /** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
    _dwFrame_TurnBegin = 50;
    /** 移動速度上限 */
    _iMoveVelocity_Top = 30000;
    /** 最低保証移動速度 */
    _iMoveVelocity_Bottom = 0;
    /** 方向転換に費やすことができるフレーム数 */
    _dwFrameInterval_Turn = 100;
    /** 方向転換中の角速度アングル値 */
    _angVelocity_Turn = 5000;
    /** 方向転換を開始（_dwFrame_TurnBegin）から再設定される加速度 */
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
}

void EnemyMeshShot001::processBehavior() {
    if (onChangeToActive()) {
        //出現時
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
        //方向転換開始
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
            _pMover->setTargetRyMoveAngle(angRy_Target);
            _pMover->setTargetRzMoveAngle(angRz_Target);

            _pMover->setMoveAcceleration(_iMoveAcceleration_2nd);
        }

        //方向転換終了
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin + _dwFrameInterval_Turn) {
            _pMover->setRzMoveAngleVelocity(0);
            _pMover->setRyMoveAngleVelocity(0);
            _pMover->_move_angle_ry_target_flg = false;
            _pMover->_move_angle_rz_target_flg = false;
        }

    }

    //addNextAnimationFrame();
    //座標に反映
    _pMover->behave();

}

void EnemyMeshShot001::processJudgement() {
    if (wasGone()) {
        inactivateTree();
        //adios();
    }
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("EnemyMeshShot001ヒットしました。("<<_X<<","<<_Y<<")");
    //adios();
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
