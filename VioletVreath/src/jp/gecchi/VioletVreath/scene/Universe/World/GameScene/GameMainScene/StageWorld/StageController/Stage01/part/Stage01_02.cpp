#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,40,100,160,220,280,340,400,460,520,580,640,700,760,820,880,940,1000,1060,1100,1120,1180,1240,1300,1360,1400,1420,1480,1540,1600,1660,1720,1780,1800,1840,1900,1960,2000,2020,2080,2100,2140,2200,2260,2300,2320,2380,2440,2500,2560,2620,2680,2700,2740,2800,2860,2920,2980,3000,3040,3100,3160,3220,3280,3340,3400,3460,3520,3580,3640,3700,3760,3820,3880,3940,4000,4060,4100,4120,4180,4240,4300,4360,4400,4420,4480,4540,4600,4660,4700,4720,4780,4840,4900,4960,5000,5100,5300,5600,5900,6000,6100,6200,6500,6800,7000,7100,7400,7700,8000,8100,8300,8600,8900,9000,9200,9500,9800};
	_paFrame_NextEvent = new frame[118];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 118;
	orderActorToFactory(40000000, EnemyMetis, "EnemyMetis-1");
	orderActorToFactory(40000001, EnemyMetis, "EnemyMetis-2");
	orderActorToFactory(40000002, EnemyMetis, "EnemyMetis-3");
	orderActorToFactory(40000003, EnemyMetis, "EnemyMetis-4");
	orderActorToFactory(40000004, EnemyMetis, "EnemyMetis-5");
	orderActorToFactory(40000005, EnemyMetis, "EnemyMetis-6");
	orderActorToFactory(40000006, EnemyMetis, "EnemyMetis-7");
	orderActorToFactory(40000007, EnemyMetis, "EnemyMetis-8");
	orderActorToFactory(40000008, EnemyMetis, "EnemyMetis-9");
	orderActorToFactory(40000009, EnemyMetis, "EnemyMetis-10");
	orderActorToFactory(40000010, EnemyMetis, "EnemyMetis-11");
	orderActorToFactory(40000011, EnemyMetis, "EnemyMetis-12");
	orderActorToFactory(40000012, EnemyMetis, "EnemyMetis-13");
	orderActorToFactory(40000013, EnemyMetis, "EnemyMetis-14");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActiveFrame()) {
			case 1: {
				break;
			}
			case 40: {
				orderActorToFactory(40000014, EnemyMetis, "EnemyMetis-15");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000000);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000015, EnemyMetis, "EnemyMetis-16");
				orderActorToFactory(40000082, VarietySylvia001, "VarietySylvia001-17");
				orderActorToFactory(40000104, FormationThalia, "FormationThalia-18");
				orderActorToFactory(40000120, FormationHebe001, "FormationHebe001-19");
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000001);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000016, EnemyMetis, "EnemyMetis-20");
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000002);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000017, EnemyMetis, "EnemyMetis-21");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000003);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000018, EnemyMetis, "EnemyMetis-22");
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000004);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000019, EnemyMetis, "EnemyMetis-23");
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000005);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000020, EnemyMetis, "EnemyMetis-24");
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000006);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000021, EnemyMetis, "EnemyMetis-25");
				break;
			}
			case 520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000007);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000022, EnemyMetis, "EnemyMetis-26");
				break;
			}
			case 580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000008);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000023, EnemyMetis, "EnemyMetis-27");
				break;
			}
			case 640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000009);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000024, EnemyMetis, "EnemyMetis-28");
				break;
			}
			case 700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000010);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000025, EnemyMetis, "EnemyMetis-29");
				break;
			}
			case 760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000011);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000026, EnemyMetis, "EnemyMetis-30");
				break;
			}
			case 820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000012);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000027, EnemyMetis, "EnemyMetis-31");
				break;
			}
			case 880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000013);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000028, EnemyMetis, "EnemyMetis-32");
				break;
			}
			case 940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000014);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000029, EnemyMetis, "EnemyMetis-33");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000015);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000030, EnemyMetis, "EnemyMetis-34");
				VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(40000082);
				getSceneDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000104);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF35 = (FormationHebe001*)obtainActorFromFactory(40000120);
				getSceneDirector()->addSubGroup(pF35);
				break;
			}
			case 1060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000016);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000031, EnemyMetis, "EnemyMetis-36");
				break;
			}
			case 1100: {
				orderActorToFactory(40000105, FormationThalia, "FormationThalia-37");
				orderActorToFactory(40000121, FormationHebe001, "FormationHebe001-38");
				break;
			}
			case 1120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000017);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000032, EnemyMetis, "EnemyMetis-39");
				break;
			}
			case 1180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000018);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000033, EnemyMetis, "EnemyMetis-40");
				break;
			}
			case 1240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000019);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000034, EnemyMetis, "EnemyMetis-41");
				break;
			}
			case 1300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000020);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000035, EnemyMetis, "EnemyMetis-42");
				break;
			}
			case 1360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000021);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000036, EnemyMetis, "EnemyMetis-43");
				break;
			}
			case 1400: {
				orderActorToFactory(40000083, EnemyAstraea, "EnemyAstraea-44");
				break;
			}
			case 1420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000022);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000037, EnemyMetis, "EnemyMetis-45");
				break;
			}
			case 1480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000023);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000038, EnemyMetis, "EnemyMetis-46");
				break;
			}
			case 1540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000024);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000039, EnemyMetis, "EnemyMetis-47");
				break;
			}
			case 1600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000025);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000040, EnemyMetis, "EnemyMetis-48");
				orderActorToFactory(40000084, FormationMassalia, "FormationMassalia-49");
				break;
			}
			case 1660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000026);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000041, EnemyMetis, "EnemyMetis-50");
				break;
			}
			case 1720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000027);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000042, EnemyMetis, "EnemyMetis-51");
				break;
			}
			case 1780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000028);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000043, EnemyMetis, "EnemyMetis-52");
				break;
			}
			case 1800: {
				orderActorToFactory(40000086, FormationPallas001a, "FormationPallas001a-53");
				orderActorToFactory(40000087, FormationPallas001b, "FormationPallas001b-54");
				orderActorToFactory(40000088, FormationPallas001c, "FormationPallas001c-55");
				orderActorToFactory(40000089, FormationPallas001d, "FormationPallas001d-56");
				orderActorToFactory(40000090, FormationPallas001a, "FormationPallas001a-57");
				orderActorToFactory(40000091, FormationPallas001d, "FormationPallas001d-58");
				orderActorToFactory(40000092, FormationPallas001b, "FormationPallas001b-59");
				orderActorToFactory(40000093, FormationPallas001c, "FormationPallas001c-60");
				orderActorToFactory(40000094, FormationPallas001a, "FormationPallas001a-61");
				orderActorToFactory(40000095, FormationPallas001d, "FormationPallas001d-62");
				orderActorToFactory(40000096, FormationPallas001b, "FormationPallas001b-63");
				orderActorToFactory(40000097, FormationPallas001c, "FormationPallas001c-64");
				break;
			}
			case 1840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000029);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000044, EnemyMetis, "EnemyMetis-65");
				break;
			}
			case 1900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000030);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000045, EnemyMetis, "EnemyMetis-66");
				break;
			}
			case 1960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000031);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000046, EnemyMetis, "EnemyMetis-67");
				break;
			}
			case 2000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000105);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF68 = (FormationHebe001*)obtainActorFromFactory(40000121);
				getSceneDirector()->addSubGroup(pF68);
				break;
			}
			case 2020: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000032);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000047, EnemyMetis, "EnemyMetis-69");
				break;
			}
			case 2080: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000033);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000048, EnemyMetis, "EnemyMetis-70");
				break;
			}
			case 2100: {
				orderActorToFactory(40000098, FormationJuno001, "FormationJuno001-71");
				orderActorToFactory(40000106, FormationThalia, "FormationThalia-72");
				orderActorToFactory(40000122, FormationHebe001, "FormationHebe001-73");
				break;
			}
			case 2140: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000034);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000049, EnemyMetis, "EnemyMetis-74");
				break;
			}
			case 2200: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000035);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000050, EnemyMetis, "EnemyMetis-75");
				break;
			}
			case 2260: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000036);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000051, EnemyMetis, "EnemyMetis-76");
				break;
			}
			case 2300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000083);
				getSceneDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2320: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000037);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000052, EnemyMetis, "EnemyMetis-77");
				break;
			}
			case 2380: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000038);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000053, EnemyMetis, "EnemyMetis-78");
				break;
			}
			case 2440: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000039);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000054, EnemyMetis, "EnemyMetis-79");
				break;
			}
			case 2500: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000040);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000055, EnemyMetis, "EnemyMetis-80");
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(40000084);
				getSceneDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 2560: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000041);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000056, EnemyMetis, "EnemyMetis-81");
				break;
			}
			case 2620: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000042);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000057, EnemyMetis, "EnemyMetis-82");
				break;
			}
			case 2680: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000043);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000058, EnemyMetis, "EnemyMetis-83");
				break;
			}
			case 2700: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-84");
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
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000059, EnemyMetis, "EnemyMetis-85");
				break;
			}
			case 2800: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000045);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000060, EnemyMetis, "EnemyMetis-86");
				break;
			}
			case 2860: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000046);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000061, EnemyMetis, "EnemyMetis-87");
				break;
			}
			case 2920: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000047);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000062, EnemyMetis, "EnemyMetis-88");
				break;
			}
			case 2980: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000048);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000063, EnemyMetis, "EnemyMetis-89");
				break;
			}
			case 3000: {
				FormationJuno001* pF90 = (FormationJuno001*)obtainActorFromFactory(40000098);
				getSceneDirector()->addSubGroup(pF90);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000106);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF91 = (FormationHebe001*)obtainActorFromFactory(40000122);
				getSceneDirector()->addSubGroup(pF91);
				break;
			}
			case 3040: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000049);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000064, EnemyMetis, "EnemyMetis-92");
				break;
			}
			case 3100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000050);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000065, EnemyMetis, "EnemyMetis-93");
				orderActorToFactory(40000099, VarietySylvia001, "VarietySylvia001-94");
				orderActorToFactory(40000107, FormationThalia, "FormationThalia-95");
				orderActorToFactory(40000123, FormationHebe001, "FormationHebe001-96");
				break;
			}
			case 3160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000051);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000066, EnemyMetis, "EnemyMetis-97");
				break;
			}
			case 3220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000052);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000067, EnemyMetis, "EnemyMetis-98");
				break;
			}
			case 3280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000053);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000068, EnemyMetis, "EnemyMetis-99");
				break;
			}
			case 3340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000054);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000069, EnemyMetis, "EnemyMetis-100");
				break;
			}
			case 3400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000055);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000070, EnemyMetis, "EnemyMetis-101");
				break;
			}
			case 3460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000056);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000071, EnemyMetis, "EnemyMetis-102");
				break;
			}
			case 3520: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000057);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000072, EnemyMetis, "EnemyMetis-103");
				break;
			}
			case 3580: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000058);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000073, EnemyMetis, "EnemyMetis-104");
				break;
			}
			case 3640: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000059);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000074, EnemyMetis, "EnemyMetis-105");
				break;
			}
			case 3700: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000060);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000075, EnemyMetis, "EnemyMetis-106");
				break;
			}
			case 3760: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000061);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000076, EnemyMetis, "EnemyMetis-107");
				break;
			}
			case 3820: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000062);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000077, EnemyMetis, "EnemyMetis-108");
				break;
			}
			case 3880: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000063);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000078, EnemyMetis, "EnemyMetis-109");
				break;
			}
			case 3940: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000064);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000079, EnemyMetis, "EnemyMetis-110");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000065);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000080, EnemyMetis, "EnemyMetis-111");
				VarietySylvia001* pSylvia = (VarietySylvia001*)obtainActorFromFactory(40000099);
				getSceneDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000107);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF112 = (FormationHebe001*)obtainActorFromFactory(40000123);
				getSceneDirector()->addSubGroup(pF112);
				break;
			}
			case 4060: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000066);
				getSceneDirector()->addSubGroup(pMetis);
				orderActorToFactory(40000081, EnemyMetis, "EnemyMetis-113");
				break;
			}
			case 4100: {
				orderActorToFactory(40000100, VarietySylvia002, "VarietySylvia002-114");
				orderActorToFactory(40000108, FormationThalia, "FormationThalia-115");
				orderActorToFactory(40000124, FormationHebe001, "FormationHebe001-116");
				orderActorToFactory(40000126, EnemyHesperia, "EnemyHesperia-117");
				break;
			}
			case 4120: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000067);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4180: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000068);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4240: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000069);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4300: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000070);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4360: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000071);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4400: {
				orderActorToFactory(40000127, EnemyHesperia, "EnemyHesperia-118");
				break;
			}
			case 4420: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000072);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4480: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000073);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4540: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000074);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4600: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000075);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4660: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000076);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4700: {
				orderActorToFactory(40000128, EnemyHesperia, "EnemyHesperia-119");
				break;
			}
			case 4720: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000077);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4780: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000078);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4840: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000079);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4900: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000080);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 4960: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000081);
				getSceneDirector()->addSubGroup(pMetis);
				break;
			}
			case 5000: {
				VarietySylvia002* pSylviaA = (VarietySylvia002*)obtainActorFromFactory(40000100);
				getSceneDirector()->addSubGroup(pSylviaA);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000108);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF120 = (FormationHebe001*)obtainActorFromFactory(40000124);
				getSceneDirector()->addSubGroup(pF120);
				EnemyHesperia* p121 = (EnemyHesperia*)obtainActorFromFactory(40000126);
				getSceneDirector()->addSubGroup(p121);
				orderActorToFactory(40000129, EnemyHesperia, "EnemyHesperia-122");
				break;
			}
			case 5100: {
				orderActorToFactory(40000101, VarietySylvia003, "VarietySylvia003-123");
				orderActorToFactory(40000109, FormationThalia, "FormationThalia-124");
				orderActorToFactory(40000125, FormationHebe001, "FormationHebe001-125");
				break;
			}
			case 5300: {
				EnemyHesperia* p126 = (EnemyHesperia*)obtainActorFromFactory(40000127);
				getSceneDirector()->addSubGroup(p126);
				orderActorToFactory(40000130, EnemyHesperia, "EnemyHesperia-127");
				break;
			}
			case 5600: {
				EnemyHesperia* p128 = (EnemyHesperia*)obtainActorFromFactory(40000128);
				getSceneDirector()->addSubGroup(p128);
				orderActorToFactory(40000131, EnemyHesperia, "EnemyHesperia-129");
				break;
			}
			case 5900: {
				EnemyHesperia* p130 = (EnemyHesperia*)obtainActorFromFactory(40000129);
				getSceneDirector()->addSubGroup(p130);
				orderActorToFactory(40000132, EnemyHesperia, "EnemyHesperia-131");
				break;
			}
			case 6000: {
				VarietySylvia003* pSylviaB = (VarietySylvia003*)obtainActorFromFactory(40000101);
				getSceneDirector()->addSubGroup(pSylviaB);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000109);
				getSceneDirector()->addSubGroup(pF);
				FormationHebe001* pF132 = (FormationHebe001*)obtainActorFromFactory(40000125);
				getSceneDirector()->addSubGroup(pF132);
				break;
			}
			case 6100: {
				orderActorToFactory(40000102, VarietySylvia004, "VarietySylvia004-133");
				orderActorToFactory(40000110, FormationThalia, "FormationThalia-134");
				break;
			}
			case 6200: {
				EnemyHesperia* p135 = (EnemyHesperia*)obtainActorFromFactory(40000130);
				getSceneDirector()->addSubGroup(p135);
				orderActorToFactory(40000133, EnemyHesperia, "EnemyHesperia-136");
				break;
			}
			case 6500: {
				EnemyHesperia* p137 = (EnemyHesperia*)obtainActorFromFactory(40000131);
				getSceneDirector()->addSubGroup(p137);
				orderActorToFactory(40000134, EnemyHesperia, "EnemyHesperia-138");
				break;
			}
			case 6800: {
				EnemyHesperia* p139 = (EnemyHesperia*)obtainActorFromFactory(40000132);
				getSceneDirector()->addSubGroup(p139);
				orderActorToFactory(40000135, EnemyHesperia, "EnemyHesperia-140");
				break;
			}
			case 7000: {
				VarietySylvia004* pSylvia = (VarietySylvia004*)obtainActorFromFactory(40000102);
				getSceneDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000110);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 7100: {
				orderActorToFactory(40000103, VarietySylvia004, "VarietySylvia004-141");
				orderActorToFactory(40000111, FormationThalia, "FormationThalia-142");
				EnemyHesperia* p143 = (EnemyHesperia*)obtainActorFromFactory(40000133);
				getSceneDirector()->addSubGroup(p143);
				orderActorToFactory(40000136, EnemyHesperia, "EnemyHesperia-144");
				break;
			}
			case 7400: {
				EnemyHesperia* p145 = (EnemyHesperia*)obtainActorFromFactory(40000134);
				getSceneDirector()->addSubGroup(p145);
				orderActorToFactory(40000137, EnemyHesperia, "EnemyHesperia-146");
				break;
			}
			case 7700: {
				EnemyHesperia* p147 = (EnemyHesperia*)obtainActorFromFactory(40000135);
				getSceneDirector()->addSubGroup(p147);
				orderActorToFactory(40000138, EnemyHesperia, "EnemyHesperia-148");
				break;
			}
			case 8000: {
				VarietySylvia004* pSylvia = (VarietySylvia004*)obtainActorFromFactory(40000103);
				getSceneDirector()->addSubGroup(pSylvia);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000111);
				getSceneDirector()->addSubGroup(pF);
				EnemyHesperia* p149 = (EnemyHesperia*)obtainActorFromFactory(40000136);
				getSceneDirector()->addSubGroup(p149);
				orderActorToFactory(40000139, EnemyHesperia, "EnemyHesperia-150");
				break;
			}
			case 8100: {
				orderActorToFactory(40000112, FormationThalia, "FormationThalia-151");
				break;
			}
			case 8300: {
				orderActorToFactory(40000114, FormationIris002, "FormationIris002-152");
				orderActorToFactory(40000115, FormationIris001, "FormationIris001-153");
				orderActorToFactory(40000116, FormationIris001, "FormationIris001-154");
				orderActorToFactory(40000117, FormationIris002, "FormationIris002-155");
				orderActorToFactory(40000118, FormationIris001, "FormationIris001-156");
				orderActorToFactory(40000119, FormationIris002, "FormationIris002-157");
				EnemyHesperia* p158 = (EnemyHesperia*)obtainActorFromFactory(40000137);
				getSceneDirector()->addSubGroup(p158);
				orderActorToFactory(40000140, EnemyHesperia, "EnemyHesperia-159");
				break;
			}
			case 8600: {
				EnemyHesperia* p160 = (EnemyHesperia*)obtainActorFromFactory(40000138);
				getSceneDirector()->addSubGroup(p160);
				orderActorToFactory(40000141, EnemyHesperia, "EnemyHesperia-161");
				break;
			}
			case 8900: {
				EnemyHesperia* p162 = (EnemyHesperia*)obtainActorFromFactory(40000139);
				getSceneDirector()->addSubGroup(p162);
				orderActorToFactory(40000142, EnemyHesperia, "EnemyHesperia-163");
				break;
			}
			case 9000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000112);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 9200: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-164");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000114)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000115)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000116)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000117)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000118)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000119)), 400);
				}
				EnemyHesperia* p165 = (EnemyHesperia*)obtainActorFromFactory(40000140);
				getSceneDirector()->addSubGroup(p165);
				break;
			}
			case 9500: {
				EnemyHesperia* p166 = (EnemyHesperia*)obtainActorFromFactory(40000141);
				getSceneDirector()->addSubGroup(p166);
				break;
			}
			case 9800: {
				EnemyHesperia* p167 = (EnemyHesperia*)obtainActorFromFactory(40000142);
				getSceneDirector()->addSubGroup(p167);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 118-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG01_02_WAS_BROKEN);
    }
}

Stage01_02::~Stage01_02() {

}
