#include "FormationOebius.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/EnemyOebius.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOebius::FormationOebius(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval) :
        TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    pXpmConnection_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Oebius_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        addFormationMember(NEW EnemyOebius(name.c_str()));
    }

    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_cnt_ = 0;

    last_average_mv_velo_ = 1000;
}

FormationOebius::FormationOebius(const char* prm_name, const char* prm_xpm_id, frame prm_call_up_interval)  :
            TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    pXpmConnection_ = getConnection_XpmManager(prm_xpm_id);
    GgafXpm* pXpM = pXpmConnection_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Oebius_ = pXpM->getPixelNum();
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        addFormationMember(NEW EnemyOebius(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_cnt_ = 0;
}

void FormationOebius::initialize() {
}

void FormationOebius::onActive() {
    call_up_row_cnt_ = 0;
}

void FormationOebius::processBehavior() {
    if (canCallUp()) {
        if (getActiveFrame() % call_up_interval_ == 0) {
            for (int col = 0; col < formation_col_num_; col++) {
                if (pXpmConnection_) {
                    if (!pXpmConnection_->peek()->isNonColor(call_up_row_cnt_, col)) {
                        EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                        if (pOebius) {
                            onCallUp(pOebius, call_up_row_cnt_, col);
                        }
                    }
                } else {
                    EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                    if (pOebius) {
                        onCallUp(pOebius, call_up_row_cnt_, col);
                    }
                }
            }
            call_up_row_cnt_ ++;
        }
    }
}

void FormationOebius::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationOebius::~FormationOebius() {
    if (pXpmConnection_) {
        pXpmConnection_->close();
    }
}
