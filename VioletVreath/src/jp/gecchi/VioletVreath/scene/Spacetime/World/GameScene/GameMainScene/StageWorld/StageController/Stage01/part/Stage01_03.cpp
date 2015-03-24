#include "Stage01_03.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

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
	orderActorToFactory(40000002, EnemyDrastea, "EnemyDrastea-1");
	orderActorToFactory(40000003, EnemyDrastea, "EnemyDrastea-2");
	orderActorToFactory(40000105, FormationAntiope001, "FormationAntiope001-3");
    // gen01 end

    getBGMer()->ready(0, "OGG_BGM_01_03");
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
				orderActorToFactory(40000004, EnemyDrastea, "EnemyDrastea-4");
				break;
			}
			case 200: {
				orderActorToFactory(40000005, EnemyDrastea, "EnemyDrastea-5");
				break;
			}
			case 300: {
				orderActorToFactory(40000006, EnemyDrastea, "EnemyDrastea-6");
				break;
			}
			case 400: {
				orderActorToFactory(40000007, EnemyDrastea, "EnemyDrastea-7");
				orderActorToFactory(40000099, FormationRis001, "FormationRis001-8");
				orderActorToFactory(40000100, FormationRis002, "FormationRis002-9");
				orderActorToFactory(40000101, FormationRis001, "FormationRis001-10");
				orderActorToFactory(40000102, FormationRis002, "FormationRis002-11");
				orderActorToFactory(40000103, FormationRis001, "FormationRis001-12");
				orderActorToFactory(40000104, FormationRis002, "FormationRis002-13");
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(40000105);
				bringDirector()->addSubGroup(pFAnti);
				orderActorToFactory(40000106, FormationAntiope001, "FormationAntiope001-14");
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000002);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000008, EnemyDrastea, "EnemyDrastea-15");
				break;
			}
			case 600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000003);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000009, EnemyDrastea, "EnemyDrastea-16");
				break;
			}
			case 700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000004);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000010, EnemyDrastea, "EnemyDrastea-17");
				break;
			}
			case 800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000005);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000011, EnemyDrastea, "EnemyDrastea-18");
				break;
			}
			case 900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000006);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000012, EnemyDrastea, "EnemyDrastea-19");
				break;
			}
			case 1000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000007);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000013, EnemyDrastea, "EnemyDrastea-20");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-21");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000099)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000100)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000101)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000102)), 400);
				ta->addToTable(((FormationRis001*)obtainActorFromFactory(40000103)), 400);
				ta->addToTable(((FormationRis002*)obtainActorFromFactory(40000104)), 400);
				}
				FormationAntiope001* pFAnti = (FormationAntiope001*)obtainActorFromFactory(40000106);
				bringDirector()->addSubGroup(pFAnti);
				break;
			}
			case 1100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000008);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000014, EnemyDrastea, "EnemyDrastea-22");
				break;
			}
			case 1200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000009);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000015, EnemyDrastea, "EnemyDrastea-23");
				break;
			}
			case 1300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000010);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000016, EnemyDrastea, "EnemyDrastea-24");
				break;
			}
			case 1400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000011);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000017, EnemyDrastea, "EnemyDrastea-25");
				break;
			}
			case 1500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000012);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000018, EnemyDrastea, "EnemyDrastea-26");
				break;
			}
			case 1600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000013);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000019, EnemyDrastea, "EnemyDrastea-27");
				break;
			}
			case 1700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000014);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000020, EnemyDrastea, "EnemyDrastea-28");
				break;
			}
			case 1800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000015);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000021, EnemyDrastea, "EnemyDrastea-29");
				break;
			}
			case 1900: {
				orderActorToFactory(40000000, FormationUnomia001a, "FormationUnomia001a-30");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000016);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000022, EnemyDrastea, "EnemyDrastea-31");
				break;
			}
			case 2000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000017);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000023, EnemyDrastea, "EnemyDrastea-32");
				break;
			}
			case 2100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000018);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000024, EnemyDrastea, "EnemyDrastea-33");
				break;
			}
			case 2200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000019);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000025, EnemyDrastea, "EnemyDrastea-34");
				break;
			}
			case 2300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000020);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000026, EnemyDrastea, "EnemyDrastea-35");
				break;
			}
			case 2400: {
				orderActorToFactory(40000001, FormationUnomia001b, "FormationUnomia001b-36");
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000021);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000027, EnemyDrastea, "EnemyDrastea-37");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)obtainActorFromFactory(40000000);
				bringDirector()->addSubGroup(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000022);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000028, EnemyDrastea, "EnemyDrastea-38");
				break;
			}
			case 2600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000023);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000029, EnemyDrastea, "EnemyDrastea-39");
				break;
			}
			case 2700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000024);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000030, EnemyDrastea, "EnemyDrastea-40");
				break;
			}
			case 2800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000025);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000031, EnemyDrastea, "EnemyDrastea-41");
				break;
			}
			case 2900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000026);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000032, EnemyDrastea, "EnemyDrastea-42");
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)obtainActorFromFactory(40000001);
				bringDirector()->addSubGroup(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000027);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000033, EnemyDrastea, "EnemyDrastea-43");
				break;
			}
			case 3100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000028);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000034, EnemyDrastea, "EnemyDrastea-44");
				break;
			}
			case 3200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000029);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000035, EnemyDrastea, "EnemyDrastea-45");
				break;
			}
			case 3300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000030);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000036, EnemyDrastea, "EnemyDrastea-46");
				break;
			}
			case 3400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000031);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000037, EnemyDrastea, "EnemyDrastea-47");
				break;
			}
			case 3500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000032);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000038, EnemyDrastea, "EnemyDrastea-48");
				break;
			}
			case 3600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000033);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000039, EnemyDrastea, "EnemyDrastea-49");
				break;
			}
			case 3700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000034);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000040, EnemyDrastea, "EnemyDrastea-50");
				break;
			}
			case 3800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000035);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000041, EnemyDrastea, "EnemyDrastea-51");
				break;
			}
			case 3900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000036);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000042, EnemyDrastea, "EnemyDrastea-52");
				break;
			}
			case 4000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000037);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000043, EnemyDrastea, "EnemyDrastea-53");
				break;
			}
			case 4100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000038);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000044, EnemyDrastea, "EnemyDrastea-54");
				break;
			}
			case 4200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000039);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000045, EnemyDrastea, "EnemyDrastea-55");
				break;
			}
			case 4300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000040);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000046, EnemyDrastea, "EnemyDrastea-56");
				break;
			}
			case 4400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000041);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000047, EnemyDrastea, "EnemyDrastea-57");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000042);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000048, EnemyDrastea, "EnemyDrastea-58");
				break;
			}
			case 4600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000043);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000049, EnemyDrastea, "EnemyDrastea-59");
				break;
			}
			case 4700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000044);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000050, EnemyDrastea, "EnemyDrastea-60");
				break;
			}
			case 4800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000045);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000051, EnemyDrastea, "EnemyDrastea-61");
				break;
			}
			case 4900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000046);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000052, EnemyDrastea, "EnemyDrastea-62");
				break;
			}
			case 5000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000047);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000053, EnemyDrastea, "EnemyDrastea-63");
				break;
			}
			case 5100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000048);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000054, EnemyDrastea, "EnemyDrastea-64");
				break;
			}
			case 5200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000049);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000055, EnemyDrastea, "EnemyDrastea-65");
				break;
			}
			case 5300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000050);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000056, EnemyDrastea, "EnemyDrastea-66");
				break;
			}
			case 5400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000051);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000057, EnemyDrastea, "EnemyDrastea-67");
				break;
			}
			case 5500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000052);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000058, EnemyDrastea, "EnemyDrastea-68");
				break;
			}
			case 5600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000053);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000059, EnemyDrastea, "EnemyDrastea-69");
				break;
			}
			case 5700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000054);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000060, EnemyDrastea, "EnemyDrastea-70");
				break;
			}
			case 5800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000055);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000061, EnemyDrastea, "EnemyDrastea-71");
				break;
			}
			case 5900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000056);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000062, EnemyDrastea, "EnemyDrastea-72");
				break;
			}
			case 6000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000057);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000063, EnemyDrastea, "EnemyDrastea-73");
				break;
			}
			case 6100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000058);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000064, EnemyDrastea, "EnemyDrastea-74");
				break;
			}
			case 6200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000059);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000065, EnemyDrastea, "EnemyDrastea-75");
				break;
			}
			case 6300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000060);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000066, EnemyDrastea, "EnemyDrastea-76");
				break;
			}
			case 6400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000061);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000067, EnemyDrastea, "EnemyDrastea-77");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000062);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000068, EnemyDrastea, "EnemyDrastea-78");
				break;
			}
			case 6600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000063);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000069, EnemyDrastea, "EnemyDrastea-79");
				break;
			}
			case 6700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000064);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000070, EnemyDrastea, "EnemyDrastea-80");
				break;
			}
			case 6800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000065);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000071, EnemyDrastea, "EnemyDrastea-81");
				break;
			}
			case 6900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000066);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000072, EnemyDrastea, "EnemyDrastea-82");
				break;
			}
			case 7000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000067);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000073, EnemyDrastea, "EnemyDrastea-83");
				break;
			}
			case 7100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000068);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000074, EnemyDrastea, "EnemyDrastea-84");
				break;
			}
			case 7200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000069);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000075, EnemyDrastea, "EnemyDrastea-85");
				break;
			}
			case 7300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000070);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000076, EnemyDrastea, "EnemyDrastea-86");
				break;
			}
			case 7400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000071);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000077, EnemyDrastea, "EnemyDrastea-87");
				break;
			}
			case 7500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000072);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000078, EnemyDrastea, "EnemyDrastea-88");
				break;
			}
			case 7600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000073);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000079, EnemyDrastea, "EnemyDrastea-89");
				break;
			}
			case 7700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000074);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000080, EnemyDrastea, "EnemyDrastea-90");
				break;
			}
			case 7800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000075);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000081, EnemyDrastea, "EnemyDrastea-91");
				break;
			}
			case 7900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000076);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000082, EnemyDrastea, "EnemyDrastea-92");
				break;
			}
			case 8000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000077);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000083, EnemyDrastea, "EnemyDrastea-93");
				break;
			}
			case 8100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000078);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000084, EnemyDrastea, "EnemyDrastea-94");
				break;
			}
			case 8200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000079);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000085, EnemyDrastea, "EnemyDrastea-95");
				break;
			}
			case 8300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000080);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000086, EnemyDrastea, "EnemyDrastea-96");
				break;
			}
			case 8400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000081);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000087, EnemyDrastea, "EnemyDrastea-97");
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000082);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000088, EnemyDrastea, "EnemyDrastea-98");
				break;
			}
			case 8600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000083);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000089, EnemyDrastea, "EnemyDrastea-99");
				break;
			}
			case 8700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000084);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000090, EnemyDrastea, "EnemyDrastea-100");
				break;
			}
			case 8800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000085);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000091, EnemyDrastea, "EnemyDrastea-101");
				break;
			}
			case 8900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000086);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000092, EnemyDrastea, "EnemyDrastea-102");
				break;
			}
			case 9000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000087);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000093, EnemyDrastea, "EnemyDrastea-103");
				break;
			}
			case 9100: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000088);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000094, EnemyDrastea, "EnemyDrastea-104");
				break;
			}
			case 9200: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000089);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000095, EnemyDrastea, "EnemyDrastea-105");
				break;
			}
			case 9300: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000090);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000096, EnemyDrastea, "EnemyDrastea-106");
				break;
			}
			case 9400: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000091);
				bringDirector()->addSubGroup(p);
				orderActorToFactory(40000097, EnemyDrastea, "EnemyDrastea-107");
				break;
			}
			case 9500: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000092);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 9600: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000093);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 9700: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000094);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 9800: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000095);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 9900: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000096);
				bringDirector()->addSubGroup(p);
				break;
			}
			case 10000: {
				EnemyDrastea* p = (EnemyDrastea*)obtainActorFromFactory(40000097);
				bringDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 101-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    if (getBehaveingFrame() == 1 && P_GAME_SCENE->getProgress()->get() == GameScene::PROG_MAIN) {
        //兄弟シーンのBGMを全てフェードアウトし、自分のシーンBGMをフェードイン
        StagePartController* pStagePartController = (StagePartController*)(getParent());
        pStagePartController->fadeout_stop_AllPartSceneBgm();
        getBGMer()->play_fadein(0);
    }
    if (getBehaveingFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        getBGMer()->fadeout_stop(0);
        getBGMer()->fadeout_stop(0);
        throwEventUpperTree(EVENT_STG01_03_WAS_BROKEN);
    }
}

Stage01_03::~Stage01_03() {

}
