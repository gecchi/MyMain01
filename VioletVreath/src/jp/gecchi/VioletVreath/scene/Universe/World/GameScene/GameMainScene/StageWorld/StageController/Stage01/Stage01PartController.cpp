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
	frame f[] = {1,40,100,120,160,220,280,340,400,460,500,520,580,640,700,760,780,820,880,940,1000,1020,1060,1120,1180,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,2020,2080,2140,2200,2260,2320,2380,2440,2500,2560,2620,2680,2740,2800,2860,2920,2980,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,9100,10000,14100,15000};
	_paFrame_NextEvent = new frame[77];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 77;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01-1");
	orderActorToFactory(10000004, FormationAppho001a, "FormationAppho001a-2");
	orderActorToFactory(10000015, FormationOrtuna001b, "FormationOrtuna001b-3");
	orderActorToFactory(10000016, EnemyGlaja, "EnemyGlaja-4");
	orderActorToFactory(10000017, EnemyGlaja, "EnemyGlaja-5");
	orderActorToFactory(10000018, EnemyDuna, "EnemyDuna-6");
	orderActorToFactory(10000019, EnemyDuna, "EnemyDuna-7");
	orderActorToFactory(10000020, EnemyDuna, "EnemyDuna-8");
	orderActorToFactory(10000021, EnemyDuna, "EnemyDuna-9");
	orderActorToFactory(10000022, EnemyDuna, "EnemyDuna-10");
	orderActorToFactory(10000023, EnemyDuna, "EnemyDuna-11");
	orderActorToFactory(10000024, EnemyDuna, "EnemyDuna-12");
	orderActorToFactory(10000025, EnemyDuna, "EnemyDuna-13");
	orderActorToFactory(10000026, EnemyDuna, "EnemyDuna-14");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
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
				orderActorToFactory(10000027, EnemyDuna, "EnemyDuna-15");
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				orderActorToFactory(10000028, EnemyDuna, "EnemyDuna-16");
				break;
			}
			case 120: {
				orderActorToFactory(10000005, FormationAppho001b, "FormationAppho001b-17");
				break;
			}
			case 160: {
				orderActorToFactory(10000029, EnemyDuna, "EnemyDuna-18");
				break;
			}
			case 220: {
				orderActorToFactory(10000030, EnemyDuna, "EnemyDuna-19");
				break;
			}
			case 280: {
				orderActorToFactory(10000031, EnemyDuna, "EnemyDuna-20");
				break;
			}
			case 340: {
				orderActorToFactory(10000032, EnemyDuna, "EnemyDuna-21");
				break;
			}
			case 400: {
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000033, EnemyDuna, "EnemyDuna-22");
				break;
			}
			case 460: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000034, EnemyDuna, "EnemyDuna-23");
				break;
			}
			case 500: {
				FormationOrtuna001b* pF1 = (FormationOrtuna001b*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pF1);
				EnemyGlaja* p = (EnemyGlaja*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(p);
				p->position(100000,0,0);
				break;
			}
			case 520: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000035, EnemyDuna, "EnemyDuna-24");
				break;
			}
			case 580: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000036, EnemyDuna, "EnemyDuna-25");
				break;
			}
			case 640: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000037, EnemyDuna, "EnemyDuna-26");
				break;
			}
			case 700: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000038, EnemyDuna, "EnemyDuna-27");
				break;
			}
			case 760: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000039, EnemyDuna, "EnemyDuna-28");
				break;
			}
			case 780: {
				FormationAppho001a* pFSap = (FormationAppho001a*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 820: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000040, EnemyDuna, "EnemyDuna-29");
				break;
			}
			case 880: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000041, EnemyDuna, "EnemyDuna-30");
				break;
			}
			case 940: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000042, EnemyDuna, "EnemyDuna-31");
				break;
			}
			case 1000: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000043, EnemyDuna, "EnemyDuna-32");
				break;
			}
			case 1020: {
				FormationAppho001b* pFSap = (FormationAppho001b*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1060: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000044, EnemyDuna, "EnemyDuna-33");
				break;
			}
			case 1120: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000045, EnemyDuna, "EnemyDuna-34");
				break;
			}
			case 1180: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000046, EnemyDuna, "EnemyDuna-35");
				break;
			}
			case 1240: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000047, EnemyDuna, "EnemyDuna-36");
				break;
			}
			case 1300: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000048, EnemyDuna, "EnemyDuna-37");
				break;
			}
			case 1360: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000049, EnemyDuna, "EnemyDuna-38");
				break;
			}
			case 1420: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000050, EnemyDuna, "EnemyDuna-39");
				break;
			}
			case 1480: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000051, EnemyDuna, "EnemyDuna-40");
				break;
			}
			case 1540: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000052, EnemyDuna, "EnemyDuna-41");
				break;
			}
			case 1600: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000053, EnemyDuna, "EnemyDuna-42");
				break;
			}
			case 1660: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000054, EnemyDuna, "EnemyDuna-43");
				break;
			}
			case 1720: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000055, EnemyDuna, "EnemyDuna-44");
				break;
			}
			case 1780: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000056, EnemyDuna, "EnemyDuna-45");
				break;
			}
			case 1840: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000057, EnemyDuna, "EnemyDuna-46");
				break;
			}
			case 1900: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000058, EnemyDuna, "EnemyDuna-47");
				break;
			}
			case 1960: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000059, EnemyDuna, "EnemyDuna-48");
				break;
			}
			case 2020: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000060, EnemyDuna, "EnemyDuna-49");
				break;
			}
			case 2080: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				orderActorToFactory(10000061, EnemyDuna, "EnemyDuna-50");
				break;
			}
			case 2140: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2200: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2260: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000049);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2320: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000050);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2380: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000051);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2440: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000052);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2500: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000053);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2560: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000054);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2620: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000055);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2680: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000056);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2740: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000057);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2800: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000058);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2860: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000059);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2920: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000060);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 2980: {
				EnemyDuna* pDuna = (EnemyDuna*)obtainActorFromFactory(10000061);
				getSceneDirector()->addSubGroup(pDuna);
				pDuna->position(2000000,RND(-800000,800000),RND(-800000,800000));
				break;
			}
			case 4100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-51");
				orderActorToFactory(10000006, FormationDelheid001, "FormationDelheid001-52");
				break;
			}
			case 4200: {
				orderActorToFactory(10000007, FormationDelheid001, "FormationDelheid001-53");
				break;
			}
			case 4300: {
				orderActorToFactory(10000008, FormationDelheid001, "FormationDelheid001-54");
				break;
			}
			case 4400: {
				orderActorToFactory(10000009, FormationDelheid001, "FormationDelheid001-55");
				break;
			}
			case 4500: {
				orderActorToFactory(10000010, FormationDelheid001, "FormationDelheid001-56");
				break;
			}
			case 4600: {
				orderActorToFactory(10000011, FormationDelheid001, "FormationDelheid001-57");
				break;
			}
			case 4700: {
				orderActorToFactory(10000012, FormationDelheid001, "FormationDelheid001-58");
				break;
			}
			case 4800: {
				orderActorToFactory(10000013, FormationDelheid001, "FormationDelheid001-59");
				break;
			}
			case 4900: {
				orderActorToFactory(10000014, FormationDelheid001, "FormationDelheid001-60");
				break;
			}
			case 5000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-400), PX_C(500), D_ANG(-40), D_ANG(0));
				break;
			}
			case 5100: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-300), PX_C(500), D_ANG(-30), D_ANG(0));
				break;
			}
			case 5200: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-200), PX_C(500), D_ANG(-20), D_ANG(0));
				break;
			}
			case 5300: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(-100), PX_C(500), D_ANG(-10), D_ANG(0));
				break;
			}
			case 5400: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C(  0), PX_C(500), D_ANG(0), D_ANG(0));
				break;
			}
			case 5500: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 100), PX_C(500), D_ANG(10), D_ANG(0));
				break;
			}
			case 5600: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 200), PX_C(500), D_ANG(20), D_ANG(0));
				break;
			}
			case 5700: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 300), PX_C(500), D_ANG(30), D_ANG(0));
				break;
			}
			case 5800: {
				FormationDelheid001* pF = (FormationDelheid001*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pF);
				pF->position(PX_C(-200), PX_C( 400), PX_C(500), D_ANG(40), D_ANG(0));
				break;
			}
			case 9100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-61");
				break;
			}
			case 10000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				break;
			}
			case 14100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-62");
				break;
			}
			case 15000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 77-1 ? _cnt_event+1 : _cnt_event);
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
