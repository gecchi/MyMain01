#include "FormationAllas001.h"

#include "EnemyAllas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_CALL_UP ,
    PHASE_WAIT  ,
    PHASE_BANPEI,
};

FormationAllas001::FormationAllas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas001";
    num_Allas_       = 0;
    interval_frames_ = 0;
    velo_mv_         = 0;

    pConn_pCurveManuf_ = connectToCurveManufactureManager("Allas01");
    //アラス編隊作成
    int max_num_Allas = RF_FormationAllas001_Num(G_MAX_RANK);
    for (int i = 0; i < max_num_Allas; i++) {
        EnemyAllas* pAllas_ = NEW EnemyAllas("Allas01");
        appendFormationMember(pAllas_);
    }
    pConn_depo_ = nullptr;
}

void FormationAllas001::initialize() {
    getPhase()->reset(PHASE_INIT);
}

void FormationAllas001::onActive() {
    num_Allas_       = RF_FormationAllas001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAllas001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    velo_mv_         = RF_FormationAllas001_MvVelo(G_RANK); //速度
}

void FormationAllas001::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_CALL_UP: {
            if (pPhase->hasJustChanged()) {

            }
            if (canCalledUp()) {
                if (getActiveFrame() % interval_frames_ == 0) {
                    EnemyAllas* pAllas = (EnemyAllas*)calledUpMember(num_Allas_);
                    if (pAllas) {
                        pAllas->getLocoVehicle()->setMvVelo(velo_mv_);
                        pAllas->config(pConn_pCurveManuf_->peek(), nullptr, nullptr);
                        onCalledUpAllas(pAllas);
                    }
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

void FormationAllas001::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationAllas001::~FormationAllas001() {
    pConn_pCurveManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
}
