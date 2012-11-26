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
	frame f[] = {1,100,200,1600,2300,2500,3200,5300,6200,8300,9100,9200,10000,11300,12200,14300,15200,17300,18200,19100,20000,20300,21200,23300,24200,26300,27200,29100,30000};
	_paFrame_NextEvent = new frame[29];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 29;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000005, EnemyHermione, "EnemyHermione-2");
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
			case 200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 1600: {
				orderActorToFactory(10000004, FormationEunomia001a, "FormationEunomia001a-3");
				break;
			}
			case 2300: {
				orderActorToFactory(10000006, EnemyHermione, "EnemyHermione-4");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 3200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 5300: {
				orderActorToFactory(10000007, EnemyHermione, "EnemyHermione-5");
				break;
			}
			case 6200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 8300: {
				orderActorToFactory(10000008, EnemyHermione, "EnemyHermione-6");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-7");
				break;
			}
			case 9200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				break;
			}
			case 11300: {
				orderActorToFactory(10000009, EnemyHermione, "EnemyHermione-8");
				break;
			}
			case 12200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 14300: {
				orderActorToFactory(10000010, EnemyHermione, "EnemyHermione-9");
				break;
			}
			case 15200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 17300: {
				orderActorToFactory(10000011, EnemyHermione, "EnemyHermione-10");
				break;
			}
			case 18200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-11");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(1);
				_pBgmPerformer->play_fadein(2);
				break;
			}
			case 20300: {
				orderActorToFactory(10000012, EnemyHermione, "EnemyHermione-12");
				break;
			}
			case 21200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 23300: {
				orderActorToFactory(10000013, EnemyHermione, "EnemyHermione-13");
				break;
			}
			case 24200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 26300: {
				orderActorToFactory(10000014, EnemyHermione, "EnemyHermione-14");
				break;
			}
			case 27200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(p);
				p->_X = RND(-1000000,1000000);
				p->_Y = RND(-1000000,1000000);
				p->_Z = RND(-1000000,1000000);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-15");
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
		_cnt_event = (_cnt_event < 29-1 ? _cnt_event+1 : _cnt_event);
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
