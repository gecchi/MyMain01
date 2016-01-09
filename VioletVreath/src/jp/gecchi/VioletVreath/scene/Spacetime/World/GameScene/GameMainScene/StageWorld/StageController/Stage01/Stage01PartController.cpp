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
	frame f[] = {1,100,300,500,501,1000,1900,2500,2900,3100,3500,3900,4500,5500,5900,6100,6500,7900,8500,8900,9100,9500,9900,10000,10500,11500,11900,12100,12500,13900,14500,14900,15100,15500,15900,16500,17500,17900,18100,18500,19700,19900,19901,20300,20500,20501,20900,21100,21500,21900,22500,23500,23900,24100,24500,25900,26500,26900,27100,27500,27900,28500,29100,29500,29900,30000,30100,30500,31900,32500,32900,33100,33500,33900,34500,35500,35900,36100,36500,37900,38500,38900,39100,39500,39700,39900,39901,40000,40300,40500,40501,41500,41900,42100,42500,43900,44500,44900,45100,45500,45900,46500,47500,47900,48100,48500,49900,50500,50900,51100,51500,51900,52500,53500,53900,54100,54500,55900,56500,56900,57100,57500,57900,58500};
	_paFrame_NextEvent = new frame[124];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 124;
	orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-10000004");
	orderActorToFactory(10000007, FormationHalia, "FormationHalia-10000007");
	orderActorToFactory(10000010, EnemyEtis, "EnemyEtis-10000010");
	orderActorToFactory(10000030, EnemyDrastea, "EnemyDrastea-10000030");
	orderActorToFactory(10000060, FormationEmilia, "FormationEmilia-10000060");
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
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-10000000");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 501: {
				bringDirector()->addSubGroup(obtainActorFromFactory(10000007));
				break;
			}
			case 1000: {
				addSubLast(obtainSceneFromFactory(10000000));
				break;
			}
			case 1900: {
				orderActorToFactory(10000031, EnemyDrastea, "EnemyDrastea-10000031");
				break;
			}
			case 2500: {
				orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-10000011");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 2900: {
				orderActorToFactory(10000061, FormationEmilia, "FormationEmilia-10000061");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 3500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 3900: {
				orderActorToFactory(10000032, EnemyDrastea, "EnemyDrastea-10000032");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 5500: {
				orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-10000012");
				break;
			}
			case 5900: {
				orderActorToFactory(10000033, EnemyDrastea, "EnemyDrastea-10000033");
				orderActorToFactory(10000062, FormationEmilia, "FormationEmilia-10000062");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 7900: {
				orderActorToFactory(10000034, EnemyDrastea, "EnemyDrastea-10000034");
				break;
			}
			case 8500: {
				orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-10000013");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 8900: {
				orderActorToFactory(10000063, FormationEmilia, "FormationEmilia-10000063");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-10000001");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 9500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 9900: {
				orderActorToFactory(10000035, EnemyDrastea, "EnemyDrastea-10000035");
				break;
			}
			case 10000: {
				addSubLast(obtainSceneFromFactory(10000001));
				break;
			}
			case 10500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 11500: {
				orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-10000014");
				break;
			}
			case 11900: {
				orderActorToFactory(10000036, EnemyDrastea, "EnemyDrastea-10000036");
				orderActorToFactory(10000064, FormationEmilia, "FormationEmilia-10000064");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 13900: {
				orderActorToFactory(10000037, EnemyDrastea, "EnemyDrastea-10000037");
				break;
			}
			case 14500: {
				orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-10000015");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 14900: {
				orderActorToFactory(10000065, FormationEmilia, "FormationEmilia-10000065");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 15500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 15900: {
				orderActorToFactory(10000038, EnemyDrastea, "EnemyDrastea-10000038");
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 17500: {
				orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-10000016");
				break;
			}
			case 17900: {
				orderActorToFactory(10000039, EnemyDrastea, "EnemyDrastea-10000039");
				orderActorToFactory(10000066, FormationEmilia, "FormationEmilia-10000066");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 19700: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-10000005");
				break;
			}
			case 19900: {
				orderActorToFactory(10000040, EnemyDrastea, "EnemyDrastea-10000040");
				break;
			}
			case 19901: {
				orderActorToFactory(10000008, FormationHalia, "FormationHalia-10000008");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20500: {
				orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-10000017");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 20501: {
				bringDirector()->addSubGroup(obtainActorFromFactory(10000008));
				break;
			}
			case 20900: {
				orderActorToFactory(10000067, FormationEmilia, "FormationEmilia-10000067");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 21500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 21900: {
				orderActorToFactory(10000041, EnemyDrastea, "EnemyDrastea-10000041");
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 23500: {
				orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-10000018");
				break;
			}
			case 23900: {
				orderActorToFactory(10000042, EnemyDrastea, "EnemyDrastea-10000042");
				orderActorToFactory(10000068, FormationEmilia, "FormationEmilia-10000068");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 25900: {
				orderActorToFactory(10000043, EnemyDrastea, "EnemyDrastea-10000043");
				break;
			}
			case 26500: {
				orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-10000019");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 26900: {
				orderActorToFactory(10000069, FormationEmilia, "FormationEmilia-10000069");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 27500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 27900: {
				orderActorToFactory(10000044, EnemyDrastea, "EnemyDrastea-10000044");
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-10000002");
				break;
			}
			case 29500: {
				orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-10000020");
				break;
			}
			case 29900: {
				orderActorToFactory(10000045, EnemyDrastea, "EnemyDrastea-10000045");
				orderActorToFactory(10000070, FormationEmilia, "FormationEmilia-10000070");
				break;
			}
			case 30000: {
				addSubLast(obtainSceneFromFactory(10000002));
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 31900: {
				orderActorToFactory(10000046, EnemyDrastea, "EnemyDrastea-10000046");
				break;
			}
			case 32500: {
				orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-10000021");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 32900: {
				orderActorToFactory(10000071, FormationEmilia, "FormationEmilia-10000071");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 33500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 33900: {
				orderActorToFactory(10000047, EnemyDrastea, "EnemyDrastea-10000047");
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 35500: {
				orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-10000022");
				break;
			}
			case 35900: {
				orderActorToFactory(10000048, EnemyDrastea, "EnemyDrastea-10000048");
				orderActorToFactory(10000072, FormationEmilia, "FormationEmilia-10000072");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 37900: {
				orderActorToFactory(10000049, EnemyDrastea, "EnemyDrastea-10000049");
				break;
			}
			case 38500: {
				orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-10000023");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 38900: {
				orderActorToFactory(10000073, FormationEmilia, "FormationEmilia-10000073");
				break;
			}
			case 39100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-10000003");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 39500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 39700: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-10000006");
				break;
			}
			case 39900: {
				orderActorToFactory(10000050, EnemyDrastea, "EnemyDrastea-10000050");
				break;
			}
			case 39901: {
				orderActorToFactory(10000009, FormationHalia, "FormationHalia-10000009");
				break;
			}
			case 40000: {
				addSubLast(obtainSceneFromFactory(10000003));
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 40501: {
				bringDirector()->addSubGroup(obtainActorFromFactory(10000009));
				break;
			}
			case 41500: {
				orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-10000024");
				break;
			}
			case 41900: {
				orderActorToFactory(10000051, EnemyDrastea, "EnemyDrastea-10000051");
				orderActorToFactory(10000074, FormationEmilia, "FormationEmilia-10000074");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 43900: {
				orderActorToFactory(10000052, EnemyDrastea, "EnemyDrastea-10000052");
				break;
			}
			case 44500: {
				orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-10000025");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 44900: {
				orderActorToFactory(10000075, FormationEmilia, "FormationEmilia-10000075");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 45500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 45900: {
				orderActorToFactory(10000053, EnemyDrastea, "EnemyDrastea-10000053");
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 47500: {
				orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-10000026");
				break;
			}
			case 47900: {
				orderActorToFactory(10000054, EnemyDrastea, "EnemyDrastea-10000054");
				orderActorToFactory(10000076, FormationEmilia, "FormationEmilia-10000076");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 49900: {
				orderActorToFactory(10000055, EnemyDrastea, "EnemyDrastea-10000055");
				break;
			}
			case 50500: {
				orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-10000027");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 50900: {
				orderActorToFactory(10000077, FormationEmilia, "FormationEmilia-10000077");
				break;
			}
			case 51100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 51500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 51900: {
				orderActorToFactory(10000056, EnemyDrastea, "EnemyDrastea-10000056");
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 53500: {
				orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-10000028");
				break;
			}
			case 53900: {
				orderActorToFactory(10000057, EnemyDrastea, "EnemyDrastea-10000057");
				orderActorToFactory(10000078, FormationEmilia, "FormationEmilia-10000078");
				break;
			}
			case 54100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 55900: {
				orderActorToFactory(10000058, EnemyDrastea, "EnemyDrastea-10000058");
				break;
			}
			case 56500: {
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-10000029");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 56900: {
				orderActorToFactory(10000079, FormationEmilia, "FormationEmilia-10000079");
				break;
			}
			case 57100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 57500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 57900: {
				orderActorToFactory(10000059, EnemyDrastea, "EnemyDrastea-10000059");
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 124-1 ? _cnt_event+1 : _cnt_event);
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
