#include "VarietyRatislavia001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia001::VarietyRatislavia001(const char* prm_name) :
        EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia001";
    for (angle ang1 = 0; ang1 < D360ANG;  ang1 += (D_ANG(60))) {
        for (angle ang2 = 0; ang2 < D360ANG;  ang2 += (D_ANG(60))) {
            std::string name = "Omulus(" + XTOS(ang1) + "," + XTOS(ang2) + ")";
            appendGroupChildAsFkOnSurface(NEW EnemyOmulus(name.c_str()), ang1, ang2);
            Sleep(1);
        }
    }

    pEnemyRatislaviaEye_ = NEW EnemyRatislaviaEye("EnemyRatislaviaEye", this);
    appendGroupChild(pEnemyRatislaviaEye_);
}

void VarietyRatislavia001::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    _x = pSpacetime->_x_bound_right + r1_*2 + r2_*2;
    _y = 0;
    _z = 0;
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->setRzRyMvAng(D180ANG, 0);
    pVecDriver->setMvVelo(2000);
    pVecDriver->setFaceAngVelo(AXIS_Z, 60);
    pVecDriver->setFaceAngVelo(AXIS_Y, 70);
}

void VarietyRatislavia001::processBehavior() {
    if (pEnemyRatislaviaEye_) {
        if (pEnemyRatislaviaEye_->is_wake_) {

        } else {
            if (_x - pMYSHIP->_x < PX_C(2000)) {
                pEnemyRatislaviaEye_->wake(); //�������I
            }
        }
    }

    EnemyRatislavia::processBehavior();
}

void VarietyRatislavia001::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == RATISLAVIA_EXPLOSION) {
        _TRACE_(FUNC_NAME<<" RATISLAVIA_EXPLOSION �L���b�`��肱�݁I");
        pEnemyRatislaviaEye_ = nullptr;
    }
    EnemyRatislavia::onCatchEvent(prm_no, prm_pSource);
}

VarietyRatislavia001::~VarietyRatislavia001() {
}
