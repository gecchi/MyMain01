#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe::FormationHebe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationHebe";

    pConn_HebeDepo_ = connectToDepositoryManager("Conn_EnemyHebe4Formation", this);
    setFormationMemberDepository(pConn_HebeDepo_->fetch());

    //スプライン定義ファイルを読み込む
    pSplManufCon_ = connectToSplineManufactureManager("FormationHebe001");
    //pConn_ShotDepo_ = connectToDepositoryManager("Conn_Shot004", nullptr); //Hebeの弾;
    pConn_ShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationHebe::updateRankParameter() {
    rr_num_formation_     = RR_FormationHebe_Num(_RANK_);            //編隊数
    rr_interval_frames_   = RR_FormationHebe_LaunchInterval(_RANK_); //ヘーベの間隔(frame)
    rr_mv_velo_           = RR_FormationHebe_MvVelo(_RANK_);         //速度
}

void FormationHebe::initialize() {
}

void FormationHebe::onActive() {
    updateRankParameter();
}

void FormationHebe::processBehavior() {
    if (canCallUp() && (getActivePartFrame() % rr_interval_frames_ == 0)) {
        EnemyHebe* pHebe = (EnemyHebe*)callUpUntil(rr_num_formation_);
        if (pHebe) {
            SplineSequence* pSplSeq = pSplManufCon_->fetch()->
                                          createSplineSequence(pHebe->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pConn_ShotDepo_ ? pConn_ShotDepo_->fetch() : nullptr;
            pHebe->config(pSplSeq, pDepo_Shot, nullptr);
            pHebe->_pKurokoA->setMvVelo(rr_mv_velo_);
            processOnActiveHebe(pHebe); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationHebe::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationHebe::~FormationHebe() {
    pConn_HebeDepo_->close();
    pSplManufCon_->close();
    if (pConn_ShotDepo_) {
        pConn_ShotDepo_->close();
    }
}

