#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp002::RankUp002(const char* prm_name) : RankUpScene(prm_name) {
    _class_name = "RankUp002";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,1000,1010,1020,1030,1040,1050,1060,1070,1080,1090,1100,1110,1120,1130,1140,1150,1160,1170,1180,1190,1200,1210,1220,1230,1240,1250,1260,1270,1280,1290,1300,1310,1320,1330,1340,1350,1360,1370,1380,1390,1400,1410,1420,1430,1440,1450,1460,1470,1480,1490,1500,1510,1520,1530,1540,1550,1560,1570,1580,1590,1600,1610,1620,1630,1640,1650,1660,1670,1680,1690,1700,1710,1720,1730,1740,1750,1760,1770,1780,1790,1800,1810,1820,1830,1840,1850,1860,1870,1880,1890,1900,1910,1920,1930,1940,1950,1960,1970,1980,1990,2000};
	_paFrame_NextEvent = new frame[201];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 201;
	orderActorToFactory(90000000, EnemyTamago01, "EnemyTamago01_1");
	orderActorToFactory(90000001, EnemyTamago01, "EnemyTamago01_2");
	orderActorToFactory(90000002, EnemyTamago01, "EnemyTamago01_3");
	orderActorToFactory(90000003, EnemyTamago01, "EnemyTamago01_4");
	orderActorToFactory(90000004, EnemyTamago01, "EnemyTamago01_5");
	orderActorToFactory(90000005, EnemyTamago01, "EnemyTamago01_6");
	orderActorToFactory(90000006, EnemyTamago01, "EnemyTamago01_7");
	orderActorToFactory(90000007, EnemyTamago01, "EnemyTamago01_8");
	orderActorToFactory(90000008, EnemyTamago01, "EnemyTamago01_9");
	orderActorToFactory(90000009, EnemyTamago01, "EnemyTamago01_10");
	orderActorToFactory(90000010, EnemyTamago01, "EnemyTamago01_11");
	orderActorToFactory(90000011, EnemyTamago01, "EnemyTamago01_12");
	orderActorToFactory(90000012, EnemyTamago01, "EnemyTamago01_13");
	orderActorToFactory(90000013, EnemyTamago01, "EnemyTamago01_14");
	orderActorToFactory(90000014, EnemyTamago01, "EnemyTamago01_15");
	orderActorToFactory(90000015, EnemyTamago01, "EnemyTamago01_16");
	orderActorToFactory(90000016, EnemyTamago01, "EnemyTamago01_17");
	orderActorToFactory(90000017, EnemyTamago01, "EnemyTamago01_18");
	orderActorToFactory(90000018, EnemyTamago01, "EnemyTamago01_19");
	orderActorToFactory(90000019, EnemyTamago01, "EnemyTamago01_20");
	orderActorToFactory(90000020, EnemyTamago01, "EnemyTamago01_21");
	orderActorToFactory(90000021, EnemyTamago01, "EnemyTamago01_22");
	orderActorToFactory(90000022, EnemyTamago01, "EnemyTamago01_23");
	orderActorToFactory(90000023, EnemyTamago01, "EnemyTamago01_24");
	orderActorToFactory(90000024, EnemyTamago01, "EnemyTamago01_25");
	orderActorToFactory(90000025, EnemyTamago01, "EnemyTamago01_26");
	orderActorToFactory(90000026, EnemyTamago01, "EnemyTamago01_27");
	orderActorToFactory(90000027, EnemyTamago01, "EnemyTamago01_28");
	orderActorToFactory(90000028, EnemyTamago01, "EnemyTamago01_29");
	orderActorToFactory(90000029, EnemyTamago01, "EnemyTamago01_30");
	orderActorToFactory(90000030, EnemyTamago01, "EnemyTamago01_31");
	orderActorToFactory(90000031, EnemyTamago01, "EnemyTamago01_32");
	orderActorToFactory(90000032, EnemyTamago01, "EnemyTamago01_33");
	orderActorToFactory(90000033, EnemyTamago01, "EnemyTamago01_34");
	orderActorToFactory(90000034, EnemyTamago01, "EnemyTamago01_35");
	orderActorToFactory(90000035, EnemyTamago01, "EnemyTamago01_36");
	orderActorToFactory(90000036, EnemyTamago01, "EnemyTamago01_37");
	orderActorToFactory(90000037, EnemyTamago01, "EnemyTamago01_38");
	orderActorToFactory(90000038, EnemyTamago01, "EnemyTamago01_39");
	orderActorToFactory(90000039, EnemyTamago01, "EnemyTamago01_40");
	orderActorToFactory(90000040, EnemyTamago01, "EnemyTamago01_41");
	orderActorToFactory(90000041, EnemyTamago01, "EnemyTamago01_42");
	orderActorToFactory(90000042, EnemyTamago01, "EnemyTamago01_43");
	orderActorToFactory(90000043, EnemyTamago01, "EnemyTamago01_44");
	orderActorToFactory(90000044, EnemyTamago01, "EnemyTamago01_45");
	orderActorToFactory(90000045, EnemyTamago01, "EnemyTamago01_46");
	orderActorToFactory(90000046, EnemyTamago01, "EnemyTamago01_47");
	orderActorToFactory(90000047, EnemyTamago01, "EnemyTamago01_48");
	orderActorToFactory(90000048, EnemyTamago01, "EnemyTamago01_49");
	orderActorToFactory(90000049, EnemyTamago01, "EnemyTamago01_50");
	orderActorToFactory(90000050, EnemyTamago01, "EnemyTamago01_51");
	orderActorToFactory(90000051, EnemyTamago01, "EnemyTamago01_52");
	orderActorToFactory(90000052, EnemyTamago01, "EnemyTamago01_53");
	orderActorToFactory(90000053, EnemyTamago01, "EnemyTamago01_54");
	orderActorToFactory(90000054, EnemyTamago01, "EnemyTamago01_55");
	orderActorToFactory(90000055, EnemyTamago01, "EnemyTamago01_56");
	orderActorToFactory(90000056, EnemyTamago01, "EnemyTamago01_57");
	orderActorToFactory(90000057, EnemyTamago01, "EnemyTamago01_58");
	orderActorToFactory(90000058, EnemyTamago01, "EnemyTamago01_59");
	orderActorToFactory(90000059, EnemyTamago01, "EnemyTamago01_60");
	orderActorToFactory(90000060, EnemyTamago01, "EnemyTamago01_61");
	orderActorToFactory(90000061, EnemyTamago01, "EnemyTamago01_62");
	orderActorToFactory(90000062, EnemyTamago01, "EnemyTamago01_63");
	orderActorToFactory(90000063, EnemyTamago01, "EnemyTamago01_64");
	orderActorToFactory(90000064, EnemyTamago01, "EnemyTamago01_65");
	orderActorToFactory(90000065, EnemyTamago01, "EnemyTamago01_66");
	orderActorToFactory(90000066, EnemyTamago01, "EnemyTamago01_67");
	orderActorToFactory(90000067, EnemyTamago01, "EnemyTamago01_68");
	orderActorToFactory(90000068, EnemyTamago01, "EnemyTamago01_69");
	orderActorToFactory(90000069, EnemyTamago01, "EnemyTamago01_70");
	orderActorToFactory(90000070, EnemyTamago01, "EnemyTamago01_71");
	orderActorToFactory(90000071, EnemyTamago01, "EnemyTamago01_72");
	orderActorToFactory(90000072, EnemyTamago01, "EnemyTamago01_73");
	orderActorToFactory(90000073, EnemyTamago01, "EnemyTamago01_74");
	orderActorToFactory(90000074, EnemyTamago01, "EnemyTamago01_75");
	orderActorToFactory(90000075, EnemyTamago01, "EnemyTamago01_76");
	orderActorToFactory(90000076, EnemyTamago01, "EnemyTamago01_77");
	orderActorToFactory(90000077, EnemyTamago01, "EnemyTamago01_78");
	orderActorToFactory(90000078, EnemyTamago01, "EnemyTamago01_79");
	orderActorToFactory(90000079, EnemyTamago01, "EnemyTamago01_80");
	orderActorToFactory(90000080, EnemyTamago01, "EnemyTamago01_81");
	orderActorToFactory(90000081, EnemyTamago01, "EnemyTamago01_82");
	orderActorToFactory(90000082, EnemyTamago01, "EnemyTamago01_83");
	orderActorToFactory(90000083, EnemyTamago01, "EnemyTamago01_84");
	orderActorToFactory(90000084, EnemyTamago01, "EnemyTamago01_85");
	orderActorToFactory(90000085, EnemyTamago01, "EnemyTamago01_86");
	orderActorToFactory(90000086, EnemyTamago01, "EnemyTamago01_87");
	orderActorToFactory(90000087, EnemyTamago01, "EnemyTamago01_88");
	orderActorToFactory(90000088, EnemyTamago01, "EnemyTamago01_89");
	orderActorToFactory(90000089, EnemyTamago01, "EnemyTamago01_90");
	orderActorToFactory(90000090, EnemyTamago01, "EnemyTamago01_91");
	orderActorToFactory(90000091, EnemyTamago01, "EnemyTamago01_92");
	orderActorToFactory(90000092, EnemyTamago01, "EnemyTamago01_93");
	orderActorToFactory(90000093, EnemyTamago01, "EnemyTamago01_94");
	orderActorToFactory(90000094, EnemyTamago01, "EnemyTamago01_95");
	orderActorToFactory(90000095, EnemyTamago01, "EnemyTamago01_96");
	orderActorToFactory(90000096, EnemyTamago01, "EnemyTamago01_97");
	orderActorToFactory(90000097, EnemyTamago01, "EnemyTamago01_98");
	orderActorToFactory(90000098, EnemyTamago01, "EnemyTamago01_99");
	orderActorToFactory(90000099, EnemyTamago01, "EnemyTamago01_100");
	orderActorToFactory(90000100, EnemyTamago01, "EnemyTamago01_101");
	orderActorToFactory(90000101, EnemyTamago01, "EnemyTamago01_102");
	orderActorToFactory(90000102, EnemyTamago01, "EnemyTamago01_103");
	orderActorToFactory(90000103, EnemyTamago01, "EnemyTamago01_104");
	orderActorToFactory(90000104, EnemyTamago01, "EnemyTamago01_105");
	orderActorToFactory(90000105, EnemyTamago01, "EnemyTamago01_106");
	orderActorToFactory(90000106, EnemyTamago01, "EnemyTamago01_107");
	orderActorToFactory(90000107, EnemyTamago01, "EnemyTamago01_108");
	orderActorToFactory(90000108, EnemyTamago01, "EnemyTamago01_109");
	orderActorToFactory(90000109, EnemyTamago01, "EnemyTamago01_110");
	orderActorToFactory(90000110, EnemyTamago01, "EnemyTamago01_111");
	orderActorToFactory(90000111, EnemyTamago01, "EnemyTamago01_112");
	orderActorToFactory(90000112, EnemyTamago01, "EnemyTamago01_113");
	orderActorToFactory(90000113, EnemyTamago01, "EnemyTamago01_114");
	orderActorToFactory(90000114, EnemyTamago01, "EnemyTamago01_115");
	orderActorToFactory(90000115, EnemyTamago01, "EnemyTamago01_116");
	orderActorToFactory(90000116, EnemyTamago01, "EnemyTamago01_117");
	orderActorToFactory(90000117, EnemyTamago01, "EnemyTamago01_118");
	orderActorToFactory(90000118, EnemyTamago01, "EnemyTamago01_119");
	orderActorToFactory(90000119, EnemyTamago01, "EnemyTamago01_120");
	orderActorToFactory(90000120, EnemyTamago01, "EnemyTamago01_121");
	orderActorToFactory(90000121, EnemyTamago01, "EnemyTamago01_122");
	orderActorToFactory(90000122, EnemyTamago01, "EnemyTamago01_123");
	orderActorToFactory(90000123, EnemyTamago01, "EnemyTamago01_124");
	orderActorToFactory(90000124, EnemyTamago01, "EnemyTamago01_125");
	orderActorToFactory(90000125, EnemyTamago01, "EnemyTamago01_126");
	orderActorToFactory(90000126, EnemyTamago01, "EnemyTamago01_127");
	orderActorToFactory(90000127, EnemyTamago01, "EnemyTamago01_128");
	orderActorToFactory(90000128, EnemyTamago01, "EnemyTamago01_129");
	orderActorToFactory(90000129, EnemyTamago01, "EnemyTamago01_130");
	orderActorToFactory(90000130, EnemyTamago01, "EnemyTamago01_131");
	orderActorToFactory(90000131, EnemyTamago01, "EnemyTamago01_132");
	orderActorToFactory(90000132, EnemyTamago01, "EnemyTamago01_133");
	orderActorToFactory(90000133, EnemyTamago01, "EnemyTamago01_134");
	orderActorToFactory(90000134, EnemyTamago01, "EnemyTamago01_135");
	orderActorToFactory(90000135, EnemyTamago01, "EnemyTamago01_136");
	orderActorToFactory(90000136, EnemyTamago01, "EnemyTamago01_137");
	orderActorToFactory(90000137, EnemyTamago01, "EnemyTamago01_138");
	orderActorToFactory(90000138, EnemyTamago01, "EnemyTamago01_139");
	orderActorToFactory(90000139, EnemyTamago01, "EnemyTamago01_140");
	orderActorToFactory(90000140, EnemyTamago01, "EnemyTamago01_141");
	orderActorToFactory(90000141, EnemyTamago01, "EnemyTamago01_142");
	orderActorToFactory(90000142, EnemyTamago01, "EnemyTamago01_143");
	orderActorToFactory(90000143, EnemyTamago01, "EnemyTamago01_144");
	orderActorToFactory(90000144, EnemyTamago01, "EnemyTamago01_145");
	orderActorToFactory(90000145, EnemyTamago01, "EnemyTamago01_146");
	orderActorToFactory(90000146, EnemyTamago01, "EnemyTamago01_147");
	orderActorToFactory(90000147, EnemyTamago01, "EnemyTamago01_148");
	orderActorToFactory(90000148, EnemyTamago01, "EnemyTamago01_149");
	orderActorToFactory(90000149, EnemyTamago01, "EnemyTamago01_150");
	orderActorToFactory(90000150, EnemyTamago01, "EnemyTamago01_151");
	orderActorToFactory(90000151, EnemyTamago01, "EnemyTamago01_152");
	orderActorToFactory(90000152, EnemyTamago01, "EnemyTamago01_153");
	orderActorToFactory(90000153, EnemyTamago01, "EnemyTamago01_154");
	orderActorToFactory(90000154, EnemyTamago01, "EnemyTamago01_155");
	orderActorToFactory(90000155, EnemyTamago01, "EnemyTamago01_156");
	orderActorToFactory(90000156, EnemyTamago01, "EnemyTamago01_157");
	orderActorToFactory(90000157, EnemyTamago01, "EnemyTamago01_158");
	orderActorToFactory(90000158, EnemyTamago01, "EnemyTamago01_159");
	orderActorToFactory(90000159, EnemyTamago01, "EnemyTamago01_160");
	orderActorToFactory(90000160, EnemyTamago01, "EnemyTamago01_161");
    // gen01 end
}

