#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


StagePartController::StagePartController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StagePartController";
    useProgress(STAGE_PROG_END);
}

//void StagePartController::addSubLast(GgafScene* prm_pScene) {
//    DefaultScene::addSubLast(prm_pScene);
//
//}

StagePartController::~StagePartController() {
}
