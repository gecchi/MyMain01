#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02_01::Stage02_01(const char* prm_name) : DefaultScene(prm_name) {
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,1000,3000};
	_paFrame_NextEvent = new frame[4];
	for (int i = 0; i < 4; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(61027100, FormationJuno001, "F002_Juno_1");
	
	orderActorToFactory(610571000, FormationIris001, "F001_Iris_2");
	orderActorToFactory(610671000, FormationIris002, "F002_Iris_3");
	orderActorToFactory(610771000, FormationIris001, "F001_Iris_4");
	orderActorToFactory(610871000, FormationIris002, "F002_Iris_5");
	orderActorToFactory(610971000, FormationIris001, "F001_Iris_6");
	orderActorToFactory(611071000, FormationIris002, "F002_Iris_7");
    // gen01 end
}

void Stage02_01::initialize() {

}

void Stage02_01::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				FormationJuno001* pActor = (FormationJuno001*)obtainActorFromFactory(61027100);
				getLordActor()->addSubGroup(pActor);
				}
				break;
			case 1000:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_8");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(610571000)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(610671000)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(610771000)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(610871000)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(610971000)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(611071000)), 400);
				}
				break;
			case 3000:
				throwUpEvent(STG02_01_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

}

void Stage02_01::processFinal() {
}

Stage02_01::~Stage02_01() {

}
