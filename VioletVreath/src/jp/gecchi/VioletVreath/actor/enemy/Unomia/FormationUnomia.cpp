#include "stdafx.h"
#include "FormationUnomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
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
    pDepoConnection_Unomia_ = connect_DepositoryManager("EnemyUnomia4Formation");
    setFormationMember(pDepoConnection_Unomia_->peek());

    //スプライン定義ファイルを読み込む
    papSplManufConnection_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationUnomia001_0"
        papSplManufConnection_[i] = connect_SplineManufactureManager(spl_id.str().c_str());
    }
    pDepo_Shot_ = getCommonDepository(Shot004);
    updateRankParameter();

}

void FormationUnomia::updateRankParameter() {
    RF_num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //編隊列数
    RF_num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //１列の編隊数
    RF_interval_frames_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //ウーノミアの間隔(frame)
    RF_mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //速度
}

void FormationUnomia::initialize() {
//    if (pDepoConnection_Unomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pDepoConnection_Unomia_ は、ワシ("<<this<<")が育てたエヘン！")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pDepoConnection_Unomia_->peek()->extract()
//                );
//    }
}

void FormationUnomia::onActive() {
    updateRankParameter();
}

void FormationUnomia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RF_interval_frames_ == 0)) {
        for (int i = 0; i < RF_num_formation_col_; i++) {
            EnemyUnomia* pUnomia = (EnemyUnomia*)callUpMember(RF_num_formation_col_*RF_num_formation_row_);
            if (pUnomia) {
                SplineKurokoLeader* pKurokoLeader = papSplManufConnection_[i]->peek()->
                                              createKurokoLeader(pUnomia->_pKurokoA);
                pUnomia->config(pKurokoLeader, nullptr, nullptr);
                pUnomia->_pKurokoA->setMvVelo(RF_mv_velo_);
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
            pShot = (GgafDxGeometricActor*)pDepo_Shot_->dispatch();
            if (pShot) {
                pShot->positionAs(pUnomia);
                pShot->_pKurokoA->setMvAngTwd(pMy);
                pShot->_pKurokoA->setMvVelo(PX_C(10));
                pShot->_pKurokoA->setMvAcce(0);
            }
            pFollower = _listFollower.next();
        }
    }
}

FormationUnomia::~FormationUnomia() {
    pDepoConnection_Unomia_->close();
    for (int i = 0; i < 7; i++) {
        papSplManufConnection_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConnection_);
}
