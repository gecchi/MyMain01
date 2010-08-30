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
	frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2110,2140,2170,2200,2230,2260,2290,2320,2350,2380,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000,4030,4060,4090,4120,4150,4180,4210,4240,4270,4300,4330,4360,4390,4420,4450,4480,4510,4540,4570,4600,4630,4660,4690,4720,4750,4780,4810,4840,4870,4900,4930,4960,4990,5020,5050,5080,5110,5140,5170,5200,5230,5260,5290,5320,5350,5380,5410,5440,5470,5500,5530,5560,5590,5620,5650,5680,5710,5740,5770,5800,5830,5860,5890,5920,5950,5980,6010,6040,6070,6100,6130,6160,6190,6220,6250,6280,6310,6340,6370,6400,6430,6460,6490,6520,6550,6580,6610,6640,6670,6700,6730,6760,6790,6820,6850,6880,6910,6940,6970,7000,7030,7060,7090,7120,7150,7180,7210,7240,7270,7300,7330,7360,7390,7420,7450,7480,7510,7540,7570,7600,7630,7660,7690,7720,7750,7780,7810,7840,7870,7900,7930,7960,7990,8020,8050,8080,8110,8140,8170,8200,8230,8260,8290,8320,8350,8380,8410,8440,8470,8500,8530,8560,8590,8620,8650,8680,8710,8740,8770,8800,8830,8860,8890,8920,8950,8980,9010,9040,9070,9100,9130,9160,9190,9220,9250,9280,9310,9340,9370,9400,9430,9460,9490,9520,9550,9580,9610,9640,9670,9700,9730,9760,9790,9820,9850,9880,9910,9940,9970,10000,10500};
	_paFrame_NextEvent = new frame[336];
	for (int i = 0; i < 336; i++) {
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
				orderActorToFactory(211771810, EnemyMetis, "Metis_70");
				break;
			case 40:
				orderActorToFactory(211771840, EnemyMetis, "Metis_71");
				break;
			case 70:
				orderActorToFactory(211771870, EnemyMetis, "Metis_72");
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_73");
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
				orderActorToFactory(211771900, EnemyMetis, "Metis_74");
				break;
			case 130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771930, EnemyMetis, "Metis_75");
				break;
			case 160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771960, EnemyMetis, "Metis_76");
				break;
			case 190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211771990, EnemyMetis, "Metis_77");
				break;
			case 220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772020, EnemyMetis, "Metis_78");
				break;
			case 250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772050, EnemyMetis, "Metis_79");
				break;
			case 280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772080, EnemyMetis, "Metis_80");
				break;
			case 310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772110, EnemyMetis, "Metis_81");
				break;
			case 340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772140, EnemyMetis, "Metis_82");
				break;
			case 370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772170, EnemyMetis, "Metis_83");
				break;
			case 400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772200, EnemyMetis, "Metis_84");
				break;
			case 430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772230, EnemyMetis, "Metis_85");
				break;
			case 460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772260, EnemyMetis, "Metis_86");
				break;
			case 490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772290, EnemyMetis, "Metis_87");
				break;
			case 520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772320, EnemyMetis, "Metis_88");
				break;
			case 550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772350, EnemyMetis, "Metis_89");
				break;
			case 580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772380, EnemyMetis, "Metis_90");
				break;
			case 610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772410, EnemyMetis, "Metis_91");
				break;
			case 640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772440, EnemyMetis, "Metis_92");
				break;
			case 670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772470, EnemyMetis, "Metis_93");
				break;
			case 700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772500, EnemyMetis, "Metis_94");
				break;
			case 730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772530, EnemyMetis, "Metis_95");
				break;
			case 760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772560, EnemyMetis, "Metis_96");
				break;
			case 790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772590, EnemyMetis, "Metis_97");
				break;
			case 820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772620, EnemyMetis, "Metis_98");
				break;
			case 850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772650, EnemyMetis, "Metis_99");
				break;
			case 880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772680, EnemyMetis, "Metis_100");
				break;
			case 910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772710, EnemyMetis, "Metis_101");
				break;
			case 940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772740, EnemyMetis, "Metis_102");
				break;
			case 970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(21177970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772770, EnemyMetis, "Metis_103");
				break;
			case 1000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772800, EnemyMetis, "Metis_104");
				break;
			case 1030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772830, EnemyMetis, "Metis_105");
				break;
			case 1060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772860, EnemyMetis, "Metis_106");
				break;
			case 1090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772890, EnemyMetis, "Metis_107");
				break;
			case 1120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772920, EnemyMetis, "Metis_108");
				break;
			case 1150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772950, EnemyMetis, "Metis_109");
				break;
			case 1180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211772980, EnemyMetis, "Metis_110");
				break;
			case 1210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773010, EnemyMetis, "Metis_111");
				break;
			case 1240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773040, EnemyMetis, "Metis_112");
				break;
			case 1270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773070, EnemyMetis, "Metis_113");
				break;
			case 1300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773100, EnemyMetis, "Metis_114");
				break;
			case 1330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773130, EnemyMetis, "Metis_115");
				break;
			case 1360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773160, EnemyMetis, "Metis_116");
				break;
			case 1390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773190, EnemyMetis, "Metis_117");
				break;
			case 1420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773220, EnemyMetis, "Metis_118");
				break;
			case 1450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773250, EnemyMetis, "Metis_119");
				break;
			case 1480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773280, EnemyMetis, "Metis_120");
				break;
			case 1510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773310, EnemyMetis, "Metis_121");
				break;
			case 1540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773340, EnemyMetis, "Metis_122");
				break;
			case 1570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773370, EnemyMetis, "Metis_123");
				break;
			case 1600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773400, EnemyMetis, "Metis_124");
				break;
			case 1630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773430, EnemyMetis, "Metis_125");
				break;
			case 1660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773460, EnemyMetis, "Metis_126");
				break;
			case 1690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773490, EnemyMetis, "Metis_127");
				break;
			case 1720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773520, EnemyMetis, "Metis_128");
				break;
			case 1750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773550, EnemyMetis, "Metis_129");
				break;
			case 1780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773580, EnemyMetis, "Metis_130");
				break;
			case 1810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773610, EnemyMetis, "Metis_131");
				break;
			case 1840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773640, EnemyMetis, "Metis_132");
				break;
			case 1870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773670, EnemyMetis, "Metis_133");
				break;
			case 1900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773700, EnemyMetis, "Metis_134");
				break;
			case 1930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773730, EnemyMetis, "Metis_135");
				break;
			case 1960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773760, EnemyMetis, "Metis_136");
				break;
			case 1990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211771990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773790, EnemyMetis, "Metis_137");
				break;
			case 2020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773820, EnemyMetis, "Metis_138");
				break;
			case 2050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773850, EnemyMetis, "Metis_139");
				break;
			case 2080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773880, EnemyMetis, "Metis_140");
				break;
			case 2110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773910, EnemyMetis, "Metis_141");
				break;
			case 2140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773940, EnemyMetis, "Metis_142");
				break;
			case 2170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211773970, EnemyMetis, "Metis_143");
				break;
			case 2200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774000, EnemyMetis, "Metis_144");
				break;
			case 2230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774030, EnemyMetis, "Metis_145");
				break;
			case 2260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774060, EnemyMetis, "Metis_146");
				break;
			case 2290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774090, EnemyMetis, "Metis_147");
				break;
			case 2320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774120, EnemyMetis, "Metis_148");
				break;
			case 2350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774150, EnemyMetis, "Metis_149");
				break;
			case 2380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774180, EnemyMetis, "Metis_150");
				break;
			case 2410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774210, EnemyMetis, "Metis_151");
				break;
			case 2440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774240, EnemyMetis, "Metis_152");
				break;
			case 2470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774270, EnemyMetis, "Metis_153");
				break;
			case 2500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774300, EnemyMetis, "Metis_154");
				break;
			case 2530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774330, EnemyMetis, "Metis_155");
				break;
			case 2560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774360, EnemyMetis, "Metis_156");
				break;
			case 2590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774390, EnemyMetis, "Metis_157");
				break;
			case 2620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774420, EnemyMetis, "Metis_158");
				break;
			case 2650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774450, EnemyMetis, "Metis_159");
				break;
			case 2680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774480, EnemyMetis, "Metis_160");
				break;
			case 2710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774510, EnemyMetis, "Metis_161");
				break;
			case 2740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774540, EnemyMetis, "Metis_162");
				break;
			case 2770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774570, EnemyMetis, "Metis_163");
				break;
			case 2800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774600, EnemyMetis, "Metis_164");
				break;
			case 2830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774630, EnemyMetis, "Metis_165");
				break;
			case 2860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774660, EnemyMetis, "Metis_166");
				break;
			case 2890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774690, EnemyMetis, "Metis_167");
				break;
			case 2920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774720, EnemyMetis, "Metis_168");
				break;
			case 2950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774750, EnemyMetis, "Metis_169");
				break;
			case 2980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211772980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774780, EnemyMetis, "Metis_170");
				break;
			case 3010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774810, EnemyMetis, "Metis_171");
				break;
			case 3040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774840, EnemyMetis, "Metis_172");
				break;
			case 3070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774870, EnemyMetis, "Metis_173");
				break;
			case 3100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774900, EnemyMetis, "Metis_174");
				break;
			case 3130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774930, EnemyMetis, "Metis_175");
				break;
			case 3160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774960, EnemyMetis, "Metis_176");
				break;
			case 3190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211774990, EnemyMetis, "Metis_177");
				break;
			case 3220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775020, EnemyMetis, "Metis_178");
				break;
			case 3250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775050, EnemyMetis, "Metis_179");
				break;
			case 3280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775080, EnemyMetis, "Metis_180");
				break;
			case 3310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775110, EnemyMetis, "Metis_181");
				break;
			case 3340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775140, EnemyMetis, "Metis_182");
				break;
			case 3370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775170, EnemyMetis, "Metis_183");
				break;
			case 3400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775200, EnemyMetis, "Metis_184");
				break;
			case 3430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775230, EnemyMetis, "Metis_185");
				break;
			case 3460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775260, EnemyMetis, "Metis_186");
				break;
			case 3490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775290, EnemyMetis, "Metis_187");
				break;
			case 3520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775320, EnemyMetis, "Metis_188");
				break;
			case 3550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775350, EnemyMetis, "Metis_189");
				break;
			case 3580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775380, EnemyMetis, "Metis_190");
				break;
			case 3610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775410, EnemyMetis, "Metis_191");
				break;
			case 3640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775440, EnemyMetis, "Metis_192");
				break;
			case 3670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775470, EnemyMetis, "Metis_193");
				break;
			case 3700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775500, EnemyMetis, "Metis_194");
				break;
			case 3730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775530, EnemyMetis, "Metis_195");
				break;
			case 3760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775560, EnemyMetis, "Metis_196");
				break;
			case 3790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775590, EnemyMetis, "Metis_197");
				break;
			case 3820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775620, EnemyMetis, "Metis_198");
				break;
			case 3850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775650, EnemyMetis, "Metis_199");
				break;
			case 3880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775680, EnemyMetis, "Metis_200");
				break;
			case 3910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775710, EnemyMetis, "Metis_201");
				break;
			case 3940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775740, EnemyMetis, "Metis_202");
				break;
			case 3970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211773970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775770, EnemyMetis, "Metis_203");
				break;
			case 4000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775800, EnemyMetis, "Metis_204");
				break;
			case 4030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775830, EnemyMetis, "Metis_205");
				break;
			case 4060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775860, EnemyMetis, "Metis_206");
				break;
			case 4090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775890, EnemyMetis, "Metis_207");
				break;
			case 4120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775920, EnemyMetis, "Metis_208");
				break;
			case 4150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775950, EnemyMetis, "Metis_209");
				break;
			case 4180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211775980, EnemyMetis, "Metis_210");
				break;
			case 4210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776010, EnemyMetis, "Metis_211");
				break;
			case 4240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776040, EnemyMetis, "Metis_212");
				break;
			case 4270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776070, EnemyMetis, "Metis_213");
				break;
			case 4300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776100, EnemyMetis, "Metis_214");
				break;
			case 4330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776130, EnemyMetis, "Metis_215");
				break;
			case 4360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776160, EnemyMetis, "Metis_216");
				break;
			case 4390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776190, EnemyMetis, "Metis_217");
				break;
			case 4420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776220, EnemyMetis, "Metis_218");
				break;
			case 4450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776250, EnemyMetis, "Metis_219");
				break;
			case 4480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776280, EnemyMetis, "Metis_220");
				break;
			case 4510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776310, EnemyMetis, "Metis_221");
				break;
			case 4540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776340, EnemyMetis, "Metis_222");
				break;
			case 4570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776370, EnemyMetis, "Metis_223");
				break;
			case 4600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776400, EnemyMetis, "Metis_224");
				break;
			case 4630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776430, EnemyMetis, "Metis_225");
				break;
			case 4660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776460, EnemyMetis, "Metis_226");
				break;
			case 4690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776490, EnemyMetis, "Metis_227");
				break;
			case 4720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776520, EnemyMetis, "Metis_228");
				break;
			case 4750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776550, EnemyMetis, "Metis_229");
				break;
			case 4780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776580, EnemyMetis, "Metis_230");
				break;
			case 4810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776610, EnemyMetis, "Metis_231");
				break;
			case 4840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776640, EnemyMetis, "Metis_232");
				break;
			case 4870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776670, EnemyMetis, "Metis_233");
				break;
			case 4900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776700, EnemyMetis, "Metis_234");
				break;
			case 4930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776730, EnemyMetis, "Metis_235");
				break;
			case 4960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776760, EnemyMetis, "Metis_236");
				break;
			case 4990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211774990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776790, EnemyMetis, "Metis_237");
				break;
			case 5020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776820, EnemyMetis, "Metis_238");
				break;
			case 5050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776850, EnemyMetis, "Metis_239");
				break;
			case 5080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776880, EnemyMetis, "Metis_240");
				break;
			case 5110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776910, EnemyMetis, "Metis_241");
				break;
			case 5140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776940, EnemyMetis, "Metis_242");
				break;
			case 5170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211776970, EnemyMetis, "Metis_243");
				break;
			case 5200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777000, EnemyMetis, "Metis_244");
				break;
			case 5230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775230);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777030, EnemyMetis, "Metis_245");
				break;
			case 5260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775260);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777060, EnemyMetis, "Metis_246");
				break;
			case 5290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775290);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777090, EnemyMetis, "Metis_247");
				break;
			case 5320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775320);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777120, EnemyMetis, "Metis_248");
				break;
			case 5350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775350);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777150, EnemyMetis, "Metis_249");
				break;
			case 5380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775380);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777180, EnemyMetis, "Metis_250");
				break;
			case 5410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775410);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777210, EnemyMetis, "Metis_251");
				break;
			case 5440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775440);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777240, EnemyMetis, "Metis_252");
				break;
			case 5470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775470);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777270, EnemyMetis, "Metis_253");
				break;
			case 5500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775500);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777300, EnemyMetis, "Metis_254");
				break;
			case 5530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775530);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777330, EnemyMetis, "Metis_255");
				break;
			case 5560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775560);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777360, EnemyMetis, "Metis_256");
				break;
			case 5590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775590);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777390, EnemyMetis, "Metis_257");
				break;
			case 5620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775620);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777420, EnemyMetis, "Metis_258");
				break;
			case 5650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775650);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777450, EnemyMetis, "Metis_259");
				break;
			case 5680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775680);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777480, EnemyMetis, "Metis_260");
				break;
			case 5710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775710);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777510, EnemyMetis, "Metis_261");
				break;
			case 5740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775740);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777540, EnemyMetis, "Metis_262");
				break;
			case 5770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775770);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777570, EnemyMetis, "Metis_263");
				break;
			case 5800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775800);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777600, EnemyMetis, "Metis_264");
				break;
			case 5830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775830);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777630, EnemyMetis, "Metis_265");
				break;
			case 5860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775860);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777660, EnemyMetis, "Metis_266");
				break;
			case 5890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775890);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777690, EnemyMetis, "Metis_267");
				break;
			case 5920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775920);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777720, EnemyMetis, "Metis_268");
				break;
			case 5950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775950);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777750, EnemyMetis, "Metis_269");
				break;
			case 5980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211775980);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777780, EnemyMetis, "Metis_270");
				break;
			case 6010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776010);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777810, EnemyMetis, "Metis_271");
				break;
			case 6040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776040);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777840, EnemyMetis, "Metis_272");
				break;
			case 6070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776070);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777870, EnemyMetis, "Metis_273");
				break;
			case 6100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776100);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777900, EnemyMetis, "Metis_274");
				break;
			case 6130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776130);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777930, EnemyMetis, "Metis_275");
				break;
			case 6160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776160);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777960, EnemyMetis, "Metis_276");
				break;
			case 6190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776190);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211777990, EnemyMetis, "Metis_277");
				break;
			case 6220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776220);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778020, EnemyMetis, "Metis_278");
				break;
			case 6250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776250);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778050, EnemyMetis, "Metis_279");
				break;
			case 6280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776280);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778080, EnemyMetis, "Metis_280");
				break;
			case 6310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776310);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778110, EnemyMetis, "Metis_281");
				break;
			case 6340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776340);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778140, EnemyMetis, "Metis_282");
				break;
			case 6370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776370);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778170, EnemyMetis, "Metis_283");
				break;
			case 6400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776400);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778200, EnemyMetis, "Metis_284");
				break;
			case 6430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776430);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778230, EnemyMetis, "Metis_285");
				break;
			case 6460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776460);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778260, EnemyMetis, "Metis_286");
				break;
			case 6490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776490);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778290, EnemyMetis, "Metis_287");
				break;
			case 6520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776520);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778320, EnemyMetis, "Metis_288");
				break;
			case 6550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776550);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778350, EnemyMetis, "Metis_289");
				break;
			case 6580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776580);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778380, EnemyMetis, "Metis_290");
				break;
			case 6610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776610);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778410, EnemyMetis, "Metis_291");
				break;
			case 6640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776640);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778440, EnemyMetis, "Metis_292");
				break;
			case 6670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776670);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778470, EnemyMetis, "Metis_293");
				break;
			case 6700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776700);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778500, EnemyMetis, "Metis_294");
				break;
			case 6730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776730);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778530, EnemyMetis, "Metis_295");
				break;
			case 6760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776760);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778560, EnemyMetis, "Metis_296");
				break;
			case 6790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776790);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778590, EnemyMetis, "Metis_297");
				break;
			case 6820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776820);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778620, EnemyMetis, "Metis_298");
				break;
			case 6850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776850);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778650, EnemyMetis, "Metis_299");
				break;
			case 6880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776880);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778680, EnemyMetis, "Metis_300");
				break;
			case 6910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776910);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778710, EnemyMetis, "Metis_301");
				break;
			case 6940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776940);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778740, EnemyMetis, "Metis_302");
				break;
			case 6970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211776970);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778770, EnemyMetis, "Metis_303");
				break;
			case 7000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777000);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778800, EnemyMetis, "Metis_304");
				break;
			case 7030:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777030);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778830, EnemyMetis, "Metis_305");
				break;
			case 7060:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777060);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778860, EnemyMetis, "Metis_306");
				break;
			case 7090:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777090);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778890, EnemyMetis, "Metis_307");
				break;
			case 7120:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777120);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778920, EnemyMetis, "Metis_308");
				break;
			case 7150:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777150);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778950, EnemyMetis, "Metis_309");
				break;
			case 7180:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777180);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211778980, EnemyMetis, "Metis_310");
				break;
			case 7210:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777210);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779010, EnemyMetis, "Metis_311");
				break;
			case 7240:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777240);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779040, EnemyMetis, "Metis_312");
				break;
			case 7270:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777270);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779070, EnemyMetis, "Metis_313");
				break;
			case 7300:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777300);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779100, EnemyMetis, "Metis_314");
				break;
			case 7330:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777330);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779130, EnemyMetis, "Metis_315");
				break;
			case 7360:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777360);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779160, EnemyMetis, "Metis_316");
				break;
			case 7390:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777390);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779190, EnemyMetis, "Metis_317");
				break;
			case 7420:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777420);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779220, EnemyMetis, "Metis_318");
				break;
			case 7450:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777450);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779250, EnemyMetis, "Metis_319");
				break;
			case 7480:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777480);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779280, EnemyMetis, "Metis_320");
				break;
			case 7510:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777510);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779310, EnemyMetis, "Metis_321");
				break;
			case 7540:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777540);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779340, EnemyMetis, "Metis_322");
				break;
			case 7570:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777570);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779370, EnemyMetis, "Metis_323");
				break;
			case 7600:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777600);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779400, EnemyMetis, "Metis_324");
				break;
			case 7630:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777630);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779430, EnemyMetis, "Metis_325");
				break;
			case 7660:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777660);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779460, EnemyMetis, "Metis_326");
				break;
			case 7690:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777690);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779490, EnemyMetis, "Metis_327");
				break;
			case 7720:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777720);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779520, EnemyMetis, "Metis_328");
				break;
			case 7750:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777750);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779550, EnemyMetis, "Metis_329");
				break;
			case 7780:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777780);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779580, EnemyMetis, "Metis_330");
				break;
			case 7810:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777810);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779610, EnemyMetis, "Metis_331");
				break;
			case 7840:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777840);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779640, EnemyMetis, "Metis_332");
				break;
			case 7870:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777870);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779670, EnemyMetis, "Metis_333");
				break;
			case 7900:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777900);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779700, EnemyMetis, "Metis_334");
				break;
			case 7930:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777930);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779730, EnemyMetis, "Metis_335");
				break;
			case 7960:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777960);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779760, EnemyMetis, "Metis_336");
				break;
			case 7990:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211777990);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779790, EnemyMetis, "Metis_337");
				break;
			case 8020:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778020);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779820, EnemyMetis, "Metis_338");
				break;
			case 8050:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778050);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779850, EnemyMetis, "Metis_339");
				break;
			case 8080:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778080);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779880, EnemyMetis, "Metis_340");
				break;
			case 8110:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778110);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779910, EnemyMetis, "Metis_341");
				break;
			case 8140:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778140);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779940, EnemyMetis, "Metis_342");
				break;
			case 8170:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778170);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(211779970, EnemyMetis, "Metis_343");
				break;
			case 8200:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778200);
				getLordActor()->addSubGroup(pActor);
				}
				orderActorToFactory(2117710000, EnemyMetis, "Metis_344");
				break;
			case 8230:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778230);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8260:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778260);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8290:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778290);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8320:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778320);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8350:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778350);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8380:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778380);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8410:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778410);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8440:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778440);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8470:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778470);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8500:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778500);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8530:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778530);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8560:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778560);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8590:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778590);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8620:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778620);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8650:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778650);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8680:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778680);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8710:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778710);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8740:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778740);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8770:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778770);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8800:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778800);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8830:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778830);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8860:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778860);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8890:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778890);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8920:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778920);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8950:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778950);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 8980:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211778980);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9010:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779010);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9040:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779040);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9070:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779070);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9100:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9130:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779130);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9160:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779160);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9190:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779190);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9220:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779220);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9250:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779250);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9280:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779280);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9310:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779310);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9340:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779340);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9370:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779370);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9400:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9430:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779430);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9460:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779460);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9490:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779490);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9520:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779520);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9550:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779550);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9580:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779580);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9610:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779610);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9640:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779640);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9670:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779670);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9700:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779700);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9730:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779730);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9760:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779760);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9790:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779790);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9820:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779820);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9850:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779850);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9880:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779880);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9910:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779910);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9940:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779940);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 9970:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(211779970);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 10000:
				{
				EnemyMetis* pActor = (EnemyMetis*)obtainActorFromFactory(2117710000);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 10500:
				throwUpEvent(STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 336-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
