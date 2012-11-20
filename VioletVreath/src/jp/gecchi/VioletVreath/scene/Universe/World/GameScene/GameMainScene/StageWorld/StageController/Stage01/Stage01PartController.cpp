#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "OGG_BGM_01_01");
    _pBgmPerformer->set(1, "OGG_BGM_01_02");
    _pBgmPerformer->set(2, "OGG_BGM_01_03");
    _pBgmPerformer->set(3, "OGG_BGM_01_CLIMAX");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,300,500,600,9100,10000,19100,20000,29100,30000};
	_paFrame_NextEvent = new frame[11];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 11;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, FormationHebe001, "FormationHebe001-2");
	orderActorToFactory(10000005, FormationEunomia001a, "FormationEunomia001a-3");
	orderActorToFactory(10000006, FormationEunomia001b, "FormationEunomia001b-4");
	orderActorToFactory(10000007, EnemyAstraea, "EnemyAstraea-5");
	orderActorToFactory(10000008, EnemyThisbe002, "EnemyThisbe002-6");
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
			case 300: {
				FormationHebe001* pF7 = (FormationHebe001*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(pF7);
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(pFormationEunomia);
				EnemyThisbe002* p = (EnemyThisbe002*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				p->_X = 0;
				p->_Y = 0;
				p->_Z = 2000000;
				break;
			}
			case 500: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 600: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1000000;
				pAstraea2->_Y = 10000;
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-8");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-9");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(1);
				_pBgmPerformer->play_fadein(2);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-10");
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(2);
				_pBgmPerformer->play_fadein(3);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 11-1 ? _cnt_event+1 : _cnt_event);
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
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
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
