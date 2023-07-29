#include "StageDebugPart03.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/RotateFormationScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"




using namespace GgafLib;
using namespace VioletVreath;

StageDebugPart03::StageDebugPart03(const char* prm_name) :
        StageDebugPart<GgafLib::DefaultScene>(prm_name, EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
    _class_name = "StageDebugPart03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000};
	_paFrame_NextEvent = new frame[101];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 101;
	requestActor(40000002, EnemyDrastea);
	requestActor(40000003, EnemyDrastea);
	requestActor(40000105, FormationAntiope001);
    // gen01 end

    getBgmConductor()->ready(0, "BGM_01_03");
}

void StageDebugPart03::initialize() {

}

void StageDebugPart03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				requestActor(40000004, EnemyDrastea);
				break;
			}
			case 200: {
				requestActor(40000005, EnemyDrastea);
				break;
			}
			case 300: {
				requestActor(40000006, EnemyDrastea);
				break;
			}
			case 400: {
				requestActor(40000007, EnemyDrastea);
				requestActor(40000099, FormationRis001);
				requestActor(40000100, FormationRis002);
				requestActor(40000101, FormationRis001);
				requestActor(40000102, FormationRis002);
				requestActor(40000103, FormationRis001);
				requestActor(40000104, FormationRis002);
				FormationAntiope001* pFAnti = (FormationAntiope001*)receiveActor(40000105);
				getSceneChief()->appendGroupChild(pFAnti);
				requestActor(40000106, FormationAntiope001);
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000002);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000008, EnemyDrastea);
				break;
			}
			case 600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000003);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000009, EnemyDrastea);
				break;
			}
			case 700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000004);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000010, EnemyDrastea);
				break;
			}
			case 800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000005);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000011, EnemyDrastea);
				break;
			}
			case 900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000006);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000012, EnemyDrastea);
				break;
			}
			case 1000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000007);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000013, EnemyDrastea);
				{
				RotateFormationScene* ta = NEW RotateFormationScene("RotateFormationScene-1");
				ta->setMaxPerformFrame(2000);
				appendChild(ta);
				ta->addFormation(((FormationRis001*)receiveActor(40000099)), 400);
				ta->addFormation(((FormationRis002*)receiveActor(40000100)), 400);
				ta->addFormation(((FormationRis001*)receiveActor(40000101)), 400);
				ta->addFormation(((FormationRis002*)receiveActor(40000102)), 400);
				ta->addFormation(((FormationRis001*)receiveActor(40000103)), 400);
				ta->addFormation(((FormationRis002*)receiveActor(40000104)), 400);
				}
				FormationAntiope001* pFAnti = (FormationAntiope001*)receiveActor(40000106);
				getSceneChief()->appendGroupChild(pFAnti);
				break;
			}
			case 1100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000008);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000014, EnemyDrastea);
				break;
			}
			case 1200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000009);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000015, EnemyDrastea);
				break;
			}
			case 1300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000010);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000016, EnemyDrastea);
				break;
			}
			case 1400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000011);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000017, EnemyDrastea);
				break;
			}
			case 1500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000012);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000018, EnemyDrastea);
				break;
			}
			case 1600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000013);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000019, EnemyDrastea);
				break;
			}
			case 1700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000014);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000020, EnemyDrastea);
				break;
			}
			case 1800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000015);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000021, EnemyDrastea);
				break;
			}
			case 1900: {
				requestActor(40000000, FormationUnomia001a);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000016);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000022, EnemyDrastea);
				break;
			}
			case 2000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000017);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000023, EnemyDrastea);
				break;
			}
			case 2100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000018);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000024, EnemyDrastea);
				break;
			}
			case 2200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000019);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000025, EnemyDrastea);
				break;
			}
			case 2300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000020);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000026, EnemyDrastea);
				break;
			}
			case 2400: {
				requestActor(40000001, FormationUnomia001b);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000021);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000027, EnemyDrastea);
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)receiveActor(40000000);
				getSceneChief()->appendGroupChild(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000022);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000028, EnemyDrastea);
				break;
			}
			case 2600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000023);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000029, EnemyDrastea);
				break;
			}
			case 2700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000024);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000030, EnemyDrastea);
				break;
			}
			case 2800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000025);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000031, EnemyDrastea);
				break;
			}
			case 2900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000026);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000032, EnemyDrastea);
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)receiveActor(40000001);
				getSceneChief()->appendGroupChild(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000027);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000033, EnemyDrastea);
				break;
			}
			case 3100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000028);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000034, EnemyDrastea);
				break;
			}
			case 3200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000029);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000035, EnemyDrastea);
				break;
			}
			case 3300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000030);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000036, EnemyDrastea);
				break;
			}
			case 3400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000031);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000037, EnemyDrastea);
				break;
			}
			case 3500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000032);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000038, EnemyDrastea);
				break;
			}
			case 3600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000033);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000039, EnemyDrastea);
				break;
			}
			case 3700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000034);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000040, EnemyDrastea);
				break;
			}
			case 3800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000035);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000041, EnemyDrastea);
				break;
			}
			case 3900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000036);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000042, EnemyDrastea);
				break;
			}
			case 4000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000037);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000043, EnemyDrastea);
				break;
			}
			case 4100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000038);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000044, EnemyDrastea);
				break;
			}
			case 4200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000039);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000045, EnemyDrastea);
				break;
			}
			case 4300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000040);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000046, EnemyDrastea);
				break;
			}
			case 4400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000041);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000047, EnemyDrastea);
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000042);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000048, EnemyDrastea);
				break;
			}
			case 4600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000043);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000049, EnemyDrastea);
				break;
			}
			case 4700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000044);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000050, EnemyDrastea);
				break;
			}
			case 4800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000045);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000051, EnemyDrastea);
				break;
			}
			case 4900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000046);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000052, EnemyDrastea);
				break;
			}
			case 5000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000047);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000053, EnemyDrastea);
				break;
			}
			case 5100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000048);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000054, EnemyDrastea);
				break;
			}
			case 5200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000049);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000055, EnemyDrastea);
				break;
			}
			case 5300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000050);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000056, EnemyDrastea);
				break;
			}
			case 5400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000051);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000057, EnemyDrastea);
				break;
			}
			case 5500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000052);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000058, EnemyDrastea);
				break;
			}
			case 5600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000053);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000059, EnemyDrastea);
				break;
			}
			case 5700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000054);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000060, EnemyDrastea);
				break;
			}
			case 5800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000055);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000061, EnemyDrastea);
				break;
			}
			case 5900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000056);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000062, EnemyDrastea);
				break;
			}
			case 6000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000057);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000063, EnemyDrastea);
				break;
			}
			case 6100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000058);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000064, EnemyDrastea);
				break;
			}
			case 6200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000059);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000065, EnemyDrastea);
				break;
			}
			case 6300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000060);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000066, EnemyDrastea);
				break;
			}
			case 6400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000061);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000067, EnemyDrastea);
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000062);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000068, EnemyDrastea);
				break;
			}
			case 6600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000063);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000069, EnemyDrastea);
				break;
			}
			case 6700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000064);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000070, EnemyDrastea);
				break;
			}
			case 6800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000065);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000071, EnemyDrastea);
				break;
			}
			case 6900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000066);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000072, EnemyDrastea);
				break;
			}
			case 7000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000067);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000073, EnemyDrastea);
				break;
			}
			case 7100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000068);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000074, EnemyDrastea);
				break;
			}
			case 7200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000069);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000075, EnemyDrastea);
				break;
			}
			case 7300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000070);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000076, EnemyDrastea);
				break;
			}
			case 7400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000071);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000077, EnemyDrastea);
				break;
			}
			case 7500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000072);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000078, EnemyDrastea);
				break;
			}
			case 7600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000073);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000079, EnemyDrastea);
				break;
			}
			case 7700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000074);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000080, EnemyDrastea);
				break;
			}
			case 7800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000075);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000081, EnemyDrastea);
				break;
			}
			case 7900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000076);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000082, EnemyDrastea);
				break;
			}
			case 8000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000077);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000083, EnemyDrastea);
				break;
			}
			case 8100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000078);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000084, EnemyDrastea);
				break;
			}
			case 8200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000079);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000085, EnemyDrastea);
				break;
			}
			case 8300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000080);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000086, EnemyDrastea);
				break;
			}
			case 8400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000081);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000087, EnemyDrastea);
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000082);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000088, EnemyDrastea);
				break;
			}
			case 8600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000083);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000089, EnemyDrastea);
				break;
			}
			case 8700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000084);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000090, EnemyDrastea);
				break;
			}
			case 8800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000085);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000091, EnemyDrastea);
				break;
			}
			case 8900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000086);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000092, EnemyDrastea);
				break;
			}
			case 9000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000087);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000093, EnemyDrastea);
				break;
			}
			case 9100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000088);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000094, EnemyDrastea);
				break;
			}
			case 9200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000089);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000095, EnemyDrastea);
				break;
			}
			case 9300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000090);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000096, EnemyDrastea);
				break;
			}
			case 9400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000091);
				getSceneChief()->appendGroupChild(p);
				requestActor(40000097, EnemyDrastea);
				break;
			}
			case 9500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000092);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 9600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000093);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 9700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000094);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 9800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000095);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 9900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000096);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			case 10000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000097);
				getSceneChief()->appendGroupChild(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 101-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

StageDebugPart03::~StageDebugPart03() {

}
