#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02PartController::Stage02PartController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02PartController";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,3,1200,3000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderSceneToFactory(60000000, Stage02_01, "Stage02_01");
    // gen01 end
    useProgress(Stage02PartController::PROG_FAINAL);
}

void Stage02PartController::initialize() {
    _pBgmPerformer->play_fadein(0, 420);
    _pProg->change(Stage02PartController::PROG_INIT);
}

void Stage02PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 3: {
				Stage02_01* pScene = (Stage02_01*)obtainSceneFromFactory(60000000);
				addSubLast(pScene);
				_pProg->change(Stage02PartController::PROG_STG02_01_BEGIN);
				break;
			}
			case 1200: {
				orderSceneToFactory(60000001, Stage02_Climax, "Stage02_Climax");
				break;
			}
			case 3000: {
				Stage02_Climax* pScene = (Stage02_Climax*)obtainSceneFromFactory(60000001);
				addSubLast(pScene);
				_pProg->change(Stage02PartController::PROG_STG02_CLIMAX_BEGIN);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_INIT)) {
        _TRACE_("Stage02PartController::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_01_BEGIN)) {
        //STG0201_開始処理

        _pProg->change(Stage02PartController::PROG_STG02_01_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_01_PLAYING) {
        //STG0201_最中の処理

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_CLIMAX_BEGIN)) {
        //STG02Climax_開始処理
        _pBgmPerformer->fadeout_stop(1);  //BGM１番フェードアウト
        _pBgmPerformer->play_fadein(2);
        _pProg->change(Stage02PartController::PROG_STG02_CLIMAX_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_CLIMAX_PLAYING) {
        //STG02Climax_最中の処理

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_FAINAL)) {
        //STG02Climax_終焉の処理
        _TRACE_("STG02Climax_終焉のStage02PartController::PROG_FAINALきた");
        _pBgmPerformer->fadeout_stop(2); //BGM１番フェードアウト
        frame_prog_fainal_ = 0;
    } else if (_pProg->get() == Stage02PartController::PROG_FAINAL) {
        //STG02Climax_終焉最中の処理
        frame_prog_fainal_++;

        if (frame_prog_fainal_ == 420) { //BGMフェードアウトを待つ。
            fadeoutScene(300);
            throwEventToUpperTree(EVENT_STG02_CTRLER_WAS_END, this); //ステージエンドを上位に伝える
        }
    }

    if (getBehaveingFrame() == 2) {

    }

}


void Stage02PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG02_01_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_01_WAS_BROKEN");
        ((Stage02_01*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG02_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_CLIMAX_WAS_BROKENキャッチした。STAGE02PARTCONTROLLER_ENDINGを投げる");
        ((Stage02_Climax*)prm_pSource)->end(30*60);
        _pProg->change(Stage02PartController::PROG_FAINAL); //進捗をStage02PartController::PROG_FAINALに切り替える
    } else {

    }
}

Stage02PartController::~Stage02PartController() {

}
