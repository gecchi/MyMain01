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
	frame f[] = {1,100,200,1000,1200,2000,2200,3000,4000};
	_paFrame_NextEvent = new frame[9];
	for (int i = 0; i < 9; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderSceneToFactory(11017100, Stage01_01, "Stage01_01");
	orderSceneToFactory(110271000, Stage01WalledScene, "GroStage01WalledScene");
	orderActorToFactory(11076100, EnemyAstraea, "Astraea_1");
    // gen01 end
    useProgress(10);
}

void Stage01Controller::initialize() {
    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
    _pBgmPerformer->fadein(0, 420);
    _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(11017100);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN);
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11076100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 200:
				orderSceneToFactory(110372000, Stage01_02, "Stage01_02");
				break;
			case 1000:
				{
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(110271000);
				addSubLast(pScene);
				}
				break;
			case 1200:
				orderSceneToFactory(110473000, Stage01_03, "Stage01_03");
				break;
			case 2000:
				{
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110372000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN);
				}
				break;
			case 2200:
				orderSceneToFactory(110574000, Stage01_Climax, "Stage01_Climax");
				break;
			case 3000:
				{
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110473000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN);
				}
				break;
			case 4000:
				{
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(110574000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 9-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_INIT)) {
        _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN)) {
        //STG01_01開始処理

        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING) {
        //STG01_01最中の処理

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN)) {
        //STG01_02開始処理
        _pBgmPerformer->fadeout_stop(0, 420);        //BGM０番フェードアウト
        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);//BGM１番フェードイン
        _pBgmPerformer->fadein(1, 420);
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING) {
        //STG01_02最中の処理

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN)) {
        //STG01_03開始処理

        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING) {
        //STG01_03最中の処理

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN)) {
        //STG01_Climax開始処理
        _pBgmPerformer->fadeout_stop(1, 420);  //BGM１番フェードアウト
        _pBgmPerformer->play(2, DSBVOLUME_MIN, true); //BGM２番フェードイン
        _pBgmPerformer->fadein(2, 420);
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING) {
        //STG01_Climax最中の処理

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_FAINAL)) {
        //STG01_Climax終焉の処理
        _TRACE_("STG01_Climax終焉のSTAGE01CONTROLLER_SCENE_PROG_FAINALきた");
        _pBgmPerformer->fadeout_stop(2, 420); //BGM１番フェードアウト
        _frame_prog_fainal = 0;
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_FAINAL) {
        //STG01_Climax終焉最中の処理
        _frame_prog_fainal++;

        if (_frame_prog_fainal == 420) { //BGMフェードアウトを待つ。
            throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END, this); //ステージエンドを上位に伝える
        }
    }

    if (getBehaveingFrame() == 2) {

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
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_FAINAL); //進捗をSTAGE01CONTROLLER_SCENE_PROG_FAINALに切り替える
    } else {

    }
}

Stage01Controller::~Stage01Controller() {

}
