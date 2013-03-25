#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000};
	_paFrame_NextEvent = new frame[101];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 101;
	orderActorToFactory(50000002, EnemyAdrastea, "EnemyAdrastea-1");
	orderActorToFactory(50000003, EnemyAdrastea, "EnemyAdrastea-2");
	orderActorToFactory(50000004, EnemyAdrastea, "EnemyAdrastea-3");
	orderActorToFactory(50000005, EnemyAdrastea, "EnemyAdrastea-4");
	orderActorToFactory(50000006, EnemyAdrastea, "EnemyAdrastea-5");
	orderActorToFactory(50000007, EnemyAdrastea, "EnemyAdrastea-6");
	orderActorToFactory(50000008, EnemyAdrastea, "EnemyAdrastea-7");
	orderActorToFactory(50000009, EnemyAdrastea, "EnemyAdrastea-8");
	orderActorToFactory(50000010, EnemyAdrastea, "EnemyAdrastea-9");
	orderActorToFactory(50000011, EnemyAdrastea, "EnemyAdrastea-10");
	orderActorToFactory(50000012, EnemyAdrastea, "EnemyAdrastea-11");
	orderActorToFactory(50000013, EnemyAdrastea, "EnemyAdrastea-12");
	orderActorToFactory(50000014, EnemyAdrastea, "EnemyAdrastea-13");
	orderActorToFactory(50000015, EnemyAdrastea, "EnemyAdrastea-14");
	
	orderActorToFactory(50000099, FormationIris001, "FormationIris001-15");
	orderActorToFactory(50000100, FormationIris002, "FormationIris002-16");
	orderActorToFactory(50000101, FormationIris001, "FormationIris001-17");
	orderActorToFactory(50000102, FormationIris002, "FormationIris002-18");
	orderActorToFactory(50000103, FormationIris001, "FormationIris001-19");
	orderActorToFactory(50000104, FormationIris002, "FormationIris002-20");
    // gen01 end
}

void Stage01_03::initialize() {

}

