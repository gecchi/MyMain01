#include "stdafx.h"
#include "FormationHalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Halia/EnemyHalia.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHalia::FormationHalia(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationHalia";
    num_Halia_      = RF_FormationHalia_Num(G_RANK);         //編隊のハリアの数
    interval_frames_ = RF_FormationHalia_LaunchInterval(G_RANK);    //各ハリアの出現間隔(frame)
    velo_mv_         = RF_FormationHalia_MvVelo(G_RANK); //各ハリアの移動速度

    //編隊作成
    papHalia_ = NEW EnemyHalia*[num_Halia_];
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i] = NEW EnemyHalia("Halia01");
        //スプライン移動プログラム設定
        papHalia_[i]->setSplineKurokoLeader(nullptr);
        addFormationMember(papHalia_[i]);
    }
}

void FormationHalia::initialize() {

}

void FormationHalia::onActive() {
    for (int i = 0; i < num_Halia_; i++) {
        papHalia_[i]->position(MyShip::lim_x_behaind_, -2000000 + (i * 400000), 0);
        papHalia_[i]->_pKuroko->setRzRyMvAng(0,0);
        papHalia_[i]->_pKuroko->setMvVelo(80000);
        papHalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

void FormationHalia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}


FormationHalia::~FormationHalia() {
    GGAF_DELETEARR(papHalia_);
}
