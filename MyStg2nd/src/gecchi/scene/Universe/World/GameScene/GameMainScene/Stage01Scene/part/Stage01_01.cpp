#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100};
	_paFrame_NextEvent = new frame[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(21046100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(21056100, FormationPallas001b, "F001b_Pallas_2");
	orderActorToFactory(21066100, FormationPallas001c, "F001c_Pallas_3");
	orderActorToFactory(21076100, FormationPallas001d, "F001d_Pallas_4");
	orderActorToFactory(21086100, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(21096100, FormationPallas001b, "F001b_Pallas_6");
	orderActorToFactory(21106100, FormationPallas001c, "F001c_Pallas_7");
	orderActorToFactory(21116100, FormationPallas001d, "F001d_Pallas_8");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableSecan_9");
				ta->setMaxPerformFrame(getActivePartFrame()+400*4);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21046100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21056100)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21066100)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21076100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21086100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21096100)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21106100)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21116100)), 400);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 2-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
