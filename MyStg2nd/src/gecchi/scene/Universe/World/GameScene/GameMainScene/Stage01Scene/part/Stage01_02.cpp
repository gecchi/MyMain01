#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,500,800,2500};
	_paFrame_NextEvent = new frame[5];
	for (int i = 0; i < 5; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(41026100, EnemyAstraea, "Astraea_1");
	
	orderActorToFactory(41097100, FormationPallas001a, "F001a_Pallas_2");
	orderActorToFactory(41107100, FormationPallas001b, "F001b_Pallas_3");
	orderActorToFactory(41117100, FormationPallas001c, "F001c_Pallas_4");
	orderActorToFactory(41127100, FormationPallas001d, "F001d_Pallas_5");
	orderActorToFactory(41137100, FormationPallas001a, "F001a_Pallas_6");
	orderActorToFactory(41147100, FormationPallas001d, "F001d_Pallas_7");
	orderActorToFactory(41157100, FormationPallas001b, "F001b_Pallas_8");
	orderActorToFactory(41167100, FormationPallas001c, "F001c_Pallas_9");
	orderActorToFactory(41177100, FormationPallas001a, "F001a_Pallas_10");
	orderActorToFactory(41187100, FormationPallas001d, "F001d_Pallas_11");
	orderActorToFactory(41197100, FormationPallas001b, "F001b_Pallas_12");
	orderActorToFactory(41207100, FormationPallas001c, "F001c_Pallas_13");
	orderActorToFactory(41246500, EnemyAstraea, "Astraea_14");
	orderActorToFactory(41246800, EnemyAstraea, "Astraea_15");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(41026100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_41086100");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41097100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41107100)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41117100)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41127100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41137100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41147100)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41157100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41167100)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(41177100)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(41187100)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(41197100)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(41207100)), 400);
				}
				break;
			case 500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(41246500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(41246800);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 2500:
				throwEventToUpperTree(EVENT_STG01_02_WAS_BROKEN,this);
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 5-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_02::processFinal() {
}

Stage01_02::~Stage01_02() {

}
