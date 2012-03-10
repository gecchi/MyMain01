#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,40,70,100,130,160,190,220,250,280,300,310,340,370,400,430,460,490,500,520,550,580,610,640,670,700,730,760,790,820,850,880,910,940,970,1000,1030,1060,1090,1100,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1420,1450,1480,1510,1540,1570,1600,1630,1660,1690,1720,1750,1780,1810,1840,1870,1900,1930,1960,1990,2020,2050,2080,2100,2110,2140,2170,2200,2230,2260,2290,2320,2350,2380,2410,2440,2470,2500,2530,2560,2590,2620,2650,2680,2710,2740,2770,2800,2830,2860,2890,2900,2920,2950,2980,3010,3040,3070,3100,3130,3160,3190,3200,3220,3250,3280,3310,3340,3370,3400,3430,3460,3490,3520,3550,3560,3580,3610,3640,3670,3700,3730,3760,3790,3800,3820,3850,3880,3910,3940,3970,4000,4030,4040,4060,4090,4120,4150,4180,4210,4240,4270,4280,4300,4330,4360,4390,4420,4450,4480,4510,4520,4540,4570,4600,4630,4660,4690,4720,4750,4760,4780,4810,4840,4870,4900,4930,4960,4990,5000,5360,5600,5840,6080,6320,6560,6800,8200,9400,10000,10600,11200,11800,12400,13000,13600,14800,30000};
	_paFrame_NextEvent = new frame[199];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 199;
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
	orderActorToFactory(30000172, EnemyAstraea, "Astraea_58");
	orderActorToFactory(30000173, EnemyAstraea, "Astraea_59");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 10: {
				orderActorToFactory(30000057, EnemyMetis, "Metis_60");
				break;
			}
			case 40: {
				orderActorToFactory(30000058, EnemyMetis, "Metis_61");
				break;
			}
			case 70: {
				orderActorToFactory(30000059, EnemyMetis, "Metis_62");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000000);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000060, EnemyMetis, "Metis_63");
				break;
			}
			case 130: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000001);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000061, EnemyMetis, "Metis_64");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000002);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000062, EnemyMetis, "Metis_65");
				break;
			}
			case 190: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000003);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000063, EnemyMetis, "Metis_66");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000004);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000064, EnemyMetis, "Metis_67");
				break;
			}
			case 250: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000005);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000065, EnemyMetis, "Metis_68");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000006);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000066, EnemyMetis, "Metis_69");
				break;
			}
			case 300: {
				orderActorToFactory(30000174, EnemyAstraea, "Astraea_70");
				break;
			}
			case 310: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000007);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000067, EnemyMetis, "Metis_71");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000008);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000068, EnemyMetis, "Metis_72");
				break;
			}
			case 370: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000009);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000069, EnemyMetis, "Metis_73");
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000010);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000070, EnemyMetis, "Metis_74");
				break;
			}
			case 430: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000011);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000071, EnemyMetis, "Metis_75");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000012);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000072, EnemyMetis, "Metis_76");
				break;
			}
			case 490: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000013);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000073, EnemyMetis, "Metis_77");
				break;
			}
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(30000172);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000014);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000074, EnemyMetis, "Metis_78");
				break;
			}
			case 550: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000015);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000075, EnemyMetis, "Metis_79");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000016);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000076, EnemyMetis, "Metis_80");
				break;
			}
			case 610: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000017);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000077, EnemyMetis, "Metis_81");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000018);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000078, EnemyMetis, "Metis_82");
				break;
			}
			case 670: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000019);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000079, EnemyMetis, "Metis_83");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000020);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000080, EnemyMetis, "Metis_84");
				break;
			}
			case 730: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000021);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000081, EnemyMetis, "Metis_85");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000022);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000082, EnemyMetis, "Metis_86");
				break;
			}
			case 790: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000023);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000083, EnemyMetis, "Metis_87");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000024);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000084, EnemyMetis, "Metis_88");
				break;
			}
			case 850: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000025);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000085, EnemyMetis, "Metis_89");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000026);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000086, EnemyMetis, "Metis_90");
				break;
			}
			case 910: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000027);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000087, EnemyMetis, "Metis_91");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000028);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000088, EnemyMetis, "Metis_92");
				break;
			}
			case 970: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000029);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000089, EnemyMetis, "Metis_93");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000030);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000090, EnemyMetis, "Metis_94");
				break;
			}
			case 1030: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000031);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000091, EnemyMetis, "Metis_95");
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000032);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000092, EnemyMetis, "Metis_96");
				break;
			}
			case 1090: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000033);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000093, EnemyMetis, "Metis_97");
				break;
			}
			case 1100: {
				orderActorToFactory(30000175, EnemyAstraea, "Astraea_98");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000034);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000094, EnemyMetis, "Metis_99");
				break;
			}
			case 1150: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000035);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000095, EnemyMetis, "Metis_100");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000036);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000096, EnemyMetis, "Metis_101");
				break;
			}
			case 1210: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000037);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000097, EnemyMetis, "Metis_102");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000038);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000098, EnemyMetis, "Metis_103");
				break;
			}
			case 1270: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000039);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000099, EnemyMetis, "Metis_104");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000040);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000100, EnemyMetis, "Metis_105");
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(30000173);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 1330: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000041);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000101, EnemyMetis, "Metis_106");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000042);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000102, EnemyMetis, "Metis_107");
				break;
			}
			case 1390: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000043);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000103, EnemyMetis, "Metis_108");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000044);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000104, EnemyMetis, "Metis_109");
				break;
			}
			case 1450: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000045);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000105, EnemyMetis, "Metis_110");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000046);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000106, EnemyMetis, "Metis_111");
				break;
			}
			case 1510: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000047);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000107, EnemyMetis, "Metis_112");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000048);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000108, EnemyMetis, "Metis_113");
				break;
			}
			case 1570: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000049);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000109, EnemyMetis, "Metis_114");
				break;
			}
			case 1600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000050);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000110, EnemyMetis, "Metis_115");
				break;
			}
			case 1630: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000051);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000111, EnemyMetis, "Metis_116");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000052);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000112, EnemyMetis, "Metis_117");
				break;
			}
			case 1690: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000053);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000113, EnemyMetis, "Metis_118");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000054);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000114, EnemyMetis, "Metis_119");
				break;
			}
			case 1750: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000055);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000115, EnemyMetis, "Metis_120");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000056);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000116, EnemyMetis, "Metis_121");
				break;
			}
			case 1810: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000057);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000117, EnemyMetis, "Metis_122");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000058);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000118, EnemyMetis, "Metis_123");
				break;
			}
			case 1870: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000059);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000119, EnemyMetis, "Metis_124");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000060);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000120, EnemyMetis, "Metis_125");
				orderActorToFactory(30000176, EnemyAstraea, "Astraea_126");
				break;
			}
			case 1930: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000061);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000121, EnemyMetis, "Metis_127");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000062);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000122, EnemyMetis, "Metis_128");
				break;
			}
			case 1990: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000063);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000123, EnemyMetis, "Metis_129");
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000064);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000124, EnemyMetis, "Metis_130");
				break;
			}
			case 2050: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000065);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000125, EnemyMetis, "Metis_131");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000066);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000126, EnemyMetis, "Metis_132");
				break;
			}
			case 2100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(30000174);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2110: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000067);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000127, EnemyMetis, "Metis_133");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000068);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000128, EnemyMetis, "Metis_134");
				break;
			}
			case 2170: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000069);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000129, EnemyMetis, "Metis_135");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000070);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000130, EnemyMetis, "Metis_136");
				break;
			}
			case 2230: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000071);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000131, EnemyMetis, "Metis_137");
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000072);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000132, EnemyMetis, "Metis_138");
				break;
			}
			case 2290: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000073);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000133, EnemyMetis, "Metis_139");
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000074);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000134, EnemyMetis, "Metis_140");
				break;
			}
			case 2350: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000075);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000135, EnemyMetis, "Metis_141");
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000076);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000136, EnemyMetis, "Metis_142");
				break;
			}
			case 2410: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000077);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000137, EnemyMetis, "Metis_143");
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000078);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000138, EnemyMetis, "Metis_144");
				break;
			}
			case 2470: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000079);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000139, EnemyMetis, "Metis_145");
				break;
			}
			case 2500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000080);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000140, EnemyMetis, "Metis_146");
				break;
			}
			case 2530: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000081);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000141, EnemyMetis, "Metis_147");
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000082);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000142, EnemyMetis, "Metis_148");
				break;
			}
			case 2590: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000083);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000143, EnemyMetis, "Metis_149");
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000084);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000144, EnemyMetis, "Metis_150");
				break;
			}
			case 2650: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000085);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000145, EnemyMetis, "Metis_151");
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000086);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000146, EnemyMetis, "Metis_152");
				break;
			}
			case 2710: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000087);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000147, EnemyMetis, "Metis_153");
				break;
			}
			case 2740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000088);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000148, EnemyMetis, "Metis_154");
				break;
			}
			case 2770: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000089);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000149, EnemyMetis, "Metis_155");
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000090);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000150, EnemyMetis, "Metis_156");
				break;
			}
			case 2830: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000091);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000151, EnemyMetis, "Metis_157");
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000092);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000152, EnemyMetis, "Metis_158");
				break;
			}
			case 2890: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000093);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000153, EnemyMetis, "Metis_159");
				break;
			}
			case 2900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(30000175);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000094);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000154, EnemyMetis, "Metis_160");
				break;
			}
			case 2950: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000095);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000155, EnemyMetis, "Metis_161");
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000096);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000156, EnemyMetis, "Metis_162");
				break;
			}
			case 3010: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000097);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000157, EnemyMetis, "Metis_163");
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000098);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000158, EnemyMetis, "Metis_164");
				break;
			}
			case 3070: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000099);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000159, EnemyMetis, "Metis_165");
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000100);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000160, EnemyMetis, "Metis_166");
				break;
			}
			case 3130: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000101);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000161, EnemyMetis, "Metis_167");
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000102);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000162, EnemyMetis, "Metis_168");
				break;
			}
			case 3190: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000103);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(30000163, EnemyMetis, "Metis_169");
				break;
			}
			case 3200: {
				orderActorToFactory(30000164, FormationEunomia001a, "F001a_Eunomia_170");
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000104);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3250: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000105);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000106);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3310: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000107);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000108);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3370: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000109);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000110);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3430: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000111);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000112);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3490: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000113);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000114);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3550: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000115);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3560: {
				orderActorToFactory(30000165, FormationEunomia001b, "F001b_Eunomia_171");
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000116);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3610: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000117);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000118);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3670: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000119);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000120);
				getDirector()->addSubGroup(pMetis);
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(30000176);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 3730: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000121);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000122);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3790: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000123);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3800: {
				orderActorToFactory(30000166, FormationEunomia001a, "F001a_Eunomia_172");
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000124);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3850: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000125);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000126);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3910: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000127);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000128);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 3970: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000129);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000130);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4030: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000131);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4040: {
				orderActorToFactory(30000167, FormationEunomia001b, "F001b_Eunomia_173");
				break;
			}
			case 4060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000132);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4090: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000133);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000134);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4150: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000135);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000136);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4210: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000137);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000138);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4270: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000139);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4280: {
				orderActorToFactory(30000168, FormationEunomia001a, "F001a_Eunomia_174");
				break;
			}
			case 4300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000140);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4330: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000141);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000142);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4390: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000143);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000144);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4450: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000145);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000146);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4510: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000147);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4520: {
				orderActorToFactory(30000169, FormationEunomia001b, "F001b_Eunomia_175");
				break;
			}
			case 4540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000148);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4570: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000149);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000150);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4630: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000151);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000152);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4690: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000153);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000154);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4750: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000155);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4760: {
				orderActorToFactory(30000170, FormationEunomia001a, "F001a_Eunomia_176");
				break;
			}
			case 4780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000156);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4810: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000157);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000158);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4870: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000159);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000160);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4930: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000161);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000162);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4990: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(30000163);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 5000: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000164);
				getDirector()->addSubGroup(pFormationEunomia);
				orderActorToFactory(30000171, FormationEunomia001b, "F001b_Eunomia_177");
				break;
			}
			case 5360: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000165);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 5600: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000166);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 5840: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000167);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6080: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000168);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6320: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000169);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6560: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000170);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 6800: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000171);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 8200: {
				orderActorToFactory(30000177, FormationMassalia, "FormationMassalia_178");
				break;
			}
			case 9400: {
				orderActorToFactory(30000178, FormationMassalia, "FormationMassalia_179");
				break;
			}
			case 10000: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(30000177);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 10600: {
				orderActorToFactory(30000179, FormationMassalia, "FormationMassalia_180");
				break;
			}
			case 11200: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(30000178);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 11800: {
				orderActorToFactory(30000180, FormationMassalia, "FormationMassalia_181");
				break;
			}
			case 12400: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(30000179);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 13000: {
				orderActorToFactory(30000181, FormationMassalia, "FormationMassalia_182");
				break;
			}
			case 13600: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(30000180);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 14800: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(30000181);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 30000: {
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 199-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01_01::~Stage01_01() {

}
