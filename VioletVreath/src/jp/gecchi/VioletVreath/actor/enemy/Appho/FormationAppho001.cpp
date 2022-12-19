#include "FormationAppho001.h"

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Appho/EnemyAppho.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAppho001::FormationAppho001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAppho001";
    num_Appho_       = 0;
    interval_frames_ = 0;

    for (int i = 0; i < RF_FormationAppho001_Num(G_MAX_RANK); i++) {
        std::string name = "Appho("+XTOS(i)+")";
        appendFormationMember(NEW EnemyAppho(name.c_str()));
    }
    cnt_called_up_ = 0;
}

void FormationAppho001::initialize() {
}

void FormationAppho001::onActive() {
    num_Appho_       = RF_FormationAppho001_Num(G_RANK);    //編隊数
    interval_frames_ = RF_FormationAppho001_LaunchInterval(G_RANK);  //アラスの間隔(frame)
}

void FormationAppho001::processBehavior() {
    if (canCalledUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemyAppho* pAppho = (EnemyAppho*)calledUpMember(num_Appho_);
        if (pAppho) {
            onCalledUpAppho(pAppho, cnt_called_up_);  //コールバック
            cnt_called_up_++;
        }
    }
}

void FormationAppho001::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationAppho001::~FormationAppho001() {
}
