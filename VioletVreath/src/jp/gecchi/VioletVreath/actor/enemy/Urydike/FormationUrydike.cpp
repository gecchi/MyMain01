#include "FormationUrydike.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUrydike::FormationUrydike(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval) :
        TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmConnection_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Urydike_ = prm_formation_col_num  * prm_formation_row_num;
    for (int i = 0; i < num_Urydike_; i++) {
        std::string name = "Urydike("+XTOS(i)+")";
        addFormationMember(NEW EnemyUrydike(name.c_str()));
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_cnt_ = 0;
    useProgress(PROG_BANPEI);
}

FormationUrydike::FormationUrydike(const char* prm_name, const char* prm_xpm_id, frame prm_call_up_interval)  :
            TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmConnection_ = getConnection_XpmManager(prm_xpm_id);
    GgafXpm* pXpM = pXpmConnection_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Urydike_ = pXpM->getPixelNum();
    for (int i = 0; i < num_Urydike_; i++) {
        std::string name = "Urydike("+XTOS(i)+")";
        addFormationMember(NEW EnemyUrydike(name.c_str()));
        Sleep(1);
    }
    call_up_interval_ = prm_call_up_interval; //oŒ»ŠÔŠu
    call_up_row_cnt_ = 0;
    useProgress(PROG_BANPEI);
}

void FormationUrydike::initialize() {
}

void FormationUrydike::onActive() {
    call_up_row_cnt_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationUrydike::processBehavior() {
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
                        if (pXpmConnection_) {
                            //xpm•Ò‘à
                            if (!pXpmConnection_->peek()->isNonColor(call_up_row_cnt_, col)) {
                                EnemyUrydike* pUrydike = (EnemyUrydike*)callUpMember();
                                if (pUrydike) {
                                    onCallUp(pUrydike, call_up_row_cnt_, col);
                                }
                            }
                        } else {
                            EnemyUrydike* pUrydike = (EnemyUrydike*)callUpMember();
                            if (pUrydike) {
                                onCallUp(pUrydike, call_up_row_cnt_, col);
                            }
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

void FormationUrydike::scatterMember() {
    EnemyUrydike* pUrydike = (EnemyUrydike*)getSubFirst();
    while (pUrydike) {
        pUrydike->scatter();
        if (pUrydike->isLast()) {
            break;
        } else {
            pUrydike = (EnemyUrydike*)(pUrydike->getNext());
        }
    }
}

void FormationUrydike::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}
void FormationUrydike::onSayonaraAll() {
}

FormationUrydike::~FormationUrydike() {
    if (pXpmConnection_) {
        pXpmConnection_->close();
    }
}
