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
	frame f[] = {1,100,200,4000};
	_paFrame_NextEvent = new frame[4];
	for (int i = 0; i < 4; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(51027200, FormationIris002, "F002_Iris_1");
	orderActorToFactory(51037100, FormationIris002, "F002_Iris_2");
	
	orderActorToFactory(51087100, FormationIris002, "F002_Iris_3");
	orderActorToFactory(51097100, FormationIris001, "F001_Iris_4");
	orderActorToFactory(51107100, FormationIris001, "F001_Iris_5");
	orderActorToFactory(51117100, FormationIris002, "F002_Iris_6");
	orderActorToFactory(51127100, FormationIris001, "F001_Iris_7");
	orderActorToFactory(51137100, FormationIris002, "F002_Iris_8");
	orderActorToFactory(51207100, VarietyTorus001, "VarietyTorus001_9");
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
			case 1:
				break;
			case 100:
				{
				FormationIris002* pActor = (FormationIris002*)obtainActorFromFactory(51037100);
				getLordActor()->addSubGroup(pActor);
				}
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_51077100");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(51087100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(51097100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(51107100)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(51117100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(51127100)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(51137100)), 400);
				}
				{
				VarietyTorus001* pActor = (VarietyTorus001*)obtainActorFromFactory(51207100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 200:
				{
				FormationIris002* pActor = (FormationIris002*)obtainActorFromFactory(51027200);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 4000:
				throwEventToUpperTree(EVENT_STG01_03_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_03::processFinal() {
}

Stage01_03::~Stage01_03() {

}
