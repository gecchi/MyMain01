#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1300,1500,1700,1900,9100,10000,19100,20000,29100,30000};
	_paFrame_NextEvent = new frame[22];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 22;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, FormationEbe001, "FormationEbe001-2");
	orderActorToFactory(10000005, EnemyEsperia, "EnemyEsperia-3");
	orderActorToFactory(10000006, EnemyEsperia, "EnemyEsperia-4");
	orderActorToFactory(10000007, EnemyEsperia, "EnemyEsperia-5");
	orderActorToFactory(10000008, EnemyEsperia, "EnemyEsperia-6");
	orderActorToFactory(10000014, FormationAntiope001, "FormationAntiope001-7");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    getProgress()->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				orderActorToFactory(10000015, FormationAntiope001, "FormationAntiope001-8");
				break;
			}
			case 200: {
				orderActorToFactory(10000009, EnemyEsperia, "EnemyEsperia-9");
				break;
			}
			case 300: {
				FormationEbe001* pF10 = (FormationEbe001*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pF10);
				EnemyEsperia* p11 = (EnemyEsperia*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p11);
				break;
			}
			case 400: {
				orderActorToFactory(10000010, EnemyEsperia, "EnemyEsperia-12");
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 500: {
				EnemyEsperia* p13 = (EnemyEsperia*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p13);
				break;
			}
			case 600: {
				orderActorToFactory(10000011, EnemyEsperia, "EnemyEsperia-14");
				break;
			}
			case 700: {
				EnemyEsperia* p15 = (EnemyEsperia*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p15);
				break;
			}
			case 800: {
				orderActorToFactory(10000012, EnemyEsperia, "EnemyEsperia-16");
				break;
			}
			case 900: {
				EnemyEsperia* p17 = (EnemyEsperia*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p17);
				break;
			}
			case 1000: {
				orderActorToFactory(10000013, EnemyEsperia, "EnemyEsperia-18");
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 1100: {
				EnemyEsperia* p19 = (EnemyEsperia*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(p19);
				break;
			}
			case 1300: {
				EnemyEsperia* p20 = (EnemyEsperia*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p20);
				break;
			}
			case 1500: {
				EnemyEsperia* p21 = (EnemyEsperia*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p21);
				break;
			}
			case 1700: {
				EnemyEsperia* p22 = (EnemyEsperia*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p22);
				break;
			}
			case 1900: {
				EnemyEsperia* p23 = (EnemyEsperia*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p23);
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-24");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-25");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-26");
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 22-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (pProg->getFrameInProgress() == 60) {
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
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
