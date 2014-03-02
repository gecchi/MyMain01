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
	frame f[] = {1,100,120,300,540,780,1020,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,9100,10000,19100,20000,29100,30000};
	_paFrame_NextEvent = new frame[31];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 31;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, FormationAppho001a, "FormationAppho001a-2");
	orderActorToFactory(10000005, FormationAppho001b, "FormationAppho001b-3");
	orderActorToFactory(10000006, FormationAppho001a, "FormationAppho001a-4");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
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
				break;
			}
			case 120: {
				orderActorToFactory(10000007, FormationAppho001b, "FormationAppho001b-5");
				break;
			}
			case 300: {
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 540: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 780: {
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1020: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 4100: {
				orderActorToFactory(10000008, FormationDelheid001, "FormationDelheid001-6");
				break;
			}
			case 4200: {
				orderActorToFactory(10000009, FormationDelheid001, "FormationDelheid001-7");
				break;
			}
			case 4300: {
				orderActorToFactory(10000010, FormationDelheid001, "FormationDelheid001-8");
				break;
			}
			case 4400: {
				orderActorToFactory(10000011, FormationDelheid001, "FormationDelheid001-9");
				break;
			}
			case 4500: {
				orderActorToFactory(10000012, FormationDelheid001, "FormationDelheid001-10");
				break;
			}
			case 4600: {
				orderActorToFactory(10000013, FormationDelheid001, "FormationDelheid001-11");
				break;
			}
			case 4700: {
				orderActorToFactory(10000014, FormationDelheid001, "FormationDelheid001-12");
				break;
			}
			case 4800: {
				orderActorToFactory(10000015, FormationDelheid001, "FormationDelheid001-13");
				break;
			}
			case 4900: {
				orderActorToFactory(10000016, FormationDelheid001, "FormationDelheid001-14");
				break;
			}
			case 5000: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5200: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-15");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-16");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-17");
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
		_cnt_event = (_cnt_event < 31-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
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
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
