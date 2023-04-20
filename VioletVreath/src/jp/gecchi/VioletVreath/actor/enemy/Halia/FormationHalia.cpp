#include "FormationHalia.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Halia/EnemyHalia.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationHalia::FormationHalia(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationHalia";
    num_Halia_  = RF_FormationHalia_Num(G_RANK);         //編隊のハリアの数
    interval_frames_ = RF_FormationHalia_LaunchInterval(G_RANK);    //各ハリアの出現間隔(frame)
    velo_mv_         = RF_FormationHalia_MvVelo(G_RANK); //各ハリアの移動速度

    //編隊作成
    papHalia_ = NEW EnemyHalia*[num_Halia_];
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i] = NEW EnemyHalia("Halia01");
        //カーブ移動プログラム設定
        papHalia_[i]->setCurveLocoVehicleLeader(nullptr);
        appendFormationMember(papHalia_[i]);
    }
}

void FormationHalia::initialize() {
}

void FormationHalia::onActive() {
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i]->setPosition(1000000, -1000000 + (i * 200000), 0);
        papHalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

void FormationHalia::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationHalia::~FormationHalia() {
    GGAF_DELETEARR(papHalia_);
}
