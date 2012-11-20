#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietySylvia001::VarietySylvia001(const char* prm_name) :
        EnemySylvia(prm_name, "Sylvia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietySylvia001";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(60))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (D_ANG(60))) {
            std::string name = "Romulus(" + ITOS(angPos1) + "," + ITOS(angPos2) + ")";
            addSubGroupAsFkOnSurface(NEW EnemyRomulus(name.c_str()), angPos1, angPos2);
            Sleep(1);
        }
    }

    pEnemySylviaEye_ = NEW EnemySylviaEye("EnemySylviaEye", this);
    addSubGroup(pEnemySylviaEye_);
}

void VarietySylvia001::initialize() {
    EnemySylvia::initialize();
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+r1_+r2_;
    _Y = 0;
    _Z = 0;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 60);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 70);
}

void VarietySylvia001::processBehavior() {
    if (pEnemySylviaEye_) {
        if (pEnemySylviaEye_->is_wake_) {

        } else {
            if (_X - P_MYSHIP->_X < PX_C(2000)) {
                pEnemySylviaEye_->wake(); //ぎょろりん！
            }
        }
    }

    EnemySylvia::processBehavior();
}

void VarietySylvia001::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == SYLVIA_EXPLOSION) {
        _TRACE_("VarietySylvia001::onCatchEvent SYLVIA_EXPLOSION キャッチわりこみ！");
        pEnemySylviaEye_ == nullptr;
    }
    EnemySylvia::onCatchEvent(prm_no, prm_pSource);
}

VarietySylvia001::~VarietySylvia001() {
}
