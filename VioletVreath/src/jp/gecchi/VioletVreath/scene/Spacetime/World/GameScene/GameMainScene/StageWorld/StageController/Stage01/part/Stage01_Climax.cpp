#include "Stage01_Climax.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"
#include "jp/ggaf/lib/util/SceneProgress.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_Climax";
    orderActorToFactory(11111111, EnemyStraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;

    getBGMer()->ready(0, "OGG_BGM_01_CLIMAX");
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (waiting_) {
        return;
    }
    if (getBehaveingFrame() == 1 && P_GAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeout_stop_AllPartSceneBgm();
        getBGMer()->play_fadein(0);
    }

    if (getBehaveingFrame() == 60) {
        pBoss_ = (EnemyStraea*)obtainActorFromFactory(11111111);
        pBoss_->_z = -1800000;
        pBoss_->_y = -100000;
        bringDirector()->addSubGroup(pBoss_);
    }

    if (getBehaveingFrame() > 60) {
        if (pBoss_->onChangeToInactive()) {
            getBGMer()->fadeout_stop(0);
            _TRACE_("Stage01_Climax::processBehavior() EVENT_STG01_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG01_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage01_Climax::~Stage01_Climax() {

}
