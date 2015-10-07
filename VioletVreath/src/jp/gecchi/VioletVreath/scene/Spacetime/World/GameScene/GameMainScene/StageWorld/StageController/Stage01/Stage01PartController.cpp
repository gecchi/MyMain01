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

#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,20,100,300,302,600,620,1000,1600,2300,2900,3600,4200,9100,10000,29100,30000,39100,40000};
	_paFrame_NextEvent = new frame[19];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 19;
	orderActorToFactory(10000004, EnemyOebiusController001, "EnemyOebiusController001-1");
	orderActorToFactory(10000006, FormationUrydike001, "FormationUrydike001-2");
	orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-3");
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
				orderActorToFactory(10000005, EnemyOebiusController002, "EnemyOebiusController002-4");
				break;
			}
			case 100: {
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-5");
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 302: {
				FormationUrydike001* p3 = (FormationUrydike001*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(p3);
				p3->position(PX_C(1000), PX_C(-800), PX_C(3000) );
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 1000: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-6");
				break;
			}
			case 1600: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 2300: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-7");
				break;
			}
			case 2900: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 3600: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-8");
				break;
			}
			case 4200: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-9");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-10");
				break;
			}
			case 30000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 39100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-11");
				break;
			}
			case 40000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
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
            if (pProg->hasJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (pProg->hasArrivedAt(60)) {
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
