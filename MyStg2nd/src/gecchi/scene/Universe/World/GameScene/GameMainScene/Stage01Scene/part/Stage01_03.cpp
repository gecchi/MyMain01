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
	frame f[] = {1,100,2500};
	_paFrame_NextEvent = new frame[3];
	for (int i = 0; i < 3; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(41087100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(41097100, FormationPallas001b, "F001b_Pallas_2");
	orderActorToFactory(41107100, FormationPallas001c, "F001c_Pallas_3");
	orderActorToFactory(41117100, FormationPallas001d, "F001d_Pallas_4");
	orderActorToFactory(41127100, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(41137100, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(41147100, FormationPallas001b, "F001b_Pallas_7");
	orderActorToFactory(41157100, FormationPallas001c, "F001c_Pallas_8");
	orderActorToFactory(41167100, FormationPallas001a, "F001a_Pallas_9");
	orderActorToFactory(41177100, FormationPallas001d, "F001d_Pallas_10");
	orderActorToFactory(41187100, FormationPallas001b, "F001b_Pallas_11");
	orderActorToFactory(41197100, FormationPallas001c, "F001c_Pallas_12");
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
				ActorTableScene* ta = NEW ActorTableScene("TableScene_41076100");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41087100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41097100)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41107100)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41117100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41127100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41137100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41147100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41157100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41167100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41177100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41187100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41197100)), 400);
				}
				break;
			case 2500:
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
