#include "MyBunshinController.h"

#include "MyBunshinBase.h"
#include "MyBunshin.h"
#include "MyBunshinShot001.h"
#include "MyBunshinSnipeShot001.h"
#include "MyBunshinWateringLaserChip001.h"
#include "MyBunshinStraightLaserChip001.h"


#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

//enum {
//    SE_FIRE_LASER  ,
//    SE_FIRE_SHOT   ,
//    SE_FIRE_TORPEDO,
//};

MyBunshinController::MyBunshinController(const char* prm_name, MyBunshinBase* prm_pBase) :
        GgafLib::DefaultGeometricActor(prm_name, nullptr) {

    _class_name = "MyBunshinController";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActorでFKベースになるために必要
    pBase_ = prm_pBase;

////////////
    std::string bunshin_name = "Bunshin";
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this, prm_pBase);
    this->appendGroupChildAsFk(pBunshin_,
                          0, 0, 0,
                          D0ANG, D0ANG, D0ANG);
////////////
//    _laser_kind = LASER_KOANYA;

//    //自弾ストック
//    pDepo_MyBunshinShot_ = NEW GgafCore::ActorDepository("Depo_MyBunshinShot");
//    for (int i = 0; i < 40; i++) {
//        std::string name = std::string(getName()) + "'s Shot(" + XTOS(i) + ")";
//        pDepo_MyBunshinShot_->put(NEW MyBunshinShot001(name.c_str()));
//    }
//    appendGroupChild(pDepo_MyBunshinShot_);

//    //自弾（スナイプ）ストック
//    pDepo_MySnipeBunshinShot_ = NEW GgafCore::ActorDepository("Depo_MySnipeBunshinShot");
//    for (int i = 0; i < 5; i++) {
//        std::string name = std::string(getName()) + "'s SnipeShot(" + XTOS(i) + ")";
//        pDepo_MySnipeBunshinShot_->put(NEW MyBunshinSnipeShot001(name.c_str()));
//    }
//    appendGroupChild(pDepo_MySnipeBunshinShot_);
    //レーザーストック
//    if (_laser_kind == LASER_KOANYA) {
//        pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
//        for (int i = 0; i < MAX_LASER_CHIP_NUM; i++) {
//            std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
//            pLaserChipDepo_->put(NEW MyBunshinWateringLaserChip001(name.c_str()));
//        }
//        pLaserChipDepo_->config(MAX_LASER_CHIP_NUM, MAX_LASER_CHIP_NUM/3);
//        appendGroupChild(pLaserChipDepo_);
//    } else if (_laser_kind == LASER_THUNDER) {
//        pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
//        for (int i = 0; i < MAX_LASER_CHIP_NUM; i++) {
//            std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
//            MyBunshinStraightLaserChip001* pChip = NEW MyBunshinStraightLaserChip001(name.c_str());
//            pChip->setSource(this);
//            pLaserChipDepo_->put(pChip);
//        }
//        pLaserChipDepo_->config(MAX_LASER_CHIP_NUM, MAX_LASER_CHIP_NUM/3);
//        appendGroupChild(pLaserChipDepo_);
//    }
//
    //ロックオンコントローラー
//    pLockonCtrler_ = NEW MyLockonController("LockonController");
//    appendGroupChild(pLockonCtrler_);
//
//    //フォトンコントローラー
//    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
//    appendGroupChild(pTorpedoCtrler_);

//    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
//    pSeTx->set(SE_FIRE_LASER,   "SE_MY_FIRE_LASER_002");
//    pSeTx->set(SE_FIRE_SHOT,    "SE_MY_FIRE_SHOT_002");
//    pSeTx->set(SE_FIRE_TORPEDO, "SE_MY_FIRE_TORPEDO_002");

    pass_p_seq_ = 0;
//    std::string name2 = std::string(prm_name) + "'s Geo2";
//    pGeo2_ = NEW GgafLib::DefaultGeometricActor(name2.c_str());
//    rz_local_copy_ = _rz_local;
//    _is_thunder_lock = false;
}

