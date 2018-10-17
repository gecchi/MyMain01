#include "Stage01Part03.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01Part03::Stage01Part03(const char* prm_name) :
        Stage01Part<GgafLib::DefaultScene>(prm_name, EVENT_STAGE01_PART_03_WAS_FINISHED) {
    _class_name = "Stage01Part03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000};
	_paFrame_NextEvent = new frame[101];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 101;
	requestActor(40000002, EnemyDrastea, "EnemyDrastea-40000002");
	requestActor(40000003, EnemyDrastea, "EnemyDrastea-40000003");
	requestActor(40000105, FormationAntiope001, "FormationAntiope001-40000105");
    // gen01 end

    getBgmConductor()->ready(0, "OGG_BGM_01_03");
}

void Stage01Part03::initialize() {

}

void Stage01Part03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 100: {
				requestActor(40000004, EnemyDrastea, "EnemyDrastea-40000004");
				break;
			}
			case 200: {
				requestActor(40000005, EnemyDrastea, "EnemyDrastea-40000005");
				break;
			}
			case 300: {
				requestActor(40000006, EnemyDrastea, "EnemyDrastea-40000006");
				break;
			}
			case 400: {
				requestActor(40000007, EnemyDrastea, "EnemyDrastea-40000007");
				requestActor(40000099, FormationRis001, "FormationRis001-40000099");
				requestActor(40000100, FormationRis002, "FormationRis002-40000100");
				requestActor(40000101, FormationRis001, "FormationRis001-40000101");
				requestActor(40000102, FormationRis002, "FormationRis002-40000102");
				requestActor(40000103, FormationRis001, "FormationRis001-40000103");
				requestActor(40000104, FormationRis002, "FormationRis002-40000104");
				FormationAntiope001* pFAnti = (FormationAntiope001*)receiveActor(40000105);
				bringSceneMediator()->appendGroupChild(pFAnti);
				requestActor(40000106, FormationAntiope001, "FormationAntiope001-40000106");
				break;
			}
			case 500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000002);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000008, EnemyDrastea, "EnemyDrastea-40000008");
				break;
			}
			case 600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000003);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000009, EnemyDrastea, "EnemyDrastea-40000009");
				break;
			}
			case 700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000004);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000010, EnemyDrastea, "EnemyDrastea-40000010");
				break;
			}
			case 800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000005);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000011, EnemyDrastea, "EnemyDrastea-40000011");
				break;
			}
			case 900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000006);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000012, EnemyDrastea, "EnemyDrastea-40000012");
				break;
			}
			case 1000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000007);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000013, EnemyDrastea, "EnemyDrastea-40000013");
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-1");
				ta->setMaxPerformFrame(2000);
				appendChild(ta);
				ta->addToTable(((FormationRis001*)receiveActor(40000099)), 400);
				ta->addToTable(((FormationRis002*)receiveActor(40000100)), 400);
				ta->addToTable(((FormationRis001*)receiveActor(40000101)), 400);
				ta->addToTable(((FormationRis002*)receiveActor(40000102)), 400);
				ta->addToTable(((FormationRis001*)receiveActor(40000103)), 400);
				ta->addToTable(((FormationRis002*)receiveActor(40000104)), 400);
				}
				FormationAntiope001* pFAnti = (FormationAntiope001*)receiveActor(40000106);
				bringSceneMediator()->appendGroupChild(pFAnti);
				break;
			}
			case 1100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000008);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000014, EnemyDrastea, "EnemyDrastea-40000014");
				break;
			}
			case 1200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000009);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000015, EnemyDrastea, "EnemyDrastea-40000015");
				break;
			}
			case 1300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000010);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000016, EnemyDrastea, "EnemyDrastea-40000016");
				break;
			}
			case 1400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000011);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000017, EnemyDrastea, "EnemyDrastea-40000017");
				break;
			}
			case 1500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000012);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000018, EnemyDrastea, "EnemyDrastea-40000018");
				break;
			}
			case 1600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000013);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000019, EnemyDrastea, "EnemyDrastea-40000019");
				break;
			}
			case 1700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000014);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000020, EnemyDrastea, "EnemyDrastea-40000020");
				break;
			}
			case 1800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000015);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000021, EnemyDrastea, "EnemyDrastea-40000021");
				break;
			}
			case 1900: {
				requestActor(40000000, FormationUnomia001a, "FormationUnomia001a-40000000");
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000016);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000022, EnemyDrastea, "EnemyDrastea-40000022");
				break;
			}
			case 2000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000017);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000023, EnemyDrastea, "EnemyDrastea-40000023");
				break;
			}
			case 2100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000018);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000024, EnemyDrastea, "EnemyDrastea-40000024");
				break;
			}
			case 2200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000019);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000025, EnemyDrastea, "EnemyDrastea-40000025");
				break;
			}
			case 2300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000020);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000026, EnemyDrastea, "EnemyDrastea-40000026");
				break;
			}
			case 2400: {
				requestActor(40000001, FormationUnomia001b, "FormationUnomia001b-40000001");
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000021);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000027, EnemyDrastea, "EnemyDrastea-40000027");
				break;
			}
			case 2500: {
				FormationUnomia001a* pFormationUnomia = (FormationUnomia001a*)receiveActor(40000000);
				bringSceneMediator()->appendGroupChild(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000022);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000028, EnemyDrastea, "EnemyDrastea-40000028");
				break;
			}
			case 2600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000023);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000029, EnemyDrastea, "EnemyDrastea-40000029");
				break;
			}
			case 2700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000024);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000030, EnemyDrastea, "EnemyDrastea-40000030");
				break;
			}
			case 2800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000025);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000031, EnemyDrastea, "EnemyDrastea-40000031");
				break;
			}
			case 2900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000026);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000032, EnemyDrastea, "EnemyDrastea-40000032");
				break;
			}
			case 3000: {
				FormationUnomia001b* pFormationUnomia = (FormationUnomia001b*)receiveActor(40000001);
				bringSceneMediator()->appendGroupChild(pFormationUnomia);
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000027);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000033, EnemyDrastea, "EnemyDrastea-40000033");
				break;
			}
			case 3100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000028);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000034, EnemyDrastea, "EnemyDrastea-40000034");
				break;
			}
			case 3200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000029);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000035, EnemyDrastea, "EnemyDrastea-40000035");
				break;
			}
			case 3300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000030);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000036, EnemyDrastea, "EnemyDrastea-40000036");
				break;
			}
			case 3400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000031);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000037, EnemyDrastea, "EnemyDrastea-40000037");
				break;
			}
			case 3500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000032);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000038, EnemyDrastea, "EnemyDrastea-40000038");
				break;
			}
			case 3600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000033);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000039, EnemyDrastea, "EnemyDrastea-40000039");
				break;
			}
			case 3700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000034);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000040, EnemyDrastea, "EnemyDrastea-40000040");
				break;
			}
			case 3800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000035);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000041, EnemyDrastea, "EnemyDrastea-40000041");
				break;
			}
			case 3900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000036);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000042, EnemyDrastea, "EnemyDrastea-40000042");
				break;
			}
			case 4000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000037);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000043, EnemyDrastea, "EnemyDrastea-40000043");
				break;
			}
			case 4100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000038);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000044, EnemyDrastea, "EnemyDrastea-40000044");
				break;
			}
			case 4200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000039);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000045, EnemyDrastea, "EnemyDrastea-40000045");
				break;
			}
			case 4300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000040);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000046, EnemyDrastea, "EnemyDrastea-40000046");
				break;
			}
			case 4400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000041);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000047, EnemyDrastea, "EnemyDrastea-40000047");
				break;
			}
			case 4500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000042);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000048, EnemyDrastea, "EnemyDrastea-40000048");
				break;
			}
			case 4600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000043);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000049, EnemyDrastea, "EnemyDrastea-40000049");
				break;
			}
			case 4700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000044);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000050, EnemyDrastea, "EnemyDrastea-40000050");
				break;
			}
			case 4800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000045);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000051, EnemyDrastea, "EnemyDrastea-40000051");
				break;
			}
			case 4900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000046);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000052, EnemyDrastea, "EnemyDrastea-40000052");
				break;
			}
			case 5000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000047);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000053, EnemyDrastea, "EnemyDrastea-40000053");
				break;
			}
			case 5100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000048);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000054, EnemyDrastea, "EnemyDrastea-40000054");
				break;
			}
			case 5200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000049);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000055, EnemyDrastea, "EnemyDrastea-40000055");
				break;
			}
			case 5300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000050);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000056, EnemyDrastea, "EnemyDrastea-40000056");
				break;
			}
			case 5400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000051);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000057, EnemyDrastea, "EnemyDrastea-40000057");
				break;
			}
			case 5500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000052);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000058, EnemyDrastea, "EnemyDrastea-40000058");
				break;
			}
			case 5600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000053);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000059, EnemyDrastea, "EnemyDrastea-40000059");
				break;
			}
			case 5700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000054);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000060, EnemyDrastea, "EnemyDrastea-40000060");
				break;
			}
			case 5800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000055);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000061, EnemyDrastea, "EnemyDrastea-40000061");
				break;
			}
			case 5900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000056);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000062, EnemyDrastea, "EnemyDrastea-40000062");
				break;
			}
			case 6000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000057);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000063, EnemyDrastea, "EnemyDrastea-40000063");
				break;
			}
			case 6100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000058);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000064, EnemyDrastea, "EnemyDrastea-40000064");
				break;
			}
			case 6200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000059);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000065, EnemyDrastea, "EnemyDrastea-40000065");
				break;
			}
			case 6300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000060);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000066, EnemyDrastea, "EnemyDrastea-40000066");
				break;
			}
			case 6400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000061);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000067, EnemyDrastea, "EnemyDrastea-40000067");
				break;
			}
			case 6500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000062);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000068, EnemyDrastea, "EnemyDrastea-40000068");
				break;
			}
			case 6600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000063);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000069, EnemyDrastea, "EnemyDrastea-40000069");
				break;
			}
			case 6700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000064);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000070, EnemyDrastea, "EnemyDrastea-40000070");
				break;
			}
			case 6800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000065);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000071, EnemyDrastea, "EnemyDrastea-40000071");
				break;
			}
			case 6900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000066);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000072, EnemyDrastea, "EnemyDrastea-40000072");
				break;
			}
			case 7000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000067);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000073, EnemyDrastea, "EnemyDrastea-40000073");
				break;
			}
			case 7100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000068);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000074, EnemyDrastea, "EnemyDrastea-40000074");
				break;
			}
			case 7200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000069);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000075, EnemyDrastea, "EnemyDrastea-40000075");
				break;
			}
			case 7300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000070);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000076, EnemyDrastea, "EnemyDrastea-40000076");
				break;
			}
			case 7400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000071);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000077, EnemyDrastea, "EnemyDrastea-40000077");
				break;
			}
			case 7500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000072);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000078, EnemyDrastea, "EnemyDrastea-40000078");
				break;
			}
			case 7600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000073);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000079, EnemyDrastea, "EnemyDrastea-40000079");
				break;
			}
			case 7700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000074);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000080, EnemyDrastea, "EnemyDrastea-40000080");
				break;
			}
			case 7800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000075);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000081, EnemyDrastea, "EnemyDrastea-40000081");
				break;
			}
			case 7900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000076);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000082, EnemyDrastea, "EnemyDrastea-40000082");
				break;
			}
			case 8000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000077);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000083, EnemyDrastea, "EnemyDrastea-40000083");
				break;
			}
			case 8100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000078);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000084, EnemyDrastea, "EnemyDrastea-40000084");
				break;
			}
			case 8200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000079);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000085, EnemyDrastea, "EnemyDrastea-40000085");
				break;
			}
			case 8300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000080);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000086, EnemyDrastea, "EnemyDrastea-40000086");
				break;
			}
			case 8400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000081);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000087, EnemyDrastea, "EnemyDrastea-40000087");
				break;
			}
			case 8500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000082);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000088, EnemyDrastea, "EnemyDrastea-40000088");
				break;
			}
			case 8600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000083);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000089, EnemyDrastea, "EnemyDrastea-40000089");
				break;
			}
			case 8700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000084);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000090, EnemyDrastea, "EnemyDrastea-40000090");
				break;
			}
			case 8800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000085);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000091, EnemyDrastea, "EnemyDrastea-40000091");
				break;
			}
			case 8900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000086);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000092, EnemyDrastea, "EnemyDrastea-40000092");
				break;
			}
			case 9000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000087);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000093, EnemyDrastea, "EnemyDrastea-40000093");
				break;
			}
			case 9100: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000088);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000094, EnemyDrastea, "EnemyDrastea-40000094");
				break;
			}
			case 9200: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000089);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000095, EnemyDrastea, "EnemyDrastea-40000095");
				break;
			}
			case 9300: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000090);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000096, EnemyDrastea, "EnemyDrastea-40000096");
				break;
			}
			case 9400: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000091);
				bringSceneMediator()->appendGroupChild(p);
				requestActor(40000097, EnemyDrastea, "EnemyDrastea-40000097");
				break;
			}
			case 9500: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000092);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 9600: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000093);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 9700: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000094);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 9800: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000095);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 9900: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000096);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			case 10000: {
				EnemyDrastea* p = (EnemyDrastea*)receiveActor(40000097);
				bringSceneMediator()->appendGroupChild(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 101-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01Part03::~Stage01Part03() {

}
