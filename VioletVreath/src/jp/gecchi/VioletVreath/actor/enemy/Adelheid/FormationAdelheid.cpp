#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAdelheid::FormationAdelheid(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationAdelheid";

    //編隊隊員デポジトリセット
    pConnection_AdelheidDepo_ = connectToDepositoryManager("EnemyAdelheid4Formation");
    setFormationMemberDepo(pConnection_AdelheidDepo_->peek());

    pSplManufConnection_ = nullptr;//下位クラスがスプライン定義ファイルを読み込む
    pConnection_ShotDepo_ = nullptr;//下位クラスが設定

    updateRankParameter();
}

void FormationAdelheid::updateRankParameter() {
    rr_num_formation_     = RR_FormationAdelheid_Num(_RANK_);            //編隊数
    rr_interval_frames_   = 30;
    rr_mv_velo_           = RR_FormationAdelheid_MvVelo(_RANK_);         //速度
}

void FormationAdelheid::initialize() {
}

void FormationAdelheid::onActive() {
    updateRankParameter();
}

void FormationAdelheid::processBehavior() {
    if (canCallUp() && (getActiveFrame() % rr_interval_frames_ == 0)) {
        EnemyAdelheid* pAdelheid = (EnemyAdelheid*)callUpMember(rr_num_formation_);
        if (pAdelheid) {
            SplineKurokoStepper* pKurokoStepper = pSplManufConnection_->peek()->
                                          createSplineKurokoStepper(pAdelheid->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pConnection_ShotDepo_->peek();
            pAdelheid->config(pKurokoStepper, pDepo_Shot, nullptr);
            pAdelheid->_pKurokoA->setMvVelo(rr_mv_velo_);
            onCallUpAdelheid(pAdelheid); //下位フォーメーションクラス個別実装の処理
        }
    }
}

void FormationAdelheid::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（※ボーナススコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationAdelheid::~FormationAdelheid() {
    pConnection_AdelheidDepo_->close();
    pSplManufConnection_->close();
    pConnection_ShotDepo_->close();
}

