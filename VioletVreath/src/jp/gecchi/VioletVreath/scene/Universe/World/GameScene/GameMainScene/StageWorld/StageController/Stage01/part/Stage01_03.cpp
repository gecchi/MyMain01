#include "stdafx.h"
#include "Stage01_03.h"

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

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000};
	_paFrame_NextEvent = new frame[101];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 101;
	orderActorToFactory(50000002, EnemyDrastea, "EnemyDrastea-1");
	orderActorToFactory(50000003, EnemyDrastea, "EnemyDrastea-2");
	orderActorToFactory(50000004, EnemyDrastea, "EnemyDrastea-3");
	orderActorToFactory(50000005, EnemyDrastea, "EnemyDrastea-4");
	orderActorToFactory(50000006, EnemyDrastea, "EnemyDrastea-5");
	orderActorToFactory(50000007, EnemyDrastea, "EnemyDrastea-6");
	orderActorToFactory(50000008, EnemyDrastea, "EnemyDrastea-7");
	orderActorToFactory(50000009, EnemyDrastea, "EnemyDrastea-8");
	orderActorToFactory(50000010, EnemyDrastea, "EnemyDrastea-9");
	orderActorToFactory(50000011, EnemyDrastea, "EnemyDrastea-10");
	orderActorToFactory(50000012, EnemyDrastea, "EnemyDrastea-11");
	orderActorToFactory(50000013, EnemyDrastea, "EnemyDrastea-12");
	orderActorToFactory(50000014, EnemyDrastea, "EnemyDrastea-13");
	orderActorToFactory(50000015, EnemyDrastea, "EnemyDrastea-14");
	
	orderActorToFactory(50000099, FormationRis001, "FormationRis001-15");
	orderActorToFactory(50000100, FormationRis002, "FormationRis002-16");
	orderActorToFactory(50000101, FormationRis001, "FormationRis001-17");
	orderActorToFactory(50000102, FormationRis002, "FormationRis002-18");
	orderActorToFactory(50000103, FormationRis001, "FormationRis001-19");
	orderActorToFactory(50000104, FormationRis002, "FormationRis002-20");
    // gen01 end
}

void Stage01_03::initialize() {

}

