#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
}
//
//void StageScene::initialize() {
//}
//
//void StageScene::processBehavior() {
//}
//
//void StageScene::processJudgement() {
//}
//
//void StageScene::processFinal() {
//    //ˆêŽž’âŽ~
//    if (VB_PLAY->isPushedDown(VB_UI_CANCEL)) {
//        if (_pause) {
//            pauseTree();
//        } else {
//            unpauseTree();
//        }
//    }
//}

StageScene::~StageScene() {
}
