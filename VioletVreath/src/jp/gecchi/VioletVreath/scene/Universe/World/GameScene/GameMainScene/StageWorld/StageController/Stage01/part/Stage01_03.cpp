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
	frame f[] = {8000};
	_paFrame_NextEvent = new frame[1];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 1;
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
			case 8000: {
				throwEventToUpperTree(EVENT_STG01_03_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 1-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end
}

Stage01_03::~Stage01_03() {

}
