#include "Stage02_Climax.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02PartController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02_Climax::Stage02_Climax(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_Climax";
    orderActorToFactory(11111111, EnemyStraea, "STG1BOSS");
    // gen01 end
    waiting_ = false;
}

void Stage02_Climax::initialize() {

}

void Stage02_Climax::processBehavior() {
    if (waiting_) {
        return;
    }

    if (getActiveFrame() == 60) {
        pBoss_ = (EnemyStraea*)obtainActorFromFactory(11111111);
        pBoss_->_z = -1800000;
        pBoss_->_y = -100000;
        getSceneDirector()->addSubGroup(pBoss_);
    }

    if (getActiveFrame() > 60) {
        if (pBoss_->isDisappear()) {
            //isDisappear()になりっ放しをなんとかする
            _DTRACE_("Stage02_Climax::processBehavior() EVENT_STG02_CLIMAX_WAS_BROKEN!!!!");
            throwEventUpperTree(EVENT_STG02_CLIMAX_WAS_BROKEN);
            waiting_ = true;
        }
    }


}

Stage02_Climax::~Stage02_Climax() {

}
