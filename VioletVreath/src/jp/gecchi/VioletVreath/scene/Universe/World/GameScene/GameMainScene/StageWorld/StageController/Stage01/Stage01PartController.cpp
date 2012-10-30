#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    _pBgmPerformer->set(3, "BGM_01_CLIMAX");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,4100,4101,5000,5001,9100,10000,14100,15000};
	_paFrame_NextEvent = new frame[10];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 10;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->set(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pBgmPerformer->play_fadein(0);
				break;
			}
			case 4100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02");
				break;
			}
			case 4101: {
				orderSceneToFactory(10000002, Stage01WalledScene, "GroStage01WalledScene");
				break;
			}
			case 5000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				break;
			}
			case 5001: {
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 9100: {
				orderSceneToFactory(10000003, Stage01_03, "Stage01_03");
				break;
			}
			case 10000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(1);
				_pBgmPerformer->play_fadein(2);
				break;
			}
			case 14100: {
				orderSceneToFactory(10000004, Stage01_Climax, "Stage01_Climax");
				break;
			}
			case 15000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000004);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(2);
				_pBgmPerformer->play_fadein(3);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 10-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->hasJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventToUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage01WalledScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
