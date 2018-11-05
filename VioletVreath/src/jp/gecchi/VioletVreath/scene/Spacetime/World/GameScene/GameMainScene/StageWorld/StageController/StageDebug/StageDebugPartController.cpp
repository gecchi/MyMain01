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
	frame f[] = {1,100,3200,4100,7200,8100,11100,12000};
	_paFrame_NextEvent = new frame[8];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 8;
	requestScene(10000000, StageDebugPart01, "StageDebugPart01-10000000");
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
			case 3200: {
				requestScene(10000001, StageDebugPart02, "StageDebugPart02-10000001");
				break;
			}
			case 4100: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03, "StageDebugPart03-10000002");
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				break;
			}
			case 11100: {
				requestScene(10000003, StageDebugPartClimax, "StageDebugPartClimax-10000003");
				break;
			}
			case 12000: {
				appendChild(receiveScene(10000003));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 8-1 ? _cnt_event+1 : _cnt_event);
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
