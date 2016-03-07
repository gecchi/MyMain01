#include "FormationOrtuna001.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001::FormationOrtuna001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationOrtuna001";
    num_Ortuna_      = RF_FormationOrtuna001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationOrtuna001_LaunchInterval(G_RANK);  //オルトゥナの間隔(frame)
    for (int i = 0; i < num_Ortuna_; i++) {
        std::string name = "Ortuna("+XTOS(i)+")";
        addFormationMember(NEW EnemyOrtuna(name.c_str()));
    }
    index_call_up_ = 0;
}

void FormationOrtuna001::initialize() {
}

void FormationOrtuna001::onActive() {
}

void FormationOrtuna001::processBehavior() {
    if (canCallUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemyOrtuna* pOrtuna = (EnemyOrtuna*)callUpMember();
        if (pOrtuna) {
            onCallUpOrtuna(pOrtuna, index_call_up_);  //コールバック
            index_call_up_++;
        }
    }
}

void FormationOrtuna001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationOrtuna001::~FormationOrtuna001() {
}
