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
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1300,1400,1500,1700,1900,2300,2400,3300,3400,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,9100,10000,19100,20000,29100,30000};
	_paFrame_NextEvent = new frame[45];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 45;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-2");
	orderActorToFactory(10000009, FormationEbe001, "FormationEbe001-3");
	orderActorToFactory(10000010, EnemyEsperia, "EnemyEsperia-4");
	orderActorToFactory(10000011, EnemyEsperia, "EnemyEsperia-5");
	orderActorToFactory(10000012, EnemyEsperia, "EnemyEsperia-6");
	orderActorToFactory(10000013, EnemyEsperia, "EnemyEsperia-7");
	orderActorToFactory(10000019, FormationAntiope001, "FormationAntiope001-8");
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
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				orderActorToFactory(10000020, FormationAntiope001, "FormationAntiope001-9");
				break;
			}
			case 200: {
				orderActorToFactory(10000014, EnemyEsperia, "EnemyEsperia-10");
				break;
			}
			case 300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				FormationEbe001* pF11 = (FormationEbe001*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF11);
				EnemyEsperia* p12 = (EnemyEsperia*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p12);
				break;
			}
			case 400: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-13");
				orderActorToFactory(10000015, EnemyEsperia, "EnemyEsperia-14");
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 500: {
				EnemyEsperia* p15 = (EnemyEsperia*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p15);
				break;
			}
			case 600: {
				orderActorToFactory(10000016, EnemyEsperia, "EnemyEsperia-16");
				break;
			}
			case 700: {
				EnemyEsperia* p17 = (EnemyEsperia*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p17);
				break;
			}
			case 800: {
				orderActorToFactory(10000017, EnemyEsperia, "EnemyEsperia-18");
				break;
			}
			case 900: {
				EnemyEsperia* p19 = (EnemyEsperia*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p19);
				break;
			}
			case 1000: {
				orderActorToFactory(10000018, EnemyEsperia, "EnemyEsperia-20");
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pFAnti);
				break;
			}
			case 1100: {
				EnemyEsperia* p21 = (EnemyEsperia*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p21);
				break;
			}
			case 1300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				EnemyEsperia* p22 = (EnemyEsperia*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p22);
				break;
			}
			case 1400: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-23");
				break;
			}
			case 1500: {
				EnemyEsperia* p24 = (EnemyEsperia*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p24);
				break;
			}
			case 1700: {
				EnemyEsperia* p25 = (EnemyEsperia*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p25);
				break;
			}
			case 1900: {
				EnemyEsperia* p26 = (EnemyEsperia*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(p26);
				break;
			}
			case 2300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 2400: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-27");
				break;
			}
			case 3300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 3400: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-28");
				break;
			}
			case 4100: {
				orderActorToFactory(10000021, FormationDelheid001, "FormationDelheid001-29");
				break;
			}
			case 4200: {
				orderActorToFactory(10000022, FormationDelheid001, "FormationDelheid001-30");
				break;
			}
			case 4300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				orderActorToFactory(10000023, FormationDelheid001, "FormationDelheid001-31");
				break;
			}
			case 4400: {
				orderActorToFactory(10000024, FormationDelheid001, "FormationDelheid001-32");
				break;
			}
			case 4500: {
				orderActorToFactory(10000025, FormationDelheid001, "FormationDelheid001-33");
				break;
			}
			case 4600: {
				orderActorToFactory(10000026, FormationDelheid001, "FormationDelheid001-34");
				break;
			}
			case 4700: {
				orderActorToFactory(10000027, FormationDelheid001, "FormationDelheid001-35");
				break;
			}
			case 4800: {
				orderActorToFactory(10000028, FormationDelheid001, "FormationDelheid001-36");
				break;
			}
			case 4900: {
				orderActorToFactory(10000029, FormationDelheid001, "FormationDelheid001-37");
				break;
			}
			case 5000: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5200: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-38");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-39");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-40");
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
		_cnt_event = (_cnt_event < 45-1 ? _cnt_event+1 : _cnt_event);
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
