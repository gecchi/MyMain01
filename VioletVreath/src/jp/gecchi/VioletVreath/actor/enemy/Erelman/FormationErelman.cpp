#include "FormationErelman.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/EnemyErelman.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "EnemyErelmanCore.h"
#include "EnemyErelmanController.h"
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

FormationErelman::FormationErelman(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval, EnemyErelmanController* prm_pController) :
        TreeFormation(prm_name) {
    _class_name = "FormationErelman";
    pController_ = prm_pController;
    pXpmConnection_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Erelman_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        addFormationMember(NEW EnemyErelman(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_idx_ = 0;
    useProgress(PROG_BANPEI);
}

FormationErelman::FormationErelman(const char* prm_name, const char* prm_xpm_id, frame prm_call_up_interval, EnemyErelmanController* prm_pController)  :
            TreeFormation(prm_name) {
    _class_name = "FormationErelman";
    pController_ = prm_pController;
    pXpmConnection_ = connectToXpmManager(prm_xpm_id);
    GgafXpm* pXpM = pXpmConnection_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Erelman_ = pXpM->getPixelNum();
    for (int i = 0; i < num_Erelman_; i++) {
        std::string name = "Erelman("+XTOS(i)+")";
        addFormationMember(NEW EnemyErelman(name.c_str()));
        Sleep(1);
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_idx_ = 0;
    useProgress(PROG_BANPEI);
}

void FormationErelman::initialize() {
}

void FormationErelman::onActive() {
    call_up_row_idx_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationErelman::processBehavior() {
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
                                EnemyErelman* pErelman = (EnemyErelman*)callUpMember();
                                if (pErelman) {
                                    onCallUp(pErelman, call_up_row_idx_, col);
                                }
                            }
                        } else {
                            EnemyErelman* pErelman = (EnemyErelman*)callUpMember();
                            if (pErelman) {
                                onCallUp(pErelman, call_up_row_idx_, col);
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

void FormationErelman::scatterMember() {
    EnemyErelman* pErelman = (EnemyErelman*)getSubFirst();
    while (pErelman) {
        pErelman->scatter();
        if (pErelman->isLast()) {
            break;
        } else {
            pErelman = (EnemyErelman*)(pErelman->getNext());
        }
    }
}

void FormationErelman::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}
void FormationErelman::onSayonaraAll() {
    pController_->pFormationErelman_ = nullptr;
}

FormationErelman::~FormationErelman() {
    if (pXpmConnection_) {
        pXpmConnection_->close();
    }
}
