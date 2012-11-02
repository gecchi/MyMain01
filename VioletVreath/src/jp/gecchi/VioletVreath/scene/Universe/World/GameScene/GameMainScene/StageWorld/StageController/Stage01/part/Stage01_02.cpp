#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,40,100,160,220,280,340,400,460,520,580,640,700,760,820,880,940,1000,1060,1100,1120,1180,1240,1300,1360,1400,1420,1480,1540,1600,1660,1720,1780,1800,1840,1900,1960,2000,2020,2080,2100,2140,2200,2260,2300,2320,2380,2440,2500,2560,2620,2680,2700,2740,2800,2860,2920,2980,3000,3040,3100,3160,3220,3280,3340,3400,3460,3520,3580,3640,3700,3760,3820,3880,3940,4000,4060,4100,4120,4180,4240,4300,4360,4400,4420,4480,4540,4600,4660,4700,4720,4780,4840,4900,4960,5000,5100,5300,5600,5900,6000,6100,6200,6500,6800,7000,7100,7400,7700,8000,8100,8300,8600,8900,9000,9200,9500,9800};
	_paFrame_NextEvent = new frame[118];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 118;
	orderActorToFactory(40000000, EnemyMetis, "Metis_1");
	orderActorToFactory(40000001, EnemyMetis, "Metis_2");
	orderActorToFactory(40000002, EnemyMetis, "Metis_3");
	orderActorToFactory(40000003, EnemyMetis, "Metis_4");
	orderActorToFactory(40000004, EnemyMetis, "Metis_5");
	orderActorToFactory(40000005, EnemyMetis, "Metis_6");
	orderActorToFactory(40000006, EnemyMetis, "Metis_7");
	orderActorToFactory(40000007, EnemyMetis, "Metis_8");
	orderActorToFactory(40000008, EnemyMetis, "Metis_9");
	orderActorToFactory(40000009, EnemyMetis, "Metis_10");
	orderActorToFactory(40000010, EnemyMetis, "Metis_11");
	orderActorToFactory(40000011, EnemyMetis, "Metis_12");
	orderActorToFactory(40000012, EnemyMetis, "Metis_13");
	orderActorToFactory(40000013, EnemyMetis, "Metis_14");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 40: {
				orderActorToFactory(40000014, EnemyMetis, "Metis_15");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000000);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000015, EnemyMetis, "Metis_16");
				orderActorToFactory(40000082, VarietySylvia001, "VarietySylvia001_17");
				orderActorToFactory(40000100, FormationThalia, "FormationThalia_18");
				orderActorToFactory(40000116, FormationHebe001, "F001a_Eunomia_19");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000001);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000016, EnemyMetis, "Metis_20");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000002);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000017, EnemyMetis, "Metis_21");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000003);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000018, EnemyMetis, "Metis_22");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000004);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000019, EnemyMetis, "Metis_23");
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000005);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000020, EnemyMetis, "Metis_24");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000006);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000021, EnemyMetis, "Metis_25");
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000007);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000022, EnemyMetis, "Metis_26");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000008);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000023, EnemyMetis, "Metis_27");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000009);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000024, EnemyMetis, "Metis_28");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000010);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000025, EnemyMetis, "Metis_29");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000011);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000026, EnemyMetis, "Metis_30");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000012);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000027, EnemyMetis, "Metis_31");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000013);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000028, EnemyMetis, "Metis_32");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000014);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000029, EnemyMetis, "Metis_33");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000015);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000030, EnemyMetis, "Metis_34");
				VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(40000082);
				getDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000100);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF35 = (FormationHebe001*)obtainActorFromFactory(40000116);
				getDirector()->addSubGroup(pF35);
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000016);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000031, EnemyMetis, "Metis_36");
				break;
			}
			case 1100: {
				orderActorToFactory(40000101, FormationThalia, "FormationThalia_37");
				orderActorToFactory(40000117, FormationHebe001, "F001a_Eunomia_38");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000017);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000032, EnemyMetis, "Metis_39");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000018);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000033, EnemyMetis, "Metis_40");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000019);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000034, EnemyMetis, "Metis_41");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000020);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000035, EnemyMetis, "Metis_42");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000021);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000036, EnemyMetis, "Metis_43");
				break;
			}
			case 1400: {
				orderActorToFactory(40000083, EnemyAstraea, "Astraea_44");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000022);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000037, EnemyMetis, "Metis_45");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000023);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000038, EnemyMetis, "Metis_46");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000024);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000039, EnemyMetis, "Metis_47");
				break;
			}
			case 1600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000025);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000040, EnemyMetis, "Metis_48");
				orderActorToFactory(40000084, FormationMassalia, "FormationMassalia_49");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000026);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000041, EnemyMetis, "Metis_50");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000027);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000042, EnemyMetis, "Metis_51");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000028);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000043, EnemyMetis, "Metis_52");
				break;
			}
			case 1800: {
				orderActorToFactory(40000086, FormationPallas001a, "F001a_Pallas_53");
				orderActorToFactory(40000087, FormationPallas001b, "F001b_Pallas_54");
				orderActorToFactory(40000088, FormationPallas001c, "F001c_Pallas_55");
				orderActorToFactory(40000089, FormationPallas001d, "F001d_Pallas_56");
				orderActorToFactory(40000090, FormationPallas001a, "F001a_Pallas_57");
				orderActorToFactory(40000091, FormationPallas001d, "F001d_Pallas_58");
				orderActorToFactory(40000092, FormationPallas001b, "F001b_Pallas_59");
				orderActorToFactory(40000093, FormationPallas001c, "F001c_Pallas_60");
				orderActorToFactory(40000094, FormationPallas001a, "F001a_Pallas_61");
				orderActorToFactory(40000095, FormationPallas001d, "F001d_Pallas_62");
				orderActorToFactory(40000096, FormationPallas001b, "F001b_Pallas_63");
				orderActorToFactory(40000097, FormationPallas001c, "F001c_Pallas_64");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000029);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000044, EnemyMetis, "Metis_65");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000030);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000045, EnemyMetis, "Metis_66");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000031);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000046, EnemyMetis, "Metis_67");
				break;
			}
			case 2000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000101);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF68 = (FormationHebe001*)obtainActorFromFactory(40000117);
				getDirector()->addSubGroup(pF68);
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000032);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000047, EnemyMetis, "Metis_69");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000033);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000048, EnemyMetis, "Metis_70");
				break;
			}
			case 2100: {
				orderActorToFactory(40000098, FormationJuno001, "F002_Juno_71");
				orderActorToFactory(40000102, FormationThalia, "FormationThalia_72");
				orderActorToFactory(40000118, FormationHebe001, "F001a_Eunomia_73");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000034);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000049, EnemyMetis, "Metis_74");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000035);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000050, EnemyMetis, "Metis_75");
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000036);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000051, EnemyMetis, "Metis_76");
				break;
			}
			case 2300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000083);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000037);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000052, EnemyMetis, "Metis_77");
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000038);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000053, EnemyMetis, "Metis_78");
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000039);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000054, EnemyMetis, "Metis_79");
				break;
			}
			case 2500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000040);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000055, EnemyMetis, "Metis_80");
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(40000084);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000041);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000056, EnemyMetis, "Metis_81");
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000042);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000057, EnemyMetis, "Metis_82");
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000043);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000058, EnemyMetis, "Metis_83");
				break;
			}
			case 2700: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_40000085");
				ta->setMaxPerformFrame(2500);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000086)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000087)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000088)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000089)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000090)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000091)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000092)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000093)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000094)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000095)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000096)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000097)), 400);
				}
				break;
			}
			case 2740: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000044);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000059, EnemyMetis, "Metis_84");
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000045);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000060, EnemyMetis, "Metis_85");
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000046);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000061, EnemyMetis, "Metis_86");
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000047);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000062, EnemyMetis, "Metis_87");
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000048);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000063, EnemyMetis, "Metis_88");
				break;
			}
			case 3000: {
				FormationJuno001* pF89 = (FormationJuno001*)obtainActorFromFactory(40000098);
				getDirector()->addSubGroup(pF89);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000102);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF90 = (FormationHebe001*)obtainActorFromFactory(40000118);
				getDirector()->addSubGroup(pF90);
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000049);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000064, EnemyMetis, "Metis_91");
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000050);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000065, EnemyMetis, "Metis_92");
				orderActorToFactory(40000099, VarietySylvia001, "VarietySylvia001_93");
				orderActorToFactory(40000103, FormationThalia, "FormationThalia_94");
				orderActorToFactory(40000119, FormationHebe001, "F001a_Eunomia_95");
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000051);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000066, EnemyMetis, "Metis_96");
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000052);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000067, EnemyMetis, "Metis_97");
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000053);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000068, EnemyMetis, "Metis_98");
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000054);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000069, EnemyMetis, "Metis_99");
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000055);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000070, EnemyMetis, "Metis_100");
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000056);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000071, EnemyMetis, "Metis_101");
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000057);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000072, EnemyMetis, "Metis_102");
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000058);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000073, EnemyMetis, "Metis_103");
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000059);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000074, EnemyMetis, "Metis_104");
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000060);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000075, EnemyMetis, "Metis_105");
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000061);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000076, EnemyMetis, "Metis_106");
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000062);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000077, EnemyMetis, "Metis_107");
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000063);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000078, EnemyMetis, "Metis_108");
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000064);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000079, EnemyMetis, "Metis_109");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000065);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000080, EnemyMetis, "Metis_110");
				VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(40000099);
				getDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000103);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF111 = (FormationHebe001*)obtainActorFromFactory(40000119);
				getDirector()->addSubGroup(pF111);
				break;
			}
			case 4060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000066);
				getDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000081, EnemyMetis, "Metis_112");
				break;
			}
			case 4100: {
				orderActorToFactory(40000104, FormationThalia, "FormationThalia_113");
				orderActorToFactory(40000120, FormationHebe001, "F001a_Eunomia_114");
				orderActorToFactory(40000122, EnemyHesperia, "EnemyHesperia_115");
				break;
			}
			case 4120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000067);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000068);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000069);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000070);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000071);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4400: {
				orderActorToFactory(40000123, EnemyHesperia, "EnemyHesperia_116");
				break;
			}
			case 4420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000072);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000073);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000074);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000075);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000076);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4700: {
				orderActorToFactory(40000124, EnemyHesperia, "EnemyHesperia_117");
				break;
			}
			case 4720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000077);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000078);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000079);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000080);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 4960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000081);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 5000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000104);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF118 = (FormationHebe001*)obtainActorFromFactory(40000120);
				getDirector()->addSubGroup(pF118);
				EnemyHesperia* p119 = (EnemyHesperia*)obtainActorFromFactory(40000122);
				getDirector()->addSubGroup(p119);
				orderActorToFactory(40000125, EnemyHesperia, "EnemyHesperia_120");
				break;
			}
			case 5100: {
				orderActorToFactory(40000105, FormationThalia, "FormationThalia_121");
				orderActorToFactory(40000121, FormationHebe001, "F001a_Eunomia_122");
				break;
			}
			case 5300: {
				EnemyHesperia* p123 = (EnemyHesperia*)obtainActorFromFactory(40000123);
				getDirector()->addSubGroup(p123);
				orderActorToFactory(40000126, EnemyHesperia, "EnemyHesperia_124");
				break;
			}
			case 5600: {
				EnemyHesperia* p125 = (EnemyHesperia*)obtainActorFromFactory(40000124);
				getDirector()->addSubGroup(p125);
				orderActorToFactory(40000127, EnemyHesperia, "EnemyHesperia_126");
				break;
			}
			case 5900: {
				EnemyHesperia* p127 = (EnemyHesperia*)obtainActorFromFactory(40000125);
				getDirector()->addSubGroup(p127);
				orderActorToFactory(40000128, EnemyHesperia, "EnemyHesperia_128");
				break;
			}
			case 6000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000105);
				getDirector()->addSubGroup(pF);
				FormationHebe001* pF129 = (FormationHebe001*)obtainActorFromFactory(40000121);
				getDirector()->addSubGroup(pF129);
				break;
			}
			case 6100: {
				orderActorToFactory(40000106, FormationThalia, "FormationThalia_130");
				break;
			}
			case 6200: {
				EnemyHesperia* p131 = (EnemyHesperia*)obtainActorFromFactory(40000126);
				getDirector()->addSubGroup(p131);
				orderActorToFactory(40000129, EnemyHesperia, "EnemyHesperia_132");
				break;
			}
			case 6500: {
				EnemyHesperia* p133 = (EnemyHesperia*)obtainActorFromFactory(40000127);
				getDirector()->addSubGroup(p133);
				orderActorToFactory(40000130, EnemyHesperia, "EnemyHesperia_134");
				break;
			}
			case 6800: {
				EnemyHesperia* p135 = (EnemyHesperia*)obtainActorFromFactory(40000128);
				getDirector()->addSubGroup(p135);
				orderActorToFactory(40000131, EnemyHesperia, "EnemyHesperia_136");
				break;
			}
			case 7000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000106);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 7100: {
				orderActorToFactory(40000107, FormationThalia, "FormationThalia_137");
				EnemyHesperia* p138 = (EnemyHesperia*)obtainActorFromFactory(40000129);
				getDirector()->addSubGroup(p138);
				orderActorToFactory(40000132, EnemyHesperia, "EnemyHesperia_139");
				break;
			}
			case 7400: {
				EnemyHesperia* p140 = (EnemyHesperia*)obtainActorFromFactory(40000130);
				getDirector()->addSubGroup(p140);
				orderActorToFactory(40000133, EnemyHesperia, "EnemyHesperia_141");
				break;
			}
			case 7700: {
				EnemyHesperia* p142 = (EnemyHesperia*)obtainActorFromFactory(40000131);
				getDirector()->addSubGroup(p142);
				orderActorToFactory(40000134, EnemyHesperia, "EnemyHesperia_143");
				break;
			}
			case 8000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000107);
				getDirector()->addSubGroup(pF);
				EnemyHesperia* p144 = (EnemyHesperia*)obtainActorFromFactory(40000132);
				getDirector()->addSubGroup(p144);
				orderActorToFactory(40000135, EnemyHesperia, "EnemyHesperia_145");
				break;
			}
			case 8100: {
				orderActorToFactory(40000108, FormationThalia, "FormationThalia_146");
				break;
			}
			case 8300: {
				orderActorToFactory(40000110, FormationIris002, "F002_Iris_147");
				orderActorToFactory(40000111, FormationIris001, "F001_Iris_148");
				orderActorToFactory(40000112, FormationIris001, "F001_Iris_149");
				orderActorToFactory(40000113, FormationIris002, "F002_Iris_150");
				orderActorToFactory(40000114, FormationIris001, "F001_Iris_151");
				orderActorToFactory(40000115, FormationIris002, "F002_Iris_152");
				EnemyHesperia* p153 = (EnemyHesperia*)obtainActorFromFactory(40000133);
				getDirector()->addSubGroup(p153);
				orderActorToFactory(40000136, EnemyHesperia, "EnemyHesperia_154");
				break;
			}
			case 8600: {
				EnemyHesperia* p155 = (EnemyHesperia*)obtainActorFromFactory(40000134);
				getDirector()->addSubGroup(p155);
				orderActorToFactory(40000137, EnemyHesperia, "EnemyHesperia_156");
				break;
			}
			case 8900: {
				EnemyHesperia* p157 = (EnemyHesperia*)obtainActorFromFactory(40000135);
				getDirector()->addSubGroup(p157);
				orderActorToFactory(40000138, EnemyHesperia, "EnemyHesperia_158");
				break;
			}
			case 9000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000108);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 9200: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_40000109");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000110)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000111)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000112)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000113)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000114)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000115)), 400);
				}
				EnemyHesperia* p159 = (EnemyHesperia*)obtainActorFromFactory(40000136);
				getDirector()->addSubGroup(p159);
				break;
			}
			case 9500: {
				EnemyHesperia* p160 = (EnemyHesperia*)obtainActorFromFactory(40000137);
				getDirector()->addSubGroup(p160);
				break;
			}
			case 9800: {
				EnemyHesperia* p161 = (EnemyHesperia*)obtainActorFromFactory(40000138);
				getDirector()->addSubGroup(p161);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 118-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActivePartFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventToUpperTree(EVENT_STG01_02_WAS_BROKEN);
    }
}

Stage01_02::~Stage01_02() {

}
