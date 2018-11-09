#include "StageDebugPartController.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebug.h"
#include "part/StageDebugPart01.h"
#include "part/StageDebugPart02.h"
#include "part/StageDebugPart03.h"
#include "part/StageDebugPartClimax.h"
#include "part/StageDebugPartWall.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_FAINAL ,
    PROG_BANPEI,
};

StageDebugPartController::StageDebugPartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "StageDebugPartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,5,100,105,205,300,305,405,505,605,705,805,905,1005,1105,1205,1305,1405,1505,1605,1705,1805,1905,2005,2105,2205,2305,2405,2505,2605,2705,2805,2905,3005,3105,3200,3205,3305,3405,3505,3605,3705,3805,3905,4005,4100,4105,4205,4305,4405,4505,4605,4705,4805,4905,5005,5105,5205,5305,5405,5505,5605,5705,5805,5905,6005,6105,6205,6305,6405,6505,6605,6705,6805,6905,7005,7105,7200,7205,7305,7405,7505,7605,7705,7805,7905,8005,8100,8105,8205,8305,8405,8505,8605,8705,8805,8905,9005,9105,9205,9305,9405,9505,9605,9705,9805,9905,10005,10105,10205,10305,10405,10505,10605,10705,10805,10905,11005,11105,11205,11305,11405,11505,11605,11705,11805,11905,12005,12105,12205,12305,12405,12505,12605,12705,12805,12905,13005,13105,13205,13305,13405,13505,13605,13705,13805,13905,14005,14105,14205,14305,14405,14505,14605,14705,14805,14905,15005,15105,15205,15305,15405,15505,15605,15705,15805,15905,16005,16105,16205,16305,16405,16505,16605,16705,16805,16905,17005,17105,17205,17305,17405,17505,17605,17705,17805,17905,18005,18105,18205,18305,18405,18505,18605,18705,18805,18905,19005,19105,19205,19305,19405,19505,19605,19705,19805,19905,20005,20105,20205,20305,20405,20505,20605,20705,20805,20905,21005,21100,21105,21205,21305,21405,21505,21605,21705,21805,21905,22000};
	_paFrame_NextEvent = new frame[229];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 229;
	requestScene(10000000, StageDebugPart01, "StageDebugPart01-10000000");
	requestActor(10000004, EnemyOzartia, "EnemyOzartia-10000004");
	requestActor(10000005, EnemyEtis, "EnemyEtis-10000005");
	requestActor(10000006, EnemyEtis, "EnemyEtis-10000006");
	requestActor(10000007, EnemyEtis, "EnemyEtis-10000007");
	requestActor(10000008, EnemyEtis, "EnemyEtis-10000008");
	requestActor(10000009, EnemyEtis, "EnemyEtis-10000009");
	requestActor(10000010, EnemyEtis, "EnemyEtis-10000010");
    // gen01 end
    useProgress(PROG_BANPEI);
}

void StageDebugPartController::initialize() {
    getProgress()->reset(PROG_INIT);
}

void StageDebugPartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000005);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000011, EnemyEtis, "EnemyEtis-10000011");
				break;
			}
			case 100: {
				appendChild(receiveScene(10000000));
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000006);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000012, EnemyEtis, "EnemyEtis-10000012");
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000007);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000013, EnemyEtis, "EnemyEtis-10000013");
				break;
			}
			case 300: {
				EnemyOzartia* p = (EnemyOzartia*)receiveActor(10000004);
				bringSceneMediator()->appendGroupChild(p);
				p->setPosition(1000000,0,0);
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000008);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000014, EnemyEtis, "EnemyEtis-10000014");
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000009);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000015, EnemyEtis, "EnemyEtis-10000015");
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000010);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000016, EnemyEtis, "EnemyEtis-10000016");
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000011);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000017, EnemyEtis, "EnemyEtis-10000017");
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000012);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000018, EnemyEtis, "EnemyEtis-10000018");
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000013);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000019, EnemyEtis, "EnemyEtis-10000019");
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000014);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000020, EnemyEtis, "EnemyEtis-10000020");
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000015);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000021, EnemyEtis, "EnemyEtis-10000021");
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000016);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000022, EnemyEtis, "EnemyEtis-10000022");
				break;
			}
			case 1205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000017);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000023, EnemyEtis, "EnemyEtis-10000023");
				break;
			}
			case 1305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000018);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000024, EnemyEtis, "EnemyEtis-10000024");
				break;
			}
			case 1405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000019);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000025, EnemyEtis, "EnemyEtis-10000025");
				break;
			}
			case 1505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000020);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000026, EnemyEtis, "EnemyEtis-10000026");
				break;
			}
			case 1605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000021);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000027, EnemyEtis, "EnemyEtis-10000027");
				break;
			}
			case 1705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000022);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000028, EnemyEtis, "EnemyEtis-10000028");
				break;
			}
			case 1805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000023);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000029, EnemyEtis, "EnemyEtis-10000029");
				break;
			}
			case 1905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000024);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000030, EnemyEtis, "EnemyEtis-10000030");
				break;
			}
			case 2005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000025);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000031, EnemyEtis, "EnemyEtis-10000031");
				break;
			}
			case 2105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000026);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000032, EnemyEtis, "EnemyEtis-10000032");
				break;
			}
			case 2205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000027);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000033, EnemyEtis, "EnemyEtis-10000033");
				break;
			}
			case 2305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000028);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000034, EnemyEtis, "EnemyEtis-10000034");
				break;
			}
			case 2405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000029);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000035, EnemyEtis, "EnemyEtis-10000035");
				break;
			}
			case 2505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000030);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000036, EnemyEtis, "EnemyEtis-10000036");
				break;
			}
			case 2605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000031);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000037, EnemyEtis, "EnemyEtis-10000037");
				break;
			}
			case 2705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000032);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000038, EnemyEtis, "EnemyEtis-10000038");
				break;
			}
			case 2805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000033);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000039, EnemyEtis, "EnemyEtis-10000039");
				break;
			}
			case 2905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000034);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000040, EnemyEtis, "EnemyEtis-10000040");
				break;
			}
			case 3005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000035);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000041, EnemyEtis, "EnemyEtis-10000041");
				break;
			}
			case 3105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000036);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000042, EnemyEtis, "EnemyEtis-10000042");
				break;
			}
			case 3200: {
				requestScene(10000001, StageDebugPart02, "StageDebugPart02-10000001");
				break;
			}
			case 3205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000037);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000043, EnemyEtis, "EnemyEtis-10000043");
				break;
			}
			case 3305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000038);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000044, EnemyEtis, "EnemyEtis-10000044");
				break;
			}
			case 3405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000039);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000045, EnemyEtis, "EnemyEtis-10000045");
				break;
			}
			case 3505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000040);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000046, EnemyEtis, "EnemyEtis-10000046");
				break;
			}
			case 3605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000041);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000047, EnemyEtis, "EnemyEtis-10000047");
				break;
			}
			case 3705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000042);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000048, EnemyEtis, "EnemyEtis-10000048");
				break;
			}
			case 3805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000043);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000049, EnemyEtis, "EnemyEtis-10000049");
				break;
			}
			case 3905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000044);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000050, EnemyEtis, "EnemyEtis-10000050");
				break;
			}
			case 4005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000045);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000051, EnemyEtis, "EnemyEtis-10000051");
				break;
			}
			case 4100: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 4105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000046);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000052, EnemyEtis, "EnemyEtis-10000052");
				break;
			}
			case 4205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000047);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000053, EnemyEtis, "EnemyEtis-10000053");
				break;
			}
			case 4305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000048);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000054, EnemyEtis, "EnemyEtis-10000054");
				break;
			}
			case 4405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000049);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000055, EnemyEtis, "EnemyEtis-10000055");
				break;
			}
			case 4505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000050);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000056, EnemyEtis, "EnemyEtis-10000056");
				break;
			}
			case 4605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000051);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000057, EnemyEtis, "EnemyEtis-10000057");
				break;
			}
			case 4705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000052);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000058, EnemyEtis, "EnemyEtis-10000058");
				break;
			}
			case 4805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000053);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000059, EnemyEtis, "EnemyEtis-10000059");
				break;
			}
			case 4905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000054);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000060, EnemyEtis, "EnemyEtis-10000060");
				break;
			}
			case 5005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000055);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000061, EnemyEtis, "EnemyEtis-10000061");
				break;
			}
			case 5105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000056);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000062, EnemyEtis, "EnemyEtis-10000062");
				break;
			}
			case 5205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000057);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000063, EnemyEtis, "EnemyEtis-10000063");
				break;
			}
			case 5305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000058);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000064, EnemyEtis, "EnemyEtis-10000064");
				break;
			}
			case 5405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000059);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000065, EnemyEtis, "EnemyEtis-10000065");
				break;
			}
			case 5505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000060);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000066, EnemyEtis, "EnemyEtis-10000066");
				break;
			}
			case 5605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000061);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000067, EnemyEtis, "EnemyEtis-10000067");
				break;
			}
			case 5705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000062);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000068, EnemyEtis, "EnemyEtis-10000068");
				break;
			}
			case 5805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000063);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000069, EnemyEtis, "EnemyEtis-10000069");
				break;
			}
			case 5905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000064);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000070, EnemyEtis, "EnemyEtis-10000070");
				break;
			}
			case 6005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000065);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000071, EnemyEtis, "EnemyEtis-10000071");
				break;
			}
			case 6105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000066);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000072, EnemyEtis, "EnemyEtis-10000072");
				break;
			}
			case 6205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000067);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000073, EnemyEtis, "EnemyEtis-10000073");
				break;
			}
			case 6305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000068);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000074, EnemyEtis, "EnemyEtis-10000074");
				break;
			}
			case 6405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000069);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000075, EnemyEtis, "EnemyEtis-10000075");
				break;
			}
			case 6505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000070);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000076, EnemyEtis, "EnemyEtis-10000076");
				break;
			}
			case 6605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000071);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000077, EnemyEtis, "EnemyEtis-10000077");
				break;
			}
			case 6705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000072);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000078, EnemyEtis, "EnemyEtis-10000078");
				break;
			}
			case 6805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000073);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000079, EnemyEtis, "EnemyEtis-10000079");
				break;
			}
			case 6905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000074);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000080, EnemyEtis, "EnemyEtis-10000080");
				break;
			}
			case 7005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000075);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000081, EnemyEtis, "EnemyEtis-10000081");
				break;
			}
			case 7105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000076);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000082, EnemyEtis, "EnemyEtis-10000082");
				break;
			}
			case 7200: {
				requestScene(10000002, StageDebugPart03, "StageDebugPart03-10000002");
				break;
			}
			case 7205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000077);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000083, EnemyEtis, "EnemyEtis-10000083");
				break;
			}
			case 7305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000078);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000084, EnemyEtis, "EnemyEtis-10000084");
				break;
			}
			case 7405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000079);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000085, EnemyEtis, "EnemyEtis-10000085");
				break;
			}
			case 7505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000080);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000086, EnemyEtis, "EnemyEtis-10000086");
				break;
			}
			case 7605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000081);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000087, EnemyEtis, "EnemyEtis-10000087");
				break;
			}
			case 7705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000082);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000088, EnemyEtis, "EnemyEtis-10000088");
				break;
			}
			case 7805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000083);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000089, EnemyEtis, "EnemyEtis-10000089");
				break;
			}
			case 7905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000084);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000090, EnemyEtis, "EnemyEtis-10000090");
				break;
			}
			case 8005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000085);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000091, EnemyEtis, "EnemyEtis-10000091");
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				break;
			}
			case 8105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000086);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000092, EnemyEtis, "EnemyEtis-10000092");
				break;
			}
			case 8205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000087);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000093, EnemyEtis, "EnemyEtis-10000093");
				break;
			}
			case 8305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000088);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000094, EnemyEtis, "EnemyEtis-10000094");
				break;
			}
			case 8405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000089);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000095, EnemyEtis, "EnemyEtis-10000095");
				break;
			}
			case 8505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000090);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000096, EnemyEtis, "EnemyEtis-10000096");
				break;
			}
			case 8605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000091);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000097, EnemyEtis, "EnemyEtis-10000097");
				break;
			}
			case 8705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000092);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000098, EnemyEtis, "EnemyEtis-10000098");
				break;
			}
			case 8805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000093);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000099, EnemyEtis, "EnemyEtis-10000099");
				break;
			}
			case 8905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000094);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000100, EnemyEtis, "EnemyEtis-10000100");
				break;
			}
			case 9005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000095);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000101, EnemyEtis, "EnemyEtis-10000101");
				break;
			}
			case 9105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000096);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000102, EnemyEtis, "EnemyEtis-10000102");
				break;
			}
			case 9205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000097);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000103, EnemyEtis, "EnemyEtis-10000103");
				break;
			}
			case 9305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000098);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000104, EnemyEtis, "EnemyEtis-10000104");
				break;
			}
			case 9405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000099);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000105, EnemyEtis, "EnemyEtis-10000105");
				break;
			}
			case 9505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000100);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000106, EnemyEtis, "EnemyEtis-10000106");
				break;
			}
			case 9605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000101);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000107, EnemyEtis, "EnemyEtis-10000107");
				break;
			}
			case 9705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000102);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000108, EnemyEtis, "EnemyEtis-10000108");
				break;
			}
			case 9805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000103);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000109, EnemyEtis, "EnemyEtis-10000109");
				break;
			}
			case 9905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000104);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000110, EnemyEtis, "EnemyEtis-10000110");
				break;
			}
			case 10005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000105);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000111, EnemyEtis, "EnemyEtis-10000111");
				break;
			}
			case 10105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000106);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000112, EnemyEtis, "EnemyEtis-10000112");
				break;
			}
			case 10205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000107);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000113, EnemyEtis, "EnemyEtis-10000113");
				break;
			}
			case 10305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000108);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000114, EnemyEtis, "EnemyEtis-10000114");
				break;
			}
			case 10405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000109);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000115, EnemyEtis, "EnemyEtis-10000115");
				break;
			}
			case 10505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000110);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000116, EnemyEtis, "EnemyEtis-10000116");
				break;
			}
			case 10605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000111);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000117, EnemyEtis, "EnemyEtis-10000117");
				break;
			}
			case 10705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000112);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000118, EnemyEtis, "EnemyEtis-10000118");
				break;
			}
			case 10805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000113);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000119, EnemyEtis, "EnemyEtis-10000119");
				break;
			}
			case 10905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000114);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000120, EnemyEtis, "EnemyEtis-10000120");
				break;
			}
			case 11005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000115);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000121, EnemyEtis, "EnemyEtis-10000121");
				break;
			}
			case 11105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000116);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000122, EnemyEtis, "EnemyEtis-10000122");
				break;
			}
			case 11205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000117);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000123, EnemyEtis, "EnemyEtis-10000123");
				break;
			}
			case 11305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000118);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000124, EnemyEtis, "EnemyEtis-10000124");
				break;
			}
			case 11405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000119);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000125, EnemyEtis, "EnemyEtis-10000125");
				break;
			}
			case 11505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000120);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000126, EnemyEtis, "EnemyEtis-10000126");
				break;
			}
			case 11605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000121);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000127, EnemyEtis, "EnemyEtis-10000127");
				break;
			}
			case 11705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000122);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000128, EnemyEtis, "EnemyEtis-10000128");
				break;
			}
			case 11805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000123);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000129, EnemyEtis, "EnemyEtis-10000129");
				break;
			}
			case 11905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000124);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000130, EnemyEtis, "EnemyEtis-10000130");
				break;
			}
			case 12005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000125);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000131, EnemyEtis, "EnemyEtis-10000131");
				break;
			}
			case 12105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000126);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000132, EnemyEtis, "EnemyEtis-10000132");
				break;
			}
			case 12205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000127);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000133, EnemyEtis, "EnemyEtis-10000133");
				break;
			}
			case 12305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000128);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000134, EnemyEtis, "EnemyEtis-10000134");
				break;
			}
			case 12405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000129);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000135, EnemyEtis, "EnemyEtis-10000135");
				break;
			}
			case 12505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000130);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000136, EnemyEtis, "EnemyEtis-10000136");
				break;
			}
			case 12605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000131);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000137, EnemyEtis, "EnemyEtis-10000137");
				break;
			}
			case 12705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000132);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000138, EnemyEtis, "EnemyEtis-10000138");
				break;
			}
			case 12805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000133);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000139, EnemyEtis, "EnemyEtis-10000139");
				break;
			}
			case 12905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000134);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000140, EnemyEtis, "EnemyEtis-10000140");
				break;
			}
			case 13005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000135);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000141, EnemyEtis, "EnemyEtis-10000141");
				break;
			}
			case 13105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000136);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000142, EnemyEtis, "EnemyEtis-10000142");
				break;
			}
			case 13205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000137);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000143, EnemyEtis, "EnemyEtis-10000143");
				break;
			}
			case 13305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000138);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000144, EnemyEtis, "EnemyEtis-10000144");
				break;
			}
			case 13405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000139);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000145, EnemyEtis, "EnemyEtis-10000145");
				break;
			}
			case 13505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000140);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000146, EnemyEtis, "EnemyEtis-10000146");
				break;
			}
			case 13605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000141);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000147, EnemyEtis, "EnemyEtis-10000147");
				break;
			}
			case 13705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000142);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000148, EnemyEtis, "EnemyEtis-10000148");
				break;
			}
			case 13805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000143);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000149, EnemyEtis, "EnemyEtis-10000149");
				break;
			}
			case 13905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000144);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000150, EnemyEtis, "EnemyEtis-10000150");
				break;
			}
			case 14005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000145);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000151, EnemyEtis, "EnemyEtis-10000151");
				break;
			}
			case 14105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000146);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000152, EnemyEtis, "EnemyEtis-10000152");
				break;
			}
			case 14205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000147);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000153, EnemyEtis, "EnemyEtis-10000153");
				break;
			}
			case 14305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000148);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000154, EnemyEtis, "EnemyEtis-10000154");
				break;
			}
			case 14405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000149);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000155, EnemyEtis, "EnemyEtis-10000155");
				break;
			}
			case 14505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000150);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000156, EnemyEtis, "EnemyEtis-10000156");
				break;
			}
			case 14605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000151);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000157, EnemyEtis, "EnemyEtis-10000157");
				break;
			}
			case 14705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000152);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000158, EnemyEtis, "EnemyEtis-10000158");
				break;
			}
			case 14805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000153);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000159, EnemyEtis, "EnemyEtis-10000159");
				break;
			}
			case 14905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000154);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000160, EnemyEtis, "EnemyEtis-10000160");
				break;
			}
			case 15005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000155);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000161, EnemyEtis, "EnemyEtis-10000161");
				break;
			}
			case 15105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000156);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000162, EnemyEtis, "EnemyEtis-10000162");
				break;
			}
			case 15205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000157);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000163, EnemyEtis, "EnemyEtis-10000163");
				break;
			}
			case 15305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000158);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000164, EnemyEtis, "EnemyEtis-10000164");
				break;
			}
			case 15405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000159);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000165, EnemyEtis, "EnemyEtis-10000165");
				break;
			}
			case 15505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000160);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000166, EnemyEtis, "EnemyEtis-10000166");
				break;
			}
			case 15605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000161);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000167, EnemyEtis, "EnemyEtis-10000167");
				break;
			}
			case 15705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000162);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000168, EnemyEtis, "EnemyEtis-10000168");
				break;
			}
			case 15805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000163);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000169, EnemyEtis, "EnemyEtis-10000169");
				break;
			}
			case 15905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000164);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000170, EnemyEtis, "EnemyEtis-10000170");
				break;
			}
			case 16005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000165);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000171, EnemyEtis, "EnemyEtis-10000171");
				break;
			}
			case 16105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000166);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000172, EnemyEtis, "EnemyEtis-10000172");
				break;
			}
			case 16205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000167);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000173, EnemyEtis, "EnemyEtis-10000173");
				break;
			}
			case 16305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000168);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000174, EnemyEtis, "EnemyEtis-10000174");
				break;
			}
			case 16405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000169);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000175, EnemyEtis, "EnemyEtis-10000175");
				break;
			}
			case 16505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000170);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000176, EnemyEtis, "EnemyEtis-10000176");
				break;
			}
			case 16605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000171);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000177, EnemyEtis, "EnemyEtis-10000177");
				break;
			}
			case 16705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000172);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000178, EnemyEtis, "EnemyEtis-10000178");
				break;
			}
			case 16805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000173);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000179, EnemyEtis, "EnemyEtis-10000179");
				break;
			}
			case 16905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000174);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000180, EnemyEtis, "EnemyEtis-10000180");
				break;
			}
			case 17005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000175);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000181, EnemyEtis, "EnemyEtis-10000181");
				break;
			}
			case 17105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000176);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000182, EnemyEtis, "EnemyEtis-10000182");
				break;
			}
			case 17205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000177);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000183, EnemyEtis, "EnemyEtis-10000183");
				break;
			}
			case 17305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000178);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000184, EnemyEtis, "EnemyEtis-10000184");
				break;
			}
			case 17405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000179);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000185, EnemyEtis, "EnemyEtis-10000185");
				break;
			}
			case 17505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000180);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000186, EnemyEtis, "EnemyEtis-10000186");
				break;
			}
			case 17605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000181);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000187, EnemyEtis, "EnemyEtis-10000187");
				break;
			}
			case 17705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000182);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000188, EnemyEtis, "EnemyEtis-10000188");
				break;
			}
			case 17805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000183);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000189, EnemyEtis, "EnemyEtis-10000189");
				break;
			}
			case 17905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000184);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000190, EnemyEtis, "EnemyEtis-10000190");
				break;
			}
			case 18005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000185);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000191, EnemyEtis, "EnemyEtis-10000191");
				break;
			}
			case 18105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000186);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000192, EnemyEtis, "EnemyEtis-10000192");
				break;
			}
			case 18205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000187);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000193, EnemyEtis, "EnemyEtis-10000193");
				break;
			}
			case 18305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000188);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000194, EnemyEtis, "EnemyEtis-10000194");
				break;
			}
			case 18405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000189);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000195, EnemyEtis, "EnemyEtis-10000195");
				break;
			}
			case 18505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000190);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000196, EnemyEtis, "EnemyEtis-10000196");
				break;
			}
			case 18605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000191);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000197, EnemyEtis, "EnemyEtis-10000197");
				break;
			}
			case 18705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000192);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000198, EnemyEtis, "EnemyEtis-10000198");
				break;
			}
			case 18805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000193);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000199, EnemyEtis, "EnemyEtis-10000199");
				break;
			}
			case 18905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000194);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000200, EnemyEtis, "EnemyEtis-10000200");
				break;
			}
			case 19005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000195);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000201, EnemyEtis, "EnemyEtis-10000201");
				break;
			}
			case 19105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000196);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000202, EnemyEtis, "EnemyEtis-10000202");
				break;
			}
			case 19205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000197);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000203, EnemyEtis, "EnemyEtis-10000203");
				break;
			}
			case 19305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000198);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000204, EnemyEtis, "EnemyEtis-10000204");
				break;
			}
			case 19405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000199);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000205, EnemyEtis, "EnemyEtis-10000205");
				break;
			}
			case 19505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000200);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000206, EnemyEtis, "EnemyEtis-10000206");
				break;
			}
			case 19605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000201);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000207, EnemyEtis, "EnemyEtis-10000207");
				break;
			}
			case 19705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000202);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000208, EnemyEtis, "EnemyEtis-10000208");
				break;
			}
			case 19805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000203);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000209, EnemyEtis, "EnemyEtis-10000209");
				break;
			}
			case 19905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000204);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000210, EnemyEtis, "EnemyEtis-10000210");
				break;
			}
			case 20005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000205);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000211, EnemyEtis, "EnemyEtis-10000211");
				break;
			}
			case 20105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000206);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000212, EnemyEtis, "EnemyEtis-10000212");
				break;
			}
			case 20205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000207);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000213, EnemyEtis, "EnemyEtis-10000213");
				break;
			}
			case 20305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000208);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000214, EnemyEtis, "EnemyEtis-10000214");
				break;
			}
			case 20405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000209);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000215, EnemyEtis, "EnemyEtis-10000215");
				break;
			}
			case 20505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000210);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000216, EnemyEtis, "EnemyEtis-10000216");
				break;
			}
			case 20605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000211);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000217, EnemyEtis, "EnemyEtis-10000217");
				break;
			}
			case 20705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000212);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000218, EnemyEtis, "EnemyEtis-10000218");
				break;
			}
			case 20805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000213);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000219, EnemyEtis, "EnemyEtis-10000219");
				break;
			}
			case 20905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000214);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000220, EnemyEtis, "EnemyEtis-10000220");
				break;
			}
			case 21005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000215);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000221, EnemyEtis, "EnemyEtis-10000221");
				break;
			}
			case 21100: {
				requestScene(10000003, StageDebugPartClimax, "StageDebugPartClimax-10000003");
				break;
			}
			case 21105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000216);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000222, EnemyEtis, "EnemyEtis-10000222");
				break;
			}
			case 21205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000217);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000223, EnemyEtis, "EnemyEtis-10000223");
				break;
			}
			case 21305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000218);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000224, EnemyEtis, "EnemyEtis-10000224");
				break;
			}
			case 21405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000219);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000220);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000221);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000222);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000223);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 21905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000224);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 22000: {
				appendChild(receiveScene(10000003));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 229-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STGDBGClimax_終焉の処理
                _TRACE_("STGDBGClimax_終焉のStageDebugPartController::PROG_FAINALきた");
            }

            if (pProg->hasArrivedAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void StageDebugPartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGEDEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //進捗をStageDebugPartController::PROG_FAINALに切り替える
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
