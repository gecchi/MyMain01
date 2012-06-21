#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    num_Pallas_      = R_FormationPallas001_Num;    //編隊数
    interval_frames_ = R_FormationPallas001_LaunchInterval;  //パラスの間隔(frame)
    velo_mv_         = R_FormationPallas001_MvVelo; //速度
    //パラス編隊作成
    pSplManufCon_ = connectSplineManufactureManager("Pallas01");
    pDepoCon_ = NULL;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    SplineSequence* pSplSeq;
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        pSplSeq = pSplManufCon_->fetch()->createSplineSequence(papPallas_[i]->_pKurokoA);
        papPallas_[i]->config(pSplSeq, NULL, NULL);
        //papPallas_[i]->setDepository_Shot(pDepoCon_->fetch()); //弾設定
        papPallas_[i]->inactivateImmed();
        addSubLast(papPallas_[i]);
    }
}
void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    GgafActor* pActor = getSubFirst();
    EnemyPallas* pPallas = NULL;
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

void FormationPallas001::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //編隊消滅時の実験
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->pDepo_EffectTurbo002_->dispatchForce();
    if (pTurbo002) {
		pTurbo002->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
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
