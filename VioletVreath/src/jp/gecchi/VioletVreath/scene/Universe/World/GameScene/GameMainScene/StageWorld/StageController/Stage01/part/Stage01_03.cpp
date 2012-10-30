#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_03";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {700,1200,2500,3000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
    // gen01 end
}

void Stage01_03::initialize() {

}

void Stage01_03::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 700: {
				orderActorToFactory(50000000, FormationEunomia001a, "F001a_Eunomia_1");
				break;
			}
			case 1200: {
				orderActorToFactory(50000001, FormationEunomia001b, "F001b_Eunomia_2");
				break;
			}
			case 2500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(50000000);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 3000: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(50000001);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    //シーン終了のイベントを通知
    if (getActivePartFrame() == _paFrame_NextEvent[_event_num-1] + 60*60) {
        throwEventToUpperTree(EVENT_STG01_03_WAS_BROKEN, this);
    }
}

Stage01_03::~Stage01_03() {

}
