#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01Controller";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,1200,2200,4000};
	_paFrame_NextEvent = new frame[5];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 5;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
	orderSceneToFactory(10000001, Stage01WalledScene, "GroStage01WalledScene");
    // gen01 end
    useProgress(10);
}

void Stage01Controller::initialize() {
    _pPrg->set(STAGE01CONTROLLER_SCENE_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN);
				break;
			}
			case 1200: {
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 2200: {
				orderSceneToFactory(10000002, Stage01_02, "Stage01_02");
				break;
			}
			case 4000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 5-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pPrg->get()) {
        case STAGE01CONTROLLER_SCENE_PROG_INIT: {
            _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
            //進捗更新待ち
            break;
        }

        //Stage01_01
        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN: {
            //BGM１番フェードイン
            _pBgmPerformer->play(0, 0, true);
            _pBgmPerformer->fadein(0, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_02
        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN: {
            //BGM０番フェードアウト
            _pBgmPerformer->fadeout_stop(0, 420);
            //BGM１番フェードイン
            _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(1, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_03
        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN: {
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_Climax
        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN: {
            //BGM１番フェードアウト
            _pBgmPerformer->fadeout_stop(1, 420);
            //BGM２番フェードイン
            _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(2, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_Climax の後
        case STAGE01CONTROLLER_SCENE_PROG_FAINAL: {
            if (_pPrg->isJustChanged()) {
                //STG01_Climax終焉の処理
                _TRACE_("STG01_Climax終焉のSTAGE01CONTROLLER_SCENE_PROG_FAINALきた");
                _pBgmPerformer->fadeout_stop(2, 420); //BGM１番フェードアウト
                _frame_prog_fainal = 0;
            }
            _frame_prog_fainal++;
            if (_frame_prog_fainal == 420) { //BGMフェードアウトを待つ。
                throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01Controller::processFinal() {
}

void Stage01Controller::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(3000*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01CONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->end(30*60);
        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_FAINAL); //進捗をSTAGE01CONTROLLER_SCENE_PROG_FAINALに切り替える
    } else {

    }

}

Stage01Controller::~Stage01Controller() {

}