//void MyBunshinController::onCreateModel() {
//}

void MyBunshinController::initialize() {
//    setScaleR(1.0);
//    getScaler()->setRange(R_SC(1.0), R_SC(4.0));
}

void MyBunshinController::onReset() {
}

void MyBunshinController::onActive() {
    //レーザーやロックンターゲットや魚雷が子にいるため
    //個別に呼び出す
//    pLockonCtrler_->onActive();
//    pTorpedoCtrler_->onActive();
//    setAlpha(0);
//    getAlphaFader()->transitionLinearToTop(120);
//    resetMaterialColor();
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_); //分身のクルクル速度
}

void MyBunshinController::processBehavior() {
    changeGeoLocal(); //ローカル座標の操作とする。
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();

    //ロックオン対象へ方向を向ける
//    _is_thunder_lock = false;
//    if (_laser_kind == LASER_THUNDER) {
//        //絶対座標系で通常のロックオン対象狙う方向ベクトル
//        GgafDx::GeometricActor* pTargetActor = pLockonCtrler_->pMainLockonCursor_->pTarget_;
//        if (pTargetActor) {
//            _is_thunder_lock = true;
//            int mvx = pTargetActor->_x - _x_final; //ここで自身の _x, _y, _z は絶対座標(_x_final)であることがポイント
//            int mvy = pTargetActor->_y - _y_final; //自機のやや上を狙う
//            int mvz = pTargetActor->_z - _z_final;
//            int tvx, tvy, tvz;
//            cnvDirectionWorldToLocal(mvx, mvy, mvz,
//                                     tvx, tvy, tvz);
//            //ロックオン対象方向向きシークエンス開始
//            angle rz_target, ry_target;
//            UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target);
//            //計算の結果、rz_target ry_target に向けば、ロックオン対象に向ける
//            pVecVehicle->turnRzRyFaceAngTo(
//                            rz_target, ry_target,
//                            D_ANG(10), D_ANG(0),
//                            TURN_CLOSE_TO, false);
//        }
//
//        if (pLockonCtrler_->pMainLockonCursor_->hasJustReleaseLockon()) {
//            pVecVehicle->turnRzRyFaceAngTo(
//                            0, rz_local_copy_,
//                            D_ANG(10), D_ANG(0),
//                            TURN_CLOSE_TO, false);
//        }
//    }

    pVecVehicle->behave();
    getScaler()->behave();
//    getAlphaFader()->behave();
//    getColorist()->behave();


    changeGeoFinal();
}


