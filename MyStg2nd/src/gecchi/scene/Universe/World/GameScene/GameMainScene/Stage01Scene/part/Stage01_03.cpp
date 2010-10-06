#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,5500};
	_paFrame_NextEvent = new frame[3];
	for (int i = 0; i < 3; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(41037100, FormationIris002, "F002_Iris_1");
	
	orderActorToFactory(41087100, FormationIris002, "F002_Iris_2");
	orderActorToFactory(41097100, FormationIris001, "F001_Iris_3");
	orderActorToFactory(41107100, FormationIris001, "F001_Iris_4");
	orderActorToFactory(41117100, FormationIris002, "F002_Iris_5");
	orderActorToFactory(41127100, FormationIris001, "F001_Iris_6");
	orderActorToFactory(41137100, FormationIris002, "F002_Iris_7");
	orderActorToFactory(41207100, VarietyTorus001, "VarietyTorus001_8");
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
				FormationIris002* pActor = (FormationIris002*)obtainActorFromFactory(41037100);
				getLordActor()->addSubGroup(pActor);
				}
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_41077100");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(41087100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(41097100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(41107100)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(41117100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(41127100)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(41137100)), 400);
				}
				{
				VarietyTorus001* pActor = (VarietyTorus001*)obtainActorFromFactory(41207100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 5500:
				throwUpEvent(STG01_03_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 3-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_03::processFinal() {
}

Stage01_03::~Stage01_03() {

}
