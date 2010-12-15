#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,40,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2110,2140,2170,2200,2230,2260,2290,2320,2350,2380,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2710,2740,2770,2800,2830,2860,2890,2920,2950,2980,3010,3040,3070,3100,3130,3160,3190,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3580,3610,3640,3670,3700,3730,3760,3790,3820,3850,3880,3910,3940,3970,4000};
	_paFrame_NextEvent = new frame[135];
	for (int i = 0; i < 135; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(30000000, EnemyMetis, "Metis_1");
	orderActorToFactory(30000001, EnemyMetis, "Metis_2");
	orderActorToFactory(30000002, EnemyMetis, "Metis_3");
	orderActorToFactory(30000003, EnemyMetis, "Metis_4");
	orderActorToFactory(30000004, EnemyMetis, "Metis_5");
	orderActorToFactory(30000005, EnemyMetis, "Metis_6");
	orderActorToFactory(30000006, EnemyMetis, "Metis_7");
	orderActorToFactory(30000007, EnemyMetis, "Metis_8");
	orderActorToFactory(30000008, EnemyMetis, "Metis_9");
	orderActorToFactory(30000009, EnemyMetis, "Metis_10");
	orderActorToFactory(30000010, EnemyMetis, "Metis_11");
	orderActorToFactory(30000011, EnemyMetis, "Metis_12");
	orderActorToFactory(30000012, EnemyMetis, "Metis_13");
	orderActorToFactory(30000013, EnemyMetis, "Metis_14");
	orderActorToFactory(30000014, EnemyMetis, "Metis_15");
	orderActorToFactory(30000015, EnemyMetis, "Metis_16");
	orderActorToFactory(30000016, EnemyMetis, "Metis_17");
	orderActorToFactory(30000017, EnemyMetis, "Metis_18");
	orderActorToFactory(30000018, EnemyMetis, "Metis_19");
	orderActorToFactory(30000019, EnemyMetis, "Metis_20");
	orderActorToFactory(30000020, EnemyMetis, "Metis_21");
	orderActorToFactory(30000021, EnemyMetis, "Metis_22");
	orderActorToFactory(30000022, EnemyMetis, "Metis_23");
	orderActorToFactory(30000023, EnemyMetis, "Metis_24");
	orderActorToFactory(30000024, EnemyMetis, "Metis_25");
	orderActorToFactory(30000025, EnemyMetis, "Metis_26");
	orderActorToFactory(30000026, EnemyMetis, "Metis_27");
	orderActorToFactory(30000027, EnemyMetis, "Metis_28");
	orderActorToFactory(30000028, EnemyMetis, "Metis_29");
	orderActorToFactory(30000029, EnemyMetis, "Metis_30");
	orderActorToFactory(30000030, EnemyMetis, "Metis_31");
	orderActorToFactory(30000031, EnemyMetis, "Metis_32");
	orderActorToFactory(30000032, EnemyMetis, "Metis_33");
	orderActorToFactory(30000033, EnemyMetis, "Metis_34");
	orderActorToFactory(30000034, EnemyMetis, "Metis_35");
	orderActorToFactory(30000035, EnemyMetis, "Metis_36");
	orderActorToFactory(30000036, EnemyMetis, "Metis_37");
	orderActorToFactory(30000037, EnemyMetis, "Metis_38");
	orderActorToFactory(30000038, EnemyMetis, "Metis_39");
	orderActorToFactory(30000039, EnemyMetis, "Metis_40");
	orderActorToFactory(30000040, EnemyMetis, "Metis_41");
	orderActorToFactory(30000041, EnemyMetis, "Metis_42");
	orderActorToFactory(30000042, EnemyMetis, "Metis_43");
	orderActorToFactory(30000043, EnemyMetis, "Metis_44");
	orderActorToFactory(30000044, EnemyMetis, "Metis_45");
	orderActorToFactory(30000045, EnemyMetis, "Metis_46");
	orderActorToFactory(30000046, EnemyMetis, "Metis_47");
	orderActorToFactory(30000047, EnemyMetis, "Metis_48");
	orderActorToFactory(30000048, EnemyMetis, "Metis_49");
	orderActorToFactory(30000049, EnemyMetis, "Metis_50");
	orderActorToFactory(30000050, EnemyMetis, "Metis_51");
	orderActorToFactory(30000051, EnemyMetis, "Metis_52");
	orderActorToFactory(30000052, EnemyMetis, "Metis_53");
	orderActorToFactory(30000053, EnemyMetis, "Metis_54");
	orderActorToFactory(30000054, EnemyMetis, "Metis_55");
	orderActorToFactory(30000055, EnemyMetis, "Metis_56");
	orderActorToFactory(30000056, EnemyMetis, "Metis_57");
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
			case 1: {
				break;
			}
			case 10: {
				orderActorToFactory(30000057, EnemyMetis, "Metis_58");
				break;
			}
			case 40: {
				orderActorToFactory(30000058, EnemyMetis, "Metis_59");
				break;
			}
			case 70: {
				orderActorToFactory(30000059, EnemyMetis, "Metis_60");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000000);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000060, EnemyMetis, "Metis_61");
				break;
			}
			case 130: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000001);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000061, EnemyMetis, "Metis_62");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000002);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000062, EnemyMetis, "Metis_63");
				break;
			}
			case 190: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000003);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000063, EnemyMetis, "Metis_64");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000004);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000064, EnemyMetis, "Metis_65");
				break;
			}
			case 250: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000005);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000065, EnemyMetis, "Metis_66");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000006);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000066, EnemyMetis, "Metis_67");
				break;
			}
			case 310: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000007);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000067, EnemyMetis, "Metis_68");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000008);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000068, EnemyMetis, "Metis_69");
				break;
			}
			case 370: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000009);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000069, EnemyMetis, "Metis_70");
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000010);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000070, EnemyMetis, "Metis_71");
				break;
			}
			case 430: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000011);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000071, EnemyMetis, "Metis_72");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000012);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000072, EnemyMetis, "Metis_73");
				break;
			}
			case 490: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000013);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000073, EnemyMetis, "Metis_74");
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000014);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000074, EnemyMetis, "Metis_75");
				break;
			}
			case 550: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000015);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000075, EnemyMetis, "Metis_76");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000016);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000076, EnemyMetis, "Metis_77");
				break;
			}
			case 610: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000017);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000077, EnemyMetis, "Metis_78");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000018);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000078, EnemyMetis, "Metis_79");
				break;
			}
			case 670: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000019);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000079, EnemyMetis, "Metis_80");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000020);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000080, EnemyMetis, "Metis_81");
				break;
			}
			case 730: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000021);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000081, EnemyMetis, "Metis_82");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000022);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000082, EnemyMetis, "Metis_83");
				break;
			}
			case 790: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000023);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000083, EnemyMetis, "Metis_84");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000024);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000084, EnemyMetis, "Metis_85");
				break;
			}
			case 850: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000025);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000085, EnemyMetis, "Metis_86");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000026);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000086, EnemyMetis, "Metis_87");
				break;
			}
			case 910: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000027);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000087, EnemyMetis, "Metis_88");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000028);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000088, EnemyMetis, "Metis_89");
				break;
			}
			case 970: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000029);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000089, EnemyMetis, "Metis_90");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000030);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000090, EnemyMetis, "Metis_91");
				break;
			}
			case 1030: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000031);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000091, EnemyMetis, "Metis_92");
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000032);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000092, EnemyMetis, "Metis_93");
				break;
			}
			case 1090: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000033);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000093, EnemyMetis, "Metis_94");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000034);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000094, EnemyMetis, "Metis_95");
				break;
			}
			case 1150: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000035);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000095, EnemyMetis, "Metis_96");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000036);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000096, EnemyMetis, "Metis_97");
				break;
			}
			case 1210: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000037);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000097, EnemyMetis, "Metis_98");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000038);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000098, EnemyMetis, "Metis_99");
				break;
			}
			case 1270: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000039);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000099, EnemyMetis, "Metis_100");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000040);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000100, EnemyMetis, "Metis_101");
				break;
			}
			case 1330: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000041);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000101, EnemyMetis, "Metis_102");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000042);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000102, EnemyMetis, "Metis_103");
				break;
			}
			case 1390: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000043);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000103, EnemyMetis, "Metis_104");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000044);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000104, EnemyMetis, "Metis_105");
				break;
			}
			case 1450: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000045);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000105, EnemyMetis, "Metis_106");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000046);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000106, EnemyMetis, "Metis_107");
				break;
			}
			case 1510: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000047);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000107, EnemyMetis, "Metis_108");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000048);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000108, EnemyMetis, "Metis_109");
				break;
			}
			case 1570: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000049);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000109, EnemyMetis, "Metis_110");
				break;
			}
			case 1600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000050);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000110, EnemyMetis, "Metis_111");
				break;
			}
			case 1630: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000051);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000111, EnemyMetis, "Metis_112");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000052);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000112, EnemyMetis, "Metis_113");
				break;
			}
			case 1690: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000053);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000113, EnemyMetis, "Metis_114");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000054);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000114, EnemyMetis, "Metis_115");
				break;
			}
			case 1750: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000055);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000115, EnemyMetis, "Metis_116");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000056);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000116, EnemyMetis, "Metis_117");
				break;
			}
			case 1810: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000057);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000117, EnemyMetis, "Metis_118");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000058);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000118, EnemyMetis, "Metis_119");
				break;
			}
			case 1870: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000059);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000119, EnemyMetis, "Metis_120");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000060);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000120, EnemyMetis, "Metis_121");
				break;
			}
			case 1930: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000061);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000121, EnemyMetis, "Metis_122");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000062);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000122, EnemyMetis, "Metis_123");
				break;
			}
			case 1990: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000063);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000123, EnemyMetis, "Metis_124");
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000064);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000124, EnemyMetis, "Metis_125");
				break;
			}
			case 2050: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000065);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000125, EnemyMetis, "Metis_126");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000066);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000126, EnemyMetis, "Metis_127");
				break;
			}
			case 2110: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000067);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000127, EnemyMetis, "Metis_128");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000068);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000128, EnemyMetis, "Metis_129");
				break;
			}
			case 2170: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000069);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000129, EnemyMetis, "Metis_130");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000070);
				getLordActor()->addSubGroup(pMetis);
				orderActorToFactory(30000130, EnemyMetis, "Metis_131");
				break;
			}
			case 2230: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000071);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000072);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2290: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000073);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000074);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2350: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000075);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000076);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2410: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000077);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000078);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2470: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000079);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000080);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2530: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000081);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000082);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2590: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000083);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000084);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2650: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000085);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000086);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2710: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000087);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000088);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2770: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000089);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000090);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2830: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000091);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000092);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2890: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000093);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000094);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2950: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000095);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000096);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3010: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000097);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000098);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3070: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000099);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000100);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3130: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000101);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000102);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3190: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000103);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000104);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3250: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000105);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000106);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3310: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000107);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000108);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3370: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000109);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000110);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3430: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000111);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000112);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3490: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000113);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000114);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3550: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000115);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000116);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3610: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000117);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000118);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3670: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000119);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000120);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3730: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000121);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000122);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3790: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000123);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000124);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3850: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000125);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000126);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3910: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000127);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000128);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 3970: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000129);
				getLordActor()->addSubGroup(pMetis);
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000130);
				getLordActor()->addSubGroup(pMetis);
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 135-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
