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
    _dwFrameInterval_Turn = 400;
    /** 方向転換中の角速度アングル値(正の値) */
    _angVelocity_Turn = 7000;
    /** 方向転換を開始（_dwFrame_TurnBegin）から再設定される加速度 */
    _iMoveAcceleration_2nd = 100;

    _frame_on_change_to_active_flg = 0;
}

void EnemyMeshShot001::initialize() {
    _pMover->setVxMoveVeloRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    useSe1("bomb1");
}

void EnemyMeshShot001::processBehavior() {
    if (onChangeToActive()) {
        //出現時
        _pMover->setMoveVelocity(_iMoveVelocity_1st);
        _pMover->setMoveVeloAcceleration(_iMoveAcceleration_1st);

        _frame_on_change_to_active_flg = 0;
        setHitAble(true);
    } else {


        _frame_on_change_to_active_flg++;
        //方向転換開始
        if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin) {

            _pMover->executeTagettingMoveAngleSequence(GameGlobal::_pMyShip,
                                                       _angVelocity_Turn, 0,
                                                       TURN_CLOSE_TO);
            _pMover->setMoveVeloAcceleration(_iMoveAcceleration_2nd);
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
    if (isOutOfGameSpace()) {
        inactivateTree();
        //adios();
    }
}

void EnemyMeshShot001::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyMeshShot001ヒットしました。("<<_X<<","<<_Y<<")");
    //adios();
    playSe1();
    setHitAble(false);
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
