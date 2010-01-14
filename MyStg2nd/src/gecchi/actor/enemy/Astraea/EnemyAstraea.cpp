#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMorphMeshActor(prm_name, "4/8box") {
    MyStgUtil::resetEnemyAstraeaStatus(this);

    //レーザーストック
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 20;
    _shot_interval = 120;
    _angveloTurn = 3000;

    _papapLaserChipDispatcher = NEW LaserChipDispatcher**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipDispatcher[i] = NEW LaserChipDispatcher*[_laser_way];
    }
    _paWayRz = NEW angle[_laser_way];
    _paWayRy = NEW angle[_laser_way];
    EnemyAstraeaLaserChip001* pChip;

    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipDispatcher[i][j] = NEW LaserChipDispatcher("RotLaser");
            for (int k = 0; k < _laser_length*2; k++) { //_laser_length の２倍分ストック
                stringstream name;
                name <<  getName() << "'s EnemyAstraeaLaserChip001["<<i<<"]["<<j<<"]-"<<k<<"";
                pChip = NEW EnemyAstraeaLaserChip001(name.str().c_str());
                pChip->inactivateImmediately();
                _papapLaserChipDispatcher[i][j]->addSubLast(pChip);
            }
            addSubGroup(_papapLaserChipDispatcher[i][j]); //仮所属
        }
    }
    setTechnique("DestBlendOne");
    useSe1("yume_Sbend", pWORLD->_frame_of_active); //レーザー発射
    useSe2("bomb1");     //爆発
}

void EnemyAstraea::initialize() {
    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 1, 1, 1);
    _pMover->setMoveVelocity(0);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
//    for (int i = 0; i < _laser_way; i++) {
//        for (int j = 0; j < _laser_way; j++) {
//            getLordActor()->addSubGroup(KIND_ENEMY_SHOT_NOMAL, _papapLaserChipDispatcher[i][j]->extract()); //本所属
//        }
//    }
}


void EnemyAstraea::onActive() {
    MyStgUtil::resetEnemyAstraeaStatus(this);
}

void EnemyAstraea::processBehavior() {
    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->loopTriangleWave(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAccelerationStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAccelerationStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->loopTriangleWave(3, 20, 13, 2);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmediately(3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->loopTriangleWave(4, 60, 3, 20);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmediately(4);
//    }
//    _pMorpher->behave();

    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pMorpher->intoTargetLinerUntil(1, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 1.0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    }
    _pMorpher->behave();
    /////////////モーフテスト////////////////


    _X = _X - 5000;
    if (_frame_of_active % _shot_interval == 0) {

        _pMover->setStopTarget_RzRyMoveAngle(GameGlobal::_pMyShip);
        _pMover->setRzMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getRzMoveAngleDistance(_pMover->_angTargetRzMove,TURN_CLOSE_TO))
                    );
        _pMover->setRyMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getRyMoveAngleDistance(_pMover->_angTargetRyMove,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pMover->behave();

    if (_pMover->_angveloRzMove == 0 && _pMover->_angveloRyMove == 0 && _cnt_laserchip < _laser_length) {

        static EnemyAstraeaLaserChip001* pLaserChip;

        angle angClearance = 150000;//開き具合

        GgafDx9Util::getWayAngle2D(_RY, _laser_way, angClearance, _paWayRy);
        GgafDx9Util::getWayAngle2D(_RZ, _laser_way, angClearance, _paWayRz);

        for (int i = 0; i < _laser_way; i++) {

            for (int j = 0; j < _laser_way; j++) {
                if (i == 0 && j == 0) {
                    playSe1(); //発射音
                }
                pLaserChip = (EnemyAstraeaLaserChip001*)_papapLaserChipDispatcher[i][j]->employ();
                if (pLaserChip != NULL) {
                    pLaserChip->activate();
//                    _TRACE_("Dispatcher employ()!!"<<(pLaserChip->getName())<<"/_is_active_flg_in_next_frame="<<_is_active_flg_in_next_frame<<
//                                                                              "/_on_change_to_active_flg="<<_on_change_to_active_flg<<
//                                                                              "/_on_change_to_inactive_flg="<<_on_change_to_inactive_flg<<
//                                                                              "/_is_active_flg="<<_is_active_flg);
                    pLaserChip->setGeometry(this);
                    pLaserChip->_pMover->setRzRyMoveAngle(_paWayRz[i], _paWayRy[j]);
                    pLaserChip->_pMover->_angFace[AXIS_Z] = _paWayRz[i];
                    pLaserChip->_pMover->_angFace[AXIS_Y] = _paWayRy[j];
//                    //とりあえずまっすぐ飛ばす、しかし、ターゲットは保存したいのでここで角速度０でたーげっと。
//                    pLaserChip->_pMover->executeTagettingMoveAngleSequence(GameGlobal::_pMyShip,
//                                                               0, TURN_CLOSE_TO);

                    pLaserChip->_pMover->behave();

                }
            }
        }
        _cnt_laserchip++;
    }

}

void EnemyAstraea::processJudgement() {
    if (isOutOfGameSpace()) {

        //レーザーは遅れて開放させるように、動きを継続させるため移動
        GgafGroupActor* pHead = getSubGroupActor(KIND_ENEMY_SHOT_NOMAL);
        pHead->adios(60 * 5);//解放予約
        getLordActor()->addSubLast(pHead->extract());

        adios();
//        for (int i = 0; i < _laser_way; i++) {
//            for (int j = 0; j < _laser_way; j++) {
//                if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
//                    _papapLaserChipDispatcher[i][j]->adios(60 * 5);
//                }
//            }
//        }
    }
}

void EnemyAstraea::processOnHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒットエフェクト
    if (MyStgUtil::calEnemyStamina(this, pOther) <= 0) {

        _SCORE_ += _pStatus->get(STAT_AddScorePoint);
        _RANK_  += _pStatus->get(STAT_AddRankPoint);
        playSe2();
        inactivate();
        //レーザーは遅れて開放させるように、動きを継続させるため移動
        GgafGroupActor* pHead = getSubGroupActor(KIND_ENEMY_SHOT_NOMAL);//解放予約
        pHead->adios(60 * 5);
        adios(); //さよなら
        //消滅エフェクト
    } else {

    }



//    GgafDx9GeometricActor* pOtherActor = (GgafDx9GeometricActor*)prm_pOtherActor;
//    setBumpable(false);
//    playSe2();
//    if (pOtherActor->getGroupActor()->_kind & KIND_MY) {
//        GameGlobal::_dwScore += _pStgChecker->_iScorePoint;
//    }
//    _TRACE_(" EnemyAstraea::EnemyAstraea::processOnHit()  "<<getName()<<" "<<_frame_of_active);
//
//    //レーザーは遅れて開放させるように、動きを継続させるため移動
//    GgafGroupActor* pHead = getSubGroupActor(KIND_ENEMY_SHOT_NOMAL);//解放予約
//    pHead->adios(60 * 5);
//    getLordActor()->addSubLast(pHead->extract());
//
//    adios(); //さよなら

//    for (int i = 0; i < _laser_way; i++) {
//        for (int j = 0; j < _laser_way; j++) {
//            if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
//                _papapLaserChipDispatcher[i][j]->adios(60 * 5);
//            }
//        }
//    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
}

int EnemyAstraea::isOutOfGameSpace() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 300000) {
        return true;
    } else {
        return false;
    }
}

EnemyAstraea::~EnemyAstraea() {
    DELETEARR_IMPOSSIBLE_NULL(_paWayRz);
    DELETEARR_IMPOSSIBLE_NULL(_paWayRy);
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher);


}
