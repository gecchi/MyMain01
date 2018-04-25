#include "Stage02_Climax.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02_Climax::Stage02_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_Climax";
    getBgmConductor()->ready(0, "OGG_BGM_01_02");

    wantActor(11111111, EnemyStraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;
}

void Stage02_Climax::initialize() {

}

void Stage02_Climax::processBehavior() {
    if (waiting_) {
        return;
    }
    if (getBehaveingFrame() == 1 && pGAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeoutBgmTree(300);
        getBgmConductor()->performFromTheBegining(0);
    }
    if (getActiveFrame() == 60) {
        pBoss_ = (EnemyStraea*)grantActor(11111111);
        pBoss_->_z = -1800000;
        pBoss_->_y = -100000;
        bringSceneMediator()->addSubGroup(pBoss_);
    }

    if (getActiveFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()になりっ放しをなんとかする
            _TRACE_(FUNC_NAME<<" EVENT_STG02_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG02_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage02_Climax::~Stage02_Climax() {

}
