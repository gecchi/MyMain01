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
	frame f[] = {1,100,160,220,280,340,400,460,500,520,580,600,640,700,760,820,880,940,1000,1060,1120,1180,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960};
	_paFrame_NextEvent = new frame[35];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 35;
	orderActorToFactory(10000000, EnemyOebiusController001, "EnemyOebiusController001-10000000");
	orderActorToFactory(10000001, EnemyOebiusController002, "EnemyOebiusController002-10000001");
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
				orderActorToFactory(10000002, EnemyOebiusController001, "EnemyOebiusController001-10000002");
				break;
			}
			case 160: {
				orderActorToFactory(10000003, EnemyOebiusController001, "EnemyOebiusController001-10000003");
				break;
			}
			case 220: {
				orderActorToFactory(10000004, EnemyOebiusController001, "EnemyOebiusController001-10000004");
				break;
			}
			case 280: {
				orderActorToFactory(10000005, EnemyOebiusController001, "EnemyOebiusController001-10000005");
				break;
			}
			case 340: {
				orderActorToFactory(10000006, EnemyOebiusController001, "EnemyOebiusController001-10000006");
				break;
			}
			case 400: {
				orderActorToFactory(10000007, EnemyOebiusController001, "EnemyOebiusController001-10000007");
				break;
			}
			case 460: {
				orderActorToFactory(10000008, EnemyOebiusController001, "EnemyOebiusController001-10000008");
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 520: {
				orderActorToFactory(10000009, EnemyOebiusController001, "EnemyOebiusController001-10000009");
				break;
			}
			case 580: {
				orderActorToFactory(10000010, EnemyOebiusController001, "EnemyOebiusController001-10000010");
				break;
			}
			case 600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 640: {
				orderActorToFactory(10000011, EnemyOebiusController001, "EnemyOebiusController001-10000011");
				break;
			}
			case 700: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000012, EnemyOebiusController001, "EnemyOebiusController001-10000012");
				break;
			}
			case 760: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000013, EnemyOebiusController001, "EnemyOebiusController001-10000013");
				break;
			}
			case 820: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000014, EnemyOebiusController001, "EnemyOebiusController001-10000014");
				break;
			}
			case 880: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000015, EnemyOebiusController001, "EnemyOebiusController001-10000015");
				break;
			}
			case 940: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000016, EnemyOebiusController001, "EnemyOebiusController001-10000016");
				break;
			}
			case 1000: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000017, EnemyOebiusController001, "EnemyOebiusController001-10000017");
				break;
			}
			case 1060: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000018, EnemyOebiusController001, "EnemyOebiusController001-10000018");
				break;
			}
			case 1120: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000019, EnemyOebiusController001, "EnemyOebiusController001-10000019");
				break;
			}
			case 1180: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000020, EnemyOebiusController001, "EnemyOebiusController001-10000020");
				break;
			}
			case 1240: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000021, EnemyOebiusController001, "EnemyOebiusController001-10000021");
				break;
			}
			case 1300: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000022, EnemyOebiusController001, "EnemyOebiusController001-10000022");
				break;
			}
			case 1360: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				orderActorToFactory(10000023, EnemyOebiusController001, "EnemyOebiusController001-10000023");
				break;
			}
			case 1420: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1480: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1540: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1600: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1660: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1720: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1780: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1840: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1900: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			case 1960: {
				EnemyOebiusController001* p3 = (EnemyOebiusController001*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(p3);
				p3->position(RND_ABOUT(PX_C(800), PX_C(2000)), RND_ABOUT(0, PX_C(2000)), RND(0, PX_C(5000)) );
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
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
