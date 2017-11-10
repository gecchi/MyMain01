#include "StagePartController.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StagePartController::StagePartController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StagePartController";
}

void StagePartController::fadeout_stop_AllPartSceneBgm() {
    _TRACE_(FUNC_NAME<<" ----->begin");
    GgafDxScene* pScene = (GgafDxScene*)(getSubFirst());
    while (pScene) {
        if (pScene->isLast()) {
            if (pScene->getBgmPerformer()) {
                pScene->getBgmPerformer()->fadeout_stop();
            }
            break;
        } else {
            if (pScene->getBgmPerformer()) {
                pScene->getBgmPerformer()->fadeout_stop();
            }
            pScene = (GgafDxScene*)(pScene->getNext());
        }
    }
    _TRACE_(FUNC_NAME<<" <---- end");
}

StagePartController::~StagePartController() {
}