void Stage01_03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				orderActorToFactory(50000016, EnemyDrastea, "EnemyDrastea-21");
				break;
			}
			case 200: {
				orderActorToFactory(50000017, EnemyDrastea, "EnemyDrastea-22");
				break;
			}
			case 300: {
				orderActorToFactory(50000018, EnemyDrastea, "EnemyDrastea-23");
				break;
			}
			case 400: {
				orderActorToFactory(50000019, EnemyDrastea, "EnemyDrastea-24");
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000002);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000020, EnemyDrastea, "EnemyDrastea-25");
				break;
			}
			case 600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000003);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000021, EnemyDrastea, "EnemyDrastea-26");
				break;
			}
			case 700: {
				orderActorToFactory(50000000, FormationUnomia001a, "FormationUnomia001a-27");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000004);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000022, EnemyDrastea, "EnemyDrastea-28");
				break;
			}
			case 800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000005);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000023, EnemyDrastea, "EnemyDrastea-29");
				break;
			}
			case 900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000006);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000024, EnemyDrastea, "EnemyDrastea-30");
				break;
			}
			case 1000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000007);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000025, EnemyDrastea, "EnemyDrastea-31");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-32");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(50000099)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(50000100)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(50000101)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(50000102)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(50000103)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(50000104)), 400);
				}
				break;
			}
			case 1100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000008);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000026, EnemyDrastea, "EnemyDrastea-33");
				break;
			}
			case 1200: {
				orderActorToFactory(50000001, FormationUnomia001b, "FormationUnomia001b-34");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000009);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000027, EnemyDrastea, "EnemyDrastea-35");
				break;
			}
			case 1300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000010);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000028, EnemyDrastea, "EnemyDrastea-36");
				break;
			}
			case 1400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000011);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000029, EnemyDrastea, "EnemyDrastea-37");
				break;
			}
			case 1500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000012);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000030, EnemyDrastea, "EnemyDrastea-38");
				break;
			}
			case 1600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000013);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000031, EnemyDrastea, "EnemyDrastea-39");
				break;
			}
			case 1700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000014);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000032, EnemyDrastea, "EnemyDrastea-40");
				break;
			}
			case 1800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000015);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000033, EnemyDrastea, "EnemyDrastea-41");
				break;
			}
			case 1900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000016);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000034, EnemyDrastea, "EnemyDrastea-42");
				break;
			}
			case 2000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000017);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000035, EnemyDrastea, "EnemyDrastea-43");
				break;
			}
			case 2100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000018);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000036, EnemyDrastea, "EnemyDrastea-44");
				break;
			}
			case 2200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000019);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000037, EnemyDrastea, "EnemyDrastea-45");
				break;
			}
			case 2300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000020);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000038, EnemyDrastea, "EnemyDrastea-46");
				break;
			}
			case 2400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000021);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000039, EnemyDrastea, "EnemyDrastea-47");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(50000000);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000022);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000040, EnemyDrastea, "EnemyDrastea-48");
				break;
			}
			case 2600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000023);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000041, EnemyDrastea, "EnemyDrastea-49");
				break;
			}
			case 2700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000024);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000042, EnemyDrastea, "EnemyDrastea-50");
				break;
			}
			case 2800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000025);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000043, EnemyDrastea, "EnemyDrastea-51");
				break;
			}
			case 2900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000026);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000044, EnemyDrastea, "EnemyDrastea-52");
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(50000001);
				getSceneDirector()->addSubGroup(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000027);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000045, EnemyDrastea, "EnemyDrastea-53");
				break;
			}
			case 3100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000028);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000046, EnemyDrastea, "EnemyDrastea-54");
				break;
			}
			case 3200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000029);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000047, EnemyDrastea, "EnemyDrastea-55");
				break;
			}
			case 3300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000030);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000048, EnemyDrastea, "EnemyDrastea-56");
				break;
			}
			case 3400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000031);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000049, EnemyDrastea, "EnemyDrastea-57");
				break;
			}
			case 3500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000032);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000050, EnemyDrastea, "EnemyDrastea-58");
				break;
			}
			case 3600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000033);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000051, EnemyDrastea, "EnemyDrastea-59");
				break;
			}
			case 3700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000034);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000052, EnemyDrastea, "EnemyDrastea-60");
				break;
			}
			case 3800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000035);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000053, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 3900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000036);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000054, EnemyDrastea, "EnemyDrastea-62");
				break;
			}
			case 4000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000037);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000055, EnemyDrastea, "EnemyDrastea-63");
				break;
			}
			case 4100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000038);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000056, EnemyDrastea, "EnemyDrastea-64");
				break;
			}
			case 4200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000039);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000057, EnemyDrastea, "EnemyDrastea-65");
				break;
			}
			case 4300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000040);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000058, EnemyDrastea, "EnemyDrastea-66");
				break;
			}
			case 4400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000041);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000059, EnemyDrastea, "EnemyDrastea-67");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000042);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000060, EnemyDrastea, "EnemyDrastea-68");
				break;
			}
			case 4600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000043);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000061, EnemyDrastea, "EnemyDrastea-69");
				break;
			}
			case 4700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000044);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000062, EnemyDrastea, "EnemyDrastea-70");
				break;
			}
			case 4800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000045);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000063, EnemyDrastea, "EnemyDrastea-71");
				break;
			}
			case 4900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000046);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000064, EnemyDrastea, "EnemyDrastea-72");
				break;
			}
			case 5000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000047);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000065, EnemyDrastea, "EnemyDrastea-73");
				break;
			}
			case 5100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000048);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000066, EnemyDrastea, "EnemyDrastea-74");
				break;
			}
			case 5200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000049);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000067, EnemyDrastea, "EnemyDrastea-75");
				break;
			}
			case 5300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000050);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000068, EnemyDrastea, "EnemyDrastea-76");
				break;
			}
			case 5400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000051);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000069, EnemyDrastea, "EnemyDrastea-77");
				break;
			}
			case 5500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000052);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000070, EnemyDrastea, "EnemyDrastea-78");
				break;
			}
			case 5600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000053);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000071, EnemyDrastea, "EnemyDrastea-79");
				break;
			}
			case 5700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000054);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000072, EnemyDrastea, "EnemyDrastea-80");
				break;
			}
			case 5800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000055);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000073, EnemyDrastea, "EnemyDrastea-81");
				break;
			}
			case 5900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000056);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000074, EnemyDrastea, "EnemyDrastea-82");
				break;
			}
			case 6000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000057);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000075, EnemyDrastea, "EnemyDrastea-83");
				break;
			}
			case 6100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000058);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000076, EnemyDrastea, "EnemyDrastea-84");
				break;
			}
			case 6200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000059);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000077, EnemyDrastea, "EnemyDrastea-85");
				break;
			}
			case 6300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000060);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000078, EnemyDrastea, "EnemyDrastea-86");
				break;
			}
			case 6400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000061);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000079, EnemyDrastea, "EnemyDrastea-87");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000062);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000080, EnemyDrastea, "EnemyDrastea-88");
				break;
			}
			case 6600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000063);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000081, EnemyDrastea, "EnemyDrastea-89");
				break;
			}
			case 6700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000064);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000082, EnemyDrastea, "EnemyDrastea-90");
				break;
			}
			case 6800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000065);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000083, EnemyDrastea, "EnemyDrastea-91");
				break;
			}
			case 6900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000066);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000084, EnemyDrastea, "EnemyDrastea-92");
				break;
			}
			case 7000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000067);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000085, EnemyDrastea, "EnemyDrastea-93");
				break;
			}
			case 7100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000068);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000086, EnemyDrastea, "EnemyDrastea-94");
				break;
			}
			case 7200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000069);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000087, EnemyDrastea, "EnemyDrastea-95");
				break;
			}
			case 7300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000070);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000088, EnemyDrastea, "EnemyDrastea-96");
				break;
			}
			case 7400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000071);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000089, EnemyDrastea, "EnemyDrastea-97");
				break;
			}
			case 7500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000072);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000090, EnemyDrastea, "EnemyDrastea-98");
				break;
			}
			case 7600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000073);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000091, EnemyDrastea, "EnemyDrastea-99");
				break;
			}
			case 7700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000074);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000092, EnemyDrastea, "EnemyDrastea-100");
				break;
			}
			case 7800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000075);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000093, EnemyDrastea, "EnemyDrastea-101");
				break;
			}
			case 7900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000076);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000094, EnemyDrastea, "EnemyDrastea-102");
				break;
			}
			case 8000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000077);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000095, EnemyDrastea, "EnemyDrastea-103");
				break;
			}
			case 8100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000078);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000096, EnemyDrastea, "EnemyDrastea-104");
				break;
			}
			case 8200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000079);
				getSceneDirector()->addSubGroup(p);
				orderActorToFactory(50000097, EnemyDrastea, "EnemyDrastea-105");
				break;
			}
			case 8300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000080);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000081);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000082);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000083);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000084);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000085);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 8900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000086);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000087);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000088);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000089);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000090);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000091);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000092);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000093);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000094);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000095);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 9900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000096);
				getSceneDirector()->addSubGroup(p);
				break;
			}
			case 10000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(50000097);
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
    if (getActiveFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG01_03_WAS_BROKEN);
    }
}

Stage01_03::~Stage01_03() {

}
