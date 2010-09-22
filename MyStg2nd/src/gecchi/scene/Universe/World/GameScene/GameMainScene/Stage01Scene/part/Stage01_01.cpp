#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,400,30000};
	_paFrame_NextEvent = new frame[4];
	for (int i = 0; i < 4; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(21387100, FormationIris002, "F002_Iris_1");
	orderActorToFactory(21397400, FormationIris002, "F002_Iris_2");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				FormationIris002* pActor = (FormationIris002*)obtainActorFromFactory(21387100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 400:
				{
				FormationIris002* pActor = (FormationIris002*)obtainActorFromFactory(21397400);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 30000:
				throwUpEvent(STG01_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage01_01::processFinal() {
}

Stage01_01::~Stage01_01() {

}
