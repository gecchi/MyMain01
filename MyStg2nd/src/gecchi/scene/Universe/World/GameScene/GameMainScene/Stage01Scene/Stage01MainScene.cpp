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
	DWORD dw[] = {1,11,500,511,530,560,590,620,650,1000,1011,1500,1511,2000,2011,2300,2500,2511,2900,3000,3500,3530,3560,3590,3620,3650,4000,4500,4530,4560,4590,4620,4650,4900,5000,5300,5500,6000,6500,7000,7300,7500,7530,7560,7590,7620,7650,7900,8000,8500,8530,8560,8590,8620,8650,9000,9400,9500,9900,10000,10300,10500,11000,11500,11530,11560,11590,11620,11650,12000,12300,12400,12500,12530,12560,12590,12620,12650,12900,13000,13500,14000,14400,14500,14900,15000,15300,15500,15530,15560,15590,15620,15650,16000,16500,16530,16560,16590,16620,16650,17000,17400,17500,17900,18000,18500,19000,19500,19530,19560,19590,19620,19650,20000,20500,21000,21500,22000,22500,23000,23500,24000,24500,25000,25500,26000,26500,27000,27500,28000,28500,29000,29500,30000,30500,31000,31500,32000,32500,33000,33500,34000,34500,35000,35500,36000,36500,37000,37500,38000,38500,39000,39500,40000,40500,41000,41500,42000,42500,43000,43500,44000,44500,45000,45500,46000,46500,47000,47500,48000,48500,49000,49500,50000,50500,51000,51500,52000};
	_paFrame_NextEvent = new DWORD[178];
	for (int i = 0; i < 178; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1102711, FormationPallas001, "F001_Pallas_1");
	orderActorToFactory(11027511, FormationPallas001, "F001_Pallas_2");
	orderActorToFactory(110271011, FormationPallas001, "F001_Pallas_3");
	orderActorToFactory(110271511, FormationPallas001, "F001_Pallas_4");
	orderActorToFactory(110272011, FormationPallas001, "F001_Pallas_5");
	orderActorToFactory(110272511, FormationPallas001, "F001_Pallas_6");
	orderActorToFactory(110563000, VarietyTorus001, "VarietyTorus001_7");
	orderActorToFactory(111271000, EnemyMetis, "Metis_8");
	orderActorToFactory(111271500, EnemyMetis, "Metis_9");
	orderActorToFactory(111272000, EnemyMetis, "Metis_10");
	orderActorToFactory(111272500, EnemyMetis, "Metis_11");
	orderActorToFactory(111273000, EnemyMetis, "Metis_12");
	orderActorToFactory(111471000, EnemyAstraea, "Astraea_13");
	orderActorToFactory(111672900, EnemyAstraea, "Astraea_14");
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
			case 11:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(1102711);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 500:
				orderActorToFactory(111273500, EnemyMetis, "Metis_15");
				orderActorWithDpToFactory(113473500, EnemyCeres, "Ceres_16", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 511:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(11027511);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 530:
				orderActorWithDpToFactory(113573530, EnemyCeres, "Ceres_17", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 560:
				orderActorWithDpToFactory(113673560, EnemyCeres, "Ceres_18", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 590:
				orderActorWithDpToFactory(113773590, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 620:
				orderActorWithDpToFactory(113873620, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 650:
				orderActorWithDpToFactory(113973650, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111271000));
				orderActorToFactory(111274000, EnemyMetis, "Metis_22");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111471000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(113174000, FormationIris001, "F001_Iris_23");
				break;
			case 1011:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110271011);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111271500));
				orderActorToFactory(111274500, EnemyMetis, "Metis_24");
				break;
			case 1511:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110271511);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111272000));
				orderActorToFactory(111275000, EnemyMetis, "Metis_25");
				orderActorToFactory(114175000, FormationJuno001, "F002_Juno_26");
				break;
			case 2011:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110272011);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2300:
				orderActorToFactory(112575300, EnemyAstraea, "Astraea_27");
				break;
			case 2500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111272500));
				orderActorToFactory(111275500, EnemyMetis, "Metis_28");
				break;
			case 2511:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(110272511);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111672900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 3000:
				getLordActor()->addSubGroup(obtainActorFromFactory(110563000));
				getLordActor()->addSubGroup(obtainActorFromFactory(111273000));
				orderActorToFactory(111276000, EnemyMetis, "Metis_29");
				orderActorToFactory(113276000, FormationIris002, "F002_Iris_30");
				break;
			case 3500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111273500));
				orderActorToFactory(111276500, EnemyMetis, "Metis_31");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113473500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113573530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113673560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113873620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113973650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111274000));
				orderActorToFactory(111277000, EnemyMetis, "Metis_32");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113174000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111274500));
				orderActorToFactory(111277500, EnemyMetis, "Metis_33");
				orderActorWithDpToFactory(113477500, EnemyCeres, "Ceres_34", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4530:
				orderActorWithDpToFactory(113577530, EnemyCeres, "Ceres_35", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4560:
				orderActorWithDpToFactory(113677560, EnemyCeres, "Ceres_36", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4590:
				orderActorWithDpToFactory(113777590, EnemyCeres, "Ceres_37", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4620:
				orderActorWithDpToFactory(113877620, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4650:
				orderActorWithDpToFactory(113977650, EnemyCeres, "Ceres_39", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4900:
				orderActorToFactory(111677900, EnemyAstraea, "Astraea_40");
				break;
			case 5000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111275000));
				orderActorToFactory(111278000, EnemyMetis, "Metis_41");
				orderActorToFactory(113178000, FormationIris001, "F001_Iris_42");
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(114175000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112575300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 5500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111275500));
				orderActorToFactory(111278500, EnemyMetis, "Metis_43");
				break;
			case 6000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111276000));
				orderActorToFactory(111279000, EnemyMetis, "Metis_44");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(113276000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111276500));
				orderActorToFactory(111279500, EnemyMetis, "Metis_45");
				break;
			case 7000:
				orderActorToFactory(1106610000, VarietyTorus002, "VarietyTorus002_46");
				orderActorToFactory(1107610000, VarietyTorus003, "VarietyTorus003_47");
				getLordActor()->addSubGroup(obtainActorFromFactory(111277000));
				orderActorToFactory(1112710000, EnemyMetis, "Metis_48");
				orderActorToFactory(1132710000, FormationIris002, "F002_Iris_49");
				break;
			case 7300:
				orderActorToFactory(1125710300, EnemyAstraea, "Astraea_50");
				break;
			case 7500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111277500));
				orderActorToFactory(1112710500, EnemyMetis, "Metis_51");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113477500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113577530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113677560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113877620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113977650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111677900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 8000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111278000));
				orderActorToFactory(1112711000, EnemyMetis, "Metis_52");
				orderActorToFactory(1128711000, EnemyAstraea, "Astraea_53");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113178000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111278500));
				orderActorToFactory(1112711500, EnemyMetis, "Metis_54");
				orderActorWithDpToFactory(1134711500, EnemyCeres, "Ceres_55", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8530:
				orderActorWithDpToFactory(1135711530, EnemyCeres, "Ceres_56", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8560:
				orderActorWithDpToFactory(1136711560, EnemyCeres, "Ceres_57", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8590:
				orderActorWithDpToFactory(1137711590, EnemyCeres, "Ceres_58", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8620:
				orderActorWithDpToFactory(1138711620, EnemyCeres, "Ceres_59", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8650:
				orderActorWithDpToFactory(1139711650, EnemyCeres, "Ceres_60", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111279000));
				orderActorToFactory(1112712000, EnemyMetis, "Metis_61");
				orderActorToFactory(1131712000, FormationIris001, "F001_Iris_62");
				break;
			case 9400:
				orderActorToFactory(1121712400, EnemyAstraea, "Astraea_63");
				break;
			case 9500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111279500));
				orderActorToFactory(1112712500, EnemyMetis, "Metis_64");
				break;
			case 9900:
				orderActorToFactory(1116712900, EnemyAstraea, "Astraea_65");
				break;
			case 10000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1106610000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1107610000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1112710000));
				orderActorToFactory(1112713000, EnemyMetis, "Metis_66");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1132710000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1141713000, FormationJuno001, "F002_Juno_67");
				break;
			case 10300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125710300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 10500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112710500));
				orderActorToFactory(1112713500, EnemyMetis, "Metis_68");
				break;
			case 11000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112711000));
				orderActorToFactory(1112714000, EnemyMetis, "Metis_69");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1128711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1132714000, FormationIris002, "F002_Iris_70");
				break;
			case 11500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112711500));
				orderActorToFactory(1112714500, EnemyMetis, "Metis_71");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134711500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135711530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136711560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137711590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138711620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139711650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112712000));
				orderActorToFactory(1112715000, EnemyMetis, "Metis_72");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1131712000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12300:
				orderActorToFactory(1125715300, EnemyAstraea, "Astraea_73");
				break;
			case 12400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121712400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 12500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112712500));
				orderActorToFactory(1112715500, EnemyMetis, "Metis_74");
				orderActorWithDpToFactory(1134715500, EnemyCeres, "Ceres_75", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12530:
				orderActorWithDpToFactory(1135715530, EnemyCeres, "Ceres_76", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12560:
				orderActorWithDpToFactory(1136715560, EnemyCeres, "Ceres_77", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12590:
				orderActorWithDpToFactory(1137715590, EnemyCeres, "Ceres_78", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12620:
				orderActorWithDpToFactory(1138715620, EnemyCeres, "Ceres_79", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12650:
				orderActorWithDpToFactory(1139715650, EnemyCeres, "Ceres_80", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116712900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 13000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112713000));
				orderActorToFactory(1112716000, EnemyMetis, "Metis_81");
				orderActorToFactory(1128716000, EnemyAstraea, "Astraea_82");
				orderActorToFactory(1131716000, FormationIris001, "F001_Iris_83");
				{
				FormationJuno001* pFormationActor = (FormationJuno001*)obtainActorFromFactory(1141713000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 13500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112713500));
				orderActorToFactory(1112716500, EnemyMetis, "Metis_84");
				break;
			case 14000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112714000));
				orderActorToFactory(1112717000, EnemyMetis, "Metis_85");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1132714000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 14400:
				orderActorToFactory(1121717400, EnemyAstraea, "Astraea_86");
				break;
			case 14500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112714500));
				orderActorToFactory(1112717500, EnemyMetis, "Metis_87");
				break;
			case 14900:
				orderActorToFactory(1116717900, EnemyAstraea, "Astraea_88");
				break;
			case 15000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112715000));
				orderActorToFactory(1112718000, EnemyMetis, "Metis_89");
				orderActorToFactory(1132718000, FormationIris002, "F002_Iris_90");
				break;
			case 15300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1125715300);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 15500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112715500));
				orderActorToFactory(1112718500, EnemyMetis, "Metis_91");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134715500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135715530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136715560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137715590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138715620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 15650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139715650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112716000));
				orderActorToFactory(1112719000, EnemyMetis, "Metis_92");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1128716000);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1131716000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112716500));
				orderActorToFactory(1112719500, EnemyMetis, "Metis_93");
				orderActorWithDpToFactory(1134719500, EnemyCeres, "Ceres_94", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16530:
				orderActorWithDpToFactory(1135719530, EnemyCeres, "Ceres_95", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16560:
				orderActorWithDpToFactory(1136719560, EnemyCeres, "Ceres_96", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16590:
				orderActorWithDpToFactory(1137719590, EnemyCeres, "Ceres_97", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16620:
				orderActorWithDpToFactory(1138719620, EnemyCeres, "Ceres_98", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16650:
				orderActorWithDpToFactory(1139719650, EnemyCeres, "Ceres_99", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17000:
				orderActorToFactory(1109620000, VarietyTorus004, "VarietyTorus004_100");
				getLordActor()->addSubGroup(obtainActorFromFactory(1112717000));
				orderActorToFactory(1112720000, EnemyMetis, "Metis_101");
				orderActorToFactory(1131720000, FormationIris001, "F001_Iris_102");
				break;
			case 17400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121717400);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 17500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112717500));
				orderActorToFactory(1112720500, EnemyMetis, "Metis_103");
				break;
			case 17900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116717900);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 18000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112718000));
				orderActorToFactory(1112721000, EnemyMetis, "Metis_104");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1132718000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112718500));
				orderActorToFactory(1112721500, EnemyMetis, "Metis_105");
				break;
			case 19000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112719000));
				orderActorToFactory(1112722000, EnemyMetis, "Metis_106");
				break;
			case 19500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112719500));
				orderActorToFactory(1112722500, EnemyMetis, "Metis_107");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134719500);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135719530);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136719560);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137719590);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138719620);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139719650);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 20000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1109620000));
				getLordActor()->addSubGroup(obtainActorFromFactory(1112720000));
				orderActorToFactory(1112723000, EnemyMetis, "Metis_108");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1131720000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 20500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112720500));
				orderActorToFactory(1112723500, EnemyMetis, "Metis_109");
				break;
			case 21000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112721000));
				orderActorToFactory(1112724000, EnemyMetis, "Metis_110");
				break;
			case 21500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112721500));
				orderActorToFactory(1112724500, EnemyMetis, "Metis_111");
				break;
			case 22000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112722000));
				orderActorToFactory(1112725000, EnemyMetis, "Metis_112");
				break;
			case 22500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112722500));
				orderActorToFactory(1112725500, EnemyMetis, "Metis_113");
				break;
			case 23000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112723000));
				orderActorToFactory(1112726000, EnemyMetis, "Metis_114");
				break;
			case 23500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112723500));
				orderActorToFactory(1112726500, EnemyMetis, "Metis_115");
				break;
			case 24000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112724000));
				orderActorToFactory(1112727000, EnemyMetis, "Metis_116");
				break;
			case 24500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112724500));
				orderActorToFactory(1112727500, EnemyMetis, "Metis_117");
				break;
			case 25000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112725000));
				orderActorToFactory(1112728000, EnemyMetis, "Metis_118");
				break;
			case 25500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112725500));
				orderActorToFactory(1112728500, EnemyMetis, "Metis_119");
				break;
			case 26000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112726000));
				orderActorToFactory(1112729000, EnemyMetis, "Metis_120");
				break;
			case 26500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112726500));
				orderActorToFactory(1112729500, EnemyMetis, "Metis_121");
				break;
			case 27000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112727000));
				orderActorToFactory(1112730000, EnemyMetis, "Metis_122");
				break;
			case 27500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112727500));
				orderActorToFactory(1112730500, EnemyMetis, "Metis_123");
				break;
			case 28000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112728000));
				orderActorToFactory(1112731000, EnemyMetis, "Metis_124");
				break;
			case 28500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112728500));
				orderActorToFactory(1112731500, EnemyMetis, "Metis_125");
				break;
			case 29000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112729000));
				orderActorToFactory(1112732000, EnemyMetis, "Metis_126");
				break;
			case 29500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112729500));
				orderActorToFactory(1112732500, EnemyMetis, "Metis_127");
				break;
			case 30000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112730000));
				orderActorToFactory(1112733000, EnemyMetis, "Metis_128");
				break;
			case 30500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112730500));
				orderActorToFactory(1112733500, EnemyMetis, "Metis_129");
				break;
			case 31000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112731000));
				orderActorToFactory(1112734000, EnemyMetis, "Metis_130");
				break;
			case 31500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112731500));
				orderActorToFactory(1112734500, EnemyMetis, "Metis_131");
				break;
			case 32000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112732000));
				orderActorToFactory(1112735000, EnemyMetis, "Metis_132");
				break;
			case 32500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112732500));
				orderActorToFactory(1112735500, EnemyMetis, "Metis_133");
				break;
			case 33000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112733000));
				orderActorToFactory(1112736000, EnemyMetis, "Metis_134");
				break;
			case 33500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112733500));
				orderActorToFactory(1112736500, EnemyMetis, "Metis_135");
				break;
			case 34000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112734000));
				orderActorToFactory(1112737000, EnemyMetis, "Metis_136");
				break;
			case 34500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112734500));
				orderActorToFactory(1112737500, EnemyMetis, "Metis_137");
				break;
			case 35000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112735000));
				orderActorToFactory(1112738000, EnemyMetis, "Metis_138");
				break;
			case 35500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112735500));
				orderActorToFactory(1112738500, EnemyMetis, "Metis_139");
				break;
			case 36000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112736000));
				orderActorToFactory(1112739000, EnemyMetis, "Metis_140");
				break;
			case 36500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112736500));
				orderActorToFactory(1112739500, EnemyMetis, "Metis_141");
				break;
			case 37000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112737000));
				orderActorToFactory(1112740000, EnemyMetis, "Metis_142");
				break;
			case 37500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112737500));
				orderActorToFactory(1112740500, EnemyMetis, "Metis_143");
				break;
			case 38000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112738000));
				orderActorToFactory(1112741000, EnemyMetis, "Metis_144");
				break;
			case 38500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112738500));
				orderActorToFactory(1112741500, EnemyMetis, "Metis_145");
				break;
			case 39000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112739000));
				orderActorToFactory(1112742000, EnemyMetis, "Metis_146");
				break;
			case 39500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112739500));
				orderActorToFactory(1112742500, EnemyMetis, "Metis_147");
				break;
			case 40000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112740000));
				orderActorToFactory(1112743000, EnemyMetis, "Metis_148");
				break;
			case 40500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112740500));
				orderActorToFactory(1112743500, EnemyMetis, "Metis_149");
				break;
			case 41000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112741000));
				orderActorToFactory(1112744000, EnemyMetis, "Metis_150");
				break;
			case 41500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112741500));
				orderActorToFactory(1112744500, EnemyMetis, "Metis_151");
				break;
			case 42000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112742000));
				orderActorToFactory(1112745000, EnemyMetis, "Metis_152");
				break;
			case 42500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112742500));
				orderActorToFactory(1112745500, EnemyMetis, "Metis_153");
				break;
			case 43000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112743000));
				orderActorToFactory(1112746000, EnemyMetis, "Metis_154");
				break;
			case 43500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112743500));
				orderActorToFactory(1112746500, EnemyMetis, "Metis_155");
				break;
			case 44000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112744000));
				orderActorToFactory(1112747000, EnemyMetis, "Metis_156");
				break;
			case 44500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112744500));
				orderActorToFactory(1112747500, EnemyMetis, "Metis_157");
				break;
			case 45000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112745000));
				orderActorToFactory(1112748000, EnemyMetis, "Metis_158");
				break;
			case 45500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112745500));
				orderActorToFactory(1112748500, EnemyMetis, "Metis_159");
				break;
			case 46000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112746000));
				orderActorToFactory(1112749000, EnemyMetis, "Metis_160");
				break;
			case 46500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112746500));
				orderActorToFactory(1112749500, EnemyMetis, "Metis_161");
				break;
			case 47000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112747000));
				orderActorToFactory(1112750000, EnemyMetis, "Metis_162");
				break;
			case 47500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112747500));
				orderActorToFactory(1112750500, EnemyMetis, "Metis_163");
				break;
			case 48000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112748000));
				orderActorToFactory(1112751000, EnemyMetis, "Metis_164");
				break;
			case 48500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112748500));
				orderActorToFactory(1112751500, EnemyMetis, "Metis_165");
				break;
			case 49000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112749000));
				orderActorToFactory(1112752000, EnemyMetis, "Metis_166");
				break;
			case 49500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112749500));
				break;
			case 50000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112750000));
				break;
			case 50500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112750500));
				break;
			case 51000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112751000));
				break;
			case 51500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112751500));
				break;
			case 52000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112752000));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 178-1 ? _iCnt_Event+1 : _iCnt_Event);
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
