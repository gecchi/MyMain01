#include "stdafx.h"
#include "Stage01_Climax.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_Climax";
    orderActorToFactory(11111111, EnemyStraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "OGG_BGM_01_CLIMAX");
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (waiting_) {
        return;
    }
    if (getBehaveingFrame() == 1) {
        _TRACE_("シーン="<<getName()<<"、のBGM[0]="<<_pBgmPerformer->_papBgmConnection[0]->peek()->_ogg_file_name<<" を、フェードイン。");
        _TRACE_("その前に、兄弟シーンのBGMを全てフェードアウト！");
         StagePartController* pStagePartController = (StagePartController*)(getParent());
         pStagePartController->fadeout_stop_AllPartSceneBgm(); //兄弟シーンのBGMを全てフェードアウト
         _pBgmPerformer->play_fadein(0);
     }


    if (getBehaveingFrame() == 60) {
        pBoss_ = (EnemyStraea*)obtainActorFromFactory(11111111);
        pBoss_->_Z = -1800000;
        pBoss_->_Y = -100000;
        getSceneDirector()->addSubGroup(pBoss_);
    }

    if (getBehaveingFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()になりっ放しをなんとかする
            _TRACE_("Stage01_Climax::processBehavior() EVENT_STG01_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG01_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage01_Climax::~Stage01_Climax() {

}
