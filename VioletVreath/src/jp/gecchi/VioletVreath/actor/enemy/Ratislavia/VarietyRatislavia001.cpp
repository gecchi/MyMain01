#include "VarietyRatislavia001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Omulus/EnemyOmulus.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEye.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyRatislavia001::VarietyRatislavia001(const char* prm_name) :
        EnemyRatislavia(prm_name, "Ratislavia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietyRatislavia001";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(60))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (D_ANG(60))) {
            std::string name = "Omulus(" + XTOS(angPos1) + "," + XTOS(angPos2) + ")";
            addSubGroupAsFkOnSurface(NEW EnemyOmulus(name.c_str()), angPos1, angPos2);
            Sleep(1);
        }
    }

    pEnemyRatislaviaEye_ = NEW EnemyRatislaviaEye("EnemyRatislaviaEye", this);
    addSubGroup(pEnemyRatislaviaEye_);
}

void VarietyRatislavia001::initialize() {
    EnemyRatislavia::initialize();
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    _x = pSpacetime->_x_gone_right + r1_ + r2_;
    _y = 0;
    _z = 0;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRzRyMvAng(D180ANG, 0);
    pKuroko->setMvVelo(2000);
    pKuroko->setFaceAngVelo(AXIS_Z, 60);
    pKuroko->setFaceAngVelo(AXIS_Y, 70);
}

void VarietyRatislavia001::processBehavior() {
    if (pEnemyRatislaviaEye_) {
        if (pEnemyRatislaviaEye_->is_wake_) {

        } else {
            if (_x - P_MYSHIP->_x < PX_C(2000)) {
                pEnemyRatislaviaEye_->wake(); //ぎょろりん！
            }
        }
    }

    EnemyRatislavia::processBehavior();
}

void VarietyRatislavia001::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == RATISLAVIA_EXPLOSION) {
        _TRACE_("VarietyRatislavia001::onCatchEvent RATISLAVIA_EXPLOSION キャッチわりこみ！");
        pEnemyRatislaviaEye_ = nullptr;
    }
    EnemyRatislavia::onCatchEvent(prm_no, prm_pSource);
}

VarietyRatislavia001::~VarietyRatislavia001() {
}
