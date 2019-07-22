#include "StagePartController.h"
#include "jp/ggaf/dx/scene/Scene.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"



using namespace GgafLib;
using namespace VioletVreath;

StagePartController::StagePartController(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "StagePartController";
}

//void StagePartController::fadeout_stop_AllPartSceneBgm() {
//    _TRACE_(FUNC_NAME<<" ----->begin");
//    GgafDx::Scene* pScene = (GgafDx::Scene*)(getChildFirst());
//    while (pScene) {
//        if (pScene->isLast()) {
//            if (pScene->getBgmConductor()) {
//                pScene->getBgmConductor()->fadeoutStopAll(120);
//            }
//            break;
//        } else {
//            if (pScene->getBgmConductor()) {
//                pScene->getBgmConductor()->fadeoutStopAll(120);
//            }
//            pScene = (GgafDx::Scene*)(pScene->getNext());
//        }
//    }
//    _TRACE_(FUNC_NAME<<" <---- end");
//}

StagePartController::~StagePartController() {
}
