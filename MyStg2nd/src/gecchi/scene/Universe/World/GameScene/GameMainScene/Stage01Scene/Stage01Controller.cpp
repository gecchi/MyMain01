#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
    frame f[] = {1,3,1000,3000};
    _paFrame_NextEvent = new frame[4];
    for (int i = 0; i < 4; i++) {
        _paFrame_NextEvent[i] = f[i];
    }
    orderSceneToFactory(110273, Stage01_01, "Stage01_01");
    orderSceneToFactory(110371000, Stage01_02, "Stage01_02");
    orderSceneToFactory(110473000, Stage01_03, "Stage01_03");
    // gen01 end
}

void Stage01Controller::initialize() {

}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start 〜 end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1:
                break;
            case 3:
                {
                Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(110273);
                addSubLast(pScene);
                }
                break;
            case 1000:
                {
                Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110371000);
                addSubLast(pScene);
                }
                break;
            case 3000:
                {
                Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110473000);
                addSubLast(pScene);
                }
                break;
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01Controller::processFinal() {
}

void Stage01Controller::catchEvent(int prm_no) {
    if (prm_no == STG01_BOSS_WAS_BREAK) {
        getParent()->setProgress(STAGE01_PROG_END);

    }


}

Stage01Controller::~Stage01Controller() {

}
