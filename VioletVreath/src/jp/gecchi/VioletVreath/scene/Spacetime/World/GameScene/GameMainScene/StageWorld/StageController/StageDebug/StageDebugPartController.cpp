#include "StageDebugPartController.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebug.h"
#include "part/StageDebugPart01.h"
#include "part/StageDebugPart02.h"
#include "part/StageDebugPart03.h"
#include "part/StageDebugPartClimax.h"
#include "part/StageDebugPartWall.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_FAINAL ,
    PROG_BANPEI,
};

StageDebugPartController::StageDebugPartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "StageDebugPartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,5,100,105,205,305,400,405,500,505,605,705,805,905,1005,1105,3200,4100,7200,8100,9000};
	_paFrame_NextEvent = new frame[21];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 21;
	requestScene(10000000, StageDebugPart01, "StageDebugPart01-10000000");
	requestActor(10000004, EnemyOebiusController001, "EnemyOebiusController001-10000004");
	requestActor(10000005, EnemyErelmanController003, "EnemyErelmanController003-10000005");
	requestActor(10000006, EnemyEtis, "EnemyEtis-10000006");
	requestActor(10000007, EnemyEtis, "EnemyEtis-10000007");
	requestActor(10000008, EnemyEtis, "EnemyEtis-10000008");
	requestActor(10000009, EnemyEtis, "EnemyEtis-10000009");
	requestActor(10000010, EnemyEtis, "EnemyEtis-10000010");
	requestActor(10000011, EnemyEtis, "EnemyEtis-10000011");
    // gen01 end
    useProgress(PROG_BANPEI);
}

void StageDebugPartController::initialize() {
    getProgress()->reset(PROG_INIT);
}

void StageDebugPartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000006);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000012, EnemyEtis, "EnemyEtis-10000012");
				break;
			}
			case 100: {
				addSubLast(receiveScene(10000000));
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000007);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000013, EnemyEtis, "EnemyEtis-10000013");
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000008);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000014, EnemyEtis, "EnemyEtis-10000014");
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000009);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000015, EnemyEtis, "EnemyEtis-10000015");
				break;
			}
			case 400: {
				EnemyErelmanController003* p1 = (EnemyErelmanController003*)receiveActor(10000005);
				bringSceneMediator()->addSubGroup(p1);
				p1->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000010);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000016, EnemyEtis, "EnemyEtis-10000016");
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)receiveActor(10000004);
				bringSceneMediator()->addSubGroup(p1);
				p1->setPosition(PX_C(1400), PX_C(500), PX_C(500) );
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000011);
				bringSceneMediator()->addSubGroup(pEtis);
				requestActor(10000017, EnemyEtis, "EnemyEtis-10000017");
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000012);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000013);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000014);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000015);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000016);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000017);
				bringSceneMediator()->addSubGroup(pEtis);
				break;
			}
			case 3200: {
				requestScene(10000001, StageDebugPart02, "StageDebugPart02-10000001");
				break;
			}
			case 4100: {
				addSubLast(receiveScene(10000001));
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03, "StageDebugPart03-10000002");
				break;
			}
			case 8100: {
				addSubLast(receiveScene(10000002));
				requestScene(10000003, StageDebugPartClimax, "StageDebugPartClimax-10000003");
				break;
			}
			case 9000: {
				addSubLast(receiveScene(10000003));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 21-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STGDBGClimax_終焉の処理
                _TRACE_("STGDBGClimax_終焉のStageDebugPartController::PROG_FAINALきた");
            }

            if (pProg->hasArrivedAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGE_DEBUG_PART_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void StageDebugPartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGE_DEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE_DEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE_DEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE_DEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE_DEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE_DEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE_DEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE_DEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE_DEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE_DEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStageDebugPartController::PROG_FAINALに切り替える
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
