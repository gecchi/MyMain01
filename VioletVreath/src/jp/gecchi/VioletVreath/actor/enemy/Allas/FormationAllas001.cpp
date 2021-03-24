#include "FormationAllas001.h"

#include "EnemyAllas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_READY_MEMBER,
    PROG_CALL_UP ,
    PROG_WAIT  ,
    PROG_BANPEI,
};

FormationAllas001::FormationAllas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas001";
    num_Allas_       = 0;
    interval_frames_ = 0;
    velo_mv_         = 0;
    //アラス編隊作成
    pConn_pSplManuf_ = connectToSplineManufactureManager("Allas01");
    pConn_depo_ = nullptr;
}

void FormationAllas001::initialize() {
    getProgress()->reset(PROG_INIT);
}

void FormationAllas001::onActive() {
    num_Allas_       = RF_FormationAllas001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAllas001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    velo_mv_         = RF_FormationAllas001_MvVelo(G_RANK); //速度
}

void FormationAllas001::processBehavior() {
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_READY_MEMBER: {
            if (pProg->hasJustChanged()) {
                for (int i = 0; i < num_Allas_; i++) {
                    requestActor(i, EnemyAllas, "EnemyAllas");
                }
            }
            if (pProg->hasArrivedAt(60)) {
                for (int i = 0; i < num_Allas_; i++) {
                    appendFormationMember(receiveActor(i));
                }
                pProg->changeNext();
            }
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->hasJustChanged()) {

            }
            if (canCallUp()) {
                if (getActiveFrame() % interval_frames_ == 0) {
                    EnemyAllas* pAllas = (EnemyAllas*)callUpMember();
                    if (pAllas) {
                        pAllas->callVecDriver()->setMvVelo(velo_mv_);
                        SplineLeader* pVecDriverLeader = pConn_pSplManuf_->peek()->createVecDriverLeader(pAllas->callVecDriver());
                        pAllas->config(pVecDriverLeader, nullptr, nullptr);
                        onCallUpAllas(pAllas);
                    }
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

void FormationAllas001::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationAllas001::~FormationAllas001() {
    pConn_pSplManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
}
