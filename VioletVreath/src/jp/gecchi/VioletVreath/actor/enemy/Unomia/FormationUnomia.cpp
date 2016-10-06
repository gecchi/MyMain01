#include "FormationUnomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"

#include "jp/ggaf/core/GgafFactory.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia::FormationUnomia(const char* prm_name, const char* prm_spl_id)
   : TreeFormation(prm_name, 20*60) {
    _class_name = "FormationUnomia";

    //スプライン定義ファイルを読み込む
    pConn_pSplManuf_ = connectToSplineManufactureManager(prm_spl_id);
    pDepo_shot_ = getCommonDepository(Shot004);
    updateRankParameter();
    useProgress(PROG_BANPEI);
}

void FormationUnomia::updateRankParameter() {
    num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //編隊列数
    num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //１列の編隊数
    launch_interval_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //ウーノミアの間隔(frame)
    mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //速度
    num_formation_member_ = num_formation_col_*num_formation_row_;
}

void FormationUnomia::initialize() {
    getProgress()->reset(PROG_INIT);
//    if (pConn_depo_Unomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_depo_Unomia_ は、ワシ(this="<<NODE_INFO<<")が育てたエヘン！")
//        getPlatformScene()->bringDirector()->addSubGroup(
//                pConn_depo_Unomia_->peek()->extract()
//                );
//    }
}

void FormationUnomia::onActive() {
    updateRankParameter();
}

void FormationUnomia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
   GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_READY_MEMBER_ORDER: {
            uint64_t order_no = pProg->getFrame();
            orderActorToFactory(order_no, EnemyUnomia, "EnemyUnomia");
            pProg->changeNextWhenArrivedAt(num_formation_member_);
            break;
        }
        case PROG_READY_MEMBER_OBTAIN: {
            uint64_t order_no = pProg->getFrame();
            addFormationMember(obtainActorFromFactory(order_no));
            pProg->changeNextWhenArrivedAt(num_formation_member_);
            break;
        }
        case PROG_CALL_UP: {
            if (canCallUp()) {
                if (getActiveFrame() % launch_interval_ == 0) {
                    for (int col = 0; col < num_formation_col_; col++) {
                        EnemyUnomia* pUnomia = (EnemyUnomia*)callUpMember();
                        if (pUnomia) {
                            SplineKurokoLeader* pKurokoLeader = pConn_pSplManuf_->peek()->
                                                          createKurokoLeader(pUnomia->getKuroko());
                            pUnomia->config(pKurokoLeader, nullptr, nullptr);
                            pUnomia->getKuroko()->setMvVelo(mv_velo_);
                            onCallUpUnomia(pUnomia, col); //フォーメーション個別実装の処理
                        }
                    }
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_WAIT1: {
            pProg->changeNextWhenArrivedAt(1200);
            break;
        }
        case PROG_SHOT: {
            MyShip* pMy = P_MYSHIP;
            GgafActor* pFollower = getSubFirst();
            while(true) {
                EnemyUnomia* pUnomia =  (EnemyUnomia*)pFollower;
                if (pUnomia->isActive()) {
                    GgafDxGeometricActor* pShot = (GgafDxGeometricActor*)pDepo_shot_->dispatch();
                    if (pShot) {
                        pShot->locateAs(pUnomia);
                        GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                        pShot_pKuroko->setMvAngTwd(pMy);
                        pShot_pKuroko->setMvVelo(PX_C(10));
                        pShot_pKuroko->setMvAcce(0);
                    }
                }
                if (pFollower->isLast()) {
                    break;
                }
                pFollower = pFollower->getNext();
            }
            pProg->changeNext();
            break;
        }
        case PROG_WAIT2: {
            //おしまい
            break;
        }
        default :
            break;
    }
}

FormationUnomia::~FormationUnomia() {
    pConn_pSplManuf_->close();
}

