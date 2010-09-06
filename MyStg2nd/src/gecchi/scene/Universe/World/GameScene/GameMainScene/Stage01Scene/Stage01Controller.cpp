#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,3,200,2000,2200,4000,28200,30000};
	_paFrame_NextEvent = new frame[8];
	for (int i = 0; i < 8; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderSceneToFactory(110273, Stage01_01, "Stage01_01");
    // gen01 end
}

void Stage01Controller::initialize() {
    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
    _pBgmPerformer->fadein(0, 420);
    setProgress(STAGE01CONTROLLER_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 3:
				{
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(110273);
				addSubLast(pScene);
				setProgress(STAGE01CONTROLLER_PROG_STG01_01_BEGIN);
				}
				break;
			case 200:
				orderSceneToFactory(110372000, Stage01_02, "Stage01_02");
				break;
			case 2000:
				{
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110372000);
				addSubLast(pScene);
				setProgress(STAGE01CONTROLLER_PROG_STG01_02_BEGIN);
				}
				break;
			case 2200:
				orderSceneToFactory(110474000, Stage01_03, "Stage01_03");
				break;
			case 4000:
				{
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110474000);
				addSubLast(pScene);
				setProgress(STAGE01CONTROLLER_PROG_STG01_03_BEGIN);
				}
				break;
			case 28200:
				orderSceneToFactory(1105730000, Stage01_Climax, "Stage01_Climax");
				break;
			case 30000:
				{
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(1105730000);
				addSubLast(pScene);
				setProgress(STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 8-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_INIT)) {
        _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");

    }

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_STG01_01_BEGIN)) {
        //STG01_01開始処理

        setProgress(STAGE01CONTROLLER_PROG_STG01_01_PLAYING);
    } else if (getProgress() == STAGE01CONTROLLER_PROG_STG01_01_PLAYING) {
        //STG01_01最中の処理

    }

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_STG01_02_BEGIN)) {
        //STG01_02開始処理
        _pBgmPerformer->fadeout_stop(0, 420);        //BGM０番フェードアウト
        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);//BGM１番フェードイン
        _pBgmPerformer->fadein(1, 420);
        setProgress(STAGE01CONTROLLER_PROG_STG01_02_PLAYING);
    } else if (getProgress() == STAGE01CONTROLLER_PROG_STG01_02_PLAYING) {
        //STG01_02最中の処理

    }

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_STG01_03_BEGIN)) {
        //STG01_03開始処理

        setProgress(STAGE01CONTROLLER_PROG_STG01_03_PLAYING);
    } else if (getProgress() == STAGE01CONTROLLER_PROG_STG01_03_PLAYING) {
        //STG01_03最中の処理

    }

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN)) {
        //STG01_Climax開始処理
        _pBgmPerformer->fadeout_stop(1, 420);  //BGM１番フェードアウト
        _pBgmPerformer->play(2, DSBVOLUME_MIN, true); //BGM２番フェードイン
        _pBgmPerformer->fadein(2, 420);
        setProgress(STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING);
    } else if (getProgress() == STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING) {
        //STG01_Climax最中の処理

    }

    if (onChangeProgressAt(STAGE01CONTROLLER_PROG_FAINAL)) {
        //STG01_Climax終焉の処理
        _TRACE_("STG01_Climax終焉のSTAGE01CONTROLLER_PROG_FAINALきた");
        _pBgmPerformer->fadeout_stop(2, 420); //BGM１番フェードアウト
        _frame_prog_fainal = 0;
    } else if (getProgress() == STAGE01CONTROLLER_PROG_FAINAL) {
        //STG01_Climax終焉最中の処理
        _frame_prog_fainal++;

        if (_frame_prog_fainal == 420) { //BGMフェードアウトを待つ。
            throwUpEvent(STAGE01CONTROLLER_WAS_END, this); //ステージエンドを上位に伝える
        }
    }

    if (getBehaveingFrame() == 2) {

    }

}

void Stage01Controller::processFinal() {
}

void Stage01Controller::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(3000*60);
    } else if (prm_no == STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(30*60);
    } else if (prm_no == STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(30*60);
    } else if (prm_no == STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01Controller::catchEvent() STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01CONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->end(30*60);
        setProgress(STAGE01CONTROLLER_PROG_FAINAL); //進捗をSTAGE01CONTROLLER_PROG_FAINALに切り替える
    } else {

    }
}

Stage01Controller::~Stage01Controller() {

}
