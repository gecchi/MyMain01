#include "FormationParaCurve.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "Zako.h"



using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT  ,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};

FormationParaCurve::FormationParaCurve(const char* prm_name) :
        FkFormation(prm_name) {
    _class_name = "FormationParaCurve";
    formation_col_num_ = 0;
    formation_row_num_ = 0;
    num_Zako_ = 0;
    call_up_interval_ = 0;
    call_up_row_idx_ = 0;
}

void FormationParaCurve::addMember(int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval) {
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Zako_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Zako_; i++) {
        std::string name = "Zako("+XTOS(i)+")";
//        appendFormationMember(NEW Zako(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //�o���Ԋu
    call_up_row_idx_ = 0;
}
void FormationParaCurve::initialize() {
}

void FormationParaCurve::onActive() {
    call_up_row_idx_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationParaCurve::processBehavior() {
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {
            }
            if (formation_row_num_ > call_up_row_idx_ && canCallUp()) {
                if (getActiveFrame() % call_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        Zako* pZako = (Zako*)callUpMember();
                        if (pZako) {
                            onCallUp(pZako, call_up_row_idx_, col);
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

void FormationParaCurve::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
}

void FormationParaCurve::onSayonaraAll() {
}

FormationParaCurve::~FormationParaCurve() {
}