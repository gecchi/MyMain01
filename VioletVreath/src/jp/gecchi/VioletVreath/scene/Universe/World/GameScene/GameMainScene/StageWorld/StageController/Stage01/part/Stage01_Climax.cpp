#include "stdafx.h"
#include "Stage01_Climax.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_Climax::Stage01_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_Climax";
    orderActorToFactory(11111111, EnemyStraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;
}

void Stage01_Climax::initialize() {

}

void Stage01_Climax::processBehavior() {
    if (waiting_) {
        return;
    }

    if (getActiveFrame() == 60) {
        pBoss_ = (EnemyStraea*)obtainActorFromFactory(11111111);
        pBoss_->_Z = -1800000;
        pBoss_->_Y = -100000;
        getSceneDirector()->addSubGroup(pBoss_);
    }

    if (getActiveFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()‚É‚È‚è‚Á•ú‚µ‚ð‚È‚ñ‚Æ‚©‚·‚é
            _TRACE_("Stage01_Climax::processBehavior() EVENT_STG01_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG01_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage01_Climax::~Stage01_Climax() {

}
