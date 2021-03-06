#include "FormationUrydike.h"

#include "jp/ggaf/core/util/Rgb.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/EnemyUrydike.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_READY_MEMBER,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};

FormationUrydike::FormationUrydike(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_called_up_interval) :
        TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmConnection_ = nullptr;
    formation_col_num_ = prm_formation_col_num;
    formation_row_num_ = prm_formation_row_num;
    num_Urydike_ = prm_formation_col_num  * prm_formation_row_num;
    called_up_interval_ = prm_called_up_interval; //�o���Ԋu
    called_up_row_idx_ = 0;
}

FormationUrydike::FormationUrydike(const char* prm_name, const char* prm_xpm_id, frame prm_called_up_interval)  :
            TreeFormation(prm_name) {
    _class_name = "FormationUrydike";
    pXpmConnection_ = connectToXpmManager(prm_xpm_id);
    GgafCore::Xpm* pXpM = pXpmConnection_->peek();
    formation_col_num_ = pXpM->getWidth();
    formation_row_num_ = pXpM->getHeight();
    num_Urydike_ = pXpM->getPixelNum();
    called_up_interval_ = prm_called_up_interval; //�o���Ԋu
    called_up_row_idx_ = 0;
}

void FormationUrydike::initialize() {
}

void FormationUrydike::onActive() {
    called_up_row_idx_ = 0;
    getProgress()->reset(PROG_INIT);
}

void FormationUrydike::processBehavior() {
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_READY_MEMBER: {
            if (pProg->hasJustChanged()) {
                for (int i = 0; i < num_Urydike_; i++) {
                    requestActor(i, EnemyUrydike, "EnemyUrydike");
                }
            }
            if (pProg->hasArrivedAt(120)) {
                for (int i = 0; i < num_Urydike_; i++) {
                    appendFormationMember(receiveActor(i));
                }
                pProg->changeNext();
            }
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {

            }
            if (canCalledUp() && called_up_row_idx_ < formation_row_num_) {
                if (getActiveFrame() % called_up_interval_ == 0) {
                    for (int col = 0; col < formation_col_num_; col++) {
                        if (pXpmConnection_) {
                            //xpm�ґ�
                            if (!pXpmConnection_->peek()->isNonColor(called_up_row_idx_, col)) {
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
    if (pXpmConnection_) {
        pXpmConnection_->close();
    }
}
