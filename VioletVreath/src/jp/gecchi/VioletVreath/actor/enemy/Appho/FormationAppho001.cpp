#include "FormationAppho001.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001::FormationAppho001(const char* prm_name) :
        VvFormationActor<TreeFormation>(prm_name, StatusReset(FormationAppho001)) {
    _class_name = "FormationAppho001";
    num_Appho_       = 0;
    interval_frames_ = 0;

    for (int i = 0; i < RF_FormationAppho001_Num(G_MAX_RANK); i++) {
        std::string name = "Appho("+XTOS(i)+")";
        appendFormationMember(NEW EnemyAppho(name.c_str()));
    }
    cnt_summon_ = 0;
}

void FormationAppho001::initialize() {
}

void FormationAppho001::onActive() {
    num_Appho_       = RF_FormationAppho001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAppho001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
}

void FormationAppho001::processBehavior() {
    if (canSummon() && getActiveFrame() % interval_frames_ == 0) {
        EnemyAppho* pAppho = (EnemyAppho*)summonMember(num_Appho_);
        if (pAppho) {
            onSummonAppho(pAppho, cnt_summon_);  //コールバック
            cnt_summon_++;
        }
    }
}

FormationAppho001::~FormationAppho001() {
}
