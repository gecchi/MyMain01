#include "FormationThagoras.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/core/util/Xpm.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras::FormationThagoras(const char* prm_name,
                                     const char* prm_xpm_id) :
        VvFormationActor<TreeFormation>(prm_name) {
    _class_name = "FormationThagoras";

    pXpmCon_ = connectToXpmManager(prm_xpm_id);
    for (int i = 0; i < getXpm()->getPixelNum(); i++) {
        std::string name = "Thagoras("+XTOS(i)+")";
        appendFormationMember(NEW EnemyThagoras(name.c_str()));
    }

    cnt_called_up_row_ = 0;
    called_up_interval_ = 20;

    pActor4Sc_ = NEW DefaultGeometricActor("Actor4Sc");
    pScaler4Sc_ = NEW GgafDx::Scaler(pActor4Sc_);

}
void FormationThagoras::initialize() {
    pScaler4Sc_->setRange(R_SC(1.0), R_SC(2.0));
    pScaler4Sc_->beat(50, 10, 0, 40, -1);
}

void FormationThagoras::onActive() {
}

void FormationThagoras::processBehavior() {
    if (canCalledUp() && getActiveFrame() % called_up_interval_ == 0) {
        GgafCore::Xpm* pXpm = getXpm();
        for (int col = 0; col < pXpm->getWidth(); col++) {
            if (!pXpm->isNonColor(cnt_called_up_row_, col)) {
                EnemyThagoras* pThagoras = (EnemyThagoras*)calledUpMember();
                if (pThagoras) {
                    onCalledUp(pThagoras, cnt_called_up_row_, col);
                }
                pThagoras->setMaterialColor(pXpm->getColor(cnt_called_up_row_, col));
            }
        }
        cnt_called_up_row_++;
    }
    pScaler4Sc_->behave();
}

GgafCore::Xpm* FormationThagoras::getXpm() {
    return pXpmCon_->peek();
}

FormationThagoras::~FormationThagoras() {
    pXpmCon_->close();
    GGAF_DELETE(pScaler4Sc_);
    GGAF_DELETE(pActor4Sc_);
}
