#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,300,400,1300,1400,2300,2400,3300,3400,4300,4400,5300,5400,6300,6400,7300,7400,8300,8400,9300,9400,10300,10400,11300,11400,12300,12400,13300,13400,14300,14400,15300,15400,16300,16400,17300,17400,18300,18400,19300,19400,20300,20400,21300,21400,22300,22400,23300,23400,24300,24400,25300,25400,26300,26400,27300,27400,28300,28400,29300,29400,30300,30400,31300,31400,32300,32400,33300,33400,34300,34400,35300,35400,36300,36400,37300,37400,38300,38400,39300,39400,40300,40400,41300,41400,42300,42400,43300,43400,44300,44400,45300,45400,46300,46400,47300,47400,48300,48400,49300};
	_paFrame_NextEvent = new frame[100];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 100;
	orderActorToFactory(10000000, EnemyErmione, "EnemyErmione-1");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 400: {
				orderActorToFactory(10000001, EnemyErmione, "EnemyErmione-2");
				break;
			}
			case 1300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 1400: {
				orderActorToFactory(10000002, EnemyErmione, "EnemyErmione-3");
				break;
			}
			case 2300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 2400: {
				orderActorToFactory(10000003, EnemyErmione, "EnemyErmione-4");
				break;
			}
			case 3300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 3400: {
				orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-5");
				break;
			}
			case 4300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 4400: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-6");
				break;
			}
			case 5300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 5400: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-7");
				break;
			}
			case 6300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 6400: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-8");
				break;
			}
			case 7300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 7400: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-9");
				break;
			}
			case 8300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 8400: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-10");
				break;
			}
			case 9300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 9400: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-11");
				break;
			}
			case 10300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 10400: {
				orderActorToFactory(10000011, EnemyErmione, "EnemyErmione-12");
				break;
			}
			case 11300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 11400: {
				orderActorToFactory(10000012, EnemyErmione, "EnemyErmione-13");
				break;
			}
			case 12300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 12400: {
				orderActorToFactory(10000013, EnemyErmione, "EnemyErmione-14");
				break;
			}
			case 13300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 13400: {
				orderActorToFactory(10000014, EnemyErmione, "EnemyErmione-15");
				break;
			}
			case 14300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 14400: {
				orderActorToFactory(10000015, EnemyErmione, "EnemyErmione-16");
				break;
			}
			case 15300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 15400: {
				orderActorToFactory(10000016, EnemyErmione, "EnemyErmione-17");
				break;
			}
			case 16300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 16400: {
				orderActorToFactory(10000017, EnemyErmione, "EnemyErmione-18");
				break;
			}
			case 17300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 17400: {
				orderActorToFactory(10000018, EnemyErmione, "EnemyErmione-19");
				break;
			}
			case 18300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 18400: {
				orderActorToFactory(10000019, EnemyErmione, "EnemyErmione-20");
				break;
			}
			case 19300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 19400: {
				orderActorToFactory(10000020, EnemyErmione, "EnemyErmione-21");
				break;
			}
			case 20300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 20400: {
				orderActorToFactory(10000021, EnemyErmione, "EnemyErmione-22");
				break;
			}
			case 21300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 21400: {
				orderActorToFactory(10000022, EnemyErmione, "EnemyErmione-23");
				break;
			}
			case 22300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 22400: {
				orderActorToFactory(10000023, EnemyErmione, "EnemyErmione-24");
				break;
			}
			case 23300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 23400: {
				orderActorToFactory(10000024, EnemyErmione, "EnemyErmione-25");
				break;
			}
			case 24300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 24400: {
				orderActorToFactory(10000025, EnemyErmione, "EnemyErmione-26");
				break;
			}
			case 25300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 25400: {
				orderActorToFactory(10000026, EnemyErmione, "EnemyErmione-27");
				break;
			}
			case 26300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 26400: {
				orderActorToFactory(10000027, EnemyErmione, "EnemyErmione-28");
				break;
			}
			case 27300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 27400: {
				orderActorToFactory(10000028, EnemyErmione, "EnemyErmione-29");
				break;
			}
			case 28300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 28400: {
				orderActorToFactory(10000029, EnemyErmione, "EnemyErmione-30");
				break;
			}
			case 29300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 29400: {
				orderActorToFactory(10000030, EnemyErmione, "EnemyErmione-31");
				break;
			}
			case 30300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 30400: {
				orderActorToFactory(10000031, EnemyErmione, "EnemyErmione-32");
				break;
			}
			case 31300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 31400: {
				orderActorToFactory(10000032, EnemyErmione, "EnemyErmione-33");
				break;
			}
			case 32300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 32400: {
				orderActorToFactory(10000033, EnemyErmione, "EnemyErmione-34");
				break;
			}
			case 33300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 33400: {
				orderActorToFactory(10000034, EnemyErmione, "EnemyErmione-35");
				break;
			}
			case 34300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 34400: {
				orderActorToFactory(10000035, EnemyErmione, "EnemyErmione-36");
				break;
			}
			case 35300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 35400: {
				orderActorToFactory(10000036, EnemyErmione, "EnemyErmione-37");
				break;
			}
			case 36300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 36400: {
				orderActorToFactory(10000037, EnemyErmione, "EnemyErmione-38");
				break;
			}
			case 37300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 37400: {
				orderActorToFactory(10000038, EnemyErmione, "EnemyErmione-39");
				break;
			}
			case 38300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 38400: {
				orderActorToFactory(10000039, EnemyErmione, "EnemyErmione-40");
				break;
			}
			case 39300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 39400: {
				orderActorToFactory(10000040, EnemyErmione, "EnemyErmione-41");
				break;
			}
			case 40300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 40400: {
				orderActorToFactory(10000041, EnemyErmione, "EnemyErmione-42");
				break;
			}
			case 41300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 41400: {
				orderActorToFactory(10000042, EnemyErmione, "EnemyErmione-43");
				break;
			}
			case 42300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 42400: {
				orderActorToFactory(10000043, EnemyErmione, "EnemyErmione-44");
				break;
			}
			case 43300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 43400: {
				orderActorToFactory(10000044, EnemyErmione, "EnemyErmione-45");
				break;
			}
			case 44300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 44400: {
				orderActorToFactory(10000045, EnemyErmione, "EnemyErmione-46");
				break;
			}
			case 45300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 45400: {
				orderActorToFactory(10000046, EnemyErmione, "EnemyErmione-47");
				break;
			}
			case 46300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 46400: {
				orderActorToFactory(10000047, EnemyErmione, "EnemyErmione-48");
				break;
			}
			case 47300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 47400: {
				orderActorToFactory(10000048, EnemyErmione, "EnemyErmione-49");
				break;
			}
			case 48300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			case 48400: {
				orderActorToFactory(10000049, EnemyErmione, "EnemyErmione-50");
				break;
			}
			case 49300: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(1000000,4000000);
				p->_y = RND(-6000000,6000000);
				p->_z = RND(-6000000,6000000);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 100-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
