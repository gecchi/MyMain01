#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage02_01::Stage02_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,1000,3000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderActorToFactory(70000000, FormationJuno001, "F002_Juno_1");
	
	orderActorToFactory(70000002, FormationIris001, "F001_Iris_2");
	orderActorToFactory(70000003, FormationIris002, "F002_Iris_3");
	orderActorToFactory(70000004, FormationIris001, "F001_Iris_4");
	orderActorToFactory(70000005, FormationIris002, "F002_Iris_5");
	orderActorToFactory(70000006, FormationIris001, "F001_Iris_6");
	orderActorToFactory(70000007, FormationIris002, "F002_Iris_7");
    // gen01 end
}

void Stage02_01::initialize() {

}

void Stage02_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(70000000);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 1000: {
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_8");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(70000002)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(70000003)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(70000004)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(70000005)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(70000006)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(70000007)), 400);
				}
				break;
			}
			case 3000: {
				throwEventToUpperTree(EVENT_STG02_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage02_01::processFinal() {
}

Stage02_01::~Stage02_01() {

}
