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
	frame f[] = {1,200,320,440,560,680,800,920,1040,1200};
	_paFrame_NextEvent = new frame[10];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 10;
	orderSceneToFactory(10000000, Stage01WalledScene, "GroStage01WalledScene");
	orderActorToFactory(10000001, FormationEunomia001a, "F001a_Eunomia_1");
	orderActorToFactory(10000002, FormationEunomia001b, "F001b_Eunomia_2");
	orderActorToFactory(10000003, FormationEunomia001a, "F001a_Eunomia_3");
	orderActorToFactory(10000004, FormationEunomia001b, "F001b_Eunomia_4");
	orderActorToFactory(10000005, FormationEunomia001a, "F001a_Eunomia_5");
	orderActorToFactory(10000006, FormationEunomia001b, "F001b_Eunomia_6");
	orderActorToFactory(10000007, FormationEunomia001a, "F001a_Eunomia_7");
	orderActorToFactory(10000008, FormationEunomia001b, "F001b_Eunomia_8");
    // gen01 end
    useProgress(10);
}

void Stage01Controller::initialize() {
//    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
//    _pBgmPerformer->fadein(0, 420);
    _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_INIT);
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
			case 200: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000001);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 320: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000002);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 440: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000003);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 560: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000004);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 680: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000005);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 800: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000006);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 920: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000007);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 1040: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000008);
				getLordActor()->addSubGroup(pFormation);
				break;
			}
			case 1200: {
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 10-1 ? _iCnt_Event+1 : _iCnt_Event);
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
