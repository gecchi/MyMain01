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
	frame f[] = {1,100,300,500,600,1900,2500,3200,3900,4100,4500,5900,6500,7200,7900,8100,8500,9900,10500,11900,12500,13900,14500,15900,16500,17900,18500,19700,19900,20300,20500,21100,21900,22000,22500,23900,24500,25900,26500,27900,28500,29900,30500,31900,32500,33900,34500,35900,36500,37900,38500,39700,39900,40300,40500,41900,42500,43900,44500,45900,46500,47900,48500,49900,50500,51900,52500,53900,54500,55900,56500,57900,58500};
	_paFrame_NextEvent = new frame[73];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 73;
	requestScene(10000000, StageDebugPart01, "StageDebugPart01-10000000");
	requestActor(10000004, EnemyErmione, "EnemyErmione-10000004");
	requestActor(10000007, EnemyDrastea, "EnemyDrastea-10000007");
	requestActor(10000037, VarietyRatislavia002, "VarietyRatislavia002-10000037");
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
			case 100: {
				appendChild(receiveScene(10000000));
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000004);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000007);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 600: {
				VarietyRatislavia002* pRatislavia = (VarietyRatislavia002*)receiveActor(10000037);
				bringSceneMediator()->appendGroupChild(pRatislavia);
				break;
			}
			case 1900: {
				requestActor(10000008, EnemyDrastea, "EnemyDrastea-10000008");
				break;
			}
			case 2500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000008);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 3200: {
				requestScene(10000001, StageDebugPart02, "StageDebugPart02-10000001");
				break;
			}
			case 3900: {
				requestActor(10000009, EnemyDrastea, "EnemyDrastea-10000009");
				break;
			}
			case 4100: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000009);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 5900: {
				requestActor(10000010, EnemyDrastea, "EnemyDrastea-10000010");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000010);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03, "StageDebugPart03-10000002");
				break;
			}
			case 7900: {
				requestActor(10000011, EnemyDrastea, "EnemyDrastea-10000011");
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000011);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 9900: {
				requestActor(10000012, EnemyDrastea, "EnemyDrastea-10000012");
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000012);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 11900: {
				requestActor(10000013, EnemyDrastea, "EnemyDrastea-10000013");
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000013);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 13900: {
				requestActor(10000014, EnemyDrastea, "EnemyDrastea-10000014");
				break;
			}
			case 14500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000014);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 15900: {
				requestActor(10000015, EnemyDrastea, "EnemyDrastea-10000015");
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000015);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 17900: {
				requestActor(10000016, EnemyDrastea, "EnemyDrastea-10000016");
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000016);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 19700: {
				requestActor(10000005, EnemyErmione, "EnemyErmione-10000005");
				break;
			}
			case 19900: {
				requestActor(10000017, EnemyDrastea, "EnemyDrastea-10000017");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000005);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000017);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 21100: {
				requestScene(10000003, StageDebugPartClimax, "StageDebugPartClimax-10000003");
				break;
			}
			case 21900: {
				requestActor(10000018, EnemyDrastea, "EnemyDrastea-10000018");
				break;
			}
			case 22000: {
				appendChild(receiveScene(10000003));
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000018);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 23900: {
				requestActor(10000019, EnemyDrastea, "EnemyDrastea-10000019");
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000019);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 25900: {
				requestActor(10000020, EnemyDrastea, "EnemyDrastea-10000020");
				break;
			}
			case 26500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000020);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 27900: {
				requestActor(10000021, EnemyDrastea, "EnemyDrastea-10000021");
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000021);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 29900: {
				requestActor(10000022, EnemyDrastea, "EnemyDrastea-10000022");
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000022);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 31900: {
				requestActor(10000023, EnemyDrastea, "EnemyDrastea-10000023");
				break;
			}
			case 32500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000023);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 33900: {
				requestActor(10000024, EnemyDrastea, "EnemyDrastea-10000024");
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000024);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 35900: {
				requestActor(10000025, EnemyDrastea, "EnemyDrastea-10000025");
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000025);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 37900: {
				requestActor(10000026, EnemyDrastea, "EnemyDrastea-10000026");
				break;
			}
			case 38500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000026);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 39700: {
				requestActor(10000006, EnemyErmione, "EnemyErmione-10000006");
				break;
			}
			case 39900: {
				requestActor(10000027, EnemyDrastea, "EnemyDrastea-10000027");
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000006);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000027);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 41900: {
				requestActor(10000028, EnemyDrastea, "EnemyDrastea-10000028");
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000028);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 43900: {
				requestActor(10000029, EnemyDrastea, "EnemyDrastea-10000029");
				break;
			}
			case 44500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000029);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 45900: {
				requestActor(10000030, EnemyDrastea, "EnemyDrastea-10000030");
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000030);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 47900: {
				requestActor(10000031, EnemyDrastea, "EnemyDrastea-10000031");
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000031);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 49900: {
				requestActor(10000032, EnemyDrastea, "EnemyDrastea-10000032");
				break;
			}
			case 50500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000032);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 51900: {
				requestActor(10000033, EnemyDrastea, "EnemyDrastea-10000033");
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000033);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 53900: {
				requestActor(10000034, EnemyDrastea, "EnemyDrastea-10000034");
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000034);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 55900: {
				requestActor(10000035, EnemyDrastea, "EnemyDrastea-10000035");
				break;
			}
			case 56500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000035);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 57900: {
				requestActor(10000036, EnemyDrastea, "EnemyDrastea-10000036");
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(10000036);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 73-1 ? _cnt_event+1 : _cnt_event);
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
                throwEventUpperTree(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END); //ステージエンドを上位に伝える
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
    if (prm_no == EVENT_STAGEDEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStageDebugPartController::PROG_FAINALに切り替える
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
