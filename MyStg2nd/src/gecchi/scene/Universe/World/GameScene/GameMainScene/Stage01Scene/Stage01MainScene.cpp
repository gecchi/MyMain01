#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW GgafActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行う。
    // gen01 start
	DWORD dw[] = {1,100,500,530,560,590,620,650,900,1000,1300,1500,1700,2000,2300,2500,2900,3000,3500,3530,3560,3590,3620,3650,4000,4500,4530,4560,4590,4620,4650,4900,5000,5300,5500,6000,6500,7000,7300,7500,7530,7560,7590,7620,7650,7900,8000,8500,8530,8560,8590,8620,8650,9000,9400,9500,9900,10000,10300,10500,11000,11500,11530,11560,11590,11620,11650,12000,12300,12400,12500,12530,12560,12590,12620,12650,12900,13000,13500,14000,14400,14500,14900,15000,15300,15500,15530,15560,15590,15620,15650,16000,16500,16530,16560,16590,16620,16650,17000,17400,17500,17900,18000,18500,19000,19500,19530,19560,19590,19620,19650,20000,20500,21000,21500,22000,22500,23000,23500,24000,24500,25000,25500,26000,26500,27000,27500,28000,28500,29000,29500,30000,30500,31000,31500,32000,32500,33000,33500,34000,34500,35000,35500,36000,36500,37000,37500,38000,38500,39000,39500,40000,40500,41000,41500,42000,42500,43000,43500,44000,44500,45000,45500,46000,46500,47000,47500,48000,48500,49000,49500,50000,50500,51000,51500,52000};
	_paFrame_NextEvent = new DWORD[176];
	for (int i = 0; i < 176; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11027100, FormationPallas001a, "F001a_Pallas_1");
	orderActorToFactory(11037500, FormationPallas001b, "F001b_Pallas_2");
	orderActorToFactory(11047900, FormationPallas001c, "F001c_Pallas_3");
	orderActorToFactory(110571300, FormationPallas001d, "F001d_Pallas_4");
	orderActorToFactory(110671700, FormationPallas001a, "F001a_Pallas_5");
	orderActorToFactory(110771700, FormationPallas001d, "F001d_Pallas_6");
	orderActorToFactory(110872000, FormationPallas001b, "F001a_Pallas_7");
	orderActorToFactory(110972000, FormationPallas001c, "F001d_Pallas_8");
	orderActorToFactory(111163000, VarietyTorus001, "VarietyTorus001_9");
	orderActorToFactory(111871000, EnemyMetis, "Metis_10");
	orderActorToFactory(111871500, EnemyMetis, "Metis_11");
	orderActorToFactory(111872000, EnemyMetis, "Metis_12");
	orderActorToFactory(111872500, EnemyMetis, "Metis_13");
	orderActorToFactory(111873000, EnemyMetis, "Metis_14");
	orderActorToFactory(112071000, EnemyAstraea, "Astraea_15");
	orderActorToFactory(112272900, EnemyAstraea, "Astraea_16");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 1:
				break;
			case 100:
				{
				FormationPallas001a* pFormationActor = (FormationPallas001a*)obtainActorFromFactory(11027100);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 500:
				{
				FormationPallas001b* pFormationActor = (FormationPallas001b*)obtainActorFromFactory(11037500);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(111873500, EnemyMetis, "Metis_17");
				orderActorWithDpToFactory(114073500, EnemyCeres, "Ceres_18", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 530:
				orderActorWithDpToFactory(114173530, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 560:
				orderActorWithDpToFactory(114273560, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 590:
				orderActorWithDpToFactory(114373590, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 620:
				orderActorWithDpToFactory(114473620, EnemyCeres, "Ceres_22", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 650:
				orderActorWithDpToFactory(114573650, EnemyCeres, "Ceres_23", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 900:
				{
				FormationPallas001c* pFormationActor = (FormationPallas001c*)obtainActorFromFactory(11047900);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111871000));
				orderActorToFactory(111874000, EnemyMetis, "Metis_24");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112071000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(113774000, FormationIris001, "F001_Iris_25");
				break;
			case 1300:
				{
				FormationPallas001d* pFormationActor = (FormationPallas001d*)obtainActorFromFactory(110571300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111871500));
				orderActorToFactory(111874500, EnemyMetis, "Metis_26");
				break;
			case 1700:
				{
				FormationPallas001a* pFormationActor = (FormationPallas001a*)obtainActorFromFactory(110671700);
				getLordActor()->addSubGroup(pFormationActor);
				}
				{
				FormationPallas001d* pFormationActor = (FormationPallas001d*)obtainActorFromFactory(110771700);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2000:
				{
				FormationPallas001b* pFormationActor = (FormationPallas001b*)obtainActorFromFactory(110872000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				{
				FormationPallas001c* pFormationActor = (FormationPallas001c*)obtainActorFromFactory(110972000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				getLordActor()->addSubGroup(obtainActorFromFactory(111872000));
				orderActorToFactory(111875000, EnemyMetis, "Metis_27");
				orderActorToFactory(114775000, FormationJuno001, "F002_Juno_28");
				break;
			case 2300:
				orderActorToFactory(113175300, EnemyAstraea, "Astraea_29");
				break;
			case 2500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111872500));
				orderActorToFactory(111875500, EnemyMetis, "Metis_30");
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112272900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 3000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111163000));
				getLordActor()->addSubGroup(obtainActorFromFactory(111873000));
				orderActorToFactory(111876000, EnemyMetis, "Metis_31");
				orderActorToFactory(113876000, FormationIris002, "F002_Iris_32");
				break;
			case 3500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111873500));
				orderActorToFactory(111876500, EnemyMetis, "Metis_33");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114073500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114173530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114273560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114373590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114473620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114573650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111874000));
				orderActorToFactory(111877000, EnemyMetis, "Metis_34");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113774000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111874500));
				orderActorToFactory(111877500, EnemyMetis, "Metis_35");
				orderActorWithDpToFactory(114077500, EnemyCeres, "Ceres_36", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4530:
				orderActorWithDpToFactory(114177530, EnemyCeres, "Ceres_37", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4560:
				orderActorWithDpToFactory(114277560, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4590:
				orderActorWithDpToFactory(114377590, EnemyCeres, "Ceres_39", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4620:
				orderActorWithDpToFactory(114477620, EnemyCeres, "Ceres_40", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4650:
				orderActorWithDpToFactory(114577650, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4900:
				orderActorToFactory(112277900, EnemyAstraea, "Astraea_42");
				break;
			case 5000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111875000));
				orderActorToFactory(111878000, EnemyMetis, "Metis_43");
				orderActorToFactory(113778000, FormationIris001, "F001_Iris_44");
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(114775000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(113175300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 5500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111875500));
				orderActorToFactory(111878500, EnemyMetis, "Metis_45");
				break;
			case 6000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111876000));
				orderActorToFactory(111879000, EnemyMetis, "Metis_46");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(113876000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111876500));
				orderActorToFactory(111879500, EnemyMetis, "Metis_47");
				break;
			case 7000:
				orderActorToFactory(1112610000, VarietyTorus002, "VarietyTorus002_48");
				orderActorToFactory(1113610000, VarietyTorus003, "VarietyTorus003_49");
				getLordActor()->addSubGroup(obtainActorFromFactory(111877000));
				orderActorToFactory(1118710000, EnemyMetis, "Metis_50");
				orderActorToFactory(1138710000, FormationIris002, "F002_Iris_51");
				break;
			case 7300:
				orderActorToFactory(1131710300, EnemyAstraea, "Astraea_52");
				break;
			case 7500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111877500));
				orderActorToFactory(1118710500, EnemyMetis, "Metis_53");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114077500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114177530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114277560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114377590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114477620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114577650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112277900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 8000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111878000));
				orderActorToFactory(1118711000, EnemyMetis, "Metis_54");
				orderActorToFactory(1134711000, EnemyAstraea, "Astraea_55");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113778000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111878500));
				orderActorToFactory(1118711500, EnemyMetis, "Metis_56");
				orderActorWithDpToFactory(1140711500, EnemyCeres, "Ceres_57", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8530:
				orderActorWithDpToFactory(1141711530, EnemyCeres, "Ceres_58", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8560:
				orderActorWithDpToFactory(1142711560, EnemyCeres, "Ceres_59", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8590:
				orderActorWithDpToFactory(1143711590, EnemyCeres, "Ceres_60", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8620:
				orderActorWithDpToFactory(1144711620, EnemyCeres, "Ceres_61", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8650:
				orderActorWithDpToFactory(1145711650, EnemyCeres, "Ceres_62", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111879000));
				orderActorToFactory(1118712000, EnemyMetis, "Metis_63");
				orderActorToFactory(1137712000, FormationIris001, "F001_Iris_64");
				break;
			case 9400:
				orderActorToFactory(1127712400, EnemyAstraea, "Astraea_65");
				break;
			case 9500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111879500));
				orderActorToFactory(1118712500, EnemyMetis, "Metis_66");
				break;
			case 9900:
				orderActorToFactory(1122712900, EnemyAstraea, "Astraea_67");
				break;
			case 10000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112610000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1113610000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1118710000));
				orderActorToFactory(1118713000, EnemyMetis, "Metis_68");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138710000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1147713000, FormationJuno001, "F002_Juno_69");
				break;
			case 10300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1131710300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 10500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118710500));
				orderActorToFactory(1118713500, EnemyMetis, "Metis_70");
				break;
			case 11000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118711000));
				orderActorToFactory(1118714000, EnemyMetis, "Metis_71");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1134711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1138714000, FormationIris002, "F002_Iris_72");
				break;
			case 11500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118711500));
				orderActorToFactory(1118714500, EnemyMetis, "Metis_73");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140711500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141711530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142711560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143711590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144711620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145711650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118712000));
				orderActorToFactory(1118715000, EnemyMetis, "Metis_74");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137712000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12300:
				orderActorToFactory(1131715300, EnemyAstraea, "Astraea_75");
				break;
			case 12400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1127712400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 12500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118712500));
				orderActorToFactory(1118715500, EnemyMetis, "Metis_76");
				orderActorWithDpToFactory(1140715500, EnemyCeres, "Ceres_77", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12530:
				orderActorWithDpToFactory(1141715530, EnemyCeres, "Ceres_78", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12560:
				orderActorWithDpToFactory(1142715560, EnemyCeres, "Ceres_79", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12590:
				orderActorWithDpToFactory(1143715590, EnemyCeres, "Ceres_80", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12620:
				orderActorWithDpToFactory(1144715620, EnemyCeres, "Ceres_81", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12650:
				orderActorWithDpToFactory(1145715650, EnemyCeres, "Ceres_82", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1122712900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 13000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118713000));
				orderActorToFactory(1118716000, EnemyMetis, "Metis_83");
				orderActorToFactory(1134716000, EnemyAstraea, "Astraea_84");
				orderActorToFactory(1137716000, FormationIris001, "F001_Iris_85");
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(1147713000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 13500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118713500));
				orderActorToFactory(1118716500, EnemyMetis, "Metis_86");
				break;
			case 14000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118714000));
				orderActorToFactory(1118717000, EnemyMetis, "Metis_87");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138714000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 14400:
				orderActorToFactory(1127717400, EnemyAstraea, "Astraea_88");
				break;
			case 14500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118714500));
				orderActorToFactory(1118717500, EnemyMetis, "Metis_89");
				break;
			case 14900:
				orderActorToFactory(1122717900, EnemyAstraea, "Astraea_90");
				break;
			case 15000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118715000));
				orderActorToFactory(1118718000, EnemyMetis, "Metis_91");
				orderActorToFactory(1138718000, FormationIris002, "F002_Iris_92");
				break;
			case 15300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1131715300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 15500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118715500));
				orderActorToFactory(1118718500, EnemyMetis, "Metis_93");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140715500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141715530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142715560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143715590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144715620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145715650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118716000));
				orderActorToFactory(1118719000, EnemyMetis, "Metis_94");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1134716000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137716000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118716500));
				orderActorToFactory(1118719500, EnemyMetis, "Metis_95");
				orderActorWithDpToFactory(1140719500, EnemyCeres, "Ceres_96", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16530:
				orderActorWithDpToFactory(1141719530, EnemyCeres, "Ceres_97", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16560:
				orderActorWithDpToFactory(1142719560, EnemyCeres, "Ceres_98", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16590:
				orderActorWithDpToFactory(1143719590, EnemyCeres, "Ceres_99", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16620:
				orderActorWithDpToFactory(1144719620, EnemyCeres, "Ceres_100", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16650:
				orderActorWithDpToFactory(1145719650, EnemyCeres, "Ceres_101", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17000:
				orderActorToFactory(1115620000, VarietyTorus004, "VarietyTorus004_102");
				getLordActor()->addSubGroup(obtainActorFromFactory(1118717000));
				orderActorToFactory(1118720000, EnemyMetis, "Metis_103");
				orderActorToFactory(1137720000, FormationIris001, "F001_Iris_104");
				break;
			case 17400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1127717400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 17500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118717500));
				orderActorToFactory(1118720500, EnemyMetis, "Metis_105");
				break;
			case 17900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1122717900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 18000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118718000));
				orderActorToFactory(1118721000, EnemyMetis, "Metis_106");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1138718000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118718500));
				orderActorToFactory(1118721500, EnemyMetis, "Metis_107");
				break;
			case 19000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118719000));
				orderActorToFactory(1118722000, EnemyMetis, "Metis_108");
				break;
			case 19500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118719500));
				orderActorToFactory(1118722500, EnemyMetis, "Metis_109");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140719500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141719530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142719560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1143719590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1144719620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1145719650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 20000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1115620000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1118720000));
				orderActorToFactory(1118723000, EnemyMetis, "Metis_110");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1137720000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 20500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118720500));
				orderActorToFactory(1118723500, EnemyMetis, "Metis_111");
				break;
			case 21000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118721000));
				orderActorToFactory(1118724000, EnemyMetis, "Metis_112");
				break;
			case 21500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118721500));
				orderActorToFactory(1118724500, EnemyMetis, "Metis_113");
				break;
			case 22000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118722000));
				orderActorToFactory(1118725000, EnemyMetis, "Metis_114");
				break;
			case 22500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118722500));
				orderActorToFactory(1118725500, EnemyMetis, "Metis_115");
				break;
			case 23000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118723000));
				orderActorToFactory(1118726000, EnemyMetis, "Metis_116");
				break;
			case 23500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118723500));
				orderActorToFactory(1118726500, EnemyMetis, "Metis_117");
				break;
			case 24000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118724000));
				orderActorToFactory(1118727000, EnemyMetis, "Metis_118");
				break;
			case 24500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118724500));
				orderActorToFactory(1118727500, EnemyMetis, "Metis_119");
				break;
			case 25000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118725000));
				orderActorToFactory(1118728000, EnemyMetis, "Metis_120");
				break;
			case 25500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118725500));
				orderActorToFactory(1118728500, EnemyMetis, "Metis_121");
				break;
			case 26000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118726000));
				orderActorToFactory(1118729000, EnemyMetis, "Metis_122");
				break;
			case 26500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118726500));
				orderActorToFactory(1118729500, EnemyMetis, "Metis_123");
				break;
			case 27000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118727000));
				orderActorToFactory(1118730000, EnemyMetis, "Metis_124");
				break;
			case 27500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118727500));
				orderActorToFactory(1118730500, EnemyMetis, "Metis_125");
				break;
			case 28000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118728000));
				orderActorToFactory(1118731000, EnemyMetis, "Metis_126");
				break;
			case 28500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118728500));
				orderActorToFactory(1118731500, EnemyMetis, "Metis_127");
				break;
			case 29000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118729000));
				orderActorToFactory(1118732000, EnemyMetis, "Metis_128");
				break;
			case 29500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118729500));
				orderActorToFactory(1118732500, EnemyMetis, "Metis_129");
				break;
			case 30000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118730000));
				orderActorToFactory(1118733000, EnemyMetis, "Metis_130");
				break;
			case 30500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118730500));
				orderActorToFactory(1118733500, EnemyMetis, "Metis_131");
				break;
			case 31000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118731000));
				orderActorToFactory(1118734000, EnemyMetis, "Metis_132");
				break;
			case 31500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118731500));
				orderActorToFactory(1118734500, EnemyMetis, "Metis_133");
				break;
			case 32000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118732000));
				orderActorToFactory(1118735000, EnemyMetis, "Metis_134");
				break;
			case 32500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118732500));
				orderActorToFactory(1118735500, EnemyMetis, "Metis_135");
				break;
			case 33000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118733000));
				orderActorToFactory(1118736000, EnemyMetis, "Metis_136");
				break;
			case 33500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118733500));
				orderActorToFactory(1118736500, EnemyMetis, "Metis_137");
				break;
			case 34000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118734000));
				orderActorToFactory(1118737000, EnemyMetis, "Metis_138");
				break;
			case 34500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118734500));
				orderActorToFactory(1118737500, EnemyMetis, "Metis_139");
				break;
			case 35000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118735000));
				orderActorToFactory(1118738000, EnemyMetis, "Metis_140");
				break;
			case 35500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118735500));
				orderActorToFactory(1118738500, EnemyMetis, "Metis_141");
				break;
			case 36000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118736000));
				orderActorToFactory(1118739000, EnemyMetis, "Metis_142");
				break;
			case 36500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118736500));
				orderActorToFactory(1118739500, EnemyMetis, "Metis_143");
				break;
			case 37000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118737000));
				orderActorToFactory(1118740000, EnemyMetis, "Metis_144");
				break;
			case 37500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118737500));
				orderActorToFactory(1118740500, EnemyMetis, "Metis_145");
				break;
			case 38000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118738000));
				orderActorToFactory(1118741000, EnemyMetis, "Metis_146");
				break;
			case 38500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118738500));
				orderActorToFactory(1118741500, EnemyMetis, "Metis_147");
				break;
			case 39000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118739000));
				orderActorToFactory(1118742000, EnemyMetis, "Metis_148");
				break;
			case 39500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118739500));
				orderActorToFactory(1118742500, EnemyMetis, "Metis_149");
				break;
			case 40000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118740000));
				orderActorToFactory(1118743000, EnemyMetis, "Metis_150");
				break;
			case 40500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118740500));
				orderActorToFactory(1118743500, EnemyMetis, "Metis_151");
				break;
			case 41000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118741000));
				orderActorToFactory(1118744000, EnemyMetis, "Metis_152");
				break;
			case 41500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118741500));
				orderActorToFactory(1118744500, EnemyMetis, "Metis_153");
				break;
			case 42000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118742000));
				orderActorToFactory(1118745000, EnemyMetis, "Metis_154");
				break;
			case 42500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118742500));
				orderActorToFactory(1118745500, EnemyMetis, "Metis_155");
				break;
			case 43000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118743000));
				orderActorToFactory(1118746000, EnemyMetis, "Metis_156");
				break;
			case 43500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118743500));
				orderActorToFactory(1118746500, EnemyMetis, "Metis_157");
				break;
			case 44000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118744000));
				orderActorToFactory(1118747000, EnemyMetis, "Metis_158");
				break;
			case 44500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118744500));
				orderActorToFactory(1118747500, EnemyMetis, "Metis_159");
				break;
			case 45000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118745000));
				orderActorToFactory(1118748000, EnemyMetis, "Metis_160");
				break;
			case 45500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118745500));
				orderActorToFactory(1118748500, EnemyMetis, "Metis_161");
				break;
			case 46000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118746000));
				orderActorToFactory(1118749000, EnemyMetis, "Metis_162");
				break;
			case 46500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118746500));
				orderActorToFactory(1118749500, EnemyMetis, "Metis_163");
				break;
			case 47000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118747000));
				orderActorToFactory(1118750000, EnemyMetis, "Metis_164");
				break;
			case 47500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118747500));
				orderActorToFactory(1118750500, EnemyMetis, "Metis_165");
				break;
			case 48000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118748000));
				orderActorToFactory(1118751000, EnemyMetis, "Metis_166");
				break;
			case 48500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118748500));
				orderActorToFactory(1118751500, EnemyMetis, "Metis_167");
				break;
			case 49000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118749000));
				orderActorToFactory(1118752000, EnemyMetis, "Metis_168");
				break;
			case 49500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118749500));
				break;
			case 50000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118750000));
				break;
			case 50500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118750500));
				break;
			case 51000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118751000));
				break;
			case 51500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118751500));
				break;
			case 52000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1118752000));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 176-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inactivateTree(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEWからprocessBehaviorまでの間に強制終了された場合、
    //_pDispatcherはどのツリーにも所属していない。
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcherが未所属のため独自delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
