#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_01::Stage01_01(const char* prm_name) : DefaultScene(prm_name) {

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100};
	_paFrame_NextEvent = new frame[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	
	orderActorToFactory(21047100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(21057100, FormationPallas001b, "F001b_Pallas_2");
	orderActorToFactory(21067100, FormationPallas001c, "F001c_Pallas_3");
	orderActorToFactory(21077100, FormationPallas001d, "F001d_Pallas_4");
	orderActorToFactory(21087100, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(21097100, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(21107100, FormationPallas001b, "F001b_Pallas_7");
	orderActorToFactory(21117100, FormationPallas001c, "F001c_Pallas_8");
	orderActorToFactory(21127100, FormationPallas001a, "F001a_Pallas_9");
	orderActorToFactory(21137100, FormationPallas001d, "F001d_Pallas_10");
	orderActorToFactory(21147100, FormationPallas001b, "F001b_Pallas_11");
	orderActorToFactory(21157100, FormationPallas001c, "F001c_Pallas_12");
    // gen01 end
}

void Stage01_01::initialize() {

}

void Stage01_01::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�ύX�́u�V�[��Creater.xls�v���J���āA��������s�����Ɓi�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_13");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21047100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21057100)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21067100)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21077100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21087100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21097100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21107100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21117100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21127100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21137100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21147100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21157100)), 400);
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