void Stage01_03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				orderActorToFactory(50000016, EnemyAdrastea, "EnemyAdrastea-21");
				break;
			}
			case 200: {
				orderActorToFactory(50000017, EnemyAdrastea, "EnemyAdrastea-22");
				break;
			}
			case 300: {
				orderActorToFactory(50000018, EnemyAdrastea, "EnemyAdrastea-23");
				break;
			}
			case 400: {
				orderActorToFactory(50000019, EnemyAdrastea, "EnemyAdrastea-24");
				break;
			}
			case 500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000002);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000020, EnemyAdrastea, "EnemyAdrastea-25");
				break;
			}
			case 600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000003);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000021, EnemyAdrastea, "EnemyAdrastea-26");
				break;
			}
			case 700: {
				orderActorToFactory(50000000, FormationEunomia001a, "FormationEunomia001a-27");
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000004);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000022, EnemyAdrastea, "EnemyAdrastea-28");
				break;
			}
			case 800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000005);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000023, EnemyAdrastea, "EnemyAdrastea-29");
				break;
			}
			case 900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000006);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000024, EnemyAdrastea, "EnemyAdrastea-30");
				break;
			}
			case 1000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000007);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000025, EnemyAdrastea, "EnemyAdrastea-31");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-32");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000099)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000101)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000102)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000103)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000104)), 400);
				}
				break;
			}
			case 1100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000008);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000026, EnemyAdrastea, "EnemyAdrastea-33");
				break;
			}
			case 1200: {
				orderActorToFactory(50000001, FormationEunomia001b, "FormationEunomia001b-34");
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000009);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000027, EnemyAdrastea, "EnemyAdrastea-35");
				break;
			}
			case 1300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000010);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000028, EnemyAdrastea, "EnemyAdrastea-36");
				break;
			}
			case 1400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000011);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000029, EnemyAdrastea, "EnemyAdrastea-37");
				break;
			}
			case 1500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000012);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000030, EnemyAdrastea, "EnemyAdrastea-38");
				break;
			}
			case 1600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000013);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000031, EnemyAdrastea, "EnemyAdrastea-39");
				break;
			}
			case 1700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000014);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000032, EnemyAdrastea, "EnemyAdrastea-40");
				break;
			}
			case 1800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000015);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000033, EnemyAdrastea, "EnemyAdrastea-41");
				break;
			}
			case 1900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000016);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000034, EnemyAdrastea, "EnemyAdrastea-42");
				break;
			}
			case 2000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000017);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000035, EnemyAdrastea, "EnemyAdrastea-43");
				break;
			}
			case 2100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000018);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000036, EnemyAdrastea, "EnemyAdrastea-44");
				break;
			}
			case 2200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000019);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000037, EnemyAdrastea, "EnemyAdrastea-45");
				break;
			}
			case 2300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000020);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000038, EnemyAdrastea, "EnemyAdrastea-46");
				break;
			}
			case 2400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000021);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000039, EnemyAdrastea, "EnemyAdrastea-47");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(50000000);
				getSceneDirector()->addSubGroup(pFormationEunomia);
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000022);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000040, EnemyAdrastea, "EnemyAdrastea-48");
				break;
			}
			case 2600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000023);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000041, EnemyAdrastea, "EnemyAdrastea-49");
				break;
			}
			case 2700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000024);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000042, EnemyAdrastea, "EnemyAdrastea-50");
				break;
			}
			case 2800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000025);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000043, EnemyAdrastea, "EnemyAdrastea-51");
				break;
			}
			case 2900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000026);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000044, EnemyAdrastea, "EnemyAdrastea-52");
				break;
			}
			case 3000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(50000001);
				getSceneDirector()->addSubGroup(pFormationEunomia);
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000027);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000045, EnemyAdrastea, "EnemyAdrastea-53");
				break;
			}
			case 3100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000028);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000046, EnemyAdrastea, "EnemyAdrastea-54");
				break;
			}
			case 3200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000029);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000047, EnemyAdrastea, "EnemyAdrastea-55");
				break;
			}
			case 3300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000030);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000048, EnemyAdrastea, "EnemyAdrastea-56");
				break;
			}
			case 3400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000031);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000049, EnemyAdrastea, "EnemyAdrastea-57");
				break;
			}
			case 3500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000032);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000050, EnemyAdrastea, "EnemyAdrastea-58");
				break;
			}
			case 3600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000033);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000051, EnemyAdrastea, "EnemyAdrastea-59");
				break;
			}
			case 3700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000034);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000052, EnemyAdrastea, "EnemyAdrastea-60");
				break;
			}
			case 3800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000035);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000053, EnemyAdrastea, "EnemyAdrastea-61");
				break;
			}
			case 3900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000036);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000054, EnemyAdrastea, "EnemyAdrastea-62");
				break;
			}
			case 4000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000037);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000055, EnemyAdrastea, "EnemyAdrastea-63");
				break;
			}
			case 4100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000038);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000056, EnemyAdrastea, "EnemyAdrastea-64");
				break;
			}
			case 4200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000039);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000057, EnemyAdrastea, "EnemyAdrastea-65");
				break;
			}
			case 4300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000040);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000058, EnemyAdrastea, "EnemyAdrastea-66");
				break;
			}
			case 4400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000041);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000059, EnemyAdrastea, "EnemyAdrastea-67");
				break;
			}
			case 4500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000042);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000060, EnemyAdrastea, "EnemyAdrastea-68");
				break;
			}
			case 4600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000043);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000061, EnemyAdrastea, "EnemyAdrastea-69");
				break;
			}
			case 4700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000044);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000062, EnemyAdrastea, "EnemyAdrastea-70");
				break;
			}
			case 4800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000045);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000063, EnemyAdrastea, "EnemyAdrastea-71");
				break;
			}
			case 4900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000046);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000064, EnemyAdrastea, "EnemyAdrastea-72");
				break;
			}
			case 5000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000047);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000065, EnemyAdrastea, "EnemyAdrastea-73");
				break;
			}
			case 5100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000048);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000066, EnemyAdrastea, "EnemyAdrastea-74");
				break;
			}
			case 5200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000049);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000067, EnemyAdrastea, "EnemyAdrastea-75");
				break;
			}
			case 5300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000050);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000068, EnemyAdrastea, "EnemyAdrastea-76");
				break;
			}
			case 5400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000051);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000069, EnemyAdrastea, "EnemyAdrastea-77");
				break;
			}
			case 5500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000052);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000070, EnemyAdrastea, "EnemyAdrastea-78");
				break;
			}
			case 5600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000053);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000071, EnemyAdrastea, "EnemyAdrastea-79");
				break;
			}
			case 5700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000054);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000072, EnemyAdrastea, "EnemyAdrastea-80");
				break;
			}
			case 5800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000055);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000073, EnemyAdrastea, "EnemyAdrastea-81");
				break;
			}
			case 5900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000056);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000074, EnemyAdrastea, "EnemyAdrastea-82");
				break;
			}
			case 6000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000057);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000075, EnemyAdrastea, "EnemyAdrastea-83");
				break;
			}
			case 6100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000058);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000076, EnemyAdrastea, "EnemyAdrastea-84");
				break;
			}
			case 6200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000059);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000077, EnemyAdrastea, "EnemyAdrastea-85");
				break;
			}
			case 6300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000060);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000078, EnemyAdrastea, "EnemyAdrastea-86");
				break;
			}
			case 6400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000061);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000079, EnemyAdrastea, "EnemyAdrastea-87");
				break;
			}
			case 6500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000062);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000080, EnemyAdrastea, "EnemyAdrastea-88");
				break;
			}
			case 6600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000063);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000081, EnemyAdrastea, "EnemyAdrastea-89");
				break;
			}
			case 6700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000064);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000082, EnemyAdrastea, "EnemyAdrastea-90");
				break;
			}
			case 6800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000065);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000083, EnemyAdrastea, "EnemyAdrastea-91");
				break;
			}
			case 6900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000066);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000084, EnemyAdrastea, "EnemyAdrastea-92");
				break;
			}
			case 7000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000067);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000085, EnemyAdrastea, "EnemyAdrastea-93");
				break;
			}
			case 7100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000068);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000086, EnemyAdrastea, "EnemyAdrastea-94");
				break;
			}
			case 7200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000069);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000087, EnemyAdrastea, "EnemyAdrastea-95");
				break;
			}
			case 7300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000070);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000088, EnemyAdrastea, "EnemyAdrastea-96");
				break;
			}
			case 7400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000071);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000089, EnemyAdrastea, "EnemyAdrastea-97");
				break;
			}
			case 7500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000072);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000090, EnemyAdrastea, "EnemyAdrastea-98");
				break;
			}
			case 7600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000073);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000091, EnemyAdrastea, "EnemyAdrastea-99");
				break;
			}
			case 7700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000074);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000092, EnemyAdrastea, "EnemyAdrastea-100");
				break;
			}
			case 7800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000075);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000093, EnemyAdrastea, "EnemyAdrastea-101");
				break;
			}
			case 7900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000076);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000094, EnemyAdrastea, "EnemyAdrastea-102");
				break;
			}
			case 8000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000077);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000095, EnemyAdrastea, "EnemyAdrastea-103");
				break;
			}
			case 8100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000078);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000096, EnemyAdrastea, "EnemyAdrastea-104");
				break;
			}
			case 8200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000079);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000097, EnemyAdrastea, "EnemyAdrastea-105");
				break;
			}
			case 8300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000080);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000081);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000082);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000083);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000084);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000085);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000086);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000087);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000088);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9200: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000089);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000090);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000091);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000092);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000093);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000094);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9800: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000095);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000096);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 10000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(50000097);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 101-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActivePartFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG01_03_WAS_BROKEN);
    }
}

Stage01_03::~Stage01_03() {

}
