#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMorphMeshActor(prm_name, "4/8box") {
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);

    //レーザーストック
    _laser_way = 2;
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
                _papapLaserChipDispatcher[i][j]->addSubLast(pChip);
            }
            addSubGroup(_papapLaserChipDispatcher[i][j]); //仮所属
        }
    }
    useSe1("yume_Sbend", GgafRepeatSeq::getNext(5)); //レーザー発射(チャンネルは0,1,2,3,4,0,1,2,3,4 となる)
    useSe2("bomb1");     //爆発
}

void EnemyAstraea::initialize() {
    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pMover->setMvVelo(0);
    _pMover->relateRzRyFaceAngToMvAng(true);
//    for (int i = 0; i < _laser_way; i++) {
//        for (int j = 0; j < _laser_way; j++) {
//            getLordActor()->addSubGroup(KIND_ENEMY_SHOT_NOMAL, _papapLaserChipDispatcher[i][j]->becomeIndependent()); //本所属
//        }
//    }
}


void EnemyAstraea::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);
}

void EnemyAstraea::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->loopTriangleWave(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
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
    if (getBehaveingFrame() % _shot_interval == 0) {

        _pMover->setStopTarget_RzRyMvAng(GameGlobal::_pMyShip);
        _pMover->setRzMvAngVelo(
                        _angveloTurn*sgn(_pMover->getRzMvAngDistance(_pMover->_angTargetRzMv,TURN_CLOSE_TO))
                    );
        _pMover->setRyMvAngVelo(
                        _angveloTurn*sgn(_pMover->getRyMvAngDistance(_pMover->_angTargetRyMv,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pMover->behave();

    if (_pMover->_angveloRzMv == 0 && _pMover->_angveloRyMv == 0 && _cnt_laserchip < _laser_length) {

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
                    pLaserChip->_pMover->setRzRyMvAng(_paWayRz[i], _paWayRy[j]);
                    pLaserChip->_pMover->_angFace[AXIS_Z] = _paWayRz[i];
                    pLaserChip->_pMover->_angFace[AXIS_Y] = _paWayRy[j];
//                    //とりあえずまっすぐ飛ばす、しかし、ターゲットは保存したいのでここで角速度０でたーげっと。
//                    pLaserChip->_pMover->execTagettingMvAngSequence(GameGlobal::_pMyShip,
//                                                               0,0, TURN_CLOSE_TO);

                    pLaserChip->_pMover->behave();

                }
            }
        }
        _cnt_laserchip++;
    }

}

void EnemyAstraea::processJudgement() {
    if (isOutOfGameSpace()) {

        inactivate();
//        for (int i = 0; i < _laser_way; i++) {
//            for (int j = 0; j < _laser_way; j++) {
//                if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
//                    _papapLaserChipDispatcher[i][j]->sayonara(60 * 5);
//                }
//            }
//        }
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    setTechniqueTemporarily("Flush", 2); //フラッシュ
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        playSe2();
        inactivate(); //さよなら
        //消滅エフェクト
    } else {

    }



//    GgafDx9GeometricActor* pOtherActor = (GgafDx9GeometricActor*)prm_pOtherActor;
//    setHitAble(false);
//    playSe2();
//    if (pOtherActor->getGroupActor()->_kind & KIND_MY) {
//        GameGlobal::_dwScore += _pCollisionChecker->_iScorePoint;
//    }
//    _TRACE_(" EnemyAstraea::EnemyAstraea::onHit()  "<<getName()<<" "<<_frame_of_behaving);
//
//    //レーザーは遅れて開放させるように、動きを継続させるため移動
//    GgafGroupActor* pGroup = getSubGroupActor(KIND_ENEMY_SHOT_NOMAL);//解放予約
//    pGroup->sayonara(60 * 5);
//    getLordActor()->addSubLast(pGroup->becomeIndependent());
//
//    sayonara(); //さよなら

//    for (int i = 0; i < _laser_way; i++) {
//        for (int j = 0; j < _laser_way; j++) {
//            if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
//                _papapLaserChipDispatcher[i][j]->sayonara(60 * 5);
//            }
//        }
//    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
}


void EnemyAstraea::onInactive() {
    //レーザーは遅れて開放させるように、動きを継続させるため移動
    GgafGroupActor* pGroup = getSubGroupActor(_papapLaserChipDispatcher[0][0]->getKind()); //
    pGroup->sayonara(60 * 5);//解放予約
    getLordActor()->addSubLast(pGroup->becomeIndependent());
    sayonara();
}


bool EnemyAstraea::isOutOfGameSpace() {
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