//void MyBunshinController::processChangeGeoFinal() {
//    if (pBase_->is_isolate_mode_) {
//        return;
//    }
//    if (getActiveFrame() <= 120) {
//        return;
//    }
//     //絶対座標計算後
//    MyShip* const pMyShip = pMYSHIP;
//    const VirtualButton* pVbPlay = VB_PLAY;
//
////    if (getAlpha() > 0.99f) {
////        if (pMyShip->is_just_shot_) {
////            if (pMyShip->is_snipe_shot_) {
////                //分身はスナイプショットは撃たない。
////    //            MyBunshinSnipeShot001* const pSnipeShot = (MyBunshinSnipeShot001*)pDepo_MySnipeBunshinShot_->dispatch();
////    //            if (pSnipeShot) {
////    //                getSeTransmitter()->play3D(SE_FIRE_SHOT);
////    //                pSnipeShot->setPositionAt(this);
////    //                pSnipeShot->getVecVehicle()->setRzRyMvAng(_rz, _ry);
////    //                pSnipeShot->getVecVehicle()->setMvVelo(PX_C(70));
////    //                pSnipeShot->getVecVehicle()->setMvAcce(100);
////    //            }
////            } else {
////                if (pMyShip->shot_level_ >= 1) {
////                    MyBunshinShot001* const  pShot = (MyBunshinShot001*)pDepo_MyBunshinShot_->dispatch();
////                    if (pShot) {
////                        getSeTransmitter()->play3D(SE_FIRE_SHOT);
////                        pShot->setPositionAt(this);
////                        pShot->getVecVehicle()->setRzRyMvAng(_rz, _ry);
////                        pShot->getVecVehicle()->setMvVelo(PX_C(70));
////                        pShot->getVecVehicle()->setMvAcce(100);
////                    }
////                }
////                if (pMyShip->shot_level_ == 2) {
////                    uint32_t i = pMyShip->soft_rapidshot_shot_count_ % 4;
////                    UTIL::shotWay003(this,
////                                     pDepo_MyBunshinShot_, MyShip::shot2_matrix_[i],
////                                     nullptr, nullptr,
////                                     nullptr, nullptr,
////                                     PX_C(1),
////                                     MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
////                                     D_ANG(5), D_ANG(5),
////                                     PX_C(70), 100,
////                                     1, 0, 1.0);
////                } else if (pMyShip->shot_level_ >= 3) {
////                    uint32_t i = pMyShip->soft_rapidshot_shot_count_ % 2;
////                    UTIL::shotWay003(this,
////                                     pDepo_MyBunshinShot_, MyShip::shot3_matrix_[i],
////                                     nullptr, nullptr,
////                                     nullptr, nullptr,
////                                     PX_C(1),
////                                     MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
////                                     D_ANG(5), D_ANG(5),
////                                     PX_C(70), 100,
////                                     1, 0, 1.0);
////                }
////            }
////        }
////        if (pMyShip->is_shooting_laser_ && pVbPlay->isPressed(0, VB_SHOT1)) {
////            if (_laser_kind == LASER_KOANYA) {
////                //レーザー発射。
////                MyBunshinWateringLaserChip001* pLaserChip = (MyBunshinWateringLaserChip001*)pLaserChipDepo_->dispatch();
////                if (pLaserChip) {
////                    pLaserChip->setOrg(this);
////                    if (pLaserChip->getInfrontChip() == nullptr) {
////                        getSeTransmitter()->play3D(SE_FIRE_LASER);
////                    }
////                }
////            } else if (_laser_kind == LASER_THUNDER) {
////                //TEST
////                MyBunshinStraightLaserChip001* pLaserChip = (MyBunshinStraightLaserChip001*)pLaserChipDepo_->dispatch();
////                if (pLaserChip) {
////                    pLaserChip->setOrg(this);
////                    if (pLaserChip->getInfrontChip() == nullptr) {
////                        getSeTransmitter()->play3D(SE_FIRE_LASER);
////                    }
////                }
////            }
////        } else {
////            pLockonCtrler_->releaseAllLockon(); //ロックオン解除
////        }
////
////        //光子魚雷発射
////        if (pVbPlay->isPushedDown(0, VB_SHOT2)) {
////            if (pTorpedoCtrler_->fire()) {
////                getSeTransmitter()->play3D(SE_FIRE_TORPEDO);
////            }
////        }
////    } //getAlpha() > 0.5
//}

void MyBunshinController::processJudgement() {
}

void MyBunshinController::onInactive() {
    //レーザーやロックンターゲットや魚雷が子にいるため
    //個別に呼び出す
//    pLockonCtrler_->onInactive();
//    pTorpedoCtrler_->onInactive();
}

//void MyBunshinController::onHit(const GgafCore::Actor* prm_pOtherActor) {
//}

void MyBunshinController::effectFreeModeIgnited() {
    getVecVehicle()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_*2); //分身の速いクルクル
//    getColorist()->flush(1.0, 5, 5, 3);
}

