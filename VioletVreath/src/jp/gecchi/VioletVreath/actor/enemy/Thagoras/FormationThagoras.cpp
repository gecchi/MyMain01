#include "FormationThagoras.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras::FormationThagoras(const char* prm_name,
                                     const char** prm_xpm) :
        TreeFormation(prm_name) {
    _class_name = "FormationThagoras";
    xpm_ = prm_xpm;
    pXpmHd_ = NEW XpmHeader(xpm_);
    num_Thagoras_ = pXpmHd_->num_color_pixels_;  //ï“ë‡êî

    for (int i = 0; i < num_Thagoras_; i++) {
        std::string name = "Thagoras("+XTOS(i)+")";
        addFormationMember(NEW EnemyThagoras(name.c_str()));
    }

    cnt_call_up_row_ = 0;
    call_up_interval_ = 20;

    pActor4Sc_ = NEW DefaultGeometricActor("Actor4Sc");
    pScaler_ = NEW GgafDxScaler(pActor4Sc_);

}
void FormationThagoras::initialize() {
    pScaler_->forceRange(R_SC(1.0), R_SC(2.0));
    pScaler_->beat(50, 10, 0, 40, -1);
}

void FormationThagoras::onActive() {
}

void FormationThagoras::processBehavior() {
    if (canCallUp() && getActiveFrame() % call_up_interval_ == 0) {
        int xpm_cols = pXpmHd_->columns_;
        for (int col = 0; col < xpm_cols; col++) {
            char c = pXpmHd_->pixels_[cnt_call_up_row_][col];
            if (c != pXpmHd_->c_px_non_) {
                EnemyThagoras* pThagoras = (EnemyThagoras*)callUpMember();
                if (pThagoras) {
                    onCallUp(pThagoras, cnt_call_up_row_, col);
                }
                pThagoras->setMaterialColor(pXpmHd_->c_rgb_[c]);
            }
        }
        cnt_call_up_row_++;
    }
    pScaler_->behave();
}

void FormationThagoras::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationThagoras::~FormationThagoras() {
    GGAF_DELETE(pScaler_);
    GGAF_DELETE(pActor4Sc_);
    GGAF_DELETE(pXpmHd_);
}
