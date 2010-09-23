#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,30000};
	_paFrame_NextEvent = new frame[3];
	for (int i = 0; i < 3; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(21307100, FormationIris002, "F002_Iris_1");
	orderActorToFactory(21317100, FormationIris001, "F001_Iris_2");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_21297100");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(21307100)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(21317100)), 400);
				}
				break;
			case 30000:
				throwUpEvent(STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 3-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