void RankUp002::initialize() {
    RankUpScene::initialize();
}

void RankUp002::processBehavior() {
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
				orderActorToFactory(90000161, EnemyTamago01, "EnemyTamago01_162");
				break;
			}
			case 20: {
				orderActorToFactory(90000162, EnemyTamago01, "EnemyTamago01_163");
				break;
			}
			case 30: {
				orderActorToFactory(90000163, EnemyTamago01, "EnemyTamago01_164");
				break;
			}
			case 40: {
				orderActorToFactory(90000164, EnemyTamago01, "EnemyTamago01_165");
				break;
			}
			case 50: {
				orderActorToFactory(90000165, EnemyTamago01, "EnemyTamago01_166");
				break;
			}
			case 60: {
				orderActorToFactory(90000166, EnemyTamago01, "EnemyTamago01_167");
				break;
			}
			case 70: {
				orderActorToFactory(90000167, EnemyTamago01, "EnemyTamago01_168");
				break;
			}
			case 80: {
				orderActorToFactory(90000168, EnemyTamago01, "EnemyTamago01_169");
				break;
			}
			case 90: {
				orderActorToFactory(90000169, EnemyTamago01, "EnemyTamago01_170");
				break;
			}
			case 100: {
				orderActorToFactory(90000170, EnemyTamago01, "EnemyTamago01_171");
				break;
			}
			case 110: {
				orderActorToFactory(90000171, EnemyTamago01, "EnemyTamago01_172");
				break;
			}
			case 120: {
				orderActorToFactory(90000172, EnemyTamago01, "EnemyTamago01_173");
				break;
			}
			case 130: {
				orderActorToFactory(90000173, EnemyTamago01, "EnemyTamago01_174");
				break;
			}
			case 140: {
				orderActorToFactory(90000174, EnemyTamago01, "EnemyTamago01_175");
				break;
			}
			case 150: {
				orderActorToFactory(90000175, EnemyTamago01, "EnemyTamago01_176");
				break;
			}
			case 160: {
				orderActorToFactory(90000176, EnemyTamago01, "EnemyTamago01_177");
				break;
			}
			case 170: {
				orderActorToFactory(90000177, EnemyTamago01, "EnemyTamago01_178");
				break;
			}
			case 180: {
				orderActorToFactory(90000178, EnemyTamago01, "EnemyTamago01_179");
				break;
			}
			case 190: {
				orderActorToFactory(90000179, EnemyTamago01, "EnemyTamago01_180");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000000);
				getDirector()->addSubGroup(pActor);
				orderActorToFactory(90000180, EnemyTamago01, "EnemyTamago01_181");
				break;
			}
			case 210: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000001);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000002);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 230: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000003);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 240: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000004);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 250: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000005);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000006);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 270: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000007);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000008);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 290: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000009);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 300: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000010);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 310: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000011);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000012);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 330: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000013);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000014);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 350: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000015);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 360: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000016);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 370: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000017);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000018);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 390: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000019);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000020);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 410: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000021);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 420: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000022);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 430: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000023);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000024);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 450: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000025);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000026);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 470: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000027);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 480: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000028);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 490: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000029);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000030);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 510: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000031);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000032);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 530: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000033);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 540: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000034);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 550: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000035);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000036);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 570: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000037);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000038);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 590: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000039);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 600: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000040);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 610: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000041);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000042);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 630: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000043);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000044);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 650: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000045);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 660: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000046);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 670: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000047);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000048);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 690: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000049);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000050);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 710: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000051);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 720: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000052);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 730: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000053);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000054);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 750: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000055);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000056);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 770: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000057);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 780: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000058);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 790: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000059);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000060);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 810: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000061);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000062);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 830: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000063);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 840: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000064);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 850: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000065);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000066);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 870: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000067);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000068);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 890: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000069);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 900: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000070);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 910: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000071);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000072);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 930: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000073);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000074);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 950: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000075);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 960: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000076);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 970: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000077);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000078);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 990: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000079);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000080);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1010: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000081);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1020: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000082);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1030: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000083);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000084);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1050: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000085);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1060: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000086);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1070: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000087);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1080: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000088);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1090: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000089);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000090);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1110: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000091);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1120: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000092);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1130: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000093);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1140: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000094);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1150: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000095);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000096);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1170: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000097);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1180: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000098);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1190: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000099);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000100);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1210: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000101);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000102);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1230: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000103);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1240: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000104);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1250: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000105);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000106);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1270: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000107);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000108);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1290: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000109);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1300: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000110);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1310: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000111);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000112);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1330: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000113);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000114);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1350: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000115);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1360: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000116);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1370: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000117);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000118);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1390: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000119);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000120);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1410: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000121);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1420: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000122);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1430: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000123);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000124);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1450: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000125);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000126);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1470: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000127);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1480: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000128);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1490: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000129);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000130);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1510: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000131);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000132);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1530: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000133);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1540: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000134);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1550: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000135);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000136);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1570: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000137);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000138);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1590: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000139);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1600: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000140);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1610: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000141);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000142);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1630: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000143);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000144);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1650: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000145);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1660: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000146);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1670: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000147);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000148);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1690: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000149);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000150);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1710: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000151);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1720: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000152);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1730: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000153);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000154);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1750: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000155);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000156);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1770: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000157);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1780: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000158);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1790: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000159);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000160);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1810: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000161);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000162);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1830: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000163);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1840: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000164);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1850: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000165);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000166);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1870: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000167);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000168);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1890: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000169);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1900: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000170);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1910: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000171);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000172);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1930: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000173);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000174);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1950: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000175);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1960: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000176);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1970: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000177);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000178);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1990: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000179);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000180);
				getDirector()->addSubGroup(pActor);
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
                _TRACE_("RankUp002::processBehavior() RANKUPSCENE_PROG_PLAYING になりますた！");
            }

            if (_pProg->getFrameInProgress() == 2500) {
                _TRACE_("RankUp002::processBehavior() RANKUPSCENE_PROG_PLAYING おわった");
                _pProg->change(RANKUPSCENE_PROG_RESULT); //RankUpSceneの共通処理へ
            }
            break;
        }
    }

}

void RankUp002::processJudgement() {
}


void RankUp002::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}


RankUp002::~RankUp002() {

}
