#include "FormationParaCurve.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "Zako.h"



using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_INIT  ,
    PHASE_CALL_UP ,
    PHASE_WAIT  ,
    PHASE_BANPEI,
};

FormationParaCurve::FormationParaCurve(const char* prm_name) :
        FkFormation(prm_name) {
    _class_name = "FormationParaCurve";
    formation_col_num_ = 0;
    formation_row_num_ = 0;
    num_Zako_ = 0;
    called_up_interval_ = 0;
    called_up_row_idx_ = 0;
}

void FormationParaCurve::addMember(int prm_formation_col_num, int prm_formation_row_num, frame prm_called_up_interval) {
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Zako_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Zako_; i++) {
        std::string name = "Zako("+XTOS(i)+")";
//        appendFormationMember(NEW Zako(name.c_str()));
    }
    called_up_interval_ = prm_called_up_interval; //oŒ»ŠÔŠu
    called_up_row_idx_ = 0;
}
void FormationParaCurve::initialize() {
}

void FormationParaCurve::onActive() {
    called_up_row_idx_ = 0;
    getPhase()->reset(PHASE_INIT);
}

void FormationParaCurve::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_CALL_UP: {
            if (pPhase->hasJustChanged()) {
            }
            if (formation_row_num_ > called_up_row_idx_ && canCalledUp()) {
                if (getActiveFrame() % called_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        Zako* pZako = (Zako*)calledUpMember();
                        if (pZako) {
                            onCalledUp(pZako, called_up_row_idx_, col);
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

void FormationParaCurve::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
}

void FormationParaCurve::onSayonaraAll() {
}

FormationParaCurve::~FormationParaCurve() {
}
