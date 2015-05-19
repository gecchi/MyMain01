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
	frame f[] = {1,20,300,302,400,501,600,620,900,1000,1500};
	_paFrame_NextEvent = new frame[11];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 11;
	orderActorToFactory(10000000, EnemyOzartia, "EnemyOzartia-1");
	orderActorToFactory(10000001, EnemyOebiusController001, "EnemyOebiusController001-2");
	orderActorToFactory(10000003, FormationUrydike001, "FormationUrydike001-3");
	orderActorToFactory(10000007, FormationHalia, "FormationHalia-4");
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
				orderActorToFactory(10000002, EnemyOebiusController002, "EnemyOebiusController002-5");
				break;
			}
			case 300: {
				EnemyOzartia* p = (EnemyOzartia*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(p);
				p->position(1000000,0,0);
				break;
			}
			case 302: {
				FormationUrydike001* p3 = (FormationUrydike001*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(p3);
				p3->position(PX_C(1000), PX_C(-800), PX_C(3000) );
				break;
			}
			case 400: {
				orderActorToFactory(10000004, FormationUrydike002, "FormationUrydike002-6");
				orderActorToFactory(10000006, FormationUnomia001b, "FormationUnomia001b-7");
				break;
			}
			case 501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 900: {
				orderActorToFactory(10000005, FormationUnomia001a, "FormationUnomia001a-8");
				break;
			}
			case 1000: {
				FormationUrydike002* p4 = (FormationUrydike002*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(p4);
				p4->position(PX_C(-500), PX_C(-800), PX_C(2000) );
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			case 1500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pFormationUnomia);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 11-1 ? _cnt_event+1 : _cnt_event);
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
