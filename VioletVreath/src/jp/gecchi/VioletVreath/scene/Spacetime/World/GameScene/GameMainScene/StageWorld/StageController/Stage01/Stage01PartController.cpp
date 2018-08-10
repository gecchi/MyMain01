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
	frame f[] = {1,100,300,400,500,600,900,1000,1500,1900,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4400,4500,5000,5900,6500,7900,8500,9100,9400,9900,10000,10500,11900,12500,13900,14400,14500,15000,15900,16500,17900,18500,19400,19900,20000,20500,21900,22500,23900,24400,24500,25000,25900,26500,27900,28500,29100,29400,29900,30000,30500,31900,32500,33900,34100,34500,35000,35900,36500,37900,38500,39900,40500,41900,42500,43900,44500,45900,46500,47900,48500,49900,50500,51900,52500,53900,54500,55900,56500,57900,58500};
	_paFrame_NextEvent = new frame[97];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 97;
	wantActor(10000004, EnemyOzartia, "EnemyOzartia-10000004");
	wantActor(10000005, FormationDelheid001, "FormationDelheid001-10000005");
	wantActor(10000006, FormationDelheid001, "FormationDelheid001-10000006");
	wantActor(10000007, EnemyOebiusController001, "EnemyOebiusController001-10000007");
	wantActor(10000008, EnemyOebiusController002, "EnemyOebiusController002-10000008");
	wantActor(10000010, EnemyErelmanController003, "EnemyErelmanController003-10000010");
	wantActor(10000013, EnemyErmione, "EnemyErmione-10000013");
	wantActor(10000014, FormationEres001, "FormationEres001-10000014");
	wantActor(10000015, EnemyDrastea, "EnemyDrastea-10000015");
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
			case 100: {
				wantScene(10000000, Stage01_01, "Stage01_01-10000000");
				break;
			}
			case 300: {
				EnemyOzartia* p = (EnemyOzartia*)grantActor(10000004);
				bringSceneMediator()->addSubGroup(p);
				p->setPosition(1000000,0,0);
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000005);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
				EnemyErmione* pE = (EnemyErmione*)grantActor(10000013);
				bringSceneMediator()->addSubGroup(pE);
				pE->setPosition(PX_C(1000),0,0);
				break;
			}
			case 400: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000006);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
				wantActor(10000009, FormationUrydike001, "FormationUrydike001-10000009");
				EnemyErelmanController003* p1 = (EnemyErelmanController003*)grantActor(10000010);
				bringSceneMediator()->addSubGroup(p1);
				p1->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				wantActor(10000012, FormationUnomia001b, "FormationUnomia001b-10000012");
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)grantActor(10000007);
				bringSceneMediator()->addSubGroup(p1);
				p1->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				bringSceneMediator()->addSubGroup(grantActor(10000014));
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000015);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)grantActor(10000008);
				bringSceneMediator()->addSubGroup(p2);
				p2->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				break;
			}
			case 900: {
				wantActor(10000011, FormationUnomia001a, "FormationUnomia001a-10000011");
				break;
			}
			case 1000: {
				addSubLast(grantScene(10000000));
				FormationUrydike001* p3 = (FormationUrydike001*)grantActor(10000009);
				bringSceneMediator()->addSubGroup(p3);
				p3->setPosition(PX_C(1000), PX_C(-800), PX_C(3000) );
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)grantActor(10000012);
				bringSceneMediator()->addSubGroup(pFormationUnomia);
				break;
			}
			case 1500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)grantActor(10000011);
				bringSceneMediator()->addSubGroup(pFormationUnomia);
				break;
			}
			case 1900: {
				wantActor(10000016, EnemyDrastea, "EnemyDrastea-10000016");
				break;
			}
			case 2400: {
				wantActor(10000051, FormationDelheid001, "FormationDelheid001-10000051");
				break;
			}
			case 2500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000016);
				bringSceneMediator()->addSubGroup(p);
				wantActor(10000052, FormationDelheid001, "FormationDelheid001-10000052");
				break;
			}
			case 2600: {
				wantActor(10000053, FormationDelheid001, "FormationDelheid001-10000053");
				break;
			}
			case 2700: {
				wantActor(10000054, FormationDelheid001, "FormationDelheid001-10000054");
				break;
			}
			case 2800: {
				wantActor(10000055, FormationDelheid001, "FormationDelheid001-10000055");
				break;
			}
			case 2900: {
				wantActor(10000056, FormationDelheid001, "FormationDelheid001-10000056");
				break;
			}
			case 3000: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000051);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(0), D_ANG(-40), D_ANG(0));
				wantActor(10000057, FormationDelheid001, "FormationDelheid001-10000057");
				break;
			}
			case 3100: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000052);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(0), D_ANG(-30), D_ANG(0));
				wantActor(10000058, FormationDelheid001, "FormationDelheid001-10000058");
				break;
			}
			case 3200: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000053);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(0), D_ANG(-20), D_ANG(0));
				wantActor(10000059, FormationDelheid001, "FormationDelheid001-10000059");
				break;
			}
			case 3300: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000054);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(0), D_ANG(-10), D_ANG(0));
				break;
			}
			case 3400: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000055);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C(   0), PX_C(500), D_ANG(0), D_ANG(  0), D_ANG(0));
				break;
			}
			case 3500: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000056);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(0), D_ANG( 10), D_ANG(0));
				break;
			}
			case 3600: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000057);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(0), D_ANG( 20), D_ANG(0));
				break;
			}
			case 3700: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000058);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
				break;
			}
			case 3800: {
				FormationDelheid001* pF = (FormationDelheid001*)grantActor(10000059);
				bringSceneMediator()->addSubGroup(pF);
				pF->setPosition(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
				break;
			}
			case 3900: {
				wantActor(10000017, EnemyDrastea, "EnemyDrastea-10000017");
				break;
			}
			case 4400: {
				wantActor(10000045, FormationGeria001, "FormationGeria001-10000045");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000017);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 5000: {
				FormationGeria001* pF1 = (FormationGeria001*)grantActor(10000045);
				bringSceneMediator()->addSubGroup(pF1);
				break;
			}
			case 5900: {
				wantActor(10000018, EnemyDrastea, "EnemyDrastea-10000018");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000018);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 7900: {
				wantActor(10000019, EnemyDrastea, "EnemyDrastea-10000019");
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000019);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 9100: {
				wantScene(10000001, Stage01_02, "Stage01_02-10000001");
				break;
			}
			case 9400: {
				wantActor(10000046, FormationGeria001, "FormationGeria001-10000046");
				break;
			}
			case 9900: {
				wantActor(10000020, EnemyDrastea, "EnemyDrastea-10000020");
				break;
			}
			case 10000: {
				addSubLast(grantScene(10000001));
				FormationGeria001* pF2 = (FormationGeria001*)grantActor(10000046);
				bringSceneMediator()->addSubGroup(pF2);
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000020);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 11900: {
				wantActor(10000021, EnemyDrastea, "EnemyDrastea-10000021");
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000021);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 13900: {
				wantActor(10000022, EnemyDrastea, "EnemyDrastea-10000022");
				break;
			}
			case 14400: {
				wantActor(10000047, FormationGeria001, "FormationGeria001-10000047");
				break;
			}
			case 14500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000022);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 15000: {
				FormationGeria001* pF3 = (FormationGeria001*)grantActor(10000047);
				bringSceneMediator()->addSubGroup(pF3);
				break;
			}
			case 15900: {
				wantActor(10000023, EnemyDrastea, "EnemyDrastea-10000023");
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000023);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 17900: {
				wantActor(10000024, EnemyDrastea, "EnemyDrastea-10000024");
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000024);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 19400: {
				wantActor(10000048, FormationGeria001, "FormationGeria001-10000048");
				break;
			}
			case 19900: {
				wantActor(10000025, EnemyDrastea, "EnemyDrastea-10000025");
				break;
			}
			case 20000: {
				FormationGeria001* pF4 = (FormationGeria001*)grantActor(10000048);
				bringSceneMediator()->addSubGroup(pF4);
				break;
			}
			case 20500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000025);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 21900: {
				wantActor(10000026, EnemyDrastea, "EnemyDrastea-10000026");
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000026);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 23900: {
				wantActor(10000027, EnemyDrastea, "EnemyDrastea-10000027");
				break;
			}
			case 24400: {
				wantActor(10000049, FormationGeria001, "FormationGeria001-10000049");
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000027);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 25000: {
				FormationGeria001* pF5 = (FormationGeria001*)grantActor(10000049);
				bringSceneMediator()->addSubGroup(pF5);
				break;
			}
			case 25900: {
				wantActor(10000028, EnemyDrastea, "EnemyDrastea-10000028");
				break;
			}
			case 26500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000028);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 27900: {
				wantActor(10000029, EnemyDrastea, "EnemyDrastea-10000029");
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000029);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 29100: {
				wantScene(10000002, Stage01_03, "Stage01_03-10000002");
				break;
			}
			case 29400: {
				wantActor(10000050, FormationGeria001, "FormationGeria001-10000050");
				break;
			}
			case 29900: {
				wantActor(10000030, EnemyDrastea, "EnemyDrastea-10000030");
				break;
			}
			case 30000: {
				addSubLast(grantScene(10000002));
				FormationGeria001* pF6 = (FormationGeria001*)grantActor(10000050);
				bringSceneMediator()->addSubGroup(pF6);
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000030);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 31900: {
				wantActor(10000031, EnemyDrastea, "EnemyDrastea-10000031");
				break;
			}
			case 32500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000031);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 33900: {
				wantActor(10000032, EnemyDrastea, "EnemyDrastea-10000032");
				break;
			}
			case 34100: {
				wantScene(10000003, Stage01_Climax, "Stage01_Climax-10000003");
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000032);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 35000: {
				addSubLast(grantScene(10000003));
				break;
			}
			case 35900: {
				wantActor(10000033, EnemyDrastea, "EnemyDrastea-10000033");
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000033);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 37900: {
				wantActor(10000034, EnemyDrastea, "EnemyDrastea-10000034");
				break;
			}
			case 38500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000034);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 39900: {
				wantActor(10000035, EnemyDrastea, "EnemyDrastea-10000035");
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000035);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 41900: {
				wantActor(10000036, EnemyDrastea, "EnemyDrastea-10000036");
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000036);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 43900: {
				wantActor(10000037, EnemyDrastea, "EnemyDrastea-10000037");
				break;
			}
			case 44500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000037);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 45900: {
				wantActor(10000038, EnemyDrastea, "EnemyDrastea-10000038");
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000038);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 47900: {
				wantActor(10000039, EnemyDrastea, "EnemyDrastea-10000039");
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000039);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 49900: {
				wantActor(10000040, EnemyDrastea, "EnemyDrastea-10000040");
				break;
			}
			case 50500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000040);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 51900: {
				wantActor(10000041, EnemyDrastea, "EnemyDrastea-10000041");
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000041);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 53900: {
				wantActor(10000042, EnemyDrastea, "EnemyDrastea-10000042");
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000042);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 55900: {
				wantActor(10000043, EnemyDrastea, "EnemyDrastea-10000043");
				break;
			}
			case 56500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000043);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			case 57900: {
				wantActor(10000044, EnemyDrastea, "EnemyDrastea-10000044");
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)grantActor(10000044);
				bringSceneMediator()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 97-1 ? _cnt_event+1 : _cnt_event);
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
