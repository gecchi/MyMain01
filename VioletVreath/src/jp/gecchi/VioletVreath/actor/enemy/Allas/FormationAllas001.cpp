#include "FormationAllas001.h"

#include "EnemyAllas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001::FormationAllas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas001";
    num_Allas_       = 0;
    interval_frames_ = 0;
    velo_mv_         = 0;
    //アラス編隊作成
    pConn_pSplManuf_ = connectToSplineManufactureManager("Allas01");
    pConn_depo_ = nullptr;
    useProgress(PROG_BANPEI);
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
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_READY_MEMBER: {
            if (pProg->hasJustChanged()) {
                for (int i = 0; i < num_Allas_; i++) {
                    orderActorToFactory(i, EnemyAllas, "EnemyAllas");
                }
            }
            if (pProg->hasArrivedAt(60)) {
                for (int i = 0; i < num_Allas_; i++) {
                    addFormationMember(obtainActorFromFactory(i));
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
                        pAllas->getKuroko()->setMvVelo(velo_mv_);
                        SplineKurokoLeader* pKurokoLeader = pConn_pSplManuf_->peek()->createKurokoLeader(pAllas->getKuroko());
                        pAllas->config(pKurokoLeader, nullptr, nullptr);
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

void FormationAllas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationAllas001::~FormationAllas001() {
    pConn_pSplManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
}
