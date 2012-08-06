#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,40,100,160,220,280,340,400,460,500,520,580,640,700,760,820,880,940,1000,1060,1120,1180,1240,1300,1360,1420,1480,1540,1600,1660,1720,1780,1840,1900,1960,30000};
	_paFrame_NextEvent = new frame[36];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 36;
	orderActorToFactory(30000000, FormationHebe001, "F001a_Eunomia_1");
	orderActorToFactory(30000001, EnemyAdrastea, "Metis_2");
	orderActorToFactory(30000002, EnemyAdrastea, "Metis_3");
	orderActorToFactory(30000003, EnemyAdrastea, "Metis_4");
	orderActorToFactory(30000004, EnemyAdrastea, "Metis_5");
	orderActorToFactory(30000005, EnemyAdrastea, "Metis_6");
	orderActorToFactory(30000006, EnemyAdrastea, "Metis_7");
	orderActorToFactory(30000007, EnemyAdrastea, "Metis_8");
	orderActorToFactory(30000008, EnemyAdrastea, "Metis_9");
	orderActorToFactory(30000009, EnemyAdrastea, "Metis_10");
	orderActorToFactory(30000010, EnemyAdrastea, "Metis_11");
	orderActorToFactory(30000011, EnemyAdrastea, "Metis_12");
	orderActorToFactory(30000012, EnemyAdrastea, "Metis_13");
	orderActorToFactory(30000013, EnemyAdrastea, "Metis_14");
	orderActorToFactory(30000014, EnemyAdrastea, "Metis_15");
	orderActorToFactory(30000015, EnemyAdrastea, "Metis_16");
	orderActorToFactory(30000016, EnemyAdrastea, "Metis_17");
	orderActorToFactory(30000017, EnemyAdrastea, "Metis_18");
	orderActorToFactory(30000018, EnemyAdrastea, "Metis_19");
	orderActorToFactory(30000019, EnemyAdrastea, "Metis_20");
	orderActorToFactory(30000020, EnemyAdrastea, "Metis_21");
	orderActorToFactory(30000021, EnemyAdrastea, "Metis_22");
	orderActorToFactory(30000022, EnemyAdrastea, "Metis_23");
	orderActorToFactory(30000023, EnemyAdrastea, "Metis_24");
	orderActorToFactory(30000024, EnemyAdrastea, "Metis_25");
	orderActorToFactory(30000025, EnemyAdrastea, "Metis_26");
	orderActorToFactory(30000026, EnemyAdrastea, "Metis_27");
	orderActorToFactory(30000027, EnemyAdrastea, "Metis_28");
	orderActorToFactory(30000028, EnemyAdrastea, "Metis_29");
	orderActorToFactory(30000029, EnemyAdrastea, "Metis_30");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 40: {
				orderActorToFactory(30000030, EnemyAdrastea, "Metis_31");
				break;
			}
			case 100: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000001);
				getDirector()->addSubGroup(p);
				orderActorToFactory(30000031, EnemyAdrastea, "Metis_32");
				break;
			}
			case 160: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000002);
				getDirector()->addSubGroup(p);
				orderActorToFactory(30000032, EnemyAdrastea, "Metis_33");
				break;
			}
			case 220: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000003);
				getDirector()->addSubGroup(p);
				break;
			}
			case 280: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000004);
				getDirector()->addSubGroup(p);
				break;
			}
			case 340: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000005);
				getDirector()->addSubGroup(p);
				break;
			}
			case 400: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000006);
				getDirector()->addSubGroup(p);
				break;
			}
			case 460: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000007);
				getDirector()->addSubGroup(p);
				break;
			}
			case 500: {
				FormationHebe001* pF = (FormationHebe001*)obtainActorFromFactory(30000000);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 520: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000008);
				getDirector()->addSubGroup(p);
				break;
			}
			case 580: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000009);
				getDirector()->addSubGroup(p);
				break;
			}
			case 640: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000010);
				getDirector()->addSubGroup(p);
				break;
			}
			case 700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000011);
				getDirector()->addSubGroup(p);
				break;
			}
			case 760: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000012);
				getDirector()->addSubGroup(p);
				break;
			}
			case 820: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000013);
				getDirector()->addSubGroup(p);
				break;
			}
			case 880: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000014);
				getDirector()->addSubGroup(p);
				break;
			}
			case 940: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000015);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1000: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000016);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1060: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000017);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1120: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000018);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1180: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000019);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1240: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000020);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1300: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000021);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1360: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000022);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1420: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000023);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1480: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000024);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1540: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000025);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000026);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1660: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000027);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1720: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000028);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1780: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000029);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1840: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000030);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1900: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000031);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1960: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(30000032);
				getDirector()->addSubGroup(p);
				break;
			}
			case 30000: {
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 36-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01_01::~Stage01_01() {

}
