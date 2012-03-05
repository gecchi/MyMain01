#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,8000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderActorToFactory(50000000, FormationIris002, "F002_Iris_1");
	orderActorToFactory(50000001, FormationIris002, "F002_Iris_2");
	
	orderActorToFactory(50000003, FormationIris002, "F002_Iris_3");
	orderActorToFactory(50000004, FormationIris001, "F001_Iris_4");
	orderActorToFactory(50000005, FormationIris001, "F001_Iris_5");
	orderActorToFactory(50000006, FormationIris002, "F002_Iris_6");
	orderActorToFactory(50000007, FormationIris001, "F001_Iris_7");
	orderActorToFactory(50000008, FormationIris002, "F002_Iris_8");
    // gen01 end
}

void Stage01_03::initialize() {

}

void Stage01_03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				FormationIris002* pF2 = (FormationIris002*)obtainActorFromFactory(50000001);
				getDirector()->addSubGroup(pF2);
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_50000002");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000003)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000004)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000005)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000006)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000007)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000008)), 400);
				}
				break;
			}
			case 200: {
				FormationIris002* pF1 = (FormationIris002*)obtainActorFromFactory(50000000);
				getDirector()->addSubGroup(pF1);
				break;
			}
			case 8000: {
				throwEventToUpperTree(EVENT_STG01_03_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

Stage01_03::~Stage01_03() {

}
