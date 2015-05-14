#include "MyBunshin.h"

#include "MyBunshinBase.h"
#include "MyBunshinShot001.h"
#include "MyBunshinSnipeShot001.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) : DefaultMorphMeshActor(prm_name, "4/Eres") {
//MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) :
        DefaultMeshSetActor(prm_name, "8/myvic", STATUS(MyBunshin)) {

    _class_name = "MyBunshin";
    pBase_ = prm_pBase;

    //自弾ストック
    pDepo_MyBunshinShot_ = NEW GgafActorDepository("Depo_MyBunshinShot");
    for (int i = 0; i < 40; i++) {
        std::string name = std::string(getName()) + "'s Shot(" + XTOS(i) + ")";
        pDepo_MyBunshinShot_->put(NEW MyBunshinShot001(name.c_str()));
    }
    addSubGroup(pDepo_MyBunshinShot_);

    //自弾（スナイプ）ストック
    pDepo_MySnipeBunshinShot_ = NEW GgafActorDepository("Depo_MySnipeBunshinShot");
    for (int i = 0; i < 5; i++) {
        std::string name = std::string(getName()) + "'s SnipeShot(" + XTOS(i) + ")";
        pDepo_MySnipeBunshinShot_->put(NEW MyBunshinSnipeShot001(name.c_str()));
    }
    addSubGroup(pDepo_MySnipeBunshinShot_);

    //レーザーストック
    pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
    for (int i = 0; i < 60; i++) {
        std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
        pLaserChipDepo_->put(NEW MyBunshinWateringLaserChip001(name.c_str()));
    }
    pLaserChipDepo_->config(80, 25, nullptr);
    addSubGroup(pLaserChipDepo_);

    //ロックオンコントローラー
    pLockonCtrler_ = NEW MyLockonController("LockonController");
    addSubGroup(pLockonCtrler_);

    //フォトンコントローラー
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    addSubGroup(pTorpedoCtrler_);

    pScaler_ = NEW GgafDxScaler(this);
    pAFader_ = NEW GgafDxAlphaFader(this);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_FIRE_LASER,   "WAVE_MY_FIRE_LASER_002");
    pSeTx->set(SE_FIRE_SHOT,    "WAVE_MY_FIRE_SHOT_002");
    pSeTx->set(SE_FIRE_TORPEDO, "WAVE_MY_FIRE_TORPEDO_002");
}

void MyBunshin::onCreateModel() {
}

void MyBunshin::initialize() {
    setScaleR(1.0);
    pScaler_->setRange(R_SC(1.0), R_SC(4.0));
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(PX_C(4)); //分身の時点
}

void MyBunshin::onReset() {
}

void MyBunshin::onActive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
    setAlpha(0);
    pAFader_->transitionLinerToTop(120);
}

void MyBunshin::processBehavior() {
    changeGeoLocal(); //ローカル座標の操作とする。

    GgafDxKuroko* pKuroko = getKuroko();

    pKuroko->behave();
    pScaler_->behave();
    pAFader_->behave();
    changeGeoFinal();
}


