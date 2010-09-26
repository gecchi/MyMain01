#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2110,2140,2170,2200,2230,2260,2290,2320,2350,2380,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4120,4150,4180,4210,4240,4270,4300,4330,4360,4390,4420,4450,4480,4510,4540,4570,4600,4630,4660,4690,4720,4750,4780,4810,4840,4870,4900,4930,4960,4990,5020,5050,5080,5110,5140,5170,5200,5230,5260,5290,5320,5350,5380,5410,5440,5470,5500,5530,5560,5590,5620,5650,5680,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8410,8440,8470,8500,8530,8560,8590,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8920,8950,8980,9010,9040,9070,9100,9130,9160,9190,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10030,10060,10090,10120,10150,10180,10210,10240,10270,10300,10330,10360,10390,10420,10450,10480,10510,10540,10570,10600,10630,10660,10690,10720,10750,10780,10810,10840,10870,10900,10930,10960,10990,11020,11050,11080,11110,11140,11170,11200,11230,11260,11290,11320,11350,11380,11410,11440,11470,11500,11530,11560,11590,11620,11650,11680,11710,11740,11770,11800,11830,11860,11890,11920,11950,11980,12010,12040,12070,12100,12130,12160,12190,12220,12250,12280,12310,12340,12370,12400,12430,12460,12490,12520,12550,12580,12610,12640,12670,12700,12730,12760,12790,12820,12850,12880,12910,12940,12970,13000,13030,13060,13090,13120,13150,13180,13210,13240,13270,13300,13330,13360,13390,13420,13450,13480,13510,13540,13570,13600,13630,13660,13690,13720,13750,13780,13810,13840,13870,13900,13930,13960,13990,14020,14050,14080,14110,14140,14170,14200,14230,14260,14290,14320,14350,14380,14410,14440,14470,14500,14530,14560,14590,14620,14650,14680,14710,14740,14770,14800,14830,14860,14890,14920,14950,14980,15010,15040,15070,15100,15130,15160,15190,15220,15250,15280,15310,15340,15370,15400,15430,15460,15490,15520,15550,15580,15610,15640,15670,15700,15730,15760,15790,15820,15850,15880,15910,15940,15970,16000,16030,16060,16090,16120,16150,16180,16210,16240,16270,16300,16330,16360,16390,16420,16450,16480,16510,16540,16570,16600,16630,16660,16690,16720,16750,16780,16810,16840,16870,16900,16930,16960,16990,17020,17050,17080,17110,17140,17170,17200,17230,17260,17290,17320,17350,17380,17410,17440,17470,17500,17530,17560,17590,17620,17650,17680,17710,17740,17770,17800,17830,17860,17890,17920,17950,17980,18010,18040,18070,18100,18130,18160,18190,18220,18250,18280,18310,18340,18370,18400,18430,18460,18490,18520,18550,18580,18610,18640,18670,18700,18730,18760,18790,18820,18850,18880,18910,18940,18970,19000,19030,19060,19090,19120,19150,19180,19210,19240,19270,19300,19330,19360,19390,19420,19450,19480,19510,19540,19570,19600,19630,19660,19690,19720,19750,19780,19810,19840,19870,19900,19930,19960,19990,20020,20050,20080,20110,20140,20170,20200,20230,20260,20290,20320,20350,20380,20410,20440,20470,20500,20530,20560,20590,20620,20650,20680,20710,20740,20770,20800,20830,20860,20890,20920,20950,20980,21010,21040,21070,21100,21130,21160,21190,21220,21250,21280,21310,21340,21370,21400,21430,21460,21490,21520,21550,21580,21610,21640,21670,21700,21730,21760,21790,21820,21850,21880,21910,21940,21970,22000,22030,22060,22090,22120,22150,22180,22210,22240,22270,22300,22330,22360,22390,22420,22450,22480,22510,22540,22570,22600,22630,22660,22690,22720,22750,22780,22810,22840,22870,22900,22930,22960,22990,23020,23050,23080,23110,23140,23170,23200,23230,23260,23290,23320,23350,23380,23410,23440,23470,23500,23530,23560,23590,23620,23650,23680,23710,23740,23770,23800,23830,23860,23890,23920,23950,23980,24010,24040,24070,24100,24130,24160,24190,24220,24250,24280,24310,24340,24370,24400,24430,24460,24490,24520,24550,24580,24610,24640,24670,24700,24730,24760,24790,24820,24850,24880,24910,24940,24970,25000,25030,25060,25090,25120,25150,25180,25210,25240,25270,25300,25330,25360,25390,25420,25450,25480,25510,25540,25570,25600,25630,25660,25690,25720,25750,25780,25810,25840,25870,25900,25930,25960,25990,26020,26050,26080,26110,26140,26170,26200,26230,26260,26290,26320,26350,26380,26410,26440,26470,26500,26530,26560,26590,26620,26650,26680,26710,26740,26770,26800,26830,26860,26890,26920,26950,26980,27010,27040,27070,27100,27130,27160,27190,27220,27250,27280,27310,27340,27370,27400,27430,27460,27490,27520,27550,27580,27610,27640,27670,27700,27730,27760,27790,27820,27850,27880,27910,27940,27970,28000,28030,28060,28090,28120,28150,28180,28210,28240,28270,28300,28330,28360,28390,28420,28450,28480,28510,28540,28570,28600,28630,28660,28690,28720,28750,28780,28810,28840,28870,28900,28930,28960,28990,29020,29050,29080,29110,29140,29170,29200,29230,29260,29290,29320,29350,29380,29410,29440,29470,29500,29530,29560,29590,29620,29650,29680,29710,29740,29770,29800,29830,29860,29890,29920,29950,29980,30000};
	_paFrame_NextEvent = new frame[1002];
	for (int i = 0; i < 1002; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(21047100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(21057100, FormationPallas001d, "F001d_Pallas_2");
	orderActorToFactory(21067100, FormationPallas001b, "F001b_Pallas_3");
	orderActorToFactory(21077100, FormationPallas001c, "F001c_Pallas_4");
	orderActorToFactory(21087100, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(21097100, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(21107100, FormationPallas001b, "F001b_Pallas_7");
	orderActorToFactory(21117100, FormationPallas001c, "F001c_Pallas_8");
	orderActorToFactory(21127100, FormationPallas001a, "F001a_Pallas_9");
	orderActorToFactory(21137100, FormationPallas001d, "F001d_Pallas_10");
	orderActorToFactory(21147100, FormationPallas001b, "F001b_Pallas_11");
	orderActorToFactory(21157100, FormationPallas001c, "F001c_Pallas_12");
	orderActorToFactory(21177100, EnemyMetis, "Metis_13");
	orderActorToFactory(21177130, EnemyMetis, "Metis_14");
	orderActorToFactory(21177160, EnemyMetis, "Metis_15");
	orderActorToFactory(21177190, EnemyMetis, "Metis_16");
	orderActorToFactory(21177220, EnemyMetis, "Metis_17");
	orderActorToFactory(21177250, EnemyMetis, "Metis_18");
	orderActorToFactory(21177280, EnemyMetis, "Metis_19");
	orderActorToFactory(21177310, EnemyMetis, "Metis_20");
	orderActorToFactory(21177340, EnemyMetis, "Metis_21");
	orderActorToFactory(21177370, EnemyMetis, "Metis_22");
	orderActorToFactory(21177400, EnemyMetis, "Metis_23");
	orderActorToFactory(21177430, EnemyMetis, "Metis_24");
	orderActorToFactory(21177460, EnemyMetis, "Metis_25");
	orderActorToFactory(21177490, EnemyMetis, "Metis_26");
	orderActorToFactory(21177520, EnemyMetis, "Metis_27");
	orderActorToFactory(21177550, EnemyMetis, "Metis_28");
	orderActorToFactory(21177580, EnemyMetis, "Metis_29");
	orderActorToFactory(21177610, EnemyMetis, "Metis_30");
	orderActorToFactory(21177640, EnemyMetis, "Metis_31");
	orderActorToFactory(21177670, EnemyMetis, "Metis_32");
	orderActorToFactory(21177700, EnemyMetis, "Metis_33");
	orderActorToFactory(21177730, EnemyMetis, "Metis_34");
	orderActorToFactory(21177760, EnemyMetis, "Metis_35");
	orderActorToFactory(21177790, EnemyMetis, "Metis_36");
	orderActorToFactory(21177820, EnemyMetis, "Metis_37");
	orderActorToFactory(21177850, EnemyMetis, "Metis_38");
	orderActorToFactory(21177880, EnemyMetis, "Metis_39");
	orderActorToFactory(21177910, EnemyMetis, "Metis_40");
	orderActorToFactory(21177940, EnemyMetis, "Metis_41");
	orderActorToFactory(21177970, EnemyMetis, "Metis_42");
	orderActorToFactory(211771000, EnemyMetis, "Metis_43");
	orderActorToFactory(211771030, EnemyMetis, "Metis_44");
	orderActorToFactory(211771060, EnemyMetis, "Metis_45");
	orderActorToFactory(211771090, EnemyMetis, "Metis_46");
	orderActorToFactory(211771120, EnemyMetis, "Metis_47");
	orderActorToFactory(211771150, EnemyMetis, "Metis_48");
	orderActorToFactory(211771180, EnemyMetis, "Metis_49");
	orderActorToFactory(211771210, EnemyMetis, "Metis_50");
	orderActorToFactory(211771240, EnemyMetis, "Metis_51");
	orderActorToFactory(211771270, EnemyMetis, "Metis_52");
	orderActorToFactory(211771300, EnemyMetis, "Metis_53");
	orderActorToFactory(211771330, EnemyMetis, "Metis_54");
	orderActorToFactory(211771360, EnemyMetis, "Metis_55");
	orderActorToFactory(211771390, EnemyMetis, "Metis_56");
	orderActorToFactory(211771420, EnemyMetis, "Metis_57");
	orderActorToFactory(211771450, EnemyMetis, "Metis_58");
	orderActorToFactory(211771480, EnemyMetis, "Metis_59");
	orderActorToFactory(211771510, EnemyMetis, "Metis_60");
	orderActorToFactory(211771540, EnemyMetis, "Metis_61");
	orderActorToFactory(211771570, EnemyMetis, "Metis_62");
	orderActorToFactory(211771600, EnemyMetis, "Metis_63");
	orderActorToFactory(211771630, EnemyMetis, "Metis_64");
	orderActorToFactory(211771660, EnemyMetis, "Metis_65");
	orderActorToFactory(211771690, EnemyMetis, "Metis_66");
	orderActorToFactory(211771720, EnemyMetis, "Metis_67");
	orderActorToFactory(211771750, EnemyMetis, "Metis_68");
	orderActorToFactory(211771780, EnemyMetis, "Metis_69");
	orderActorToFactory(21226100, EnemyAstraea, "Astraea_70");
	orderActorToFactory(21226400, EnemyAstraea, "Astraea_71");
	orderActorToFactory(21226700, EnemyAstraea, "Astraea_72");
	orderActorToFactory(212261000, EnemyAstraea, "Astraea_73");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 10:
				orderActorToFactory(211771810, EnemyMetis, "Metis_74");
				break;
			case 40:
				orderActorToFactory(211771840, EnemyMetis, "Metis_75");
				break;
			case 70:
				orderActorToFactory(211771870, EnemyMetis, "Metis_76");
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_77");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21047100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21057100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21067100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21077100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21087100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21097100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21107100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21117100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21127100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21137100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21147100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21157100)), 400);
				}
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771900, EnemyMetis, "Metis_78");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(21226100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771930, EnemyMetis, "Metis_79");
				break;
			case 160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771960, EnemyMetis, "Metis_80");
				break;
			case 190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771990, EnemyMetis, "Metis_81");
				break;
			case 220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772020, EnemyMetis, "Metis_82");
				break;
			case 250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772050, EnemyMetis, "Metis_83");
				break;
			case 280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772080, EnemyMetis, "Metis_84");
				break;
			case 310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772110, EnemyMetis, "Metis_85");
				break;
			case 340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772140, EnemyMetis, "Metis_86");
				break;
			case 370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772170, EnemyMetis, "Metis_87");
				break;
			case 400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772200, EnemyMetis, "Metis_88");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(21226400);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772230, EnemyMetis, "Metis_89");
				break;
			case 460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772260, EnemyMetis, "Metis_90");
				break;
			case 490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772290, EnemyMetis, "Metis_91");
				break;
			case 520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772320, EnemyMetis, "Metis_92");
				break;
			case 550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772350, EnemyMetis, "Metis_93");
				break;
			case 580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772380, EnemyMetis, "Metis_94");
				break;
			case 610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772410, EnemyMetis, "Metis_95");
				break;
			case 640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772440, EnemyMetis, "Metis_96");
				break;
			case 670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772470, EnemyMetis, "Metis_97");
				break;
			case 700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772500, EnemyMetis, "Metis_98");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(21226700);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772530, EnemyMetis, "Metis_99");
				break;
			case 760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772560, EnemyMetis, "Metis_100");
				break;
			case 790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772590, EnemyMetis, "Metis_101");
				break;
			case 820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772620, EnemyMetis, "Metis_102");
				break;
			case 850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772650, EnemyMetis, "Metis_103");
				break;
			case 880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772680, EnemyMetis, "Metis_104");
				break;
			case 910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772710, EnemyMetis, "Metis_105");
				break;
			case 940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772740, EnemyMetis, "Metis_106");
				break;
			case 970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772770, EnemyMetis, "Metis_107");
				break;
			case 1000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772800, EnemyMetis, "Metis_108");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(212261000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 1030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772830, EnemyMetis, "Metis_109");
				break;
			case 1060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772860, EnemyMetis, "Metis_110");
				break;
			case 1090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772890, EnemyMetis, "Metis_111");
				break;
			case 1120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772920, EnemyMetis, "Metis_112");
				break;
			case 1150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772950, EnemyMetis, "Metis_113");
				break;
			case 1180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772980, EnemyMetis, "Metis_114");
				break;
			case 1210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773010, EnemyMetis, "Metis_115");
				break;
			case 1240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773040, EnemyMetis, "Metis_116");
				break;
			case 1270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773070, EnemyMetis, "Metis_117");
				break;
			case 1300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773100, EnemyMetis, "Metis_118");
				break;
			case 1330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773130, EnemyMetis, "Metis_119");
				break;
			case 1360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773160, EnemyMetis, "Metis_120");
				break;
			case 1390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773190, EnemyMetis, "Metis_121");
				break;
			case 1420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773220, EnemyMetis, "Metis_122");
				break;
			case 1450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773250, EnemyMetis, "Metis_123");
				break;
			case 1480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773280, EnemyMetis, "Metis_124");
				break;
			case 1510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773310, EnemyMetis, "Metis_125");
				break;
			case 1540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773340, EnemyMetis, "Metis_126");
				break;
			case 1570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773370, EnemyMetis, "Metis_127");
				break;
			case 1600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773400, EnemyMetis, "Metis_128");
				break;
			case 1630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773430, EnemyMetis, "Metis_129");
				break;
			case 1660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773460, EnemyMetis, "Metis_130");
				break;
			case 1690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773490, EnemyMetis, "Metis_131");
				break;
			case 1720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773520, EnemyMetis, "Metis_132");
				break;
			case 1750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773550, EnemyMetis, "Metis_133");
				break;
			case 1780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773580, EnemyMetis, "Metis_134");
				break;
			case 1810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773610, EnemyMetis, "Metis_135");
				break;
			case 1840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773640, EnemyMetis, "Metis_136");
				break;
			case 1870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773670, EnemyMetis, "Metis_137");
				break;
			case 1900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773700, EnemyMetis, "Metis_138");
				break;
			case 1930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773730, EnemyMetis, "Metis_139");
				break;
			case 1960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773760, EnemyMetis, "Metis_140");
				break;
			case 1990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773790, EnemyMetis, "Metis_141");
				break;
			case 2020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773820, EnemyMetis, "Metis_142");
				break;
			case 2050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773850, EnemyMetis, "Metis_143");
				break;
			case 2080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773880, EnemyMetis, "Metis_144");
				break;
			case 2110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773910, EnemyMetis, "Metis_145");
				break;
			case 2140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773940, EnemyMetis, "Metis_146");
				break;
			case 2170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773970, EnemyMetis, "Metis_147");
				break;
			case 2200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774000, EnemyMetis, "Metis_148");
				break;
			case 2230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774030, EnemyMetis, "Metis_149");
				break;
			case 2260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774060, EnemyMetis, "Metis_150");
				break;
			case 2290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774090, EnemyMetis, "Metis_151");
				break;
			case 2320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774120, EnemyMetis, "Metis_152");
				break;
			case 2350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774150, EnemyMetis, "Metis_153");
				break;
			case 2380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774180, EnemyMetis, "Metis_154");
				break;
			case 2410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774210, EnemyMetis, "Metis_155");
				break;
			case 2440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774240, EnemyMetis, "Metis_156");
				break;
			case 2470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774270, EnemyMetis, "Metis_157");
				break;
			case 2500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774300, EnemyMetis, "Metis_158");
				break;
			case 2530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774330, EnemyMetis, "Metis_159");
				break;
			case 2560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774360, EnemyMetis, "Metis_160");
				break;
			case 2590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774390, EnemyMetis, "Metis_161");
				break;
			case 2620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774420, EnemyMetis, "Metis_162");
				break;
			case 2650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774450, EnemyMetis, "Metis_163");
				break;
			case 2680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774480, EnemyMetis, "Metis_164");
				break;
			case 2710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774510, EnemyMetis, "Metis_165");
				break;
			case 2740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774540, EnemyMetis, "Metis_166");
				break;
			case 2770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774570, EnemyMetis, "Metis_167");
				break;
			case 2800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774600, EnemyMetis, "Metis_168");
				break;
			case 2830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774630, EnemyMetis, "Metis_169");
				break;
			case 2860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774660, EnemyMetis, "Metis_170");
				break;
			case 2890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774690, EnemyMetis, "Metis_171");
				break;
			case 2920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774720, EnemyMetis, "Metis_172");
				break;
			case 2950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774750, EnemyMetis, "Metis_173");
				break;
			case 2980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774780, EnemyMetis, "Metis_174");
				break;
			case 3010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774810, EnemyMetis, "Metis_175");
				break;
			case 3040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774840, EnemyMetis, "Metis_176");
				break;
			case 3070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774870, EnemyMetis, "Metis_177");
				break;
			case 3100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774900, EnemyMetis, "Metis_178");
				break;
			case 3130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774930, EnemyMetis, "Metis_179");
				break;
			case 3160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774960, EnemyMetis, "Metis_180");
				break;
			case 3190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774990, EnemyMetis, "Metis_181");
				break;
			case 3220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775020, EnemyMetis, "Metis_182");
				break;
			case 3250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775050, EnemyMetis, "Metis_183");
				break;
			case 3280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775080, EnemyMetis, "Metis_184");
				break;
			case 3310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775110, EnemyMetis, "Metis_185");
				break;
			case 3340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775140, EnemyMetis, "Metis_186");
				break;
			case 3370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775170, EnemyMetis, "Metis_187");
				break;
			case 3400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775200, EnemyMetis, "Metis_188");
				break;
			case 3430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775230, EnemyMetis, "Metis_189");
				break;
			case 3460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775260, EnemyMetis, "Metis_190");
				break;
			case 3490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775290, EnemyMetis, "Metis_191");
				break;
			case 3520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775320, EnemyMetis, "Metis_192");
				break;
			case 3550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775350, EnemyMetis, "Metis_193");
				break;
			case 3580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775380, EnemyMetis, "Metis_194");
				break;
			case 3610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775410, EnemyMetis, "Metis_195");
				break;
			case 3640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775440, EnemyMetis, "Metis_196");
				break;
			case 3670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775470, EnemyMetis, "Metis_197");
				break;
			case 3700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775500, EnemyMetis, "Metis_198");
				break;
			case 3730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775530, EnemyMetis, "Metis_199");
				break;
			case 3760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775560, EnemyMetis, "Metis_200");
				break;
			case 3790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775590, EnemyMetis, "Metis_201");
				break;
			case 3820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775620, EnemyMetis, "Metis_202");
				break;
			case 3850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775650, EnemyMetis, "Metis_203");
				break;
			case 3880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775680, EnemyMetis, "Metis_204");
				break;
			case 3910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775710, EnemyMetis, "Metis_205");
				break;
			case 3940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775740, EnemyMetis, "Metis_206");
				break;
			case 3970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775770, EnemyMetis, "Metis_207");
				break;
			case 4000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775800, EnemyMetis, "Metis_208");
				break;
			case 4030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775830, EnemyMetis, "Metis_209");
				break;
			case 4060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775860, EnemyMetis, "Metis_210");
				break;
			case 4090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775890, EnemyMetis, "Metis_211");
				break;
			case 4120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775920, EnemyMetis, "Metis_212");
				break;
			case 4150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775950, EnemyMetis, "Metis_213");
				break;
			case 4180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775980, EnemyMetis, "Metis_214");
				break;
			case 4210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776010, EnemyMetis, "Metis_215");
				break;
			case 4240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776040, EnemyMetis, "Metis_216");
				break;
			case 4270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776070, EnemyMetis, "Metis_217");
				break;
			case 4300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776100, EnemyMetis, "Metis_218");
				break;
			case 4330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776130, EnemyMetis, "Metis_219");
				break;
			case 4360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776160, EnemyMetis, "Metis_220");
				break;
			case 4390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776190, EnemyMetis, "Metis_221");
				break;
			case 4420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776220, EnemyMetis, "Metis_222");
				break;
			case 4450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776250, EnemyMetis, "Metis_223");
				break;
			case 4480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776280, EnemyMetis, "Metis_224");
				break;
			case 4510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776310, EnemyMetis, "Metis_225");
				break;
			case 4540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776340, EnemyMetis, "Metis_226");
				break;
			case 4570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776370, EnemyMetis, "Metis_227");
				break;
			case 4600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776400, EnemyMetis, "Metis_228");
				break;
			case 4630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776430, EnemyMetis, "Metis_229");
				break;
			case 4660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776460, EnemyMetis, "Metis_230");
				break;
			case 4690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776490, EnemyMetis, "Metis_231");
				break;
			case 4720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776520, EnemyMetis, "Metis_232");
				break;
			case 4750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776550, EnemyMetis, "Metis_233");
				break;
			case 4780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776580, EnemyMetis, "Metis_234");
				break;
			case 4810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776610, EnemyMetis, "Metis_235");
				break;
			case 4840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776640, EnemyMetis, "Metis_236");
				break;
			case 4870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776670, EnemyMetis, "Metis_237");
				break;
			case 4900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776700, EnemyMetis, "Metis_238");
				break;
			case 4930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776730, EnemyMetis, "Metis_239");
				break;
			case 4960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776760, EnemyMetis, "Metis_240");
				break;
			case 4990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776790, EnemyMetis, "Metis_241");
				break;
			case 5020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776820, EnemyMetis, "Metis_242");
				break;
			case 5050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776850, EnemyMetis, "Metis_243");
				break;
			case 5080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776880, EnemyMetis, "Metis_244");
				break;
			case 5110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776910, EnemyMetis, "Metis_245");
				break;
			case 5140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776940, EnemyMetis, "Metis_246");
				break;
			case 5170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776970, EnemyMetis, "Metis_247");
				break;
			case 5200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777000, EnemyMetis, "Metis_248");
				break;
			case 5230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777030, EnemyMetis, "Metis_249");
				break;
			case 5260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777060, EnemyMetis, "Metis_250");
				break;
			case 5290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777090, EnemyMetis, "Metis_251");
				break;
			case 5320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777120, EnemyMetis, "Metis_252");
				break;
			case 5350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777150, EnemyMetis, "Metis_253");
				break;
			case 5380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777180, EnemyMetis, "Metis_254");
				break;
			case 5410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777210, EnemyMetis, "Metis_255");
				break;
			case 5440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777240, EnemyMetis, "Metis_256");
				break;
			case 5470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777270, EnemyMetis, "Metis_257");
				break;
			case 5500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777300, EnemyMetis, "Metis_258");
				break;
			case 5530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777330, EnemyMetis, "Metis_259");
				break;
			case 5560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777360, EnemyMetis, "Metis_260");
				break;
			case 5590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777390, EnemyMetis, "Metis_261");
				break;
			case 5620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777420, EnemyMetis, "Metis_262");
				break;
			case 5650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777450, EnemyMetis, "Metis_263");
				break;
			case 5680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777480, EnemyMetis, "Metis_264");
				break;
			case 5710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777510, EnemyMetis, "Metis_265");
				break;
			case 5740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777540, EnemyMetis, "Metis_266");
				break;
			case 5770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777570, EnemyMetis, "Metis_267");
				break;
			case 5800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777600, EnemyMetis, "Metis_268");
				break;
			case 5830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777630, EnemyMetis, "Metis_269");
				break;
			case 5860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777660, EnemyMetis, "Metis_270");
				break;
			case 5890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777690, EnemyMetis, "Metis_271");
				break;
			case 5920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777720, EnemyMetis, "Metis_272");
				break;
			case 5950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777750, EnemyMetis, "Metis_273");
				break;
			case 5980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777780, EnemyMetis, "Metis_274");
				break;
			case 6010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777810, EnemyMetis, "Metis_275");
				break;
			case 6040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777840, EnemyMetis, "Metis_276");
				break;
			case 6070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777870, EnemyMetis, "Metis_277");
				break;
			case 6100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777900, EnemyMetis, "Metis_278");
				break;
			case 6130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777930, EnemyMetis, "Metis_279");
				break;
			case 6160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777960, EnemyMetis, "Metis_280");
				break;
			case 6190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777990, EnemyMetis, "Metis_281");
				break;
			case 6220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778020, EnemyMetis, "Metis_282");
				break;
			case 6250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778050, EnemyMetis, "Metis_283");
				break;
			case 6280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778080, EnemyMetis, "Metis_284");
				break;
			case 6310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778110, EnemyMetis, "Metis_285");
				break;
			case 6340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778140, EnemyMetis, "Metis_286");
				break;
			case 6370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778170, EnemyMetis, "Metis_287");
				break;
			case 6400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778200, EnemyMetis, "Metis_288");
				break;
			case 6430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778230, EnemyMetis, "Metis_289");
				break;
			case 6460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778260, EnemyMetis, "Metis_290");
				break;
			case 6490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778290, EnemyMetis, "Metis_291");
				break;
			case 6520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778320, EnemyMetis, "Metis_292");
				break;
			case 6550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778350, EnemyMetis, "Metis_293");
				break;
			case 6580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778380, EnemyMetis, "Metis_294");
				break;
			case 6610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778410, EnemyMetis, "Metis_295");
				break;
			case 6640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778440, EnemyMetis, "Metis_296");
				break;
			case 6670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778470, EnemyMetis, "Metis_297");
				break;
			case 6700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778500, EnemyMetis, "Metis_298");
				break;
			case 6730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778530, EnemyMetis, "Metis_299");
				break;
			case 6760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778560, EnemyMetis, "Metis_300");
				break;
			case 6790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778590, EnemyMetis, "Metis_301");
				break;
			case 6820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778620, EnemyMetis, "Metis_302");
				break;
			case 6850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778650, EnemyMetis, "Metis_303");
				break;
			case 6880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778680, EnemyMetis, "Metis_304");
				break;
			case 6910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778710, EnemyMetis, "Metis_305");
				break;
			case 6940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778740, EnemyMetis, "Metis_306");
				break;
			case 6970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778770, EnemyMetis, "Metis_307");
				break;
			case 7000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778800, EnemyMetis, "Metis_308");
				break;
			case 7030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778830, EnemyMetis, "Metis_309");
				break;
			case 7060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778860, EnemyMetis, "Metis_310");
				break;
			case 7090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778890, EnemyMetis, "Metis_311");
				break;
			case 7120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778920, EnemyMetis, "Metis_312");
				break;
			case 7150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778950, EnemyMetis, "Metis_313");
				break;
			case 7180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778980, EnemyMetis, "Metis_314");
				break;
			case 7210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779010, EnemyMetis, "Metis_315");
				break;
			case 7240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779040, EnemyMetis, "Metis_316");
				break;
			case 7270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779070, EnemyMetis, "Metis_317");
				break;
			case 7300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779100, EnemyMetis, "Metis_318");
				break;
			case 7330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779130, EnemyMetis, "Metis_319");
				break;
			case 7360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779160, EnemyMetis, "Metis_320");
				break;
			case 7390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779190, EnemyMetis, "Metis_321");
				break;
			case 7420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779220, EnemyMetis, "Metis_322");
				break;
			case 7450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779250, EnemyMetis, "Metis_323");
				break;
			case 7480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779280, EnemyMetis, "Metis_324");
				break;
			case 7510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779310, EnemyMetis, "Metis_325");
				break;
			case 7540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779340, EnemyMetis, "Metis_326");
				break;
			case 7570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779370, EnemyMetis, "Metis_327");
				break;
			case 7600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779400, EnemyMetis, "Metis_328");
				break;
			case 7630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779430, EnemyMetis, "Metis_329");
				break;
			case 7660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779460, EnemyMetis, "Metis_330");
				break;
			case 7690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779490, EnemyMetis, "Metis_331");
				break;
			case 7720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779520, EnemyMetis, "Metis_332");
				break;
			case 7750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779550, EnemyMetis, "Metis_333");
				break;
			case 7780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779580, EnemyMetis, "Metis_334");
				break;
			case 7810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779610, EnemyMetis, "Metis_335");
				break;
			case 7840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779640, EnemyMetis, "Metis_336");
				break;
			case 7870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779670, EnemyMetis, "Metis_337");
				break;
			case 7900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779700, EnemyMetis, "Metis_338");
				break;
			case 7930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779730, EnemyMetis, "Metis_339");
				break;
			case 7960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779760, EnemyMetis, "Metis_340");
				break;
			case 7990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779790, EnemyMetis, "Metis_341");
				break;
			case 8020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779820, EnemyMetis, "Metis_342");
				break;
			case 8050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779850, EnemyMetis, "Metis_343");
				break;
			case 8080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779880, EnemyMetis, "Metis_344");
				break;
			case 8110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779910, EnemyMetis, "Metis_345");
				break;
			case 8140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779940, EnemyMetis, "Metis_346");
				break;
			case 8170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779970, EnemyMetis, "Metis_347");
				break;
			case 8200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710000, EnemyMetis, "Metis_348");
				break;
			case 8230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710030, EnemyMetis, "Metis_349");
				break;
			case 8260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710060, EnemyMetis, "Metis_350");
				break;
			case 8290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710090, EnemyMetis, "Metis_351");
				break;
			case 8320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710120, EnemyMetis, "Metis_352");
				break;
			case 8350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710150, EnemyMetis, "Metis_353");
				break;
			case 8380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710180, EnemyMetis, "Metis_354");
				break;
			case 8410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710210, EnemyMetis, "Metis_355");
				break;
			case 8440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710240, EnemyMetis, "Metis_356");
				break;
			case 8470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710270, EnemyMetis, "Metis_357");
				break;
			case 8500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710300, EnemyMetis, "Metis_358");
				break;
			case 8530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710330, EnemyMetis, "Metis_359");
				break;
			case 8560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710360, EnemyMetis, "Metis_360");
				break;
			case 8590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710390, EnemyMetis, "Metis_361");
				break;
			case 8620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710420, EnemyMetis, "Metis_362");
				break;
			case 8650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710450, EnemyMetis, "Metis_363");
				break;
			case 8680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710480, EnemyMetis, "Metis_364");
				break;
			case 8710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710510, EnemyMetis, "Metis_365");
				break;
			case 8740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710540, EnemyMetis, "Metis_366");
				break;
			case 8770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710570, EnemyMetis, "Metis_367");
				break;
			case 8800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710600, EnemyMetis, "Metis_368");
				break;
			case 8830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710630, EnemyMetis, "Metis_369");
				break;
			case 8860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710660, EnemyMetis, "Metis_370");
				break;
			case 8890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710690, EnemyMetis, "Metis_371");
				break;
			case 8920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710720, EnemyMetis, "Metis_372");
				break;
			case 8950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710750, EnemyMetis, "Metis_373");
				break;
			case 8980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710780, EnemyMetis, "Metis_374");
				break;
			case 9010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710810, EnemyMetis, "Metis_375");
				break;
			case 9040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710840, EnemyMetis, "Metis_376");
				break;
			case 9070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710870, EnemyMetis, "Metis_377");
				break;
			case 9100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710900, EnemyMetis, "Metis_378");
				break;
			case 9130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710930, EnemyMetis, "Metis_379");
				break;
			case 9160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710960, EnemyMetis, "Metis_380");
				break;
			case 9190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710990, EnemyMetis, "Metis_381");
				break;
			case 9220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711020, EnemyMetis, "Metis_382");
				break;
			case 9250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711050, EnemyMetis, "Metis_383");
				break;
			case 9280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711080, EnemyMetis, "Metis_384");
				break;
			case 9310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711110, EnemyMetis, "Metis_385");
				break;
			case 9340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711140, EnemyMetis, "Metis_386");
				break;
			case 9370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711170, EnemyMetis, "Metis_387");
				break;
			case 9400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711200, EnemyMetis, "Metis_388");
				break;
			case 9430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711230, EnemyMetis, "Metis_389");
				break;
			case 9460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711260, EnemyMetis, "Metis_390");
				break;
			case 9490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711290, EnemyMetis, "Metis_391");
				break;
			case 9520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711320, EnemyMetis, "Metis_392");
				break;
			case 9550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711350, EnemyMetis, "Metis_393");
				break;
			case 9580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711380, EnemyMetis, "Metis_394");
				break;
			case 9610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711410, EnemyMetis, "Metis_395");
				break;
			case 9640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711440, EnemyMetis, "Metis_396");
				break;
			case 9670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711470, EnemyMetis, "Metis_397");
				break;
			case 9700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711500, EnemyMetis, "Metis_398");
				break;
			case 9730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711530, EnemyMetis, "Metis_399");
				break;
			case 9760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711560, EnemyMetis, "Metis_400");
				break;
			case 9790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711590, EnemyMetis, "Metis_401");
				break;
			case 9820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711620, EnemyMetis, "Metis_402");
				break;
			case 9850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711650, EnemyMetis, "Metis_403");
				break;
			case 9880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711680, EnemyMetis, "Metis_404");
				break;
			case 9910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711710, EnemyMetis, "Metis_405");
				break;
			case 9940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711740, EnemyMetis, "Metis_406");
				break;
			case 9970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711770, EnemyMetis, "Metis_407");
				break;
			case 10000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711800, EnemyMetis, "Metis_408");
				break;
			case 10030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711830, EnemyMetis, "Metis_409");
				break;
			case 10060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711860, EnemyMetis, "Metis_410");
				break;
			case 10090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711890, EnemyMetis, "Metis_411");
				break;
			case 10120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711920, EnemyMetis, "Metis_412");
				break;
			case 10150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711950, EnemyMetis, "Metis_413");
				break;
			case 10180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117711980, EnemyMetis, "Metis_414");
				break;
			case 10210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712010, EnemyMetis, "Metis_415");
				break;
			case 10240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712040, EnemyMetis, "Metis_416");
				break;
			case 10270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712070, EnemyMetis, "Metis_417");
				break;
			case 10300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712100, EnemyMetis, "Metis_418");
				break;
			case 10330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712130, EnemyMetis, "Metis_419");
				break;
			case 10360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712160, EnemyMetis, "Metis_420");
				break;
			case 10390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712190, EnemyMetis, "Metis_421");
				break;
			case 10420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712220, EnemyMetis, "Metis_422");
				break;
			case 10450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712250, EnemyMetis, "Metis_423");
				break;
			case 10480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712280, EnemyMetis, "Metis_424");
				break;
			case 10510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712310, EnemyMetis, "Metis_425");
				break;
			case 10540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712340, EnemyMetis, "Metis_426");
				break;
			case 10570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712370, EnemyMetis, "Metis_427");
				break;
			case 10600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712400, EnemyMetis, "Metis_428");
				break;
			case 10630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712430, EnemyMetis, "Metis_429");
				break;
			case 10660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712460, EnemyMetis, "Metis_430");
				break;
			case 10690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712490, EnemyMetis, "Metis_431");
				break;
			case 10720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712520, EnemyMetis, "Metis_432");
				break;
			case 10750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712550, EnemyMetis, "Metis_433");
				break;
			case 10780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712580, EnemyMetis, "Metis_434");
				break;
			case 10810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712610, EnemyMetis, "Metis_435");
				break;
			case 10840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712640, EnemyMetis, "Metis_436");
				break;
			case 10870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712670, EnemyMetis, "Metis_437");
				break;
			case 10900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712700, EnemyMetis, "Metis_438");
				break;
			case 10930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712730, EnemyMetis, "Metis_439");
				break;
			case 10960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712760, EnemyMetis, "Metis_440");
				break;
			case 10990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712790, EnemyMetis, "Metis_441");
				break;
			case 11020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712820, EnemyMetis, "Metis_442");
				break;
			case 11050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712850, EnemyMetis, "Metis_443");
				break;
			case 11080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712880, EnemyMetis, "Metis_444");
				break;
			case 11110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712910, EnemyMetis, "Metis_445");
				break;
			case 11140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712940, EnemyMetis, "Metis_446");
				break;
			case 11170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117712970, EnemyMetis, "Metis_447");
				break;
			case 11200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713000, EnemyMetis, "Metis_448");
				break;
			case 11230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713030, EnemyMetis, "Metis_449");
				break;
			case 11260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713060, EnemyMetis, "Metis_450");
				break;
			case 11290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713090, EnemyMetis, "Metis_451");
				break;
			case 11320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713120, EnemyMetis, "Metis_452");
				break;
			case 11350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713150, EnemyMetis, "Metis_453");
				break;
			case 11380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713180, EnemyMetis, "Metis_454");
				break;
			case 11410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713210, EnemyMetis, "Metis_455");
				break;
			case 11440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713240, EnemyMetis, "Metis_456");
				break;
			case 11470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713270, EnemyMetis, "Metis_457");
				break;
			case 11500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713300, EnemyMetis, "Metis_458");
				break;
			case 11530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713330, EnemyMetis, "Metis_459");
				break;
			case 11560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713360, EnemyMetis, "Metis_460");
				break;
			case 11590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713390, EnemyMetis, "Metis_461");
				break;
			case 11620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713420, EnemyMetis, "Metis_462");
				break;
			case 11650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713450, EnemyMetis, "Metis_463");
				break;
			case 11680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713480, EnemyMetis, "Metis_464");
				break;
			case 11710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713510, EnemyMetis, "Metis_465");
				break;
			case 11740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713540, EnemyMetis, "Metis_466");
				break;
			case 11770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713570, EnemyMetis, "Metis_467");
				break;
			case 11800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713600, EnemyMetis, "Metis_468");
				break;
			case 11830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713630, EnemyMetis, "Metis_469");
				break;
			case 11860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713660, EnemyMetis, "Metis_470");
				break;
			case 11890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713690, EnemyMetis, "Metis_471");
				break;
			case 11920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713720, EnemyMetis, "Metis_472");
				break;
			case 11950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713750, EnemyMetis, "Metis_473");
				break;
			case 11980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117711980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713780, EnemyMetis, "Metis_474");
				break;
			case 12010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713810, EnemyMetis, "Metis_475");
				break;
			case 12040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713840, EnemyMetis, "Metis_476");
				break;
			case 12070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713870, EnemyMetis, "Metis_477");
				break;
			case 12100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713900, EnemyMetis, "Metis_478");
				break;
			case 12130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713930, EnemyMetis, "Metis_479");
				break;
			case 12160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713960, EnemyMetis, "Metis_480");
				break;
			case 12190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117713990, EnemyMetis, "Metis_481");
				break;
			case 12220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714020, EnemyMetis, "Metis_482");
				break;
			case 12250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714050, EnemyMetis, "Metis_483");
				break;
			case 12280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714080, EnemyMetis, "Metis_484");
				break;
			case 12310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714110, EnemyMetis, "Metis_485");
				break;
			case 12340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714140, EnemyMetis, "Metis_486");
				break;
			case 12370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714170, EnemyMetis, "Metis_487");
				break;
			case 12400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714200, EnemyMetis, "Metis_488");
				break;
			case 12430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714230, EnemyMetis, "Metis_489");
				break;
			case 12460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714260, EnemyMetis, "Metis_490");
				break;
			case 12490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714290, EnemyMetis, "Metis_491");
				break;
			case 12520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714320, EnemyMetis, "Metis_492");
				break;
			case 12550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714350, EnemyMetis, "Metis_493");
				break;
			case 12580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714380, EnemyMetis, "Metis_494");
				break;
			case 12610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714410, EnemyMetis, "Metis_495");
				break;
			case 12640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714440, EnemyMetis, "Metis_496");
				break;
			case 12670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714470, EnemyMetis, "Metis_497");
				break;
			case 12700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714500, EnemyMetis, "Metis_498");
				break;
			case 12730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714530, EnemyMetis, "Metis_499");
				break;
			case 12760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714560, EnemyMetis, "Metis_500");
				break;
			case 12790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714590, EnemyMetis, "Metis_501");
				break;
			case 12820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714620, EnemyMetis, "Metis_502");
				break;
			case 12850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714650, EnemyMetis, "Metis_503");
				break;
			case 12880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714680, EnemyMetis, "Metis_504");
				break;
			case 12910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714710, EnemyMetis, "Metis_505");
				break;
			case 12940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714740, EnemyMetis, "Metis_506");
				break;
			case 12970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117712970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714770, EnemyMetis, "Metis_507");
				break;
			case 13000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714800, EnemyMetis, "Metis_508");
				break;
			case 13030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714830, EnemyMetis, "Metis_509");
				break;
			case 13060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714860, EnemyMetis, "Metis_510");
				break;
			case 13090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714890, EnemyMetis, "Metis_511");
				break;
			case 13120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714920, EnemyMetis, "Metis_512");
				break;
			case 13150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714950, EnemyMetis, "Metis_513");
				break;
			case 13180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117714980, EnemyMetis, "Metis_514");
				break;
			case 13210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715010, EnemyMetis, "Metis_515");
				break;
			case 13240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715040, EnemyMetis, "Metis_516");
				break;
			case 13270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715070, EnemyMetis, "Metis_517");
				break;
			case 13300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715100, EnemyMetis, "Metis_518");
				break;
			case 13330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715130, EnemyMetis, "Metis_519");
				break;
			case 13360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715160, EnemyMetis, "Metis_520");
				break;
			case 13390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715190, EnemyMetis, "Metis_521");
				break;
			case 13420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715220, EnemyMetis, "Metis_522");
				break;
			case 13450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715250, EnemyMetis, "Metis_523");
				break;
			case 13480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715280, EnemyMetis, "Metis_524");
				break;
			case 13510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715310, EnemyMetis, "Metis_525");
				break;
			case 13540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715340, EnemyMetis, "Metis_526");
				break;
			case 13570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715370, EnemyMetis, "Metis_527");
				break;
			case 13600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715400, EnemyMetis, "Metis_528");
				break;
			case 13630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715430, EnemyMetis, "Metis_529");
				break;
			case 13660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715460, EnemyMetis, "Metis_530");
				break;
			case 13690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715490, EnemyMetis, "Metis_531");
				break;
			case 13720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715520, EnemyMetis, "Metis_532");
				break;
			case 13750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715550, EnemyMetis, "Metis_533");
				break;
			case 13780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715580, EnemyMetis, "Metis_534");
				break;
			case 13810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715610, EnemyMetis, "Metis_535");
				break;
			case 13840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715640, EnemyMetis, "Metis_536");
				break;
			case 13870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715670, EnemyMetis, "Metis_537");
				break;
			case 13900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715700, EnemyMetis, "Metis_538");
				break;
			case 13930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715730, EnemyMetis, "Metis_539");
				break;
			case 13960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715760, EnemyMetis, "Metis_540");
				break;
			case 13990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117713990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715790, EnemyMetis, "Metis_541");
				break;
			case 14020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715820, EnemyMetis, "Metis_542");
				break;
			case 14050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715850, EnemyMetis, "Metis_543");
				break;
			case 14080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715880, EnemyMetis, "Metis_544");
				break;
			case 14110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715910, EnemyMetis, "Metis_545");
				break;
			case 14140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715940, EnemyMetis, "Metis_546");
				break;
			case 14170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117715970, EnemyMetis, "Metis_547");
				break;
			case 14200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716000, EnemyMetis, "Metis_548");
				break;
			case 14230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716030, EnemyMetis, "Metis_549");
				break;
			case 14260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716060, EnemyMetis, "Metis_550");
				break;
			case 14290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716090, EnemyMetis, "Metis_551");
				break;
			case 14320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716120, EnemyMetis, "Metis_552");
				break;
			case 14350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716150, EnemyMetis, "Metis_553");
				break;
			case 14380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716180, EnemyMetis, "Metis_554");
				break;
			case 14410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716210, EnemyMetis, "Metis_555");
				break;
			case 14440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716240, EnemyMetis, "Metis_556");
				break;
			case 14470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716270, EnemyMetis, "Metis_557");
				break;
			case 14500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716300, EnemyMetis, "Metis_558");
				break;
			case 14530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716330, EnemyMetis, "Metis_559");
				break;
			case 14560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716360, EnemyMetis, "Metis_560");
				break;
			case 14590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716390, EnemyMetis, "Metis_561");
				break;
			case 14620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716420, EnemyMetis, "Metis_562");
				break;
			case 14650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716450, EnemyMetis, "Metis_563");
				break;
			case 14680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716480, EnemyMetis, "Metis_564");
				break;
			case 14710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716510, EnemyMetis, "Metis_565");
				break;
			case 14740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716540, EnemyMetis, "Metis_566");
				break;
			case 14770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716570, EnemyMetis, "Metis_567");
				break;
			case 14800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716600, EnemyMetis, "Metis_568");
				break;
			case 14830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716630, EnemyMetis, "Metis_569");
				break;
			case 14860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716660, EnemyMetis, "Metis_570");
				break;
			case 14890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716690, EnemyMetis, "Metis_571");
				break;
			case 14920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716720, EnemyMetis, "Metis_572");
				break;
			case 14950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716750, EnemyMetis, "Metis_573");
				break;
			case 14980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117714980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716780, EnemyMetis, "Metis_574");
				break;
			case 15010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716810, EnemyMetis, "Metis_575");
				break;
			case 15040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716840, EnemyMetis, "Metis_576");
				break;
			case 15070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716870, EnemyMetis, "Metis_577");
				break;
			case 15100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716900, EnemyMetis, "Metis_578");
				break;
			case 15130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716930, EnemyMetis, "Metis_579");
				break;
			case 15160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716960, EnemyMetis, "Metis_580");
				break;
			case 15190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117716990, EnemyMetis, "Metis_581");
				break;
			case 15220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717020, EnemyMetis, "Metis_582");
				break;
			case 15250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717050, EnemyMetis, "Metis_583");
				break;
			case 15280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717080, EnemyMetis, "Metis_584");
				break;
			case 15310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717110, EnemyMetis, "Metis_585");
				break;
			case 15340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717140, EnemyMetis, "Metis_586");
				break;
			case 15370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717170, EnemyMetis, "Metis_587");
				break;
			case 15400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717200, EnemyMetis, "Metis_588");
				break;
			case 15430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717230, EnemyMetis, "Metis_589");
				break;
			case 15460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717260, EnemyMetis, "Metis_590");
				break;
			case 15490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717290, EnemyMetis, "Metis_591");
				break;
			case 15520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717320, EnemyMetis, "Metis_592");
				break;
			case 15550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717350, EnemyMetis, "Metis_593");
				break;
			case 15580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717380, EnemyMetis, "Metis_594");
				break;
			case 15610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717410, EnemyMetis, "Metis_595");
				break;
			case 15640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717440, EnemyMetis, "Metis_596");
				break;
			case 15670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717470, EnemyMetis, "Metis_597");
				break;
			case 15700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717500, EnemyMetis, "Metis_598");
				break;
			case 15730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717530, EnemyMetis, "Metis_599");
				break;
			case 15760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717560, EnemyMetis, "Metis_600");
				break;
			case 15790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717590, EnemyMetis, "Metis_601");
				break;
			case 15820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717620, EnemyMetis, "Metis_602");
				break;
			case 15850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717650, EnemyMetis, "Metis_603");
				break;
			case 15880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717680, EnemyMetis, "Metis_604");
				break;
			case 15910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717710, EnemyMetis, "Metis_605");
				break;
			case 15940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717740, EnemyMetis, "Metis_606");
				break;
			case 15970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117715970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717770, EnemyMetis, "Metis_607");
				break;
			case 16000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717800, EnemyMetis, "Metis_608");
				break;
			case 16030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717830, EnemyMetis, "Metis_609");
				break;
			case 16060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717860, EnemyMetis, "Metis_610");
				break;
			case 16090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717890, EnemyMetis, "Metis_611");
				break;
			case 16120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717920, EnemyMetis, "Metis_612");
				break;
			case 16150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717950, EnemyMetis, "Metis_613");
				break;
			case 16180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117717980, EnemyMetis, "Metis_614");
				break;
			case 16210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718010, EnemyMetis, "Metis_615");
				break;
			case 16240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718040, EnemyMetis, "Metis_616");
				break;
			case 16270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718070, EnemyMetis, "Metis_617");
				break;
			case 16300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718100, EnemyMetis, "Metis_618");
				break;
			case 16330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718130, EnemyMetis, "Metis_619");
				break;
			case 16360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718160, EnemyMetis, "Metis_620");
				break;
			case 16390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718190, EnemyMetis, "Metis_621");
				break;
			case 16420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718220, EnemyMetis, "Metis_622");
				break;
			case 16450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718250, EnemyMetis, "Metis_623");
				break;
			case 16480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718280, EnemyMetis, "Metis_624");
				break;
			case 16510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718310, EnemyMetis, "Metis_625");
				break;
			case 16540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718340, EnemyMetis, "Metis_626");
				break;
			case 16570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718370, EnemyMetis, "Metis_627");
				break;
			case 16600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718400, EnemyMetis, "Metis_628");
				break;
			case 16630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718430, EnemyMetis, "Metis_629");
				break;
			case 16660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718460, EnemyMetis, "Metis_630");
				break;
			case 16690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718490, EnemyMetis, "Metis_631");
				break;
			case 16720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718520, EnemyMetis, "Metis_632");
				break;
			case 16750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718550, EnemyMetis, "Metis_633");
				break;
			case 16780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718580, EnemyMetis, "Metis_634");
				break;
			case 16810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718610, EnemyMetis, "Metis_635");
				break;
			case 16840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718640, EnemyMetis, "Metis_636");
				break;
			case 16870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718670, EnemyMetis, "Metis_637");
				break;
			case 16900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718700, EnemyMetis, "Metis_638");
				break;
			case 16930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718730, EnemyMetis, "Metis_639");
				break;
			case 16960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718760, EnemyMetis, "Metis_640");
				break;
			case 16990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117716990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718790, EnemyMetis, "Metis_641");
				break;
			case 17020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718820, EnemyMetis, "Metis_642");
				break;
			case 17050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718850, EnemyMetis, "Metis_643");
				break;
			case 17080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718880, EnemyMetis, "Metis_644");
				break;
			case 17110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718910, EnemyMetis, "Metis_645");
				break;
			case 17140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718940, EnemyMetis, "Metis_646");
				break;
			case 17170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117718970, EnemyMetis, "Metis_647");
				break;
			case 17200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719000, EnemyMetis, "Metis_648");
				break;
			case 17230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719030, EnemyMetis, "Metis_649");
				break;
			case 17260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719060, EnemyMetis, "Metis_650");
				break;
			case 17290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719090, EnemyMetis, "Metis_651");
				break;
			case 17320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719120, EnemyMetis, "Metis_652");
				break;
			case 17350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719150, EnemyMetis, "Metis_653");
				break;
			case 17380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719180, EnemyMetis, "Metis_654");
				break;
			case 17410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719210, EnemyMetis, "Metis_655");
				break;
			case 17440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719240, EnemyMetis, "Metis_656");
				break;
			case 17470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719270, EnemyMetis, "Metis_657");
				break;
			case 17500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719300, EnemyMetis, "Metis_658");
				break;
			case 17530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719330, EnemyMetis, "Metis_659");
				break;
			case 17560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719360, EnemyMetis, "Metis_660");
				break;
			case 17590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719390, EnemyMetis, "Metis_661");
				break;
			case 17620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719420, EnemyMetis, "Metis_662");
				break;
			case 17650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719450, EnemyMetis, "Metis_663");
				break;
			case 17680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719480, EnemyMetis, "Metis_664");
				break;
			case 17710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719510, EnemyMetis, "Metis_665");
				break;
			case 17740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719540, EnemyMetis, "Metis_666");
				break;
			case 17770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719570, EnemyMetis, "Metis_667");
				break;
			case 17800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719600, EnemyMetis, "Metis_668");
				break;
			case 17830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719630, EnemyMetis, "Metis_669");
				break;
			case 17860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719660, EnemyMetis, "Metis_670");
				break;
			case 17890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719690, EnemyMetis, "Metis_671");
				break;
			case 17920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719720, EnemyMetis, "Metis_672");
				break;
			case 17950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719750, EnemyMetis, "Metis_673");
				break;
			case 17980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117717980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719780, EnemyMetis, "Metis_674");
				break;
			case 18010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719810, EnemyMetis, "Metis_675");
				break;
			case 18040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719840, EnemyMetis, "Metis_676");
				break;
			case 18070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719870, EnemyMetis, "Metis_677");
				break;
			case 18100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719900, EnemyMetis, "Metis_678");
				break;
			case 18130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719930, EnemyMetis, "Metis_679");
				break;
			case 18160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719960, EnemyMetis, "Metis_680");
				break;
			case 18190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117719990, EnemyMetis, "Metis_681");
				break;
			case 18220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720020, EnemyMetis, "Metis_682");
				break;
			case 18250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720050, EnemyMetis, "Metis_683");
				break;
			case 18280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720080, EnemyMetis, "Metis_684");
				break;
			case 18310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720110, EnemyMetis, "Metis_685");
				break;
			case 18340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720140, EnemyMetis, "Metis_686");
				break;
			case 18370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720170, EnemyMetis, "Metis_687");
				break;
			case 18400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720200, EnemyMetis, "Metis_688");
				break;
			case 18430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720230, EnemyMetis, "Metis_689");
				break;
			case 18460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720260, EnemyMetis, "Metis_690");
				break;
			case 18490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720290, EnemyMetis, "Metis_691");
				break;
			case 18520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720320, EnemyMetis, "Metis_692");
				break;
			case 18550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720350, EnemyMetis, "Metis_693");
				break;
			case 18580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720380, EnemyMetis, "Metis_694");
				break;
			case 18610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720410, EnemyMetis, "Metis_695");
				break;
			case 18640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720440, EnemyMetis, "Metis_696");
				break;
			case 18670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720470, EnemyMetis, "Metis_697");
				break;
			case 18700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720500, EnemyMetis, "Metis_698");
				break;
			case 18730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720530, EnemyMetis, "Metis_699");
				break;
			case 18760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720560, EnemyMetis, "Metis_700");
				break;
			case 18790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720590, EnemyMetis, "Metis_701");
				break;
			case 18820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720620, EnemyMetis, "Metis_702");
				break;
			case 18850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720650, EnemyMetis, "Metis_703");
				break;
			case 18880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720680, EnemyMetis, "Metis_704");
				break;
			case 18910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720710, EnemyMetis, "Metis_705");
				break;
			case 18940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720740, EnemyMetis, "Metis_706");
				break;
			case 18970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117718970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720770, EnemyMetis, "Metis_707");
				break;
			case 19000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720800, EnemyMetis, "Metis_708");
				break;
			case 19030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720830, EnemyMetis, "Metis_709");
				break;
			case 19060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720860, EnemyMetis, "Metis_710");
				break;
			case 19090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720890, EnemyMetis, "Metis_711");
				break;
			case 19120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720920, EnemyMetis, "Metis_712");
				break;
			case 19150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720950, EnemyMetis, "Metis_713");
				break;
			case 19180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117720980, EnemyMetis, "Metis_714");
				break;
			case 19210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721010, EnemyMetis, "Metis_715");
				break;
			case 19240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721040, EnemyMetis, "Metis_716");
				break;
			case 19270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721070, EnemyMetis, "Metis_717");
				break;
			case 19300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721100, EnemyMetis, "Metis_718");
				break;
			case 19330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721130, EnemyMetis, "Metis_719");
				break;
			case 19360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721160, EnemyMetis, "Metis_720");
				break;
			case 19390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721190, EnemyMetis, "Metis_721");
				break;
			case 19420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721220, EnemyMetis, "Metis_722");
				break;
			case 19450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721250, EnemyMetis, "Metis_723");
				break;
			case 19480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721280, EnemyMetis, "Metis_724");
				break;
			case 19510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721310, EnemyMetis, "Metis_725");
				break;
			case 19540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721340, EnemyMetis, "Metis_726");
				break;
			case 19570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721370, EnemyMetis, "Metis_727");
				break;
			case 19600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721400, EnemyMetis, "Metis_728");
				break;
			case 19630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721430, EnemyMetis, "Metis_729");
				break;
			case 19660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721460, EnemyMetis, "Metis_730");
				break;
			case 19690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721490, EnemyMetis, "Metis_731");
				break;
			case 19720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721520, EnemyMetis, "Metis_732");
				break;
			case 19750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721550, EnemyMetis, "Metis_733");
				break;
			case 19780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721580, EnemyMetis, "Metis_734");
				break;
			case 19810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721610, EnemyMetis, "Metis_735");
				break;
			case 19840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721640, EnemyMetis, "Metis_736");
				break;
			case 19870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721670, EnemyMetis, "Metis_737");
				break;
			case 19900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721700, EnemyMetis, "Metis_738");
				break;
			case 19930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721730, EnemyMetis, "Metis_739");
				break;
			case 19960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721760, EnemyMetis, "Metis_740");
				break;
			case 19990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117719990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721790, EnemyMetis, "Metis_741");
				break;
			case 20020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721820, EnemyMetis, "Metis_742");
				break;
			case 20050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721850, EnemyMetis, "Metis_743");
				break;
			case 20080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721880, EnemyMetis, "Metis_744");
				break;
			case 20110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721910, EnemyMetis, "Metis_745");
				break;
			case 20140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721940, EnemyMetis, "Metis_746");
				break;
			case 20170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117721970, EnemyMetis, "Metis_747");
				break;
			case 20200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722000, EnemyMetis, "Metis_748");
				break;
			case 20230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722030, EnemyMetis, "Metis_749");
				break;
			case 20260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722060, EnemyMetis, "Metis_750");
				break;
			case 20290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722090, EnemyMetis, "Metis_751");
				break;
			case 20320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722120, EnemyMetis, "Metis_752");
				break;
			case 20350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722150, EnemyMetis, "Metis_753");
				break;
			case 20380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722180, EnemyMetis, "Metis_754");
				break;
			case 20410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722210, EnemyMetis, "Metis_755");
				break;
			case 20440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722240, EnemyMetis, "Metis_756");
				break;
			case 20470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722270, EnemyMetis, "Metis_757");
				break;
			case 20500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722300, EnemyMetis, "Metis_758");
				break;
			case 20530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722330, EnemyMetis, "Metis_759");
				break;
			case 20560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722360, EnemyMetis, "Metis_760");
				break;
			case 20590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722390, EnemyMetis, "Metis_761");
				break;
			case 20620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722420, EnemyMetis, "Metis_762");
				break;
			case 20650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722450, EnemyMetis, "Metis_763");
				break;
			case 20680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722480, EnemyMetis, "Metis_764");
				break;
			case 20710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722510, EnemyMetis, "Metis_765");
				break;
			case 20740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722540, EnemyMetis, "Metis_766");
				break;
			case 20770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722570, EnemyMetis, "Metis_767");
				break;
			case 20800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722600, EnemyMetis, "Metis_768");
				break;
			case 20830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722630, EnemyMetis, "Metis_769");
				break;
			case 20860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722660, EnemyMetis, "Metis_770");
				break;
			case 20890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722690, EnemyMetis, "Metis_771");
				break;
			case 20920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722720, EnemyMetis, "Metis_772");
				break;
			case 20950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722750, EnemyMetis, "Metis_773");
				break;
			case 20980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117720980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722780, EnemyMetis, "Metis_774");
				break;
			case 21010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722810, EnemyMetis, "Metis_775");
				break;
			case 21040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722840, EnemyMetis, "Metis_776");
				break;
			case 21070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722870, EnemyMetis, "Metis_777");
				break;
			case 21100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722900, EnemyMetis, "Metis_778");
				break;
			case 21130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722930, EnemyMetis, "Metis_779");
				break;
			case 21160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722960, EnemyMetis, "Metis_780");
				break;
			case 21190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117722990, EnemyMetis, "Metis_781");
				break;
			case 21220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723020, EnemyMetis, "Metis_782");
				break;
			case 21250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723050, EnemyMetis, "Metis_783");
				break;
			case 21280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723080, EnemyMetis, "Metis_784");
				break;
			case 21310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723110, EnemyMetis, "Metis_785");
				break;
			case 21340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723140, EnemyMetis, "Metis_786");
				break;
			case 21370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723170, EnemyMetis, "Metis_787");
				break;
			case 21400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723200, EnemyMetis, "Metis_788");
				break;
			case 21430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723230, EnemyMetis, "Metis_789");
				break;
			case 21460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723260, EnemyMetis, "Metis_790");
				break;
			case 21490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723290, EnemyMetis, "Metis_791");
				break;
			case 21520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723320, EnemyMetis, "Metis_792");
				break;
			case 21550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723350, EnemyMetis, "Metis_793");
				break;
			case 21580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723380, EnemyMetis, "Metis_794");
				break;
			case 21610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723410, EnemyMetis, "Metis_795");
				break;
			case 21640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723440, EnemyMetis, "Metis_796");
				break;
			case 21670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723470, EnemyMetis, "Metis_797");
				break;
			case 21700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723500, EnemyMetis, "Metis_798");
				break;
			case 21730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723530, EnemyMetis, "Metis_799");
				break;
			case 21760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723560, EnemyMetis, "Metis_800");
				break;
			case 21790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723590, EnemyMetis, "Metis_801");
				break;
			case 21820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723620, EnemyMetis, "Metis_802");
				break;
			case 21850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723650, EnemyMetis, "Metis_803");
				break;
			case 21880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723680, EnemyMetis, "Metis_804");
				break;
			case 21910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723710, EnemyMetis, "Metis_805");
				break;
			case 21940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723740, EnemyMetis, "Metis_806");
				break;
			case 21970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117721970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723770, EnemyMetis, "Metis_807");
				break;
			case 22000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723800, EnemyMetis, "Metis_808");
				break;
			case 22030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723830, EnemyMetis, "Metis_809");
				break;
			case 22060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723860, EnemyMetis, "Metis_810");
				break;
			case 22090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723890, EnemyMetis, "Metis_811");
				break;
			case 22120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723920, EnemyMetis, "Metis_812");
				break;
			case 22150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723950, EnemyMetis, "Metis_813");
				break;
			case 22180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117723980, EnemyMetis, "Metis_814");
				break;
			case 22210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724010, EnemyMetis, "Metis_815");
				break;
			case 22240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724040, EnemyMetis, "Metis_816");
				break;
			case 22270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724070, EnemyMetis, "Metis_817");
				break;
			case 22300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724100, EnemyMetis, "Metis_818");
				break;
			case 22330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724130, EnemyMetis, "Metis_819");
				break;
			case 22360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724160, EnemyMetis, "Metis_820");
				break;
			case 22390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724190, EnemyMetis, "Metis_821");
				break;
			case 22420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724220, EnemyMetis, "Metis_822");
				break;
			case 22450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724250, EnemyMetis, "Metis_823");
				break;
			case 22480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724280, EnemyMetis, "Metis_824");
				break;
			case 22510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724310, EnemyMetis, "Metis_825");
				break;
			case 22540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724340, EnemyMetis, "Metis_826");
				break;
			case 22570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724370, EnemyMetis, "Metis_827");
				break;
			case 22600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724400, EnemyMetis, "Metis_828");
				break;
			case 22630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724430, EnemyMetis, "Metis_829");
				break;
			case 22660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724460, EnemyMetis, "Metis_830");
				break;
			case 22690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724490, EnemyMetis, "Metis_831");
				break;
			case 22720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724520, EnemyMetis, "Metis_832");
				break;
			case 22750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724550, EnemyMetis, "Metis_833");
				break;
			case 22780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724580, EnemyMetis, "Metis_834");
				break;
			case 22810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724610, EnemyMetis, "Metis_835");
				break;
			case 22840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724640, EnemyMetis, "Metis_836");
				break;
			case 22870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724670, EnemyMetis, "Metis_837");
				break;
			case 22900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724700, EnemyMetis, "Metis_838");
				break;
			case 22930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724730, EnemyMetis, "Metis_839");
				break;
			case 22960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724760, EnemyMetis, "Metis_840");
				break;
			case 22990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117722990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724790, EnemyMetis, "Metis_841");
				break;
			case 23020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724820, EnemyMetis, "Metis_842");
				break;
			case 23050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724850, EnemyMetis, "Metis_843");
				break;
			case 23080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724880, EnemyMetis, "Metis_844");
				break;
			case 23110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724910, EnemyMetis, "Metis_845");
				break;
			case 23140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724940, EnemyMetis, "Metis_846");
				break;
			case 23170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117724970, EnemyMetis, "Metis_847");
				break;
			case 23200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725000, EnemyMetis, "Metis_848");
				break;
			case 23230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725030, EnemyMetis, "Metis_849");
				break;
			case 23260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725060, EnemyMetis, "Metis_850");
				break;
			case 23290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725090, EnemyMetis, "Metis_851");
				break;
			case 23320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725120, EnemyMetis, "Metis_852");
				break;
			case 23350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725150, EnemyMetis, "Metis_853");
				break;
			case 23380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725180, EnemyMetis, "Metis_854");
				break;
			case 23410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725210, EnemyMetis, "Metis_855");
				break;
			case 23440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725240, EnemyMetis, "Metis_856");
				break;
			case 23470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725270, EnemyMetis, "Metis_857");
				break;
			case 23500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725300, EnemyMetis, "Metis_858");
				break;
			case 23530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725330, EnemyMetis, "Metis_859");
				break;
			case 23560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725360, EnemyMetis, "Metis_860");
				break;
			case 23590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725390, EnemyMetis, "Metis_861");
				break;
			case 23620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725420, EnemyMetis, "Metis_862");
				break;
			case 23650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725450, EnemyMetis, "Metis_863");
				break;
			case 23680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725480, EnemyMetis, "Metis_864");
				break;
			case 23710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725510, EnemyMetis, "Metis_865");
				break;
			case 23740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725540, EnemyMetis, "Metis_866");
				break;
			case 23770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725570, EnemyMetis, "Metis_867");
				break;
			case 23800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725600, EnemyMetis, "Metis_868");
				break;
			case 23830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725630, EnemyMetis, "Metis_869");
				break;
			case 23860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725660, EnemyMetis, "Metis_870");
				break;
			case 23890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725690, EnemyMetis, "Metis_871");
				break;
			case 23920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725720, EnemyMetis, "Metis_872");
				break;
			case 23950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725750, EnemyMetis, "Metis_873");
				break;
			case 23980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117723980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725780, EnemyMetis, "Metis_874");
				break;
			case 24010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725810, EnemyMetis, "Metis_875");
				break;
			case 24040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725840, EnemyMetis, "Metis_876");
				break;
			case 24070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725870, EnemyMetis, "Metis_877");
				break;
			case 24100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725900, EnemyMetis, "Metis_878");
				break;
			case 24130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725930, EnemyMetis, "Metis_879");
				break;
			case 24160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725960, EnemyMetis, "Metis_880");
				break;
			case 24190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117725990, EnemyMetis, "Metis_881");
				break;
			case 24220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726020, EnemyMetis, "Metis_882");
				break;
			case 24250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726050, EnemyMetis, "Metis_883");
				break;
			case 24280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726080, EnemyMetis, "Metis_884");
				break;
			case 24310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726110, EnemyMetis, "Metis_885");
				break;
			case 24340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726140, EnemyMetis, "Metis_886");
				break;
			case 24370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726170, EnemyMetis, "Metis_887");
				break;
			case 24400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726200, EnemyMetis, "Metis_888");
				break;
			case 24430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726230, EnemyMetis, "Metis_889");
				break;
			case 24460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726260, EnemyMetis, "Metis_890");
				break;
			case 24490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726290, EnemyMetis, "Metis_891");
				break;
			case 24520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726320, EnemyMetis, "Metis_892");
				break;
			case 24550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726350, EnemyMetis, "Metis_893");
				break;
			case 24580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726380, EnemyMetis, "Metis_894");
				break;
			case 24610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726410, EnemyMetis, "Metis_895");
				break;
			case 24640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726440, EnemyMetis, "Metis_896");
				break;
			case 24670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726470, EnemyMetis, "Metis_897");
				break;
			case 24700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726500, EnemyMetis, "Metis_898");
				break;
			case 24730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726530, EnemyMetis, "Metis_899");
				break;
			case 24760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726560, EnemyMetis, "Metis_900");
				break;
			case 24790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726590, EnemyMetis, "Metis_901");
				break;
			case 24820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726620, EnemyMetis, "Metis_902");
				break;
			case 24850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726650, EnemyMetis, "Metis_903");
				break;
			case 24880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726680, EnemyMetis, "Metis_904");
				break;
			case 24910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726710, EnemyMetis, "Metis_905");
				break;
			case 24940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726740, EnemyMetis, "Metis_906");
				break;
			case 24970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117724970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726770, EnemyMetis, "Metis_907");
				break;
			case 25000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726800, EnemyMetis, "Metis_908");
				break;
			case 25030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726830, EnemyMetis, "Metis_909");
				break;
			case 25060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726860, EnemyMetis, "Metis_910");
				break;
			case 25090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726890, EnemyMetis, "Metis_911");
				break;
			case 25120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726920, EnemyMetis, "Metis_912");
				break;
			case 25150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726950, EnemyMetis, "Metis_913");
				break;
			case 25180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117726980, EnemyMetis, "Metis_914");
				break;
			case 25210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727010, EnemyMetis, "Metis_915");
				break;
			case 25240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727040, EnemyMetis, "Metis_916");
				break;
			case 25270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727070, EnemyMetis, "Metis_917");
				break;
			case 25300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727100, EnemyMetis, "Metis_918");
				break;
			case 25330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727130, EnemyMetis, "Metis_919");
				break;
			case 25360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727160, EnemyMetis, "Metis_920");
				break;
			case 25390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727190, EnemyMetis, "Metis_921");
				break;
			case 25420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727220, EnemyMetis, "Metis_922");
				break;
			case 25450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727250, EnemyMetis, "Metis_923");
				break;
			case 25480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727280, EnemyMetis, "Metis_924");
				break;
			case 25510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727310, EnemyMetis, "Metis_925");
				break;
			case 25540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727340, EnemyMetis, "Metis_926");
				break;
			case 25570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727370, EnemyMetis, "Metis_927");
				break;
			case 25600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727400, EnemyMetis, "Metis_928");
				break;
			case 25630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727430, EnemyMetis, "Metis_929");
				break;
			case 25660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727460, EnemyMetis, "Metis_930");
				break;
			case 25690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727490, EnemyMetis, "Metis_931");
				break;
			case 25720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727520, EnemyMetis, "Metis_932");
				break;
			case 25750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727550, EnemyMetis, "Metis_933");
				break;
			case 25780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727580, EnemyMetis, "Metis_934");
				break;
			case 25810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727610, EnemyMetis, "Metis_935");
				break;
			case 25840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727640, EnemyMetis, "Metis_936");
				break;
			case 25870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727670, EnemyMetis, "Metis_937");
				break;
			case 25900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727700, EnemyMetis, "Metis_938");
				break;
			case 25930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727730, EnemyMetis, "Metis_939");
				break;
			case 25960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727760, EnemyMetis, "Metis_940");
				break;
			case 25990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117725990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727790, EnemyMetis, "Metis_941");
				break;
			case 26020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727820, EnemyMetis, "Metis_942");
				break;
			case 26050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727850, EnemyMetis, "Metis_943");
				break;
			case 26080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727880, EnemyMetis, "Metis_944");
				break;
			case 26110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727910, EnemyMetis, "Metis_945");
				break;
			case 26140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727940, EnemyMetis, "Metis_946");
				break;
			case 26170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117727970, EnemyMetis, "Metis_947");
				break;
			case 26200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728000, EnemyMetis, "Metis_948");
				break;
			case 26230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728030, EnemyMetis, "Metis_949");
				break;
			case 26260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728060, EnemyMetis, "Metis_950");
				break;
			case 26290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728090, EnemyMetis, "Metis_951");
				break;
			case 26320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728120, EnemyMetis, "Metis_952");
				break;
			case 26350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728150, EnemyMetis, "Metis_953");
				break;
			case 26380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728180, EnemyMetis, "Metis_954");
				break;
			case 26410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728210, EnemyMetis, "Metis_955");
				break;
			case 26440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728240, EnemyMetis, "Metis_956");
				break;
			case 26470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728270, EnemyMetis, "Metis_957");
				break;
			case 26500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728300, EnemyMetis, "Metis_958");
				break;
			case 26530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728330, EnemyMetis, "Metis_959");
				break;
			case 26560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728360, EnemyMetis, "Metis_960");
				break;
			case 26590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728390, EnemyMetis, "Metis_961");
				break;
			case 26620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728420, EnemyMetis, "Metis_962");
				break;
			case 26650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728450, EnemyMetis, "Metis_963");
				break;
			case 26680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728480, EnemyMetis, "Metis_964");
				break;
			case 26710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728510, EnemyMetis, "Metis_965");
				break;
			case 26740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728540, EnemyMetis, "Metis_966");
				break;
			case 26770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728570, EnemyMetis, "Metis_967");
				break;
			case 26800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728600, EnemyMetis, "Metis_968");
				break;
			case 26830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728630, EnemyMetis, "Metis_969");
				break;
			case 26860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728660, EnemyMetis, "Metis_970");
				break;
			case 26890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728690, EnemyMetis, "Metis_971");
				break;
			case 26920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728720, EnemyMetis, "Metis_972");
				break;
			case 26950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728750, EnemyMetis, "Metis_973");
				break;
			case 26980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117726980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728780, EnemyMetis, "Metis_974");
				break;
			case 27010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728810, EnemyMetis, "Metis_975");
				break;
			case 27040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728840, EnemyMetis, "Metis_976");
				break;
			case 27070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728870, EnemyMetis, "Metis_977");
				break;
			case 27100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728900, EnemyMetis, "Metis_978");
				break;
			case 27130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728930, EnemyMetis, "Metis_979");
				break;
			case 27160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728960, EnemyMetis, "Metis_980");
				break;
			case 27190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117728990, EnemyMetis, "Metis_981");
				break;
			case 27220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729020, EnemyMetis, "Metis_982");
				break;
			case 27250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729050, EnemyMetis, "Metis_983");
				break;
			case 27280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729080, EnemyMetis, "Metis_984");
				break;
			case 27310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729110, EnemyMetis, "Metis_985");
				break;
			case 27340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729140, EnemyMetis, "Metis_986");
				break;
			case 27370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729170, EnemyMetis, "Metis_987");
				break;
			case 27400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729200, EnemyMetis, "Metis_988");
				break;
			case 27430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729230, EnemyMetis, "Metis_989");
				break;
			case 27460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729260, EnemyMetis, "Metis_990");
				break;
			case 27490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729290, EnemyMetis, "Metis_991");
				break;
			case 27520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729320, EnemyMetis, "Metis_992");
				break;
			case 27550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729350, EnemyMetis, "Metis_993");
				break;
			case 27580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729380, EnemyMetis, "Metis_994");
				break;
			case 27610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729410, EnemyMetis, "Metis_995");
				break;
			case 27640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729440, EnemyMetis, "Metis_996");
				break;
			case 27670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729470, EnemyMetis, "Metis_997");
				break;
			case 27700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729500, EnemyMetis, "Metis_998");
				break;
			case 27730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729530, EnemyMetis, "Metis_999");
				break;
			case 27760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729560, EnemyMetis, "Metis_1000");
				break;
			case 27790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729590, EnemyMetis, "Metis_1001");
				break;
			case 27820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729620, EnemyMetis, "Metis_1002");
				break;
			case 27850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729650, EnemyMetis, "Metis_1003");
				break;
			case 27880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729680, EnemyMetis, "Metis_1004");
				break;
			case 27910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729710, EnemyMetis, "Metis_1005");
				break;
			case 27940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729740, EnemyMetis, "Metis_1006");
				break;
			case 27970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117727970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729770, EnemyMetis, "Metis_1007");
				break;
			case 28000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729800, EnemyMetis, "Metis_1008");
				break;
			case 28030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729830, EnemyMetis, "Metis_1009");
				break;
			case 28060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729860, EnemyMetis, "Metis_1010");
				break;
			case 28090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729890, EnemyMetis, "Metis_1011");
				break;
			case 28120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729920, EnemyMetis, "Metis_1012");
				break;
			case 28150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729950, EnemyMetis, "Metis_1013");
				break;
			case 28180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117729980, EnemyMetis, "Metis_1014");
				break;
			case 28210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728210);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728240);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728270);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728300);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728330);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728360);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728390);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728420);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728450);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728480);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728510);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728540);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728570);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728600);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728630);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728660);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728690);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728720);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728750);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728780);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728810);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728840);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728870);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728900);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728930);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728960);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 28990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117728990);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729020);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729050);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729080);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729110);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729140);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729170);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729200);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729230);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729260);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729290);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729320);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729350);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729380);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729410);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729440);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729470);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729500);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729530);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729560);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729590);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729620);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729650);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729680);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729710);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729740);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729770);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729800);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729830);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729860);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729890);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729920);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729950);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 29980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117729980);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 30000:
				throwUpEvent(STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 1002-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
