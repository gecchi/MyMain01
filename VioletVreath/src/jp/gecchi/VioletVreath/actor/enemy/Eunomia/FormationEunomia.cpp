#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //エウノミア編隊用デポジトリ
    pDepoConnection_Eunomia_ = connectToDepositoryManager("EnemyEunomia4Formation");
    setFormationMemberDepo(pDepoConnection_Eunomia_->peek());

    //スプライン定義ファイルを読み込む
    papSplManufConnection_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        papSplManufConnection_[i] = connectToSplineManufactureManager(spl_id.str().c_str());
    }
    pConnection_ShotDepo_ = connectToDepositoryManager("Shot004"); //Eunomiaの弾;
    pDepo_Shot_ = pConnection_ShotDepo_->peek();
    updateRankParameter();

}

void FormationEunomia::updateRankParameter() {
    RR_num_formation_col_ = RR_FormationEunomia001_Col(_RANK_);            //編隊列数
    RR_num_formation_row_ = RR_FormationEunomia001_Num(_RANK_);            //１列の編隊数
    RR_interval_frames_   = RR_FormationEunomia001_LaunchInterval(_RANK_); //エウノミアの間隔(frame)
    RR_mv_velo_           = RR_FormationEunomia001_MvVelo(_RANK_);         //速度
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
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

void FormationEunomia::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RR_interval_frames_ == 0)) {
        for (int i = 0; i < RR_num_formation_col_; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpMember(RR_num_formation_col_*RR_num_formation_row_);
            if (pEunomia) {
                SplineKurokoLeader* pKurokoLeader = papSplManufConnection_[i]->peek()->
                                              createKurokoLeader(pEunomia->_pKurokoA);
                pEunomia->config(pKurokoLeader, nullptr, nullptr);
                pEunomia->_pKurokoA->setMvVelo(RR_mv_velo_);
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
    if (pConnection_ShotDepo_) {
        pConnection_ShotDepo_->close();
    }
}
