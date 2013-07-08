#include "stdafx.h"
#include "Stage01_02.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"

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
	orderActorToFactory(40000000, EnemyEtis, "EnemyEtis-1");
	orderActorToFactory(40000001, EnemyEtis, "EnemyEtis-2");
	orderActorToFactory(40000002, EnemyEtis, "EnemyEtis-3");
	orderActorToFactory(40000003, EnemyEtis, "EnemyEtis-4");
	orderActorToFactory(40000004, EnemyEtis, "EnemyEtis-5");
	orderActorToFactory(40000005, EnemyEtis, "EnemyEtis-6");
	orderActorToFactory(40000006, EnemyEtis, "EnemyEtis-7");
	orderActorToFactory(40000007, EnemyEtis, "EnemyEtis-8");
	orderActorToFactory(40000008, EnemyEtis, "EnemyEtis-9");
	orderActorToFactory(40000009, EnemyEtis, "EnemyEtis-10");
	orderActorToFactory(40000010, EnemyEtis, "EnemyEtis-11");
	orderActorToFactory(40000011, EnemyEtis, "EnemyEtis-12");
	orderActorToFactory(40000012, EnemyEtis, "EnemyEtis-13");
	orderActorToFactory(40000013, EnemyEtis, "EnemyEtis-14");
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
				orderActorToFactory(40000014, EnemyEtis, "EnemyEtis-15");
				break;
			}
			case 100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000000);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000015, EnemyEtis, "EnemyEtis-16");
				orderActorToFactory(40000082, VarietyRatislavia001, "VarietyRatislavia001-17");
				orderActorToFactory(40000100, FormationHalia, "FormationHalia-18");
				orderActorToFactory(40000116, FormationEbe001, "FormationEbe001-19");
				break;
			}
			case 160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000001);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000016, EnemyEtis, "EnemyEtis-20");
				break;
			}
			case 220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000002);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000017, EnemyEtis, "EnemyEtis-21");
				break;
			}
			case 280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000003);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000018, EnemyEtis, "EnemyEtis-22");
				break;
			}
			case 340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000004);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000019, EnemyEtis, "EnemyEtis-23");
				break;
			}
			case 400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000005);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000020, EnemyEtis, "EnemyEtis-24");
				break;
			}
			case 460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000006);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000021, EnemyEtis, "EnemyEtis-25");
				break;
			}
			case 520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000007);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000022, EnemyEtis, "EnemyEtis-26");
				break;
			}
			case 580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000008);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000023, EnemyEtis, "EnemyEtis-27");
				break;
			}
			case 640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000009);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000024, EnemyEtis, "EnemyEtis-28");
				break;
			}
			case 700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000010);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000025, EnemyEtis, "EnemyEtis-29");
				break;
			}
			case 760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000011);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000026, EnemyEtis, "EnemyEtis-30");
				break;
			}
			case 820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000012);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000027, EnemyEtis, "EnemyEtis-31");
				break;
			}
			case 880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000013);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000028, EnemyEtis, "EnemyEtis-32");
				break;
			}
			case 940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000014);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000029, EnemyEtis, "EnemyEtis-33");
				break;
			}
			case 1000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000015);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000030, EnemyEtis, "EnemyEtis-34");
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(40000082);
				getSceneDirector()->addSubGroup(pRatislavia);
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000100);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF35 = (FormationEbe001*)obtainActorFromFactory(40000116);
				getSceneDirector()->addSubGroup(pF35);
				break;
			}
			case 1060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000016);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000031, EnemyEtis, "EnemyEtis-36");
				break;
			}
			case 1100: {
				orderActorToFactory(40000101, FormationHalia, "FormationHalia-37");
				orderActorToFactory(40000117, FormationEbe001, "FormationEbe001-38");
				break;
			}
			case 1120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000017);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000032, EnemyEtis, "EnemyEtis-39");
				break;
			}
			case 1180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000018);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000033, EnemyEtis, "EnemyEtis-40");
				break;
			}
			case 1240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000019);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000034, EnemyEtis, "EnemyEtis-41");
				break;
			}
			case 1300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000020);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000035, EnemyEtis, "EnemyEtis-42");
				break;
			}
			case 1360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000021);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000036, EnemyEtis, "EnemyEtis-43");
				break;
			}
			case 1400: {
				orderActorToFactory(40000083, EnemyStraea, "EnemyStraea-44");
				break;
			}
			case 1420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000022);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000037, EnemyEtis, "EnemyEtis-45");
				break;
			}
			case 1480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000023);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000038, EnemyEtis, "EnemyEtis-46");
				break;
			}
			case 1540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000024);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000039, EnemyEtis, "EnemyEtis-47");
				break;
			}
			case 1600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000025);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000040, EnemyEtis, "EnemyEtis-48");
				orderActorToFactory(40000084, FormationAssalia, "FormationAssalia-49");
				break;
			}
			case 1660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000026);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000041, EnemyEtis, "EnemyEtis-50");
				break;
			}
			case 1720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000027);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000042, EnemyEtis, "EnemyEtis-51");
				break;
			}
			case 1780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000028);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000043, EnemyEtis, "EnemyEtis-52");
				break;
			}
			case 1800: {
				orderActorToFactory(40000086, FormationAllas001a, "FormationAllas001a-53");
				orderActorToFactory(40000087, FormationAllas001b, "FormationAllas001b-54");
				orderActorToFactory(40000088, FormationAllas001c, "FormationAllas001c-55");
				orderActorToFactory(40000089, FormationAllas001d, "FormationAllas001d-56");
				orderActorToFactory(40000090, FormationAllas001a, "FormationAllas001a-57");
				orderActorToFactory(40000091, FormationAllas001d, "FormationAllas001d-58");
				orderActorToFactory(40000092, FormationAllas001b, "FormationAllas001b-59");
				orderActorToFactory(40000093, FormationAllas001c, "FormationAllas001c-60");
				orderActorToFactory(40000094, FormationAllas001a, "FormationAllas001a-61");
				orderActorToFactory(40000095, FormationAllas001d, "FormationAllas001d-62");
				orderActorToFactory(40000096, FormationAllas001b, "FormationAllas001b-63");
				orderActorToFactory(40000097, FormationAllas001c, "FormationAllas001c-64");
				break;
			}
			case 1840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000029);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000044, EnemyEtis, "EnemyEtis-65");
				break;
			}
			case 1900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000030);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000045, EnemyEtis, "EnemyEtis-66");
				break;
			}
			case 1960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000031);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000046, EnemyEtis, "EnemyEtis-67");
				break;
			}
			case 2000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000101);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF68 = (FormationEbe001*)obtainActorFromFactory(40000117);
				getSceneDirector()->addSubGroup(pF68);
				break;
			}
			case 2020: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000032);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000047, EnemyEtis, "EnemyEtis-69");
				break;
			}
			case 2080: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000033);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000048, EnemyEtis, "EnemyEtis-70");
				break;
			}
			case 2100: {
				orderActorToFactory(40000098, FormationGeria001, "FormationGeria001-71");
				orderActorToFactory(40000102, FormationHalia, "FormationHalia-72");
				orderActorToFactory(40000118, FormationEbe001, "FormationEbe001-73");
				break;
			}
			case 2140: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000034);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000049, EnemyEtis, "EnemyEtis-74");
				break;
			}
			case 2200: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000035);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000050, EnemyEtis, "EnemyEtis-75");
				break;
			}
			case 2260: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000036);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000051, EnemyEtis, "EnemyEtis-76");
				break;
			}
			case 2300: {
				EnemyStraea* pStraea2 = (EnemyStraea*)obtainActorFromFactory(40000083);
				getSceneDirector()->addSubGroup(pStraea2);
				pStraea2->_Z = 1800000;
				pStraea2->_Y = -100000;
				break;
			}
			case 2320: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000037);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000052, EnemyEtis, "EnemyEtis-77");
				break;
			}
			case 2380: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000038);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000053, EnemyEtis, "EnemyEtis-78");
				break;
			}
			case 2440: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000039);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000054, EnemyEtis, "EnemyEtis-79");
				break;
			}
			case 2500: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000040);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000055, EnemyEtis, "EnemyEtis-80");
				FormationAssalia* pFormationAssalia = (FormationAssalia*)obtainActorFromFactory(40000084);
				getSceneDirector()->addSubGroup(pFormationAssalia);
				break;
			}
			case 2560: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000041);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000056, EnemyEtis, "EnemyEtis-81");
				break;
			}
			case 2620: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000042);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000057, EnemyEtis, "EnemyEtis-82");
				break;
			}
			case 2680: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000043);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000058, EnemyEtis, "EnemyEtis-83");
				break;
			}
			case 2700: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-84");
				ta->setMaxPerformFrame(2500);
				addSubLast(ta);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000086)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000087)), 400);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000088)), 400);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000089)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000090)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000091)), 400);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000092)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000093)), 400);
				ta->addToTable(((FormationAllas001a*)obtainActorFromFactory(40000094)), 1);
				ta->addToTable(((FormationAllas001d*)obtainActorFromFactory(40000095)), 1);
				ta->addToTable(((FormationAllas001b*)obtainActorFromFactory(40000096)), 1);
				ta->addToTable(((FormationAllas001c*)obtainActorFromFactory(40000097)), 400);
				}
				break;
			}
			case 2740: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000044);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000059, EnemyEtis, "EnemyEtis-85");
				break;
			}
			case 2800: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000045);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000060, EnemyEtis, "EnemyEtis-86");
				break;
			}
			case 2860: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000046);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000061, EnemyEtis, "EnemyEtis-87");
				break;
			}
			case 2920: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000047);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000062, EnemyEtis, "EnemyEtis-88");
				break;
			}
			case 2980: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000048);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000063, EnemyEtis, "EnemyEtis-89");
				break;
			}
			case 3000: {
				FormationGeria001* pF90 = (FormationGeria001*)obtainActorFromFactory(40000098);
				getSceneDirector()->addSubGroup(pF90);
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000102);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF91 = (FormationEbe001*)obtainActorFromFactory(40000118);
				getSceneDirector()->addSubGroup(pF91);
				break;
			}
			case 3040: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000049);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000064, EnemyEtis, "EnemyEtis-92");
				break;
			}
			case 3100: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000050);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000065, EnemyEtis, "EnemyEtis-93");
				orderActorToFactory(40000099, VarietyRatislavia001, "VarietyRatislavia001-94");
				orderActorToFactory(40000103, FormationHalia, "FormationHalia-95");
				orderActorToFactory(40000119, FormationEbe001, "FormationEbe001-96");
				break;
			}
			case 3160: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000051);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000066, EnemyEtis, "EnemyEtis-97");
				break;
			}
			case 3220: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000052);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000067, EnemyEtis, "EnemyEtis-98");
				break;
			}
			case 3280: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000053);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000068, EnemyEtis, "EnemyEtis-99");
				break;
			}
			case 3340: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000054);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000069, EnemyEtis, "EnemyEtis-100");
				break;
			}
			case 3400: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000055);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000070, EnemyEtis, "EnemyEtis-101");
				break;
			}
			case 3460: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000056);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000071, EnemyEtis, "EnemyEtis-102");
				break;
			}
			case 3520: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000057);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000072, EnemyEtis, "EnemyEtis-103");
				break;
			}
			case 3580: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000058);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000073, EnemyEtis, "EnemyEtis-104");
				break;
			}
			case 3640: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000059);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000074, EnemyEtis, "EnemyEtis-105");
				break;
			}
			case 3700: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000060);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000075, EnemyEtis, "EnemyEtis-106");
				break;
			}
			case 3760: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000061);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000076, EnemyEtis, "EnemyEtis-107");
				break;
			}
			case 3820: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000062);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000077, EnemyEtis, "EnemyEtis-108");
				break;
			}
			case 3880: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000063);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000078, EnemyEtis, "EnemyEtis-109");
				break;
			}
			case 3940: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000064);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000079, EnemyEtis, "EnemyEtis-110");
				break;
			}
			case 4000: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000065);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000080, EnemyEtis, "EnemyEtis-111");
				VarietyRatislavia001* pRatislavia = (VarietyRatislavia001*)obtainActorFromFactory(40000099);
				getSceneDirector()->addSubGroup(pRatislavia);
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000103);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF112 = (FormationEbe001*)obtainActorFromFactory(40000119);
				getSceneDirector()->addSubGroup(pF112);
				break;
			}
			case 4060: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000066);
				getSceneDirector()->addSubGroup(pEtis);
				orderActorToFactory(40000081, EnemyEtis, "EnemyEtis-113");
				break;
			}
			case 4100: {
				orderActorToFactory(40000104, FormationHalia, "FormationHalia-114");
				orderActorToFactory(40000120, FormationEbe001, "FormationEbe001-115");
				orderActorToFactory(40000122, EnemyEsperia, "EnemyEsperia-116");
				break;
			}
			case 4120: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000067);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4180: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000068);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4240: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000069);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4300: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000070);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4360: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000071);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4400: {
				orderActorToFactory(40000123, EnemyEsperia, "EnemyEsperia-117");
				break;
			}
			case 4420: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000072);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4480: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000073);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4540: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000074);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4600: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000075);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4660: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000076);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4700: {
				orderActorToFactory(40000124, EnemyEsperia, "EnemyEsperia-118");
				break;
			}
			case 4720: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000077);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4780: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000078);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4840: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000079);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4900: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000080);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 4960: {
				EnemyEtis* pEtis = (EnemyEtis*)obtainActorFromFactory(40000081);
				getSceneDirector()->addSubGroup(pEtis);
				break;
			}
			case 5000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000104);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF119 = (FormationEbe001*)obtainActorFromFactory(40000120);
				getSceneDirector()->addSubGroup(pF119);
				EnemyEsperia* p120 = (EnemyEsperia*)obtainActorFromFactory(40000122);
				getSceneDirector()->addSubGroup(p120);
				orderActorToFactory(40000125, EnemyEsperia, "EnemyEsperia-121");
				break;
			}
			case 5100: {
				orderActorToFactory(40000105, FormationHalia, "FormationHalia-122");
				orderActorToFactory(40000121, FormationEbe001, "FormationEbe001-123");
				break;
			}
			case 5300: {
				EnemyEsperia* p124 = (EnemyEsperia*)obtainActorFromFactory(40000123);
				getSceneDirector()->addSubGroup(p124);
				orderActorToFactory(40000126, EnemyEsperia, "EnemyEsperia-125");
				break;
			}
			case 5600: {
				EnemyEsperia* p126 = (EnemyEsperia*)obtainActorFromFactory(40000124);
				getSceneDirector()->addSubGroup(p126);
				orderActorToFactory(40000127, EnemyEsperia, "EnemyEsperia-127");
				break;
			}
			case 5900: {
				EnemyEsperia* p128 = (EnemyEsperia*)obtainActorFromFactory(40000125);
				getSceneDirector()->addSubGroup(p128);
				orderActorToFactory(40000128, EnemyEsperia, "EnemyEsperia-129");
				break;
			}
			case 6000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000105);
				getSceneDirector()->addSubGroup(pF);
				FormationEbe001* pF130 = (FormationEbe001*)obtainActorFromFactory(40000121);
				getSceneDirector()->addSubGroup(pF130);
				break;
			}
			case 6100: {
				orderActorToFactory(40000106, FormationHalia, "FormationHalia-131");
				break;
			}
			case 6200: {
				EnemyEsperia* p132 = (EnemyEsperia*)obtainActorFromFactory(40000126);
				getSceneDirector()->addSubGroup(p132);
				orderActorToFactory(40000129, EnemyEsperia, "EnemyEsperia-133");
				break;
			}
			case 6500: {
				EnemyEsperia* p134 = (EnemyEsperia*)obtainActorFromFactory(40000127);
				getSceneDirector()->addSubGroup(p134);
				orderActorToFactory(40000130, EnemyEsperia, "EnemyEsperia-135");
				break;
			}
			case 6800: {
				EnemyEsperia* p136 = (EnemyEsperia*)obtainActorFromFactory(40000128);
				getSceneDirector()->addSubGroup(p136);
				orderActorToFactory(40000131, EnemyEsperia, "EnemyEsperia-137");
				break;
			}
			case 7000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000106);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 7100: {
				orderActorToFactory(40000107, FormationHalia, "FormationHalia-138");
				EnemyEsperia* p139 = (EnemyEsperia*)obtainActorFromFactory(40000129);
				getSceneDirector()->addSubGroup(p139);
				orderActorToFactory(40000132, EnemyEsperia, "EnemyEsperia-140");
				break;
			}
			case 7400: {
				EnemyEsperia* p141 = (EnemyEsperia*)obtainActorFromFactory(40000130);
				getSceneDirector()->addSubGroup(p141);
				orderActorToFactory(40000133, EnemyEsperia, "EnemyEsperia-142");
				break;
			}
			case 7700: {
				EnemyEsperia* p143 = (EnemyEsperia*)obtainActorFromFactory(40000131);
				getSceneDirector()->addSubGroup(p143);
				orderActorToFactory(40000134, EnemyEsperia, "EnemyEsperia-144");
				break;
			}
			case 8000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000107);
				getSceneDirector()->addSubGroup(pF);
				EnemyEsperia* p145 = (EnemyEsperia*)obtainActorFromFactory(40000132);
				getSceneDirector()->addSubGroup(p145);
				orderActorToFactory(40000135, EnemyEsperia, "EnemyEsperia-146");
				break;
			}
			case 8100: {
				orderActorToFactory(40000108, FormationHalia, "FormationHalia-147");
				break;
			}
			case 8300: {
				orderActorToFactory(40000110, FormationRis002, "FormationRis002-148");
				orderActorToFactory(40000111, FormationRis001, "FormationRis001-149");
				orderActorToFactory(40000112, FormationRis001, "FormationRis001-150");
				orderActorToFactory(40000113, FormationRis002, "FormationRis002-151");
				orderActorToFactory(40000114, FormationRis001, "FormationRis001-152");
				orderActorToFactory(40000115, FormationRis002, "FormationRis002-153");
				EnemyEsperia* p154 = (EnemyEsperia*)obtainActorFromFactory(40000133);
				getSceneDirector()->addSubGroup(p154);
				orderActorToFactory(40000136, EnemyEsperia, "EnemyEsperia-155");
				break;
			}
			case 8600: {
				EnemyEsperia* p156 = (EnemyEsperia*)obtainActorFromFactory(40000134);
				getSceneDirector()->addSubGroup(p156);
				orderActorToFactory(40000137, EnemyEsperia, "EnemyEsperia-157");
				break;
			}
			case 8900: {
				EnemyEsperia* p158 = (EnemyEsperia*)obtainActorFromFactory(40000135);
				getSceneDirector()->addSubGroup(p158);
				orderActorToFactory(40000138, EnemyEsperia, "EnemyEsperia-159");
				break;
			}
			case 9000: {
				FormationHalia* pF = (FormationHalia*)obtainActorFromFactory(40000108);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 9200: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-160");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000110)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000111)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000112)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000113)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000114)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000115)), 400);
				}
				EnemyEsperia* p161 = (EnemyEsperia*)obtainActorFromFactory(40000136);
				getSceneDirector()->addSubGroup(p161);
				break;
			}
			case 9500: {
				EnemyEsperia* p162 = (EnemyEsperia*)obtainActorFromFactory(40000137);
				getSceneDirector()->addSubGroup(p162);
				break;
			}
			case 9800: {
				EnemyEsperia* p163 = (EnemyEsperia*)obtainActorFromFactory(40000138);
				getSceneDirector()->addSubGroup(p163);
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
