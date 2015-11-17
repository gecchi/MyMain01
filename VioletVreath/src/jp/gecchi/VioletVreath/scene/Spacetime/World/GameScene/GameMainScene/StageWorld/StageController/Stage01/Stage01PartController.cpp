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
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000,10100,10200,10300,10400,10500,10600,10700,10800,10900,11000,11100,11200,11300,11400,11500,11600,11700,11800,11900,12000,12100,12200,12300,12400,12500,12600,12700,12800,12900,13000,13100,13200,13300,13400,13500,13600,13700,13800,13900,14000,14100,14200,14300,14400,14500,14600,14700,14800,14900,15000,15100,15200,15300,15400,15500,15600,15700,15800,15900,16000,16100,16200,16300,16400,16500,16600,16700,16800,16900,17000,17100,17200,17300,17400,17500,17600,17700,17800,17900,18000,18100,18200,18300,18400,18500,18600,18700,18800,18900,19000,19100,19200,19300,19400,19500,19600,19700,19800,19900,20000,20100,20200,20300,20400,20500,20600,20700,20800,20900,21000,21100,21200,21300,21400,21500,21600,21700,21800,21900,22000,22100,22200,22300,22400,22500,22600,22700,22800,22900,23000,23100,23200,23300,23400,23500,23600,23700,23800,23900,24000,24100,24200,24300,24400,24500,24600,24700,24800,24900,25000,25100,25200,25300,25400,25500,25600,25700,25800,25900,26000,26100,26200,26300,26400,26500,26600,26700,26800,26900,27000,27100,27200,27300,27400,27500,27600,27700,27800,27900,28000,28100,28200,28300,28400,28500,28600,28700,28800,28900,29000,29100,29200,29300,29400,29500,29600,29700,29800,29900,30000,30100,30200,30300,30400,30500,30600,30700,30800,30900,31000,31100,31200,31300,31400,31500,31600,31700,31800,31900,32000,32100,32200,32300,32400,32500,32600,32700,32800,32900,33000,33100,33200,33300,33400,33500,33600,33700,33800,33900,34000,34100,34200,34300,34400,34500,34600,34700,34800,34900,35000,35100,35200,35300,35400,35500,35600,35700,35800,35900,36000,36100,36200,36300,36400,36500,36600,36700,36800,36900,37000,37100,37200,37300,37400,37500,37600,37700,37800,37900,38000,38100,38200,38300,38400,38500,38600,38700,38800,38900,39000,39100,39200,39300,39400,39500,39600,39700,39800,39900,40000,40100,40200,40300,40400,40500,40600,40700,40800,40900,41000,41100,41200,41300,41400,41500,41600,41700,41800,41900,42000,42100,42200,42300,42400,42500,42600,42700,42800,42900,43000,43100,43200,43300,43400,43500,43600,43700,43800,43900,44000,44100,44200,44300,44400,44500,44600,44700,44800,44900,45000,45100,45200,45300,45400,45500,45600,45700,45800,45900,46000,46100,46200,46300,46400,46500,46600,46700,46800,46900,47000,47100,47200,47300,47400,47500,47600,47700,47800,47900,48000,48100,48200,48300,48400,48500,48600,48700,48800,48900,49000,49100,49200,49300,49400,49500,49600,49700,49800,49900,50000,50100,50200,50300,50400,50500,50600,50700,50800,50900,51000,51100,51200,51300,51400,51500,51600,51700,51800,51900,52000,52100,52200,52300,52400,52500,52600,52700,52800,52900,53000,53100,53200,53300,53400,53500,53600,53700,53800,53900,54000,54100,54200,54300,54400,54500,54600,54700,54800,54900,55000,55100,55200,55300,55400,55500,55600,55700,55800,55900,56000,56100,56200,56300,56400,56500,56600,56700,56800,56900,57000,57100,57200,57300,57400,57500,57600,57700,57800,57900,58000,58100,58200,58300,58400,58500,58600,58700,58800,58900,59000,59100,59200,59300,59400,59500,59600,59700,59800,59900,60000};
	_paFrame_NextEvent = new frame[601];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 601;
	orderActorToFactory(10000000, EnemyEtis, "EnemyEtis-1");
	orderActorToFactory(10000001, EnemyEtis, "EnemyEtis-2");
	orderActorToFactory(10000002, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000003, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(10000004, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(10000005, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(10000600, EnemyDrastea, "EnemyDrastea-7");
	orderActorToFactory(10000907, FormationEmilia, "FormationEmilia-8");
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
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000000);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000006, EnemyEtis, "EnemyEtis-9");
				orderActorToFactory(10000601, EnemyDrastea, "EnemyDrastea-10");
				break;
			}
			case 200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000001);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000007, EnemyEtis, "EnemyEtis-11");
				break;
			}
			case 300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000002);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000008, EnemyEtis, "EnemyEtis-12");
				orderActorToFactory(10000602, EnemyDrastea, "EnemyDrastea-13");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000003);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000009, EnemyEtis, "EnemyEtis-14");
				break;
			}
			case 500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000004);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000010, EnemyEtis, "EnemyEtis-15");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000600);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000603, EnemyDrastea, "EnemyDrastea-16");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000907);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-17");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-18");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000601);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000604, EnemyDrastea, "EnemyDrastea-19");
				break;
			}
			case 800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-20");
				break;
			}
			case 900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-21");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000602);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000605, EnemyDrastea, "EnemyDrastea-22");
				orderActorToFactory(10000908, FormationEmilia, "FormationEmilia-23");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-24");
				break;
			}
			case 1100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-25");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000603);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000606, EnemyDrastea, "EnemyDrastea-26");
				break;
			}
			case 1200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-27");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-28");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000604);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000607, EnemyDrastea, "EnemyDrastea-29");
				break;
			}
			case 1400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-30");
				break;
			}
			case 1500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-31");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000605);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000608, EnemyDrastea, "EnemyDrastea-32");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000908);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-33");
				break;
			}
			case 1700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-34");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000606);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000609, EnemyDrastea, "EnemyDrastea-35");
				break;
			}
			case 1800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-36");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-37");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000607);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000610, EnemyDrastea, "EnemyDrastea-38");
				orderActorToFactory(10000909, FormationEmilia, "FormationEmilia-39");
				break;
			}
			case 2000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-40");
				break;
			}
			case 2100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-41");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000608);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000611, EnemyDrastea, "EnemyDrastea-42");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-43");
				break;
			}
			case 2300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-44");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000609);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000612, EnemyDrastea, "EnemyDrastea-45");
				break;
			}
			case 2400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-46");
				orderActorToFactory(10000898, FormationDelheid001, "FormationDelheid001-47");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-48");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000610);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000613, EnemyDrastea, "EnemyDrastea-49");
				orderActorToFactory(10000899, FormationDelheid001, "FormationDelheid001-50");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000909);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 2600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-51");
				orderActorToFactory(10000900, FormationDelheid001, "FormationDelheid001-52");
				break;
			}
			case 2700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-53");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000611);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000614, EnemyDrastea, "EnemyDrastea-54");
				orderActorToFactory(10000901, FormationDelheid001, "FormationDelheid001-55");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-56");
				orderActorToFactory(10000902, FormationDelheid001, "FormationDelheid001-57");
				break;
			}
			case 2900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-58");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000612);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000615, EnemyDrastea, "EnemyDrastea-59");
				orderActorToFactory(10000903, FormationDelheid001, "FormationDelheid001-60");
				orderActorToFactory(10000910, FormationEmilia, "FormationEmilia-61");
				break;
			}
			case 3000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-62");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000898);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(0), D_ANG(-40), D_ANG(0));
				orderActorToFactory(10000904, FormationDelheid001, "FormationDelheid001-63");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-64");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000613);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000616, EnemyDrastea, "EnemyDrastea-65");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000899);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(0), D_ANG(-30), D_ANG(0));
				orderActorToFactory(10000905, FormationDelheid001, "FormationDelheid001-66");
				break;
			}
			case 3200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-67");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000900);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(0), D_ANG(-20), D_ANG(0));
				orderActorToFactory(10000906, FormationDelheid001, "FormationDelheid001-68");
				break;
			}
			case 3300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-69");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000614);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000617, EnemyDrastea, "EnemyDrastea-70");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000901);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(0), D_ANG(-10), D_ANG(0));
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-71");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000902);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(   0), PX_C(500), D_ANG(0), D_ANG(  0), D_ANG(0));
				break;
			}
			case 3500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-72");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000615);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000618, EnemyDrastea, "EnemyDrastea-73");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000903);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(0), D_ANG( 10), D_ANG(0));
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000910);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 3600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-74");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000904);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(0), D_ANG( 20), D_ANG(0));
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-75");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000616);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000619, EnemyDrastea, "EnemyDrastea-76");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000905);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(0), D_ANG( 30), D_ANG(0));
				break;
			}
			case 3800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-77");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000906);
				bringDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(0), D_ANG( 40), D_ANG(0));
				break;
			}
			case 3900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-78");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000617);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000620, EnemyDrastea, "EnemyDrastea-79");
				orderActorToFactory(10000911, FormationEmilia, "FormationEmilia-80");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-81");
				break;
			}
			case 4100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-82");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000618);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000621, EnemyDrastea, "EnemyDrastea-83");
				break;
			}
			case 4200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-84");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-85");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000619);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000622, EnemyDrastea, "EnemyDrastea-86");
				break;
			}
			case 4400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-87");
				break;
			}
			case 4500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-88");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000620);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000623, EnemyDrastea, "EnemyDrastea-89");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000911);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-90");
				break;
			}
			case 4700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-91");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000621);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000624, EnemyDrastea, "EnemyDrastea-92");
				break;
			}
			case 4800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-93");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-94");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000622);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000625, EnemyDrastea, "EnemyDrastea-95");
				orderActorToFactory(10000912, FormationEmilia, "FormationEmilia-96");
				break;
			}
			case 5000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 5100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-98");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000623);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000626, EnemyDrastea, "EnemyDrastea-99");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-100");
				break;
			}
			case 5300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-101");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000624);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000627, EnemyDrastea, "EnemyDrastea-102");
				break;
			}
			case 5400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-104");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000625);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000628, EnemyDrastea, "EnemyDrastea-105");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000912);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 5600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 5700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-107");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000626);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000629, EnemyDrastea, "EnemyDrastea-108");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 5900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-110");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000627);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000630, EnemyDrastea, "EnemyDrastea-111");
				orderActorToFactory(10000913, FormationEmilia, "FormationEmilia-112");
				break;
			}
			case 6000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-113");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-114");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000628);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000631, EnemyDrastea, "EnemyDrastea-115");
				break;
			}
			case 6200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-116");
				break;
			}
			case 6300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-117");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000629);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000632, EnemyDrastea, "EnemyDrastea-118");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-119");
				break;
			}
			case 6500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-120");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000630);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000633, EnemyDrastea, "EnemyDrastea-121");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000913);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 6600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-122");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-123");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000631);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000634, EnemyDrastea, "EnemyDrastea-124");
				break;
			}
			case 6800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-125");
				break;
			}
			case 6900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-126");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000632);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000635, EnemyDrastea, "EnemyDrastea-127");
				orderActorToFactory(10000914, FormationEmilia, "FormationEmilia-128");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-129");
				break;
			}
			case 7100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-130");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000633);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000636, EnemyDrastea, "EnemyDrastea-131");
				break;
			}
			case 7200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-132");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-133");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000634);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000637, EnemyDrastea, "EnemyDrastea-134");
				break;
			}
			case 7400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-135");
				break;
			}
			case 7500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-136");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000635);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000638, EnemyDrastea, "EnemyDrastea-137");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000914);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-138");
				break;
			}
			case 7700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-139");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000636);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000639, EnemyDrastea, "EnemyDrastea-140");
				break;
			}
			case 7800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-141");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-142");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000637);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000640, EnemyDrastea, "EnemyDrastea-143");
				orderActorToFactory(10000915, FormationEmilia, "FormationEmilia-144");
				break;
			}
			case 8000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-145");
				break;
			}
			case 8100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-146");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000638);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000641, EnemyDrastea, "EnemyDrastea-147");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-148");
				break;
			}
			case 8300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-149");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000639);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000642, EnemyDrastea, "EnemyDrastea-150");
				break;
			}
			case 8400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-151");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-152");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000640);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000643, EnemyDrastea, "EnemyDrastea-153");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000915);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 8600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-154");
				break;
			}
			case 8700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-155");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000641);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000644, EnemyDrastea, "EnemyDrastea-156");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-157");
				break;
			}
			case 8900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-158");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000642);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000645, EnemyDrastea, "EnemyDrastea-159");
				orderActorToFactory(10000916, FormationEmilia, "FormationEmilia-160");
				break;
			}
			case 9000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-161");
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-162");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000643);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000646, EnemyDrastea, "EnemyDrastea-163");
				break;
			}
			case 9200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 9300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-165");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000644);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000647, EnemyDrastea, "EnemyDrastea-166");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-167");
				break;
			}
			case 9500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-168");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000645);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000648, EnemyDrastea, "EnemyDrastea-169");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000916);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 9600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-170");
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-171");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000646);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000649, EnemyDrastea, "EnemyDrastea-172");
				break;
			}
			case 9800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-173");
				break;
			}
			case 9900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-174");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000647);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000650, EnemyDrastea, "EnemyDrastea-175");
				orderActorToFactory(10000917, FormationEmilia, "FormationEmilia-176");
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-177");
				break;
			}
			case 10100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-178");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000648);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000651, EnemyDrastea, "EnemyDrastea-179");
				break;
			}
			case 10200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-180");
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-181");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000649);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000652, EnemyDrastea, "EnemyDrastea-182");
				break;
			}
			case 10400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-183");
				break;
			}
			case 10500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-184");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000650);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000653, EnemyDrastea, "EnemyDrastea-185");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000917);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-186");
				break;
			}
			case 10700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-187");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000651);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000654, EnemyDrastea, "EnemyDrastea-188");
				break;
			}
			case 10800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-189");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-190");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000652);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000655, EnemyDrastea, "EnemyDrastea-191");
				orderActorToFactory(10000918, FormationEmilia, "FormationEmilia-192");
				break;
			}
			case 11000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-193");
				break;
			}
			case 11100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-194");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000653);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000656, EnemyDrastea, "EnemyDrastea-195");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-196");
				break;
			}
			case 11300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-197");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000654);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000657, EnemyDrastea, "EnemyDrastea-198");
				break;
			}
			case 11400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-199");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-200");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000655);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000658, EnemyDrastea, "EnemyDrastea-201");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000918);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 11600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-202");
				break;
			}
			case 11700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-203");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000656);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000659, EnemyDrastea, "EnemyDrastea-204");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-205");
				break;
			}
			case 11900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-206");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000657);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000660, EnemyDrastea, "EnemyDrastea-207");
				orderActorToFactory(10000919, FormationEmilia, "FormationEmilia-208");
				break;
			}
			case 12000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-209");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-210");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000658);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000661, EnemyDrastea, "EnemyDrastea-211");
				break;
			}
			case 12200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 12300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-213");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000659);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000662, EnemyDrastea, "EnemyDrastea-214");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-215");
				break;
			}
			case 12500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-216");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000660);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000663, EnemyDrastea, "EnemyDrastea-217");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000919);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 12600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-219");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000661);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000664, EnemyDrastea, "EnemyDrastea-220");
				break;
			}
			case 12800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-221");
				break;
			}
			case 12900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-222");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000662);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000665, EnemyDrastea, "EnemyDrastea-223");
				orderActorToFactory(10000920, FormationEmilia, "FormationEmilia-224");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-225");
				break;
			}
			case 13100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-226");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000663);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000666, EnemyDrastea, "EnemyDrastea-227");
				break;
			}
			case 13200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-228");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-229");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000664);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000667, EnemyDrastea, "EnemyDrastea-230");
				break;
			}
			case 13400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-231");
				break;
			}
			case 13500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-232");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000665);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000668, EnemyDrastea, "EnemyDrastea-233");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000920);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-234");
				break;
			}
			case 13700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-235");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000666);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000669, EnemyDrastea, "EnemyDrastea-236");
				break;
			}
			case 13800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-237");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-238");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000667);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000670, EnemyDrastea, "EnemyDrastea-239");
				orderActorToFactory(10000921, FormationEmilia, "FormationEmilia-240");
				break;
			}
			case 14000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-241");
				break;
			}
			case 14100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-242");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000668);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000671, EnemyDrastea, "EnemyDrastea-243");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-244");
				break;
			}
			case 14300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-245");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000669);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000672, EnemyDrastea, "EnemyDrastea-246");
				break;
			}
			case 14400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-247");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-248");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000670);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000673, EnemyDrastea, "EnemyDrastea-249");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000921);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 14600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-250");
				break;
			}
			case 14700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-251");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000671);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000674, EnemyDrastea, "EnemyDrastea-252");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-253");
				break;
			}
			case 14900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-254");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000672);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000675, EnemyDrastea, "EnemyDrastea-255");
				orderActorToFactory(10000922, FormationEmilia, "FormationEmilia-256");
				break;
			}
			case 15000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-257");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-258");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000673);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000676, EnemyDrastea, "EnemyDrastea-259");
				break;
			}
			case 15200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-260");
				break;
			}
			case 15300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-261");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000674);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000677, EnemyDrastea, "EnemyDrastea-262");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 15500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-264");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000675);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000678, EnemyDrastea, "EnemyDrastea-265");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000922);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 15600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-266");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-267");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000676);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000679, EnemyDrastea, "EnemyDrastea-268");
				break;
			}
			case 15800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 15900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-270");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000677);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000680, EnemyDrastea, "EnemyDrastea-271");
				orderActorToFactory(10000923, FormationEmilia, "FormationEmilia-272");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-273");
				break;
			}
			case 16100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-274");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000678);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000681, EnemyDrastea, "EnemyDrastea-275");
				break;
			}
			case 16200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-276");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-277");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000679);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000682, EnemyDrastea, "EnemyDrastea-278");
				break;
			}
			case 16400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-279");
				break;
			}
			case 16500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-280");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000680);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000683, EnemyDrastea, "EnemyDrastea-281");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000923);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-282");
				break;
			}
			case 16700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-283");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000681);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000684, EnemyDrastea, "EnemyDrastea-284");
				break;
			}
			case 16800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-285");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-286");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000682);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000685, EnemyDrastea, "EnemyDrastea-287");
				orderActorToFactory(10000924, FormationEmilia, "FormationEmilia-288");
				break;
			}
			case 17000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-289");
				break;
			}
			case 17100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-290");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000683);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000686, EnemyDrastea, "EnemyDrastea-291");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-292");
				break;
			}
			case 17300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-293");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000684);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000687, EnemyDrastea, "EnemyDrastea-294");
				break;
			}
			case 17400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-295");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-296");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000685);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000688, EnemyDrastea, "EnemyDrastea-297");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000924);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 17600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-298");
				break;
			}
			case 17700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-299");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000686);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000689, EnemyDrastea, "EnemyDrastea-300");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-301");
				break;
			}
			case 17900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-302");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000687);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000690, EnemyDrastea, "EnemyDrastea-303");
				orderActorToFactory(10000925, FormationEmilia, "FormationEmilia-304");
				break;
			}
			case 18000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-305");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-306");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000688);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000691, EnemyDrastea, "EnemyDrastea-307");
				break;
			}
			case 18200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 18300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-309");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000689);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000692, EnemyDrastea, "EnemyDrastea-310");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 18500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-312");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000690);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000693, EnemyDrastea, "EnemyDrastea-313");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000925);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 18600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-314");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-315");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000691);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000694, EnemyDrastea, "EnemyDrastea-316");
				break;
			}
			case 18800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 18900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-318");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000692);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000695, EnemyDrastea, "EnemyDrastea-319");
				orderActorToFactory(10000926, FormationEmilia, "FormationEmilia-320");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-321");
				break;
			}
			case 19100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-322");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000693);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000696, EnemyDrastea, "EnemyDrastea-323");
				break;
			}
			case 19200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-324");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-325");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000694);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000697, EnemyDrastea, "EnemyDrastea-326");
				break;
			}
			case 19400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-327");
				break;
			}
			case 19500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-328");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000695);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000698, EnemyDrastea, "EnemyDrastea-329");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000926);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-330");
				break;
			}
			case 19700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-331");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000696);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000699, EnemyDrastea, "EnemyDrastea-332");
				break;
			}
			case 19800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-333");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-334");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000697);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000700, EnemyDrastea, "EnemyDrastea-335");
				orderActorToFactory(10000927, FormationEmilia, "FormationEmilia-336");
				break;
			}
			case 20000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-337");
				break;
			}
			case 20100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-338");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000698);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000701, EnemyDrastea, "EnemyDrastea-339");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-340");
				break;
			}
			case 20300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-341");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000699);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000702, EnemyDrastea, "EnemyDrastea-342");
				break;
			}
			case 20400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-343");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-344");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000700);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000703, EnemyDrastea, "EnemyDrastea-345");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000927);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 20600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-346");
				break;
			}
			case 20700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-347");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000701);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000704, EnemyDrastea, "EnemyDrastea-348");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-349");
				break;
			}
			case 20900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-350");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000702);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000705, EnemyDrastea, "EnemyDrastea-351");
				orderActorToFactory(10000928, FormationEmilia, "FormationEmilia-352");
				break;
			}
			case 21000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-353");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-354");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000703);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000706, EnemyDrastea, "EnemyDrastea-355");
				break;
			}
			case 21200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 21300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-357");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000704);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000707, EnemyDrastea, "EnemyDrastea-358");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 21500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-360");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000705);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000708, EnemyDrastea, "EnemyDrastea-361");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000928);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 21600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-363");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000706);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000709, EnemyDrastea, "EnemyDrastea-364");
				break;
			}
			case 21800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-365");
				break;
			}
			case 21900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-366");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000707);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000710, EnemyDrastea, "EnemyDrastea-367");
				orderActorToFactory(10000929, FormationEmilia, "FormationEmilia-368");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-369");
				break;
			}
			case 22100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-370");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000708);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000711, EnemyDrastea, "EnemyDrastea-371");
				break;
			}
			case 22200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-372");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-373");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000709);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000712, EnemyDrastea, "EnemyDrastea-374");
				break;
			}
			case 22400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-375");
				break;
			}
			case 22500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-376");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000710);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000713, EnemyDrastea, "EnemyDrastea-377");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000929);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-378");
				break;
			}
			case 22700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-379");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000711);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000714, EnemyDrastea, "EnemyDrastea-380");
				break;
			}
			case 22800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-381");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-382");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000712);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000715, EnemyDrastea, "EnemyDrastea-383");
				orderActorToFactory(10000930, FormationEmilia, "FormationEmilia-384");
				break;
			}
			case 23000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-385");
				break;
			}
			case 23100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-386");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000713);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000716, EnemyDrastea, "EnemyDrastea-387");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-388");
				break;
			}
			case 23300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-389");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000714);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000717, EnemyDrastea, "EnemyDrastea-390");
				break;
			}
			case 23400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-391");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-392");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000715);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000718, EnemyDrastea, "EnemyDrastea-393");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000930);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 23600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-394");
				break;
			}
			case 23700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-395");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000716);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000719, EnemyDrastea, "EnemyDrastea-396");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-397");
				break;
			}
			case 23900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-398");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000717);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000720, EnemyDrastea, "EnemyDrastea-399");
				orderActorToFactory(10000931, FormationEmilia, "FormationEmilia-400");
				break;
			}
			case 24000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-402");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000718);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000721, EnemyDrastea, "EnemyDrastea-403");
				break;
			}
			case 24200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-404");
				break;
			}
			case 24300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-405");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000719);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000722, EnemyDrastea, "EnemyDrastea-406");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 24500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-408");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000720);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000723, EnemyDrastea, "EnemyDrastea-409");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000931);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 24600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-411");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000721);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000724, EnemyDrastea, "EnemyDrastea-412");
				break;
			}
			case 24800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-413");
				break;
			}
			case 24900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-414");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000722);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000725, EnemyDrastea, "EnemyDrastea-415");
				orderActorToFactory(10000932, FormationEmilia, "FormationEmilia-416");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-417");
				break;
			}
			case 25100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-418");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000723);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000726, EnemyDrastea, "EnemyDrastea-419");
				break;
			}
			case 25200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-420");
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-421");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000724);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000727, EnemyDrastea, "EnemyDrastea-422");
				break;
			}
			case 25400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-423");
				break;
			}
			case 25500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-424");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000725);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000728, EnemyDrastea, "EnemyDrastea-425");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000932);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-426");
				break;
			}
			case 25700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-427");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000726);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000729, EnemyDrastea, "EnemyDrastea-428");
				break;
			}
			case 25800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-429");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-430");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000727);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000730, EnemyDrastea, "EnemyDrastea-431");
				orderActorToFactory(10000933, FormationEmilia, "FormationEmilia-432");
				break;
			}
			case 26000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-433");
				break;
			}
			case 26100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-434");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000728);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000731, EnemyDrastea, "EnemyDrastea-435");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-436");
				break;
			}
			case 26300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-437");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000729);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000732, EnemyDrastea, "EnemyDrastea-438");
				break;
			}
			case 26400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-439");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-440");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000730);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000733, EnemyDrastea, "EnemyDrastea-441");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000933);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 26600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-442");
				break;
			}
			case 26700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-443");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000731);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000734, EnemyDrastea, "EnemyDrastea-444");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-445");
				break;
			}
			case 26900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-446");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000732);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000735, EnemyDrastea, "EnemyDrastea-447");
				orderActorToFactory(10000934, FormationEmilia, "FormationEmilia-448");
				break;
			}
			case 27000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-449");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-450");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000733);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000736, EnemyDrastea, "EnemyDrastea-451");
				break;
			}
			case 27200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 27300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-453");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000734);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000737, EnemyDrastea, "EnemyDrastea-454");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 27500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-456");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000735);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000738, EnemyDrastea, "EnemyDrastea-457");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000934);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 27600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-458");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-459");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000736);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000739, EnemyDrastea, "EnemyDrastea-460");
				break;
			}
			case 27800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 27900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-462");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000737);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000740, EnemyDrastea, "EnemyDrastea-463");
				orderActorToFactory(10000935, FormationEmilia, "FormationEmilia-464");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-465");
				break;
			}
			case 28100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-466");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000738);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000741, EnemyDrastea, "EnemyDrastea-467");
				break;
			}
			case 28200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-468");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-469");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000739);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000742, EnemyDrastea, "EnemyDrastea-470");
				break;
			}
			case 28400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-471");
				break;
			}
			case 28500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-472");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000740);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000743, EnemyDrastea, "EnemyDrastea-473");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000935);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-474");
				break;
			}
			case 28700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-475");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000741);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000744, EnemyDrastea, "EnemyDrastea-476");
				break;
			}
			case 28800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-477");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-478");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000742);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000745, EnemyDrastea, "EnemyDrastea-479");
				orderActorToFactory(10000936, FormationEmilia, "FormationEmilia-480");
				break;
			}
			case 29000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-481");
				break;
			}
			case 29100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-482");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000743);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000746, EnemyDrastea, "EnemyDrastea-483");
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-484");
				break;
			}
			case 29300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-485");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000744);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000747, EnemyDrastea, "EnemyDrastea-486");
				break;
			}
			case 29400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-487");
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-488");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000745);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000748, EnemyDrastea, "EnemyDrastea-489");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000936);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 29600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-490");
				break;
			}
			case 29700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-491");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000746);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000749, EnemyDrastea, "EnemyDrastea-492");
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-493");
				break;
			}
			case 29900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-494");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000747);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000750, EnemyDrastea, "EnemyDrastea-495");
				orderActorToFactory(10000937, FormationEmilia, "FormationEmilia-496");
				break;
			}
			case 30000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-497");
				break;
			}
			case 30100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-498");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000748);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000751, EnemyDrastea, "EnemyDrastea-499");
				break;
			}
			case 30200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 30300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-501");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000749);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000752, EnemyDrastea, "EnemyDrastea-502");
				break;
			}
			case 30400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 30500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-504");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000750);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000753, EnemyDrastea, "EnemyDrastea-505");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000937);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 30600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 30700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-507");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000751);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000754, EnemyDrastea, "EnemyDrastea-508");
				break;
			}
			case 30800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-509");
				break;
			}
			case 30900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-510");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000752);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000755, EnemyDrastea, "EnemyDrastea-511");
				orderActorToFactory(10000938, FormationEmilia, "FormationEmilia-512");
				break;
			}
			case 31000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-513");
				break;
			}
			case 31100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-514");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000753);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000756, EnemyDrastea, "EnemyDrastea-515");
				break;
			}
			case 31200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-516");
				break;
			}
			case 31300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-517");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000754);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000757, EnemyDrastea, "EnemyDrastea-518");
				break;
			}
			case 31400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-519");
				break;
			}
			case 31500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-520");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000755);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000758, EnemyDrastea, "EnemyDrastea-521");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000938);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 31600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-522");
				break;
			}
			case 31700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-523");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000756);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000759, EnemyDrastea, "EnemyDrastea-524");
				break;
			}
			case 31800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-525");
				break;
			}
			case 31900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-526");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000757);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000760, EnemyDrastea, "EnemyDrastea-527");
				orderActorToFactory(10000939, FormationEmilia, "FormationEmilia-528");
				break;
			}
			case 32000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-529");
				break;
			}
			case 32100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-530");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000758);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000761, EnemyDrastea, "EnemyDrastea-531");
				break;
			}
			case 32200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-532");
				break;
			}
			case 32300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-533");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000759);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000762, EnemyDrastea, "EnemyDrastea-534");
				break;
			}
			case 32400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-535");
				break;
			}
			case 32500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-536");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000760);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000763, EnemyDrastea, "EnemyDrastea-537");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000939);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 32600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-538");
				break;
			}
			case 32700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-539");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000761);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000764, EnemyDrastea, "EnemyDrastea-540");
				break;
			}
			case 32800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-541");
				break;
			}
			case 32900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-542");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000762);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000765, EnemyDrastea, "EnemyDrastea-543");
				orderActorToFactory(10000940, FormationEmilia, "FormationEmilia-544");
				break;
			}
			case 33000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 33100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-546");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000763);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000766, EnemyDrastea, "EnemyDrastea-547");
				break;
			}
			case 33200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-548");
				break;
			}
			case 33300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-549");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000764);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000767, EnemyDrastea, "EnemyDrastea-550");
				break;
			}
			case 33400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 33500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-552");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000765);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000768, EnemyDrastea, "EnemyDrastea-553");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000940);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 33600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 33700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-555");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000766);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000769, EnemyDrastea, "EnemyDrastea-556");
				break;
			}
			case 33800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-557");
				break;
			}
			case 33900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-558");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000767);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000770, EnemyDrastea, "EnemyDrastea-559");
				orderActorToFactory(10000941, FormationEmilia, "FormationEmilia-560");
				break;
			}
			case 34000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-561");
				break;
			}
			case 34100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-562");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000768);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000771, EnemyDrastea, "EnemyDrastea-563");
				break;
			}
			case 34200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-564");
				break;
			}
			case 34300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-565");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000769);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000772, EnemyDrastea, "EnemyDrastea-566");
				break;
			}
			case 34400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-567");
				break;
			}
			case 34500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-568");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000770);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000773, EnemyDrastea, "EnemyDrastea-569");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000941);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 34600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-570");
				break;
			}
			case 34700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-571");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000771);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000774, EnemyDrastea, "EnemyDrastea-572");
				break;
			}
			case 34800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-573");
				break;
			}
			case 34900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-574");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000772);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000775, EnemyDrastea, "EnemyDrastea-575");
				orderActorToFactory(10000942, FormationEmilia, "FormationEmilia-576");
				break;
			}
			case 35000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-577");
				break;
			}
			case 35100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-578");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000773);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000776, EnemyDrastea, "EnemyDrastea-579");
				break;
			}
			case 35200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-580");
				break;
			}
			case 35300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-581");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000774);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000777, EnemyDrastea, "EnemyDrastea-582");
				break;
			}
			case 35400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-583");
				break;
			}
			case 35500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-584");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000775);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000778, EnemyDrastea, "EnemyDrastea-585");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000942);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 35600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-586");
				break;
			}
			case 35700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-587");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000776);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000779, EnemyDrastea, "EnemyDrastea-588");
				break;
			}
			case 35800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-589");
				break;
			}
			case 35900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-590");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000777);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000780, EnemyDrastea, "EnemyDrastea-591");
				orderActorToFactory(10000943, FormationEmilia, "FormationEmilia-592");
				break;
			}
			case 36000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 36100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-594");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000778);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000781, EnemyDrastea, "EnemyDrastea-595");
				break;
			}
			case 36200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-596");
				break;
			}
			case 36300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-597");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000779);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000782, EnemyDrastea, "EnemyDrastea-598");
				break;
			}
			case 36400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 36500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-600");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000780);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000783, EnemyDrastea, "EnemyDrastea-601");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000943);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 36600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 36700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-603");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000781);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000784, EnemyDrastea, "EnemyDrastea-604");
				break;
			}
			case 36800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-605");
				break;
			}
			case 36900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-606");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000782);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000785, EnemyDrastea, "EnemyDrastea-607");
				orderActorToFactory(10000944, FormationEmilia, "FormationEmilia-608");
				break;
			}
			case 37000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-609");
				break;
			}
			case 37100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-610");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000783);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000786, EnemyDrastea, "EnemyDrastea-611");
				break;
			}
			case 37200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-612");
				break;
			}
			case 37300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-613");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000784);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000787, EnemyDrastea, "EnemyDrastea-614");
				break;
			}
			case 37400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-615");
				break;
			}
			case 37500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-616");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000785);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000788, EnemyDrastea, "EnemyDrastea-617");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000944);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 37600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-618");
				break;
			}
			case 37700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-619");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000786);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000789, EnemyDrastea, "EnemyDrastea-620");
				break;
			}
			case 37800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-621");
				break;
			}
			case 37900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-622");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000787);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000790, EnemyDrastea, "EnemyDrastea-623");
				orderActorToFactory(10000945, FormationEmilia, "FormationEmilia-624");
				break;
			}
			case 38000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-625");
				break;
			}
			case 38100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-626");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000788);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000791, EnemyDrastea, "EnemyDrastea-627");
				break;
			}
			case 38200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-628");
				break;
			}
			case 38300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-629");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000789);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000792, EnemyDrastea, "EnemyDrastea-630");
				break;
			}
			case 38400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-631");
				break;
			}
			case 38500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-632");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000790);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000793, EnemyDrastea, "EnemyDrastea-633");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000945);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 38600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-634");
				break;
			}
			case 38700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-635");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000791);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000794, EnemyDrastea, "EnemyDrastea-636");
				break;
			}
			case 38800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-637");
				break;
			}
			case 38900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-638");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000792);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000795, EnemyDrastea, "EnemyDrastea-639");
				orderActorToFactory(10000946, FormationEmilia, "FormationEmilia-640");
				break;
			}
			case 39000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 39100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-642");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000793);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000796, EnemyDrastea, "EnemyDrastea-643");
				break;
			}
			case 39200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-644");
				break;
			}
			case 39300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-645");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000794);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000797, EnemyDrastea, "EnemyDrastea-646");
				break;
			}
			case 39400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 39500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-648");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000795);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000798, EnemyDrastea, "EnemyDrastea-649");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000946);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 39600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 39700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-651");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000796);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000799, EnemyDrastea, "EnemyDrastea-652");
				break;
			}
			case 39800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-653");
				break;
			}
			case 39900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-654");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000797);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000800, EnemyDrastea, "EnemyDrastea-655");
				orderActorToFactory(10000947, FormationEmilia, "FormationEmilia-656");
				break;
			}
			case 40000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-657");
				break;
			}
			case 40100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-658");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000798);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000801, EnemyDrastea, "EnemyDrastea-659");
				break;
			}
			case 40200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-660");
				break;
			}
			case 40300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-661");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000799);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000802, EnemyDrastea, "EnemyDrastea-662");
				break;
			}
			case 40400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-663");
				break;
			}
			case 40500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-664");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000800);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000803, EnemyDrastea, "EnemyDrastea-665");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000947);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 40600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-666");
				break;
			}
			case 40700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-667");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000801);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000804, EnemyDrastea, "EnemyDrastea-668");
				break;
			}
			case 40800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-669");
				break;
			}
			case 40900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-670");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000802);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000805, EnemyDrastea, "EnemyDrastea-671");
				orderActorToFactory(10000948, FormationEmilia, "FormationEmilia-672");
				break;
			}
			case 41000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-673");
				break;
			}
			case 41100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-674");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000803);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000806, EnemyDrastea, "EnemyDrastea-675");
				break;
			}
			case 41200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-676");
				break;
			}
			case 41300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-677");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000804);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000807, EnemyDrastea, "EnemyDrastea-678");
				break;
			}
			case 41400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-679");
				break;
			}
			case 41500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-680");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000805);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000808, EnemyDrastea, "EnemyDrastea-681");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000948);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 41600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-682");
				break;
			}
			case 41700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-683");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000806);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000809, EnemyDrastea, "EnemyDrastea-684");
				break;
			}
			case 41800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-685");
				break;
			}
			case 41900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-686");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000807);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000810, EnemyDrastea, "EnemyDrastea-687");
				orderActorToFactory(10000949, FormationEmilia, "FormationEmilia-688");
				break;
			}
			case 42000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 42100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-690");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000808);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000811, EnemyDrastea, "EnemyDrastea-691");
				break;
			}
			case 42200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-692");
				break;
			}
			case 42300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-693");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000809);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000812, EnemyDrastea, "EnemyDrastea-694");
				break;
			}
			case 42400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 42500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-696");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000810);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000813, EnemyDrastea, "EnemyDrastea-697");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000949);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 42600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 42700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-699");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000811);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000814, EnemyDrastea, "EnemyDrastea-700");
				break;
			}
			case 42800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-701");
				break;
			}
			case 42900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-702");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000812);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000815, EnemyDrastea, "EnemyDrastea-703");
				orderActorToFactory(10000950, FormationEmilia, "FormationEmilia-704");
				break;
			}
			case 43000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-705");
				break;
			}
			case 43100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-706");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000813);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000816, EnemyDrastea, "EnemyDrastea-707");
				break;
			}
			case 43200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-708");
				break;
			}
			case 43300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-709");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000814);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000817, EnemyDrastea, "EnemyDrastea-710");
				break;
			}
			case 43400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-711");
				break;
			}
			case 43500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-712");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000815);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000818, EnemyDrastea, "EnemyDrastea-713");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000950);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 43600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-714");
				break;
			}
			case 43700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-715");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000816);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000819, EnemyDrastea, "EnemyDrastea-716");
				break;
			}
			case 43800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-717");
				break;
			}
			case 43900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-718");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000817);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000820, EnemyDrastea, "EnemyDrastea-719");
				orderActorToFactory(10000951, FormationEmilia, "FormationEmilia-720");
				break;
			}
			case 44000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-721");
				break;
			}
			case 44100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-722");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000818);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000821, EnemyDrastea, "EnemyDrastea-723");
				break;
			}
			case 44200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-724");
				break;
			}
			case 44300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-725");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000819);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000822, EnemyDrastea, "EnemyDrastea-726");
				break;
			}
			case 44400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-727");
				break;
			}
			case 44500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-728");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000820);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000823, EnemyDrastea, "EnemyDrastea-729");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000951);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 44600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-730");
				break;
			}
			case 44700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-731");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000821);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000824, EnemyDrastea, "EnemyDrastea-732");
				break;
			}
			case 44800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-733");
				break;
			}
			case 44900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-734");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000822);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000825, EnemyDrastea, "EnemyDrastea-735");
				orderActorToFactory(10000952, FormationEmilia, "FormationEmilia-736");
				break;
			}
			case 45000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 45100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-738");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000823);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000826, EnemyDrastea, "EnemyDrastea-739");
				break;
			}
			case 45200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-740");
				break;
			}
			case 45300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-741");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000824);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000827, EnemyDrastea, "EnemyDrastea-742");
				break;
			}
			case 45400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 45500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-744");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000825);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000828, EnemyDrastea, "EnemyDrastea-745");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000952);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 45600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 45700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-747");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000826);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000829, EnemyDrastea, "EnemyDrastea-748");
				break;
			}
			case 45800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-749");
				break;
			}
			case 45900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-750");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000827);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000830, EnemyDrastea, "EnemyDrastea-751");
				orderActorToFactory(10000953, FormationEmilia, "FormationEmilia-752");
				break;
			}
			case 46000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-753");
				break;
			}
			case 46100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-754");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000828);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000831, EnemyDrastea, "EnemyDrastea-755");
				break;
			}
			case 46200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-756");
				break;
			}
			case 46300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-757");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000829);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000832, EnemyDrastea, "EnemyDrastea-758");
				break;
			}
			case 46400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-759");
				break;
			}
			case 46500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-760");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000830);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000833, EnemyDrastea, "EnemyDrastea-761");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000953);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 46600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-762");
				break;
			}
			case 46700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-763");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000831);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000834, EnemyDrastea, "EnemyDrastea-764");
				break;
			}
			case 46800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-765");
				break;
			}
			case 46900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-766");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000832);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000835, EnemyDrastea, "EnemyDrastea-767");
				orderActorToFactory(10000954, FormationEmilia, "FormationEmilia-768");
				break;
			}
			case 47000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-769");
				break;
			}
			case 47100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-770");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000833);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000836, EnemyDrastea, "EnemyDrastea-771");
				break;
			}
			case 47200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-772");
				break;
			}
			case 47300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-773");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000834);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000837, EnemyDrastea, "EnemyDrastea-774");
				break;
			}
			case 47400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-775");
				break;
			}
			case 47500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-776");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000835);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000838, EnemyDrastea, "EnemyDrastea-777");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000954);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 47600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-778");
				break;
			}
			case 47700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-779");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000836);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000839, EnemyDrastea, "EnemyDrastea-780");
				break;
			}
			case 47800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-781");
				break;
			}
			case 47900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-782");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000837);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000840, EnemyDrastea, "EnemyDrastea-783");
				orderActorToFactory(10000955, FormationEmilia, "FormationEmilia-784");
				break;
			}
			case 48000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 48100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-786");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000838);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000841, EnemyDrastea, "EnemyDrastea-787");
				break;
			}
			case 48200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-788");
				break;
			}
			case 48300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-789");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000839);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000842, EnemyDrastea, "EnemyDrastea-790");
				break;
			}
			case 48400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 48500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-792");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000840);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000843, EnemyDrastea, "EnemyDrastea-793");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000955);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 48600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 48700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-795");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000841);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000844, EnemyDrastea, "EnemyDrastea-796");
				break;
			}
			case 48800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-797");
				break;
			}
			case 48900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-798");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000842);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000845, EnemyDrastea, "EnemyDrastea-799");
				orderActorToFactory(10000956, FormationEmilia, "FormationEmilia-800");
				break;
			}
			case 49000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-801");
				break;
			}
			case 49100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-802");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000843);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000846, EnemyDrastea, "EnemyDrastea-803");
				break;
			}
			case 49200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-804");
				break;
			}
			case 49300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-805");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000844);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000847, EnemyDrastea, "EnemyDrastea-806");
				break;
			}
			case 49400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-807");
				break;
			}
			case 49500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-808");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000845);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000848, EnemyDrastea, "EnemyDrastea-809");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000956);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 49600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-810");
				break;
			}
			case 49700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-811");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000846);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000849, EnemyDrastea, "EnemyDrastea-812");
				break;
			}
			case 49800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-813");
				break;
			}
			case 49900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-814");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000847);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000850, EnemyDrastea, "EnemyDrastea-815");
				orderActorToFactory(10000957, FormationEmilia, "FormationEmilia-816");
				break;
			}
			case 50000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-817");
				break;
			}
			case 50100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-818");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000848);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000851, EnemyDrastea, "EnemyDrastea-819");
				break;
			}
			case 50200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-820");
				break;
			}
			case 50300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-821");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000849);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000852, EnemyDrastea, "EnemyDrastea-822");
				break;
			}
			case 50400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-823");
				break;
			}
			case 50500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-824");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000850);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000853, EnemyDrastea, "EnemyDrastea-825");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000957);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 50600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-826");
				break;
			}
			case 50700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-827");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000851);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000854, EnemyDrastea, "EnemyDrastea-828");
				break;
			}
			case 50800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-829");
				break;
			}
			case 50900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-830");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000852);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000855, EnemyDrastea, "EnemyDrastea-831");
				orderActorToFactory(10000958, FormationEmilia, "FormationEmilia-832");
				break;
			}
			case 51000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 51100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-834");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000853);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000856, EnemyDrastea, "EnemyDrastea-835");
				break;
			}
			case 51200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-836");
				break;
			}
			case 51300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-837");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000854);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000857, EnemyDrastea, "EnemyDrastea-838");
				break;
			}
			case 51400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 51500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-840");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000855);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000858, EnemyDrastea, "EnemyDrastea-841");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000958);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 51600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 51700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-843");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000856);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000859, EnemyDrastea, "EnemyDrastea-844");
				break;
			}
			case 51800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 51900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-846");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000857);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000860, EnemyDrastea, "EnemyDrastea-847");
				orderActorToFactory(10000959, FormationEmilia, "FormationEmilia-848");
				break;
			}
			case 52000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-849");
				break;
			}
			case 52100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-850");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000858);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000861, EnemyDrastea, "EnemyDrastea-851");
				break;
			}
			case 52200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-852");
				break;
			}
			case 52300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-853");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000859);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000862, EnemyDrastea, "EnemyDrastea-854");
				break;
			}
			case 52400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-855");
				break;
			}
			case 52500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-856");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000860);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000863, EnemyDrastea, "EnemyDrastea-857");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000959);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 52600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-858");
				break;
			}
			case 52700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-859");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000861);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000864, EnemyDrastea, "EnemyDrastea-860");
				break;
			}
			case 52800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-861");
				break;
			}
			case 52900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-862");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000862);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000865, EnemyDrastea, "EnemyDrastea-863");
				orderActorToFactory(10000960, FormationEmilia, "FormationEmilia-864");
				break;
			}
			case 53000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-865");
				break;
			}
			case 53100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-866");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000863);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000866, EnemyDrastea, "EnemyDrastea-867");
				break;
			}
			case 53200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-868");
				break;
			}
			case 53300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-869");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000864);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000867, EnemyDrastea, "EnemyDrastea-870");
				break;
			}
			case 53400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-871");
				break;
			}
			case 53500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-872");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000865);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000868, EnemyDrastea, "EnemyDrastea-873");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000960);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 53600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-874");
				break;
			}
			case 53700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-875");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000866);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000869, EnemyDrastea, "EnemyDrastea-876");
				break;
			}
			case 53800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-877");
				break;
			}
			case 53900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-878");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000867);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000870, EnemyDrastea, "EnemyDrastea-879");
				orderActorToFactory(10000961, FormationEmilia, "FormationEmilia-880");
				break;
			}
			case 54000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 54100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-882");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000868);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000871, EnemyDrastea, "EnemyDrastea-883");
				break;
			}
			case 54200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-884");
				break;
			}
			case 54300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-885");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000869);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000872, EnemyDrastea, "EnemyDrastea-886");
				break;
			}
			case 54400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 54500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-888");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000870);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000873, EnemyDrastea, "EnemyDrastea-889");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000961);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 54600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 54700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-891");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000871);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000874, EnemyDrastea, "EnemyDrastea-892");
				break;
			}
			case 54800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-893");
				break;
			}
			case 54900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-894");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000872);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000875, EnemyDrastea, "EnemyDrastea-895");
				orderActorToFactory(10000962, FormationEmilia, "FormationEmilia-896");
				break;
			}
			case 55000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-897");
				break;
			}
			case 55100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-898");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000873);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000876, EnemyDrastea, "EnemyDrastea-899");
				break;
			}
			case 55200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-900");
				break;
			}
			case 55300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-901");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000874);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000877, EnemyDrastea, "EnemyDrastea-902");
				break;
			}
			case 55400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-903");
				break;
			}
			case 55500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-904");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000875);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000878, EnemyDrastea, "EnemyDrastea-905");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000962);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 55600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-906");
				break;
			}
			case 55700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-907");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000876);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000879, EnemyDrastea, "EnemyDrastea-908");
				break;
			}
			case 55800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-909");
				break;
			}
			case 55900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-910");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000877);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000880, EnemyDrastea, "EnemyDrastea-911");
				orderActorToFactory(10000963, FormationEmilia, "FormationEmilia-912");
				break;
			}
			case 56000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-913");
				break;
			}
			case 56100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-914");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000878);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000881, EnemyDrastea, "EnemyDrastea-915");
				break;
			}
			case 56200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-916");
				break;
			}
			case 56300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-917");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000879);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000882, EnemyDrastea, "EnemyDrastea-918");
				break;
			}
			case 56400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-919");
				break;
			}
			case 56500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-920");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000880);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000883, EnemyDrastea, "EnemyDrastea-921");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000963);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 56600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-922");
				break;
			}
			case 56700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-923");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000881);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000884, EnemyDrastea, "EnemyDrastea-924");
				break;
			}
			case 56800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-925");
				break;
			}
			case 56900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-926");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000882);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000885, EnemyDrastea, "EnemyDrastea-927");
				orderActorToFactory(10000964, FormationEmilia, "FormationEmilia-928");
				break;
			}
			case 57000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 57100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-930");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000883);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000886, EnemyDrastea, "EnemyDrastea-931");
				break;
			}
			case 57200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-932");
				break;
			}
			case 57300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-933");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000884);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000887, EnemyDrastea, "EnemyDrastea-934");
				break;
			}
			case 57400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 57500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-936");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000885);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000888, EnemyDrastea, "EnemyDrastea-937");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000964);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 57600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 57700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-939");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000886);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000889, EnemyDrastea, "EnemyDrastea-940");
				break;
			}
			case 57800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-941");
				break;
			}
			case 57900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-942");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000887);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000890, EnemyDrastea, "EnemyDrastea-943");
				orderActorToFactory(10000965, FormationEmilia, "FormationEmilia-944");
				break;
			}
			case 58000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-945");
				break;
			}
			case 58100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-946");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000888);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000891, EnemyDrastea, "EnemyDrastea-947");
				break;
			}
			case 58200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-948");
				break;
			}
			case 58300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-949");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000889);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000892, EnemyDrastea, "EnemyDrastea-950");
				break;
			}
			case 58400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-951");
				break;
			}
			case 58500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-952");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000890);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000893, EnemyDrastea, "EnemyDrastea-953");
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000965);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 58600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-954");
				break;
			}
			case 58700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-955");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000891);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000894, EnemyDrastea, "EnemyDrastea-956");
				break;
			}
			case 58800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-957");
				break;
			}
			case 58900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-958");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000892);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000895, EnemyDrastea, "EnemyDrastea-959");
				orderActorToFactory(10000966, FormationEmilia, "FormationEmilia-960");
				break;
			}
			case 59000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-961");
				break;
			}
			case 59100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-962");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000893);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000896, EnemyDrastea, "EnemyDrastea-963");
				break;
			}
			case 59200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-964");
				break;
			}
			case 59300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-965");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000894);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(10000897, EnemyDrastea, "EnemyDrastea-966");
				break;
			}
			case 59400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				bringDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-967");
				break;
			}
			case 59500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000895);
				bringDirector()->addSubGroup(p);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)obtainActorFromFactory(10000966);
				bringDirector()->addSubGroup(pFormationEmilia);
				break;
			}
			case 59600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000896);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 59800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			case 59900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				bringDirector()->addSubGroup(pEtis);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(10000897);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 60000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				bringDirector()->addSubGroup(pEtis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 601-1 ? _cnt_event+1 : _cnt_event);
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
