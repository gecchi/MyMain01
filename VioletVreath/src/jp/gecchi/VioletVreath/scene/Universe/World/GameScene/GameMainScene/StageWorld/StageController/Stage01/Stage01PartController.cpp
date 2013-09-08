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
	frame f[] = {1,10,40,70,100,120,130,160,190,220,250,280,310,340,370,400,430,460,490,500,520,550,580,610,640,670,700,730,760,780,790,820,850,880,910,940,970,1000,1020,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2110,2140,2170,2200,2230,2260,2290,2320,2350,2380,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4100,4120,4150,4180,4200,4210,4240,4270,4300,4330,4360,4390,4400,4420,4450,4480,4500,4510,4540,4570,4600,4630,4660,4690,4700,4720,4750,4780,4800,4810,4840,4870,4900,4930,4960,4990,5000,5020,5050,5080,5100,5110,5140,5170,5200,5230,5260,5290,5300,5320,5350,5380,5400,5410,5440,5470,5500,5530,5560,5590,5600,5620,5650,5680,5700,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8410,8440,8470,8500,8530,8560,8590,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8920,8950,8980,9010,9040,9070,9100,9130,9160,9190,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10030,10060,10090,10120,10150,10180,10210,10240,10270,10300,10330,10360,10390,10420,10450,10480,10510,10540,10570,10600,10630,10660,10690,10720,10750,10780,10810,10840,10870,10900,10930,10960,10990,11020,11050,11080,11110,11140,11170,11200,11230,11260,11290,11320,11350,11380,11410,11440,11470,11500,11530,11560,11590,11620,11650,11680,11710,11740,11770,11800,11830,11860,11890,11920,11950,11980,12010,12040,12070,12100,12130,12160,12190,12220,12250,12280,12310,12340,12370,12400,12430,12460,12490,12520,12550,12580,12610,12640,12670,12700,12730,12760,12790,12820,12850,12880,12910,12940,12970,13000,13030,13060,13090,13120,13150,13180,13210,13240,13270,13300,13330,13360,13390,13420,13450,13480,13510,13540,13570,13600,13630,13660,13690,13720,13750,13780,13810,13840,13870,13900,13930,13960,13990,14020,14050,14080,14110,14140,14170,14200,14230,14260,14290,14320,14350,14380,14410,14440,14470,14500,14530,14560,14590,14620,14650,14680,14710,14740,14770,14800,14830,14860,14890,14920,14950,14980,15010,15040,15070,15100,15130,15160,15190,15220,15250,15280,15310,15340,15370,15400,15430,15460,15490,15520,15550,15580,15610,15640,15670,15700,15730,15760,15790,15820,15850,15880,15910,15940,15970,16000,16030,16060,16090,16120,16150,16180,16210,16240,16270,16300,16330,16360,16390,16420,16450,16480,16510,16540,16570,16600,16630,16660,16690,16720,16750,16780,16810,16840,16870,16900,16930,16960,16990,17020,17050,17080,17110,17140,17170,17200,17230,17260,17290,17320,17350,17380,17410,17440,17470,17500,17530,17560,17590,17620,17650,17680,17710,17740,17770,17800,17830,17860,17890,17920,17950,17980,18010,18040,18070,18100,18130,18160,18190,18220,18250,18280,18310,18340,18370,18400,18430,18460,18490,18520,18550,18580,18610,18640,18670,18700,18730,18760,18790,18820,18850,18880,18910,18940,18970,19000,19030,19060,19090,19100,19120,19150,19180,19210,19240,19270,19300,19330,19360,19390,19420,19450,19480,19510,19540,19570,19600,19630,19660,19690,19720,19750,19780,19810,19840,19870,19900,19930,19960,19990,20000,20020,20050,20080,20110,20140,20170,20200,20230,20260,20290,20320,20350,20380,20410,20440,20470,20500,20530,20560,20590,20620,20650,20680,20710,20740,20770,20800,20830,20860,20890,20920,20950,20980,21010,21040,21070,21100,21130,21160,21190,21220,21250,21280,21310,21340,21370,21400,21430,21460,21490,21520,21550,21580,21610,21640,21670,21700,21730,21760,21790,21820,21850,21880,21910,21940,21970,22000,22030,22060,22090,22120,22150,22180,22210,22240,22270,22300,22330,22360,22390,22420,22450,22480,22510,22540,22570,22600,22630,22660,22690,22720,22750,22780,22810,22840,22870,22900,22930,22960,22990,23020,23050,23080,23110,23140,23170,23200,23230,23260,23290,23320,23350,23380,23410,23440,23470,23500,23530,23560,23590,23620,23650,23680,23710,23740,23770,23800,23830,23860,23890,23920,23950,23980,24010,24040,24070,24100,24130,24160,24190,24220,24250,24280,24310,24340,24370,24400,24430,24460,24490,24520,24550,24580,24610,24640,24670,24700,24730,24760,24790,24820,24850,24880,24910,24940,24970,25000,25030,25060,25090,25120,25150,25180,25210,25240,25270,25300,25330,25360,25390,25420,25450,25480,25510,25540,25570,25600,25630,25660,25690,25720,25750,25780,25810,25840,25870,25900,25930,25960,25990,26020,26050,26080,26110,26140,26170,26200,26230,26260,26290,26320,26350,26380,26410,26440,26470,26500,26530,26560,26590,26620,26650,26680,26710,26740,26770,26800,26830,26860,26890,26920,26950,26980,27010,27040,27070,27100,27130,27160,27190,27220,27250,27280,27310,27340,27370,27400,27430,27460,27490,27520,27550,27580,27610,27640,27670,27700,27730,27760,27790,27820,27850,27880,27910,27940,27970,28000,28030,28060,28090,28120,28150,28180,28210,28240,28270,28300,28330,28360,28390,28420,28450,28480,28510,28540,28570,28600,28630,28660,28690,28720,28750,28780,28810,28840,28870,28900,28930,28960,28990,29020,29050,29080,29100,29110,29140,29170,29200,29230,29260,29290,29320,29350,29380,29410,29440,29470,29500,29530,29560,29590,29620,29650,29680,29710,29740,29770,29800,29830,29860,29890,29920,29950,29980,30000};
	_paFrame_NextEvent = new frame[1021];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1021;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, EnemyEtis, "EnemyEtis-2");
	orderActorToFactory(10000005, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(10000006, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(10000007, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(10000008, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(10000009, EnemyEtis, "EnemyEtis-7");
	orderActorToFactory(10000010, EnemyEtis, "EnemyEtis-8");
	orderActorToFactory(10000011, EnemyEtis, "EnemyEtis-9");
	orderActorToFactory(10000012, EnemyEtis, "EnemyEtis-10");
	orderActorToFactory(10000013, EnemyEtis, "EnemyEtis-11");
	orderActorToFactory(10000014, EnemyEtis, "EnemyEtis-12");
	orderActorToFactory(10000015, EnemyEtis, "EnemyEtis-13");
	orderActorToFactory(10000016, EnemyEtis, "EnemyEtis-14");
	orderActorToFactory(10000017, EnemyEtis, "EnemyEtis-15");
	orderActorToFactory(10000018, EnemyEtis, "EnemyEtis-16");
	orderActorToFactory(10000019, EnemyEtis, "EnemyEtis-17");
	orderActorToFactory(10000020, EnemyEtis, "EnemyEtis-18");
	orderActorToFactory(10000021, EnemyEtis, "EnemyEtis-19");
	orderActorToFactory(10000022, EnemyEtis, "EnemyEtis-20");
	orderActorToFactory(10000023, EnemyEtis, "EnemyEtis-21");
	orderActorToFactory(10000024, EnemyEtis, "EnemyEtis-22");
	orderActorToFactory(10000025, EnemyEtis, "EnemyEtis-23");
	orderActorToFactory(10000026, EnemyEtis, "EnemyEtis-24");
	orderActorToFactory(10000027, EnemyEtis, "EnemyEtis-25");
	orderActorToFactory(10000028, EnemyEtis, "EnemyEtis-26");
	orderActorToFactory(10000029, EnemyEtis, "EnemyEtis-27");
	orderActorToFactory(10000030, EnemyEtis, "EnemyEtis-28");
	orderActorToFactory(10001001, FormationAppho001a, "FormationAppho001a-29");
	orderActorToFactory(10001012, FormationOrtuna001b, "FormationOrtuna001b-30");
	orderActorToFactory(10001013, EnemyGlaja, "EnemyGlaja-31");
	orderActorToFactory(10001014, EnemyGlaja, "EnemyGlaja-32");
	orderActorToFactory(10001015, EnemyDuna, "EnemyDuna-33");
	orderActorToFactory(10001016, EnemyDuna, "EnemyDuna-34");
	orderActorToFactory(10001017, EnemyDuna, "EnemyDuna-35");
	orderActorToFactory(10001018, EnemyDuna, "EnemyDuna-36");
	orderActorToFactory(10001019, EnemyDuna, "EnemyDuna-37");
	orderActorToFactory(10001020, EnemyDuna, "EnemyDuna-38");
	orderActorToFactory(10001021, EnemyDuna, "EnemyDuna-39");
	orderActorToFactory(10001022, EnemyDuna, "EnemyDuna-40");
	orderActorToFactory(10001023, EnemyDuna, "EnemyDuna-41");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
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
			case 10: {
				orderActorToFactory(10000031, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 40: {
				orderActorToFactory(10000032, EnemyEtis, "EnemyEtis-43");
				orderActorToFactory(10001024, EnemyDuna, "EnemyDuna-44");
				break;
			}
			case 70: {
				orderActorToFactory(10000033, EnemyEtis, "EnemyEtis-45");
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000034, EnemyEtis, "EnemyEtis-46");
				orderActorToFactory(10001025, EnemyDuna, "EnemyDuna-47");
				break;
			}
			case 120: {
				orderActorToFactory(10001002, FormationAppho001b, "FormationAppho001b-48");
				break;
			}
			case 130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000035, EnemyEtis, "EnemyEtis-49");
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000036, EnemyEtis, "EnemyEtis-50");
				orderActorToFactory(10001026, EnemyDuna, "EnemyDuna-51");
				break;
			}
			case 190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000037, EnemyEtis, "EnemyEtis-52");
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000038, EnemyEtis, "EnemyEtis-53");
				orderActorToFactory(10001027, EnemyDuna, "EnemyDuna-54");
				break;
			}
			case 250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000039, EnemyEtis, "EnemyEtis-55");
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000040, EnemyEtis, "EnemyEtis-56");
				orderActorToFactory(10001028, EnemyDuna, "EnemyDuna-57");
				break;
			}
			case 310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000041, EnemyEtis, "EnemyEtis-58");
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000042, EnemyEtis, "EnemyEtis-59");
				orderActorToFactory(10001029, EnemyDuna, "EnemyDuna-60");
				break;
			}
			case 370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000043, EnemyEtis, "EnemyEtis-61");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000044, EnemyEtis, "EnemyEtis-62");
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10001013);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001015);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001030, EnemyDuna, "EnemyDuna-63");
				break;
			}
			case 430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000045, EnemyEtis, "EnemyEtis-64");
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000046, EnemyEtis, "EnemyEtis-65");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001016);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001031, EnemyDuna, "EnemyDuna-66");
				break;
			}
			case 490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000047, EnemyEtis, "EnemyEtis-67");
				break;
			}
			case 500: {
				FormationOrtuna001b* pF1 = (FormationOrtuna001b*)obtainActorFromFactory(10001012);
				getSceneDirector()->addSubGroup(pF1);
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10001014);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000048, EnemyEtis, "EnemyEtis-68");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001017);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001032, EnemyDuna, "EnemyDuna-69");
				break;
			}
			case 550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000049, EnemyEtis, "EnemyEtis-70");
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000050, EnemyEtis, "EnemyEtis-71");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001018);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001033, EnemyDuna, "EnemyDuna-72");
				break;
			}
			case 610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000051, EnemyEtis, "EnemyEtis-73");
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000052, EnemyEtis, "EnemyEtis-74");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001019);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001034, EnemyDuna, "EnemyDuna-75");
				break;
			}
			case 670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000053, EnemyEtis, "EnemyEtis-76");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000054, EnemyEtis, "EnemyEtis-77");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001020);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001035, EnemyDuna, "EnemyDuna-78");
				break;
			}
			case 730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000055, EnemyEtis, "EnemyEtis-79");
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000056, EnemyEtis, "EnemyEtis-80");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001021);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001036, EnemyDuna, "EnemyDuna-81");
				break;
			}
			case 780: {
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10001001);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000057, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000058, EnemyEtis, "EnemyEtis-83");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001022);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001037, EnemyDuna, "EnemyDuna-84");
				break;
			}
			case 850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000059, EnemyEtis, "EnemyEtis-85");
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000060, EnemyEtis, "EnemyEtis-86");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001023);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001038, EnemyDuna, "EnemyDuna-87");
				break;
			}
			case 910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000061, EnemyEtis, "EnemyEtis-88");
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000062, EnemyEtis, "EnemyEtis-89");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001024);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001039, EnemyDuna, "EnemyDuna-90");
				break;
			}
			case 970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000063, EnemyEtis, "EnemyEtis-91");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000064, EnemyEtis, "EnemyEtis-92");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001025);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001040, EnemyDuna, "EnemyDuna-93");
				break;
			}
			case 1020: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10001002);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000065, EnemyEtis, "EnemyEtis-94");
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000066, EnemyEtis, "EnemyEtis-95");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001026);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001041, EnemyDuna, "EnemyDuna-96");
				break;
			}
			case 1090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000067, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000068, EnemyEtis, "EnemyEtis-98");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001027);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001042, EnemyDuna, "EnemyDuna-99");
				break;
			}
			case 1150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000069, EnemyEtis, "EnemyEtis-100");
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000070, EnemyEtis, "EnemyEtis-101");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001028);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001043, EnemyDuna, "EnemyDuna-102");
				break;
			}
			case 1210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000071, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000072, EnemyEtis, "EnemyEtis-104");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001029);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001044, EnemyDuna, "EnemyDuna-105");
				break;
			}
			case 1270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000073, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000074, EnemyEtis, "EnemyEtis-107");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001030);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001045, EnemyDuna, "EnemyDuna-108");
				break;
			}
			case 1330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000075, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000076, EnemyEtis, "EnemyEtis-110");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001031);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001046, EnemyDuna, "EnemyDuna-111");
				break;
			}
			case 1390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000077, EnemyEtis, "EnemyEtis-112");
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000078, EnemyEtis, "EnemyEtis-113");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001032);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001047, EnemyDuna, "EnemyDuna-114");
				break;
			}
			case 1450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000079, EnemyEtis, "EnemyEtis-115");
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000080, EnemyEtis, "EnemyEtis-116");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001033);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001048, EnemyDuna, "EnemyDuna-117");
				break;
			}
			case 1510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000081, EnemyEtis, "EnemyEtis-118");
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000082, EnemyEtis, "EnemyEtis-119");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001034);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001049, EnemyDuna, "EnemyDuna-120");
				break;
			}
			case 1570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000083, EnemyEtis, "EnemyEtis-121");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000084, EnemyEtis, "EnemyEtis-122");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001035);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001050, EnemyDuna, "EnemyDuna-123");
				break;
			}
			case 1630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000085, EnemyEtis, "EnemyEtis-124");
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000086, EnemyEtis, "EnemyEtis-125");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001036);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001051, EnemyDuna, "EnemyDuna-126");
				break;
			}
			case 1690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000087, EnemyEtis, "EnemyEtis-127");
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000088, EnemyEtis, "EnemyEtis-128");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001037);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001052, EnemyDuna, "EnemyDuna-129");
				break;
			}
			case 1750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000089, EnemyEtis, "EnemyEtis-130");
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000090, EnemyEtis, "EnemyEtis-131");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001038);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001053, EnemyDuna, "EnemyDuna-132");
				break;
			}
			case 1810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000091, EnemyEtis, "EnemyEtis-133");
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000062);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000092, EnemyEtis, "EnemyEtis-134");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001039);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001054, EnemyDuna, "EnemyDuna-135");
				break;
			}
			case 1870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000063);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000093, EnemyEtis, "EnemyEtis-136");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000064);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000094, EnemyEtis, "EnemyEtis-137");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001040);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001055, EnemyDuna, "EnemyDuna-138");
				break;
			}
			case 1930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000065);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000095, EnemyEtis, "EnemyEtis-139");
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000066);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000096, EnemyEtis, "EnemyEtis-140");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001041);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001056, EnemyDuna, "EnemyDuna-141");
				break;
			}
			case 1990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000067);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000097, EnemyEtis, "EnemyEtis-142");
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000068);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000098, EnemyEtis, "EnemyEtis-143");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001042);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001057, EnemyDuna, "EnemyDuna-144");
				break;
			}
			case 2050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000069);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000099, EnemyEtis, "EnemyEtis-145");
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000070);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000100, EnemyEtis, "EnemyEtis-146");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001043);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10001058, EnemyDuna, "EnemyDuna-147");
				break;
			}
			case 2110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000071);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000101, EnemyEtis, "EnemyEtis-148");
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000072);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000102, EnemyEtis, "EnemyEtis-149");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001044);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000073);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000103, EnemyEtis, "EnemyEtis-150");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000074);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000104, EnemyEtis, "EnemyEtis-151");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001045);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000075);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000105, EnemyEtis, "EnemyEtis-152");
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000076);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000106, EnemyEtis, "EnemyEtis-153");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001046);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000077);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000107, EnemyEtis, "EnemyEtis-154");
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000078);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000108, EnemyEtis, "EnemyEtis-155");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001047);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000079);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000109, EnemyEtis, "EnemyEtis-156");
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000080);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000110, EnemyEtis, "EnemyEtis-157");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001048);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000081);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000111, EnemyEtis, "EnemyEtis-158");
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000082);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000112, EnemyEtis, "EnemyEtis-159");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001049);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000083);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000113, EnemyEtis, "EnemyEtis-160");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000084);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000114, EnemyEtis, "EnemyEtis-161");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001050);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000085);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000115, EnemyEtis, "EnemyEtis-162");
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000086);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000116, EnemyEtis, "EnemyEtis-163");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001051);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000087);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000117, EnemyEtis, "EnemyEtis-164");
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000088);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000118, EnemyEtis, "EnemyEtis-165");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001052);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000089);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000119, EnemyEtis, "EnemyEtis-166");
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000090);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000120, EnemyEtis, "EnemyEtis-167");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001053);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000091);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000121, EnemyEtis, "EnemyEtis-168");
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000092);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000122, EnemyEtis, "EnemyEtis-169");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001054);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000093);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000123, EnemyEtis, "EnemyEtis-170");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000094);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000124, EnemyEtis, "EnemyEtis-171");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001055);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000095);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000125, EnemyEtis, "EnemyEtis-172");
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000096);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000126, EnemyEtis, "EnemyEtis-173");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001056);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000097);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000127, EnemyEtis, "EnemyEtis-174");
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000098);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000128, EnemyEtis, "EnemyEtis-175");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001057);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000099);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000129, EnemyEtis, "EnemyEtis-176");
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000100);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000130, EnemyEtis, "EnemyEtis-177");
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10001058);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 3010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000101);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000131, EnemyEtis, "EnemyEtis-178");
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000102);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000132, EnemyEtis, "EnemyEtis-179");
				break;
			}
			case 3070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000103);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000133, EnemyEtis, "EnemyEtis-180");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000104);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000134, EnemyEtis, "EnemyEtis-181");
				break;
			}
			case 3130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000105);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000135, EnemyEtis, "EnemyEtis-182");
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000106);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000136, EnemyEtis, "EnemyEtis-183");
				break;
			}
			case 3190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000107);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000137, EnemyEtis, "EnemyEtis-184");
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000108);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000138, EnemyEtis, "EnemyEtis-185");
				break;
			}
			case 3250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000109);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000139, EnemyEtis, "EnemyEtis-186");
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000110);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000140, EnemyEtis, "EnemyEtis-187");
				break;
			}
			case 3310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000111);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000141, EnemyEtis, "EnemyEtis-188");
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000112);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000142, EnemyEtis, "EnemyEtis-189");
				break;
			}
			case 3370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000113);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000143, EnemyEtis, "EnemyEtis-190");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000114);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000144, EnemyEtis, "EnemyEtis-191");
				break;
			}
			case 3430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000115);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000145, EnemyEtis, "EnemyEtis-192");
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000116);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000146, EnemyEtis, "EnemyEtis-193");
				break;
			}
			case 3490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000117);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000147, EnemyEtis, "EnemyEtis-194");
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000118);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000148, EnemyEtis, "EnemyEtis-195");
				break;
			}
			case 3550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000119);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000149, EnemyEtis, "EnemyEtis-196");
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000120);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000150, EnemyEtis, "EnemyEtis-197");
				break;
			}
			case 3610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000121);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000151, EnemyEtis, "EnemyEtis-198");
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000122);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000152, EnemyEtis, "EnemyEtis-199");
				break;
			}
			case 3670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000123);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000153, EnemyEtis, "EnemyEtis-200");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000124);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000154, EnemyEtis, "EnemyEtis-201");
				break;
			}
			case 3730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000125);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000155, EnemyEtis, "EnemyEtis-202");
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000126);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000156, EnemyEtis, "EnemyEtis-203");
				break;
			}
			case 3790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000127);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000157, EnemyEtis, "EnemyEtis-204");
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000128);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000158, EnemyEtis, "EnemyEtis-205");
				break;
			}
			case 3850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000129);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000159, EnemyEtis, "EnemyEtis-206");
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000130);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000160, EnemyEtis, "EnemyEtis-207");
				break;
			}
			case 3910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000131);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000161, EnemyEtis, "EnemyEtis-208");
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000132);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000162, EnemyEtis, "EnemyEtis-209");
				break;
			}
			case 3970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000133);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000163, EnemyEtis, "EnemyEtis-210");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000134);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000164, EnemyEtis, "EnemyEtis-211");
				break;
			}
			case 4030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000135);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000165, EnemyEtis, "EnemyEtis-212");
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000136);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000166, EnemyEtis, "EnemyEtis-213");
				break;
			}
			case 4090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000137);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000167, EnemyEtis, "EnemyEtis-214");
				break;
			}
			case 4100: {
				orderActorToFactory(10001003, FormationDelheid001, "FormationDelheid001-215");
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000138);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000168, EnemyEtis, "EnemyEtis-216");
				break;
			}
			case 4150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000139);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000169, EnemyEtis, "EnemyEtis-217");
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000140);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000170, EnemyEtis, "EnemyEtis-218");
				break;
			}
			case 4200: {
				orderActorToFactory(10001004, FormationDelheid001, "FormationDelheid001-219");
				break;
			}
			case 4210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000141);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000171, EnemyEtis, "EnemyEtis-220");
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000142);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000172, EnemyEtis, "EnemyEtis-221");
				break;
			}
			case 4270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000143);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000173, EnemyEtis, "EnemyEtis-222");
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000144);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000174, EnemyEtis, "EnemyEtis-223");
				orderActorToFactory(10001005, FormationDelheid001, "FormationDelheid001-224");
				break;
			}
			case 4330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000145);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000175, EnemyEtis, "EnemyEtis-225");
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000146);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000176, EnemyEtis, "EnemyEtis-226");
				break;
			}
			case 4390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000147);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000177, EnemyEtis, "EnemyEtis-227");
				break;
			}
			case 4400: {
				orderActorToFactory(10001006, FormationDelheid001, "FormationDelheid001-228");
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000148);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000178, EnemyEtis, "EnemyEtis-229");
				break;
			}
			case 4450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000149);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000179, EnemyEtis, "EnemyEtis-230");
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000150);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000180, EnemyEtis, "EnemyEtis-231");
				break;
			}
			case 4500: {
				orderActorToFactory(10001007, FormationDelheid001, "FormationDelheid001-232");
				break;
			}
			case 4510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000151);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000181, EnemyEtis, "EnemyEtis-233");
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000152);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000182, EnemyEtis, "EnemyEtis-234");
				break;
			}
			case 4570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000153);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000183, EnemyEtis, "EnemyEtis-235");
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000154);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000184, EnemyEtis, "EnemyEtis-236");
				orderActorToFactory(10001008, FormationDelheid001, "FormationDelheid001-237");
				break;
			}
			case 4630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000155);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000185, EnemyEtis, "EnemyEtis-238");
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000156);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000186, EnemyEtis, "EnemyEtis-239");
				break;
			}
			case 4690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000157);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000187, EnemyEtis, "EnemyEtis-240");
				break;
			}
			case 4700: {
				orderActorToFactory(10001009, FormationDelheid001, "FormationDelheid001-241");
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000158);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000188, EnemyEtis, "EnemyEtis-242");
				break;
			}
			case 4750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000159);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000189, EnemyEtis, "EnemyEtis-243");
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000160);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000190, EnemyEtis, "EnemyEtis-244");
				break;
			}
			case 4800: {
				orderActorToFactory(10001010, FormationDelheid001, "FormationDelheid001-245");
				break;
			}
			case 4810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000161);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000191, EnemyEtis, "EnemyEtis-246");
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000162);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000192, EnemyEtis, "EnemyEtis-247");
				break;
			}
			case 4870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000163);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000193, EnemyEtis, "EnemyEtis-248");
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000164);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000194, EnemyEtis, "EnemyEtis-249");
				orderActorToFactory(10001011, FormationDelheid001, "FormationDelheid001-250");
				break;
			}
			case 4930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000165);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000195, EnemyEtis, "EnemyEtis-251");
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000166);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000196, EnemyEtis, "EnemyEtis-252");
				break;
			}
			case 4990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000167);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000197, EnemyEtis, "EnemyEtis-253");
				break;
			}
			case 5000: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001003);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000168);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000198, EnemyEtis, "EnemyEtis-254");
				break;
			}
			case 5050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000169);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000199, EnemyEtis, "EnemyEtis-255");
				break;
			}
			case 5080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000170);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000200, EnemyEtis, "EnemyEtis-256");
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001004);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000171);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000201, EnemyEtis, "EnemyEtis-257");
				break;
			}
			case 5140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000172);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000202, EnemyEtis, "EnemyEtis-258");
				break;
			}
			case 5170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000173);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000203, EnemyEtis, "EnemyEtis-259");
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000174);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000204, EnemyEtis, "EnemyEtis-260");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001005);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000175);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000205, EnemyEtis, "EnemyEtis-261");
				break;
			}
			case 5260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000176);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000206, EnemyEtis, "EnemyEtis-262");
				break;
			}
			case 5290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000177);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000207, EnemyEtis, "EnemyEtis-263");
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001006);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000178);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000208, EnemyEtis, "EnemyEtis-264");
				break;
			}
			case 5350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000179);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000209, EnemyEtis, "EnemyEtis-265");
				break;
			}
			case 5380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000180);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000210, EnemyEtis, "EnemyEtis-266");
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001007);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000181);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000211, EnemyEtis, "EnemyEtis-267");
				break;
			}
			case 5440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000182);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000212, EnemyEtis, "EnemyEtis-268");
				break;
			}
			case 5470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000183);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000213, EnemyEtis, "EnemyEtis-269");
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000184);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000214, EnemyEtis, "EnemyEtis-270");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001008);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000185);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000215, EnemyEtis, "EnemyEtis-271");
				break;
			}
			case 5560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000186);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000216, EnemyEtis, "EnemyEtis-272");
				break;
			}
			case 5590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000187);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000217, EnemyEtis, "EnemyEtis-273");
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001009);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000188);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000218, EnemyEtis, "EnemyEtis-274");
				break;
			}
			case 5650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000189);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000219, EnemyEtis, "EnemyEtis-275");
				break;
			}
			case 5680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000190);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000220, EnemyEtis, "EnemyEtis-276");
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001010);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000191);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000221, EnemyEtis, "EnemyEtis-277");
				break;
			}
			case 5740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000192);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000222, EnemyEtis, "EnemyEtis-278");
				break;
			}
			case 5770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000193);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000223, EnemyEtis, "EnemyEtis-279");
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000194);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000224, EnemyEtis, "EnemyEtis-280");
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10001011);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 5830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000195);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000225, EnemyEtis, "EnemyEtis-281");
				break;
			}
			case 5860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000196);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000226, EnemyEtis, "EnemyEtis-282");
				break;
			}
			case 5890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000197);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000227, EnemyEtis, "EnemyEtis-283");
				break;
			}
			case 5920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000198);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000228, EnemyEtis, "EnemyEtis-284");
				break;
			}
			case 5950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000199);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000229, EnemyEtis, "EnemyEtis-285");
				break;
			}
			case 5980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000200);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000230, EnemyEtis, "EnemyEtis-286");
				break;
			}
			case 6010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000201);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000231, EnemyEtis, "EnemyEtis-287");
				break;
			}
			case 6040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000202);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000232, EnemyEtis, "EnemyEtis-288");
				break;
			}
			case 6070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000203);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000233, EnemyEtis, "EnemyEtis-289");
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000204);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000234, EnemyEtis, "EnemyEtis-290");
				break;
			}
			case 6130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000205);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000235, EnemyEtis, "EnemyEtis-291");
				break;
			}
			case 6160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000206);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000236, EnemyEtis, "EnemyEtis-292");
				break;
			}
			case 6190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000207);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000237, EnemyEtis, "EnemyEtis-293");
				break;
			}
			case 6220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000208);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000238, EnemyEtis, "EnemyEtis-294");
				break;
			}
			case 6250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000209);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000239, EnemyEtis, "EnemyEtis-295");
				break;
			}
			case 6280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000210);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000240, EnemyEtis, "EnemyEtis-296");
				break;
			}
			case 6310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000211);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000241, EnemyEtis, "EnemyEtis-297");
				break;
			}
			case 6340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000212);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000242, EnemyEtis, "EnemyEtis-298");
				break;
			}
			case 6370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000213);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000243, EnemyEtis, "EnemyEtis-299");
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000214);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000244, EnemyEtis, "EnemyEtis-300");
				break;
			}
			case 6430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000215);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000245, EnemyEtis, "EnemyEtis-301");
				break;
			}
			case 6460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000216);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000246, EnemyEtis, "EnemyEtis-302");
				break;
			}
			case 6490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000217);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000247, EnemyEtis, "EnemyEtis-303");
				break;
			}
			case 6520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000218);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000248, EnemyEtis, "EnemyEtis-304");
				break;
			}
			case 6550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000219);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000249, EnemyEtis, "EnemyEtis-305");
				break;
			}
			case 6580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000220);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000250, EnemyEtis, "EnemyEtis-306");
				break;
			}
			case 6610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000221);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000251, EnemyEtis, "EnemyEtis-307");
				break;
			}
			case 6640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000222);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000252, EnemyEtis, "EnemyEtis-308");
				break;
			}
			case 6670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000223);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000253, EnemyEtis, "EnemyEtis-309");
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000224);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000254, EnemyEtis, "EnemyEtis-310");
				break;
			}
			case 6730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000225);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000255, EnemyEtis, "EnemyEtis-311");
				break;
			}
			case 6760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000226);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000256, EnemyEtis, "EnemyEtis-312");
				break;
			}
			case 6790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000227);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000257, EnemyEtis, "EnemyEtis-313");
				break;
			}
			case 6820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000228);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000258, EnemyEtis, "EnemyEtis-314");
				break;
			}
			case 6850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000229);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000259, EnemyEtis, "EnemyEtis-315");
				break;
			}
			case 6880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000230);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000260, EnemyEtis, "EnemyEtis-316");
				break;
			}
			case 6910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000231);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000261, EnemyEtis, "EnemyEtis-317");
				break;
			}
			case 6940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000232);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000262, EnemyEtis, "EnemyEtis-318");
				break;
			}
			case 6970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000233);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000263, EnemyEtis, "EnemyEtis-319");
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000234);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000264, EnemyEtis, "EnemyEtis-320");
				break;
			}
			case 7030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000235);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000265, EnemyEtis, "EnemyEtis-321");
				break;
			}
			case 7060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000236);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000266, EnemyEtis, "EnemyEtis-322");
				break;
			}
			case 7090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000237);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000267, EnemyEtis, "EnemyEtis-323");
				break;
			}
			case 7120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000238);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000268, EnemyEtis, "EnemyEtis-324");
				break;
			}
			case 7150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000239);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000269, EnemyEtis, "EnemyEtis-325");
				break;
			}
			case 7180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000240);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000270, EnemyEtis, "EnemyEtis-326");
				break;
			}
			case 7210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000241);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000271, EnemyEtis, "EnemyEtis-327");
				break;
			}
			case 7240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000242);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000272, EnemyEtis, "EnemyEtis-328");
				break;
			}
			case 7270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000243);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000273, EnemyEtis, "EnemyEtis-329");
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000244);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000274, EnemyEtis, "EnemyEtis-330");
				break;
			}
			case 7330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000245);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000275, EnemyEtis, "EnemyEtis-331");
				break;
			}
			case 7360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000246);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000276, EnemyEtis, "EnemyEtis-332");
				break;
			}
			case 7390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000247);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000277, EnemyEtis, "EnemyEtis-333");
				break;
			}
			case 7420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000248);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000278, EnemyEtis, "EnemyEtis-334");
				break;
			}
			case 7450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000249);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000279, EnemyEtis, "EnemyEtis-335");
				break;
			}
			case 7480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000250);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000280, EnemyEtis, "EnemyEtis-336");
				break;
			}
			case 7510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000251);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000281, EnemyEtis, "EnemyEtis-337");
				break;
			}
			case 7540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000252);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000282, EnemyEtis, "EnemyEtis-338");
				break;
			}
			case 7570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000253);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000283, EnemyEtis, "EnemyEtis-339");
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000254);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000284, EnemyEtis, "EnemyEtis-340");
				break;
			}
			case 7630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000255);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000285, EnemyEtis, "EnemyEtis-341");
				break;
			}
			case 7660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000256);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000286, EnemyEtis, "EnemyEtis-342");
				break;
			}
			case 7690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000257);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000287, EnemyEtis, "EnemyEtis-343");
				break;
			}
			case 7720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000258);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000288, EnemyEtis, "EnemyEtis-344");
				break;
			}
			case 7750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000259);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000289, EnemyEtis, "EnemyEtis-345");
				break;
			}
			case 7780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000260);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000290, EnemyEtis, "EnemyEtis-346");
				break;
			}
			case 7810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000261);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000291, EnemyEtis, "EnemyEtis-347");
				break;
			}
			case 7840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000262);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000292, EnemyEtis, "EnemyEtis-348");
				break;
			}
			case 7870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000263);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000293, EnemyEtis, "EnemyEtis-349");
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000264);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000294, EnemyEtis, "EnemyEtis-350");
				break;
			}
			case 7930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000265);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000295, EnemyEtis, "EnemyEtis-351");
				break;
			}
			case 7960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000266);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000296, EnemyEtis, "EnemyEtis-352");
				break;
			}
			case 7990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000267);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000297, EnemyEtis, "EnemyEtis-353");
				break;
			}
			case 8020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000268);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000298, EnemyEtis, "EnemyEtis-354");
				break;
			}
			case 8050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000269);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000299, EnemyEtis, "EnemyEtis-355");
				break;
			}
			case 8080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000270);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000300, EnemyEtis, "EnemyEtis-356");
				break;
			}
			case 8110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000271);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000301, EnemyEtis, "EnemyEtis-357");
				break;
			}
			case 8140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000272);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000302, EnemyEtis, "EnemyEtis-358");
				break;
			}
			case 8170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000273);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000303, EnemyEtis, "EnemyEtis-359");
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000274);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000304, EnemyEtis, "EnemyEtis-360");
				break;
			}
			case 8230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000275);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000305, EnemyEtis, "EnemyEtis-361");
				break;
			}
			case 8260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000276);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000306, EnemyEtis, "EnemyEtis-362");
				break;
			}
			case 8290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000277);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000307, EnemyEtis, "EnemyEtis-363");
				break;
			}
			case 8320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000278);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000308, EnemyEtis, "EnemyEtis-364");
				break;
			}
			case 8350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000279);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000309, EnemyEtis, "EnemyEtis-365");
				break;
			}
			case 8380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000280);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000310, EnemyEtis, "EnemyEtis-366");
				break;
			}
			case 8410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000281);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000311, EnemyEtis, "EnemyEtis-367");
				break;
			}
			case 8440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000282);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000312, EnemyEtis, "EnemyEtis-368");
				break;
			}
			case 8470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000283);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000313, EnemyEtis, "EnemyEtis-369");
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000284);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000314, EnemyEtis, "EnemyEtis-370");
				break;
			}
			case 8530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000285);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000315, EnemyEtis, "EnemyEtis-371");
				break;
			}
			case 8560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000286);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000316, EnemyEtis, "EnemyEtis-372");
				break;
			}
			case 8590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000287);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000317, EnemyEtis, "EnemyEtis-373");
				break;
			}
			case 8620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000288);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000318, EnemyEtis, "EnemyEtis-374");
				break;
			}
			case 8650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000289);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000319, EnemyEtis, "EnemyEtis-375");
				break;
			}
			case 8680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000290);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000320, EnemyEtis, "EnemyEtis-376");
				break;
			}
			case 8710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000291);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000321, EnemyEtis, "EnemyEtis-377");
				break;
			}
			case 8740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000292);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000322, EnemyEtis, "EnemyEtis-378");
				break;
			}
			case 8770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000293);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000323, EnemyEtis, "EnemyEtis-379");
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000294);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000324, EnemyEtis, "EnemyEtis-380");
				break;
			}
			case 8830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000295);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000325, EnemyEtis, "EnemyEtis-381");
				break;
			}
			case 8860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000296);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000326, EnemyEtis, "EnemyEtis-382");
				break;
			}
			case 8890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000297);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000327, EnemyEtis, "EnemyEtis-383");
				break;
			}
			case 8920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000298);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000328, EnemyEtis, "EnemyEtis-384");
				break;
			}
			case 8950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000299);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000329, EnemyEtis, "EnemyEtis-385");
				break;
			}
			case 8980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000300);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000330, EnemyEtis, "EnemyEtis-386");
				break;
			}
			case 9010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000301);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000331, EnemyEtis, "EnemyEtis-387");
				break;
			}
			case 9040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000302);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000332, EnemyEtis, "EnemyEtis-388");
				break;
			}
			case 9070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000303);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000333, EnemyEtis, "EnemyEtis-389");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-390");
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000304);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000334, EnemyEtis, "EnemyEtis-391");
				break;
			}
			case 9130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000305);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000335, EnemyEtis, "EnemyEtis-392");
				break;
			}
			case 9160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000306);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000336, EnemyEtis, "EnemyEtis-393");
				break;
			}
			case 9190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000307);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000337, EnemyEtis, "EnemyEtis-394");
				break;
			}
			case 9220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000308);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000338, EnemyEtis, "EnemyEtis-395");
				break;
			}
			case 9250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000309);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000339, EnemyEtis, "EnemyEtis-396");
				break;
			}
			case 9280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000310);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000340, EnemyEtis, "EnemyEtis-397");
				break;
			}
			case 9310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000311);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000341, EnemyEtis, "EnemyEtis-398");
				break;
			}
			case 9340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000312);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000342, EnemyEtis, "EnemyEtis-399");
				break;
			}
			case 9370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000313);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000343, EnemyEtis, "EnemyEtis-400");
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000314);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000344, EnemyEtis, "EnemyEtis-401");
				break;
			}
			case 9430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000315);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000345, EnemyEtis, "EnemyEtis-402");
				break;
			}
			case 9460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000316);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000346, EnemyEtis, "EnemyEtis-403");
				break;
			}
			case 9490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000317);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000347, EnemyEtis, "EnemyEtis-404");
				break;
			}
			case 9520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000318);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000348, EnemyEtis, "EnemyEtis-405");
				break;
			}
			case 9550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000319);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000349, EnemyEtis, "EnemyEtis-406");
				break;
			}
			case 9580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000320);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000350, EnemyEtis, "EnemyEtis-407");
				break;
			}
			case 9610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000321);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000351, EnemyEtis, "EnemyEtis-408");
				break;
			}
			case 9640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000322);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000352, EnemyEtis, "EnemyEtis-409");
				break;
			}
			case 9670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000323);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000353, EnemyEtis, "EnemyEtis-410");
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000324);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000354, EnemyEtis, "EnemyEtis-411");
				break;
			}
			case 9730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000325);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000355, EnemyEtis, "EnemyEtis-412");
				break;
			}
			case 9760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000326);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000356, EnemyEtis, "EnemyEtis-413");
				break;
			}
			case 9790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000327);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000357, EnemyEtis, "EnemyEtis-414");
				break;
			}
			case 9820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000328);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000358, EnemyEtis, "EnemyEtis-415");
				break;
			}
			case 9850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000329);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000359, EnemyEtis, "EnemyEtis-416");
				break;
			}
			case 9880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000330);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000360, EnemyEtis, "EnemyEtis-417");
				break;
			}
			case 9910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000331);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000361, EnemyEtis, "EnemyEtis-418");
				break;
			}
			case 9940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000332);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000362, EnemyEtis, "EnemyEtis-419");
				break;
			}
			case 9970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000333);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000363, EnemyEtis, "EnemyEtis-420");
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000334);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000364, EnemyEtis, "EnemyEtis-421");
				break;
			}
			case 10030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000335);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000365, EnemyEtis, "EnemyEtis-422");
				break;
			}
			case 10060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000336);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000366, EnemyEtis, "EnemyEtis-423");
				break;
			}
			case 10090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000337);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000367, EnemyEtis, "EnemyEtis-424");
				break;
			}
			case 10120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000338);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000368, EnemyEtis, "EnemyEtis-425");
				break;
			}
			case 10150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000339);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000369, EnemyEtis, "EnemyEtis-426");
				break;
			}
			case 10180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000340);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000370, EnemyEtis, "EnemyEtis-427");
				break;
			}
			case 10210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000341);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000371, EnemyEtis, "EnemyEtis-428");
				break;
			}
			case 10240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000342);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000372, EnemyEtis, "EnemyEtis-429");
				break;
			}
			case 10270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000343);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000373, EnemyEtis, "EnemyEtis-430");
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000344);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000374, EnemyEtis, "EnemyEtis-431");
				break;
			}
			case 10330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000345);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000375, EnemyEtis, "EnemyEtis-432");
				break;
			}
			case 10360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000346);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000376, EnemyEtis, "EnemyEtis-433");
				break;
			}
			case 10390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000347);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000377, EnemyEtis, "EnemyEtis-434");
				break;
			}
			case 10420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000348);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000378, EnemyEtis, "EnemyEtis-435");
				break;
			}
			case 10450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000349);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000379, EnemyEtis, "EnemyEtis-436");
				break;
			}
			case 10480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000350);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000380, EnemyEtis, "EnemyEtis-437");
				break;
			}
			case 10510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000351);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000381, EnemyEtis, "EnemyEtis-438");
				break;
			}
			case 10540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000352);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000382, EnemyEtis, "EnemyEtis-439");
				break;
			}
			case 10570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000353);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000383, EnemyEtis, "EnemyEtis-440");
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000354);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000384, EnemyEtis, "EnemyEtis-441");
				break;
			}
			case 10630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000355);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000385, EnemyEtis, "EnemyEtis-442");
				break;
			}
			case 10660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000356);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000386, EnemyEtis, "EnemyEtis-443");
				break;
			}
			case 10690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000357);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000387, EnemyEtis, "EnemyEtis-444");
				break;
			}
			case 10720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000358);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000388, EnemyEtis, "EnemyEtis-445");
				break;
			}
			case 10750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000359);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000389, EnemyEtis, "EnemyEtis-446");
				break;
			}
			case 10780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000360);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000390, EnemyEtis, "EnemyEtis-447");
				break;
			}
			case 10810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000361);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000391, EnemyEtis, "EnemyEtis-448");
				break;
			}
			case 10840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000362);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000392, EnemyEtis, "EnemyEtis-449");
				break;
			}
			case 10870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000363);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000393, EnemyEtis, "EnemyEtis-450");
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000364);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000394, EnemyEtis, "EnemyEtis-451");
				break;
			}
			case 10930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000365);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000395, EnemyEtis, "EnemyEtis-452");
				break;
			}
			case 10960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000366);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000396, EnemyEtis, "EnemyEtis-453");
				break;
			}
			case 10990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000367);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000397, EnemyEtis, "EnemyEtis-454");
				break;
			}
			case 11020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000368);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000398, EnemyEtis, "EnemyEtis-455");
				break;
			}
			case 11050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000369);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000399, EnemyEtis, "EnemyEtis-456");
				break;
			}
			case 11080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000370);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000400, EnemyEtis, "EnemyEtis-457");
				break;
			}
			case 11110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000371);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000401, EnemyEtis, "EnemyEtis-458");
				break;
			}
			case 11140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000372);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000402, EnemyEtis, "EnemyEtis-459");
				break;
			}
			case 11170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000373);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000403, EnemyEtis, "EnemyEtis-460");
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000374);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000404, EnemyEtis, "EnemyEtis-461");
				break;
			}
			case 11230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000375);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000405, EnemyEtis, "EnemyEtis-462");
				break;
			}
			case 11260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000376);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000406, EnemyEtis, "EnemyEtis-463");
				break;
			}
			case 11290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000377);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000407, EnemyEtis, "EnemyEtis-464");
				break;
			}
			case 11320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000378);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000408, EnemyEtis, "EnemyEtis-465");
				break;
			}
			case 11350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000379);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000409, EnemyEtis, "EnemyEtis-466");
				break;
			}
			case 11380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000380);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000410, EnemyEtis, "EnemyEtis-467");
				break;
			}
			case 11410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000381);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000411, EnemyEtis, "EnemyEtis-468");
				break;
			}
			case 11440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000382);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000412, EnemyEtis, "EnemyEtis-469");
				break;
			}
			case 11470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000383);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000413, EnemyEtis, "EnemyEtis-470");
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000384);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000414, EnemyEtis, "EnemyEtis-471");
				break;
			}
			case 11530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000385);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000415, EnemyEtis, "EnemyEtis-472");
				break;
			}
			case 11560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000386);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000416, EnemyEtis, "EnemyEtis-473");
				break;
			}
			case 11590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000387);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000417, EnemyEtis, "EnemyEtis-474");
				break;
			}
			case 11620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000388);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000418, EnemyEtis, "EnemyEtis-475");
				break;
			}
			case 11650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000389);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000419, EnemyEtis, "EnemyEtis-476");
				break;
			}
			case 11680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000390);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000420, EnemyEtis, "EnemyEtis-477");
				break;
			}
			case 11710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000391);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000421, EnemyEtis, "EnemyEtis-478");
				break;
			}
			case 11740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000392);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000422, EnemyEtis, "EnemyEtis-479");
				break;
			}
			case 11770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000393);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000423, EnemyEtis, "EnemyEtis-480");
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000394);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000424, EnemyEtis, "EnemyEtis-481");
				break;
			}
			case 11830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000395);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000425, EnemyEtis, "EnemyEtis-482");
				break;
			}
			case 11860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000396);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000426, EnemyEtis, "EnemyEtis-483");
				break;
			}
			case 11890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000397);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000427, EnemyEtis, "EnemyEtis-484");
				break;
			}
			case 11920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000398);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000428, EnemyEtis, "EnemyEtis-485");
				break;
			}
			case 11950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000399);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000429, EnemyEtis, "EnemyEtis-486");
				break;
			}
			case 11980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000400);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000430, EnemyEtis, "EnemyEtis-487");
				break;
			}
			case 12010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000401);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000431, EnemyEtis, "EnemyEtis-488");
				break;
			}
			case 12040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000402);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000432, EnemyEtis, "EnemyEtis-489");
				break;
			}
			case 12070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000403);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000433, EnemyEtis, "EnemyEtis-490");
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000404);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000434, EnemyEtis, "EnemyEtis-491");
				break;
			}
			case 12130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000405);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000435, EnemyEtis, "EnemyEtis-492");
				break;
			}
			case 12160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000406);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000436, EnemyEtis, "EnemyEtis-493");
				break;
			}
			case 12190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000407);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000437, EnemyEtis, "EnemyEtis-494");
				break;
			}
			case 12220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000408);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000438, EnemyEtis, "EnemyEtis-495");
				break;
			}
			case 12250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000409);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000439, EnemyEtis, "EnemyEtis-496");
				break;
			}
			case 12280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000410);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000440, EnemyEtis, "EnemyEtis-497");
				break;
			}
			case 12310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000411);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000441, EnemyEtis, "EnemyEtis-498");
				break;
			}
			case 12340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000412);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000442, EnemyEtis, "EnemyEtis-499");
				break;
			}
			case 12370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000413);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000443, EnemyEtis, "EnemyEtis-500");
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000414);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000444, EnemyEtis, "EnemyEtis-501");
				break;
			}
			case 12430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000415);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000445, EnemyEtis, "EnemyEtis-502");
				break;
			}
			case 12460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000416);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000446, EnemyEtis, "EnemyEtis-503");
				break;
			}
			case 12490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000417);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000447, EnemyEtis, "EnemyEtis-504");
				break;
			}
			case 12520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000418);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000448, EnemyEtis, "EnemyEtis-505");
				break;
			}
			case 12550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000419);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000449, EnemyEtis, "EnemyEtis-506");
				break;
			}
			case 12580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000420);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000450, EnemyEtis, "EnemyEtis-507");
				break;
			}
			case 12610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000421);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000451, EnemyEtis, "EnemyEtis-508");
				break;
			}
			case 12640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000422);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000452, EnemyEtis, "EnemyEtis-509");
				break;
			}
			case 12670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000423);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000453, EnemyEtis, "EnemyEtis-510");
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000424);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000454, EnemyEtis, "EnemyEtis-511");
				break;
			}
			case 12730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000425);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000455, EnemyEtis, "EnemyEtis-512");
				break;
			}
			case 12760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000426);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000456, EnemyEtis, "EnemyEtis-513");
				break;
			}
			case 12790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000427);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000457, EnemyEtis, "EnemyEtis-514");
				break;
			}
			case 12820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000428);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000458, EnemyEtis, "EnemyEtis-515");
				break;
			}
			case 12850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000429);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000459, EnemyEtis, "EnemyEtis-516");
				break;
			}
			case 12880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000430);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000460, EnemyEtis, "EnemyEtis-517");
				break;
			}
			case 12910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000431);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000461, EnemyEtis, "EnemyEtis-518");
				break;
			}
			case 12940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000432);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000462, EnemyEtis, "EnemyEtis-519");
				break;
			}
			case 12970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000433);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000463, EnemyEtis, "EnemyEtis-520");
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000434);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000464, EnemyEtis, "EnemyEtis-521");
				break;
			}
			case 13030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000435);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000465, EnemyEtis, "EnemyEtis-522");
				break;
			}
			case 13060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000436);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000466, EnemyEtis, "EnemyEtis-523");
				break;
			}
			case 13090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000437);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000467, EnemyEtis, "EnemyEtis-524");
				break;
			}
			case 13120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000438);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000468, EnemyEtis, "EnemyEtis-525");
				break;
			}
			case 13150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000439);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000469, EnemyEtis, "EnemyEtis-526");
				break;
			}
			case 13180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000440);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000470, EnemyEtis, "EnemyEtis-527");
				break;
			}
			case 13210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000441);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000471, EnemyEtis, "EnemyEtis-528");
				break;
			}
			case 13240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000442);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000472, EnemyEtis, "EnemyEtis-529");
				break;
			}
			case 13270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000443);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000473, EnemyEtis, "EnemyEtis-530");
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000444);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000474, EnemyEtis, "EnemyEtis-531");
				break;
			}
			case 13330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000445);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000475, EnemyEtis, "EnemyEtis-532");
				break;
			}
			case 13360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000446);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000476, EnemyEtis, "EnemyEtis-533");
				break;
			}
			case 13390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000447);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000477, EnemyEtis, "EnemyEtis-534");
				break;
			}
			case 13420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000448);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000478, EnemyEtis, "EnemyEtis-535");
				break;
			}
			case 13450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000449);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000479, EnemyEtis, "EnemyEtis-536");
				break;
			}
			case 13480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000450);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000480, EnemyEtis, "EnemyEtis-537");
				break;
			}
			case 13510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000451);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000481, EnemyEtis, "EnemyEtis-538");
				break;
			}
			case 13540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000452);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000482, EnemyEtis, "EnemyEtis-539");
				break;
			}
			case 13570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000453);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000483, EnemyEtis, "EnemyEtis-540");
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000454);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000484, EnemyEtis, "EnemyEtis-541");
				break;
			}
			case 13630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000455);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000485, EnemyEtis, "EnemyEtis-542");
				break;
			}
			case 13660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000456);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000486, EnemyEtis, "EnemyEtis-543");
				break;
			}
			case 13690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000457);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000487, EnemyEtis, "EnemyEtis-544");
				break;
			}
			case 13720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000458);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000488, EnemyEtis, "EnemyEtis-545");
				break;
			}
			case 13750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000459);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000489, EnemyEtis, "EnemyEtis-546");
				break;
			}
			case 13780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000460);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000490, EnemyEtis, "EnemyEtis-547");
				break;
			}
			case 13810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000461);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000491, EnemyEtis, "EnemyEtis-548");
				break;
			}
			case 13840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000462);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000492, EnemyEtis, "EnemyEtis-549");
				break;
			}
			case 13870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000463);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000493, EnemyEtis, "EnemyEtis-550");
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000464);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000494, EnemyEtis, "EnemyEtis-551");
				break;
			}
			case 13930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000465);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000495, EnemyEtis, "EnemyEtis-552");
				break;
			}
			case 13960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000466);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000496, EnemyEtis, "EnemyEtis-553");
				break;
			}
			case 13990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000467);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000497, EnemyEtis, "EnemyEtis-554");
				break;
			}
			case 14020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000468);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000498, EnemyEtis, "EnemyEtis-555");
				break;
			}
			case 14050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000469);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000499, EnemyEtis, "EnemyEtis-556");
				break;
			}
			case 14080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000470);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000500, EnemyEtis, "EnemyEtis-557");
				break;
			}
			case 14110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000471);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000501, EnemyEtis, "EnemyEtis-558");
				break;
			}
			case 14140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000472);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000502, EnemyEtis, "EnemyEtis-559");
				break;
			}
			case 14170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000473);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000503, EnemyEtis, "EnemyEtis-560");
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000474);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000504, EnemyEtis, "EnemyEtis-561");
				break;
			}
			case 14230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000475);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000505, EnemyEtis, "EnemyEtis-562");
				break;
			}
			case 14260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000476);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000506, EnemyEtis, "EnemyEtis-563");
				break;
			}
			case 14290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000477);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000507, EnemyEtis, "EnemyEtis-564");
				break;
			}
			case 14320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000478);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000508, EnemyEtis, "EnemyEtis-565");
				break;
			}
			case 14350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000479);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000509, EnemyEtis, "EnemyEtis-566");
				break;
			}
			case 14380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000480);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000510, EnemyEtis, "EnemyEtis-567");
				break;
			}
			case 14410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000481);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000511, EnemyEtis, "EnemyEtis-568");
				break;
			}
			case 14440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000482);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000512, EnemyEtis, "EnemyEtis-569");
				break;
			}
			case 14470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000483);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000513, EnemyEtis, "EnemyEtis-570");
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000484);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000514, EnemyEtis, "EnemyEtis-571");
				break;
			}
			case 14530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000485);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000515, EnemyEtis, "EnemyEtis-572");
				break;
			}
			case 14560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000486);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000516, EnemyEtis, "EnemyEtis-573");
				break;
			}
			case 14590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000487);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000517, EnemyEtis, "EnemyEtis-574");
				break;
			}
			case 14620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000488);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000518, EnemyEtis, "EnemyEtis-575");
				break;
			}
			case 14650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000489);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000519, EnemyEtis, "EnemyEtis-576");
				break;
			}
			case 14680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000490);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000520, EnemyEtis, "EnemyEtis-577");
				break;
			}
			case 14710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000491);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000521, EnemyEtis, "EnemyEtis-578");
				break;
			}
			case 14740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000492);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000522, EnemyEtis, "EnemyEtis-579");
				break;
			}
			case 14770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000493);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000523, EnemyEtis, "EnemyEtis-580");
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000494);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000524, EnemyEtis, "EnemyEtis-581");
				break;
			}
			case 14830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000495);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000525, EnemyEtis, "EnemyEtis-582");
				break;
			}
			case 14860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000496);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000526, EnemyEtis, "EnemyEtis-583");
				break;
			}
			case 14890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000497);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000527, EnemyEtis, "EnemyEtis-584");
				break;
			}
			case 14920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000498);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000528, EnemyEtis, "EnemyEtis-585");
				break;
			}
			case 14950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000499);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000529, EnemyEtis, "EnemyEtis-586");
				break;
			}
			case 14980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000500);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000530, EnemyEtis, "EnemyEtis-587");
				break;
			}
			case 15010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000501);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000531, EnemyEtis, "EnemyEtis-588");
				break;
			}
			case 15040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000502);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000532, EnemyEtis, "EnemyEtis-589");
				break;
			}
			case 15070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000503);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000533, EnemyEtis, "EnemyEtis-590");
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000504);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000534, EnemyEtis, "EnemyEtis-591");
				break;
			}
			case 15130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000505);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000535, EnemyEtis, "EnemyEtis-592");
				break;
			}
			case 15160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000506);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000536, EnemyEtis, "EnemyEtis-593");
				break;
			}
			case 15190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000507);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000537, EnemyEtis, "EnemyEtis-594");
				break;
			}
			case 15220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000508);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000538, EnemyEtis, "EnemyEtis-595");
				break;
			}
			case 15250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000509);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000539, EnemyEtis, "EnemyEtis-596");
				break;
			}
			case 15280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000510);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000540, EnemyEtis, "EnemyEtis-597");
				break;
			}
			case 15310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000511);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000541, EnemyEtis, "EnemyEtis-598");
				break;
			}
			case 15340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000512);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000542, EnemyEtis, "EnemyEtis-599");
				break;
			}
			case 15370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000513);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000543, EnemyEtis, "EnemyEtis-600");
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000514);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000544, EnemyEtis, "EnemyEtis-601");
				break;
			}
			case 15430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000515);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000545, EnemyEtis, "EnemyEtis-602");
				break;
			}
			case 15460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000516);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000546, EnemyEtis, "EnemyEtis-603");
				break;
			}
			case 15490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000517);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000547, EnemyEtis, "EnemyEtis-604");
				break;
			}
			case 15520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000518);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000548, EnemyEtis, "EnemyEtis-605");
				break;
			}
			case 15550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000519);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000549, EnemyEtis, "EnemyEtis-606");
				break;
			}
			case 15580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000520);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000550, EnemyEtis, "EnemyEtis-607");
				break;
			}
			case 15610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000521);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000551, EnemyEtis, "EnemyEtis-608");
				break;
			}
			case 15640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000522);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000552, EnemyEtis, "EnemyEtis-609");
				break;
			}
			case 15670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000523);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000553, EnemyEtis, "EnemyEtis-610");
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000524);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000554, EnemyEtis, "EnemyEtis-611");
				break;
			}
			case 15730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000525);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000555, EnemyEtis, "EnemyEtis-612");
				break;
			}
			case 15760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000526);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000556, EnemyEtis, "EnemyEtis-613");
				break;
			}
			case 15790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000527);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000557, EnemyEtis, "EnemyEtis-614");
				break;
			}
			case 15820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000528);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000558, EnemyEtis, "EnemyEtis-615");
				break;
			}
			case 15850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000529);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000559, EnemyEtis, "EnemyEtis-616");
				break;
			}
			case 15880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000530);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000560, EnemyEtis, "EnemyEtis-617");
				break;
			}
			case 15910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000531);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000561, EnemyEtis, "EnemyEtis-618");
				break;
			}
			case 15940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000532);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000562, EnemyEtis, "EnemyEtis-619");
				break;
			}
			case 15970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000533);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000563, EnemyEtis, "EnemyEtis-620");
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000534);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000564, EnemyEtis, "EnemyEtis-621");
				break;
			}
			case 16030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000535);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000565, EnemyEtis, "EnemyEtis-622");
				break;
			}
			case 16060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000536);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000566, EnemyEtis, "EnemyEtis-623");
				break;
			}
			case 16090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000537);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000567, EnemyEtis, "EnemyEtis-624");
				break;
			}
			case 16120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000538);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000568, EnemyEtis, "EnemyEtis-625");
				break;
			}
			case 16150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000539);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000569, EnemyEtis, "EnemyEtis-626");
				break;
			}
			case 16180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000540);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000570, EnemyEtis, "EnemyEtis-627");
				break;
			}
			case 16210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000541);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000571, EnemyEtis, "EnemyEtis-628");
				break;
			}
			case 16240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000542);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000572, EnemyEtis, "EnemyEtis-629");
				break;
			}
			case 16270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000543);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000573, EnemyEtis, "EnemyEtis-630");
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000544);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000574, EnemyEtis, "EnemyEtis-631");
				break;
			}
			case 16330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000545);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000575, EnemyEtis, "EnemyEtis-632");
				break;
			}
			case 16360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000546);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000576, EnemyEtis, "EnemyEtis-633");
				break;
			}
			case 16390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000547);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000577, EnemyEtis, "EnemyEtis-634");
				break;
			}
			case 16420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000548);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000578, EnemyEtis, "EnemyEtis-635");
				break;
			}
			case 16450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000549);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000579, EnemyEtis, "EnemyEtis-636");
				break;
			}
			case 16480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000550);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000580, EnemyEtis, "EnemyEtis-637");
				break;
			}
			case 16510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000551);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000581, EnemyEtis, "EnemyEtis-638");
				break;
			}
			case 16540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000552);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000582, EnemyEtis, "EnemyEtis-639");
				break;
			}
			case 16570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000553);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000583, EnemyEtis, "EnemyEtis-640");
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000554);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000584, EnemyEtis, "EnemyEtis-641");
				break;
			}
			case 16630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000555);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000585, EnemyEtis, "EnemyEtis-642");
				break;
			}
			case 16660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000556);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000586, EnemyEtis, "EnemyEtis-643");
				break;
			}
			case 16690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000557);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000587, EnemyEtis, "EnemyEtis-644");
				break;
			}
			case 16720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000558);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000588, EnemyEtis, "EnemyEtis-645");
				break;
			}
			case 16750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000559);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000589, EnemyEtis, "EnemyEtis-646");
				break;
			}
			case 16780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000560);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000590, EnemyEtis, "EnemyEtis-647");
				break;
			}
			case 16810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000561);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000591, EnemyEtis, "EnemyEtis-648");
				break;
			}
			case 16840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000562);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000592, EnemyEtis, "EnemyEtis-649");
				break;
			}
			case 16870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000563);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000593, EnemyEtis, "EnemyEtis-650");
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000564);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000594, EnemyEtis, "EnemyEtis-651");
				break;
			}
			case 16930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000565);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000595, EnemyEtis, "EnemyEtis-652");
				break;
			}
			case 16960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000566);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000596, EnemyEtis, "EnemyEtis-653");
				break;
			}
			case 16990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000567);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000597, EnemyEtis, "EnemyEtis-654");
				break;
			}
			case 17020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000568);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000598, EnemyEtis, "EnemyEtis-655");
				break;
			}
			case 17050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000569);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000599, EnemyEtis, "EnemyEtis-656");
				break;
			}
			case 17080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000570);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000600, EnemyEtis, "EnemyEtis-657");
				break;
			}
			case 17110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000571);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000601, EnemyEtis, "EnemyEtis-658");
				break;
			}
			case 17140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000572);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000602, EnemyEtis, "EnemyEtis-659");
				break;
			}
			case 17170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000573);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000603, EnemyEtis, "EnemyEtis-660");
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000574);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000604, EnemyEtis, "EnemyEtis-661");
				break;
			}
			case 17230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000575);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000605, EnemyEtis, "EnemyEtis-662");
				break;
			}
			case 17260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000576);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000606, EnemyEtis, "EnemyEtis-663");
				break;
			}
			case 17290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000577);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000607, EnemyEtis, "EnemyEtis-664");
				break;
			}
			case 17320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000578);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000608, EnemyEtis, "EnemyEtis-665");
				break;
			}
			case 17350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000579);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000609, EnemyEtis, "EnemyEtis-666");
				break;
			}
			case 17380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000580);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000610, EnemyEtis, "EnemyEtis-667");
				break;
			}
			case 17410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000581);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000611, EnemyEtis, "EnemyEtis-668");
				break;
			}
			case 17440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000582);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000612, EnemyEtis, "EnemyEtis-669");
				break;
			}
			case 17470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000583);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000613, EnemyEtis, "EnemyEtis-670");
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000584);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000614, EnemyEtis, "EnemyEtis-671");
				break;
			}
			case 17530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000585);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000615, EnemyEtis, "EnemyEtis-672");
				break;
			}
			case 17560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000586);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000616, EnemyEtis, "EnemyEtis-673");
				break;
			}
			case 17590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000587);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000617, EnemyEtis, "EnemyEtis-674");
				break;
			}
			case 17620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000588);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000618, EnemyEtis, "EnemyEtis-675");
				break;
			}
			case 17650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000589);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000619, EnemyEtis, "EnemyEtis-676");
				break;
			}
			case 17680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000590);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000620, EnemyEtis, "EnemyEtis-677");
				break;
			}
			case 17710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000591);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000621, EnemyEtis, "EnemyEtis-678");
				break;
			}
			case 17740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000592);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000622, EnemyEtis, "EnemyEtis-679");
				break;
			}
			case 17770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000593);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000623, EnemyEtis, "EnemyEtis-680");
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000594);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000624, EnemyEtis, "EnemyEtis-681");
				break;
			}
			case 17830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000595);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000625, EnemyEtis, "EnemyEtis-682");
				break;
			}
			case 17860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000596);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000626, EnemyEtis, "EnemyEtis-683");
				break;
			}
			case 17890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000597);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000627, EnemyEtis, "EnemyEtis-684");
				break;
			}
			case 17920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000598);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000628, EnemyEtis, "EnemyEtis-685");
				break;
			}
			case 17950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000599);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000629, EnemyEtis, "EnemyEtis-686");
				break;
			}
			case 17980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000600);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000630, EnemyEtis, "EnemyEtis-687");
				break;
			}
			case 18010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000601);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000631, EnemyEtis, "EnemyEtis-688");
				break;
			}
			case 18040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000602);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000632, EnemyEtis, "EnemyEtis-689");
				break;
			}
			case 18070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000603);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000633, EnemyEtis, "EnemyEtis-690");
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000604);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000634, EnemyEtis, "EnemyEtis-691");
				break;
			}
			case 18130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000605);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000635, EnemyEtis, "EnemyEtis-692");
				break;
			}
			case 18160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000606);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000636, EnemyEtis, "EnemyEtis-693");
				break;
			}
			case 18190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000607);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000637, EnemyEtis, "EnemyEtis-694");
				break;
			}
			case 18220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000608);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000638, EnemyEtis, "EnemyEtis-695");
				break;
			}
			case 18250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000609);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000639, EnemyEtis, "EnemyEtis-696");
				break;
			}
			case 18280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000610);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000640, EnemyEtis, "EnemyEtis-697");
				break;
			}
			case 18310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000611);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000641, EnemyEtis, "EnemyEtis-698");
				break;
			}
			case 18340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000612);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000642, EnemyEtis, "EnemyEtis-699");
				break;
			}
			case 18370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000613);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000643, EnemyEtis, "EnemyEtis-700");
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000614);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000644, EnemyEtis, "EnemyEtis-701");
				break;
			}
			case 18430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000615);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000645, EnemyEtis, "EnemyEtis-702");
				break;
			}
			case 18460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000616);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000646, EnemyEtis, "EnemyEtis-703");
				break;
			}
			case 18490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000617);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000647, EnemyEtis, "EnemyEtis-704");
				break;
			}
			case 18520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000618);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000648, EnemyEtis, "EnemyEtis-705");
				break;
			}
			case 18550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000619);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000649, EnemyEtis, "EnemyEtis-706");
				break;
			}
			case 18580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000620);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000650, EnemyEtis, "EnemyEtis-707");
				break;
			}
			case 18610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000621);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000651, EnemyEtis, "EnemyEtis-708");
				break;
			}
			case 18640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000622);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000652, EnemyEtis, "EnemyEtis-709");
				break;
			}
			case 18670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000623);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000653, EnemyEtis, "EnemyEtis-710");
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000624);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000654, EnemyEtis, "EnemyEtis-711");
				break;
			}
			case 18730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000625);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000655, EnemyEtis, "EnemyEtis-712");
				break;
			}
			case 18760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000626);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000656, EnemyEtis, "EnemyEtis-713");
				break;
			}
			case 18790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000627);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000657, EnemyEtis, "EnemyEtis-714");
				break;
			}
			case 18820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000628);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000658, EnemyEtis, "EnemyEtis-715");
				break;
			}
			case 18850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000629);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000659, EnemyEtis, "EnemyEtis-716");
				break;
			}
			case 18880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000630);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000660, EnemyEtis, "EnemyEtis-717");
				break;
			}
			case 18910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000631);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000661, EnemyEtis, "EnemyEtis-718");
				break;
			}
			case 18940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000632);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000662, EnemyEtis, "EnemyEtis-719");
				break;
			}
			case 18970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000633);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000663, EnemyEtis, "EnemyEtis-720");
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000634);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000664, EnemyEtis, "EnemyEtis-721");
				break;
			}
			case 19030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000635);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000665, EnemyEtis, "EnemyEtis-722");
				break;
			}
			case 19060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000636);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000666, EnemyEtis, "EnemyEtis-723");
				break;
			}
			case 19090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000637);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000667, EnemyEtis, "EnemyEtis-724");
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-725");
				break;
			}
			case 19120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000638);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000668, EnemyEtis, "EnemyEtis-726");
				break;
			}
			case 19150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000639);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000669, EnemyEtis, "EnemyEtis-727");
				break;
			}
			case 19180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000640);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000670, EnemyEtis, "EnemyEtis-728");
				break;
			}
			case 19210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000641);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000671, EnemyEtis, "EnemyEtis-729");
				break;
			}
			case 19240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000642);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000672, EnemyEtis, "EnemyEtis-730");
				break;
			}
			case 19270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000643);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000673, EnemyEtis, "EnemyEtis-731");
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000644);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000674, EnemyEtis, "EnemyEtis-732");
				break;
			}
			case 19330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000645);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000675, EnemyEtis, "EnemyEtis-733");
				break;
			}
			case 19360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000646);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000676, EnemyEtis, "EnemyEtis-734");
				break;
			}
			case 19390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000647);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000677, EnemyEtis, "EnemyEtis-735");
				break;
			}
			case 19420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000648);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000678, EnemyEtis, "EnemyEtis-736");
				break;
			}
			case 19450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000649);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000679, EnemyEtis, "EnemyEtis-737");
				break;
			}
			case 19480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000650);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000680, EnemyEtis, "EnemyEtis-738");
				break;
			}
			case 19510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000651);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000681, EnemyEtis, "EnemyEtis-739");
				break;
			}
			case 19540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000652);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000682, EnemyEtis, "EnemyEtis-740");
				break;
			}
			case 19570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000653);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000683, EnemyEtis, "EnemyEtis-741");
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000654);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000684, EnemyEtis, "EnemyEtis-742");
				break;
			}
			case 19630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000655);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000685, EnemyEtis, "EnemyEtis-743");
				break;
			}
			case 19660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000656);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000686, EnemyEtis, "EnemyEtis-744");
				break;
			}
			case 19690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000657);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000687, EnemyEtis, "EnemyEtis-745");
				break;
			}
			case 19720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000658);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000688, EnemyEtis, "EnemyEtis-746");
				break;
			}
			case 19750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000659);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000689, EnemyEtis, "EnemyEtis-747");
				break;
			}
			case 19780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000660);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000690, EnemyEtis, "EnemyEtis-748");
				break;
			}
			case 19810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000661);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000691, EnemyEtis, "EnemyEtis-749");
				break;
			}
			case 19840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000662);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000692, EnemyEtis, "EnemyEtis-750");
				break;
			}
			case 19870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000663);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000693, EnemyEtis, "EnemyEtis-751");
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000664);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000694, EnemyEtis, "EnemyEtis-752");
				break;
			}
			case 19930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000665);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000695, EnemyEtis, "EnemyEtis-753");
				break;
			}
			case 19960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000666);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000696, EnemyEtis, "EnemyEtis-754");
				break;
			}
			case 19990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000667);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000697, EnemyEtis, "EnemyEtis-755");
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 20020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000668);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000698, EnemyEtis, "EnemyEtis-756");
				break;
			}
			case 20050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000669);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000699, EnemyEtis, "EnemyEtis-757");
				break;
			}
			case 20080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000670);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000700, EnemyEtis, "EnemyEtis-758");
				break;
			}
			case 20110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000671);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000701, EnemyEtis, "EnemyEtis-759");
				break;
			}
			case 20140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000672);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000702, EnemyEtis, "EnemyEtis-760");
				break;
			}
			case 20170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000673);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000703, EnemyEtis, "EnemyEtis-761");
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000674);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000704, EnemyEtis, "EnemyEtis-762");
				break;
			}
			case 20230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000675);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000705, EnemyEtis, "EnemyEtis-763");
				break;
			}
			case 20260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000676);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000706, EnemyEtis, "EnemyEtis-764");
				break;
			}
			case 20290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000677);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000707, EnemyEtis, "EnemyEtis-765");
				break;
			}
			case 20320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000678);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000708, EnemyEtis, "EnemyEtis-766");
				break;
			}
			case 20350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000679);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000709, EnemyEtis, "EnemyEtis-767");
				break;
			}
			case 20380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000680);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000710, EnemyEtis, "EnemyEtis-768");
				break;
			}
			case 20410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000681);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000711, EnemyEtis, "EnemyEtis-769");
				break;
			}
			case 20440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000682);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000712, EnemyEtis, "EnemyEtis-770");
				break;
			}
			case 20470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000683);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000713, EnemyEtis, "EnemyEtis-771");
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000684);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000714, EnemyEtis, "EnemyEtis-772");
				break;
			}
			case 20530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000685);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000715, EnemyEtis, "EnemyEtis-773");
				break;
			}
			case 20560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000686);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000716, EnemyEtis, "EnemyEtis-774");
				break;
			}
			case 20590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000687);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000717, EnemyEtis, "EnemyEtis-775");
				break;
			}
			case 20620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000688);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000718, EnemyEtis, "EnemyEtis-776");
				break;
			}
			case 20650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000689);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000719, EnemyEtis, "EnemyEtis-777");
				break;
			}
			case 20680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000690);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000720, EnemyEtis, "EnemyEtis-778");
				break;
			}
			case 20710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000691);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000721, EnemyEtis, "EnemyEtis-779");
				break;
			}
			case 20740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000692);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000722, EnemyEtis, "EnemyEtis-780");
				break;
			}
			case 20770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000693);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000723, EnemyEtis, "EnemyEtis-781");
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000694);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000724, EnemyEtis, "EnemyEtis-782");
				break;
			}
			case 20830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000695);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000725, EnemyEtis, "EnemyEtis-783");
				break;
			}
			case 20860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000696);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000726, EnemyEtis, "EnemyEtis-784");
				break;
			}
			case 20890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000697);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000727, EnemyEtis, "EnemyEtis-785");
				break;
			}
			case 20920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000698);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000728, EnemyEtis, "EnemyEtis-786");
				break;
			}
			case 20950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000699);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000729, EnemyEtis, "EnemyEtis-787");
				break;
			}
			case 20980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000700);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000730, EnemyEtis, "EnemyEtis-788");
				break;
			}
			case 21010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000701);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000731, EnemyEtis, "EnemyEtis-789");
				break;
			}
			case 21040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000702);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000732, EnemyEtis, "EnemyEtis-790");
				break;
			}
			case 21070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000703);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000733, EnemyEtis, "EnemyEtis-791");
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000704);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000734, EnemyEtis, "EnemyEtis-792");
				break;
			}
			case 21130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000705);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000735, EnemyEtis, "EnemyEtis-793");
				break;
			}
			case 21160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000706);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000736, EnemyEtis, "EnemyEtis-794");
				break;
			}
			case 21190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000707);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000737, EnemyEtis, "EnemyEtis-795");
				break;
			}
			case 21220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000708);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000738, EnemyEtis, "EnemyEtis-796");
				break;
			}
			case 21250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000709);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000739, EnemyEtis, "EnemyEtis-797");
				break;
			}
			case 21280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000710);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000740, EnemyEtis, "EnemyEtis-798");
				break;
			}
			case 21310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000711);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000741, EnemyEtis, "EnemyEtis-799");
				break;
			}
			case 21340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000712);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000742, EnemyEtis, "EnemyEtis-800");
				break;
			}
			case 21370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000713);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000743, EnemyEtis, "EnemyEtis-801");
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000714);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000744, EnemyEtis, "EnemyEtis-802");
				break;
			}
			case 21430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000715);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000745, EnemyEtis, "EnemyEtis-803");
				break;
			}
			case 21460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000716);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000746, EnemyEtis, "EnemyEtis-804");
				break;
			}
			case 21490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000717);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000747, EnemyEtis, "EnemyEtis-805");
				break;
			}
			case 21520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000718);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000748, EnemyEtis, "EnemyEtis-806");
				break;
			}
			case 21550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000719);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000749, EnemyEtis, "EnemyEtis-807");
				break;
			}
			case 21580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000720);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000750, EnemyEtis, "EnemyEtis-808");
				break;
			}
			case 21610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000721);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000751, EnemyEtis, "EnemyEtis-809");
				break;
			}
			case 21640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000722);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000752, EnemyEtis, "EnemyEtis-810");
				break;
			}
			case 21670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000723);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000753, EnemyEtis, "EnemyEtis-811");
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000724);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000754, EnemyEtis, "EnemyEtis-812");
				break;
			}
			case 21730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000725);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000755, EnemyEtis, "EnemyEtis-813");
				break;
			}
			case 21760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000726);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000756, EnemyEtis, "EnemyEtis-814");
				break;
			}
			case 21790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000727);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000757, EnemyEtis, "EnemyEtis-815");
				break;
			}
			case 21820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000728);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000758, EnemyEtis, "EnemyEtis-816");
				break;
			}
			case 21850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000729);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000759, EnemyEtis, "EnemyEtis-817");
				break;
			}
			case 21880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000730);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000760, EnemyEtis, "EnemyEtis-818");
				break;
			}
			case 21910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000731);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000761, EnemyEtis, "EnemyEtis-819");
				break;
			}
			case 21940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000732);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000762, EnemyEtis, "EnemyEtis-820");
				break;
			}
			case 21970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000733);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000763, EnemyEtis, "EnemyEtis-821");
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000734);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000764, EnemyEtis, "EnemyEtis-822");
				break;
			}
			case 22030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000735);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000765, EnemyEtis, "EnemyEtis-823");
				break;
			}
			case 22060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000736);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000766, EnemyEtis, "EnemyEtis-824");
				break;
			}
			case 22090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000737);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000767, EnemyEtis, "EnemyEtis-825");
				break;
			}
			case 22120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000738);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000768, EnemyEtis, "EnemyEtis-826");
				break;
			}
			case 22150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000739);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000769, EnemyEtis, "EnemyEtis-827");
				break;
			}
			case 22180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000740);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000770, EnemyEtis, "EnemyEtis-828");
				break;
			}
			case 22210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000741);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000771, EnemyEtis, "EnemyEtis-829");
				break;
			}
			case 22240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000742);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000772, EnemyEtis, "EnemyEtis-830");
				break;
			}
			case 22270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000743);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000773, EnemyEtis, "EnemyEtis-831");
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000744);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000774, EnemyEtis, "EnemyEtis-832");
				break;
			}
			case 22330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000745);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000775, EnemyEtis, "EnemyEtis-833");
				break;
			}
			case 22360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000746);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000776, EnemyEtis, "EnemyEtis-834");
				break;
			}
			case 22390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000747);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000777, EnemyEtis, "EnemyEtis-835");
				break;
			}
			case 22420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000748);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000778, EnemyEtis, "EnemyEtis-836");
				break;
			}
			case 22450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000749);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000779, EnemyEtis, "EnemyEtis-837");
				break;
			}
			case 22480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000750);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000780, EnemyEtis, "EnemyEtis-838");
				break;
			}
			case 22510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000751);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000781, EnemyEtis, "EnemyEtis-839");
				break;
			}
			case 22540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000752);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000782, EnemyEtis, "EnemyEtis-840");
				break;
			}
			case 22570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000753);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000783, EnemyEtis, "EnemyEtis-841");
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000754);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000784, EnemyEtis, "EnemyEtis-842");
				break;
			}
			case 22630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000755);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000785, EnemyEtis, "EnemyEtis-843");
				break;
			}
			case 22660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000756);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000786, EnemyEtis, "EnemyEtis-844");
				break;
			}
			case 22690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000757);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000787, EnemyEtis, "EnemyEtis-845");
				break;
			}
			case 22720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000758);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000788, EnemyEtis, "EnemyEtis-846");
				break;
			}
			case 22750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000759);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000789, EnemyEtis, "EnemyEtis-847");
				break;
			}
			case 22780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000760);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000790, EnemyEtis, "EnemyEtis-848");
				break;
			}
			case 22810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000761);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000791, EnemyEtis, "EnemyEtis-849");
				break;
			}
			case 22840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000762);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000792, EnemyEtis, "EnemyEtis-850");
				break;
			}
			case 22870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000763);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000793, EnemyEtis, "EnemyEtis-851");
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000764);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000794, EnemyEtis, "EnemyEtis-852");
				break;
			}
			case 22930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000765);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000795, EnemyEtis, "EnemyEtis-853");
				break;
			}
			case 22960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000766);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000796, EnemyEtis, "EnemyEtis-854");
				break;
			}
			case 22990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000767);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000797, EnemyEtis, "EnemyEtis-855");
				break;
			}
			case 23020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000768);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000798, EnemyEtis, "EnemyEtis-856");
				break;
			}
			case 23050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000769);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000799, EnemyEtis, "EnemyEtis-857");
				break;
			}
			case 23080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000770);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000800, EnemyEtis, "EnemyEtis-858");
				break;
			}
			case 23110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000771);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000801, EnemyEtis, "EnemyEtis-859");
				break;
			}
			case 23140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000772);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000802, EnemyEtis, "EnemyEtis-860");
				break;
			}
			case 23170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000773);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000803, EnemyEtis, "EnemyEtis-861");
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000774);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000804, EnemyEtis, "EnemyEtis-862");
				break;
			}
			case 23230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000775);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000805, EnemyEtis, "EnemyEtis-863");
				break;
			}
			case 23260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000776);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000806, EnemyEtis, "EnemyEtis-864");
				break;
			}
			case 23290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000777);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000807, EnemyEtis, "EnemyEtis-865");
				break;
			}
			case 23320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000778);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000808, EnemyEtis, "EnemyEtis-866");
				break;
			}
			case 23350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000779);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000809, EnemyEtis, "EnemyEtis-867");
				break;
			}
			case 23380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000780);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000810, EnemyEtis, "EnemyEtis-868");
				break;
			}
			case 23410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000781);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000811, EnemyEtis, "EnemyEtis-869");
				break;
			}
			case 23440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000782);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000812, EnemyEtis, "EnemyEtis-870");
				break;
			}
			case 23470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000783);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000813, EnemyEtis, "EnemyEtis-871");
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000784);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000814, EnemyEtis, "EnemyEtis-872");
				break;
			}
			case 23530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000785);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000815, EnemyEtis, "EnemyEtis-873");
				break;
			}
			case 23560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000786);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000816, EnemyEtis, "EnemyEtis-874");
				break;
			}
			case 23590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000787);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000817, EnemyEtis, "EnemyEtis-875");
				break;
			}
			case 23620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000788);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000818, EnemyEtis, "EnemyEtis-876");
				break;
			}
			case 23650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000789);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000819, EnemyEtis, "EnemyEtis-877");
				break;
			}
			case 23680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000790);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000820, EnemyEtis, "EnemyEtis-878");
				break;
			}
			case 23710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000791);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000821, EnemyEtis, "EnemyEtis-879");
				break;
			}
			case 23740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000792);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000822, EnemyEtis, "EnemyEtis-880");
				break;
			}
			case 23770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000793);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000823, EnemyEtis, "EnemyEtis-881");
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000794);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000824, EnemyEtis, "EnemyEtis-882");
				break;
			}
			case 23830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000795);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000825, EnemyEtis, "EnemyEtis-883");
				break;
			}
			case 23860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000796);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000826, EnemyEtis, "EnemyEtis-884");
				break;
			}
			case 23890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000797);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000827, EnemyEtis, "EnemyEtis-885");
				break;
			}
			case 23920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000798);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000828, EnemyEtis, "EnemyEtis-886");
				break;
			}
			case 23950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000799);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000829, EnemyEtis, "EnemyEtis-887");
				break;
			}
			case 23980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000800);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000830, EnemyEtis, "EnemyEtis-888");
				break;
			}
			case 24010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000801);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000831, EnemyEtis, "EnemyEtis-889");
				break;
			}
			case 24040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000802);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000832, EnemyEtis, "EnemyEtis-890");
				break;
			}
			case 24070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000803);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000833, EnemyEtis, "EnemyEtis-891");
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000804);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000834, EnemyEtis, "EnemyEtis-892");
				break;
			}
			case 24130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000805);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000835, EnemyEtis, "EnemyEtis-893");
				break;
			}
			case 24160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000806);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000836, EnemyEtis, "EnemyEtis-894");
				break;
			}
			case 24190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000807);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000837, EnemyEtis, "EnemyEtis-895");
				break;
			}
			case 24220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000808);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000838, EnemyEtis, "EnemyEtis-896");
				break;
			}
			case 24250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000809);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000839, EnemyEtis, "EnemyEtis-897");
				break;
			}
			case 24280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000810);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000840, EnemyEtis, "EnemyEtis-898");
				break;
			}
			case 24310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000811);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000841, EnemyEtis, "EnemyEtis-899");
				break;
			}
			case 24340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000812);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000842, EnemyEtis, "EnemyEtis-900");
				break;
			}
			case 24370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000813);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000843, EnemyEtis, "EnemyEtis-901");
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000814);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000844, EnemyEtis, "EnemyEtis-902");
				break;
			}
			case 24430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000815);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000845, EnemyEtis, "EnemyEtis-903");
				break;
			}
			case 24460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000816);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000846, EnemyEtis, "EnemyEtis-904");
				break;
			}
			case 24490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000817);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000847, EnemyEtis, "EnemyEtis-905");
				break;
			}
			case 24520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000818);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000848, EnemyEtis, "EnemyEtis-906");
				break;
			}
			case 24550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000819);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000849, EnemyEtis, "EnemyEtis-907");
				break;
			}
			case 24580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000820);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000850, EnemyEtis, "EnemyEtis-908");
				break;
			}
			case 24610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000821);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000851, EnemyEtis, "EnemyEtis-909");
				break;
			}
			case 24640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000822);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000852, EnemyEtis, "EnemyEtis-910");
				break;
			}
			case 24670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000823);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000853, EnemyEtis, "EnemyEtis-911");
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000824);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000854, EnemyEtis, "EnemyEtis-912");
				break;
			}
			case 24730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000825);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000855, EnemyEtis, "EnemyEtis-913");
				break;
			}
			case 24760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000826);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000856, EnemyEtis, "EnemyEtis-914");
				break;
			}
			case 24790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000827);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000857, EnemyEtis, "EnemyEtis-915");
				break;
			}
			case 24820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000828);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000858, EnemyEtis, "EnemyEtis-916");
				break;
			}
			case 24850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000829);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000859, EnemyEtis, "EnemyEtis-917");
				break;
			}
			case 24880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000830);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000860, EnemyEtis, "EnemyEtis-918");
				break;
			}
			case 24910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000831);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000861, EnemyEtis, "EnemyEtis-919");
				break;
			}
			case 24940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000832);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000862, EnemyEtis, "EnemyEtis-920");
				break;
			}
			case 24970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000833);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000863, EnemyEtis, "EnemyEtis-921");
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000834);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000864, EnemyEtis, "EnemyEtis-922");
				break;
			}
			case 25030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000835);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000865, EnemyEtis, "EnemyEtis-923");
				break;
			}
			case 25060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000836);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000866, EnemyEtis, "EnemyEtis-924");
				break;
			}
			case 25090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000837);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000867, EnemyEtis, "EnemyEtis-925");
				break;
			}
			case 25120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000838);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000868, EnemyEtis, "EnemyEtis-926");
				break;
			}
			case 25150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000839);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000869, EnemyEtis, "EnemyEtis-927");
				break;
			}
			case 25180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000840);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000870, EnemyEtis, "EnemyEtis-928");
				break;
			}
			case 25210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000841);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000871, EnemyEtis, "EnemyEtis-929");
				break;
			}
			case 25240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000842);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000872, EnemyEtis, "EnemyEtis-930");
				break;
			}
			case 25270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000843);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000873, EnemyEtis, "EnemyEtis-931");
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000844);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000874, EnemyEtis, "EnemyEtis-932");
				break;
			}
			case 25330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000845);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000875, EnemyEtis, "EnemyEtis-933");
				break;
			}
			case 25360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000846);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000876, EnemyEtis, "EnemyEtis-934");
				break;
			}
			case 25390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000847);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000877, EnemyEtis, "EnemyEtis-935");
				break;
			}
			case 25420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000848);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000878, EnemyEtis, "EnemyEtis-936");
				break;
			}
			case 25450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000849);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000879, EnemyEtis, "EnemyEtis-937");
				break;
			}
			case 25480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000850);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000880, EnemyEtis, "EnemyEtis-938");
				break;
			}
			case 25510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000851);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000881, EnemyEtis, "EnemyEtis-939");
				break;
			}
			case 25540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000852);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000882, EnemyEtis, "EnemyEtis-940");
				break;
			}
			case 25570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000853);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000883, EnemyEtis, "EnemyEtis-941");
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000854);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000884, EnemyEtis, "EnemyEtis-942");
				break;
			}
			case 25630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000855);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000885, EnemyEtis, "EnemyEtis-943");
				break;
			}
			case 25660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000856);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000886, EnemyEtis, "EnemyEtis-944");
				break;
			}
			case 25690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000857);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000887, EnemyEtis, "EnemyEtis-945");
				break;
			}
			case 25720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000858);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000888, EnemyEtis, "EnemyEtis-946");
				break;
			}
			case 25750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000859);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000889, EnemyEtis, "EnemyEtis-947");
				break;
			}
			case 25780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000860);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000890, EnemyEtis, "EnemyEtis-948");
				break;
			}
			case 25810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000861);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000891, EnemyEtis, "EnemyEtis-949");
				break;
			}
			case 25840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000862);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000892, EnemyEtis, "EnemyEtis-950");
				break;
			}
			case 25870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000863);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000893, EnemyEtis, "EnemyEtis-951");
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000864);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000894, EnemyEtis, "EnemyEtis-952");
				break;
			}
			case 25930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000865);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000895, EnemyEtis, "EnemyEtis-953");
				break;
			}
			case 25960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000866);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000896, EnemyEtis, "EnemyEtis-954");
				break;
			}
			case 25990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000867);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000897, EnemyEtis, "EnemyEtis-955");
				break;
			}
			case 26020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000868);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000898, EnemyEtis, "EnemyEtis-956");
				break;
			}
			case 26050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000869);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000899, EnemyEtis, "EnemyEtis-957");
				break;
			}
			case 26080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000870);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000900, EnemyEtis, "EnemyEtis-958");
				break;
			}
			case 26110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000871);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000901, EnemyEtis, "EnemyEtis-959");
				break;
			}
			case 26140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000872);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000902, EnemyEtis, "EnemyEtis-960");
				break;
			}
			case 26170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000873);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000903, EnemyEtis, "EnemyEtis-961");
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000874);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000904, EnemyEtis, "EnemyEtis-962");
				break;
			}
			case 26230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000875);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000905, EnemyEtis, "EnemyEtis-963");
				break;
			}
			case 26260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000876);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000906, EnemyEtis, "EnemyEtis-964");
				break;
			}
			case 26290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000877);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000907, EnemyEtis, "EnemyEtis-965");
				break;
			}
			case 26320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000878);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000908, EnemyEtis, "EnemyEtis-966");
				break;
			}
			case 26350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000879);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000909, EnemyEtis, "EnemyEtis-967");
				break;
			}
			case 26380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000880);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000910, EnemyEtis, "EnemyEtis-968");
				break;
			}
			case 26410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000881);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000911, EnemyEtis, "EnemyEtis-969");
				break;
			}
			case 26440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000882);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000912, EnemyEtis, "EnemyEtis-970");
				break;
			}
			case 26470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000883);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000913, EnemyEtis, "EnemyEtis-971");
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000884);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000914, EnemyEtis, "EnemyEtis-972");
				break;
			}
			case 26530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000885);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000915, EnemyEtis, "EnemyEtis-973");
				break;
			}
			case 26560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000886);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000916, EnemyEtis, "EnemyEtis-974");
				break;
			}
			case 26590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000887);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000917, EnemyEtis, "EnemyEtis-975");
				break;
			}
			case 26620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000888);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000918, EnemyEtis, "EnemyEtis-976");
				break;
			}
			case 26650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000889);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000919, EnemyEtis, "EnemyEtis-977");
				break;
			}
			case 26680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000890);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000920, EnemyEtis, "EnemyEtis-978");
				break;
			}
			case 26710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000891);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000921, EnemyEtis, "EnemyEtis-979");
				break;
			}
			case 26740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000892);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000922, EnemyEtis, "EnemyEtis-980");
				break;
			}
			case 26770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000893);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000923, EnemyEtis, "EnemyEtis-981");
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000894);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000924, EnemyEtis, "EnemyEtis-982");
				break;
			}
			case 26830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000895);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000925, EnemyEtis, "EnemyEtis-983");
				break;
			}
			case 26860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000896);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000926, EnemyEtis, "EnemyEtis-984");
				break;
			}
			case 26890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000897);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000927, EnemyEtis, "EnemyEtis-985");
				break;
			}
			case 26920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000898);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000928, EnemyEtis, "EnemyEtis-986");
				break;
			}
			case 26950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000899);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000929, EnemyEtis, "EnemyEtis-987");
				break;
			}
			case 26980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000900);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000930, EnemyEtis, "EnemyEtis-988");
				break;
			}
			case 27010: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000901);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000931, EnemyEtis, "EnemyEtis-989");
				break;
			}
			case 27040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000902);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000932, EnemyEtis, "EnemyEtis-990");
				break;
			}
			case 27070: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000903);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000933, EnemyEtis, "EnemyEtis-991");
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000904);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000934, EnemyEtis, "EnemyEtis-992");
				break;
			}
			case 27130: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000905);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000935, EnemyEtis, "EnemyEtis-993");
				break;
			}
			case 27160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000906);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000936, EnemyEtis, "EnemyEtis-994");
				break;
			}
			case 27190: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000907);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000937, EnemyEtis, "EnemyEtis-995");
				break;
			}
			case 27220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000908);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000938, EnemyEtis, "EnemyEtis-996");
				break;
			}
			case 27250: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000909);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000939, EnemyEtis, "EnemyEtis-997");
				break;
			}
			case 27280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000910);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000940, EnemyEtis, "EnemyEtis-998");
				break;
			}
			case 27310: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000911);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000941, EnemyEtis, "EnemyEtis-999");
				break;
			}
			case 27340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000912);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000942, EnemyEtis, "EnemyEtis-1000");
				break;
			}
			case 27370: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000913);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000943, EnemyEtis, "EnemyEtis-1001");
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000914);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000944, EnemyEtis, "EnemyEtis-1002");
				break;
			}
			case 27430: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000915);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000945, EnemyEtis, "EnemyEtis-1003");
				break;
			}
			case 27460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000916);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000946, EnemyEtis, "EnemyEtis-1004");
				break;
			}
			case 27490: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000917);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000947, EnemyEtis, "EnemyEtis-1005");
				break;
			}
			case 27520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000918);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000948, EnemyEtis, "EnemyEtis-1006");
				break;
			}
			case 27550: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000919);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000949, EnemyEtis, "EnemyEtis-1007");
				break;
			}
			case 27580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000920);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000950, EnemyEtis, "EnemyEtis-1008");
				break;
			}
			case 27610: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000921);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000951, EnemyEtis, "EnemyEtis-1009");
				break;
			}
			case 27640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000922);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000952, EnemyEtis, "EnemyEtis-1010");
				break;
			}
			case 27670: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000923);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000953, EnemyEtis, "EnemyEtis-1011");
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000924);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000954, EnemyEtis, "EnemyEtis-1012");
				break;
			}
			case 27730: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000925);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000955, EnemyEtis, "EnemyEtis-1013");
				break;
			}
			case 27760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000926);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000956, EnemyEtis, "EnemyEtis-1014");
				break;
			}
			case 27790: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000927);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000957, EnemyEtis, "EnemyEtis-1015");
				break;
			}
			case 27820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000928);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000958, EnemyEtis, "EnemyEtis-1016");
				break;
			}
			case 27850: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000929);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000959, EnemyEtis, "EnemyEtis-1017");
				break;
			}
			case 27880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000930);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000960, EnemyEtis, "EnemyEtis-1018");
				break;
			}
			case 27910: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000931);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000961, EnemyEtis, "EnemyEtis-1019");
				break;
			}
			case 27940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000932);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000962, EnemyEtis, "EnemyEtis-1020");
				break;
			}
			case 27970: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000933);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000963, EnemyEtis, "EnemyEtis-1021");
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000934);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000964, EnemyEtis, "EnemyEtis-1022");
				break;
			}
			case 28030: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000935);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000965, EnemyEtis, "EnemyEtis-1023");
				break;
			}
			case 28060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000936);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000966, EnemyEtis, "EnemyEtis-1024");
				break;
			}
			case 28090: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000937);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000967, EnemyEtis, "EnemyEtis-1025");
				break;
			}
			case 28120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000938);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000968, EnemyEtis, "EnemyEtis-1026");
				break;
			}
			case 28150: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000939);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000969, EnemyEtis, "EnemyEtis-1027");
				break;
			}
			case 28180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000940);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000970, EnemyEtis, "EnemyEtis-1028");
				break;
			}
			case 28210: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000941);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000971, EnemyEtis, "EnemyEtis-1029");
				break;
			}
			case 28240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000942);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000972, EnemyEtis, "EnemyEtis-1030");
				break;
			}
			case 28270: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000943);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000973, EnemyEtis, "EnemyEtis-1031");
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000944);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000974, EnemyEtis, "EnemyEtis-1032");
				break;
			}
			case 28330: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000945);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000975, EnemyEtis, "EnemyEtis-1033");
				break;
			}
			case 28360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000946);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000976, EnemyEtis, "EnemyEtis-1034");
				break;
			}
			case 28390: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000947);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000977, EnemyEtis, "EnemyEtis-1035");
				break;
			}
			case 28420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000948);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000978, EnemyEtis, "EnemyEtis-1036");
				break;
			}
			case 28450: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000949);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000979, EnemyEtis, "EnemyEtis-1037");
				break;
			}
			case 28480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000950);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000980, EnemyEtis, "EnemyEtis-1038");
				break;
			}
			case 28510: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000951);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000981, EnemyEtis, "EnemyEtis-1039");
				break;
			}
			case 28540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000952);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000982, EnemyEtis, "EnemyEtis-1040");
				break;
			}
			case 28570: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000953);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000983, EnemyEtis, "EnemyEtis-1041");
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000954);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000984, EnemyEtis, "EnemyEtis-1042");
				break;
			}
			case 28630: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000955);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000985, EnemyEtis, "EnemyEtis-1043");
				break;
			}
			case 28660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000956);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000986, EnemyEtis, "EnemyEtis-1044");
				break;
			}
			case 28690: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000957);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000987, EnemyEtis, "EnemyEtis-1045");
				break;
			}
			case 28720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000958);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000988, EnemyEtis, "EnemyEtis-1046");
				break;
			}
			case 28750: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000959);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000989, EnemyEtis, "EnemyEtis-1047");
				break;
			}
			case 28780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000960);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000990, EnemyEtis, "EnemyEtis-1048");
				break;
			}
			case 28810: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000961);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000991, EnemyEtis, "EnemyEtis-1049");
				break;
			}
			case 28840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000962);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000992, EnemyEtis, "EnemyEtis-1050");
				break;
			}
			case 28870: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000963);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000993, EnemyEtis, "EnemyEtis-1051");
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000964);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000994, EnemyEtis, "EnemyEtis-1052");
				break;
			}
			case 28930: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000965);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000995, EnemyEtis, "EnemyEtis-1053");
				break;
			}
			case 28960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000966);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000996, EnemyEtis, "EnemyEtis-1054");
				break;
			}
			case 28990: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000967);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000997, EnemyEtis, "EnemyEtis-1055");
				break;
			}
			case 29020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000968);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000998, EnemyEtis, "EnemyEtis-1056");
				break;
			}
			case 29050: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000969);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10000999, EnemyEtis, "EnemyEtis-1057");
				break;
			}
			case 29080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000970);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(10001000, EnemyEtis, "EnemyEtis-1058");
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-1059");
				break;
			}
			case 29110: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000971);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000972);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29170: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000973);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000974);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29230: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000975);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000976);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29290: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000977);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000978);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29350: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000979);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000980);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29410: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000981);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000982);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29470: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000983);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000984);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29530: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000985);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000986);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29590: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000987);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000988);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29650: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000989);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000990);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29710: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000991);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000992);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29770: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000993);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000994);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29830: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000995);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000996);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29890: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000997);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000998);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29950: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10000999);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 29980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(10001000);
				getSceneDirector()->addSubGroup(pEtis);
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
		_cnt_event = (_cnt_event < 1021-1 ? _cnt_event+1 : _cnt_event);
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
