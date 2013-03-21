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
	frame f[] = {1,10,100,120,300,540,780,1000,1020};
	_paFrame_NextEvent = new frame[9];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 9;
	orderActorToFactory(10000000, EnemyMetis, "EnemyMetis-1");
	orderActorToFactory(10000001, FormationSappho001a, "FormationSappho001a-2");
	orderActorToFactory(10000002, FormationSappho001b, "FormationSappho001b-3");
	orderActorToFactory(10000003, FormationSappho001a, "FormationSappho001a-4");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
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
			case 10: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 100: {
				orderActorToFactory(10000006, FormationPallas001a, "FormationPallas001a-5");
				orderActorToFactory(10000007, FormationPallas001b, "FormationPallas001b-6");
				orderActorToFactory(10000008, FormationPallas001c, "FormationPallas001c-7");
				orderActorToFactory(10000009, FormationPallas001d, "FormationPallas001d-8");
				orderActorToFactory(10000010, FormationPallas001a, "FormationPallas001a-9");
				orderActorToFactory(10000011, FormationPallas001d, "FormationPallas001d-10");
				orderActorToFactory(10000012, FormationPallas001b, "FormationPallas001b-11");
				orderActorToFactory(10000013, FormationPallas001c, "FormationPallas001c-12");
				orderActorToFactory(10000014, FormationPallas001a, "FormationPallas001a-13");
				orderActorToFactory(10000015, FormationPallas001d, "FormationPallas001d-14");
				orderActorToFactory(10000016, FormationPallas001b, "FormationPallas001b-15");
				orderActorToFactory(10000017, FormationPallas001c, "FormationPallas001c-16");
				break;
			}
			case 120: {
				orderActorToFactory(10000004, FormationSappho001b, "FormationSappho001b-17");
				break;
			}
			case 300: {
				FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 540: {
				FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 780: {
				FormationSappho001a* pF = (FormationSappho001a*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 1000: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-18");
				ta->setMaxPerformFrame(3000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10000006)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10000007)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10000008)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10000009)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10000010)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10000011)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10000012)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10000013)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(10000014)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(10000015)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(10000016)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(10000017)), 400);
				}
				break;
			}
			case 1020: {
				FormationSappho001b* pF = (FormationSappho001b*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(pF);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 9-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
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
