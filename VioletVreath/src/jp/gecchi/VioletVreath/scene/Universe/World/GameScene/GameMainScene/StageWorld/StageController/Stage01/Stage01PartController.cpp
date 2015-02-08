#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
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
	frame f[] = {1,20,100,302,303,400,600,620,900,1000,1500,9100,10000,19100,20000,29100,30000,39100,40000};
	_paFrame_NextEvent = new frame[19];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 19;
	orderActorToFactory(10000005, EnemyOebiusController001, "EnemyOebiusController001-1");
	orderActorToFactory(10000007, FormationUrydike001, "FormationUrydike001-2");
	orderActorToFactory(10000008, FormationUrydike002, "FormationUrydike002-3");
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
			case 20: {
				orderActorToFactory(10000006, EnemyOebiusController002, "EnemyOebiusController002-4");
				break;
			}
			case 100: {
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-5");
				break;
			}
			case 302: {
				FormationUrydike001* p1 = (FormationUrydike001*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p1);
				p1->position(PX_C(1000), PX_C(-800), PX_C(3000) );
				break;
			}
			case 303: {
				FormationUrydike002* p1 = (FormationUrydike002*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p1);
				p1->position(PX_C(-500), PX_C(-800), PX_C(2000) );
				break;
			}
			case 400: {
				orderActorToFactory(10000010, FormationUnomia001b, "FormationUnomia001b-6");
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 900: {
				orderActorToFactory(10000009, FormationUnomia001a, "FormationUnomia001a-7");
				break;
			}
			case 1000: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 1500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-8");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01WalledScene, "Stage01WalledScene-9");
				break;
			}
			case 20000: {
				Stage01WalledScene* pWScene = (Stage01WalledScene*)obtainSceneFromFactory(10000002);
				addSubLast(pWScene);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_03, "Stage01_03-10");
				break;
			}
			case 30000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			case 39100: {
				orderSceneToFactory(10000004, Stage01_Climax, "Stage01_Climax-11");
				break;
			}
			case 40000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000004);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 19-1 ? _cnt_event+1 : _cnt_event);
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
