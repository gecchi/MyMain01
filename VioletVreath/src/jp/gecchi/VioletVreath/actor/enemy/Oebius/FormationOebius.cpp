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
#include "EnemyOebiusCore.h"
#include "EnemyOebiusController.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};

FormationOebius::FormationOebius(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval, EnemyOebiusController* prm_pController) :
        TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    pController_ = prm_pController;
    pXpmConnection_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Oebius_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        addFormationMember(NEW EnemyOebius(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_idx_ = 0;
    useProgress(PROG_BANPEI);
}

FormationOebius::FormationOebius(const char* prm_name, const char* prm_xpm_id, frame prm_call_up_interval, EnemyOebiusController* prm_pController)  :
            TreeFormation(prm_name) {
    _class_name = "FormationOebius";
    pController_ = prm_pController;
    pXpmConnection_ = connectToXpmManager(prm_xpm_id);
    GgafXpm* pXpM = pXpmConnection_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Oebius_ = pXpM->getPixelNum();
    for (int i = 0; i < num_Oebius_; i++) {
        std::string name = "Oebius("+XTOS(i)+")";
        addFormationMember(NEW EnemyOebius(name.c_str()));
        Sleep(1);
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_idx_ = 0;
    useProgress(PROG_BANPEI);
}

void FormationOebius::initialize() {
}

void FormationOebius::onActive() {
    call_up_row_idx_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationOebius::processBehavior() {
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {
            }
            if (canCallUp() && call_up_row_idx_ < formation_row_num_) {
                if (getActiveFrame() % call_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        if (pXpmConnection_) {
                            //xpm•Ò‘à
                            if (!pXpmConnection_->peek()->isNonColor(call_up_row_idx_, col)) {
                                EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                                if (pOebius) {
                                    onCallUp(pOebius, call_up_row_idx_, col);
                                }
                            }
                        } else {
                            EnemyOebius* pOebius = (EnemyOebius*)callUpMember();
                            if (pOebius) {
                                onCallUp(pOebius, call_up_row_idx_, col);
                            }
                        }
                    }
                    call_up_row_idx_ ++;
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_WAIT: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

void FormationOebius::scatterMember() {
    EnemyOebius* pOebius = (EnemyOebius*)getSubFirst();
    while (pOebius) {
        pOebius->scatter();
        if (pOebius->isLast()) {
            break;
        } else {
            pOebius = (EnemyOebius*)(pOebius->getNext());
        }
    }
}

void FormationOebius::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}
void FormationOebius::onSayonaraAll() {
    pController_->pFormationOebius_ = nullptr;
}

FormationOebius::~FormationOebius() {
    if (pXpmConnection_) {
        pXpmConnection_->close();
    }
}
