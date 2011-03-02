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
	frame f[] = {1,100,200,500,700,1000,1200,1500,1700,2000,2200,2500,2700,3000,3200,3500,3700,4000,4200,4500,4700,5000,5200,5500,5700,6000,6200,6500,6700,7000,7200,7500,7700,8000,8200,8500,8700,9000,9200,9500,9700,10000,10200,10500,10700,11000,11200,11500,11700,12000,12200,12500,12700,13000,13200,13500,13700,14000,14200,14500,14700,15000,15200,15500,15700,16000,16200,16500,16700,17000,17200,17500,17700,18000,18200,18500,18700,19000,19200,19500,19700,20000,20200,20500,20700,21000,21200,21500,21700,22000,22200,22201,22301,22401,22500,22501,22601,22701,22801,22901,23000,23001,23101,23201,23301,23401,23500,23501,23601,23701,23801,23901,24000,24001,24101,24201,24301,24401,24501,24601,24701,24801,24901,25001,25101,25201,25301,25401,25501,25601,25701,25801,25901,26001,26101,26201,26301,26401,26501,26601,26701,26801,26901,27001,27101,27201,27301,27401,27501,27601,27701,27801,27901,28001,28101,28201,28301,28401,28501,28601,28701,28801,28901,29001,29101,29201,29301,29401,29501,29601,29701,29801,29901,30001,30101,30201,30301,30401,30501,30601,30701,30801,30901,31001,31101,31201,31301,31401,31501,31601,31701,31801,31901,32001,32101,32201,32301,32401,32501,32601,32701,32801,32901,33001,33101,33201,33301,33401,33501,33601,33701,33801,33901,34001,34101,34201,34301,34401,34501,34601,34701,34801,34901,35001,35101,35201,35301,35401,35501,35601,35701,35801,35901,36001,36101,36201,36301,36401,36501,36601,36701,36801,36901,37001,37101,37201,37301,37401,37501,37601,37701,37801,37901,38001,38101,38201,38301,38401,38501,38601,38701,38801,38901,39001,39101,39201,39301,39401,39501,39601,39701,39801,39901,40001,40101,40201,40301,40401,40501,40601,40701,40801,40901,41001,41101,41201,41301,41401,41501,41601,41701,41801,41901,42001,42101,42201,42301,42401,42501,42601,42701,42801,42901,43001,43101,43201,43301,43401,43501,43601,43701,43801,43901,44001,44101,44201,44301,44401,44501,44601,44701,44801,44901,45001,45101,45201,45301,45401,45501,45601,45701,45801,45901,46001,46101,46201,46301,46401,46501,46601,46701,46801,46901,47001,47101,47201,47301,47401,47501,47601,47701,47801,47901,48001,48101,48201,48301,48401,48501,48601,48701,48801,48901,49001,49101,49201,49301,49401,49501,49601,49701,49801,49901,50001,50101,50201,50301,50401,50501,50601,50701,50801,50901,51001,51101,51201,51301,51401,51501,51601,51701,51801,51901,52001,52101,52201,52301,52401,52501,52601,52701,52801,52901,53001,53101,53201,53301,53401,53501,53601,53701,53801,53901,54001,54101,54201,54301,54401,54501,54601,54701,54801,54901,55001,55101,55201,55301,55401,55501,55601,55701,55801,55901,56001,56101,56201,56301,56401,56501,56601,56701,56801,56901,57001,57101,57201,57301,57401,57501,57601,57701,57801,57901,58001,58101,58201,58301,58401,58501,58601,58701,58801,58901,59001,59101,59201,59301,59401,59501,59601,59701,59801,59901,60001,60101,60201,60301,60401,60501,60601,60701,60801,60901,61001,61101,61201,61301,61401,61501,61601,61701,61801,61901};
	_paFrame_NextEvent = new frame[493];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 493;
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
	orderActorToFactory(40000021, EnemyMetis, "Metis_16");
	orderActorToFactory(40000022, EnemyMetis, "Metis_17");
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
				ta->setMaxPerformFrame(2500);
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
				orderActorToFactory(40000023, EnemyMetis, "Metis_18");
				orderActorToFactory(40000452, FormationThalia, "FormationThalia_19");
				break;
			}
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000014);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				break;
			}
			case 700: {
				orderActorToFactory(40000016, EnemyAstraea, "Astraea_20");
				orderActorToFactory(40000024, EnemyMetis, "Metis_21");
				break;
			}
			case 1000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000021);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 1200: {
				orderActorToFactory(40000017, VarietyTorus001, "VarietyTorus001_22");
				orderActorToFactory(40000025, EnemyMetis, "Metis_23");
				break;
			}
			case 1500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000015);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000022);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 1700: {
				orderActorToFactory(40000026, EnemyMetis, "Metis_24");
				break;
			}
			case 2000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000023);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000452);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 2200: {
				orderActorToFactory(40000027, EnemyMetis, "Metis_25");
				break;
			}
			case 2500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(40000016);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = -1800000;
				pAstraea2->_Y = -100000;
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000024);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 2700: {
				orderActorToFactory(40000028, EnemyMetis, "Metis_26");
				break;
			}
			case 3000: {
				VarietyTorus001* pTorus = (VarietyTorus001*)obtainActorFromFactory(40000017);
				getLordActor()->addSubGroup(pTorus);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000025);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 3200: {
				orderActorToFactory(40000029, EnemyMetis, "Metis_27");
				orderActorToFactory(40000448, FormationJuno001, "F002_Juno_28");
				orderActorToFactory(40000450, FormationIris002, "F002_Iris_29");
				break;
			}
			case 3500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000026);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 3700: {
				orderActorToFactory(40000030, EnemyMetis, "Metis_30");
				orderActorToFactory(40000451, FormationIris002, "F002_Iris_31");
				break;
			}
			case 4000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000027);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 4200: {
				orderActorToFactory(40000031, EnemyMetis, "Metis_32");
				break;
			}
			case 4500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000028);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 4700: {
				orderActorToFactory(40000032, EnemyMetis, "Metis_33");
				break;
			}
			case 5000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000029);
				getLordActor()->addSubGroup(pMetis1);
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40000448);
				getLordActor()->addSubGroup(pF);
				FormationIris002* pF1 = (FormationIris002*)obtainActorFromFactory(40000450);
				getLordActor()->addSubGroup(pF1);
				break;
			}
			case 5200: {
				orderActorToFactory(40000033, EnemyMetis, "Metis_34");
				break;
			}
			case 5500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000030);
				getLordActor()->addSubGroup(pMetis1);
				FormationIris002* pF2 = (FormationIris002*)obtainActorFromFactory(40000451);
				getLordActor()->addSubGroup(pF2);
				break;
			}
			case 5700: {
				orderActorToFactory(40000034, EnemyMetis, "Metis_35");
				break;
			}
			case 6000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000031);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 6200: {
				orderActorToFactory(40000035, EnemyMetis, "Metis_36");
				break;
			}
			case 6500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000032);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 6700: {
				orderActorToFactory(40000036, EnemyMetis, "Metis_37");
				break;
			}
			case 7000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000033);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 7200: {
				orderActorToFactory(40000037, EnemyMetis, "Metis_38");
				break;
			}
			case 7500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000034);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 7700: {
				orderActorToFactory(40000038, EnemyMetis, "Metis_39");
				break;
			}
			case 8000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000035);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 8200: {
				orderActorToFactory(40000018, VarietyTorus002, "VarietyTorus002_40");
				orderActorToFactory(40000019, VarietyTorus003, "VarietyTorus003_41");
				orderActorToFactory(40000039, EnemyMetis, "Metis_42");
				break;
			}
			case 8500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000036);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 8700: {
				orderActorToFactory(40000040, EnemyMetis, "Metis_43");
				break;
			}
			case 9000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000037);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 9200: {
				orderActorToFactory(40000041, EnemyMetis, "Metis_44");
				break;
			}
			case 9500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000038);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 9700: {
				orderActorToFactory(40000042, EnemyMetis, "Metis_45");
				break;
			}
			case 10000: {
				VarietyTorus002* pTorusA = (VarietyTorus002*)obtainActorFromFactory(40000018);
				getLordActor()->addSubGroup(pTorusA);
				VarietyTorus003* pTorusB = (VarietyTorus003*)obtainActorFromFactory(40000019);
				getLordActor()->addSubGroup(pTorusB);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000039);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 10200: {
				orderActorToFactory(40000043, EnemyMetis, "Metis_46");
				break;
			}
			case 10500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000040);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 10700: {
				orderActorToFactory(40000044, EnemyMetis, "Metis_47");
				break;
			}
			case 11000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000041);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 11200: {
				orderActorToFactory(40000045, EnemyMetis, "Metis_48");
				orderActorToFactory(40000449, FormationJuno001, "F002_Juno_49");
				break;
			}
			case 11500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000042);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 11700: {
				orderActorToFactory(40000046, EnemyMetis, "Metis_50");
				break;
			}
			case 12000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000043);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 12200: {
				orderActorToFactory(40000047, EnemyMetis, "Metis_51");
				break;
			}
			case 12500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000044);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 12700: {
				orderActorToFactory(40000048, EnemyMetis, "Metis_52");
				break;
			}
			case 13000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000045);
				getLordActor()->addSubGroup(pMetis1);
				FormationJuno001* pF = (FormationJuno001*)obtainActorFromFactory(40000449);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 13200: {
				orderActorToFactory(40000049, EnemyMetis, "Metis_53");
				break;
			}
			case 13500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000046);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 13700: {
				orderActorToFactory(40000050, EnemyMetis, "Metis_54");
				break;
			}
			case 14000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000047);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 14200: {
				orderActorToFactory(40000051, EnemyMetis, "Metis_55");
				break;
			}
			case 14500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000048);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 14700: {
				orderActorToFactory(40000052, EnemyMetis, "Metis_56");
				break;
			}
			case 15000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000049);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 15200: {
				orderActorToFactory(40000053, EnemyMetis, "Metis_57");
				orderActorToFactory(40000453, FormationThalia, "FormationThalia_58");
				break;
			}
			case 15500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000050);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 15700: {
				orderActorToFactory(40000054, EnemyMetis, "Metis_59");
				break;
			}
			case 16000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000051);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 16200: {
				orderActorToFactory(40000055, EnemyMetis, "Metis_60");
				break;
			}
			case 16500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000052);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 16700: {
				orderActorToFactory(40000056, EnemyMetis, "Metis_61");
				break;
			}
			case 17000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000053);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000453);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 17200: {
				orderActorToFactory(40000057, EnemyMetis, "Metis_62");
				orderActorToFactory(40000454, FormationThalia, "FormationThalia_63");
				break;
			}
			case 17500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000054);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 17700: {
				orderActorToFactory(40000058, EnemyMetis, "Metis_64");
				break;
			}
			case 18000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000055);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 18200: {
				orderActorToFactory(40000020, VarietyTorus004, "VarietyTorus004_65");
				orderActorToFactory(40000059, EnemyMetis, "Metis_66");
				break;
			}
			case 18500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000056);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 18700: {
				orderActorToFactory(40000060, EnemyMetis, "Metis_67");
				break;
			}
			case 19000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000057);
				getLordActor()->addSubGroup(pMetis1);
				FormationThalia* pF = (FormationThalia*)obtainActorFromFactory(40000454);
				getLordActor()->addSubGroup(pF);
				break;
			}
			case 19200: {
				orderActorToFactory(40000061, EnemyMetis, "Metis_68");
				break;
			}
			case 19500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000058);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 19700: {
				orderActorToFactory(40000062, EnemyMetis, "Metis_69");
				break;
			}
			case 20000: {
				VarietyTorus004* pTorus = (VarietyTorus004*)obtainActorFromFactory(40000020);
				getLordActor()->addSubGroup(pTorus);
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000059);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 20200: {
				orderActorToFactory(40000063, EnemyMetis, "Metis_70");
				break;
			}
			case 20500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000060);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 20700: {
				orderActorToFactory(40000064, EnemyMetis, "Metis_71");
				break;
			}
			case 21000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000061);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 21200: {
				orderActorToFactory(40000065, EnemyMetis, "Metis_72");
				break;
			}
			case 21500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000062);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 21700: {
				orderActorToFactory(40000066, EnemyMetis, "Metis_73");
				break;
			}
			case 22000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000063);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 22200: {
				orderActorToFactory(40000067, EnemyMetis, "Metis_74");
				break;
			}
			case 22201: {
				orderActorToFactory(40000068, EnemyMetis, "Metis_75");
				break;
			}
			case 22301: {
				orderActorToFactory(40000069, EnemyMetis, "Metis_76");
				break;
			}
			case 22401: {
				orderActorToFactory(40000070, EnemyMetis, "Metis_77");
				break;
			}
			case 22500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000064);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 22501: {
				orderActorToFactory(40000071, EnemyMetis, "Metis_78");
				break;
			}
			case 22601: {
				orderActorToFactory(40000072, EnemyMetis, "Metis_79");
				break;
			}
			case 22701: {
				orderActorToFactory(40000073, EnemyMetis, "Metis_80");
				break;
			}
			case 22801: {
				orderActorToFactory(40000074, EnemyMetis, "Metis_81");
				break;
			}
			case 22901: {
				orderActorToFactory(40000075, EnemyMetis, "Metis_82");
				break;
			}
			case 23000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000065);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 23001: {
				orderActorToFactory(40000076, EnemyMetis, "Metis_83");
				break;
			}
			case 23101: {
				orderActorToFactory(40000077, EnemyMetis, "Metis_84");
				break;
			}
			case 23201: {
				orderActorToFactory(40000078, EnemyMetis, "Metis_85");
				break;
			}
			case 23301: {
				orderActorToFactory(40000079, EnemyMetis, "Metis_86");
				break;
			}
			case 23401: {
				orderActorToFactory(40000080, EnemyMetis, "Metis_87");
				break;
			}
			case 23500: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000066);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 23501: {
				orderActorToFactory(40000081, EnemyMetis, "Metis_88");
				break;
			}
			case 23601: {
				orderActorToFactory(40000082, EnemyMetis, "Metis_89");
				break;
			}
			case 23701: {
				orderActorToFactory(40000083, EnemyMetis, "Metis_90");
				break;
			}
			case 23801: {
				orderActorToFactory(40000084, EnemyMetis, "Metis_91");
				break;
			}
			case 23901: {
				orderActorToFactory(40000085, EnemyMetis, "Metis_92");
				break;
			}
			case 24000: {
				EnemyMetis* pMetis1 = (EnemyMetis*)obtainActorFromFactory(40000067);
				getLordActor()->addSubGroup(pMetis1);
				break;
			}
			case 24001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000068);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000086, EnemyMetis, "Metis_93");
				break;
			}
			case 24101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000069);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000087, EnemyMetis, "Metis_94");
				break;
			}
			case 24201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000070);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000088, EnemyMetis, "Metis_95");
				break;
			}
			case 24301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000071);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000089, EnemyMetis, "Metis_96");
				break;
			}
			case 24401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000072);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000090, EnemyMetis, "Metis_97");
				break;
			}
			case 24501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000073);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000091, EnemyMetis, "Metis_98");
				break;
			}
			case 24601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000074);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000092, EnemyMetis, "Metis_99");
				break;
			}
			case 24701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000075);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000093, EnemyMetis, "Metis_100");
				break;
			}
			case 24801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000076);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000094, EnemyMetis, "Metis_101");
				break;
			}
			case 24901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000077);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000095, EnemyMetis, "Metis_102");
				break;
			}
			case 25001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000078);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000096, EnemyMetis, "Metis_103");
				break;
			}
			case 25101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000079);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000097, EnemyMetis, "Metis_104");
				break;
			}
			case 25201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000080);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000098, EnemyMetis, "Metis_105");
				break;
			}
			case 25301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000081);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000099, EnemyMetis, "Metis_106");
				break;
			}
			case 25401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000082);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000100, EnemyMetis, "Metis_107");
				break;
			}
			case 25501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000083);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000101, EnemyMetis, "Metis_108");
				break;
			}
			case 25601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000084);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000102, EnemyMetis, "Metis_109");
				break;
			}
			case 25701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000085);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000103, EnemyMetis, "Metis_110");
				break;
			}
			case 25801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000086);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000104, EnemyMetis, "Metis_111");
				break;
			}
			case 25901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000087);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000105, EnemyMetis, "Metis_112");
				break;
			}
			case 26001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000088);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000106, EnemyMetis, "Metis_113");
				break;
			}
			case 26101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000089);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000107, EnemyMetis, "Metis_114");
				break;
			}
			case 26201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000090);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000108, EnemyMetis, "Metis_115");
				break;
			}
			case 26301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000091);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000109, EnemyMetis, "Metis_116");
				break;
			}
			case 26401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000092);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000110, EnemyMetis, "Metis_117");
				break;
			}
			case 26501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000093);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000111, EnemyMetis, "Metis_118");
				break;
			}
			case 26601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000094);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000112, EnemyMetis, "Metis_119");
				break;
			}
			case 26701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000095);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000113, EnemyMetis, "Metis_120");
				break;
			}
			case 26801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000096);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000114, EnemyMetis, "Metis_121");
				break;
			}
			case 26901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000097);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000115, EnemyMetis, "Metis_122");
				break;
			}
			case 27001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000098);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000116, EnemyMetis, "Metis_123");
				break;
			}
			case 27101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000099);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000117, EnemyMetis, "Metis_124");
				break;
			}
			case 27201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000100);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000118, EnemyMetis, "Metis_125");
				break;
			}
			case 27301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000101);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000119, EnemyMetis, "Metis_126");
				break;
			}
			case 27401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000102);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000120, EnemyMetis, "Metis_127");
				break;
			}
			case 27501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000103);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000121, EnemyMetis, "Metis_128");
				break;
			}
			case 27601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000104);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000122, EnemyMetis, "Metis_129");
				break;
			}
			case 27701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000105);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000123, EnemyMetis, "Metis_130");
				break;
			}
			case 27801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000106);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000124, EnemyMetis, "Metis_131");
				break;
			}
			case 27901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000107);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000125, EnemyMetis, "Metis_132");
				break;
			}
			case 28001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000108);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000126, EnemyMetis, "Metis_133");
				break;
			}
			case 28101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000109);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000127, EnemyMetis, "Metis_134");
				break;
			}
			case 28201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000110);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000128, EnemyMetis, "Metis_135");
				break;
			}
			case 28301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000111);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000129, EnemyMetis, "Metis_136");
				break;
			}
			case 28401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000112);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000130, EnemyMetis, "Metis_137");
				break;
			}
			case 28501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000113);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000131, EnemyMetis, "Metis_138");
				break;
			}
			case 28601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000114);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000132, EnemyMetis, "Metis_139");
				break;
			}
			case 28701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000115);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000133, EnemyMetis, "Metis_140");
				break;
			}
			case 28801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000116);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000134, EnemyMetis, "Metis_141");
				break;
			}
			case 28901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000117);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000135, EnemyMetis, "Metis_142");
				break;
			}
			case 29001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000118);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000136, EnemyMetis, "Metis_143");
				break;
			}
			case 29101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000119);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000137, EnemyMetis, "Metis_144");
				break;
			}
			case 29201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000120);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000138, EnemyMetis, "Metis_145");
				break;
			}
			case 29301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000121);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000139, EnemyMetis, "Metis_146");
				break;
			}
			case 29401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000122);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000140, EnemyMetis, "Metis_147");
				break;
			}
			case 29501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000123);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000141, EnemyMetis, "Metis_148");
				break;
			}
			case 29601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000124);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000142, EnemyMetis, "Metis_149");
				break;
			}
			case 29701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000125);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000143, EnemyMetis, "Metis_150");
				break;
			}
			case 29801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000126);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000144, EnemyMetis, "Metis_151");
				break;
			}
			case 29901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000127);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000145, EnemyMetis, "Metis_152");
				break;
			}
			case 30001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000128);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000146, EnemyMetis, "Metis_153");
				break;
			}
			case 30101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000129);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000147, EnemyMetis, "Metis_154");
				break;
			}
			case 30201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000130);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000148, EnemyMetis, "Metis_155");
				break;
			}
			case 30301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000131);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000149, EnemyMetis, "Metis_156");
				break;
			}
			case 30401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000132);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000150, EnemyMetis, "Metis_157");
				break;
			}
			case 30501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000133);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000151, EnemyMetis, "Metis_158");
				break;
			}
			case 30601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000134);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000152, EnemyMetis, "Metis_159");
				break;
			}
			case 30701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000135);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000153, EnemyMetis, "Metis_160");
				break;
			}
			case 30801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000136);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000154, EnemyMetis, "Metis_161");
				break;
			}
			case 30901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000137);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000155, EnemyMetis, "Metis_162");
				break;
			}
			case 31001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000138);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000156, EnemyMetis, "Metis_163");
				break;
			}
			case 31101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000139);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000157, EnemyMetis, "Metis_164");
				break;
			}
			case 31201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000140);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000158, EnemyMetis, "Metis_165");
				break;
			}
			case 31301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000141);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000159, EnemyMetis, "Metis_166");
				break;
			}
			case 31401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000142);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000160, EnemyMetis, "Metis_167");
				break;
			}
			case 31501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000143);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000161, EnemyMetis, "Metis_168");
				break;
			}
			case 31601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000144);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000162, EnemyMetis, "Metis_169");
				break;
			}
			case 31701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000145);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000163, EnemyMetis, "Metis_170");
				break;
			}
			case 31801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000146);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000164, EnemyMetis, "Metis_171");
				break;
			}
			case 31901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000147);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000165, EnemyMetis, "Metis_172");
				break;
			}
			case 32001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000148);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000166, EnemyMetis, "Metis_173");
				break;
			}
			case 32101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000149);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000167, EnemyMetis, "Metis_174");
				break;
			}
			case 32201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000150);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000168, EnemyMetis, "Metis_175");
				break;
			}
			case 32301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000151);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000169, EnemyMetis, "Metis_176");
				break;
			}
			case 32401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000152);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000170, EnemyMetis, "Metis_177");
				break;
			}
			case 32501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000153);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000171, EnemyMetis, "Metis_178");
				break;
			}
			case 32601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000154);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000172, EnemyMetis, "Metis_179");
				break;
			}
			case 32701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000155);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000173, EnemyMetis, "Metis_180");
				break;
			}
			case 32801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000156);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000174, EnemyMetis, "Metis_181");
				break;
			}
			case 32901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000157);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000175, EnemyMetis, "Metis_182");
				break;
			}
			case 33001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000158);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000176, EnemyMetis, "Metis_183");
				break;
			}
			case 33101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000159);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000177, EnemyMetis, "Metis_184");
				break;
			}
			case 33201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000160);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000178, EnemyMetis, "Metis_185");
				break;
			}
			case 33301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000161);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000179, EnemyMetis, "Metis_186");
				break;
			}
			case 33401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000162);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000180, EnemyMetis, "Metis_187");
				break;
			}
			case 33501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000163);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000181, EnemyMetis, "Metis_188");
				break;
			}
			case 33601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000164);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000182, EnemyMetis, "Metis_189");
				break;
			}
			case 33701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000165);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000183, EnemyMetis, "Metis_190");
				break;
			}
			case 33801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000166);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000184, EnemyMetis, "Metis_191");
				break;
			}
			case 33901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000167);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000185, EnemyMetis, "Metis_192");
				break;
			}
			case 34001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000168);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000186, EnemyMetis, "Metis_193");
				break;
			}
			case 34101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000169);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000187, EnemyMetis, "Metis_194");
				break;
			}
			case 34201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000170);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000188, EnemyMetis, "Metis_195");
				break;
			}
			case 34301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000171);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000189, EnemyMetis, "Metis_196");
				break;
			}
			case 34401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000172);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000190, EnemyMetis, "Metis_197");
				break;
			}
			case 34501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000173);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000191, EnemyMetis, "Metis_198");
				break;
			}
			case 34601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000174);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000192, EnemyMetis, "Metis_199");
				break;
			}
			case 34701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000175);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000193, EnemyMetis, "Metis_200");
				break;
			}
			case 34801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000176);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000194, EnemyMetis, "Metis_201");
				break;
			}
			case 34901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000177);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000195, EnemyMetis, "Metis_202");
				break;
			}
			case 35001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000178);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000196, EnemyMetis, "Metis_203");
				break;
			}
			case 35101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000179);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000197, EnemyMetis, "Metis_204");
				break;
			}
			case 35201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000180);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000198, EnemyMetis, "Metis_205");
				break;
			}
			case 35301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000181);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000199, EnemyMetis, "Metis_206");
				break;
			}
			case 35401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000182);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000200, EnemyMetis, "Metis_207");
				break;
			}
			case 35501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000183);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000201, EnemyMetis, "Metis_208");
				break;
			}
			case 35601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000184);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000202, EnemyMetis, "Metis_209");
				break;
			}
			case 35701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000185);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000203, EnemyMetis, "Metis_210");
				break;
			}
			case 35801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000186);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000204, EnemyMetis, "Metis_211");
				break;
			}
			case 35901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000187);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000205, EnemyMetis, "Metis_212");
				break;
			}
			case 36001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000188);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000206, EnemyMetis, "Metis_213");
				break;
			}
			case 36101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000189);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000207, EnemyMetis, "Metis_214");
				break;
			}
			case 36201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000190);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000208, EnemyMetis, "Metis_215");
				break;
			}
			case 36301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000191);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000209, EnemyMetis, "Metis_216");
				break;
			}
			case 36401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000192);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000210, EnemyMetis, "Metis_217");
				break;
			}
			case 36501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000193);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000211, EnemyMetis, "Metis_218");
				break;
			}
			case 36601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000194);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000212, EnemyMetis, "Metis_219");
				break;
			}
			case 36701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000195);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000213, EnemyMetis, "Metis_220");
				break;
			}
			case 36801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000196);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000214, EnemyMetis, "Metis_221");
				break;
			}
			case 36901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000197);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000215, EnemyMetis, "Metis_222");
				break;
			}
			case 37001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000198);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000216, EnemyMetis, "Metis_223");
				break;
			}
			case 37101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000199);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000217, EnemyMetis, "Metis_224");
				break;
			}
			case 37201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000200);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000218, EnemyMetis, "Metis_225");
				break;
			}
			case 37301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000201);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000219, EnemyMetis, "Metis_226");
				break;
			}
			case 37401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000202);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000220, EnemyMetis, "Metis_227");
				break;
			}
			case 37501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000203);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000221, EnemyMetis, "Metis_228");
				break;
			}
			case 37601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000204);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000222, EnemyMetis, "Metis_229");
				break;
			}
			case 37701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000205);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000223, EnemyMetis, "Metis_230");
				break;
			}
			case 37801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000206);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000224, EnemyMetis, "Metis_231");
				break;
			}
			case 37901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000207);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000225, EnemyMetis, "Metis_232");
				break;
			}
			case 38001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000208);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000226, EnemyMetis, "Metis_233");
				break;
			}
			case 38101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000209);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000227, EnemyMetis, "Metis_234");
				break;
			}
			case 38201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000210);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000228, EnemyMetis, "Metis_235");
				break;
			}
			case 38301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000211);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000229, EnemyMetis, "Metis_236");
				break;
			}
			case 38401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000212);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000230, EnemyMetis, "Metis_237");
				break;
			}
			case 38501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000213);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000231, EnemyMetis, "Metis_238");
				break;
			}
			case 38601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000214);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000232, EnemyMetis, "Metis_239");
				break;
			}
			case 38701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000215);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000233, EnemyMetis, "Metis_240");
				break;
			}
			case 38801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000216);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000234, EnemyMetis, "Metis_241");
				break;
			}
			case 38901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000217);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000235, EnemyMetis, "Metis_242");
				break;
			}
			case 39001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000218);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000236, EnemyMetis, "Metis_243");
				break;
			}
			case 39101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000219);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000237, EnemyMetis, "Metis_244");
				break;
			}
			case 39201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000220);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000238, EnemyMetis, "Metis_245");
				break;
			}
			case 39301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000221);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000239, EnemyMetis, "Metis_246");
				break;
			}
			case 39401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000222);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000240, EnemyMetis, "Metis_247");
				break;
			}
			case 39501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000223);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000241, EnemyMetis, "Metis_248");
				break;
			}
			case 39601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000224);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000242, EnemyMetis, "Metis_249");
				break;
			}
			case 39701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000225);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000243, EnemyMetis, "Metis_250");
				break;
			}
			case 39801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000226);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000244, EnemyMetis, "Metis_251");
				break;
			}
			case 39901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000227);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000245, EnemyMetis, "Metis_252");
				break;
			}
			case 40001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000228);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000246, EnemyMetis, "Metis_253");
				break;
			}
			case 40101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000229);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000247, EnemyMetis, "Metis_254");
				break;
			}
			case 40201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000230);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000248, EnemyMetis, "Metis_255");
				break;
			}
			case 40301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000231);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000249, EnemyMetis, "Metis_256");
				break;
			}
			case 40401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000232);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000250, EnemyMetis, "Metis_257");
				break;
			}
			case 40501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000233);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000251, EnemyMetis, "Metis_258");
				break;
			}
			case 40601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000234);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000252, EnemyMetis, "Metis_259");
				break;
			}
			case 40701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000235);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000253, EnemyMetis, "Metis_260");
				break;
			}
			case 40801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000236);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000254, EnemyMetis, "Metis_261");
				break;
			}
			case 40901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000237);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000255, EnemyMetis, "Metis_262");
				break;
			}
			case 41001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000238);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000256, EnemyMetis, "Metis_263");
				break;
			}
			case 41101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000239);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000257, EnemyMetis, "Metis_264");
				break;
			}
			case 41201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000240);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000258, EnemyMetis, "Metis_265");
				break;
			}
			case 41301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000241);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000259, EnemyMetis, "Metis_266");
				break;
			}
			case 41401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000242);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000260, EnemyMetis, "Metis_267");
				break;
			}
			case 41501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000243);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000261, EnemyMetis, "Metis_268");
				break;
			}
			case 41601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000244);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000262, EnemyMetis, "Metis_269");
				break;
			}
			case 41701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000245);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000263, EnemyMetis, "Metis_270");
				break;
			}
			case 41801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000246);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000264, EnemyMetis, "Metis_271");
				break;
			}
			case 41901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000247);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000265, EnemyMetis, "Metis_272");
				break;
			}
			case 42001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000248);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000266, EnemyMetis, "Metis_273");
				break;
			}
			case 42101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000249);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000267, EnemyMetis, "Metis_274");
				break;
			}
			case 42201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000250);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000268, EnemyMetis, "Metis_275");
				break;
			}
			case 42301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000251);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000269, EnemyMetis, "Metis_276");
				break;
			}
			case 42401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000252);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000270, EnemyMetis, "Metis_277");
				break;
			}
			case 42501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000253);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000271, EnemyMetis, "Metis_278");
				break;
			}
			case 42601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000254);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000272, EnemyMetis, "Metis_279");
				break;
			}
			case 42701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000255);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000273, EnemyMetis, "Metis_280");
				break;
			}
			case 42801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000256);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000274, EnemyMetis, "Metis_281");
				break;
			}
			case 42901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000257);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000275, EnemyMetis, "Metis_282");
				break;
			}
			case 43001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000258);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000276, EnemyMetis, "Metis_283");
				break;
			}
			case 43101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000259);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000277, EnemyMetis, "Metis_284");
				break;
			}
			case 43201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000260);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000278, EnemyMetis, "Metis_285");
				break;
			}
			case 43301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000261);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000279, EnemyMetis, "Metis_286");
				break;
			}
			case 43401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000262);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000280, EnemyMetis, "Metis_287");
				break;
			}
			case 43501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000263);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000281, EnemyMetis, "Metis_288");
				break;
			}
			case 43601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000264);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000282, EnemyMetis, "Metis_289");
				break;
			}
			case 43701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000265);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000283, EnemyMetis, "Metis_290");
				break;
			}
			case 43801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000266);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000284, EnemyMetis, "Metis_291");
				break;
			}
			case 43901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000267);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000285, EnemyMetis, "Metis_292");
				break;
			}
			case 44001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000268);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000286, EnemyMetis, "Metis_293");
				break;
			}
			case 44101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000269);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000287, EnemyMetis, "Metis_294");
				break;
			}
			case 44201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000270);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000288, EnemyMetis, "Metis_295");
				break;
			}
			case 44301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000271);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000289, EnemyMetis, "Metis_296");
				break;
			}
			case 44401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000272);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000290, EnemyMetis, "Metis_297");
				break;
			}
			case 44501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000273);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000291, EnemyMetis, "Metis_298");
				break;
			}
			case 44601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000274);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000292, EnemyMetis, "Metis_299");
				break;
			}
			case 44701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000275);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000293, EnemyMetis, "Metis_300");
				break;
			}
			case 44801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000276);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000294, EnemyMetis, "Metis_301");
				break;
			}
			case 44901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000277);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000295, EnemyMetis, "Metis_302");
				break;
			}
			case 45001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000278);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000296, EnemyMetis, "Metis_303");
				break;
			}
			case 45101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000279);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000297, EnemyMetis, "Metis_304");
				break;
			}
			case 45201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000280);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000298, EnemyMetis, "Metis_305");
				break;
			}
			case 45301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000281);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000299, EnemyMetis, "Metis_306");
				break;
			}
			case 45401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000282);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000300, EnemyMetis, "Metis_307");
				break;
			}
			case 45501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000283);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000301, EnemyMetis, "Metis_308");
				break;
			}
			case 45601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000284);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000302, EnemyMetis, "Metis_309");
				break;
			}
			case 45701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000285);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000303, EnemyMetis, "Metis_310");
				break;
			}
			case 45801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000286);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000304, EnemyMetis, "Metis_311");
				break;
			}
			case 45901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000287);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000305, EnemyMetis, "Metis_312");
				break;
			}
			case 46001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000288);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000306, EnemyMetis, "Metis_313");
				break;
			}
			case 46101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000289);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000307, EnemyMetis, "Metis_314");
				break;
			}
			case 46201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000290);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000308, EnemyMetis, "Metis_315");
				break;
			}
			case 46301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000291);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000309, EnemyMetis, "Metis_316");
				break;
			}
			case 46401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000292);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000310, EnemyMetis, "Metis_317");
				break;
			}
			case 46501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000293);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000311, EnemyMetis, "Metis_318");
				break;
			}
			case 46601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000294);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000312, EnemyMetis, "Metis_319");
				break;
			}
			case 46701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000295);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000313, EnemyMetis, "Metis_320");
				break;
			}
			case 46801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000296);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000314, EnemyMetis, "Metis_321");
				break;
			}
			case 46901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000297);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000315, EnemyMetis, "Metis_322");
				break;
			}
			case 47001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000298);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000316, EnemyMetis, "Metis_323");
				break;
			}
			case 47101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000299);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000317, EnemyMetis, "Metis_324");
				break;
			}
			case 47201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000300);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000318, EnemyMetis, "Metis_325");
				break;
			}
			case 47301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000301);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000319, EnemyMetis, "Metis_326");
				break;
			}
			case 47401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000302);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000320, EnemyMetis, "Metis_327");
				break;
			}
			case 47501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000303);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000321, EnemyMetis, "Metis_328");
				break;
			}
			case 47601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000304);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000322, EnemyMetis, "Metis_329");
				break;
			}
			case 47701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000305);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000323, EnemyMetis, "Metis_330");
				break;
			}
			case 47801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000306);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000324, EnemyMetis, "Metis_331");
				break;
			}
			case 47901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000307);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000325, EnemyMetis, "Metis_332");
				break;
			}
			case 48001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000308);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000326, EnemyMetis, "Metis_333");
				break;
			}
			case 48101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000309);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000327, EnemyMetis, "Metis_334");
				break;
			}
			case 48201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000310);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000328, EnemyMetis, "Metis_335");
				break;
			}
			case 48301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000311);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000329, EnemyMetis, "Metis_336");
				break;
			}
			case 48401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000312);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000330, EnemyMetis, "Metis_337");
				break;
			}
			case 48501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000313);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000331, EnemyMetis, "Metis_338");
				break;
			}
			case 48601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000314);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000332, EnemyMetis, "Metis_339");
				break;
			}
			case 48701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000315);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000333, EnemyMetis, "Metis_340");
				break;
			}
			case 48801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000316);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000334, EnemyMetis, "Metis_341");
				break;
			}
			case 48901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000317);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000335, EnemyMetis, "Metis_342");
				break;
			}
			case 49001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000318);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000336, EnemyMetis, "Metis_343");
				break;
			}
			case 49101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000319);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000337, EnemyMetis, "Metis_344");
				break;
			}
			case 49201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000320);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000338, EnemyMetis, "Metis_345");
				break;
			}
			case 49301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000321);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000339, EnemyMetis, "Metis_346");
				break;
			}
			case 49401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000322);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000340, EnemyMetis, "Metis_347");
				break;
			}
			case 49501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000323);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000341, EnemyMetis, "Metis_348");
				break;
			}
			case 49601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000324);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000342, EnemyMetis, "Metis_349");
				break;
			}
			case 49701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000325);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000343, EnemyMetis, "Metis_350");
				break;
			}
			case 49801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000326);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000344, EnemyMetis, "Metis_351");
				break;
			}
			case 49901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000327);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000345, EnemyMetis, "Metis_352");
				break;
			}
			case 50001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000328);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000346, EnemyMetis, "Metis_353");
				break;
			}
			case 50101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000329);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000347, EnemyMetis, "Metis_354");
				break;
			}
			case 50201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000330);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000348, EnemyMetis, "Metis_355");
				break;
			}
			case 50301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000331);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000349, EnemyMetis, "Metis_356");
				break;
			}
			case 50401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000332);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000350, EnemyMetis, "Metis_357");
				break;
			}
			case 50501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000333);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000351, EnemyMetis, "Metis_358");
				break;
			}
			case 50601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000334);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000352, EnemyMetis, "Metis_359");
				break;
			}
			case 50701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000335);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000353, EnemyMetis, "Metis_360");
				break;
			}
			case 50801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000336);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000354, EnemyMetis, "Metis_361");
				break;
			}
			case 50901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000337);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000355, EnemyMetis, "Metis_362");
				break;
			}
			case 51001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000338);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000356, EnemyMetis, "Metis_363");
				break;
			}
			case 51101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000339);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000357, EnemyMetis, "Metis_364");
				break;
			}
			case 51201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000340);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000358, EnemyMetis, "Metis_365");
				break;
			}
			case 51301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000341);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000359, EnemyMetis, "Metis_366");
				break;
			}
			case 51401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000342);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000360, EnemyMetis, "Metis_367");
				break;
			}
			case 51501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000343);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000361, EnemyMetis, "Metis_368");
				break;
			}
			case 51601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000344);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000362, EnemyMetis, "Metis_369");
				break;
			}
			case 51701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000345);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000363, EnemyMetis, "Metis_370");
				break;
			}
			case 51801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000346);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000364, EnemyMetis, "Metis_371");
				break;
			}
			case 51901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000347);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000365, EnemyMetis, "Metis_372");
				break;
			}
			case 52001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000348);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000366, EnemyMetis, "Metis_373");
				break;
			}
			case 52101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000349);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000367, EnemyMetis, "Metis_374");
				break;
			}
			case 52201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000350);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000368, EnemyMetis, "Metis_375");
				break;
			}
			case 52301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000351);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000369, EnemyMetis, "Metis_376");
				break;
			}
			case 52401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000352);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000370, EnemyMetis, "Metis_377");
				break;
			}
			case 52501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000353);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000371, EnemyMetis, "Metis_378");
				break;
			}
			case 52601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000354);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000372, EnemyMetis, "Metis_379");
				break;
			}
			case 52701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000355);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000373, EnemyMetis, "Metis_380");
				break;
			}
			case 52801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000356);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000374, EnemyMetis, "Metis_381");
				break;
			}
			case 52901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000357);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000375, EnemyMetis, "Metis_382");
				break;
			}
			case 53001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000358);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000376, EnemyMetis, "Metis_383");
				break;
			}
			case 53101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000359);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000377, EnemyMetis, "Metis_384");
				break;
			}
			case 53201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000360);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000378, EnemyMetis, "Metis_385");
				break;
			}
			case 53301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000361);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000379, EnemyMetis, "Metis_386");
				break;
			}
			case 53401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000362);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000380, EnemyMetis, "Metis_387");
				break;
			}
			case 53501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000363);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000381, EnemyMetis, "Metis_388");
				break;
			}
			case 53601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000364);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000382, EnemyMetis, "Metis_389");
				break;
			}
			case 53701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000365);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000383, EnemyMetis, "Metis_390");
				break;
			}
			case 53801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000366);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000384, EnemyMetis, "Metis_391");
				break;
			}
			case 53901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000367);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000385, EnemyMetis, "Metis_392");
				break;
			}
			case 54001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000368);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000386, EnemyMetis, "Metis_393");
				break;
			}
			case 54101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000369);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000387, EnemyMetis, "Metis_394");
				break;
			}
			case 54201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000370);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000388, EnemyMetis, "Metis_395");
				break;
			}
			case 54301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000371);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000389, EnemyMetis, "Metis_396");
				break;
			}
			case 54401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000372);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000390, EnemyMetis, "Metis_397");
				break;
			}
			case 54501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000373);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000391, EnemyMetis, "Metis_398");
				break;
			}
			case 54601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000374);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000392, EnemyMetis, "Metis_399");
				break;
			}
			case 54701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000375);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000393, EnemyMetis, "Metis_400");
				break;
			}
			case 54801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000376);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000394, EnemyMetis, "Metis_401");
				break;
			}
			case 54901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000377);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000395, EnemyMetis, "Metis_402");
				break;
			}
			case 55001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000378);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000396, EnemyMetis, "Metis_403");
				break;
			}
			case 55101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000379);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000397, EnemyMetis, "Metis_404");
				break;
			}
			case 55201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000380);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000398, EnemyMetis, "Metis_405");
				break;
			}
			case 55301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000381);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000399, EnemyMetis, "Metis_406");
				break;
			}
			case 55401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000382);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000400, EnemyMetis, "Metis_407");
				break;
			}
			case 55501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000383);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000401, EnemyMetis, "Metis_408");
				break;
			}
			case 55601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000384);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000402, EnemyMetis, "Metis_409");
				break;
			}
			case 55701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000385);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000403, EnemyMetis, "Metis_410");
				break;
			}
			case 55801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000386);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000404, EnemyMetis, "Metis_411");
				break;
			}
			case 55901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000387);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000405, EnemyMetis, "Metis_412");
				break;
			}
			case 56001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000388);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000406, EnemyMetis, "Metis_413");
				break;
			}
			case 56101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000389);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000407, EnemyMetis, "Metis_414");
				break;
			}
			case 56201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000390);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000408, EnemyMetis, "Metis_415");
				break;
			}
			case 56301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000391);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000409, EnemyMetis, "Metis_416");
				break;
			}
			case 56401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000392);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000410, EnemyMetis, "Metis_417");
				break;
			}
			case 56501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000393);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000411, EnemyMetis, "Metis_418");
				break;
			}
			case 56601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000394);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000412, EnemyMetis, "Metis_419");
				break;
			}
			case 56701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000395);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000413, EnemyMetis, "Metis_420");
				break;
			}
			case 56801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000396);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000414, EnemyMetis, "Metis_421");
				break;
			}
			case 56901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000397);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000415, EnemyMetis, "Metis_422");
				break;
			}
			case 57001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000398);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000416, EnemyMetis, "Metis_423");
				break;
			}
			case 57101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000399);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000417, EnemyMetis, "Metis_424");
				break;
			}
			case 57201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000400);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000418, EnemyMetis, "Metis_425");
				break;
			}
			case 57301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000401);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000419, EnemyMetis, "Metis_426");
				break;
			}
			case 57401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000402);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000420, EnemyMetis, "Metis_427");
				break;
			}
			case 57501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000403);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000421, EnemyMetis, "Metis_428");
				break;
			}
			case 57601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000404);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000422, EnemyMetis, "Metis_429");
				break;
			}
			case 57701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000405);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000423, EnemyMetis, "Metis_430");
				break;
			}
			case 57801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000406);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000424, EnemyMetis, "Metis_431");
				break;
			}
			case 57901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000407);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000425, EnemyMetis, "Metis_432");
				break;
			}
			case 58001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000408);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000426, EnemyMetis, "Metis_433");
				break;
			}
			case 58101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000409);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000427, EnemyMetis, "Metis_434");
				break;
			}
			case 58201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000410);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000428, EnemyMetis, "Metis_435");
				break;
			}
			case 58301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000411);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000429, EnemyMetis, "Metis_436");
				break;
			}
			case 58401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000412);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000430, EnemyMetis, "Metis_437");
				break;
			}
			case 58501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000413);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000431, EnemyMetis, "Metis_438");
				break;
			}
			case 58601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000414);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000432, EnemyMetis, "Metis_439");
				break;
			}
			case 58701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000415);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000433, EnemyMetis, "Metis_440");
				break;
			}
			case 58801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000416);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000434, EnemyMetis, "Metis_441");
				break;
			}
			case 58901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000417);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000435, EnemyMetis, "Metis_442");
				break;
			}
			case 59001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000418);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000436, EnemyMetis, "Metis_443");
				break;
			}
			case 59101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000419);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000437, EnemyMetis, "Metis_444");
				break;
			}
			case 59201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000420);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000438, EnemyMetis, "Metis_445");
				break;
			}
			case 59301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000421);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000439, EnemyMetis, "Metis_446");
				break;
			}
			case 59401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000422);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000440, EnemyMetis, "Metis_447");
				break;
			}
			case 59501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000423);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000441, EnemyMetis, "Metis_448");
				break;
			}
			case 59601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000424);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000442, EnemyMetis, "Metis_449");
				break;
			}
			case 59701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000425);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000443, EnemyMetis, "Metis_450");
				break;
			}
			case 59801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000426);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000444, EnemyMetis, "Metis_451");
				break;
			}
			case 59901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000427);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000445, EnemyMetis, "Metis_452");
				break;
			}
			case 60001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000428);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000446, EnemyMetis, "Metis_453");
				break;
			}
			case 60101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000429);
				getLordActor()->addSubGroup(pMetis2);
				orderActorToFactory(40000447, EnemyMetis, "Metis_454");
				break;
			}
			case 60201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000430);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000431);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000432);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000433);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000434);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000435);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000436);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 60901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000437);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61001: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000438);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61101: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000439);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61201: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000440);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61301: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000441);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61401: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000442);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61501: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000443);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61601: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000444);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61701: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000445);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61801: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000446);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			case 61901: {
				EnemyMetis* pMetis2 = (EnemyMetis*)obtainActorFromFactory(40000447);
				getLordActor()->addSubGroup(pMetis2);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 493-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end
}

void Stage01_02::processFinal() {
}

Stage01_02::~Stage01_02() {

}
