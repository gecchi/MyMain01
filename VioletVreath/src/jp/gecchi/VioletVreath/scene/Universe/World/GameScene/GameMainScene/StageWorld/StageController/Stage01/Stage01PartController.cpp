#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
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
	frame f[] = {1,40,100,160,220,280,340,400,460,520,580,640,700,760,820,880,940,1000,1060,1120,1180,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,2020,2080,2140,2200,2260,2320,2380,2440,2500,2560,2620,2680,2740,2800,2860,2920,2980};
	_paFrame_NextEvent = new frame[51];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 51;
	orderActorToFactory(10000000, FormationOebius002, "FormationOebius002-1");
	orderActorToFactory(10000001, FormationOebius002, "FormationOebius002-2");
	orderActorToFactory(10000002, FormationOebius002, "FormationOebius002-3");
	orderActorToFactory(10000003, FormationOebius002, "FormationOebius002-4");
	orderActorToFactory(10000004, FormationOebius002, "FormationOebius002-5");
	orderActorToFactory(10000005, FormationOebius002, "FormationOebius002-6");
	orderActorToFactory(10000006, FormationOebius002, "FormationOebius002-7");
	orderActorToFactory(10000007, FormationOebius002, "FormationOebius002-8");
	orderActorToFactory(10000008, FormationOebius002, "FormationOebius002-9");
	orderActorToFactory(10000009, FormationOebius002, "FormationOebius002-10");
	orderActorToFactory(10000010, FormationOebius002, "FormationOebius002-11");
	orderActorToFactory(10000011, FormationOebius002, "FormationOebius002-12");
	orderActorToFactory(10000012, FormationOebius002, "FormationOebius002-13");
	orderActorToFactory(10000013, FormationOebius002, "FormationOebius002-14");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    getProgress()->reset(Stage01PartController::PROG_INIT);
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
				orderActorToFactory(10000014, FormationOebius002, "FormationOebius002-15");
				break;
			}
			case 100: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000015, FormationOebius002, "FormationOebius002-16");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 160: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000016, FormationOebius002, "FormationOebius002-17");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 220: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000017, FormationOebius002, "FormationOebius002-18");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 280: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000018, FormationOebius002, "FormationOebius002-19");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 340: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000019, FormationOebius002, "FormationOebius002-20");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 400: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000020, FormationOebius002, "FormationOebius002-21");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 460: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000021, FormationOebius002, "FormationOebius002-22");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 520: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000022, FormationOebius002, "FormationOebius002-23");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 580: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000023, FormationOebius002, "FormationOebius002-24");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 640: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000024, FormationOebius002, "FormationOebius002-25");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 700: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000025, FormationOebius002, "FormationOebius002-26");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 760: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000026, FormationOebius002, "FormationOebius002-27");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 820: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000027, FormationOebius002, "FormationOebius002-28");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 880: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000028, FormationOebius002, "FormationOebius002-29");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 940: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000029, FormationOebius002, "FormationOebius002-30");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1000: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000030, FormationOebius002, "FormationOebius002-31");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1060: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000031, FormationOebius002, "FormationOebius002-32");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1120: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000032, FormationOebius002, "FormationOebius002-33");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1180: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000033, FormationOebius002, "FormationOebius002-34");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1240: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000034, FormationOebius002, "FormationOebius002-35");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1300: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000020);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000035, FormationOebius002, "FormationOebius002-36");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1360: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000021);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000036, FormationOebius002, "FormationOebius002-37");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1420: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000022);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000037, FormationOebius002, "FormationOebius002-38");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1480: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000023);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000038, FormationOebius002, "FormationOebius002-39");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1540: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000024);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000039, FormationOebius002, "FormationOebius002-40");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1600: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000025);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000040, FormationOebius002, "FormationOebius002-41");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1660: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000026);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000041, FormationOebius002, "FormationOebius002-42");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1720: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000027);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000042, FormationOebius002, "FormationOebius002-43");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1780: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000028);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000043, FormationOebius002, "FormationOebius002-44");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1840: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000029);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000044, FormationOebius002, "FormationOebius002-45");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1900: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000030);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000045, FormationOebius002, "FormationOebius002-46");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 1960: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000031);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000046, FormationOebius002, "FormationOebius002-47");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2020: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000032);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000047, FormationOebius002, "FormationOebius002-48");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2080: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000033);
				getSceneDirector()->addSubGroup(pF);
				orderActorToFactory(10000048, FormationOebius002, "FormationOebius002-49");
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2140: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000034);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2200: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000035);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2260: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000036);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2320: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000037);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2380: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000038);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2440: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000039);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2500: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000040);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2560: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000041);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2620: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000042);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2680: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000043);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2740: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000044);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2800: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000045);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2860: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000046);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2920: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000047);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 2980: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000048);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 51-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (pProg->getFrameInProgress() == 60) {
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
    SceneProgress* pProg = getProgress();
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
        pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
