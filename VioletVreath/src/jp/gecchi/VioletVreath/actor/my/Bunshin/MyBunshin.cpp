#include "MyBunshin.h"

#include "MyBunshinBase.h"
#include "MyBunshinController.h"
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
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAssistant.h"
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

enum {
    SE_FIRE_LASER  ,
    SE_FIRE_SHOT   ,
    SE_FIRE_TORPEDO,
};

MyBunshin::MyBunshin(const char* prm_name, MyBunshinController* prm_pBunshinController, MyBunshinBase* prm_pBase) :
        VvEffectActor<DefaultMeshSetActor>(prm_name, "myvic", StatusReset(MyBunshin)) {

    _class_name = "MyBunshin";
    pBase_ = prm_pBase;
    pBunshinController_ = prm_pBunshinController;
    _laser_kind = LASER_KOANYA; //LASER_KOANYA; //LASER_THUNDER

    //���e�X�g�b�N
    pDepo_MyBunshinShot_ = NEW GgafCore::ActorDepository("Depo_MyBunshinShot");
    for (int i = 0; i < 40; i++) {
        std::string name = std::string(getName()) + "'s Shot(" + XTOS(i) + ")";
        pDepo_MyBunshinShot_->put(NEW MyBunshinShot001(name.c_str()));
    }
    appendGroupChild(pDepo_MyBunshinShot_);

//    //���e�i�X�i�C�v�j�X�g�b�N
//    pDepo_MySnipeBunshinShot_ = NEW GgafCore::ActorDepository("Depo_MySnipeBunshinShot");
//    for (int i = 0; i < 5; i++) {
//        std::string name = std::string(getName()) + "'s SnipeShot(" + XTOS(i) + ")";
//        pDepo_MySnipeBunshinShot_->put(NEW MyBunshinSnipeShot001(name.c_str()));
//    }
//    appendGroupChild(pDepo_MySnipeBunshinShot_);
    //���[�U�[�X�g�b�N
    if (_laser_kind == LASER_KOANYA) {
        pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
        for (int i = 0; i < MAX_LASER_CHIP_NUM; i++) {
            std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
            pLaserChipDepo_->put(NEW MyBunshinWateringLaserChip001(name.c_str()));
        }
        pLaserChipDepo_->config(MAX_LASER_CHIP_NUM, MAX_LASER_CHIP_NUM/3);
        appendGroupChild(pLaserChipDepo_);
    } else if (_laser_kind == LASER_THUNDER) {
        pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
        for (int i = 0; i < MAX_LASER_CHIP_NUM; i++) {
            std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
            MyBunshinStraightLaserChip001* pChip = NEW MyBunshinStraightLaserChip001(name.c_str());
            pChip->setSource(this);
            pLaserChipDepo_->put(pChip);
        }
        pLaserChipDepo_->config(MAX_LASER_CHIP_NUM, MAX_LASER_CHIP_NUM/3);
        appendGroupChild(pLaserChipDepo_);
    }

    //���b�N�I���R���g���[���[
    pLockonCtrler_ = NEW MyLockonController("LockonController");
    appendGroupChild(pLockonCtrler_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    appendGroupChild(pTorpedoCtrler_);

    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_FIRE_LASER,   "SE_MY_FIRE_LASER_002");
    pSeXmtr->set(SE_FIRE_SHOT,    "SE_MY_FIRE_SHOT_002");
    pSeXmtr->set(SE_FIRE_TORPEDO, "SE_MY_FIRE_TORPEDO_002");

    std::string name2 = std::string(prm_name) + "'s Geo2";
    pGeo2_ = NEW GgafLib::DefaultGeometricActor(name2.c_str());
    rz_prev_ = _rz;
    ry_prev_ = _ry;
}

void MyBunshin::onCreateModel() {
}

void MyBunshin::initialize() {
    setScaleR(1.0);
    getScaler()->setRange(R_SC(1.0), R_SC(4.0));
}

void MyBunshin::onReset() {
}

void MyBunshin::onActive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����q�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
    setAlpha(0); //!!
//    getAlphaFader()->transitionLinearToTop(120);
    resetMaterialColor(); //!!
