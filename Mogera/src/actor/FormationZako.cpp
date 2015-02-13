#include <actor/FormationZako.h>

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include <actor/Zako.h>
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

FormationZako::FormationZako(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationZako";
    formation_col_num_ = 0;
    formation_row_num_ = 0;
    num_Zako_ = 0;
    call_up_interval_ = 0;
    call_up_row_cnt_ = 0;
    useProgress(PROG_BANPEI);
}

void FormationZako::createMember(int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval) {
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Zako_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Zako_; i++) {
        std::string name = "Zako("+XTOS(i)+")";
        addFormationMember(NEW Zako(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_cnt_ = 0;
}
void FormationZako::initialize() {
}

void FormationZako::onActive() {
    call_up_row_cnt_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationZako::processBehavior() {
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->isJustChanged()) {
            }
            if (canCallUp()) {
                if (getActiveFrame() % call_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        Zako* pZako = (Zako*)callUpMember();
                        if (pZako) {
                            onCallUp(pZako, call_up_row_cnt_, col);
                        }
                    }
                    call_up_row_cnt_ ++;
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_WAIT: {
            if (pProg->isJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

void FormationZako::scatterMember() {
    Zako* pZako = (Zako*)getSubFirst();
    while (pZako) {
        pZako->scatter();
        if (pZako->isLast()) {
            break;
        } else {
            pZako = (Zako*)(pZako->getNext());
        }
    }
}

void FormationZako::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
}

void FormationZako::onSayonaraAll() {
}

FormationZako::~FormationZako() {
}
