#include "FormationUrydike.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_READY_MEMBER,
    PHASE_CALL_UP ,
    PHASE_WAIT  ,
    PHASE_BANPEI,
};

FormationUrydike::FormationUrydike(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_called_up_interval) :
        TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmCon_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Urydike_ = prm_formation_col_num  * prm_formation_row_num;
    called_up_interval_ = prm_called_up_interval; //oŒ»ŠÔŠu
    called_up_row_idx_ = 0;
}

FormationUrydike::FormationUrydike(const char* prm_name, const char* prm_xpm_id, frame prm_called_up_interval)  :
            TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmCon_ = connectToXpmManager(prm_xpm_id);
    GgafCore::Xpm* pXpM = pXpmCon_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Urydike_ = pXpM->getPixelNum();
    called_up_interval_ = prm_called_up_interval; //oŒ»ŠÔŠu
    called_up_row_idx_ = 0;
}

void FormationUrydike::initialize() {
}

void FormationUrydike::onActive() {
    called_up_row_idx_ = 0;
    getPhase()->reset(PHASE_INIT);
}

void FormationUrydike::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_READY_MEMBER: {
            if (pPhase->hasJustChanged()) {
                for (int i = 0; i < num_Urydike_; i++) {
                    requestActor(i, EnemyUrydike, "EnemyUrydike");
                }
            }
            if (pPhase->hasArrivedFrameAt(120)) {
                for (int i = 0; i < num_Urydike_; i++) {
                    appendFormationMember(receiveActor(i));
                }
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_CALL_UP: {
            if (pPhase->hasJustChanged()) {

            }
            if (canCalledUp() && called_up_row_idx_ < formation_row_num_) {
                if (getActiveFrame() % called_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        if (pXpmCon_) {
                            //xpm•Ò‘à
                            if (!pXpmCon_->peek()->isNonColor(called_up_row_idx_, col)) {
                                EnemyUrydike* pUrydike = (EnemyUrydike*)calledUpMember();
                                if (pUrydike) {
                                    onCalledUp(pUrydike, called_up_row_idx_, col);
                                }
                            }
                        } else {
                            EnemyUrydike* pUrydike = (EnemyUrydike*)calledUpMember();
                            if (pUrydike) {
                                onCalledUp(pUrydike, called_up_row_idx_, col);
                            }
                        }
                    }
                    called_up_row_idx_ ++;
                }
            } else {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_WAIT: {
            if (pPhase->hasJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

void FormationUrydike::scatterMember() {
    EnemyUrydike* pUrydike = (EnemyUrydike*)getChildFirst();
    while (pUrydike) {
        pUrydike->scatter();
        if (pUrydike->isLast()) {
            break;
        } else {
            pUrydike = (EnemyUrydike*)(pUrydike->getNext());
        }
    }
}

void FormationUrydike::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

void FormationUrydike::onSayonaraAll() {
}

FormationUrydike::~FormationUrydike() {
    if (pXpmCon_) {
        pXpmCon_->close();
    }
}
