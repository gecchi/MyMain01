#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01_02::Stage01_02(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01_02";
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,20,100,160,220,260,280,340,400,460,500,700,860,1100,1200,1340,1580,1820,2060,2200,2300,2500,2700,3000,3200,4000,4200,5000,5200,6000,6200,7000,7200,8000,9000,9200};
	_paFrame_NextEvent = new frame[36];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 36;
	orderActorToFactory(40000000, EnemyMetis, "Metis_1");
	orderActorToFactory(40000001, EnemyMetis, "Metis_2");
	orderActorToFactory(40000002, EnemyMetis, "Metis_3");
	orderActorToFactory(40000003, EnemyMetis, "Metis_4");
	orderActorToFactory(40000004, EnemyMetis, "Metis_5");
	orderActorToFactory(40000005, EnemyMetis, "Metis_6");
	orderActorToFactory(40000006, EnemyMetis, "Metis_7");
	orderActorToFactory(40000007, FormationEunomia001a, "F001a_Eunomia_8");
	orderActorToFactory(40000008, FormationEunomia001b, "F001b_Eunomia_9");
	orderActorToFactory(40000009, FormationEunomia001a, "F001a_Eunomia_10");
	orderActorToFactory(40000010, FormationEunomia001b, "F001b_Eunomia_11");
	orderActorToFactory(40000011, FormationEunomia001a, "F001a_Eunomia_12");
	
	orderActorToFactory(40000018, FormationPallas001a, "F001a_Pallas_13");
	orderActorToFactory(40000019, FormationPallas001b, "F001b_Pallas_14");
	orderActorToFactory(40000020, FormationPallas001c, "F001c_Pallas_15");
	orderActorToFactory(40000021, FormationPallas001d, "F001d_Pallas_16");
	orderActorToFactory(40000022, FormationPallas001a, "F001a_Pallas_17");
	orderActorToFactory(40000023, FormationPallas001d, "F001d_Pallas_18");
	orderActorToFactory(40000024, FormationPallas001b, "F001b_Pallas_19");
	orderActorToFactory(40000025, FormationPallas001c, "F001c_Pallas_20");
	orderActorToFactory(40000026, FormationPallas001a, "F001a_Pallas_21");
	orderActorToFactory(40000027, FormationPallas001d, "F001d_Pallas_22");
	orderActorToFactory(40000028, FormationPallas001b, "F001b_Pallas_23");
	orderActorToFactory(40000029, FormationPallas001c, "F001c_Pallas_24");
    // gen01 end
}

void Stage01_02::initialize() {

}

void Stage01_02::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(40000012, FormationEunomia001b, "F001b_Eunomia_25");
				break;
			}
			case 100: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000000);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 160: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000001);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 220: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000002);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 260: {
				orderActorToFactory(40000013, FormationEunomia001a, "F001a_Eunomia_26");
				break;
			}
			case 280: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000003);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 340: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000004);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 400: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000005);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 460: {
				EnemyMetis* pMetis = (EnemyMetis*)obtainActorFromFactory(40000006);
				getDirector()->addSubGroup(pMetis);
				break;
			}
			case 500: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(40000007);
				getDirector()->addSubGroup(pFormationEunomia);
				orderActorToFactory(40000014, FormationEunomia001b, "F001b_Eunomia_27");
				orderActorToFactory(40000015, EnemyAstraea, "Astraea_28");
				break;
			}
			case 700: {
				orderActorToFactory(40000016, FormationMassalia, "FormationMassalia_29");
				break;
			}
			case 860: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(40000008);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 1100: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(40000009);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 1200: {
				orderActorToFactory(40000030, FormationJuno001, "F002_Juno_30");
				break;
			}
			case 1340: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(40000010);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 1580: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(40000011);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 1820: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(40000012);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 2060: {
				FormationEunomia001a* pFormationEunomia = (FormationEunomia001a*)obtainActorFromFactory(40000013);
				getDirector()->addSubGroup(pFormationEunomia);
				break;
			}
			case 2200: {
				orderActorToFactory(40000031, VarietyTorus001, "VarietyTorus001_31");
				break;
			}
			case 2300: {
				FormationEunomia001b* pFormationEunomia = (FormationEunomia001b*)obtainActorFromFactory(40000014);
				getDirector()->addSubGroup(pFormationEunomia);
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000015);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 2500: {
				FormationMassalia* pFormationMassalia = (FormationMassalia*)obtainActorFromFactory(40000016);
				getDirector()->addSubGroup(pFormationMassalia);
				break;
			}
			case 2700: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_40000017");
				ta->setMaxPerformFrame(2500);
				addSubLast(ta);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000018)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000019)), 400);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000020)), 400);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000021)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000022)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000023)), 400);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000024)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000025)), 400);
				ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(40000026)), 1);
				ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(40000027)), 1);
				ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(40000028)), 1);
				ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(40000029)), 400);
				}
				break;
			}
			case 3000: {
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40000030);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 3200: {
				orderActorToFactory(40000032, VarietyTorus002, "VarietyTorus002_32");
				break;
			}
			case 4000: {
				VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(40000031);
				getDirector()->addSubGroup(pTorus);
				break;
			}
			case 4200: {
				orderActorToFactory(40000033, VarietyTorus003, "VarietyTorus003_33");
				break;
			}
			case 5000: {
				VarietyTorus002* pTorusA = (VarietyTorus002*)obtainActorFromFactory(40000032);
				getDirector()->addSubGroup(pTorusA);
				break;
			}
			case 5200: {
				orderActorToFactory(40000034, VarietyTorus004, "VarietyTorus004_34");
				break;
			}
			case 6000: {
				VarietyTorus003* pTorusB = (VarietyTorus003*)obtainActorFromFactory(40000033);
				getDirector()->addSubGroup(pTorusB);
				break;
			}
			case 6200: {
				orderActorToFactory(40000035, VarietyTorus004, "VarietyTorus004_35");
				orderActorToFactory(40000038, FormationIris002, "F002_Iris_36");
				orderActorToFactory(40000039, FormationIris001, "F001_Iris_37");
				orderActorToFactory(40000040, FormationIris001, "F001_Iris_38");
				orderActorToFactory(40000041, FormationIris002, "F002_Iris_39");
				orderActorToFactory(40000042, FormationIris001, "F001_Iris_40");
				orderActorToFactory(40000043, FormationIris002, "F002_Iris_41");
				break;
			}
			case 7000: {
				VarietyTorus004* pTorus = (VarietyTorus004*)obtainActorFromFactory(40000034);
				getDirector()->addSubGroup(pTorus);
				break;
			}
			case 7200: {
				orderActorToFactory(40000036, FormationThalia, "FormationThalia_42");
				break;
			}
			case 8000: {
				throwEventToUpperTree(EVENT_STG01_02_WAS_BROKEN,this);
				VarietyTorus004* pTorus = (VarietyTorus004*)obtainActorFromFactory(40000035);
				getDirector()->addSubGroup(pTorus);
				break;
			}
			case 9000: {
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000036);
				getDirector()->addSubGroup(pF);
				break;
			}
			case 9200: {
				{
				FormationTableScene* ta = NEW FormationTableScene("FormationTable_40000037");
				ta->setMaxPerformFrame(2000);
				addSubLast(ta);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000038)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000039)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000040)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000041)), 400);
				ta->addToTable(((FormationIris001*)obtainActorFromFactory(40000042)), 400);
				ta->addToTable(((FormationIris002*)obtainActorFromFactory(40000043)), 400);
				}
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 36-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end
}

Stage01_02::~Stage01_02() {

}