void MyBunshin::processChangeGeoFinal() {
    if (pBase_->is_isolate_mode_) {
        return;
    }
    if (getActiveFrame() <= 120) {
        return;
    }
     //絶対座標計算後
    MyShip* const pMyShip = P_MYSHIP;
    const VirtualButton* pVbPlay = VB_PLAY;

    if (pMyShip->is_just_shot_) {
        if (pMyShip->is_snipe_shot_) {
            MyBunshinSnipeShot001* const pSnipeShot = (MyBunshinSnipeShot001*)pDepo_MySnipeBunshinShot_->dispatch();
            if (pSnipeShot) {
                getSeTx()->play3D(SE_FIRE_SHOT);
                pSnipeShot->positionAs(this);
                pSnipeShot->getKuroko()->setRzRyMvAng(_rz, _ry);
                pSnipeShot->getKuroko()->setMvVelo(PX_C(70));
                pSnipeShot->getKuroko()->setMvAcce(100);
            }
        } else {
            if (pMyShip->shot_level_ >= 1) {
                MyBunshinShot001* const  pShot = (MyBunshinShot001*)pDepo_MyBunshinShot_->dispatch();
                if (pShot) {
                    getSeTx()->play3D(SE_FIRE_SHOT);
                    pShot->positionAs(this);
                    pShot->getKuroko()->setRzRyMvAng(_rz, _ry);
                    pShot->getKuroko()->setMvVelo(PX_C(70));
                    pShot->getKuroko()->setMvAcce(100);
                }
            }
            if (pMyShip->shot_level_ == 2) {
                uint32_t i = pMyShip->soft_rapidshot_shot_count_ % 4;
                UTIL::shotWay003(this,
                                 pDepo_MyBunshinShot_, MyShip::shot2_matrix_[i],
                                 nullptr, nullptr,
                                 nullptr, nullptr,
                                 PX_C(1),
                                 MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
                                 D_ANG(5), D_ANG(5),
                                 PX_C(70), 100,
                                 1, 0, 1.0);
            } else if (pMyShip->shot_level_ >= 3) {
                uint32_t i = pMyShip->soft_rapidshot_shot_count_ % 2;
                UTIL::shotWay003(this,
                                 pDepo_MyBunshinShot_, MyShip::shot3_matrix_[i],
                                 nullptr, nullptr,
                                 nullptr, nullptr,
                                 PX_C(1),
                                 MYSHIP_SHOT_MATRIX, MYSHIP_SHOT_MATRIX,
                                 D_ANG(5), D_ANG(5),
                                 PX_C(70), 100,
                                 1, 0, 1.0);
            }
        }
    }

    //レーザー発射。
    if (pMyShip->is_shooting_laser_ && pVbPlay->isBeingPressed(VB_SHOT1)) {
        MyBunshinWateringLaserChip001* pLaserChip = (MyBunshinWateringLaserChip001*)pLaserChipDepo_->dispatch();
        if (pLaserChip) {
            pLaserChip->setOrg(this);
            if (pLaserChip->getFrontChip() == nullptr) {
                getSeTx()->play3D(SE_FIRE_LASER);
            }
        }
    } else {
        pLockonCtrler_->releaseAllLockon(); //ロックオン解除
    }
    //光子魚雷発射
    if (pVbPlay->isPushedDown(VB_SHOT2)) {
        if (pTorpedoCtrler_->fire()) {
            getSeTx()->play3D(SE_FIRE_TORPEDO);
        }
    }
}

void MyBunshin::processJudgement() {
}

void MyBunshin::onInactive() {
    //レーザーやロックンターゲットや魚雷がサブにいるため
    //個別に呼び出す
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
}

void MyBunshin::onHit(const GgafActor* prm_pOtherActor) {
}

void MyBunshin::effectIgnited() {
    pScaler_->beat(10, 4, 0, 4, 1); //オプションぷるぷる、発射じゅんびOKのエフェクト
}

void MyBunshin::setRadiusPosition(coord prm_radius_position) {
    if (_is_local) {
        _y = prm_radius_position;
        if (_y < 1) {
            _y = 1;
        }
    } else {
        _y_local = prm_radius_position;
        if (_y_local < 1) {
            _y_local = 1;
        }
    }
}
void MyBunshin::addRadiusPosition(coord prm_radius_position) {
    if (_is_local) {
        _y += prm_radius_position;
        if (_y < 1) {
            _y = 1;
        }
    } else {
        _y_local += prm_radius_position;
        if (_y_local < 1) {
            _y_local = 1;
        }
    }
}

coord MyBunshin::getRadiusPosition() {
    return _is_local ? _y : _y_local;
}

void MyBunshin::slideMvRadiusPosition(coord prm_target_radius_position, frame prm_spent_frames) {
    bool is_local = _is_local;
    if (!is_local) { changeGeoLocal(); }  //ローカル座標の操作とする。
    coord d = prm_target_radius_position - _y;
    getKuroko()->setRzRyMvAng(D90ANG, D0ANG); //Y軸方向
    getKuroko()->asstA()->slideMvByDt(d, prm_spent_frames, 0.2, 0.8, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}

void MyBunshin::setExpanse(angvelo prm_ang_expanse) {
    if (_is_local) {
        _rz = UTIL::simplifyAng(prm_ang_expanse);
    } else {
        _rz_local = UTIL::simplifyAng(prm_ang_expanse);
    }
}

void MyBunshin::addExpanse(angvelo prm_ang_expanse) {
    if (_is_local) {
        _rz = UTIL::simplifyAng(_rz+prm_ang_expanse);
    } else {
        _rz_local = UTIL::simplifyAng(_rz_local+prm_ang_expanse);
    }
}

angvelo MyBunshin::getExpanse() {
    return _is_local ? _rz : _rz_local;
}

void MyBunshin::turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames) {
    bool is_local = _is_local;
    if (!is_local) { changeGeoLocal(); }  //ローカル座標の操作とする。
    getKuroko()->asstB()->turnRzFaceAngByDtTo(prm_target_ang_expanse, TURN_CLOSE_TO,
                                              prm_spent_frames, 0.3, 0.5, 0, true);
    if (!is_local) { changeGeoFinal(); }  //座標系を戻す
}

MyBunshin::~MyBunshin() {
    GGAF_DELETE(pScaler_);
    GGAF_DELETE(pAFader_);
}

