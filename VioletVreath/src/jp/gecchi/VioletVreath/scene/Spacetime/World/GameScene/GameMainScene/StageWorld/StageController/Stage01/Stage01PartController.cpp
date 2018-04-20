#include "Stage01PartController.h"


#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"
#include "part/Stage01WallScene.h"
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

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,300,500,600,19700,20300,39700,40300};
	_paFrame_NextEvent = new frame[8];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 8;
	wishScene(10000000, Stage01_Climax, "Stage01_Climax-10000000");
	wishScene(10000001, Stage01WallScene, "Stage01WallScene-10000001");
	wishActor(10000002, EnemyOebiusController001, "EnemyOebiusController001-10000002");
	wishActor(10000003, EnemyOebiusController002, "EnemyOebiusController002-10000003");
	wishActor(10000004, EnemyErmione, "EnemyErmione-10000004");
    // gen01 end
    useProgress(PROG_BANPEI);
}

void Stage01PartController::initialize() {
    getProgress()->reset(PROG_INIT);
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
			case 300: {
				addSubLast(receiveScene(10000001));
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000004);
				bringSceneMediator()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)receiveActor(10000002);
				bringSceneMediator()->addSubGroup(p1);
				p1->setPosition(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 600: {
				addSubLast(receiveScene(10000000));
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)receiveActor(10000003);
				bringSceneMediator()->addSubGroup(p2);
				p2->setPosition(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 19700: {
				wishActor(10000005, EnemyErmione, "EnemyErmione-10000005");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000005);
				bringSceneMediator()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 39700: {
				wishActor(10000006, EnemyErmione, "EnemyErmione-10000006");
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000006);
				bringSceneMediator()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
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
        _TRACE_(FUNC_NAME<<" EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
