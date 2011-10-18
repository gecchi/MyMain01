#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp001::RankUp001(const char* prm_name) : RankUpScene(prm_name) {
    _class_name = "RankUp001";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,1000,1010,1020,1030,1040,1050,1060,1070,1080,1090,1100,1110,1120,1130,1140,1150,1160,1170,1180,1190,1200,1210,1220,1230,1240,1250,1260,1270,1280,1290,1300,1310,1320,1330,1340,1350,1360,1370,1380,1390,1400,1410,1420,1430,1440,1450,1460,1470,1480,1490,1500,1510,1520,1530,1540,1550,1560,1570,1580,1590,1600,1610,1620,1630,1640,1650,1660,1670,1680,1690,1700,1710,1720,1730,1740,1750,1760,1770,1780,1790,1800,1810,1820,1830,1840,1850,1860,1870,1880,1890,1900,1910,1920,1930,1940,1950,1960,1970,1980,1990,2000};
	_paFrame_NextEvent = new frame[201];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 201;
	orderActorToFactory(80000000, EnemyCirce, "EnemyCirce_1");
	orderActorToFactory(80000001, EnemyCirce, "EnemyCirce_2");
	orderActorToFactory(80000002, EnemyCirce, "EnemyCirce_3");
	orderActorToFactory(80000003, EnemyCirce, "EnemyCirce_4");
	orderActorToFactory(80000004, EnemyCirce, "EnemyCirce_5");
	orderActorToFactory(80000005, EnemyCirce, "EnemyCirce_6");
	orderActorToFactory(80000006, EnemyCirce, "EnemyCirce_7");
	orderActorToFactory(80000007, EnemyCirce, "EnemyCirce_8");
	orderActorToFactory(80000008, EnemyCirce, "EnemyCirce_9");
	orderActorToFactory(80000009, EnemyCirce, "EnemyCirce_10");
	orderActorToFactory(80000010, EnemyCirce, "EnemyCirce_11");
	orderActorToFactory(80000011, EnemyCirce, "EnemyCirce_12");
	orderActorToFactory(80000012, EnemyCirce, "EnemyCirce_13");
	orderActorToFactory(80000013, EnemyCirce, "EnemyCirce_14");
	orderActorToFactory(80000014, EnemyCirce, "EnemyCirce_15");
	orderActorToFactory(80000015, EnemyCirce, "EnemyCirce_16");
	orderActorToFactory(80000016, EnemyCirce, "EnemyCirce_17");
	orderActorToFactory(80000017, EnemyCirce, "EnemyCirce_18");
	orderActorToFactory(80000018, EnemyCirce, "EnemyCirce_19");
	orderActorToFactory(80000019, EnemyCirce, "EnemyCirce_20");
	orderActorToFactory(80000020, EnemyCirce, "EnemyCirce_21");
	orderActorToFactory(80000021, EnemyCirce, "EnemyCirce_22");
	orderActorToFactory(80000022, EnemyCirce, "EnemyCirce_23");
	orderActorToFactory(80000023, EnemyCirce, "EnemyCirce_24");
	orderActorToFactory(80000024, EnemyCirce, "EnemyCirce_25");
	orderActorToFactory(80000025, EnemyCirce, "EnemyCirce_26");
	orderActorToFactory(80000026, EnemyCirce, "EnemyCirce_27");
	orderActorToFactory(80000027, EnemyCirce, "EnemyCirce_28");
	orderActorToFactory(80000028, EnemyCirce, "EnemyCirce_29");
	orderActorToFactory(80000029, EnemyCirce, "EnemyCirce_30");
	orderActorToFactory(80000030, EnemyCirce, "EnemyCirce_31");
	orderActorToFactory(80000031, EnemyCirce, "EnemyCirce_32");
	orderActorToFactory(80000032, EnemyCirce, "EnemyCirce_33");
	orderActorToFactory(80000033, EnemyCirce, "EnemyCirce_34");
	orderActorToFactory(80000034, EnemyCirce, "EnemyCirce_35");
	orderActorToFactory(80000035, EnemyCirce, "EnemyCirce_36");
	orderActorToFactory(80000036, EnemyCirce, "EnemyCirce_37");
	orderActorToFactory(80000037, EnemyCirce, "EnemyCirce_38");
	orderActorToFactory(80000038, EnemyCirce, "EnemyCirce_39");
	orderActorToFactory(80000039, EnemyCirce, "EnemyCirce_40");
	orderActorToFactory(80000040, EnemyCirce, "EnemyCirce_41");
	orderActorToFactory(80000041, EnemyCirce, "EnemyCirce_42");
	orderActorToFactory(80000042, EnemyCirce, "EnemyCirce_43");
	orderActorToFactory(80000043, EnemyCirce, "EnemyCirce_44");
	orderActorToFactory(80000044, EnemyCirce, "EnemyCirce_45");
	orderActorToFactory(80000045, EnemyCirce, "EnemyCirce_46");
	orderActorToFactory(80000046, EnemyCirce, "EnemyCirce_47");
	orderActorToFactory(80000047, EnemyCirce, "EnemyCirce_48");
	orderActorToFactory(80000048, EnemyCirce, "EnemyCirce_49");
	orderActorToFactory(80000049, EnemyCirce, "EnemyCirce_50");
	orderActorToFactory(80000050, EnemyCirce, "EnemyCirce_51");
	orderActorToFactory(80000051, EnemyCirce, "EnemyCirce_52");
	orderActorToFactory(80000052, EnemyCirce, "EnemyCirce_53");
	orderActorToFactory(80000053, EnemyCirce, "EnemyCirce_54");
	orderActorToFactory(80000054, EnemyCirce, "EnemyCirce_55");
	orderActorToFactory(80000055, EnemyCirce, "EnemyCirce_56");
	orderActorToFactory(80000056, EnemyCirce, "EnemyCirce_57");
	orderActorToFactory(80000057, EnemyCirce, "EnemyCirce_58");
	orderActorToFactory(80000058, EnemyCirce, "EnemyCirce_59");
	orderActorToFactory(80000059, EnemyCirce, "EnemyCirce_60");
	orderActorToFactory(80000060, EnemyCirce, "EnemyCirce_61");
	orderActorToFactory(80000061, EnemyCirce, "EnemyCirce_62");
	orderActorToFactory(80000062, EnemyCirce, "EnemyCirce_63");
	orderActorToFactory(80000063, EnemyCirce, "EnemyCirce_64");
	orderActorToFactory(80000064, EnemyCirce, "EnemyCirce_65");
	orderActorToFactory(80000065, EnemyCirce, "EnemyCirce_66");
	orderActorToFactory(80000066, EnemyCirce, "EnemyCirce_67");
	orderActorToFactory(80000067, EnemyCirce, "EnemyCirce_68");
	orderActorToFactory(80000068, EnemyCirce, "EnemyCirce_69");
	orderActorToFactory(80000069, EnemyCirce, "EnemyCirce_70");
	orderActorToFactory(80000070, EnemyCirce, "EnemyCirce_71");
	orderActorToFactory(80000071, EnemyCirce, "EnemyCirce_72");
	orderActorToFactory(80000072, EnemyCirce, "EnemyCirce_73");
	orderActorToFactory(80000073, EnemyCirce, "EnemyCirce_74");
	orderActorToFactory(80000074, EnemyCirce, "EnemyCirce_75");
	orderActorToFactory(80000075, EnemyCirce, "EnemyCirce_76");
	orderActorToFactory(80000076, EnemyCirce, "EnemyCirce_77");
	orderActorToFactory(80000077, EnemyCirce, "EnemyCirce_78");
	orderActorToFactory(80000078, EnemyCirce, "EnemyCirce_79");
	orderActorToFactory(80000079, EnemyCirce, "EnemyCirce_80");
	orderActorToFactory(80000080, EnemyCirce, "EnemyCirce_81");
	orderActorToFactory(80000081, EnemyCirce, "EnemyCirce_82");
	orderActorToFactory(80000082, EnemyCirce, "EnemyCirce_83");
	orderActorToFactory(80000083, EnemyCirce, "EnemyCirce_84");
	orderActorToFactory(80000084, EnemyCirce, "EnemyCirce_85");
	orderActorToFactory(80000085, EnemyCirce, "EnemyCirce_86");
	orderActorToFactory(80000086, EnemyCirce, "EnemyCirce_87");
	orderActorToFactory(80000087, EnemyCirce, "EnemyCirce_88");
	orderActorToFactory(80000088, EnemyCirce, "EnemyCirce_89");
	orderActorToFactory(80000089, EnemyCirce, "EnemyCirce_90");
	orderActorToFactory(80000090, EnemyCirce, "EnemyCirce_91");
	orderActorToFactory(80000091, EnemyCirce, "EnemyCirce_92");
	orderActorToFactory(80000092, EnemyCirce, "EnemyCirce_93");
	orderActorToFactory(80000093, EnemyCirce, "EnemyCirce_94");
	orderActorToFactory(80000094, EnemyCirce, "EnemyCirce_95");
	orderActorToFactory(80000095, EnemyCirce, "EnemyCirce_96");
	orderActorToFactory(80000096, EnemyCirce, "EnemyCirce_97");
	orderActorToFactory(80000097, EnemyCirce, "EnemyCirce_98");
	orderActorToFactory(80000098, EnemyCirce, "EnemyCirce_99");
	orderActorToFactory(80000099, EnemyCirce, "EnemyCirce_100");
	orderActorToFactory(80000100, EnemyCirce, "EnemyCirce_101");
	orderActorToFactory(80000101, EnemyCirce, "EnemyCirce_102");
	orderActorToFactory(80000102, EnemyCirce, "EnemyCirce_103");
	orderActorToFactory(80000103, EnemyCirce, "EnemyCirce_104");
	orderActorToFactory(80000104, EnemyCirce, "EnemyCirce_105");
	orderActorToFactory(80000105, EnemyCirce, "EnemyCirce_106");
	orderActorToFactory(80000106, EnemyCirce, "EnemyCirce_107");
	orderActorToFactory(80000107, EnemyCirce, "EnemyCirce_108");
	orderActorToFactory(80000108, EnemyCirce, "EnemyCirce_109");
	orderActorToFactory(80000109, EnemyCirce, "EnemyCirce_110");
	orderActorToFactory(80000110, EnemyCirce, "EnemyCirce_111");
	orderActorToFactory(80000111, EnemyCirce, "EnemyCirce_112");
	orderActorToFactory(80000112, EnemyCirce, "EnemyCirce_113");
	orderActorToFactory(80000113, EnemyCirce, "EnemyCirce_114");
	orderActorToFactory(80000114, EnemyCirce, "EnemyCirce_115");
	orderActorToFactory(80000115, EnemyCirce, "EnemyCirce_116");
	orderActorToFactory(80000116, EnemyCirce, "EnemyCirce_117");
	orderActorToFactory(80000117, EnemyCirce, "EnemyCirce_118");
	orderActorToFactory(80000118, EnemyCirce, "EnemyCirce_119");
	orderActorToFactory(80000119, EnemyCirce, "EnemyCirce_120");
	orderActorToFactory(80000120, EnemyCirce, "EnemyCirce_121");
	orderActorToFactory(80000121, EnemyCirce, "EnemyCirce_122");
	orderActorToFactory(80000122, EnemyCirce, "EnemyCirce_123");
	orderActorToFactory(80000123, EnemyCirce, "EnemyCirce_124");
	orderActorToFactory(80000124, EnemyCirce, "EnemyCirce_125");
	orderActorToFactory(80000125, EnemyCirce, "EnemyCirce_126");
	orderActorToFactory(80000126, EnemyCirce, "EnemyCirce_127");
	orderActorToFactory(80000127, EnemyCirce, "EnemyCirce_128");
	orderActorToFactory(80000128, EnemyCirce, "EnemyCirce_129");
	orderActorToFactory(80000129, EnemyCirce, "EnemyCirce_130");
	orderActorToFactory(80000130, EnemyCirce, "EnemyCirce_131");
	orderActorToFactory(80000131, EnemyCirce, "EnemyCirce_132");
	orderActorToFactory(80000132, EnemyCirce, "EnemyCirce_133");
	orderActorToFactory(80000133, EnemyCirce, "EnemyCirce_134");
	orderActorToFactory(80000134, EnemyCirce, "EnemyCirce_135");
	orderActorToFactory(80000135, EnemyCirce, "EnemyCirce_136");
	orderActorToFactory(80000136, EnemyCirce, "EnemyCirce_137");
	orderActorToFactory(80000137, EnemyCirce, "EnemyCirce_138");
	orderActorToFactory(80000138, EnemyCirce, "EnemyCirce_139");
	orderActorToFactory(80000139, EnemyCirce, "EnemyCirce_140");
	orderActorToFactory(80000140, EnemyCirce, "EnemyCirce_141");
	orderActorToFactory(80000141, EnemyCirce, "EnemyCirce_142");
	orderActorToFactory(80000142, EnemyCirce, "EnemyCirce_143");
	orderActorToFactory(80000143, EnemyCirce, "EnemyCirce_144");
	orderActorToFactory(80000144, EnemyCirce, "EnemyCirce_145");
	orderActorToFactory(80000145, EnemyCirce, "EnemyCirce_146");
	orderActorToFactory(80000146, EnemyCirce, "EnemyCirce_147");
	orderActorToFactory(80000147, EnemyCirce, "EnemyCirce_148");
	orderActorToFactory(80000148, EnemyCirce, "EnemyCirce_149");
	orderActorToFactory(80000149, EnemyCirce, "EnemyCirce_150");
	orderActorToFactory(80000150, EnemyCirce, "EnemyCirce_151");
	orderActorToFactory(80000151, EnemyCirce, "EnemyCirce_152");
	orderActorToFactory(80000152, EnemyCirce, "EnemyCirce_153");
	orderActorToFactory(80000153, EnemyCirce, "EnemyCirce_154");
	orderActorToFactory(80000154, EnemyCirce, "EnemyCirce_155");
	orderActorToFactory(80000155, EnemyCirce, "EnemyCirce_156");
	orderActorToFactory(80000156, EnemyCirce, "EnemyCirce_157");
	orderActorToFactory(80000157, EnemyCirce, "EnemyCirce_158");
	orderActorToFactory(80000158, EnemyCirce, "EnemyCirce_159");
	orderActorToFactory(80000159, EnemyCirce, "EnemyCirce_160");
	orderActorToFactory(80000160, EnemyCirce, "EnemyCirce_161");
    // gen01 end
}

