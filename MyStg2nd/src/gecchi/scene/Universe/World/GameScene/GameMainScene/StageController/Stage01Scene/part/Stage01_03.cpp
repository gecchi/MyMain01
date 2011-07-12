#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,200,2200,4000,8000};
	_paFrame_NextEvent = new frame[6];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 6;
	orderActorToFactory(50000000, FormationIris002, "F002_Iris_1");
	orderActorToFactory(50000001, FormationIris002, "F002_Iris_2");
	
	orderActorToFactory(50000003, FormationIris002, "F002_Iris_3");
	orderActorToFactory(50000004, FormationIris001, "F001_Iris_4");
	orderActorToFactory(50000005, FormationIris001, "F001_Iris_5");
	orderActorToFactory(50000006, FormationIris002, "F002_Iris_6");
	orderActorToFactory(50000007, FormationIris001, "F001_Iris_7");
	orderActorToFactory(50000008, FormationIris002, "F002_Iris_8");
	orderActorToFactory(50000009, VarietyTorus001, "VarietyTorus001_9");
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
				getLordActor()->addSubGroup(pF2);
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_50000002");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000003)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000004)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000005)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000006)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(50000007)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(50000008)), 400);
				}
				VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(50000009);
				getLordActor()->addSubGroup(pTorus);
				break;
			}
			case 200: {
				FormationIris002* pF1 = (FormationIris002*)obtainActorFromFactory(50000000);
				getLordActor()->addSubGroup(pF1);
				break;
			}
			case 2200: {
				orderActorToFactory(50000010, VarietyTorus002, "VarietyTorus002_10");
				break;
			}
			case 4000: {
				VarietyTorus002* pTorus = (VarietyTorus002*)obtainActorFromFactory(50000010);
				getLordActor()->addSubGroup(pTorus);
				break;
			}
			case 8000: {
				throwEventToUpperTree(EVENT_STG01_03_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 6-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_03::processFinal() {
}

Stage01_03::~Stage01_03() {

}
