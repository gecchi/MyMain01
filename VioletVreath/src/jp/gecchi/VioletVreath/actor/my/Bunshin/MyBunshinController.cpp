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
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Colorist.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
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

MyBunshinController::MyBunshinController(const char* prm_name, MyBunshinBase* prm_pBase) :
        GgafLib::DefaultGeometricActor(prm_name, nullptr) {

    _class_name = "MyBunshinController";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActorでFKベースになるために必要
    pBase_ = prm_pBase;

////////////
    std::string bunshin_name = "MyBunshin" + XTOS(prm_pBase->bunshin_no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this, prm_pBase);
    this->appendGroupChildAsFk(pBunshin_,
                          0, 0, 0,
                          D0ANG, D0ANG, D0ANG);
}


void MyBunshinController::initialize() {
}

void MyBunshinController::onReset() {
}

void MyBunshinController::onActive() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_); //分身のクルクル速度
    pBunshin_->onActive();
}

void MyBunshinController::processBehavior() {
    changeGeoLocal(); //ローカル座標の操作とする。
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->behave();
    getScaler()->behave();
    changeGeoFinal();
}

void MyBunshinController::processJudgement() {
}

void MyBunshinController::onInactive() {
    pBunshin_->onInactive();
}

void MyBunshinController::effectFreeModeIgnited() {
    getLocusVehicle()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_*2); //分身の速いクルクル
}

void MyBunshinController::effectFreeModePause() {
    getLocusVehicle()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_);
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
    getLocusVehicle()->setRzRyMvAng(D90ANG, D0ANG); //Y軸方向
    getLocusVehicle()->asstMv()->slideByDt(d, prm_spent_frames, 0.2, 0.8, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}

void MyBunshinController::addExpanse(angvelo prm_ang_expanse) {
    if (_is_local) {
        _rz = UTIL::simplifyAng(_rz+prm_ang_expanse);
    } else {
        GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
        if (pLocusVehicle->isTurningFaceAng()) {
            pLocusVehicle->_target_face[AXIS_Z] = UTIL::simplifyAng(pLocusVehicle->_target_face[AXIS_Z]+prm_ang_expanse);
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
    getLocusVehicle()->asstFaceAng()->turnRzRyByDtTo(prm_target_ang_expanse, D_ANG(0), TURN_CLOSE_TO, true,
                                                    prm_spent_frames, 0.3, 0.5, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}

MyBunshinController::~MyBunshinController() {
}

