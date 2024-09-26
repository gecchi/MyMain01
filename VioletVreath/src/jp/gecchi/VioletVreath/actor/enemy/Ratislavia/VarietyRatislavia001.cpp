#include "VarietyRatislavia001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia001::VarietyRatislavia001(const char* prm_name) :
        EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia001";
    for (angle ang1 = 0; ang1 < D360ANG;  ang1 += (D_ANG(60))) {
        for (angle ang2 = 0; ang2 < D360ANG;  ang2 += (D_ANG(60))) {
            std::string name = "Omulus(" + XTOS(ang1) + "," + XTOS(ang2) + ")";
            appendChildAsFkOnSurface(NEW EnemyOmulus(name.c_str()), ang1, ang2);
            Sleep(1);
        }
    }

    pEnemyRatislaviaEye_ = NEW EnemyRatislaviaEye("EnemyRatislaviaEye", this);
    appendChild(pEnemyRatislaviaEye_);
}

void VarietyRatislavia001::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right + r1_*2 + r2_*2;
    _y = 0;
    _z = 0;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRzRyMvAng(D180ANG, 0);
    pLocusVehicle->setMvVelo(2000);
    pLocusVehicle->setFaceAngVelo(AXIS_Z, 60);
    pLocusVehicle->setFaceAngVelo(AXIS_Y, 70);
}

void VarietyRatislavia001::processBehavior() {
    if (pEnemyRatislaviaEye_) {
        if (pEnemyRatislaviaEye_->is_wake_) {

        } else {
            if (_x - pMYSHIP->_x < PX_C(2000)) {
                pEnemyRatislaviaEye_->wake(); //ぎょろりん！
            }
        }
    }

    EnemyRatislavia::processBehavior();
}

void VarietyRatislavia001::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if (prm_event_val == RATISLAVIA_EXPLOSION) {
        _TRACE_(FUNC_NAME<<" RATISLAVIA_EXPLOSION キャッチわりこみ！");
        pEnemyRatislaviaEye_ = nullptr;
    }
    EnemyRatislavia::onCatchEvent(prm_event_val, prm_pSource);
}

VarietyRatislavia001::~VarietyRatislavia001() {
}
