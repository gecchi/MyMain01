#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCeresShot001::EnemyCeresShot001(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "16/vic2") {
    _class_name = "EnemyCeresShot001";
    MyStgUtil::resetEnemyCeresShot001Status(_pStatus);
    inactivateTree();

    /** 出現時の初速 */
    _iMoveVelocity_1st = 13000;
    /** 出現時の加速度（負で遅くなる） */
    _iMoveAcceleration_1st = -150;
    /** 自身が出現してから、時機の方向に方向転換を開始するフレーム */
    _dwFrame_TurnBegin = 60;
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

void EnemyCeresShot001::initialize() {
    _pMover->setVxMoveVeloRenge(_iMoveVelocity_Top, _iMoveVelocity_Bottom);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
    setBumpable(true);
    useSe1("break_glass01");
}

void EnemyCeresShot001::onActive() {
    MyStgUtil::resetEnemyCeresShot001Status(_pStatus);

    //出現時
    _pMover->setMoveVelocity(_iMoveVelocity_1st);
    _pMover->setMoveVeloAcceleration(_iMoveAcceleration_1st);

    _frame_on_change_to_active_flg = 0;
    setBumpable(true);
}

void EnemyCeresShot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    _frame_on_change_to_active_flg++;
    //方向転換開始
    if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin) {

        _pMover->executeTagettingMoveAngleSequence(GameGlobal::_pMyShip, _angVelocity_Turn, TURN_CLOSE_TO);
        _pMover->setMoveVeloAcceleration(_iMoveAcceleration_2nd);
    }

    //方向転換終了
    if (_frame_on_change_to_active_flg == _dwFrame_TurnBegin + _dwFrameInterval_Turn) {
        _pMover->setRzMoveAngleVelocity(0);
        _pMover->setRyMoveAngleVelocity(0);
        _pMover->_move_angle_ry_target_flg = false;
        _pMover->_move_angle_rz_target_flg = false;
    }

    //addNextAnimationFrame();
    //座標に反映
    _pMover->behave();

}

void EnemyCeresShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyCeresShot001::processOnHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここに消滅エフェクト
        playSe1();
        setBumpable(false);
        inactivate();
        EffectExplosion001* pExplo001 =
                (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
    }
}

void EnemyCeresShot001::onInactive() {
    //ディスパッチャに戻るだけなのでadios不要？
    //adios();
}

EnemyCeresShot001::~EnemyCeresShot001() {
}
