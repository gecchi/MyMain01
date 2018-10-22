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
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_FIRE_LASER  ,
    SE_FIRE_SHOT   ,
    SE_FIRE_TORPEDO,
};

//MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) : DefaultMorphMeshActor(prm_name, "4/Eres") {
//MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyBunshin::MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase) :
        DefaultMeshSetActor(prm_name, "8/myvic", STATUS(MyBunshin)) {

    _class_name = "MyBunshin";
    pBase_ = prm_pBase;

    //���e�X�g�b�N
    pDepo_MyBunshinShot_ = NEW GgafActorDepository("Depo_MyBunshinShot");
    for (int i = 0; i < 40; i++) {
        std::string name = std::string(getName()) + "'s Shot(" + XTOS(i) + ")";
        pDepo_MyBunshinShot_->put(NEW MyBunshinShot001(name.c_str()));
    }
    appendGroupChild(pDepo_MyBunshinShot_);

//    //���e�i�X�i�C�v�j�X�g�b�N
//    pDepo_MySnipeBunshinShot_ = NEW GgafActorDepository("Depo_MySnipeBunshinShot");
//    for (int i = 0; i < 5; i++) {
//        std::string name = std::string(getName()) + "'s SnipeShot(" + XTOS(i) + ")";
//        pDepo_MySnipeBunshinShot_->put(NEW MyBunshinSnipeShot001(name.c_str()));
//    }
//    appendGroupChild(pDepo_MySnipeBunshinShot_);

    //���[�U�[�X�g�b�N
    pLaserChipDepo_ = NEW LaserChipDepository("DepoBunshinLaser");
    for (int i = 0; i < 80; i++) {
        std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
        pLaserChipDepo_->put(NEW MyBunshinWateringLaserChip001(name.c_str()));
    }
    pLaserChipDepo_->config(80, 25, nullptr);
    appendGroupChild(pLaserChipDepo_);

    //���b�N�I���R���g���[���[
    pLockonCtrler_ = NEW MyLockonController("LockonController");
    appendGroupChild(pLockonCtrler_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    appendGroupChild(pTorpedoCtrler_);

    pColorist_ = NEW GgafDxColorist(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_FIRE_LASER,   "WAVE_MY_FIRE_LASER_002");
    pSeTx->set(SE_FIRE_SHOT,    "WAVE_MY_FIRE_SHOT_002");
    pSeTx->set(SE_FIRE_TORPEDO, "WAVE_MY_FIRE_TORPEDO_002");

    pass_p_seq_ = 0;
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
    setAlpha(0);
    getAlphaFader()->transitionLinearToTop(120);
    resetMaterialColor();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_); //���g�̃N���N�����x
}

void MyBunshin::processBehavior() {
    changeGeoLocal(); //���[�J�����W�̑���Ƃ���B

    GgafDxKuroko* pKuroko = getKuroko();

    pKuroko->behave();
    getScaler()->behave();
    getAlphaFader()->behave();
    pColorist_->behave();
    changeGeoFinal();
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
    const VirtualButton* pVbPlay = VB_PLAY;

    if (pMyShip->is_just_shot_) {
        if (pMyShip->is_snipe_shot_) {
            //���g�̓X�i�C�v�V���b�g�͌����Ȃ��B
//            MyBunshinSnipeShot001* const pSnipeShot = (MyBunshinSnipeShot001*)pDepo_MySnipeBunshinShot_->dispatch();
//            if (pSnipeShot) {
//                getSeTransmitter()->play3D(SE_FIRE_SHOT);
//                pSnipeShot->setPositionAt(this);
//                pSnipeShot->getKuroko()->setRzRyMvAng(_rz, _ry);
//                pSnipeShot->getKuroko()->setMvVelo(PX_C(70));
//                pSnipeShot->getKuroko()->setMvAcce(100);
//            }
        } else {
            if (pMyShip->shot_level_ >= 1) {
                MyBunshinShot001* const  pShot = (MyBunshinShot001*)pDepo_MyBunshinShot_->dispatch();
                if (pShot) {
                    getSeTransmitter()->play3D(SE_FIRE_SHOT);
                    pShot->setPositionAt(this);
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

    //���[�U�[���ˁB
    if (pMyShip->is_shooting_laser_ && pVbPlay->isPressed(VB_SHOT1)) {
        MyBunshinWateringLaserChip001* pLaserChip = (MyBunshinWateringLaserChip001*)pLaserChipDepo_->dispatch();
        if (pLaserChip) {
            pLaserChip->setOrg(this);
            if (pLaserChip->getInfrontChip() == nullptr) {
                getSeTransmitter()->play3D(SE_FIRE_LASER);
            }
        }
    } else {
        pLockonCtrler_->releaseAllLockon(); //���b�N�I������
    }
    //���q��������
    if (pVbPlay->isPushedDown(VB_SHOT2)) {
        if (pTorpedoCtrler_->fire()) {
            getSeTransmitter()->play3D(SE_FIRE_TORPEDO);
        }
    }
}

void MyBunshin::processJudgement() {
}

void MyBunshin::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����q�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
}

void MyBunshin::onHit(const GgafActor* prm_pOtherActor) {
}

void MyBunshin::effectFreeModeIgnited() {
    getKuroko()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_*2); //���g�̑����N���N��
    pColorist_->flush(1.0, 5, 5, 3);
}

void MyBunshin::effectFreeModeReady() {
    getScaler()->beat(10, 4, 0, 4, 1); //�I�v�V�����Ղ�Ղ�A���˂�����OK�̃G�t�F�N�g
}

void MyBunshin::effectFreeModeLaunch() {
    EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
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
    getKuroko()->setRollFaceAngVelo(pBase_->bunshin_default_angvelo_mv_);
}

void MyBunshin::setRadiusPosition(coord prm_radius_pos) {
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
void MyBunshin::addRadiusPosition(coord prm_radius_pos) {
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

coord MyBunshin::getRadiusPosition() {
    return _is_local ? _y : _y_local;
}

void MyBunshin::slideMvRadiusPosition(coord prm_target_radius_pos, frame prm_spent_frames) {
    bool is_local = _is_local;
    if (!is_local) { changeGeoLocal(); }  //���[�J�����W�̑���Ƃ���B
    coord d = prm_target_radius_pos - _y;
    getKuroko()->setRzRyMvAng(D90ANG, D0ANG); //Y������
    getKuroko()->asstMv()->slideByDt(d, prm_spent_frames, 0.2, 0.8, 0, true);
    if (!is_local) { changeGeoFinal(); }  //���W�n��߂�
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
    if (!is_local) { changeGeoLocal(); }  //���[�J�����W�̑���Ƃ���B
    getKuroko()->asstFaceAng()->turnRzByDtTo(prm_target_ang_expanse, TURN_CLOSE_TO,
                                                    prm_spent_frames, 0.3, 0.5, 0, true);
    if (!is_local) { changeGeoFinal(); }  //���W�n��߂�
}

MyBunshin::~MyBunshin() {
    GGAF_DELETE(pColorist_);
}

