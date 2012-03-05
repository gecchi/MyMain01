#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //エウノミア編隊用デポジトリ
    pDepoCon_Eunomia_ = connectToDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setFormationAbleActorDepository(pDepoCon_Eunomia_->use());

    //スプライン定義ファイルを読み込む
    papSplManufCon_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //＜例＞"FormationEunomia001_0"
        papSplManufCon_[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }
    pDepoCon_Shot_ = NULL;
    updateRankParameter();
}

void FormationEunomia::updateRankParameter() {
    R_num_formation_col_ = R_FormationEunomia001_Col;            //編隊列数
    R_num_formation_row_ = R_FormationEunomia001_Num;            //１列の編隊数
    R_interval_frames_   = R_FormationEunomia001_LaunchInterval; //エウノミアの間隔(frame)
    R_mv_velo_           = R_FormationEunomia001_MvVelo;         //速度
}

void FormationEunomia::initialize() {
}

void FormationEunomia::onActive() {
    updateRankParameter();
}

void FormationEunomia::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //編隊消滅時の実験
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->pDepo_EffectTurbo002_->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
    //編隊全滅アイテム出現
    Item* pItem = (Item*)P_COMMON_SCENE->pDP_MagicPointItem002_->dispatch();
    if (pItem) {
        pItem->locateAs((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}


void FormationEunomia::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % R_interval_frames_ == 0)) {
        for (int i = 0; i < R_num_formation_col_; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpUntil(R_num_formation_col_*R_num_formation_row_);
            if (pEunomia) {
                SplineSequence* pSplSeq = papSplManufCon_[i]->use()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(R_mv_velo_);
                processOnActiveEunomia(pEunomia, i); //フォーメーション個別実装の処理
            }
        }
    }
}

FormationEunomia::~FormationEunomia() {
    pDepoCon_Eunomia_->close();
    for (int i = 0; i < 7; i++) {
        papSplManufCon_[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papSplManufCon_);
    if (pDepoCon_Shot_) {
        pDepoCon_Shot_->close();
    }
}
