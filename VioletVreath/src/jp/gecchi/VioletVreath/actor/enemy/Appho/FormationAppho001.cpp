#include "FormationAppho001.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001::FormationAppho001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAppho001";
    num_Appho_       = RF_FormationAppho001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAppho001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
    for (int i = 0; i < num_Appho_; i++) {
        std::string name = "Appho("+XTOS(i)+")";
        addFormationMember(NEW EnemyAppho(name.c_str()));
    }
    cnt_call_up_ = 0;
}

void FormationAppho001::initialize() {
}

void FormationAppho001::onActive() {
}

void FormationAppho001::processBehavior() {
    if (canCallUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemyAppho* pAppho = (EnemyAppho*)callUpMember();
        if (pAppho) {
            onCallUpAppho(pAppho, cnt_call_up_);  //コールバック
            cnt_call_up_++;
        }
    }
}

void FormationAppho001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationAppho001::~FormationAppho001() {
}