void RankUp001::initialize() {
    RankUpScene::initialize();
}

void RankUp001::processBehavior() {
    RankUpScene::processBehavior();

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 10: {
				orderActorToFactory(80000161, EnemyCirce, "EnemyCirce_162");
				break;
			}
			case 20: {
				orderActorToFactory(80000162, EnemyCirce, "EnemyCirce_163");
				break;
			}
			case 30: {
				orderActorToFactory(80000163, EnemyCirce, "EnemyCirce_164");
				break;
			}
			case 40: {
				orderActorToFactory(80000164, EnemyCirce, "EnemyCirce_165");
				break;
			}
			case 50: {
				orderActorToFactory(80000165, EnemyCirce, "EnemyCirce_166");
				break;
			}
			case 60: {
				orderActorToFactory(80000166, EnemyCirce, "EnemyCirce_167");
				break;
			}
			case 70: {
				orderActorToFactory(80000167, EnemyCirce, "EnemyCirce_168");
				break;
			}
			case 80: {
				orderActorToFactory(80000168, EnemyCirce, "EnemyCirce_169");
				break;
			}
			case 90: {
				orderActorToFactory(80000169, EnemyCirce, "EnemyCirce_170");
				break;
			}
			case 100: {
				orderActorToFactory(80000170, EnemyCirce, "EnemyCirce_171");
				break;
			}
			case 110: {
				orderActorToFactory(80000171, EnemyCirce, "EnemyCirce_172");
				break;
			}
			case 120: {
				orderActorToFactory(80000172, EnemyCirce, "EnemyCirce_173");
				break;
			}
			case 130: {
				orderActorToFactory(80000173, EnemyCirce, "EnemyCirce_174");
				break;
			}
			case 140: {
				orderActorToFactory(80000174, EnemyCirce, "EnemyCirce_175");
				break;
			}
			case 150: {
				orderActorToFactory(80000175, EnemyCirce, "EnemyCirce_176");
				break;
			}
			case 160: {
				orderActorToFactory(80000176, EnemyCirce, "EnemyCirce_177");
				break;
			}
			case 170: {
				orderActorToFactory(80000177, EnemyCirce, "EnemyCirce_178");
				break;
			}
			case 180: {
				orderActorToFactory(80000178, EnemyCirce, "EnemyCirce_179");
				break;
			}
			case 190: {
				orderActorToFactory(80000179, EnemyCirce, "EnemyCirce_180");
				break;
			}
			case 200: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000000);
				getDirector()->addSubGroup(p);
				orderActorToFactory(80000180, EnemyCirce, "EnemyCirce_181");
				break;
			}
			case 210: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000001);
				getDirector()->addSubGroup(p);
				break;
			}
			case 220: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000002);
				getDirector()->addSubGroup(p);
				break;
			}
			case 230: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000003);
				getDirector()->addSubGroup(p);
				break;
			}
			case 240: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000004);
				getDirector()->addSubGroup(p);
				break;
			}
			case 250: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000005);
				getDirector()->addSubGroup(p);
				break;
			}
			case 260: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000006);
				getDirector()->addSubGroup(p);
				break;
			}
			case 270: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000007);
				getDirector()->addSubGroup(p);
				break;
			}
			case 280: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000008);
				getDirector()->addSubGroup(p);
				break;
			}
			case 290: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000009);
				getDirector()->addSubGroup(p);
				break;
			}
			case 300: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000010);
				getDirector()->addSubGroup(p);
				break;
			}
			case 310: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000011);
				getDirector()->addSubGroup(p);
				break;
			}
			case 320: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000012);
				getDirector()->addSubGroup(p);
				break;
			}
			case 330: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000013);
				getDirector()->addSubGroup(p);
				break;
			}
			case 340: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000014);
				getDirector()->addSubGroup(p);
				break;
			}
			case 350: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000015);
				getDirector()->addSubGroup(p);
				break;
			}
			case 360: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000016);
				getDirector()->addSubGroup(p);
				break;
			}
			case 370: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000017);
				getDirector()->addSubGroup(p);
				break;
			}
			case 380: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000018);
				getDirector()->addSubGroup(p);
				break;
			}
			case 390: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000019);
				getDirector()->addSubGroup(p);
				break;
			}
			case 400: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000020);
				getDirector()->addSubGroup(p);
				break;
			}
			case 410: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000021);
				getDirector()->addSubGroup(p);
				break;
			}
			case 420: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000022);
				getDirector()->addSubGroup(p);
				break;
			}
			case 430: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000023);
				getDirector()->addSubGroup(p);
				break;
			}
			case 440: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000024);
				getDirector()->addSubGroup(p);
				break;
			}
			case 450: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000025);
				getDirector()->addSubGroup(p);
				break;
			}
			case 460: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000026);
				getDirector()->addSubGroup(p);
				break;
			}
			case 470: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000027);
				getDirector()->addSubGroup(p);
				break;
			}
			case 480: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000028);
				getDirector()->addSubGroup(p);
				break;
			}
			case 490: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000029);
				getDirector()->addSubGroup(p);
				break;
			}
			case 500: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000030);
				getDirector()->addSubGroup(p);
				break;
			}
			case 510: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000031);
				getDirector()->addSubGroup(p);
				break;
			}
			case 520: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000032);
				getDirector()->addSubGroup(p);
				break;
			}
			case 530: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000033);
				getDirector()->addSubGroup(p);
				break;
			}
			case 540: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000034);
				getDirector()->addSubGroup(p);
				break;
			}
			case 550: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000035);
				getDirector()->addSubGroup(p);
				break;
			}
			case 560: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000036);
				getDirector()->addSubGroup(p);
				break;
			}
			case 570: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000037);
				getDirector()->addSubGroup(p);
				break;
			}
			case 580: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000038);
				getDirector()->addSubGroup(p);
				break;
			}
			case 590: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000039);
				getDirector()->addSubGroup(p);
				break;
			}
			case 600: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000040);
				getDirector()->addSubGroup(p);
				break;
			}
			case 610: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000041);
				getDirector()->addSubGroup(p);
				break;
			}
			case 620: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000042);
				getDirector()->addSubGroup(p);
				break;
			}
			case 630: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000043);
				getDirector()->addSubGroup(p);
				break;
			}
			case 640: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000044);
				getDirector()->addSubGroup(p);
				break;
			}
			case 650: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000045);
				getDirector()->addSubGroup(p);
				break;
			}
			case 660: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000046);
				getDirector()->addSubGroup(p);
				break;
			}
			case 670: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000047);
				getDirector()->addSubGroup(p);
				break;
			}
			case 680: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000048);
				getDirector()->addSubGroup(p);
				break;
			}
			case 690: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000049);
				getDirector()->addSubGroup(p);
				break;
			}
			case 700: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000050);
				getDirector()->addSubGroup(p);
				break;
			}
			case 710: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000051);
				getDirector()->addSubGroup(p);
				break;
			}
			case 720: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000052);
				getDirector()->addSubGroup(p);
				break;
			}
			case 730: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000053);
				getDirector()->addSubGroup(p);
				break;
			}
			case 740: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000054);
				getDirector()->addSubGroup(p);
				break;
			}
			case 750: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000055);
				getDirector()->addSubGroup(p);
				break;
			}
			case 760: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000056);
				getDirector()->addSubGroup(p);
				break;
			}
			case 770: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000057);
				getDirector()->addSubGroup(p);
				break;
			}
			case 780: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000058);
				getDirector()->addSubGroup(p);
				break;
			}
			case 790: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000059);
				getDirector()->addSubGroup(p);
				break;
			}
			case 800: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000060);
				getDirector()->addSubGroup(p);
				break;
			}
			case 810: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000061);
				getDirector()->addSubGroup(p);
				break;
			}
			case 820: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000062);
				getDirector()->addSubGroup(p);
				break;
			}
			case 830: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000063);
				getDirector()->addSubGroup(p);
				break;
			}
			case 840: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000064);
				getDirector()->addSubGroup(p);
				break;
			}
			case 850: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000065);
				getDirector()->addSubGroup(p);
				break;
			}
			case 860: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000066);
				getDirector()->addSubGroup(p);
				break;
			}
			case 870: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000067);
				getDirector()->addSubGroup(p);
				break;
			}
			case 880: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000068);
				getDirector()->addSubGroup(p);
				break;
			}
			case 890: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000069);
				getDirector()->addSubGroup(p);
				break;
			}
			case 900: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000070);
				getDirector()->addSubGroup(p);
				break;
			}
			case 910: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000071);
				getDirector()->addSubGroup(p);
				break;
			}
			case 920: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000072);
				getDirector()->addSubGroup(p);
				break;
			}
			case 930: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000073);
				getDirector()->addSubGroup(p);
				break;
			}
			case 940: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000074);
				getDirector()->addSubGroup(p);
				break;
			}
			case 950: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000075);
				getDirector()->addSubGroup(p);
				break;
			}
			case 960: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000076);
				getDirector()->addSubGroup(p);
				break;
			}
			case 970: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000077);
				getDirector()->addSubGroup(p);
				break;
			}
			case 980: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000078);
				getDirector()->addSubGroup(p);
				break;
			}
			case 990: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000079);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1000: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000080);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1010: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000081);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1020: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000082);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1030: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000083);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1040: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000084);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1050: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000085);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1060: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000086);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1070: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000087);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1080: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000088);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1090: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000089);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1100: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000090);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1110: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000091);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1120: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000092);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1130: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000093);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1140: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000094);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1150: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000095);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1160: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000096);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1170: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000097);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1180: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000098);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1190: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000099);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1200: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000100);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1210: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000101);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1220: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000102);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1230: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000103);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1240: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000104);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1250: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000105);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1260: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000106);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1270: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000107);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1280: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000108);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1290: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000109);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1300: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000110);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1310: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000111);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1320: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000112);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1330: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000113);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1340: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000114);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1350: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000115);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1360: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000116);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1370: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000117);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1380: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000118);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1390: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000119);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1400: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000120);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1410: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000121);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1420: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000122);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1430: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000123);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1440: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000124);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1450: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000125);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1460: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000126);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1470: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000127);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1480: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000128);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1490: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000129);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1500: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000130);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1510: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000131);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1520: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000132);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1530: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000133);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1540: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000134);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1550: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000135);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1560: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000136);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1570: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000137);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1580: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000138);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1590: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000139);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1600: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000140);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1610: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000141);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1620: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000142);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1630: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000143);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1640: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000144);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1650: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000145);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1660: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000146);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1670: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000147);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1680: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000148);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1690: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000149);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1700: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000150);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1710: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000151);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1720: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000152);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1730: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000153);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1740: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000154);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1750: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000155);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1760: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000156);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1770: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000157);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1780: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000158);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1790: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000159);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1800: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000160);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1810: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000161);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1820: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000162);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1830: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000163);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1840: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000164);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1850: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000165);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1860: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000166);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1870: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000167);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1880: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000168);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1890: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000169);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1900: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000170);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1910: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000171);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1920: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000172);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1930: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000173);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1940: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000174);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1950: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000175);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1960: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000176);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1970: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000177);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1980: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000178);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1990: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000179);
				getDirector()->addSubGroup(p);
				break;
			}
			case 2000: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000180);
				getDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 201-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case RANKUPSCENE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp001::processBehavior() RANKUPSCENE_PROG_PLAYING になりますた！");
            }

            if (_pProg->getFrameInProgress() == 2500) {
                _TRACE_("RankUp001::processBehavior() RANKUPSCENE_PROG_PLAYING おわった");
                _pProg->change(RANKUPSCENE_PROG_RESULT); //RankUpSceneの共通処理へ
            }
            break;
        }
    }

}

void RankUp001::processJudgement() {
}


void RankUp001::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}


RankUp001::~RankUp001() {

}
