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
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100};
	_paFrame_NextEvent = new frame[12];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 12;
	orderActorToFactory(10000000, FormationOebius001, "FormationOebius001-1");
	orderActorToFactory(10000001, FormationOebius001, "FormationOebius001-2");
	orderActorToFactory(10000002, FormationOebius001, "FormationOebius001-3");
	orderActorToFactory(10000003, FormationOebius001, "FormationOebius001-4");
	orderActorToFactory(10000004, FormationOebius001, "FormationOebius001-5");
	orderActorToFactory(10000005, FormationOebius002, "FormationOebius002-6");
	orderActorToFactory(10000006, FormationOebius002, "FormationOebius002-7");
	orderActorToFactory(10000007, FormationOebius002, "FormationOebius002-8");
	orderActorToFactory(10000008, FormationOebius002, "FormationOebius002-9");
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
				FormationOebius001* pF1 = (FormationOebius001*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF1->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				orderActorToFactory(10000009, FormationOebius002, "FormationOebius002-10");
				break;
			}
			case 200: {
				FormationOebius001* pF1 = (FormationOebius001*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF1->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				orderActorToFactory(10000010, FormationOebius002, "FormationOebius002-11");
				break;
			}
			case 300: {
				FormationOebius001* pF1 = (FormationOebius001*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF1->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 400: {
				FormationOebius001* pF1 = (FormationOebius001*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF1->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 500: {
				FormationOebius001* pF1 = (FormationOebius001*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pF1);
				pF1->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF1->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 600: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 700: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 800: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 900: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1000: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1100: {
				FormationOebius002* pF2 = (FormationOebius002*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pF2);
				pF2->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF2->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 12-1 ? _cnt_event+1 : _cnt_event);
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
