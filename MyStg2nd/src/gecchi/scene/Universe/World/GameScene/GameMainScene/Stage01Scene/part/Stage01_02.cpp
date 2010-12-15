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
	frame f[] = {1,100,200,500,800,1100,1400,1700,2000,2300,2600,2900,4000};
	_paFrame_NextEvent = new frame[13];
	for (int i = 0; i < 13; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderActorToFactory(40000000, EnemyAstraea, "Astraea_1");
	
	orderActorToFactory(40000002, FormationPallas001a, "F001a_Pallas_2");
	orderActorToFactory(40000003, FormationPallas001b, "F001b_Pallas_3");
	orderActorToFactory(40000004, FormationPallas001c, "F001c_Pallas_4");
	orderActorToFactory(40000005, FormationPallas001d, "F001d_Pallas_5");
	orderActorToFactory(40000006, FormationPallas001a, "F001a_Pallas_6");
	orderActorToFactory(40000007, FormationPallas001d, "F001d_Pallas_7");
	orderActorToFactory(40000008, FormationPallas001b, "F001b_Pallas_8");
	orderActorToFactory(40000009, FormationPallas001c, "F001c_Pallas_9");
	orderActorToFactory(40000010, FormationPallas001a, "F001a_Pallas_10");
	orderActorToFactory(40000011, FormationPallas001d, "F001d_Pallas_11");
	orderActorToFactory(40000012, FormationPallas001b, "F001b_Pallas_12");
	orderActorToFactory(40000013, FormationPallas001c, "F001c_Pallas_13");
	orderActorToFactory(40000014, EnemyAstraea, "Astraea_14");
	orderActorToFactory(40000015, EnemyAstraea, "Astraea_15");
	orderActorToFactory(40000016, EnemyAstraea, "Astraea_16");
	orderActorToFactory(40000017, EnemyAstraea, "Astraea_17");
	orderActorToFactory(40000018, EnemyAstraea, "Astraea_18");
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
			case 1: {
				break;
			}
			case 100: {
				EnemyAstraea* pAstraea = (EnemyAstraea*)obtainActorFromFactory(40000000);
				getLordActor()->addSubGroup(pAstraea);
				pAstraea->_Z = -1800000;
				pAstraea->_Y = -100000;
				{
				ActorTableScene* ta = NEW ActorTableScene("TableScene_40000001");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000002)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000003)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000004)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000005)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000006)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000007)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000008)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000009)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000010)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000011)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000012)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000013)), 400);
				}
				break;
			}
			case 200: {
				orderActorToFactory(40000019, EnemyAstraea, "Astraea_19");
				break;
			}
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000014);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(40000020, EnemyAstraea, "Astraea_20");
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 800: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000015);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(40000021, EnemyAstraea, "Astraea_21");
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 1100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000016);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(40000022, EnemyAstraea, "Astraea_22");
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 1400: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000017);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 1700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000018);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2000: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000019);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000020);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2600: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000021);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000022);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 4000: {
				throwEventToUpperTree(EVENT_STG01_02_WAS_BROKEN,this);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 13-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_02::processFinal() {
}

Stage01_02::~Stage01_02() {

}
