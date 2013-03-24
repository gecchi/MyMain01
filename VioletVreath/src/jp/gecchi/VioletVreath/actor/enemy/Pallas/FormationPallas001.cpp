#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationPallas001";
    num_Pallas_      = RR_FormationPallas001_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationPallas001_LaunchInterval(_RANK_);  //パラスの間隔(frame)
    velo_mv_         = RR_FormationPallas001_MvVelo(_RANK_); //速度
    //パラス編隊作成
    pSplManufCon_ = connectToSplineManufactureManager("Pallas01");
    pDepoCon_ = nullptr;
    for (int i = 0; i < num_Pallas_; i++) {
        EnemyPallas* pPallas= NEW EnemyPallas("Pallas01");
        SplineSequence* pSplSeq = pSplManufCon_->fetch()->createSplineSequence(pPallas->_pKurokoA);
        pPallas->config(pSplSeq, nullptr, nullptr);
        addFormationMember(pPallas);
    }
}

void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    for (int n = 0; canCallUp(); n++) {
        EnemyPallas* pPallas = (EnemyPallas*)callUpMember();
        if (pPallas) {
            onCallUpPallas(pPallas); //コールバック
            pPallas->activateDelay(n*interval_frames_ + 1);
            n++;
        }
    }
    //FormationTableScene に追加する編隊の場合、
    //編隊が途中でちょん切れる事を防ぐために、このように
    //onActive()で、一気に全ての編隊要員を callUpMember() & activate() しておく事。
}

void FormationPallas001::processBehavior() {
}

void FormationPallas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationPallas001::~FormationPallas001() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
}
