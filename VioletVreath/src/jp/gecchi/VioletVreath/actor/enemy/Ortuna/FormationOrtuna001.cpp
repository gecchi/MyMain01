#include "FormationOrtuna001.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/EnemyOrtuna.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationOrtuna001::FormationOrtuna001(const char* prm_name) :
        VvFormationActor<TreeFormation>(prm_name, StatusReset(FormationOrtuna001)) {
    _class_name = "FormationOrtuna001";
    num_Ortuna_ = 0;
    interval_frames_ = 0;
    for (int i = 0; i < RF_FormationOrtuna001_Num(G_MAX_RANK); i++) {
        std::string name = "Ortuna("+XTOS(i)+")";
        appendFormationMember(NEW EnemyOrtuna(name.c_str()));
    }
    index_called_up_ = 0;
}

void FormationOrtuna001::initialize() {
}

void FormationOrtuna001::onActive() {
    num_Ortuna_      = RF_FormationOrtuna001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationOrtuna001_LaunchInterval(G_RANK);  //オルトゥナの間隔(frame)
}

void FormationOrtuna001::processBehavior() {
    if (canCalledUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemyOrtuna* pOrtuna = (EnemyOrtuna*)calledUpMember(num_Ortuna_);
        if (pOrtuna) {
            onCalledUpOrtuna(pOrtuna, index_called_up_);  //コールバック
            index_called_up_++;
        }
    }
}

FormationOrtuna001::~FormationOrtuna001() {
}
