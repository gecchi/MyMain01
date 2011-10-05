#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool RankUpScene::_pause = false;

RankUpScene::RankUpScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpScene";
    useProgress(RANKUPSCENE_PROG_END);
}

void RankUpScene::initialize() {
    _pProg->set(RANKUPSCENE_PROG_INIT);
}

void RankUpScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ||
        prm_no == EVENT_STG02_CONTROLLER_WAS_END
    ) {
        _TRACE_("RankUpScene::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��RANKUPSCENE_PROG_END��");
        _pProg->change(RANKUPSCENE_PROG_END);
    } else {

    }
}


//
//void RankUpScene::initialize() {
//}
//
//
//void RankUpScene::processJudgement() {
//}
//
//void RankUpScene::processFinal() {
//    //�ꎞ��~
//    if (VB->isPushedDown(VB_UI_CANCEL)) {
//        if (_pause) {
//            pauseTree();
//        } else {
//            unpauseTree();
//        }
//    }
//}

RankUpScene::~RankUpScene() {
}
