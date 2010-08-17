#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_03::Stage01_03(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,101,102,103};
	_paFrame_NextEvent = new frame[5];
	for (int i = 0; i < 5; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(41026100, VarietyTorus004, "VarietyTorus004_1");
	orderActorToFactory(41026101, VarietyTorus004, "VarietyTorus004_2");
	orderActorToFactory(41026102, VarietyTorus004, "VarietyTorus004_3");
	orderActorToFactory(41026103, VarietyTorus004, "VarietyTorus004_4");
    // gen01 end
}

void Stage01_03::initialize() {

}

void Stage01_03::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				getLordActor()->addSubGroup(obtainActorFromFactory(41026100));
				break;
			case 101:
				getLordActor()->addSubGroup(obtainActorFromFactory(41026101));
				break;
			case 102:
				getLordActor()->addSubGroup(obtainActorFromFactory(41026102));
				break;
			case 103:
				getLordActor()->addSubGroup(obtainActorFromFactory(41026103));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 5-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_03::processFinal() {
}

Stage01_03::~Stage01_03() {

}
