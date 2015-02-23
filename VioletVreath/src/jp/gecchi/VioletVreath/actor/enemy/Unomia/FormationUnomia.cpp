#include "FormationUnomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

#include "jp/ggaf/core/GgafFactory.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia::FormationUnomia(const char* prm_name, const char* prm_spl_id)
   : TreeFormation(prm_name, 20*60) {
    _class_name = "FormationUnomia";

    //スプライン定義ファイルを読み込む
    pConn_pSplManuf_ = getConnection_SplineManufactureManager(prm_spl_id);
    pDepo_shot_ = getCommonDepository(Shot004);
    updateRankParameter();
    useProgress(PROG_BANPEI);
}

void FormationUnomia::updateRankParameter() {
    RF_num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //編隊列数
    RF_num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //１列の編隊数
    RF_interval_frames_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //ウーノミアの間隔(frame)
    RF_mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //速度
}

void FormationUnomia::initialize() {
    getProgress()->reset(PROG_INIT);
//    if (pConn_depo_Unomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_depo_Unomia_ は、ワシ("<<this<<")が育てたエヘン！")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pConn_depo_Unomia_->peek()->extract()
//                );
//    }
}

void FormationUnomia::onActive() {
    updateRankParameter();
}

void FormationUnomia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::transactFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
   GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_READY_MEMBER: {
            if (pProg->isJustChanged()) {
                for (int i = 0; i < RF_num_formation_col_*RF_num_formation_row_; i++) {
                    orderActorToFactory(getId()*10000 + i, EnemyUnomia, "EnemyUnomia");
                }
            }
            if (pProg->getFrameInProgress() == 120) {
                for (int i = 0; i < RF_num_formation_col_*RF_num_formation_row_; i++) {
                    addFormationMember(obtainActorFromFactory(getId()*10000 + i));
                }
                pProg->changeNext();
            }
            break;
        }
        case PROG_CALL_UP: {
            if (pProg->isJustChanged()) {

            }
            if (canCallUp()) {
                if (getActiveFrame() % RF_interval_frames_ == 0) {
                    for (int col = 0; col < RF_num_formation_col_; col++) {
                        EnemyUnomia* pUnomia = (EnemyUnomia*)callUpMember();
                        if (pUnomia) {
                            SplineKurokoLeader* pKurokoLeader = pConn_pSplManuf_->peek()->
                                                          createKurokoLeader(pUnomia->getKuroko());
                            pUnomia->config(pKurokoLeader, nullptr, nullptr);
                            pUnomia->getKuroko()->setMvVelo(RF_mv_velo_);
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
            if (pProg->getFrameInProgress() == 60*20) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_SHOT: {
            if (pProg->isJustChanged()) {
                MyShip* pMy = P_MYSHIP;
                GgafActor* pFollower = getSubFirst();
                while(true) {
                    EnemyUnomia* pUnomia =  (EnemyUnomia*)pFollower;
                    if (pUnomia->isActive()) {
                        GgafDxGeometricActor* pShot = (GgafDxGeometricActor*)pDepo_shot_->dispatch();
                        if (pShot) {
                            pShot->positionAs(pUnomia);
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
            }
            pProg->changeNext();
            break;
        }
        case PROG_WAIT2: {
            if (pProg->isJustChanged()) {
            }
            break;
        }
        default :
            break;
    }
}

FormationUnomia::~FormationUnomia() {
    pConn_pSplManuf_->close();
}
