#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001::FormationSappho001(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationSappho001";
    num_Sappho_      = RR_FormationSappho001_Num(_RANK_);    //編隊数
    interval_frames_ = RR_FormationSappho001_LaunchInterval(_RANK_);  //パラスの間隔(frame)
    velo_mv_         = RR_FormationSappho001_MvVelo(_RANK_); //速度
    pDepoCon_ = nullptr;
    SplineSequence* pSplSeq;
    for (int i = 0; i < num_Sappho_; i++) {
        EnemySappho* pSappho = NEW EnemySappho("Sappho01");
        pSappho->inactivateImmed();
        addSubLast(pSappho);
    }
    can_fetch_ = true;
}
void FormationSappho001::initialize() {
}

void FormationSappho001::onActive() {
}

void FormationSappho001::processBehavior() {
    if (can_fetch_ && getActivePartFrame() % interval_frames_ == 0) {
        EnemySappho* pSappho = (EnemySappho*)fetchSub();
        if (pSappho) {
            pSappho->activate();
            onActiveSappho(pSappho);  //コールバック
        } else {
            can_fetch_ = false;
        }
    }
}

void FormationSappho001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //編隊全滅時エフェクト出現（スコア加算も行われる）
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //編隊全滅アイテム出現
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}



FormationSappho001::~FormationSappho001() {
}
