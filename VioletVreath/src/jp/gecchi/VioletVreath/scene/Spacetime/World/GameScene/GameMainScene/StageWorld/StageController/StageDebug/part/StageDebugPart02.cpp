#include "StageDebugPart02.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/RotateFormationScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

StageDebugPart02::StageDebugPart02(const char* prm_name) :
        StageDebugPart<GgafLib::DefaultScene>(prm_name, EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
    _class_name = "StageDebugPart02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1700,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2100,2110,2140,2170,2200,2230,2260,2290,2300,2320,2350,2380,2400,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2700,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3000,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4120,4150,4180,4210,4240,4270,4300,4330,4360,4390,4400,4420,4450,4480,4510,4540,4570,4600,4630,4660,4690,4720,4750,4780,4810,4840,4870,4900,4930,4960,4990,5000,5020,5050,5080,5110,5140,5170,5200,5230,5260,5290,5320,5350,5380,5400,5410,5440,5470,5500,5530,5560,5590,5620,5650,5680,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6000,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7400,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8000,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8400,8410,8440,8470,8500,8530,8560,8590,8600,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8900,8920,8950,8980,9000,9010,9040,9070,9100,9130,9160,9190,9200,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9500,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10030,10060,10090,10120,10150,10180,10210,10240,10270,10300,10330,10360,10390,10420,10450,10480,10510,10540,10570,10600,10630,10660,10690,10720,10750,10780,10810,10840,10870,10900,10930,10960,10990,11020,11050,11080,11110,11140,11170,11200,11230,11260,11290,11320,11350,11380,11410,11440,11470,11500,11530,11560,11590,11620,11650,11680,11710,11740,11770,11800,11830,11860,11890,11920,11950,11980,12010,12040,12070,12100,12130,12160,12190,12220,12250,12280,12310,12340,12370,12400,12430,12460,12490,12520,12550,12580,12610,12640,12670,12700,12730,12760,12790,12820,12850,12880,12910,12940,12970,13000,13030,13060,13090,13120,13150,13180,13210,13240,13270,13300,13330,13360,13390,13420,13450,13480,13510,13540,13570,13600,13630,13660,13690,13720,13750,13780,13810,13840,13870,13900,13930,13960,13990,14020,14050,14080,14110,14140,14170,14200,14230,14260,14290,14320,14350,14380,14410,14440,14470,14500,14530,14560,14590,14620,14650,14680,14710,14740,14770,14800,14830,14860,14890,14920,14950,14980,15010,15040,15070,15100,15130,15160,15190,15220,15250,15280,15310,15340,15370,15400,15430,15460,15490,15520,15550,15580,15610,15640,15670,15700,15730,15760,15790,15820,15850,15880,15910,15940,15970,16000,16030,16060,16090,16120,16150,16180,16210,16240,16270,16300,16330,16360,16390,16420,16450,16480,16510,16540,16570,16600,16630,16660,16690,16720,16750,16780,16810,16840,16870,16900,16930,16960,16990,17020,17050,17080,17110,17140,17170,17200,17230,17260,17290,17320,17350,17380,17410,17440,17470,17500,17530,17560,17590,17620,17650,17680,17710,17740,17770,17800,17830,17860,17890,17920,17950,17980,18010,18040,18070,18100,18130,18160,18190,18220,18250,18280,18310,18340,18370,18400,18430,18460,18490,18520,18550,18580,18610,18640,18670,18700,18730,18760,18790,18820,18850,18880,18910,18940,18970,19000,19030,19060,19090,19120,19150,19180,19210,19240,19270,19300,19330,19360,19390,19420,19450,19480,19510,19540,19570,19600,19630,19660,19690,19720,19750,19780,19810,19840,19870,19900,19930,19960,19990,20020,20050,20080,20110,20140,20170,20200,20230,20260,20290,20320,20350,20380,20410,20440,20470,20500,20530,20560,20590,20620,20650,20680,20710,20740,20770,20800,20830,20860,20890,20920,20950,20980,21010,21040,21070,21100,21130,21160,21190,21220,21250,21280,21310,21340,21370,21400,21430,21460,21490,21520,21550,21580,21610,21640,21670,21700,21730,21760,21790,21820,21850,21880,21910,21940,21970,22000,22030,22060,22090,22120,22150,22180,22210,22240,22270,22300,22330,22360,22390,22420,22450,22480,22510,22540,22570,22600,22630,22660,22690,22720,22750,22780,22810,22840,22870,22900,22930,22960,22990,23020,23050,23080,23110,23140,23170,23200,23230,23260,23290,23320,23350,23380,23410,23440,23470,23500,23530,23560,23590,23620,23650,23680,23710,23740,23770,23800,23830,23860,23890,23920,23950,23980,24010,24040,24070,24100,24130,24160,24190,24220,24250,24280,24310,24340,24370,24400,24430,24460,24490,24520,24550,24580,24610,24640,24670,24700,24730,24760,24790,24820,24850,24880,24910,24940,24970,25000,25030,25060,25090,25120,25150,25180,25210,25240,25270,25300,25330,25360,25390,25420,25450,25480,25510,25540,25570,25600,25630,25660,25690,25720,25750,25780,25810,25840,25870,25900,25930,25960,25990,26020,26050,26080,26110,26140,26170,26200,26230,26260,26290,26320,26350,26380,26410,26440,26470,26500,26530,26560,26590,26620,26650,26680,26710,26740,26770,26800,26830,26860,26890,26920,26950,26980,27010,27040,27070,27100,27130,27160,27190,27220,27250,27280,27310,27340,27370,27400,27430,27460,27490,27520,27550,27580,27610,27640,27670,27700,27730,27760,27790,27820,27850,27880,27910,27940,27970,28000,28030,28060,28090,28120,28150,28180,28210,28240,28270,28300,28330,28360,28390,28420,28450,28480,28510,28540,28570,28600,28630,28660,28690,28720,28750,28780,28810,28840,28870,28900,28930,28960,28990,29020,29050,29080,29110,29140,29170,29200,29230,29260,29290,29320,29350,29380,29410,29440,29470,29500,29530,29560,29590,29620,29650,29680,29710,29740,29770,29800,29830,29860,29890,29920,29950,29980};
	_paFrame_NextEvent = new frame[1019];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1019;
	requestActor(30000000, EnemyEtis);
	requestActor(30000001, EnemyEtis);
	requestActor(30000002, EnemyEtis);
	requestActor(30000003, EnemyEtis);
	requestActor(30000004, EnemyEtis);
	requestActor(30000005, EnemyEtis);
	requestActor(30000006, EnemyEtis);
	requestActor(30000007, EnemyEtis);
	requestActor(30000008, EnemyEtis);
	requestActor(30000009, EnemyEtis);
	requestActor(30000010, EnemyEtis);
	requestActor(30000011, EnemyEtis);
	requestActor(30000012, EnemyEtis);
	requestActor(30000013, EnemyEtis);
	requestActor(30000014, EnemyEtis);
	requestActor(30000015, EnemyEtis);
	requestActor(30000016, EnemyEtis);
    // gen01 end

    getBgmConductor()->ready(0, "BGM_01_02");
}

void StageDebugPart02::initialize() {

}

