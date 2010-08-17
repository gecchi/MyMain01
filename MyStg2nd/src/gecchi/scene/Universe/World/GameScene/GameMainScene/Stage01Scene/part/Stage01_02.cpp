#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,500};
	_paFrame_NextEvent = new frame[3];
	for (int i = 0; i < 3; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(31027100, EnemyAstraea, "Astraea_1");
	orderActorToFactory(31037500, EnemyAstraea, "Astraea_2");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(31027100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(31037500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500001;
				pActor->_Y = -220001;
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 3-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_02::processFinal() {
}

Stage01_02::~Stage01_02() {

}
