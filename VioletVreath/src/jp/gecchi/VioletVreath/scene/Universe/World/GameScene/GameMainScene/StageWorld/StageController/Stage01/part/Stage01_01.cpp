#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_01";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {100,1000,10000};
	_paFrame_NextEvent = new frame[3];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 3;
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 100: {
				orderActorToFactory(30000000, VarietySylvia002, "VarietySylvia002_1");
				break;
			}
			case 1000: {
				VarietySylvia002* pSylvia = (VarietySylvia002*)obtainActorFromFactory(30000000);
				getDirector()->addSubGroup(pSylvia);
				break;
			}
			case 10000: {
				throwEventToUpperTree(EVENT_STG01_01_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 3-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

}

Stage01_01::~Stage01_01() {

}
