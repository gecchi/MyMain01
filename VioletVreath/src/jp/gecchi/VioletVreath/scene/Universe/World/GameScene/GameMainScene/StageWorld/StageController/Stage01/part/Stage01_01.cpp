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
	frame f[] = {1,500,1600,2100,2500,3000,10000};
	_paFrame_NextEvent = new frame[7];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 7;
	
	orderActorToFactory(30000001, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(30000002, FormationPallas001b, "F001b_Pallas_2");
	orderActorToFactory(30000003, FormationPallas001c, "F001c_Pallas_3");
	orderActorToFactory(30000004, FormationPallas001d, "F001d_Pallas_4");
	orderActorToFactory(30000005, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(30000006, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(30000007, FormationPallas001b, "F001b_Pallas_7");
	orderActorToFactory(30000008, FormationPallas001c, "F001c_Pallas_8");
	orderActorToFactory(30000009, FormationPallas001a, "F001a_Pallas_9");
	orderActorToFactory(30000010, FormationPallas001d, "F001d_Pallas_10");
	orderActorToFactory(30000011, FormationPallas001b, "F001b_Pallas_11");
	orderActorToFactory(30000012, FormationPallas001c, "F001c_Pallas_12");
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
			case 500: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_30000000");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000001)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000002)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000003)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000004)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000005)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000006)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000007)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000008)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(30000009)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(30000010)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(30000011)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(30000012)), 400);
				}
				break;
			}
			case 1600: {
				orderActorToFactory(30000013, FormationEunomia001a, "F001a_Eunomia_13");
				break;
			}
			case 2100: {
				orderActorToFactory(30000014, FormationEunomia001b, "F001b_Eunomia_14");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(30000013);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 3000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(30000014);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 10000: {
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 7-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01_01::~Stage01_01() {

}