void StageDebugPart02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 10: {
				requestActor(30000017, EnemyEtis);
				break;
			}
			case 40: {
				requestActor(30000018, EnemyEtis);
				break;
			}
			case 70: {
				requestActor(30000019, EnemyEtis);
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000000);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000020, EnemyEtis);
				break;
			}
			case 130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000001);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000021, EnemyEtis);
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000002);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000022, EnemyEtis);
				break;
			}
			case 190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000003);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000023, EnemyEtis);
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000004);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000024, EnemyEtis);
				break;
			}
			case 250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000005);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000025, EnemyEtis);
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000006);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000026, EnemyEtis);
				break;
			}
			case 310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000007);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000027, EnemyEtis);
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000008);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000028, EnemyEtis);
				break;
			}
			case 370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000009);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000029, EnemyEtis);
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000010);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000030, EnemyEtis);
				requestActor(30000997, VarietyRatislavia001);
				requestActor(30001014, FormationHalia);
				requestActor(30001025, FormationEbe001);
				break;
			}
			case 430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000011);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000031, EnemyEtis);
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000012);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000032, EnemyEtis);
				break;
			}
			case 490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000013);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000033, EnemyEtis);
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000014);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000034, EnemyEtis);
				break;
			}
			case 550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000015);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000035, EnemyEtis);
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000016);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000036, EnemyEtis);
				break;
			}
			case 610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000017);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000037, EnemyEtis);
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000018);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000038, EnemyEtis);
				break;
			}
			case 670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000019);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000039, EnemyEtis);
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000020);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000040, EnemyEtis);
				break;
			}
			case 730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000021);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000041, EnemyEtis);
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000022);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000042, EnemyEtis);
				break;
			}
			case 790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000023);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000043, EnemyEtis);
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000024);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000044, EnemyEtis);
				break;
			}
			case 850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000025);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000045, EnemyEtis);
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000026);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000046, EnemyEtis);
				break;
			}
			case 910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000027);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000047, EnemyEtis);
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000028);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000048, EnemyEtis);
				break;
			}
			case 970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000029);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000049, EnemyEtis);
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000030);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000050, EnemyEtis);
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)receiveActor(30000997);
				getSceneChief()->appendGroupChild(pRatislavia);
				FormationHalia* pF = (FormationHalia*)receiveActor(30001014);
				getSceneChief()->appendGroupChild(pF);
				FormationEbe001* pF1 = (FormationEbe001*)receiveActor(30001025);
				getSceneChief()->appendGroupChild(pF1);
				break;
			}
			case 1030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000031);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000051, EnemyEtis);
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000032);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000052, EnemyEtis);
				break;
			}
			case 1090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000033);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000053, EnemyEtis);
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000034);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000054, EnemyEtis);
				break;
			}
			case 1150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000035);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000055, EnemyEtis);
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000036);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000056, EnemyEtis);
				break;
			}
			case 1210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000037);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000057, EnemyEtis);
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000038);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000058, EnemyEtis);
				break;
			}
			case 1270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000039);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000059, EnemyEtis);
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000040);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000060, EnemyEtis);
				break;
			}
			case 1330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000041);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000061, EnemyEtis);
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000042);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000062, EnemyEtis);
				break;
			}
			case 1390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000043);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000063, EnemyEtis);
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000044);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000064, EnemyEtis);
				break;
			}
			case 1450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000045);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000065, EnemyEtis);
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000046);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000066, EnemyEtis);
				break;
			}
			case 1510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000047);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000067, EnemyEtis);
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000048);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000068, EnemyEtis);
				break;
			}
			case 1570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000049);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000069, EnemyEtis);
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000050);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000070, EnemyEtis);
				break;
			}
			case 1630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000051);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000071, EnemyEtis);
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000052);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000072, EnemyEtis);
				break;
			}
			case 1690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000053);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000073, EnemyEtis);
				break;
			}
			case 1700: {
				requestActor(30000998, EnemyStraea);
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000054);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000074, EnemyEtis);
				break;
			}
			case 1750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000055);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000075, EnemyEtis);
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000056);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000076, EnemyEtis);
				break;
			}
			case 1810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000057);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000077, EnemyEtis);
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000058);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000078, EnemyEtis);
				break;
			}
			case 1870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000059);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000079, EnemyEtis);
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000060);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000080, EnemyEtis);
				requestActor(30000999, FormationEmilia);
				break;
			}
			case 1930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000061);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000081, EnemyEtis);
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000062);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000082, EnemyEtis);
				break;
			}
			case 1990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000063);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000083, EnemyEtis);
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000064);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000084, EnemyEtis);
				break;
			}
			case 2050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000065);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000085, EnemyEtis);
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000066);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000086, EnemyEtis);
				break;
			}
			case 2100: {
				requestActor(30001001, FormationAllas001a);
				requestActor(30001002, FormationAllas001b);
				requestActor(30001003, FormationAllas001c);
				requestActor(30001004, FormationAllas001d);
				requestActor(30001005, FormationAllas001a);
				requestActor(30001006, FormationAllas001d);
				requestActor(30001007, FormationAllas001b);
				requestActor(30001008, FormationAllas001c);
				requestActor(30001009, FormationAllas001a);
				requestActor(30001010, FormationAllas001d);
				requestActor(30001011, FormationAllas001b);
				requestActor(30001012, FormationAllas001c);
				break;
			}
			case 2110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000067);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000087, EnemyEtis);
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000068);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000088, EnemyEtis);
				break;
			}
			case 2170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000069);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000089, EnemyEtis);
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000070);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000090, EnemyEtis);
				break;
			}
			case 2230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000071);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000091, EnemyEtis);
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000072);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000092, EnemyEtis);
				break;
			}
			case 2290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000073);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000093, EnemyEtis);
				break;
			}
			case 2300: {
				EnemyStraea* pStraea2 = (EnemyStraea*)receiveActor(30000998);
				getSceneChief()->appendGroupChild(pStraea2);
				pStraea2->_z = 1800000;
				pStraea2->_y = -100000;
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000074);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000094, EnemyEtis);
				break;
			}
			case 2350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000075);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000095, EnemyEtis);
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000076);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000096, EnemyEtis);
				break;
			}
			case 2400: {
				requestActor(30001013, FormationGeria001);
				break;
			}
			case 2410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000077);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000097, EnemyEtis);
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000078);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000098, EnemyEtis);
				break;
			}
			case 2470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000079);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000099, EnemyEtis);
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000080);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000100, EnemyEtis);
				FormationEmilia* pFormationEmilia = (FormationEmilia*)receiveActor(30000999);
				getSceneChief()->appendGroupChild(pFormationEmilia);
				break;
			}
			case 2530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000081);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000101, EnemyEtis);
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000082);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000102, EnemyEtis);
				break;
			}
			case 2590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000083);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000103, EnemyEtis);
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000084);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000104, EnemyEtis);
				break;
			}
			case 2650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000085);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000105, EnemyEtis);
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000086);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000106, EnemyEtis);
				break;
			}
			case 2700: {
				{
				RotateFormationScene* ta = NEW RotateFormationScene("RotateFormationScene-2");
				ta->setMaxPerformFrame(2500);
				appendChild(ta);
				ta->addFormation(((FormationAllas001a*)receiveActor(30001001)), 400);
				ta->addFormation(((FormationAllas001b*)receiveActor(30001002)), 400);
				ta->addFormation(((FormationAllas001c*)receiveActor(30001003)), 400);
				ta->addFormation(((FormationAllas001d*)receiveActor(30001004)), 400);
				ta->addFormation(((FormationAllas001a*)receiveActor(30001005)), 1);
				ta->addFormation(((FormationAllas001d*)receiveActor(30001006)), 400);
				ta->addFormation(((FormationAllas001b*)receiveActor(30001007)), 1);
				ta->addFormation(((FormationAllas001c*)receiveActor(30001008)), 400);
				ta->addFormation(((FormationAllas001a*)receiveActor(30001009)), 1);
				ta->addFormation(((FormationAllas001d*)receiveActor(30001010)), 1);
				ta->addFormation(((FormationAllas001b*)receiveActor(30001011)), 1);
				ta->addFormation(((FormationAllas001c*)receiveActor(30001012)), 400);
				}
				break;
			}
			case 2710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000087);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000107, EnemyEtis);
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000088);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000108, EnemyEtis);
				break;
			}
			case 2770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000089);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000109, EnemyEtis);
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000090);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000110, EnemyEtis);
				break;
			}
			case 2830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000091);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000111, EnemyEtis);
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000092);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000112, EnemyEtis);
				break;
			}
			case 2890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000093);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000113, EnemyEtis);
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000094);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000114, EnemyEtis);
				break;
			}
			case 2950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000095);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000115, EnemyEtis);
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000096);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000116, EnemyEtis);
				break;
			}
			case 3000: {
				FormationGeria001* pF3 = (FormationGeria001*)receiveActor(30001013);
				getSceneChief()->appendGroupChild(pF3);
				break;
			}
			case 3010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000097);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000117, EnemyEtis);
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000098);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000118, EnemyEtis);
				break;
			}
			case 3070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000099);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000119, EnemyEtis);
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000100);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000120, EnemyEtis);
				break;
			}
			case 3130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000101);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000121, EnemyEtis);
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000102);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000122, EnemyEtis);
				break;
			}
			case 3190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000103);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000123, EnemyEtis);
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000104);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000124, EnemyEtis);
				break;
			}
			case 3250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000105);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000125, EnemyEtis);
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000106);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000126, EnemyEtis);
				break;
			}
			case 3310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000107);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000127, EnemyEtis);
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000108);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000128, EnemyEtis);
				break;
			}
			case 3370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000109);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000129, EnemyEtis);
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000110);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000130, EnemyEtis);
				break;
			}
			case 3430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000111);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000131, EnemyEtis);
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000112);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000132, EnemyEtis);
				break;
			}
			case 3490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000113);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000133, EnemyEtis);
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000114);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000134, EnemyEtis);
				break;
			}
			case 3550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000115);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000135, EnemyEtis);
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000116);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000136, EnemyEtis);
				break;
			}
			case 3610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000117);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000137, EnemyEtis);
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000118);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000138, EnemyEtis);
				break;
			}
			case 3670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000119);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000139, EnemyEtis);
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000120);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000140, EnemyEtis);
				break;
			}
			case 3730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000121);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000141, EnemyEtis);
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000122);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000142, EnemyEtis);
				break;
			}
			case 3790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000123);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000143, EnemyEtis);
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000124);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000144, EnemyEtis);
				break;
			}
			case 3850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000125);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000145, EnemyEtis);
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000126);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000146, EnemyEtis);
				break;
			}
			case 3910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000127);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000147, EnemyEtis);
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000128);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000148, EnemyEtis);
				break;
			}
			case 3970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000129);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000149, EnemyEtis);
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000130);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000150, EnemyEtis);
				break;
			}
			case 4030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000131);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000151, EnemyEtis);
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000132);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000152, EnemyEtis);
				break;
			}
			case 4090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000133);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000153, EnemyEtis);
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000134);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000154, EnemyEtis);
				break;
			}
			case 4150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000135);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000155, EnemyEtis);
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000136);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000156, EnemyEtis);
				break;
			}
			case 4210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000137);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000157, EnemyEtis);
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000138);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000158, EnemyEtis);
				break;
			}
			case 4270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000139);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000159, EnemyEtis);
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000140);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000160, EnemyEtis);
				break;
			}
			case 4330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000141);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000161, EnemyEtis);
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000142);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000162, EnemyEtis);
				break;
			}
			case 4390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000143);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000163, EnemyEtis);
				break;
			}
			case 4400: {
				requestActor(30001015, FormationHalia);
				requestActor(30001026, EnemyEsperia);
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000144);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000164, EnemyEtis);
				break;
			}
			case 4450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000145);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000165, EnemyEtis);
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000146);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000166, EnemyEtis);
				break;
			}
			case 4510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000147);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000167, EnemyEtis);
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000148);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000168, EnemyEtis);
				break;
			}
			case 4570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000149);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000169, EnemyEtis);
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000150);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000170, EnemyEtis);
				break;
			}
			case 4630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000151);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000171, EnemyEtis);
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000152);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000172, EnemyEtis);
				break;
			}
			case 4690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000153);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000173, EnemyEtis);
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000154);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000174, EnemyEtis);
				break;
			}
			case 4750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000155);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000175, EnemyEtis);
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000156);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000176, EnemyEtis);
				break;
			}
			case 4810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000157);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000177, EnemyEtis);
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000158);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000178, EnemyEtis);
				break;
			}
			case 4870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000159);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000179, EnemyEtis);
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000160);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000180, EnemyEtis);
				break;
			}
			case 4930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000161);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000181, EnemyEtis);
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000162);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000182, EnemyEtis);
				break;
			}
			case 4990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000163);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000183, EnemyEtis);
				break;
			}
			case 5000: {
				FormationHalia* pF = (FormationHalia*)receiveActor(30001015);
				getSceneChief()->appendGroupChild(pF);
				getSceneChief()->appendGroupChild(receiveActor(30001026));
				break;
			}
			case 5020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000164);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000184, EnemyEtis);
				break;
			}
			case 5050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000165);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000185, EnemyEtis);
				break;
			}
			case 5080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000166);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000186, EnemyEtis);
				break;
			}
			case 5110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000167);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000187, EnemyEtis);
				break;
			}
			case 5140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000168);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000188, EnemyEtis);
				break;
			}
			case 5170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000169);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000189, EnemyEtis);
				break;
			}
			case 5200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000170);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000190, EnemyEtis);
				break;
			}
			case 5230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000171);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000191, EnemyEtis);
				break;
			}
			case 5260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000172);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000192, EnemyEtis);
				break;
			}
			case 5290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000173);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000193, EnemyEtis);
				break;
			}
			case 5320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000174);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000194, EnemyEtis);
				break;
			}
			case 5350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000175);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000195, EnemyEtis);
				break;
			}
			case 5380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000176);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000196, EnemyEtis);
				break;
			}
			case 5400: {
				requestActor(30001027, EnemyEsperia);
				break;
			}
			case 5410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000177);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000197, EnemyEtis);
				break;
			}
			case 5440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000178);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000198, EnemyEtis);
				break;
			}
			case 5470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000179);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000199, EnemyEtis);
				break;
			}
			case 5500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000180);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000200, EnemyEtis);
				break;
			}
			case 5530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000181);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000201, EnemyEtis);
				break;
			}
			case 5560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000182);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000202, EnemyEtis);
				break;
			}
			case 5590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000183);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000203, EnemyEtis);
				break;
			}
			case 5620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000184);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000204, EnemyEtis);
				break;
			}
			case 5650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000185);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000205, EnemyEtis);
				break;
			}
			case 5680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000186);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000206, EnemyEtis);
				break;
			}
			case 5710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000187);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000207, EnemyEtis);
				break;
			}
			case 5740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000188);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000208, EnemyEtis);
				break;
			}
			case 5770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000189);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000209, EnemyEtis);
				break;
			}
			case 5800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000190);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000210, EnemyEtis);
				break;
			}
			case 5830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000191);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000211, EnemyEtis);
				break;
			}
			case 5860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000192);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000212, EnemyEtis);
				break;
			}
			case 5890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000193);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000213, EnemyEtis);
				break;
			}
			case 5920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000194);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000214, EnemyEtis);
				break;
			}
			case 5950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000195);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000215, EnemyEtis);
				break;
			}
			case 5980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000196);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000216, EnemyEtis);
				break;
			}
			case 6000: {
				getSceneChief()->appendGroupChild(receiveActor(30001027));
				break;
			}
			case 6010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000197);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000217, EnemyEtis);
				break;
			}
			case 6040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000198);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000218, EnemyEtis);
				break;
			}
			case 6070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000199);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000219, EnemyEtis);
				break;
			}
			case 6100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000200);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000220, EnemyEtis);
				break;
			}
			case 6130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000201);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000221, EnemyEtis);
				break;
			}
			case 6160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000202);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000222, EnemyEtis);
				break;
			}
			case 6190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000203);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000223, EnemyEtis);
				break;
			}
			case 6220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000204);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000224, EnemyEtis);
				break;
			}
			case 6250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000205);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000225, EnemyEtis);
				break;
			}
			case 6280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000206);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000226, EnemyEtis);
				break;
			}
			case 6310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000207);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000227, EnemyEtis);
				break;
			}
			case 6340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000208);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000228, EnemyEtis);
				break;
			}
			case 6370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000209);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000229, EnemyEtis);
				break;
			}
			case 6400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000210);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000230, EnemyEtis);
				requestActor(30001028, EnemyEsperia);
				break;
			}
			case 6430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000211);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000231, EnemyEtis);
				break;
			}
			case 6460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000212);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000232, EnemyEtis);
				break;
			}
			case 6490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000213);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000233, EnemyEtis);
				break;
			}
			case 6520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000214);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000234, EnemyEtis);
				break;
			}
			case 6550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000215);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000235, EnemyEtis);
				break;
			}
			case 6580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000216);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000236, EnemyEtis);
				break;
			}
			case 6610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000217);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000237, EnemyEtis);
				break;
			}
			case 6640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000218);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000238, EnemyEtis);
				break;
			}
			case 6670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000219);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000239, EnemyEtis);
				break;
			}
			case 6700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000220);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000240, EnemyEtis);
				break;
			}
			case 6730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000221);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000241, EnemyEtis);
				break;
			}
			case 6760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000222);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000242, EnemyEtis);
				break;
			}
			case 6790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000223);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000243, EnemyEtis);
				break;
			}
			case 6820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000224);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000244, EnemyEtis);
				break;
			}
			case 6850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000225);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000245, EnemyEtis);
				break;
			}
			case 6880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000226);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000246, EnemyEtis);
				break;
			}
			case 6910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000227);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000247, EnemyEtis);
				break;
			}
			case 6940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000228);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000248, EnemyEtis);
				break;
			}
			case 6970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000229);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000249, EnemyEtis);
				break;
			}
			case 7000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000230);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000250, EnemyEtis);
				getSceneChief()->appendGroupChild(receiveActor(30001028));
				break;
			}
			case 7030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000231);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000251, EnemyEtis);
				break;
			}
			case 7060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000232);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000252, EnemyEtis);
				break;
			}
			case 7090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000233);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000253, EnemyEtis);
				break;
			}
			case 7120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000234);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000254, EnemyEtis);
				break;
			}
			case 7150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000235);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000255, EnemyEtis);
				break;
			}
			case 7180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000236);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000256, EnemyEtis);
				break;
			}
			case 7210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000237);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000257, EnemyEtis);
				break;
			}
			case 7240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000238);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000258, EnemyEtis);
				break;
			}
			case 7270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000239);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000259, EnemyEtis);
				break;
			}
			case 7300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000240);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000260, EnemyEtis);
				break;
			}
			case 7330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000241);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000261, EnemyEtis);
				break;
			}
			case 7360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000242);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000262, EnemyEtis);
				break;
			}
			case 7390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000243);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000263, EnemyEtis);
				break;
			}
			case 7400: {
				requestActor(30001029, EnemyEsperia);
				break;
			}
			case 7420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000244);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000264, EnemyEtis);
				break;
			}
			case 7450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000245);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000265, EnemyEtis);
				break;
			}
			case 7480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000246);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000266, EnemyEtis);
				break;
			}
			case 7510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000247);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000267, EnemyEtis);
				break;
			}
			case 7540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000248);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000268, EnemyEtis);
				break;
			}
			case 7570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000249);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000269, EnemyEtis);
				break;
			}
			case 7600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000250);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000270, EnemyEtis);
				break;
			}
			case 7630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000251);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000271, EnemyEtis);
				break;
			}
			case 7660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000252);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000272, EnemyEtis);
				break;
			}
			case 7690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000253);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000273, EnemyEtis);
				break;
			}
			case 7720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000254);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000274, EnemyEtis);
				break;
			}
			case 7750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000255);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000275, EnemyEtis);
				break;
			}
			case 7780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000256);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000276, EnemyEtis);
				break;
			}
			case 7810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000257);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000277, EnemyEtis);
				break;
			}
			case 7840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000258);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000278, EnemyEtis);
				break;
			}
			case 7870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000259);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000279, EnemyEtis);
				break;
			}
			case 7900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000260);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000280, EnemyEtis);
				break;
			}
			case 7930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000261);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000281, EnemyEtis);
				break;
			}
			case 7960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000262);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000282, EnemyEtis);
				break;
			}
			case 7990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000263);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000283, EnemyEtis);
				break;
			}
			case 8000: {
				getSceneChief()->appendGroupChild(receiveActor(30001029));
				break;
			}
			case 8020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000264);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000284, EnemyEtis);
				break;
			}
			case 8050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000265);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000285, EnemyEtis);
				break;
			}
			case 8080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000266);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000286, EnemyEtis);
				break;
			}
			case 8110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000267);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000287, EnemyEtis);
				break;
			}
			case 8140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000268);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000288, EnemyEtis);
				break;
			}
			case 8170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000269);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000289, EnemyEtis);
				break;
			}
			case 8200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000270);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000290, EnemyEtis);
				break;
			}
			case 8230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000271);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000291, EnemyEtis);
				break;
			}
			case 8260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000272);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000292, EnemyEtis);
				break;
			}
			case 8290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000273);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000293, EnemyEtis);
				break;
			}
			case 8320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000274);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000294, EnemyEtis);
				break;
			}
			case 8350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000275);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000295, EnemyEtis);
				break;
			}
			case 8380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000276);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000296, EnemyEtis);
				break;
			}
			case 8400: {
				requestActor(30001016, FormationHalia);
				requestActor(30001030, EnemyEsperia);
				break;
			}
			case 8410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000277);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000297, EnemyEtis);
				break;
			}
			case 8440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000278);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000298, EnemyEtis);
				break;
			}
			case 8470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000279);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000299, EnemyEtis);
				break;
			}
			case 8500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000280);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000300, EnemyEtis);
				break;
			}
			case 8530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000281);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000301, EnemyEtis);
				break;
			}
			case 8560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000282);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000302, EnemyEtis);
				break;
			}
			case 8590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000283);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000303, EnemyEtis);
				break;
			}
			case 8600: {
				requestActor(30001018, FormationRis002);
				requestActor(30001019, FormationRis001);
				requestActor(30001020, FormationRis001);
				requestActor(30001021, FormationRis002);
				requestActor(30001022, FormationRis001);
				requestActor(30001023, FormationRis002);
				break;
			}
			case 8620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000284);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000304, EnemyEtis);
				break;
			}
			case 8650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000285);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000305, EnemyEtis);
				break;
			}
			case 8680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000286);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000306, EnemyEtis);
				break;
			}
			case 8710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000287);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000307, EnemyEtis);
				break;
			}
			case 8740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000288);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000308, EnemyEtis);
				break;
			}
			case 8770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000289);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000309, EnemyEtis);
				break;
			}
			case 8800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000290);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000310, EnemyEtis);
				break;
			}
			case 8830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000291);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000311, EnemyEtis);
				break;
			}
			case 8860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000292);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000312, EnemyEtis);
				break;
			}
			case 8890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000293);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000313, EnemyEtis);
				break;
			}
			case 8900: {
				requestActor(30001024, EnemyIrce);
				break;
			}
			case 8920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000294);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000314, EnemyEtis);
				break;
			}
			case 8950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000295);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000315, EnemyEtis);
				break;
			}
			case 8980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000296);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000316, EnemyEtis);
				break;
			}
			case 9000: {
				FormationHalia* pF = (FormationHalia*)receiveActor(30001016);
				getSceneChief()->appendGroupChild(pF);
				getSceneChief()->appendGroupChild(receiveActor(30001030));
				break;
			}
			case 9010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000297);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000317, EnemyEtis);
				break;
			}
			case 9040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000298);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000318, EnemyEtis);
				break;
			}
			case 9070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000299);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000319, EnemyEtis);
				break;
			}
			case 9100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000300);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000320, EnemyEtis);
				break;
			}
			case 9130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000301);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000321, EnemyEtis);
				break;
			}
			case 9160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000302);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000322, EnemyEtis);
				break;
			}
			case 9190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000303);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000323, EnemyEtis);
				break;
			}
			case 9200: {
				{
				RotateFormationScene* ta = NEW RotateFormationScene("RotateFormationScene-4");
				ta->setMaxPerformFrame(2000);
				appendChild(ta);
				ta->addFormation(((FormationRis002*)receiveActor(30001018)), 400);
				ta->addFormation(((FormationRis001*)receiveActor(30001019)), 400);
				ta->addFormation(((FormationRis001*)receiveActor(30001020)), 400);
				ta->addFormation(((FormationRis002*)receiveActor(30001021)), 400);
				ta->addFormation(((FormationRis001*)receiveActor(30001022)), 400);
				ta->addFormation(((FormationRis002*)receiveActor(30001023)), 400);
				}
				break;
			}
			case 9220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000304);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000324, EnemyEtis);
				break;
			}
			case 9250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000305);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000325, EnemyEtis);
				break;
			}
			case 9280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000306);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000326, EnemyEtis);
				break;
			}
			case 9310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000307);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000327, EnemyEtis);
				break;
			}
			case 9340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000308);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000328, EnemyEtis);
				break;
			}
			case 9370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000309);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000329, EnemyEtis);
				break;
			}
			case 9400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000310);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000330, EnemyEtis);
				requestActor(30001031, EnemyEsperia);
				break;
			}
			case 9430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000311);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000331, EnemyEtis);
				break;
			}
			case 9460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000312);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000332, EnemyEtis);
				break;
			}
			case 9490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000313);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000333, EnemyEtis);
				break;
			}
			case 9500: {
				EnemyIrce* p5 = (EnemyIrce*)receiveActor(30001024);
				getSceneChief()->appendGroupChild(p5);
				break;
			}
			case 9520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000314);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000334, EnemyEtis);
				break;
			}
			case 9550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000315);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000335, EnemyEtis);
				break;
			}
			case 9580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000316);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000336, EnemyEtis);
				break;
			}
			case 9610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000317);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000337, EnemyEtis);
				break;
			}
			case 9640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000318);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000338, EnemyEtis);
				break;
			}
			case 9670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000319);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000339, EnemyEtis);
				break;
			}
			case 9700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000320);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000340, EnemyEtis);
				break;
			}
			case 9730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000321);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000341, EnemyEtis);
				break;
			}
			case 9760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000322);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000342, EnemyEtis);
				break;
			}
			case 9790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000323);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000343, EnemyEtis);
				break;
			}
			case 9820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000324);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000344, EnemyEtis);
				break;
			}
			case 9850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000325);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000345, EnemyEtis);
				break;
			}
			case 9880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000326);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000346, EnemyEtis);
				break;
			}
			case 9910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000327);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000347, EnemyEtis);
				break;
			}
			case 9940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000328);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000348, EnemyEtis);
				break;
			}
			case 9970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000329);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000349, EnemyEtis);
				break;
			}
			case 10000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000330);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000350, EnemyEtis);
				getSceneChief()->appendGroupChild(receiveActor(30001031));
				break;
			}
			case 10030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000331);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000351, EnemyEtis);
				break;
			}
			case 10060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000332);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000352, EnemyEtis);
				break;
			}
			case 10090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000333);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000353, EnemyEtis);
				break;
			}
			case 10120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000334);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000354, EnemyEtis);
				break;
			}
			case 10150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000335);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000355, EnemyEtis);
				break;
			}
			case 10180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000336);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000356, EnemyEtis);
				break;
			}
			case 10210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000337);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000357, EnemyEtis);
				break;
			}
			case 10240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000338);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000358, EnemyEtis);
				break;
			}
			case 10270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000339);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000359, EnemyEtis);
				break;
			}
			case 10300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000340);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000360, EnemyEtis);
				break;
			}
			case 10330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000341);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000361, EnemyEtis);
				break;
			}
			case 10360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000342);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000362, EnemyEtis);
				break;
			}
			case 10390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000343);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000363, EnemyEtis);
				break;
			}
			case 10420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000344);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000364, EnemyEtis);
				break;
			}
			case 10450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000345);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000365, EnemyEtis);
				break;
			}
			case 10480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000346);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000366, EnemyEtis);
				break;
			}
			case 10510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000347);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000367, EnemyEtis);
				break;
			}
			case 10540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000348);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000368, EnemyEtis);
				break;
			}
			case 10570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000349);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000369, EnemyEtis);
				break;
			}
			case 10600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000350);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000370, EnemyEtis);
				break;
			}
			case 10630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000351);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000371, EnemyEtis);
				break;
			}
			case 10660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000352);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000372, EnemyEtis);
				break;
			}
			case 10690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000353);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000373, EnemyEtis);
				break;
			}
			case 10720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000354);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000374, EnemyEtis);
				break;
			}
			case 10750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000355);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000375, EnemyEtis);
				break;
			}
			case 10780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000356);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000376, EnemyEtis);
				break;
			}
			case 10810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000357);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000377, EnemyEtis);
				break;
			}
			case 10840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000358);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000378, EnemyEtis);
				break;
			}
			case 10870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000359);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000379, EnemyEtis);
				break;
			}
			case 10900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000360);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000380, EnemyEtis);
				break;
			}
			case 10930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000361);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000381, EnemyEtis);
				break;
			}
			case 10960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000362);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000382, EnemyEtis);
				break;
			}
			case 10990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000363);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000383, EnemyEtis);
				break;
			}
			case 11020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000364);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000384, EnemyEtis);
				break;
			}
			case 11050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000365);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000385, EnemyEtis);
				break;
			}
			case 11080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000366);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000386, EnemyEtis);
				break;
			}
			case 11110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000367);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000387, EnemyEtis);
				break;
			}
			case 11140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000368);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000388, EnemyEtis);
				break;
			}
			case 11170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000369);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000389, EnemyEtis);
				break;
			}
			case 11200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000370);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000390, EnemyEtis);
				break;
			}
			case 11230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000371);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000391, EnemyEtis);
				break;
			}
			case 11260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000372);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000392, EnemyEtis);
				break;
			}
			case 11290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000373);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000393, EnemyEtis);
				break;
			}
			case 11320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000374);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000394, EnemyEtis);
				break;
			}
			case 11350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000375);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000395, EnemyEtis);
				break;
			}
			case 11380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000376);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000396, EnemyEtis);
				break;
			}
			case 11410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000377);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000397, EnemyEtis);
				break;
			}
			case 11440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000378);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000398, EnemyEtis);
				break;
			}
			case 11470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000379);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000399, EnemyEtis);
				break;
			}
			case 11500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000380);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000400, EnemyEtis);
				break;
			}
			case 11530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000381);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000401, EnemyEtis);
				break;
			}
			case 11560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000382);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000402, EnemyEtis);
				break;
			}
			case 11590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000383);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000403, EnemyEtis);
				break;
			}
			case 11620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000384);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000404, EnemyEtis);
				break;
			}
			case 11650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000385);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000405, EnemyEtis);
				break;
			}
			case 11680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000386);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000406, EnemyEtis);
				break;
			}
			case 11710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000387);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000407, EnemyEtis);
				break;
			}
			case 11740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000388);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000408, EnemyEtis);
				break;
			}
			case 11770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000389);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000409, EnemyEtis);
				break;
			}
			case 11800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000390);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000410, EnemyEtis);
				break;
			}
			case 11830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000391);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000411, EnemyEtis);
				break;
			}
			case 11860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000392);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000412, EnemyEtis);
				break;
			}
			case 11890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000393);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000413, EnemyEtis);
				break;
			}
			case 11920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000394);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000414, EnemyEtis);
				break;
			}
			case 11950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000395);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000415, EnemyEtis);
				break;
			}
			case 11980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000396);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000416, EnemyEtis);
				break;
			}
			case 12010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000397);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000417, EnemyEtis);
				break;
			}
			case 12040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000398);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000418, EnemyEtis);
				break;
			}
			case 12070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000399);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000419, EnemyEtis);
				break;
			}
			case 12100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000400);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000420, EnemyEtis);
				break;
			}
			case 12130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000401);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000421, EnemyEtis);
				break;
			}
			case 12160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000402);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000422, EnemyEtis);
				break;
			}
			case 12190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000403);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000423, EnemyEtis);
				break;
			}
			case 12220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000404);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000424, EnemyEtis);
				break;
			}
			case 12250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000405);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000425, EnemyEtis);
				break;
			}
			case 12280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000406);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000426, EnemyEtis);
				break;
			}
			case 12310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000407);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000427, EnemyEtis);
				break;
			}
			case 12340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000408);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000428, EnemyEtis);
				break;
			}
			case 12370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000409);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000429, EnemyEtis);
				break;
			}
			case 12400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000410);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000430, EnemyEtis);
				break;
			}
			case 12430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000411);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000431, EnemyEtis);
				break;
			}
			case 12460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000412);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000432, EnemyEtis);
				break;
			}
			case 12490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000413);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000433, EnemyEtis);
				break;
			}
			case 12520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000414);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000434, EnemyEtis);
				break;
			}
			case 12550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000415);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000435, EnemyEtis);
				break;
			}
			case 12580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000416);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000436, EnemyEtis);
				break;
			}
			case 12610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000417);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000437, EnemyEtis);
				break;
			}
			case 12640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000418);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000438, EnemyEtis);
				break;
			}
			case 12670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000419);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000439, EnemyEtis);
				break;
			}
			case 12700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000420);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000440, EnemyEtis);
				break;
			}
			case 12730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000421);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000441, EnemyEtis);
				break;
			}
			case 12760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000422);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000442, EnemyEtis);
				break;
			}
			case 12790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000423);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000443, EnemyEtis);
				break;
			}
			case 12820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000424);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000444, EnemyEtis);
				break;
			}
			case 12850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000425);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000445, EnemyEtis);
				break;
			}
			case 12880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000426);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000446, EnemyEtis);
				break;
			}
			case 12910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000427);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000447, EnemyEtis);
				break;
			}
			case 12940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000428);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000448, EnemyEtis);
				break;
			}
			case 12970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000429);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000449, EnemyEtis);
				break;
			}
			case 13000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000430);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000450, EnemyEtis);
				break;
			}
			case 13030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000431);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000451, EnemyEtis);
				break;
			}
			case 13060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000432);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000452, EnemyEtis);
				break;
			}
			case 13090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000433);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000453, EnemyEtis);
				break;
			}
			case 13120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000434);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000454, EnemyEtis);
				break;
			}
			case 13150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000435);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000455, EnemyEtis);
				break;
			}
			case 13180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000436);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000456, EnemyEtis);
				break;
			}
			case 13210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000437);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000457, EnemyEtis);
				break;
			}
			case 13240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000438);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000458, EnemyEtis);
				break;
			}
			case 13270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000439);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000459, EnemyEtis);
				break;
			}
			case 13300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000440);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000460, EnemyEtis);
				break;
			}
			case 13330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000441);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000461, EnemyEtis);
				break;
			}
			case 13360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000442);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000462, EnemyEtis);
				break;
			}
			case 13390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000443);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000463, EnemyEtis);
				break;
			}
			case 13420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000444);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000464, EnemyEtis);
				break;
			}
			case 13450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000445);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000465, EnemyEtis);
				break;
			}
			case 13480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000446);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000466, EnemyEtis);
				break;
			}
			case 13510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000447);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000467, EnemyEtis);
				break;
			}
			case 13540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000448);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000468, EnemyEtis);
				break;
			}
			case 13570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000449);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000469, EnemyEtis);
				break;
			}
			case 13600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000450);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000470, EnemyEtis);
				break;
			}
			case 13630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000451);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000471, EnemyEtis);
				break;
			}
			case 13660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000452);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000472, EnemyEtis);
				break;
			}
			case 13690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000453);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000473, EnemyEtis);
				break;
			}
			case 13720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000454);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000474, EnemyEtis);
				break;
			}
			case 13750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000455);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000475, EnemyEtis);
				break;
			}
			case 13780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000456);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000476, EnemyEtis);
				break;
			}
			case 13810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000457);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000477, EnemyEtis);
				break;
			}
			case 13840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000458);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000478, EnemyEtis);
				break;
			}
			case 13870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000459);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000479, EnemyEtis);
				break;
			}
			case 13900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000460);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000480, EnemyEtis);
				break;
			}
			case 13930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000461);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000481, EnemyEtis);
				break;
			}
			case 13960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000462);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000482, EnemyEtis);
				break;
			}
			case 13990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000463);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000483, EnemyEtis);
				break;
			}
			case 14020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000464);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000484, EnemyEtis);
				break;
			}
			case 14050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000465);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000485, EnemyEtis);
				break;
			}
			case 14080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000466);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000486, EnemyEtis);
				break;
			}
			case 14110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000467);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000487, EnemyEtis);
				break;
			}
			case 14140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000468);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000488, EnemyEtis);
				break;
			}
			case 14170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000469);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000489, EnemyEtis);
				break;
			}
			case 14200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000470);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000490, EnemyEtis);
				break;
			}
			case 14230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000471);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000491, EnemyEtis);
				break;
			}
			case 14260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000472);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000492, EnemyEtis);
				break;
			}
			case 14290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000473);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000493, EnemyEtis);
				break;
			}
			case 14320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000474);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000494, EnemyEtis);
				break;
			}
			case 14350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000475);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000495, EnemyEtis);
				break;
			}
			case 14380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000476);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000496, EnemyEtis);
				break;
			}
			case 14410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000477);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000497, EnemyEtis);
				break;
			}
			case 14440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000478);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000498, EnemyEtis);
				break;
			}
			case 14470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000479);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000499, EnemyEtis);
				break;
			}
			case 14500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000480);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000500, EnemyEtis);
				break;
			}
			case 14530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000481);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000501, EnemyEtis);
				break;
			}
			case 14560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000482);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000502, EnemyEtis);
				break;
			}
			case 14590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000483);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000503, EnemyEtis);
				break;
			}
			case 14620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000484);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000504, EnemyEtis);
				break;
			}
			case 14650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000485);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000505, EnemyEtis);
				break;
			}
			case 14680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000486);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000506, EnemyEtis);
				break;
			}
			case 14710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000487);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000507, EnemyEtis);
				break;
			}
			case 14740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000488);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000508, EnemyEtis);
				break;
			}
			case 14770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000489);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000509, EnemyEtis);
				break;
			}
			case 14800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000490);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000510, EnemyEtis);
				break;
			}
			case 14830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000491);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000511, EnemyEtis);
				break;
			}
			case 14860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000492);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000512, EnemyEtis);
				break;
			}
			case 14890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000493);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000513, EnemyEtis);
				break;
			}
			case 14920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000494);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000514, EnemyEtis);
				break;
			}
			case 14950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000495);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000515, EnemyEtis);
				break;
			}
			case 14980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000496);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000516, EnemyEtis);
				break;
			}
			case 15010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000497);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000517, EnemyEtis);
				break;
			}
			case 15040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000498);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000518, EnemyEtis);
				break;
			}
			case 15070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000499);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000519, EnemyEtis);
				break;
			}
			case 15100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000500);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000520, EnemyEtis);
				break;
			}
			case 15130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000501);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000521, EnemyEtis);
				break;
			}
			case 15160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000502);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000522, EnemyEtis);
				break;
			}
			case 15190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000503);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000523, EnemyEtis);
				break;
			}
			case 15220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000504);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000524, EnemyEtis);
				break;
			}
			case 15250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000505);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000525, EnemyEtis);
				break;
			}
			case 15280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000506);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000526, EnemyEtis);
				break;
			}
			case 15310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000507);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000527, EnemyEtis);
				break;
			}
			case 15340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000508);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000528, EnemyEtis);
				break;
			}
			case 15370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000509);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000529, EnemyEtis);
				break;
			}
			case 15400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000510);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000530, EnemyEtis);
				break;
			}
			case 15430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000511);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000531, EnemyEtis);
				break;
			}
			case 15460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000512);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000532, EnemyEtis);
				break;
			}
			case 15490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000513);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000533, EnemyEtis);
				break;
			}
			case 15520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000514);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000534, EnemyEtis);
				break;
			}
			case 15550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000515);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000535, EnemyEtis);
				break;
			}
			case 15580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000516);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000536, EnemyEtis);
				break;
			}
			case 15610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000517);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000537, EnemyEtis);
				break;
			}
			case 15640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000518);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000538, EnemyEtis);
				break;
			}
			case 15670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000519);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000539, EnemyEtis);
				break;
			}
			case 15700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000520);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000540, EnemyEtis);
				break;
			}
			case 15730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000521);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000541, EnemyEtis);
				break;
			}
			case 15760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000522);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000542, EnemyEtis);
				break;
			}
			case 15790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000523);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000543, EnemyEtis);
				break;
			}
			case 15820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000524);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000544, EnemyEtis);
				break;
			}
			case 15850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000525);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000545, EnemyEtis);
				break;
			}
			case 15880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000526);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000546, EnemyEtis);
				break;
			}
			case 15910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000527);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000547, EnemyEtis);
				break;
			}
			case 15940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000528);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000548, EnemyEtis);
				break;
			}
			case 15970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000529);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000549, EnemyEtis);
				break;
			}
			case 16000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000530);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000550, EnemyEtis);
				break;
			}
			case 16030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000531);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000551, EnemyEtis);
				break;
			}
			case 16060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000532);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000552, EnemyEtis);
				break;
			}
			case 16090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000533);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000553, EnemyEtis);
				break;
			}
			case 16120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000534);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000554, EnemyEtis);
				break;
			}
			case 16150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000535);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000555, EnemyEtis);
				break;
			}
			case 16180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000536);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000556, EnemyEtis);
				break;
			}
			case 16210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000537);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000557, EnemyEtis);
				break;
			}
			case 16240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000538);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000558, EnemyEtis);
				break;
			}
			case 16270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000539);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000559, EnemyEtis);
				break;
			}
			case 16300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000540);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000560, EnemyEtis);
				break;
			}
			case 16330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000541);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000561, EnemyEtis);
				break;
			}
			case 16360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000542);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000562, EnemyEtis);
				break;
			}
			case 16390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000543);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000563, EnemyEtis);
				break;
			}
			case 16420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000544);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000564, EnemyEtis);
				break;
			}
			case 16450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000545);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000565, EnemyEtis);
				break;
			}
			case 16480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000546);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000566, EnemyEtis);
				break;
			}
			case 16510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000547);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000567, EnemyEtis);
				break;
			}
			case 16540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000548);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000568, EnemyEtis);
				break;
			}
			case 16570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000549);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000569, EnemyEtis);
				break;
			}
			case 16600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000550);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000570, EnemyEtis);
				break;
			}
			case 16630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000551);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000571, EnemyEtis);
				break;
			}
			case 16660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000552);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000572, EnemyEtis);
				break;
			}
			case 16690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000553);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000573, EnemyEtis);
				break;
			}
			case 16720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000554);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000574, EnemyEtis);
				break;
			}
			case 16750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000555);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000575, EnemyEtis);
				break;
			}
			case 16780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000556);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000576, EnemyEtis);
				break;
			}
			case 16810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000557);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000577, EnemyEtis);
				break;
			}
			case 16840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000558);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000578, EnemyEtis);
				break;
			}
			case 16870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000559);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000579, EnemyEtis);
				break;
			}
			case 16900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000560);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000580, EnemyEtis);
				break;
			}
			case 16930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000561);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000581, EnemyEtis);
				break;
			}
			case 16960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000562);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000582, EnemyEtis);
				break;
			}
			case 16990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000563);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000583, EnemyEtis);
				break;
			}
			case 17020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000564);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000584, EnemyEtis);
				break;
			}
			case 17050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000565);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000585, EnemyEtis);
				break;
			}
			case 17080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000566);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000586, EnemyEtis);
				break;
			}
			case 17110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000567);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000587, EnemyEtis);
				break;
			}
			case 17140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000568);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000588, EnemyEtis);
				break;
			}
			case 17170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000569);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000589, EnemyEtis);
				break;
			}
			case 17200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000570);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000590, EnemyEtis);
				break;
			}
			case 17230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000571);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000591, EnemyEtis);
				break;
			}
			case 17260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000572);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000592, EnemyEtis);
				break;
			}
			case 17290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000573);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000593, EnemyEtis);
				break;
			}
			case 17320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000574);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000594, EnemyEtis);
				break;
			}
			case 17350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000575);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000595, EnemyEtis);
				break;
			}
			case 17380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000576);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000596, EnemyEtis);
				break;
			}
			case 17410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000577);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000597, EnemyEtis);
				break;
			}
			case 17440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000578);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000598, EnemyEtis);
				break;
			}
			case 17470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000579);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000599, EnemyEtis);
				break;
			}
			case 17500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000580);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000600, EnemyEtis);
				break;
			}
			case 17530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000581);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000601, EnemyEtis);
				break;
			}
			case 17560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000582);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000602, EnemyEtis);
				break;
			}
			case 17590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000583);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000603, EnemyEtis);
				break;
			}
			case 17620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000584);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000604, EnemyEtis);
				break;
			}
			case 17650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000585);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000605, EnemyEtis);
				break;
			}
			case 17680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000586);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000606, EnemyEtis);
				break;
			}
			case 17710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000587);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000607, EnemyEtis);
				break;
			}
			case 17740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000588);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000608, EnemyEtis);
				break;
			}
			case 17770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000589);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000609, EnemyEtis);
				break;
			}
			case 17800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000590);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000610, EnemyEtis);
				break;
			}
			case 17830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000591);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000611, EnemyEtis);
				break;
			}
			case 17860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000592);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000612, EnemyEtis);
				break;
			}
			case 17890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000593);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000613, EnemyEtis);
				break;
			}
			case 17920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000594);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000614, EnemyEtis);
				break;
			}
			case 17950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000595);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000615, EnemyEtis);
				break;
			}
			case 17980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000596);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000616, EnemyEtis);
				break;
			}
			case 18010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000597);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000617, EnemyEtis);
				break;
			}
			case 18040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000598);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000618, EnemyEtis);
				break;
			}
			case 18070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000599);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000619, EnemyEtis);
				break;
			}
			case 18100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000600);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000620, EnemyEtis);
				break;
			}
			case 18130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000601);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000621, EnemyEtis);
				break;
			}
			case 18160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000602);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000622, EnemyEtis);
				break;
			}
			case 18190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000603);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000623, EnemyEtis);
				break;
			}
			case 18220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000604);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000624, EnemyEtis);
				break;
			}
			case 18250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000605);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000625, EnemyEtis);
				break;
			}
			case 18280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000606);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000626, EnemyEtis);
				break;
			}
			case 18310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000607);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000627, EnemyEtis);
				break;
			}
			case 18340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000608);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000628, EnemyEtis);
				break;
			}
			case 18370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000609);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000629, EnemyEtis);
				break;
			}
			case 18400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000610);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000630, EnemyEtis);
				break;
			}
			case 18430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000611);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000631, EnemyEtis);
				break;
			}
			case 18460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000612);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000632, EnemyEtis);
				break;
			}
			case 18490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000613);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000633, EnemyEtis);
				break;
			}
			case 18520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000614);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000634, EnemyEtis);
				break;
			}
			case 18550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000615);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000635, EnemyEtis);
				break;
			}
			case 18580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000616);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000636, EnemyEtis);
				break;
			}
			case 18610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000617);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000637, EnemyEtis);
				break;
			}
			case 18640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000618);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000638, EnemyEtis);
				break;
			}
			case 18670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000619);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000639, EnemyEtis);
				break;
			}
			case 18700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000620);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000640, EnemyEtis);
				break;
			}
			case 18730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000621);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000641, EnemyEtis);
				break;
			}
			case 18760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000622);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000642, EnemyEtis);
				break;
			}
			case 18790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000623);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000643, EnemyEtis);
				break;
			}
			case 18820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000624);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000644, EnemyEtis);
				break;
			}
			case 18850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000625);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000645, EnemyEtis);
				break;
			}
			case 18880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000626);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000646, EnemyEtis);
				break;
			}
			case 18910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000627);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000647, EnemyEtis);
				break;
			}
			case 18940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000628);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000648, EnemyEtis);
				break;
			}
			case 18970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000629);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000649, EnemyEtis);
				break;
			}
			case 19000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000630);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000650, EnemyEtis);
				break;
			}
			case 19030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000631);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000651, EnemyEtis);
				break;
			}
			case 19060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000632);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000652, EnemyEtis);
				break;
			}
			case 19090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000633);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000653, EnemyEtis);
				break;
			}
			case 19120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000634);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000654, EnemyEtis);
				break;
			}
			case 19150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000635);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000655, EnemyEtis);
				break;
			}
			case 19180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000636);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000656, EnemyEtis);
				break;
			}
			case 19210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000637);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000657, EnemyEtis);
				break;
			}
			case 19240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000638);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000658, EnemyEtis);
				break;
			}
			case 19270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000639);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000659, EnemyEtis);
				break;
			}
			case 19300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000640);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000660, EnemyEtis);
				break;
			}
			case 19330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000641);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000661, EnemyEtis);
				break;
			}
			case 19360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000642);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000662, EnemyEtis);
				break;
			}
			case 19390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000643);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000663, EnemyEtis);
				break;
			}
			case 19420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000644);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000664, EnemyEtis);
				break;
			}
			case 19450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000645);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000665, EnemyEtis);
				break;
			}
			case 19480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000646);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000666, EnemyEtis);
				break;
			}
			case 19510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000647);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000667, EnemyEtis);
				break;
			}
			case 19540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000648);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000668, EnemyEtis);
				break;
			}
			case 19570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000649);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000669, EnemyEtis);
				break;
			}
			case 19600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000650);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000670, EnemyEtis);
				break;
			}
			case 19630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000651);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000671, EnemyEtis);
				break;
			}
			case 19660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000652);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000672, EnemyEtis);
				break;
			}
			case 19690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000653);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000673, EnemyEtis);
				break;
			}
			case 19720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000654);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000674, EnemyEtis);
				break;
			}
			case 19750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000655);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000675, EnemyEtis);
				break;
			}
			case 19780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000656);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000676, EnemyEtis);
				break;
			}
			case 19810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000657);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000677, EnemyEtis);
				break;
			}
			case 19840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000658);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000678, EnemyEtis);
				break;
			}
			case 19870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000659);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000679, EnemyEtis);
				break;
			}
			case 19900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000660);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000680, EnemyEtis);
				break;
			}
			case 19930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000661);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000681, EnemyEtis);
				break;
			}
			case 19960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000662);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000682, EnemyEtis);
				break;
			}
			case 19990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000663);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000683, EnemyEtis);
				break;
			}
			case 20020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000664);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000684, EnemyEtis);
				break;
			}
			case 20050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000665);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000685, EnemyEtis);
				break;
			}
			case 20080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000666);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000686, EnemyEtis);
				break;
			}
			case 20110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000667);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000687, EnemyEtis);
				break;
			}
			case 20140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000668);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000688, EnemyEtis);
				break;
			}
			case 20170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000669);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000689, EnemyEtis);
				break;
			}
			case 20200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000670);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000690, EnemyEtis);
				break;
			}
			case 20230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000671);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000691, EnemyEtis);
				break;
			}
			case 20260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000672);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000692, EnemyEtis);
				break;
			}
			case 20290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000673);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000693, EnemyEtis);
				break;
			}
			case 20320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000674);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000694, EnemyEtis);
				break;
			}
			case 20350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000675);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000695, EnemyEtis);
				break;
			}
			case 20380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000676);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000696, EnemyEtis);
				break;
			}
			case 20410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000677);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000697, EnemyEtis);
				break;
			}
			case 20440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000678);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000698, EnemyEtis);
				break;
			}
			case 20470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000679);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000699, EnemyEtis);
				break;
			}
			case 20500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000680);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000700, EnemyEtis);
				break;
			}
			case 20530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000681);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000701, EnemyEtis);
				break;
			}
			case 20560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000682);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000702, EnemyEtis);
				break;
			}
			case 20590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000683);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000703, EnemyEtis);
				break;
			}
			case 20620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000684);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000704, EnemyEtis);
				break;
			}
			case 20650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000685);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000705, EnemyEtis);
				break;
			}
			case 20680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000686);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000706, EnemyEtis);
				break;
			}
			case 20710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000687);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000707, EnemyEtis);
				break;
			}
			case 20740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000688);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000708, EnemyEtis);
				break;
			}
			case 20770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000689);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000709, EnemyEtis);
				break;
			}
			case 20800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000690);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000710, EnemyEtis);
				break;
			}
			case 20830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000691);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000711, EnemyEtis);
				break;
			}
			case 20860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000692);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000712, EnemyEtis);
				break;
			}
			case 20890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000693);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000713, EnemyEtis);
				break;
			}
			case 20920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000694);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000714, EnemyEtis);
				break;
			}
			case 20950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000695);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000715, EnemyEtis);
				break;
			}
			case 20980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000696);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000716, EnemyEtis);
				break;
			}
			case 21010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000697);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000717, EnemyEtis);
				break;
			}
			case 21040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000698);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000718, EnemyEtis);
				break;
			}
			case 21070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000699);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000719, EnemyEtis);
				break;
			}
			case 21100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000700);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000720, EnemyEtis);
				break;
			}
			case 21130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000701);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000721, EnemyEtis);
				break;
			}
			case 21160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000702);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000722, EnemyEtis);
				break;
			}
			case 21190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000703);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000723, EnemyEtis);
				break;
			}
			case 21220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000704);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000724, EnemyEtis);
				break;
			}
			case 21250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000705);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000725, EnemyEtis);
				break;
			}
			case 21280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000706);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000726, EnemyEtis);
				break;
			}
			case 21310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000707);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000727, EnemyEtis);
				break;
			}
			case 21340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000708);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000728, EnemyEtis);
				break;
			}
			case 21370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000709);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000729, EnemyEtis);
				break;
			}
			case 21400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000710);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000730, EnemyEtis);
				break;
			}
			case 21430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000711);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000731, EnemyEtis);
				break;
			}
			case 21460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000712);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000732, EnemyEtis);
				break;
			}
			case 21490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000713);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000733, EnemyEtis);
				break;
			}
			case 21520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000714);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000734, EnemyEtis);
				break;
			}
			case 21550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000715);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000735, EnemyEtis);
				break;
			}
			case 21580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000716);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000736, EnemyEtis);
				break;
			}
			case 21610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000717);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000737, EnemyEtis);
				break;
			}
			case 21640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000718);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000738, EnemyEtis);
				break;
			}
			case 21670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000719);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000739, EnemyEtis);
				break;
			}
			case 21700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000720);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000740, EnemyEtis);
				break;
			}
			case 21730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000721);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000741, EnemyEtis);
				break;
			}
			case 21760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000722);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000742, EnemyEtis);
				break;
			}
			case 21790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000723);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000743, EnemyEtis);
				break;
			}
			case 21820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000724);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000744, EnemyEtis);
				break;
			}
			case 21850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000725);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000745, EnemyEtis);
				break;
			}
			case 21880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000726);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000746, EnemyEtis);
				break;
			}
			case 21910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000727);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000747, EnemyEtis);
				break;
			}
			case 21940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000728);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000748, EnemyEtis);
				break;
			}
			case 21970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000729);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000749, EnemyEtis);
				break;
			}
			case 22000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000730);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000750, EnemyEtis);
				break;
			}
			case 22030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000731);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000751, EnemyEtis);
				break;
			}
			case 22060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000732);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000752, EnemyEtis);
				break;
			}
			case 22090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000733);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000753, EnemyEtis);
				break;
			}
			case 22120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000734);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000754, EnemyEtis);
				break;
			}
			case 22150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000735);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000755, EnemyEtis);
				break;
			}
			case 22180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000736);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000756, EnemyEtis);
				break;
			}
			case 22210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000737);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000757, EnemyEtis);
				break;
			}
			case 22240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000738);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000758, EnemyEtis);
				break;
			}
			case 22270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000739);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000759, EnemyEtis);
				break;
			}
			case 22300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000740);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000760, EnemyEtis);
				break;
			}
			case 22330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000741);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000761, EnemyEtis);
				break;
			}
			case 22360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000742);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000762, EnemyEtis);
				break;
			}
			case 22390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000743);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000763, EnemyEtis);
				break;
			}
			case 22420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000744);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000764, EnemyEtis);
				break;
			}
			case 22450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000745);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000765, EnemyEtis);
				break;
			}
			case 22480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000746);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000766, EnemyEtis);
				break;
			}
			case 22510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000747);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000767, EnemyEtis);
				break;
			}
			case 22540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000748);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000768, EnemyEtis);
				break;
			}
			case 22570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000749);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000769, EnemyEtis);
				break;
			}
			case 22600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000750);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000770, EnemyEtis);
				break;
			}
			case 22630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000751);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000771, EnemyEtis);
				break;
			}
			case 22660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000752);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000772, EnemyEtis);
				break;
			}
			case 22690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000753);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000773, EnemyEtis);
				break;
			}
			case 22720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000754);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000774, EnemyEtis);
				break;
			}
			case 22750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000755);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000775, EnemyEtis);
				break;
			}
			case 22780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000756);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000776, EnemyEtis);
				break;
			}
			case 22810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000757);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000777, EnemyEtis);
				break;
			}
			case 22840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000758);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000778, EnemyEtis);
				break;
			}
			case 22870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000759);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000779, EnemyEtis);
				break;
			}
			case 22900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000760);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000780, EnemyEtis);
				break;
			}
			case 22930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000761);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000781, EnemyEtis);
				break;
			}
			case 22960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000762);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000782, EnemyEtis);
				break;
			}
			case 22990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000763);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000783, EnemyEtis);
				break;
			}
			case 23020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000764);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000784, EnemyEtis);
				break;
			}
			case 23050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000765);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000785, EnemyEtis);
				break;
			}
			case 23080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000766);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000786, EnemyEtis);
				break;
			}
			case 23110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000767);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000787, EnemyEtis);
				break;
			}
			case 23140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000768);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000788, EnemyEtis);
				break;
			}
			case 23170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000769);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000789, EnemyEtis);
				break;
			}
			case 23200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000770);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000790, EnemyEtis);
				break;
			}
			case 23230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000771);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000791, EnemyEtis);
				break;
			}
			case 23260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000772);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000792, EnemyEtis);
				break;
			}
			case 23290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000773);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000793, EnemyEtis);
				break;
			}
			case 23320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000774);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000794, EnemyEtis);
				break;
			}
			case 23350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000775);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000795, EnemyEtis);
				break;
			}
			case 23380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000776);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000796, EnemyEtis);
				break;
			}
			case 23410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000777);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000797, EnemyEtis);
				break;
			}
			case 23440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000778);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000798, EnemyEtis);
				break;
			}
			case 23470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000779);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000799, EnemyEtis);
				break;
			}
			case 23500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000780);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000800, EnemyEtis);
				break;
			}
			case 23530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000781);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000801, EnemyEtis);
				break;
			}
			case 23560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000782);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000802, EnemyEtis);
				break;
			}
			case 23590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000783);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000803, EnemyEtis);
				break;
			}
			case 23620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000784);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000804, EnemyEtis);
				break;
			}
			case 23650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000785);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000805, EnemyEtis);
				break;
			}
			case 23680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000786);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000806, EnemyEtis);
				break;
			}
			case 23710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000787);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000807, EnemyEtis);
				break;
			}
			case 23740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000788);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000808, EnemyEtis);
				break;
			}
			case 23770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000789);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000809, EnemyEtis);
				break;
			}
			case 23800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000790);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000810, EnemyEtis);
				break;
			}
			case 23830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000791);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000811, EnemyEtis);
				break;
			}
			case 23860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000792);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000812, EnemyEtis);
				break;
			}
			case 23890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000793);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000813, EnemyEtis);
				break;
			}
			case 23920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000794);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000814, EnemyEtis);
				break;
			}
			case 23950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000795);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000815, EnemyEtis);
				break;
			}
			case 23980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000796);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000816, EnemyEtis);
				break;
			}
			case 24010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000797);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000817, EnemyEtis);
				break;
			}
			case 24040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000798);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000818, EnemyEtis);
				break;
			}
			case 24070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000799);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000819, EnemyEtis);
				break;
			}
			case 24100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000800);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000820, EnemyEtis);
				break;
			}
			case 24130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000801);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000821, EnemyEtis);
				break;
			}
			case 24160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000802);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000822, EnemyEtis);
				break;
			}
			case 24190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000803);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000823, EnemyEtis);
				break;
			}
			case 24220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000804);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000824, EnemyEtis);
				break;
			}
			case 24250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000805);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000825, EnemyEtis);
				break;
			}
			case 24280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000806);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000826, EnemyEtis);
				break;
			}
			case 24310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000807);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000827, EnemyEtis);
				break;
			}
			case 24340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000808);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000828, EnemyEtis);
				break;
			}
			case 24370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000809);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000829, EnemyEtis);
				break;
			}
			case 24400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000810);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000830, EnemyEtis);
				break;
			}
			case 24430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000811);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000831, EnemyEtis);
				break;
			}
			case 24460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000812);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000832, EnemyEtis);
				break;
			}
			case 24490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000813);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000833, EnemyEtis);
				break;
			}
			case 24520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000814);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000834, EnemyEtis);
				break;
			}
			case 24550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000815);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000835, EnemyEtis);
				break;
			}
			case 24580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000816);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000836, EnemyEtis);
				break;
			}
			case 24610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000817);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000837, EnemyEtis);
				break;
			}
			case 24640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000818);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000838, EnemyEtis);
				break;
			}
			case 24670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000819);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000839, EnemyEtis);
				break;
			}
			case 24700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000820);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000840, EnemyEtis);
				break;
			}
			case 24730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000821);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000841, EnemyEtis);
				break;
			}
			case 24760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000822);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000842, EnemyEtis);
				break;
			}
			case 24790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000823);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000843, EnemyEtis);
				break;
			}
			case 24820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000824);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000844, EnemyEtis);
				break;
			}
			case 24850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000825);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000845, EnemyEtis);
				break;
			}
			case 24880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000826);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000846, EnemyEtis);
				break;
			}
			case 24910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000827);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000847, EnemyEtis);
				break;
			}
			case 24940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000828);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000848, EnemyEtis);
				break;
			}
			case 24970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000829);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000849, EnemyEtis);
				break;
			}
			case 25000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000830);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000850, EnemyEtis);
				break;
			}
			case 25030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000831);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000851, EnemyEtis);
				break;
			}
			case 25060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000832);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000852, EnemyEtis);
				break;
			}
			case 25090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000833);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000853, EnemyEtis);
				break;
			}
			case 25120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000834);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000854, EnemyEtis);
				break;
			}
			case 25150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000835);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000855, EnemyEtis);
				break;
			}
			case 25180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000836);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000856, EnemyEtis);
				break;
			}
			case 25210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000837);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000857, EnemyEtis);
				break;
			}
			case 25240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000838);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000858, EnemyEtis);
				break;
			}
			case 25270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000839);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000859, EnemyEtis);
				break;
			}
			case 25300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000840);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000860, EnemyEtis);
				break;
			}
			case 25330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000841);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000861, EnemyEtis);
				break;
			}
			case 25360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000842);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000862, EnemyEtis);
				break;
			}
			case 25390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000843);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000863, EnemyEtis);
				break;
			}
			case 25420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000844);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000864, EnemyEtis);
				break;
			}
			case 25450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000845);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000865, EnemyEtis);
				break;
			}
			case 25480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000846);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000866, EnemyEtis);
				break;
			}
			case 25510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000847);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000867, EnemyEtis);
				break;
			}
			case 25540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000848);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000868, EnemyEtis);
				break;
			}
			case 25570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000849);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000869, EnemyEtis);
				break;
			}
			case 25600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000850);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000870, EnemyEtis);
				break;
			}
			case 25630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000851);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000871, EnemyEtis);
				break;
			}
			case 25660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000852);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000872, EnemyEtis);
				break;
			}
			case 25690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000853);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000873, EnemyEtis);
				break;
			}
			case 25720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000854);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000874, EnemyEtis);
				break;
			}
			case 25750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000855);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000875, EnemyEtis);
				break;
			}
			case 25780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000856);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000876, EnemyEtis);
				break;
			}
			case 25810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000857);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000877, EnemyEtis);
				break;
			}
			case 25840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000858);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000878, EnemyEtis);
				break;
			}
			case 25870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000859);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000879, EnemyEtis);
				break;
			}
			case 25900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000860);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000880, EnemyEtis);
				break;
			}
			case 25930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000861);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000881, EnemyEtis);
				break;
			}
			case 25960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000862);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000882, EnemyEtis);
				break;
			}
			case 25990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000863);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000883, EnemyEtis);
				break;
			}
			case 26020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000864);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000884, EnemyEtis);
				break;
			}
			case 26050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000865);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000885, EnemyEtis);
				break;
			}
			case 26080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000866);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000886, EnemyEtis);
				break;
			}
			case 26110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000867);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000887, EnemyEtis);
				break;
			}
			case 26140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000868);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000888, EnemyEtis);
				break;
			}
			case 26170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000869);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000889, EnemyEtis);
				break;
			}
			case 26200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000870);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000890, EnemyEtis);
				break;
			}
			case 26230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000871);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000891, EnemyEtis);
				break;
			}
			case 26260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000872);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000892, EnemyEtis);
				break;
			}
			case 26290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000873);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000893, EnemyEtis);
				break;
			}
			case 26320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000874);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000894, EnemyEtis);
				break;
			}
			case 26350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000875);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000895, EnemyEtis);
				break;
			}
			case 26380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000876);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000896, EnemyEtis);
				break;
			}
			case 26410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000877);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000897, EnemyEtis);
				break;
			}
			case 26440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000878);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000898, EnemyEtis);
				break;
			}
			case 26470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000879);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000899, EnemyEtis);
				break;
			}
			case 26500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000880);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000900, EnemyEtis);
				break;
			}
			case 26530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000881);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000901, EnemyEtis);
				break;
			}
			case 26560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000882);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000902, EnemyEtis);
				break;
			}
			case 26590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000883);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000903, EnemyEtis);
				break;
			}
			case 26620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000884);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000904, EnemyEtis);
				break;
			}
			case 26650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000885);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000905, EnemyEtis);
				break;
			}
			case 26680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000886);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000906, EnemyEtis);
				break;
			}
			case 26710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000887);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000907, EnemyEtis);
				break;
			}
			case 26740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000888);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000908, EnemyEtis);
				break;
			}
			case 26770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000889);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000909, EnemyEtis);
				break;
			}
			case 26800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000890);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000910, EnemyEtis);
				break;
			}
			case 26830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000891);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000911, EnemyEtis);
				break;
			}
			case 26860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000892);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000912, EnemyEtis);
				break;
			}
			case 26890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000893);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000913, EnemyEtis);
				break;
			}
			case 26920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000894);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000914, EnemyEtis);
				break;
			}
			case 26950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000895);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000915, EnemyEtis);
				break;
			}
			case 26980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000896);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000916, EnemyEtis);
				break;
			}
			case 27010: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000897);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000917, EnemyEtis);
				break;
			}
			case 27040: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000898);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000918, EnemyEtis);
				break;
			}
			case 27070: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000899);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000919, EnemyEtis);
				break;
			}
			case 27100: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000900);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000920, EnemyEtis);
				break;
			}
			case 27130: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000901);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000921, EnemyEtis);
				break;
			}
			case 27160: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000902);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000922, EnemyEtis);
				break;
			}
			case 27190: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000903);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000923, EnemyEtis);
				break;
			}
			case 27220: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000904);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000924, EnemyEtis);
				break;
			}
			case 27250: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000905);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000925, EnemyEtis);
				break;
			}
			case 27280: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000906);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000926, EnemyEtis);
				break;
			}
			case 27310: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000907);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000927, EnemyEtis);
				break;
			}
			case 27340: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000908);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000928, EnemyEtis);
				break;
			}
			case 27370: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000909);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000929, EnemyEtis);
				break;
			}
			case 27400: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000910);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000930, EnemyEtis);
				break;
			}
			case 27430: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000911);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000931, EnemyEtis);
				break;
			}
			case 27460: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000912);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000932, EnemyEtis);
				break;
			}
			case 27490: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000913);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000933, EnemyEtis);
				break;
			}
			case 27520: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000914);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000934, EnemyEtis);
				break;
			}
			case 27550: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000915);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000935, EnemyEtis);
				break;
			}
			case 27580: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000916);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000936, EnemyEtis);
				break;
			}
			case 27610: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000917);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000937, EnemyEtis);
				break;
			}
			case 27640: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000918);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000938, EnemyEtis);
				break;
			}
			case 27670: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000919);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000939, EnemyEtis);
				break;
			}
			case 27700: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000920);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000940, EnemyEtis);
				break;
			}
			case 27730: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000921);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000941, EnemyEtis);
				break;
			}
			case 27760: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000922);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000942, EnemyEtis);
				break;
			}
			case 27790: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000923);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000943, EnemyEtis);
				break;
			}
			case 27820: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000924);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000944, EnemyEtis);
				break;
			}
			case 27850: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000925);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000945, EnemyEtis);
				break;
			}
			case 27880: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000926);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000946, EnemyEtis);
				break;
			}
			case 27910: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000927);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000947, EnemyEtis);
				break;
			}
			case 27940: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000928);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000948, EnemyEtis);
				break;
			}
			case 27970: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000929);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000949, EnemyEtis);
				break;
			}
			case 28000: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000930);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000950, EnemyEtis);
				break;
			}
			case 28030: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000931);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000951, EnemyEtis);
				break;
			}
			case 28060: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000932);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000952, EnemyEtis);
				break;
			}
			case 28090: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000933);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000953, EnemyEtis);
				break;
			}
			case 28120: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000934);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000954, EnemyEtis);
				break;
			}
			case 28150: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000935);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000955, EnemyEtis);
				break;
			}
			case 28180: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000936);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000956, EnemyEtis);
				break;
			}
			case 28210: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000937);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000957, EnemyEtis);
				break;
			}
			case 28240: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000938);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000958, EnemyEtis);
				break;
			}
			case 28270: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000939);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000959, EnemyEtis);
				break;
			}
			case 28300: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000940);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000960, EnemyEtis);
				break;
			}
			case 28330: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000941);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000961, EnemyEtis);
				break;
			}
			case 28360: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000942);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000962, EnemyEtis);
				break;
			}
			case 28390: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000943);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000963, EnemyEtis);
				break;
			}
			case 28420: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000944);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000964, EnemyEtis);
				break;
			}
			case 28450: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000945);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000965, EnemyEtis);
				break;
			}
			case 28480: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000946);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000966, EnemyEtis);
				break;
			}
			case 28510: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000947);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000967, EnemyEtis);
				break;
			}
			case 28540: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000948);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000968, EnemyEtis);
				break;
			}
			case 28570: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000949);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000969, EnemyEtis);
				break;
			}
			case 28600: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000950);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000970, EnemyEtis);
				break;
			}
			case 28630: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000951);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000971, EnemyEtis);
				break;
			}
			case 28660: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000952);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000972, EnemyEtis);
				break;
			}
			case 28690: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000953);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000973, EnemyEtis);
				break;
			}
			case 28720: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000954);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000974, EnemyEtis);
				break;
			}
			case 28750: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000955);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000975, EnemyEtis);
				break;
			}
			case 28780: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000956);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000976, EnemyEtis);
				break;
			}
			case 28810: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000957);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000977, EnemyEtis);
				break;
			}
			case 28840: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000958);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000978, EnemyEtis);
				break;
			}
			case 28870: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000959);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000979, EnemyEtis);
				break;
			}
			case 28900: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000960);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000980, EnemyEtis);
				break;
			}
			case 28930: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000961);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000981, EnemyEtis);
				break;
			}
			case 28960: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000962);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000982, EnemyEtis);
				break;
			}
			case 28990: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000963);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000983, EnemyEtis);
				break;
			}
			case 29020: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000964);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000984, EnemyEtis);
				break;
			}
			case 29050: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000965);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000985, EnemyEtis);
				break;
			}
			case 29080: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000966);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000986, EnemyEtis);
				break;
			}
			case 29110: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000967);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000987, EnemyEtis);
				break;
			}
			case 29140: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000968);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000988, EnemyEtis);
				break;
			}
			case 29170: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000969);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000989, EnemyEtis);
				break;
			}
			case 29200: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000970);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000990, EnemyEtis);
				break;
			}
			case 29230: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000971);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000991, EnemyEtis);
				break;
			}
			case 29260: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000972);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000992, EnemyEtis);
				break;
			}
			case 29290: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000973);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000993, EnemyEtis);
				break;
			}
			case 29320: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000974);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000994, EnemyEtis);
				break;
			}
			case 29350: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000975);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000995, EnemyEtis);
				break;
			}
			case 29380: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000976);
				getSceneChief()->appendGroupChild(pEtis);
				requestActor(30000996, EnemyEtis);
				break;
			}
			case 29410: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000977);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29440: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000978);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29470: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000979);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29500: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000980);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29530: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000981);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29560: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000982);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29590: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000983);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29620: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000984);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29650: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000985);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29680: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000986);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29710: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000987);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29740: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000988);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29770: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000989);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29800: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000990);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29830: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000991);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29860: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000992);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29890: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000993);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29920: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000994);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29950: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000995);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			case 29980: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(30000996);
				getSceneChief()->appendGroupChild(pEtis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1019-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

StageDebugPart02::~StageDebugPart02() {

}
