#include "stdafx.h"
#include "FormationEunomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/EnemyEunomia.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //エウノミア編隊用デポジトリ
    pDepoConnection_Eunomia_ = connectToDepositoryManager("EnemyEunomia4Formation");
    setFormationMember(pDepoConnection_Eunomia_->peek());

    //スプライン定義ファイルを読み込む
    papSplManufConnection_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        papSplManufConnection_[i] = connectToSplineManufactureManager(spl_id.str().c_str());
    }
    pConne_ShotDepo_ = connectToDepositoryManager("Shot004"); //Eunomiaの弾;
    pDepo_Shot_ = pConne_ShotDepo_->peek();
    updateRankParameter();

}

void FormationEunomia::updateRankParameter() {
    RF_num_formation_col_ = RF_FormationEunomia001_Col(G_RANK);            //編隊列数
    RF_num_formation_row_ = RF_FormationEunomia001_Num(G_RANK);            //１列の編隊数
    RF_interval_frames_   = RF_FormationEunomia001_LaunchInterval(G_RANK); //エウノミアの間隔(frame)
    RF_mv_velo_           = RF_FormationEunomia001_MvVelo(G_RANK);         //速度
}

void FormationEunomia::initialize() {
//    if (pDepoConnection_Eunomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pDepoConnection_Eunomia_ は、ワシ("<<this<<")が育てたエヘン！")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pDepoConnection_Eunomia_->peek()->extract()
//                );
//    }
}

void FormationEunomia::onActive() {
    updateRankParameter();
}

void FormationEunomia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationEunomia::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RF_interval_frames_ == 0)) {
        for (int i = 0; i < RF_num_formation_col_; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpMember(RF_num_formation_col_*RF_num_formation_row_);
            if (pEunomia) {
                SplineKurokoLeader* pKurokoLeader = papSplManufConnection_[i]->peek()->
                                              createKurokoLeader(pEunomia->_pKurokoA);
                pEunomia->config(pKurokoLeader, nullptr, nullptr);
                pEunomia->_pKurokoA->setMvVelo(RF_mv_velo_);
                onCallUpEunomia(pEunomia, i); //フォーメーション個別実装の処理
            }
        }
    }

    if (getActiveFrame() == 60 * 20) {
        MyShip* pMy = P_MYSHIP;
        GgafActor* pFollower = _listFollower.getCurrent();
        int num_follwer = _listFollower.length();
        EnemyEunomia* pEunomia;
        GgafDxGeometricActor* pShot;
        for (int i = 0; i < num_follwer; i++) {
            pEunomia = (EnemyEunomia*)pFollower;
            pShot = (GgafDxGeometricActor*)pDepo_Shot_->dispatch();
            if (pShot) {
                pShot->locateAs(pEunomia);
                pShot->_pKurokoA->setMvAngTwd(pMy);
                pShot->_pKurokoA->setMvVelo(PX_C(10));
                pShot->_pKurokoA->setMvAcce(0);
            }
            pFollower = _listFollower.next();
        }
    }
}

FormationEunomia::~FormationEunomia() {
    pDepoConnection_Eunomia_->close();
    for (int i = 0; i < 7; i++) {
        papSplManufConnection_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConnection_);
    if (pConne_ShotDepo_) {
        pConne_ShotDepo_->close();
    }
}
