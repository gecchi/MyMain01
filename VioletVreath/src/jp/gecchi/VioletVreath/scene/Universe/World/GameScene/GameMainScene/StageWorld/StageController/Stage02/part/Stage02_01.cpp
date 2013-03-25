#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02_01::Stage02_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,1000};
	_paFrame_NextEvent = new frame[3];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 3;
	orderActorToFactory(70000000, FormationJuno001, "FormationJuno001-1");
	
	orderActorToFactory(70000002, FormationIris001, "FormationIris001-2");
	orderActorToFactory(70000003, FormationIris002, "FormationIris002-3");
	orderActorToFactory(70000004, FormationIris001, "FormationIris001-4");
	orderActorToFactory(70000005, FormationIris002, "FormationIris002-5");
	orderActorToFactory(70000006, FormationIris001, "FormationIris001-6");
	orderActorToFactory(70000007, FormationIris002, "FormationIris002-7");
    // gen01 end
}

void Stage02_01::initialize() {

}

void Stage02_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(70000000);
				getSceneDirector()->addSubGroup(pF);
				break;
			}
			case 1000: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTableScene-8");
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
			default :
				break;
		}
		_cnt_event = (_cnt_event < 3-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActivePartFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventUpperTree(EVENT_STG02_01_WAS_BROKEN);
    }

}

Stage02_01::~Stage02_01() {

}
