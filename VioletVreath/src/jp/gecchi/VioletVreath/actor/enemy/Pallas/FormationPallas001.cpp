#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    num_Pallas_      = RR_FormationPallas001_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationPallas001_LaunchInterval(_RANK_);  //パラスの間隔(frame)
    velo_mv_         = RR_FormationPallas001_MvVelo(_RANK_); //速度
    //パラス編隊作成
    pSplManufCon_ = connectToSplineManufactureManager("Pallas01");
    pDepoCon_ = nullptr;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    SplineSequence* pSplSeq;
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        pSplSeq = pSplManufCon_->fetch()->createSplineSequence(papPallas_[i]->_pKurokoA);
        papPallas_[i]->config(pSplSeq, nullptr, nullptr);
        //papPallas_[i]->setDepository_Shot(pDepoCon_->fetch()); //弾設定
        papPallas_[i]->inactivateImmed();
        addSubLast(papPallas_[i]);
    }
}
void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    GgafActor* pActor = getSubFirst();
    EnemyPallas* pPallas = nullptr;
    int t = 0;
    do {
        pPallas = (EnemyPallas*)pActor;
        pPallas->pSplSeq_->setAbsoluteBeginCoordinate();
        pPallas->_pKurokoA->setMvVelo(velo_mv_);
        pPallas->activateDelay(t*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());
}

void FormationPallas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

void FormationPallas001::processBehavior() {
}

FormationPallas001::~FormationPallas001() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papPallas_);
}