//    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
//    pLocoVehicle->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_); //���g�̃N���N�����x
}

void MyBunshin::processBehavior() {
}

void MyBunshin::processSettlementBehavior() {
    rz_prev_ = _rz;
    ry_prev_ = _ry;

    changeGeoLocal(); //���[�J�����W�̑���Ƃ���B
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();

    //���b�N�I���Ώۂ֕�����������
//    _is_thunder_lock = false;
    if (_laser_kind == LASER_THUNDER) {
        //��΍��W�n�Œʏ�̃��b�N�I���Ώۑ_�������x�N�g��
        GgafDx::GeometricActor* pTargetActor = pLockonCtrler_->pMainLockonCursor_->pTarget_;
        if (pTargetActor) {
//            _is_thunder_lock = true;
            int mvx = pTargetActor->_x - _x_final; //�����Ŏ��g�� _x, _y, _z �͐�΍��W(_x_final)�ł��邱�Ƃ��|�C���g
            int mvy = pTargetActor->_y - _y_final; //���@�̂����_��
            int mvz = pTargetActor->_z - _z_final;
            int tvx, tvy, tvz;
            cnvDirectionWorldToLocal(mvx, mvy, mvz,
                                     tvx, tvy, tvz);
            //���b�N�I���Ώە��������V�[�N�G���X�J�n
            angle rz_target, ry_target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target);
            //�v�Z�̌��ʁArz_target ry_target �Ɍ����΁A���b�N�I���ΏۂɌ�����
//            setRzRyFaceAng(rz_target, ry_target);
            //����������������
            pLocoVehicle->turnRzRyFaceAngTo(
                            rz_target, ry_target,
                            D_ANG(5), D_ANG(0),
                            TURN_CLOSE_TO, false);
        } else {
//            setRzRyFaceAng(0, 0);
            pLocoVehicle->turnRzRyFaceAngTo(
                            D_ANG(0), D_ANG(0),
                            D_ANG(5), D_ANG(0),
                            TURN_CLOSE_TO, false);
        }
    }

    pLocoVehicle->behave();
    getScaler()->behave();
    getAlphaFader()->behave(); //!!
    getColorist()->behave();   //!!


    changeGeoFinal();

    VvEffectActor<DefaultMeshSetActor>::processSettlementBehavior();

    UTIL::getWayAngleArr(_rz, rz_prev_, N_DISPATCH_AT_ONCE+1, out_way_rz_, TURN_CLOSE_TO); //+1�͑O���`�b�v�̌����Ɠ����ł��邽�߁A�̂Ă�
    UTIL::getWayAngleArr(_ry, ry_prev_, N_DISPATCH_AT_ONCE+1, out_way_ry_, TURN_CLOSE_TO);

}
void MyBunshin::processChangeGeoFinal() {
    if (pBase_->is_isolate_mode_) {
        return;
    }
    if (getActiveFrame() <= 120) {
        return;
    }
     //��΍��W�v�Z��
    MyShip* const pMyShip = pMYSHIP;
    const VirtualButton* pVbPlay = VV_VB_PLAY;


    //!! -->
    if (getAlpha() > 0.99f) {
        if (pMyShip->is_just_shot_) {
            if (pMyShip->is_snipe_shot_) {
                //���g�̓X�i�C�v�V���b�g�͌����Ȃ��B
    //            MyBunshinSnipeShot001* const pSnipeShot = (MyBunshinSnipeShot001*)pDepo_MySnipeBunshinShot_->dispatch();
    //            if (pSnipeShot) {
    //                getSeXmtr()->play3D(SE_FIRE_SHOT);
    //                pSnipeShot->setPositionAt(this);
    //                pSnipeShot->getLocoVehicle()->setRzRyMvAng(_rz, _ry);
    //                pSnipeShot->getLocoVehicle()->setMvVelo(PX_C(70));
    //                pSnipeShot->getLocoVehicle()->setMvAcce(100);
    //            }
            } else {
                if (pMyShip->shot_level_ >= 1) {
                    MyBunshinShot001* const  pShot = (MyBunshinShot001*)pDepo_MyBunshinShot_->dispatch();
                    if (pShot) {
                        getSeXmtr()->play3D(SE_FIRE_SHOT);
                        pShot->setPositionAt(this);
                        pShot->getLocoVehicle()->setRzRyMvAng(_rz, _ry);
                        pShot->getLocoVehicle()->setMvVelo(PX_C(70));
                        pShot->getLocoVehicle()->setMvAcce(100);
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
        if (pMyShip->is_shooting_laser_ && pVbPlay->isPressed(0, VV_VB_SHOT1)) {
            if (_laser_kind == LASER_KOANYA) {
                //���[�U�[���ˁB
                std::vector<LaserChip*> lstLaserChip = pLaserChipDepo_->dispatchN(N_DISPATCH_AT_ONCE);
                for (int i = 0; i < lstLaserChip.size(); i++) {
                    MyBunshinWateringLaserChip001* pLaserChip = (MyBunshinWateringLaserChip001*)lstLaserChip[i];
                    if (pLaserChip) {
                        pLaserChip->setOrg(this);
                        if (pLaserChip->getInfrontChip() == nullptr) {
                            getSeXmtr()->play3D(SE_FIRE_LASER);
                        }
                    }
                }
            } else if (_laser_kind == LASER_THUNDER) {
                //TEST
                std::vector<LaserChip*> lstLaserChip = pLaserChipDepo_->dispatchN(N_DISPATCH_AT_ONCE);
                for (int i = 0; i < lstLaserChip.size(); i++) {
                    MyBunshinStraightLaserChip001* pLaserChip = (MyBunshinStraightLaserChip001*)lstLaserChip[i];
                    if (pLaserChip) {
                        pLaserChip->setOrg(this);
                        if (pLaserChip->getInfrontChip() == nullptr) {
                            getSeXmtr()->play3D(SE_FIRE_LASER);
                        }
                    }
                }
//                MyBunshinStraightLaserChip001* pLaserChip = (MyBunshinStraightLaserChip001*)pLaserChipDepo_->dispatch();
//                if (pLaserChip) {
//                    pLaserChip->setOrg(this);
//                    if (pLaserChip->getInfrontChip() == nullptr) {
//                        getSeXmtr()->play3D(SE_FIRE_LASER);
//                    }
//                }
            }
        } else {
            pLockonCtrler_->releaseAllLockon(); //���b�N�I������
        }

        //���q��������
        if (pVbPlay->isPushedDown(0, VV_VB_SHOT2)) {
            if (pTorpedoCtrler_->fire()) {
                getSeXmtr()->play3D(SE_FIRE_TORPEDO);
            }
        }
    } //getAlpha() > 0.5
    //!! <--
}

void MyBunshin::processJudgement() {
}

void MyBunshin::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����q�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
}

void MyBunshin::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void MyBunshin::effectFreeModeIgnited() {
    pBunshinController_->effectFreeModeIgnited();
//    getLocoVehicle()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_*2); //���g�̑����N���N��
    getColorist()->flush(1.0, 5, 5, 3); //!!
}

void MyBunshin::effectFreeModeReady() {
    getScaler()->beat(10, 4, 0, 4, 1); //�I�v�V�����Ղ�Ղ�A���˂�����OK�̃G�t�F�N�g
}

void MyBunshin::effectFreeModeLaunch() {
    EffectTurbo002* const pTurbo002 = CommonScene_dispatch(EffectTurbo002);
    if (pTurbo002) {
        if (_is_local) {
            pTurbo002->setPosition(_x_final,_y_final,_z_final);
            pTurbo002->setRollFaceAng(_rx_final);
            pTurbo002->setRzRyFaceAng(_rz_final, _ry_final+D90ANG);
        } else {
            pTurbo002->setPositionAt(this);
            pTurbo002->setRollFaceAng(_rx);
            pTurbo002->setRzRyFaceAng(_rz, _ry+D90ANG);
        }
    }
}
void MyBunshin::effectFreeModePause() {
    pBunshinController_->effectFreeModePause();
}


MyBunshin::~MyBunshin() {
    GGAF_DELETE(pGeo2_);
}