//void MyBunshinController::effectFreeModeReady() {
//    getScaler()->beat(10, 4, 0, 4, 1); //オプションぷるぷる、発射じゅんびOKのエフェクト
//}
//
//void MyBunshinController::effectFreeModeLaunch() {
//    EffectTurbo002* const pTurbo002 = CommonScene_dispatch(EffectTurbo002);
//    if (pTurbo002) {
//        if (_is_local) {
//            pTurbo002->setPosition(_x_final,_y_final,_z_final);
//            pTurbo002->setRollFaceAng(_rx_final);
//            pTurbo002->setRzRyFaceAng(_rz_final, _ry_final+D90ANG);
//        } else {
//            pTurbo002->setPositionAt(this);
//            pTurbo002->setRollFaceAng(_rx);
//            pTurbo002->setRzRyFaceAng(_rz, _ry+D90ANG);
//        }
//    }
//}
void MyBunshinController::effectFreeModePause() {
    getVecVehicle()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_);
}

void MyBunshinController::setRadiusPosition(coord prm_radius_pos) {
    if (_is_local) {
        _y = prm_radius_pos;
        if (_y < 1) {
            _y = 1;
        }
    } else {
        _y_local = prm_radius_pos;
        if (_y_local < 1) {
            _y_local = 1;
        }
    }
}
void MyBunshinController::addRadiusPosition(coord prm_radius_pos) {
    if (_is_local) {
        _y += prm_radius_pos;
        if (_y < 1) {
            _y = 1;
        }
    } else {
        _y_local += prm_radius_pos;
        if (_y_local < 1) {
            _y_local = 1;
        }
    }
}

coord MyBunshinController::getRadiusPosition() {
    return _is_local ? _y : _y_local;
}

void MyBunshinController::slideMvRadiusPosition(coord prm_target_radius_pos, frame prm_spent_frames) {
    bool is_local = _is_local;
    if (!is_local) { changeGeoLocal(); }  //ローカル座標の操作とする。
    coord d = prm_target_radius_pos - _y;
    getVecVehicle()->setRzRyMvAng(D90ANG, D0ANG); //Y軸方向
    getVecVehicle()->asstMv()->slideByDt(d, prm_spent_frames, 0.2, 0.8, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}

//void MyBunshinController::setExpanse(angvelo prm_ang_expanse) {
//    if (_is_thunder_lock) {
//        rz_local_copy_ = UTIL::simplifyAng(prm_ang_expanse);
//    } else {
//
//        if (_is_local) {
//            _rz = UTIL::simplifyAng(prm_ang_expanse);
//        } else {
//            _rz_local = UTIL::simplifyAng(prm_ang_expanse);
//            rz_local_copy_ = _rz_local;
//        }
//    }
//}

void MyBunshinController::addExpanse(angvelo prm_ang_expanse) {
    if (_is_local) {
        _rz = UTIL::simplifyAng(_rz+prm_ang_expanse);
    } else {
        GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
        if (pVecVehicle->isTurningFaceAng()) {
            pVecVehicle->_target_face[AXIS_Z] = UTIL::simplifyAng(pVecVehicle->_target_face[AXIS_Z]+prm_ang_expanse);
        } else {
            _rz_local = UTIL::simplifyAng(_rz_local+prm_ang_expanse);
        }
    }
}

angvelo MyBunshinController::getExpanse() {
    return _is_local ? _rz : _rz_local;
}

void MyBunshinController::turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames) {
    bool is_local = _is_local;
    if (!is_local) { changeGeoLocal(); }  //ローカル座標の操作とする。
    getVecVehicle()->asstFaceAng()->turnRzRyByDtTo(prm_target_ang_expanse, D_ANG(0), TURN_CLOSE_TO, true,
                                                    prm_spent_frames, 0.3, 0.5, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}
//
//bool MyBunshinController::setFaceAngAsMainLockon() {
//    bool is_local = _is_local;
//    if (!is_local) { changeGeoLocal(); }  //ローカル座標の操作とする。
//    GgafDx::GeometricActor* pTargetActor = pLockonCtrler_->pMainLockonCursor_->pTarget_;
//    bool r = false;
//    if (pTargetActor) {
//        r = true;
//        setFaceAngAs(pTargetActor);
//    }
//    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
//    return r;
//
//}

MyBunshinController::~MyBunshinController() {
//    GGAF_DELETE(pGeo2_);
}

