#include "FormationThagoras.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/core/util/GgafXpm.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras::FormationThagoras(const char* prm_name,
                                     const char* prm_xpm_id) :
        TreeFormation(prm_name) {
    _class_name = "FormationThagoras";

    pXpmConnection_ = getConnection_XpmManager(prm_xpm_id);
    num_Thagoras_ = getXpm()->getPixelNum();  //ï“ë‡êî
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
        GgafXpm* pXpm = getXpm();
        for (int col = 0; col < pXpm->getWidth(); col++) {
            if (!pXpm->isNonColor(cnt_call_up_row_, col)) {
                EnemyThagoras* pThagoras = (EnemyThagoras*)callUpMember();
                if (pThagoras) {
                    onCallUp(pThagoras, cnt_call_up_row_, col);
                }
                pThagoras->setMaterialColor(pXpm->getColor(cnt_call_up_row_, col));
            }
        }
        cnt_call_up_row_++;
    }
    pScaler_->behave();
}

void FormationThagoras::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

GgafXpm* FormationThagoras::getXpm() {
    return pXpmConnection_->peek();
}

FormationThagoras::~FormationThagoras() {
    pXpmConnection_->close();
    GGAF_DELETE(pScaler_);
    GGAF_DELETE(pActor4Sc_);
}
