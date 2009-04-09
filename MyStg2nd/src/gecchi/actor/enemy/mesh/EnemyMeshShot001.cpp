#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMeshShot001::EnemyMeshShot001(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/vic2") {
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

    _dwFrame_switchedToActiveFlg = 0;
}

void EnemyMeshShot001::initialize() {
    _pGeoMover->setVxMoveVelocityRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_Flg = true;
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_Flg = true;

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    setBumpableAlone(true);
}

void EnemyMeshShot001::processBehavior() {
    if (switchedToActive()) {
        //出現時
        _pGeoMover->setMoveVelocity(_iMoveVelocity_1st);
        _pGeoMover->setMoveAcceleration(_iMoveAcceleration_1st);

        _dwFrame_switchedToActiveFlg = 0;
        setBumpableAlone(true);
    } else {

        //		_pGeoMover->setMoveAngle(
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
        //		_pGeoMover->setRzMoveAngle(angRz_Target);
        //		_pGeoMover->setRyMoveAngle(angRy_Target);

        _dwFrame_switchedToActiveFlg++;
        //方向転換開始
        if (_dwFrame_switchedToActiveFlg == _dwFrame_TurnBegin) {
            angle angRz_Target;
            angle angRy_Target;
            GgafDx9Util::getRotAngleZY(GameGlobal::_pMyShip->_X - _X, GameGlobal::_pMyShip->_Y - _Y,
                                       GameGlobal::_pMyShip->_Z - _Z, angRz_Target, angRy_Target);
            if (_pGeoMover->getDistanceFromRzMoveAngleTo(angRz_Target, TURN_CLOSE_TO) > 0) {
                _pGeoMover->setRzMoveAngleVelocity(_angVelocity_Turn);
            } else {
                _pGeoMover->setRzMoveAngleVelocity(-1 * _angVelocity_Turn);
            }
            if (_pGeoMover->getDistanceFromRyMoveAngleTo(angRy_Target, TURN_CLOSE_TO) > 0) {
                _pGeoMover->setRyMoveAngleVelocity(_angVelocity_Turn);
            } else {
                _pGeoMover->setRyMoveAngleVelocity(-1 * _angVelocity_Turn);
            }
            _pGeoMover->setAutoTargetRyMoveAngle(angRy_Target);
            _pGeoMover->setAutoTargetRzMoveAngle(angRz_Target);

            _pGeoMover->setMoveAcceleration(_iMoveAcceleration_2nd);
        }

        //方向転換終了
        if (_dwFrame_switchedToActiveFlg == _dwFrame_TurnBegin + _dwFrameInterval_Turn) {
            _pGeoMover->setRzMoveAngleVelocity(0);
            _pGeoMover->setRyMoveAngleVelocity(0);
            _pGeoMover->_auto_move_angle_ry_target_Flg = false;
            _pGeoMover->_auto_move_angle_rz_target_Flg = false;
        }

    }

    //addNextAnimationFrame();
    //座標に反映
    _pGeoMover->behave();

}

void EnemyMeshShot001::processJudgement() {
    if (isOffScreen()) {
        inactivateTree();
        //arigatou_sayounara();
    }
}

bool EnemyMeshShot001::isOffScreen() {
    if (_X < _X_OffScreenLeft) {
        return true;
    } else {
        if (_X > _X_OffScreenRight) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}

void EnemyMeshShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("EnemyMeshShot001ヒットしました。("<<_X<<","<<_Y<<")");
    //arigatou_sayounara();
    setBumpableAlone(false);
    inactivateTree();
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activateTree();
    }
}

EnemyMeshShot001::~EnemyMeshShot001() {
}
