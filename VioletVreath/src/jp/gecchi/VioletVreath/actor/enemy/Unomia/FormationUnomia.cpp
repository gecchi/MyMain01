#include "FormationUnomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia::FormationUnomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationUnomia";

    //ウーノミア編隊用デポジトリ
    pConn_depo_Unomia_ = getConnection_DepositoryManager("EnemyUnomia4Formation");
    setFormationMember(pConn_depo_Unomia_->peek());

    //スプライン定義ファイルを読み込む
    papConn_pSplManuf_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationUnomia001_0"
        papConn_pSplManuf_[i] = getConnection_SplineManufactureManager(spl_id.str().c_str());
    }
    pDepo_shot_ = getCommonDepository(Shot004);
    updateRankParameter();

}

void FormationUnomia::updateRankParameter() {
    RF_num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //編隊列数
    RF_num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //１列の編隊数
    RF_interval_frames_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //ウーノミアの間隔(frame)
    RF_mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //速度
}

void FormationUnomia::initialize() {
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
    UTIL::transactFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RF_interval_frames_ == 0)) {
        for (int i = 0; i < RF_num_formation_col_; i++) {
            EnemyUnomia* pUnomia = (EnemyUnomia*)callUpMember(RF_num_formation_col_*RF_num_formation_row_);
            if (pUnomia) {
                SplineKurokoLeader* pKurokoLeader = papConn_pSplManuf_[i]->peek()->
                                              createKurokoLeader(pUnomia->getKuroko());
                pUnomia->config(pKurokoLeader, nullptr, nullptr);
                pUnomia->getKuroko()->setMvVelo(RF_mv_velo_);
                onCallUpUnomia(pUnomia, i); //フォーメーション個別実装の処理
            }
        }
    }

    if (getActiveFrame() == 60 * 20) {
        MyShip* pMy = P_MYSHIP;
        GgafActor* pFollower = _listFollower.getCurrent();
        int num_follwer = _listFollower.length();
        EnemyUnomia* pUnomia;
        GgafDxGeometricActor* pShot;
        for (int i = 0; i < num_follwer; i++) {
            pUnomia = (EnemyUnomia*)pFollower;
            pShot = (GgafDxGeometricActor*)pDepo_shot_->dispatch();
            if (pShot) {
                pShot->positionAs(pUnomia);
                GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                pShot_pKuroko->setMvAngTwd(pMy);
                pShot_pKuroko->setMvVelo(PX_C(10));
                pShot_pKuroko->setMvAcce(0);
            }
            pFollower = _listFollower.next();
        }
    }
}

FormationUnomia::~FormationUnomia() {
    pConn_depo_Unomia_->close();
    for (int i = 0; i < 7; i++) {
        papConn_pSplManuf_[i]->close();
    }
    GGAF_DELETEARR(papConn_pSplManuf_);
}
