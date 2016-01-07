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
	frame f[] = {1,100,300,500,501,1000,1700,1900,1901,2300,2500,2501,2900,3100,3500,3700,3900,3901,4300,4500,4501,5500,5700,5900,5901,6100,6300,6500,6501,7700,7900,7901,8300,8500,8501,8900,9100,9500,9700,9900,9901,10000,10300,10500,10501,11500,11700,11900,11901,12100,12300,12500,12501,13700,13900,13901,14300,14500,14501,14900,15100,15500,15700,15900,15901,16300,16500,16501,17500,17700,17900,17901,18100,18300,18500,18501,19700,19900,19901,20300,20500,20501,20900,21100,21500,21700,21900,21901,22300,22500,22501,23500,23700,23900,23901,24100,24300,24500,24501,25700,25900,25901,26300,26500,26501,26900,27100,27500,27700,27900,27901,28300,28500,28501,29100,29500,29700,29900,29901,30000,30100,30300,30500,30501,31700,31900,31901,32300,32500,32501,32900,33100,33500,33700,33900,33901,34300,34500,34501,35500,35700,35900,35901,36100,36300,36500,36501,37700,37900,37901,38300,38500,38501,38900,39100,39500,39700,39900,39901,40000,40300,40500,40501,41500,41700,41900,41901,42100,42300,42500,42501,43700,43900,43901,44300,44500,44501,44900,45100,45500,45700,45900,45901,46300,46500,46501,47500,47700,47900,47901,48100,48300,48500,48501,49900,49901,50500,50501,50900,51100,51500,51900,51901,52500,52501,53500,53900,53901,54100,54500,54501,55900,55901,56500,56501,56900,57100,57500,57900,57901,58500,58501};
	_paFrame_NextEvent = new frame[222];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 222;
	orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-1");
	orderActorToFactory(10000029, FormationHalia, "FormationHalia-2");
	orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000079, EnemyDrastea, "EnemyDrastea-4");
	orderActorToFactory(10000109, FormationEmilia, "FormationEmilia-5");
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
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-6");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
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
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 1000: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				break;
			}
			case 1700: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-7");
				break;
			}
			case 1900: {
				orderActorToFactory(10000080, EnemyDrastea, "EnemyDrastea-8");
				break;
			}
			case 1901: {
				orderActorToFactory(10000030, FormationHalia, "FormationHalia-9");
				break;
			}
			case 2300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 2500: {
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-10");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 2501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 2900: {
				orderActorToFactory(10000110, FormationEmilia, "FormationEmilia-11");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 3500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 3700: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-12");
				break;
			}
			case 3900: {
				orderActorToFactory(10000081, EnemyDrastea, "EnemyDrastea-13");
				break;
			}
			case 3901: {
				orderActorToFactory(10000031, FormationHalia, "FormationHalia-14");
				break;
			}
			case 4300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 4501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 5500: {
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-15");
				break;
			}
			case 5700: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-16");
				break;
			}
			case 5900: {
				orderActorToFactory(10000082, EnemyDrastea, "EnemyDrastea-17");
				orderActorToFactory(10000111, FormationEmilia, "FormationEmilia-18");
				break;
			}
			case 5901: {
				orderActorToFactory(10000032, FormationHalia, "FormationHalia-19");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 6300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 6501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 7700: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-20");
				break;
			}
			case 7900: {
				orderActorToFactory(10000083, EnemyDrastea, "EnemyDrastea-21");
				break;
			}
			case 7901: {
				orderActorToFactory(10000033, FormationHalia, "FormationHalia-22");
				break;
			}
			case 8300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 8500: {
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-23");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 8501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 8900: {
				orderActorToFactory(10000112, FormationEmilia, "FormationEmilia-24");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-25");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 9500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 9700: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-26");
				break;
			}
			case 9900: {
				orderActorToFactory(10000084, EnemyDrastea, "EnemyDrastea-27");
				break;
			}
			case 9901: {
				orderActorToFactory(10000034, FormationHalia, "FormationHalia-28");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
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
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 10501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 11500: {
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-29");
				break;
			}
			case 11700: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-30");
				break;
			}
			case 11900: {
				orderActorToFactory(10000085, EnemyDrastea, "EnemyDrastea-31");
				orderActorToFactory(10000113, FormationEmilia, "FormationEmilia-32");
				break;
			}
			case 11901: {
				orderActorToFactory(10000035, FormationHalia, "FormationHalia-33");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 12300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 12500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 12501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 13700: {
				orderActorToFactory(10000011, EnemyErmione, "EnemyErmione-34");
				break;
			}
			case 13900: {
				orderActorToFactory(10000086, EnemyDrastea, "EnemyDrastea-35");
				break;
			}
			case 13901: {
				orderActorToFactory(10000036, FormationHalia, "FormationHalia-36");
				break;
			}
			case 14300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 14500: {
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-37");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 14501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 14900: {
				orderActorToFactory(10000114, FormationEmilia, "FormationEmilia-38");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 15500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 15700: {
				orderActorToFactory(10000012, EnemyErmione, "EnemyErmione-39");
				break;
			}
			case 15900: {
				orderActorToFactory(10000087, EnemyDrastea, "EnemyDrastea-40");
				break;
			}
			case 15901: {
				orderActorToFactory(10000037, FormationHalia, "FormationHalia-41");
				break;
			}
			case 16300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 16500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 16501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 17500: {
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 17700: {
				orderActorToFactory(10000013, EnemyErmione, "EnemyErmione-43");
				break;
			}
			case 17900: {
				orderActorToFactory(10000088, EnemyDrastea, "EnemyDrastea-44");
				orderActorToFactory(10000115, FormationEmilia, "FormationEmilia-45");
				break;
			}
			case 17901: {
				orderActorToFactory(10000038, FormationHalia, "FormationHalia-46");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 18300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 18500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 18501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 19700: {
				orderActorToFactory(10000014, EnemyErmione, "EnemyErmione-47");
				break;
			}
			case 19900: {
				orderActorToFactory(10000089, EnemyDrastea, "EnemyDrastea-48");
				break;
			}
			case 19901: {
				orderActorToFactory(10000039, FormationHalia, "FormationHalia-49");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 20500: {
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-50");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 20501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 20900: {
				orderActorToFactory(10000116, FormationEmilia, "FormationEmilia-51");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 21500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 21700: {
				orderActorToFactory(10000015, EnemyErmione, "EnemyErmione-52");
				break;
			}
			case 21900: {
				orderActorToFactory(10000090, EnemyDrastea, "EnemyDrastea-53");
				break;
			}
			case 21901: {
				orderActorToFactory(10000040, FormationHalia, "FormationHalia-54");
				break;
			}
			case 22300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 22500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 22501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 23500: {
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-55");
				break;
			}
			case 23700: {
				orderActorToFactory(10000016, EnemyErmione, "EnemyErmione-56");
				break;
			}
			case 23900: {
				orderActorToFactory(10000091, EnemyDrastea, "EnemyDrastea-57");
				orderActorToFactory(10000117, FormationEmilia, "FormationEmilia-58");
				break;
			}
			case 23901: {
				orderActorToFactory(10000041, FormationHalia, "FormationHalia-59");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 24300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 24500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000117);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 24501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 25700: {
				orderActorToFactory(10000017, EnemyErmione, "EnemyErmione-60");
				break;
			}
			case 25900: {
				orderActorToFactory(10000092, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 25901: {
				orderActorToFactory(10000042, FormationHalia, "FormationHalia-62");
				break;
			}
			case 26300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 26500: {
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-63");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 26501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 26900: {
				orderActorToFactory(10000118, FormationEmilia, "FormationEmilia-64");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 27500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000118);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 27700: {
				orderActorToFactory(10000018, EnemyErmione, "EnemyErmione-65");
				break;
			}
			case 27900: {
				orderActorToFactory(10000093, EnemyDrastea, "EnemyDrastea-66");
				break;
			}
			case 27901: {
				orderActorToFactory(10000043, FormationHalia, "FormationHalia-67");
				break;
			}
			case 28300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 28500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 28501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-68");
				break;
			}
			case 29500: {
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-69");
				break;
			}
			case 29700: {
				orderActorToFactory(10000019, EnemyErmione, "EnemyErmione-70");
				break;
			}
			case 29900: {
				orderActorToFactory(10000094, EnemyDrastea, "EnemyDrastea-71");
				orderActorToFactory(10000119, FormationEmilia, "FormationEmilia-72");
				break;
			}
			case 29901: {
				orderActorToFactory(10000044, FormationHalia, "FormationHalia-73");
				break;
			}
			case 30000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 30300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 30500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000119);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 30501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 31700: {
				orderActorToFactory(10000020, EnemyErmione, "EnemyErmione-74");
				break;
			}
			case 31900: {
				orderActorToFactory(10000095, EnemyDrastea, "EnemyDrastea-75");
				break;
			}
			case 31901: {
				orderActorToFactory(10000045, FormationHalia, "FormationHalia-76");
				break;
			}
			case 32300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 32500: {
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-77");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 32501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 32900: {
				orderActorToFactory(10000120, FormationEmilia, "FormationEmilia-78");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 33500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000120);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 33700: {
				orderActorToFactory(10000021, EnemyErmione, "EnemyErmione-79");
				break;
			}
			case 33900: {
				orderActorToFactory(10000096, EnemyDrastea, "EnemyDrastea-80");
				break;
			}
			case 33901: {
				orderActorToFactory(10000046, FormationHalia, "FormationHalia-81");
				break;
			}
			case 34300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 34500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 34501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 35500: {
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 35700: {
				orderActorToFactory(10000022, EnemyErmione, "EnemyErmione-83");
				break;
			}
			case 35900: {
				orderActorToFactory(10000097, EnemyDrastea, "EnemyDrastea-84");
				orderActorToFactory(10000121, FormationEmilia, "FormationEmilia-85");
				break;
			}
			case 35901: {
				orderActorToFactory(10000047, FormationHalia, "FormationHalia-86");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 36300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 36500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000121);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 36501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 37700: {
				orderActorToFactory(10000023, EnemyErmione, "EnemyErmione-87");
				break;
			}
			case 37900: {
				orderActorToFactory(10000098, EnemyDrastea, "EnemyDrastea-88");
				break;
			}
			case 37901: {
				orderActorToFactory(10000048, FormationHalia, "FormationHalia-89");
				break;
			}
			case 38300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 38500: {
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-90");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 38501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 38900: {
				orderActorToFactory(10000122, FormationEmilia, "FormationEmilia-91");
				break;
			}
			case 39100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-92");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 39500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000122);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 39700: {
				orderActorToFactory(10000024, EnemyErmione, "EnemyErmione-93");
				break;
			}
			case 39900: {
				orderActorToFactory(10000099, EnemyDrastea, "EnemyDrastea-94");
				break;
			}
			case 39901: {
				orderActorToFactory(10000049, FormationHalia, "FormationHalia-95");
				break;
			}
			case 40000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 40500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 40501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 41500: {
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-96");
				break;
			}
			case 41700: {
				orderActorToFactory(10000025, EnemyErmione, "EnemyErmione-97");
				break;
			}
			case 41900: {
				orderActorToFactory(10000100, EnemyDrastea, "EnemyDrastea-98");
				orderActorToFactory(10000123, FormationEmilia, "FormationEmilia-99");
				break;
			}
			case 41901: {
				orderActorToFactory(10000050, FormationHalia, "FormationHalia-100");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 42300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 42500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000123);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 42501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 43700: {
				orderActorToFactory(10000026, EnemyErmione, "EnemyErmione-101");
				break;
			}
			case 43900: {
				orderActorToFactory(10000101, EnemyDrastea, "EnemyDrastea-102");
				break;
			}
			case 43901: {
				orderActorToFactory(10000051, FormationHalia, "FormationHalia-103");
				break;
			}
			case 44300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 44500: {
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 44501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 44900: {
				orderActorToFactory(10000124, FormationEmilia, "FormationEmilia-105");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 45500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000124);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 45700: {
				orderActorToFactory(10000027, EnemyErmione, "EnemyErmione-106");
				break;
			}
			case 45900: {
				orderActorToFactory(10000102, EnemyDrastea, "EnemyDrastea-107");
				break;
			}
			case 45901: {
				orderActorToFactory(10000052, FormationHalia, "FormationHalia-108");
				break;
			}
			case 46300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 46500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 46501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 47500: {
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 47700: {
				orderActorToFactory(10000028, EnemyErmione, "EnemyErmione-110");
				break;
			}
			case 47900: {
				orderActorToFactory(10000103, EnemyDrastea, "EnemyDrastea-111");
				orderActorToFactory(10000125, FormationEmilia, "FormationEmilia-112");
				break;
			}
			case 47901: {
				orderActorToFactory(10000053, FormationHalia, "FormationHalia-113");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 48300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 48500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000125);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 48501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 49900: {
				orderActorToFactory(10000104, EnemyDrastea, "EnemyDrastea-114");
				break;
			}
			case 49901: {
				orderActorToFactory(10000054, FormationHalia, "FormationHalia-115");
				break;
			}
			case 50500: {
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-116");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 50501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 50900: {
				orderActorToFactory(10000126, FormationEmilia, "FormationEmilia-117");
				break;
			}
			case 51100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 51500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000126);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 51900: {
				orderActorToFactory(10000105, EnemyDrastea, "EnemyDrastea-118");
				break;
			}
			case 51901: {
				orderActorToFactory(10000055, FormationHalia, "FormationHalia-119");
				break;
			}
			case 52500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 52501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 53500: {
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-120");
				break;
			}
			case 53900: {
				orderActorToFactory(10000106, EnemyDrastea, "EnemyDrastea-121");
				orderActorToFactory(10000127, FormationEmilia, "FormationEmilia-122");
				break;
			}
			case 53901: {
				orderActorToFactory(10000056, FormationHalia, "FormationHalia-123");
				break;
			}
			case 54100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 54500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000127);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 54501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 55900: {
				orderActorToFactory(10000107, EnemyDrastea, "EnemyDrastea-124");
				break;
			}
			case 55901: {
				orderActorToFactory(10000057, FormationHalia, "FormationHalia-125");
				break;
			}
			case 56500: {
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-126");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 56501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(pF);
				break;
			}
			case 56900: {
				orderActorToFactory(10000128, FormationEmilia, "FormationEmilia-127");
				break;
			}
			case 57100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 57500: {
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000128);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 57900: {
				orderActorToFactory(10000108, EnemyDrastea, "EnemyDrastea-128");
				break;
			}
			case 57901: {
				orderActorToFactory(10000058, FormationHalia, "FormationHalia-129");
				break;
			}
			case 58500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 58501: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(pF);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 222-1 ? _cnt_event+1 : _cnt_event);
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
