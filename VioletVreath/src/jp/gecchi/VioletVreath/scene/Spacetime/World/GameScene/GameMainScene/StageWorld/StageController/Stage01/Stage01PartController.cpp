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
	frame f[] = {1,20,100,300,400,500,600,620,1000,1500,1900,2100,2500,2900,3100,3500,3900,4100,4500,4700,5300,5500,5900,6100,6500,7500,7900,8100,8500,8900,9100,9500,9700,9900,10000,10100,10300,10500,11500,11900,12100,12500,13500,13900,14100,14500,14700,14900,15100,15300,15500,15900,16100,16500,17500,17900,18100,18500,19500,19700,19900,20100,20300,20500,20900,21100,21500,21900,22100,22500,23500,23900,24100,24500,24700,25300,25500,25900,26100,26500,26900,27100,27500,27900,28100,28500,29100,29500,29700,29900,30000,30100,30300,30500,31500,31900,32100,32500,32900,33100,33500,33900,34100,34500,34700,35300,35500,35900,36100,36500,37500,37900,38100,38500,38900,39100,39500,39700,39900,40000,40100,40300,40500,41500,41900,42100,42500,43500,43900,44100,44500,44700,44900,45100,45300,45500,45900,46100,46500,47500,47900,48100,48500,49500,49900,50100,50500,50900,51100,51500,51900,52100,52500,53500,53900,54100,54500,55500,55900,56100,56500,56900,57100,57500,57900,58100,58500};
	_paFrame_NextEvent = new frame[167];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 167;
	orderActorToFactory(10000004, EnemyOebiusController001, "EnemyOebiusController001-1");
	orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-2");
	orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000037, EnemyDrastea, "EnemyDrastea-4");
	orderActorToFactory(10000067, FormationEmilia, "FormationEmilia-5");
	orderActorToFactory(10000087, FormationGeria001, "FormationGeria001-6");
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
				orderActorToFactory(10000005, EnemyOebiusController002, "EnemyOebiusController002-7");
				break;
			}
			case 100: {
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-8");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 400: {
				orderActorToFactory(10000006, FormationUrydike002, "FormationUrydike002-9");
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 600: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(p1);
				p1->position(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 620: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(p2);
				p2->position(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 1000: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				FormationUrydike002* p4 = (FormationUrydike002*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(p4);
				p4->position(PX_C(-500), PX_C(-800), PX_C(2000) );
				break;
			}
			case 1500: {
				orderActorToFactory(10000088, FormationGeria001, "FormationGeria001-10");
				break;
			}
			case 1900: {
				orderActorToFactory(10000038, EnemyDrastea, "EnemyDrastea-11");
				break;
			}
			case 2100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 2500: {
				orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-12");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 2900: {
				orderActorToFactory(10000068, FormationEmilia, "FormationEmilia-13");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 3500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000089, FormationGeria001, "FormationGeria001-14");
				break;
			}
			case 3900: {
				orderActorToFactory(10000039, EnemyDrastea, "EnemyDrastea-15");
				break;
			}
			case 4100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 4700: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-16");
				break;
			}
			case 5300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 5500: {
				orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-17");
				orderActorToFactory(10000090, FormationGeria001, "FormationGeria001-18");
				break;
			}
			case 5900: {
				orderActorToFactory(10000040, EnemyDrastea, "EnemyDrastea-19");
				orderActorToFactory(10000069, FormationEmilia, "FormationEmilia-20");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 7500: {
				orderActorToFactory(10000091, FormationGeria001, "FormationGeria001-21");
				break;
			}
			case 7900: {
				orderActorToFactory(10000041, EnemyDrastea, "EnemyDrastea-22");
				break;
			}
			case 8100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 8500: {
				orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-23");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 8900: {
				orderActorToFactory(10000070, FormationEmilia, "FormationEmilia-24");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-25");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 9500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000092, FormationGeria001, "FormationGeria001-26");
				break;
			}
			case 9700: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-27");
				break;
			}
			case 9900: {
				orderActorToFactory(10000042, EnemyDrastea, "EnemyDrastea-28");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 10100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 10300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 11500: {
				orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-29");
				orderActorToFactory(10000093, FormationGeria001, "FormationGeria001-30");
				break;
			}
			case 11900: {
				orderActorToFactory(10000043, EnemyDrastea, "EnemyDrastea-31");
				orderActorToFactory(10000071, FormationEmilia, "FormationEmilia-32");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 13500: {
				orderActorToFactory(10000094, FormationGeria001, "FormationGeria001-33");
				break;
			}
			case 13900: {
				orderActorToFactory(10000044, EnemyDrastea, "EnemyDrastea-34");
				break;
			}
			case 14100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 14500: {
				orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-35");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 14700: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-36");
				break;
			}
			case 14900: {
				orderActorToFactory(10000072, FormationEmilia, "FormationEmilia-37");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 15300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 15500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000095, FormationGeria001, "FormationGeria001-38");
				break;
			}
			case 15900: {
				orderActorToFactory(10000045, EnemyDrastea, "EnemyDrastea-39");
				break;
			}
			case 16100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 17500: {
				orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-40");
				orderActorToFactory(10000096, FormationGeria001, "FormationGeria001-41");
				break;
			}
			case 17900: {
				orderActorToFactory(10000046, EnemyDrastea, "EnemyDrastea-42");
				orderActorToFactory(10000073, FormationEmilia, "FormationEmilia-43");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 19500: {
				orderActorToFactory(10000097, FormationGeria001, "FormationGeria001-44");
				break;
			}
			case 19700: {
				orderActorToFactory(10000011, EnemyErmione, "EnemyErmione-45");
				break;
			}
			case 19900: {
				orderActorToFactory(10000047, EnemyDrastea, "EnemyDrastea-46");
				break;
			}
			case 20100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20500: {
				orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-47");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 20900: {
				orderActorToFactory(10000074, FormationEmilia, "FormationEmilia-48");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 21500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000098, FormationGeria001, "FormationGeria001-49");
				break;
			}
			case 21900: {
				orderActorToFactory(10000048, EnemyDrastea, "EnemyDrastea-50");
				break;
			}
			case 22100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 23500: {
				orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-51");
				orderActorToFactory(10000099, FormationGeria001, "FormationGeria001-52");
				break;
			}
			case 23900: {
				orderActorToFactory(10000049, EnemyDrastea, "EnemyDrastea-53");
				orderActorToFactory(10000075, FormationEmilia, "FormationEmilia-54");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 24700: {
				orderActorToFactory(10000012, EnemyErmione, "EnemyErmione-55");
				break;
			}
			case 25300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 25500: {
				orderActorToFactory(10000100, FormationGeria001, "FormationGeria001-56");
				break;
			}
			case 25900: {
				orderActorToFactory(10000050, EnemyDrastea, "EnemyDrastea-57");
				break;
			}
			case 26100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 26500: {
				orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-58");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 26900: {
				orderActorToFactory(10000076, FormationEmilia, "FormationEmilia-59");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 27500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000101, FormationGeria001, "FormationGeria001-60");
				break;
			}
			case 27900: {
				orderActorToFactory(10000051, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 28100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-62");
				break;
			}
			case 29500: {
				orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-63");
				orderActorToFactory(10000102, FormationGeria001, "FormationGeria001-64");
				break;
			}
			case 29700: {
				orderActorToFactory(10000013, EnemyErmione, "EnemyErmione-65");
				break;
			}
			case 29900: {
				orderActorToFactory(10000052, EnemyDrastea, "EnemyDrastea-66");
				orderActorToFactory(10000077, FormationEmilia, "FormationEmilia-67");
				break;
			}
			case 30000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 30300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 31500: {
				orderActorToFactory(10000103, FormationGeria001, "FormationGeria001-68");
				break;
			}
			case 31900: {
				orderActorToFactory(10000053, EnemyDrastea, "EnemyDrastea-69");
				break;
			}
			case 32100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 32500: {
				orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-70");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 32900: {
				orderActorToFactory(10000078, FormationEmilia, "FormationEmilia-71");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 33500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000104, FormationGeria001, "FormationGeria001-72");
				break;
			}
			case 33900: {
				orderActorToFactory(10000054, EnemyDrastea, "EnemyDrastea-73");
				break;
			}
			case 34100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 34700: {
				orderActorToFactory(10000014, EnemyErmione, "EnemyErmione-74");
				break;
			}
			case 35300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 35500: {
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-75");
				orderActorToFactory(10000105, FormationGeria001, "FormationGeria001-76");
				break;
			}
			case 35900: {
				orderActorToFactory(10000055, EnemyDrastea, "EnemyDrastea-77");
				orderActorToFactory(10000079, FormationEmilia, "FormationEmilia-78");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 37500: {
				orderActorToFactory(10000106, FormationGeria001, "FormationGeria001-79");
				break;
			}
			case 37900: {
				orderActorToFactory(10000056, EnemyDrastea, "EnemyDrastea-80");
				break;
			}
			case 38100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 38500: {
				orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-81");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 38900: {
				orderActorToFactory(10000080, FormationEmilia, "FormationEmilia-82");
				break;
			}
			case 39100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-83");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 39500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000107, FormationGeria001, "FormationGeria001-84");
				break;
			}
			case 39700: {
				orderActorToFactory(10000015, EnemyErmione, "EnemyErmione-85");
				break;
			}
			case 39900: {
				orderActorToFactory(10000057, EnemyDrastea, "EnemyDrastea-86");
				break;
			}
			case 40000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			case 40100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 41500: {
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-87");
				orderActorToFactory(10000108, FormationGeria001, "FormationGeria001-88");
				break;
			}
			case 41900: {
				orderActorToFactory(10000058, EnemyDrastea, "EnemyDrastea-89");
				orderActorToFactory(10000081, FormationEmilia, "FormationEmilia-90");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 43500: {
				orderActorToFactory(10000109, FormationGeria001, "FormationGeria001-91");
				break;
			}
			case 43900: {
				orderActorToFactory(10000059, EnemyDrastea, "EnemyDrastea-92");
				break;
			}
			case 44100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 44500: {
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-93");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 44700: {
				orderActorToFactory(10000016, EnemyErmione, "EnemyErmione-94");
				break;
			}
			case 44900: {
				orderActorToFactory(10000082, FormationEmilia, "FormationEmilia-95");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 45300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 45500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000110, FormationGeria001, "FormationGeria001-96");
				break;
			}
			case 45900: {
				orderActorToFactory(10000060, EnemyDrastea, "EnemyDrastea-97");
				break;
			}
			case 46100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 47500: {
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-98");
				orderActorToFactory(10000111, FormationGeria001, "FormationGeria001-99");
				break;
			}
			case 47900: {
				orderActorToFactory(10000061, EnemyDrastea, "EnemyDrastea-100");
				orderActorToFactory(10000083, FormationEmilia, "FormationEmilia-101");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 49500: {
				orderActorToFactory(10000112, FormationGeria001, "FormationGeria001-102");
				break;
			}
			case 49900: {
				orderActorToFactory(10000062, EnemyDrastea, "EnemyDrastea-103");
				break;
			}
			case 50100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 50500: {
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 50900: {
				orderActorToFactory(10000084, FormationEmilia, "FormationEmilia-105");
				break;
			}
			case 51100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 51500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000113, FormationGeria001, "FormationGeria001-106");
				break;
			}
			case 51900: {
				orderActorToFactory(10000063, EnemyDrastea, "EnemyDrastea-107");
				break;
			}
			case 52100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 53500: {
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-108");
				orderActorToFactory(10000114, FormationGeria001, "FormationGeria001-109");
				break;
			}
			case 53900: {
				orderActorToFactory(10000064, EnemyDrastea, "EnemyDrastea-110");
				orderActorToFactory(10000085, FormationEmilia, "FormationEmilia-111");
				break;
			}
			case 54100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pEtis);
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 55500: {
				orderActorToFactory(10000115, FormationGeria001, "FormationGeria001-112");
				break;
			}
			case 55900: {
				orderActorToFactory(10000065, EnemyDrastea, "EnemyDrastea-113");
				break;
			}
			case 56100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 56500: {
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-114");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 56900: {
				orderActorToFactory(10000086, FormationEmilia, "FormationEmilia-115");
				break;
			}
			case 57100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 57500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(pFormationEmilia);
				orderActorToFactory(10000116, FormationGeria001, "FormationGeria001-116");
				break;
			}
			case 57900: {
				orderActorToFactory(10000066, EnemyDrastea, "EnemyDrastea-117");
				break;
			}
			case 58100: {
				FormationGeria001* pFGria = (FormationGeria001*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pFGria);
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 167-1 ? _cnt_event+1 : _cnt_event);
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
