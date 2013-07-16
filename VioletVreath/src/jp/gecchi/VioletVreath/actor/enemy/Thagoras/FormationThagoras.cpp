#include "stdafx.h"
#include "FormationThagoras.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/gecchi/VioletVreath/God.h"


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
    num_Thagoras_ = pXpmHd_->columns_ * pXpmHd_->rows_;  //ï“ë‡êî

    for (int i = 0; i < num_Thagoras_; i++) {
        std::string name = "Thagoras("+XTOS(i)+")";
        addFormationMember(NEW EnemyThagoras(name.c_str()));
    }

    cnt_call_up_row_ = 0;
    call_up_interval_ = 8;
}
void FormationThagoras::initialize() {
}

void FormationThagoras::onActive() {
}

void FormationThagoras::processBehavior() {
    if (cnt_call_up_row_ < pXpmHd_->rows_ && canCallUp() && getActiveFrame() % call_up_interval_ == 0) {

        for (int col = 0; col < pXpmHd_->columns_; col++) {
            char x = pXpmHd_->pixels_[cnt_call_up_row_][col];
            if (x != pXpmHd_->c_px_non_) {
                EnemyThagoras* pThagoras = (EnemyThagoras*)callUpMember();
                if (pThagoras) {
                    onCallUp(pThagoras, cnt_call_up_row_, col);
                }
                GgafRgb* pRgb = pXpmHd_->c_rgb_[x];
                pThagoras->setMaterialColor(pRgb->_r, pRgb->_g, pRgb->_b);
            } else {
            }
        }
        cnt_call_up_row_++;
    }
}

void FormationThagoras::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationThagoras::~FormationThagoras() {
    GGAF_DELETE(pXpmHd_);
}
