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
	frame f[] = {1,40,100,160,220,280,300,340,400,460,500,520,580,600,640,700,760,820,880,940,1000,1060,1120,1180,1200,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,2020,2080,2140,2200,2260,2300,2320,2380,2440,2500,2560,2620,2680,2740,2800,2860,2920,2980,3200,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,6300,7200,8300,9100,9200,10000,10300,11200,12300,13200,14300,15200,16300,17200,18300,19100,19200,20000,20300,21200,22300,23200,24300,25200,26300,27200,28300,29100,29200,30000};
	_paFrame_NextEvent = new frame[105];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 105;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000028, EnemyDuna, "EnemyDuna-2");
	orderActorToFactory(10000029, EnemyDuna, "EnemyDuna-3");
	orderActorToFactory(10000030, EnemyDuna, "EnemyDuna-4");
	orderActorToFactory(10000031, EnemyDuna, "EnemyDuna-5");
	orderActorToFactory(10000032, EnemyDuna, "EnemyDuna-6");
	orderActorToFactory(10000033, EnemyDuna, "EnemyDuna-7");
	orderActorToFactory(10000034, EnemyDuna, "EnemyDuna-8");
	orderActorToFactory(10000035, EnemyDuna, "EnemyDuna-9");
	orderActorToFactory(10000036, EnemyDuna, "EnemyDuna-10");
	orderActorToFactory(10000072, EnemyOzartia, "EnemyOzartia-11");
	orderActorToFactory(10000073, EnemyOzartia, "EnemyOzartia-12");
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
			case 40: {
				orderActorToFactory(10000037, EnemyDuna, "EnemyDuna-13");
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				orderActorToFactory(10000038, EnemyDuna, "EnemyDuna-14");
				break;
			}
			case 160: {
				orderActorToFactory(10000039, EnemyDuna, "EnemyDuna-15");
				break;
			}
			case 220: {
				orderActorToFactory(10000040, EnemyDuna, "EnemyDuna-16");
				break;
			}
			case 280: {
				orderActorToFactory(10000041, EnemyDuna, "EnemyDuna-17");
				break;
			}
			case 300: {
				orderActorToFactory(10000004, EnemyErmione, "EnemyErmione-18");
				break;
			}
			case 340: {
				orderActorToFactory(10000042, EnemyDuna, "EnemyDuna-19");
				break;
			}
			case 400: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000043, EnemyDuna, "EnemyDuna-20");
				break;
			}
			case 460: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000044, EnemyDuna, "EnemyDuna-21");
				break;
			}
			case 500: {
				EnemyOzartia* p = (EnemyOzartia*)obtainActorFromFactory(10000072);
				getSceneDirector()->addSubGroup(p);
				p->position(1000000,0,0);
				break;
			}
			case 520: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000045, EnemyDuna, "EnemyDuna-22");
				break;
			}
			case 580: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000046, EnemyDuna, "EnemyDuna-23");
				break;
			}
			case 600: {
				EnemyOzartia* p = (EnemyOzartia*)obtainActorFromFactory(10000073);
				getSceneDirector()->addSubGroup(p);
				p->position(1000000,0,0);
				break;
			}
			case 640: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000047, EnemyDuna, "EnemyDuna-24");
				break;
			}
			case 700: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000048, EnemyDuna, "EnemyDuna-25");
				break;
			}
			case 760: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000049, EnemyDuna, "EnemyDuna-26");
				break;
			}
			case 820: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000050, EnemyDuna, "EnemyDuna-27");
				break;
			}
			case 880: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000051, EnemyDuna, "EnemyDuna-28");
				break;
			}
			case 940: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000052, EnemyDuna, "EnemyDuna-29");
				break;
			}
			case 1000: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000053, EnemyDuna, "EnemyDuna-30");
				break;
			}
			case 1060: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000054, EnemyDuna, "EnemyDuna-31");
				break;
			}
			case 1120: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000055, EnemyDuna, "EnemyDuna-32");
				break;
			}
			case 1180: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000056, EnemyDuna, "EnemyDuna-33");
				break;
			}
			case 1200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 1240: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000057, EnemyDuna, "EnemyDuna-34");
				break;
			}
			case 1300: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000058, EnemyDuna, "EnemyDuna-35");
				break;
			}
			case 1360: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000059, EnemyDuna, "EnemyDuna-36");
				break;
			}
			case 1420: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000060, EnemyDuna, "EnemyDuna-37");
				break;
			}
			case 1480: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000061, EnemyDuna, "EnemyDuna-38");
				break;
			}
			case 1540: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000062, EnemyDuna, "EnemyDuna-39");
				break;
			}
			case 1600: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000063, EnemyDuna, "EnemyDuna-40");
				break;
			}
			case 1660: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000064, EnemyDuna, "EnemyDuna-41");
				break;
			}
			case 1720: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000065, EnemyDuna, "EnemyDuna-42");
				break;
			}
			case 1780: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000066, EnemyDuna, "EnemyDuna-43");
				break;
			}
			case 1840: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000067, EnemyDuna, "EnemyDuna-44");
				break;
			}
			case 1900: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000068, EnemyDuna, "EnemyDuna-45");
				break;
			}
			case 1960: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000069, EnemyDuna, "EnemyDuna-46");
				break;
			}
			case 2020: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000070, EnemyDuna, "EnemyDuna-47");
				break;
			}
			case 2080: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000071, EnemyDuna, "EnemyDuna-48");
				break;
			}
			case 2140: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2200: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2260: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2300: {
				orderActorToFactory(10000005, EnemyErmione, "EnemyErmione-49");
				break;
			}
			case 2320: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2380: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2440: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000062);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2500: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000063);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2560: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000064);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2620: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000065);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2680: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000066);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2740: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000067);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2800: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000068);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2860: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000069);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2920: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000070);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2980: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000071);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 3200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 4100: {
				orderActorToFactory(10000019, FormationDelheid001, "FormationDelheid001-50");
				break;
			}
			case 4200: {
				orderActorToFactory(10000020, FormationDelheid001, "FormationDelheid001-51");
				break;
			}
			case 4300: {
				orderActorToFactory(10000006, EnemyErmione, "EnemyErmione-52");
				orderActorToFactory(10000021, FormationDelheid001, "FormationDelheid001-53");
				break;
			}
			case 4400: {
				orderActorToFactory(10000022, FormationDelheid001, "FormationDelheid001-54");
				break;
			}
			case 4500: {
				orderActorToFactory(10000023, FormationDelheid001, "FormationDelheid001-55");
				break;
			}
			case 4600: {
				orderActorToFactory(10000024, FormationDelheid001, "FormationDelheid001-56");
				break;
			}
			case 4700: {
				orderActorToFactory(10000025, FormationDelheid001, "FormationDelheid001-57");
				break;
			}
			case 4800: {
				orderActorToFactory(10000026, FormationDelheid001, "FormationDelheid001-58");
				break;
			}
			case 4900: {
				orderActorToFactory(10000027, FormationDelheid001, "FormationDelheid001-59");
				break;
			}
			case 5000: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 6300: {
				orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-60");
				break;
			}
			case 7200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 8300: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-61");
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-62");
				break;
			}
			case 9200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 10300: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-63");
				break;
			}
			case 11200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 12300: {
				orderActorToFactory(10000010, EnemyErmione, "EnemyErmione-64");
				break;
			}
			case 13200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 14300: {
				orderActorToFactory(10000011, EnemyErmione, "EnemyErmione-65");
				break;
			}
			case 15200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 16300: {
				orderActorToFactory(10000012, EnemyErmione, "EnemyErmione-66");
				break;
			}
			case 17200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 18300: {
				orderActorToFactory(10000013, EnemyErmione, "EnemyErmione-67");
				break;
			}
			case 19100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-68");
				break;
			}
			case 19200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 20000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 20300: {
				orderActorToFactory(10000014, EnemyErmione, "EnemyErmione-69");
				break;
			}
			case 21200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 22300: {
				orderActorToFactory(10000015, EnemyErmione, "EnemyErmione-70");
				break;
			}
			case 23200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 24300: {
				orderActorToFactory(10000016, EnemyErmione, "EnemyErmione-71");
				break;
			}
			case 25200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 26300: {
				orderActorToFactory(10000017, EnemyErmione, "EnemyErmione-72");
				break;
			}
			case 27200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 28300: {
				orderActorToFactory(10000018, EnemyErmione, "EnemyErmione-73");
				break;
			}
			case 29100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-74");
				break;
			}
			case 29200: {
				EnemyErmione* p = (EnemyErmione*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(p);
				p->_x = RND(000000,1000000);
				p->_y = RND(-600000,600000);
				p->_z = RND(-600000,600000);
				break;
			}
			case 30000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 105-1 ? _cnt_event+1 : _cnt_event);
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
