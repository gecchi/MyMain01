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
	DWORD dw[] = {1,11,500,511,1000,1011,1500,1511,2000,2011,2300,2500,2511,2900,3000,3500,4000,4500,4900,5000,5300,5500,6000,6500,7000,7300,7500,7900,8000,8500,9000,9400,9500,9900,10000,10300,10500,11000,11500,12000,12300,12400,12500,12900,13000,13500,14000,14400,14500,14900,15000,15300,15500,16000,16500,17000,17400,17500,17900,18000,18500,19000,19500,20000,20500,21000,21500,22000,22500,23000,23500,24000,24500,25000,25500,26000,26500,27000,27500,28000,28500,29000,29500,30000,30500,31000,31500,32000};
	_paFrame_NextEvent = new DWORD[88];
	for (int i = 0; i < 88; i++) {
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
	orderActorWithDpToFactory(113473000, EnemyCeres, "Ceres_15", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113573000, EnemyCeres, "Ceres_16", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113673000, EnemyCeres, "Ceres_17", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113773000, EnemyCeres, "Ceres_18", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113873000, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113973000, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorToFactory(111273500, EnemyMetis, "Metis_21");
				break;
			case 511:
				{
				FormationPallas001* pFormationActor = (FormationPallas001*)obtainActorFromFactory(11027511);
				getLordActor()->addSubGroup(pFormationActor);
				}
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
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113473000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113573000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113673000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113873000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113973000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 3500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111273500));
				orderActorToFactory(111276500, EnemyMetis, "Metis_31");
				break;
			case 4000:
				getLordActor()->addSubGroup(obtainActorFromFactory(111274000));
				orderActorToFactory(111277000, EnemyMetis, "Metis_32");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(113174000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorWithDpToFactory(113477000, EnemyCeres, "Ceres_33", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(113577000, EnemyCeres, "Ceres_34", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(113677000, EnemyCeres, "Ceres_35", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(113777000, EnemyCeres, "Ceres_36", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(113877000, EnemyCeres, "Ceres_37", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(113977000, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111274500));
				orderActorToFactory(111277500, EnemyMetis, "Metis_39");
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
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113477000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113577000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113677000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113877000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113977000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 7300:
				orderActorToFactory(1125710300, EnemyAstraea, "Astraea_50");
				break;
			case 7500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111277500));
				orderActorToFactory(1112710500, EnemyMetis, "Metis_51");
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
				orderActorWithDpToFactory(1134711000, EnemyCeres, "Ceres_54", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1135711000, EnemyCeres, "Ceres_55", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1136711000, EnemyCeres, "Ceres_56", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1137711000, EnemyCeres, "Ceres_57", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1138711000, EnemyCeres, "Ceres_58", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1139711000, EnemyCeres, "Ceres_59", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8500:
				getLordActor()->addSubGroup(obtainActorFromFactory(111278500));
				orderActorToFactory(1112711500, EnemyMetis, "Metis_60");
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
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139711000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 11500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112711500));
				orderActorToFactory(1112714500, EnemyMetis, "Metis_71");
				break;
			case 12000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112712000));
				orderActorToFactory(1112715000, EnemyMetis, "Metis_72");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1131712000);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorWithDpToFactory(1134715000, EnemyCeres, "Ceres_73", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1135715000, EnemyCeres, "Ceres_74", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1136715000, EnemyCeres, "Ceres_75", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1137715000, EnemyCeres, "Ceres_76", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1138715000, EnemyCeres, "Ceres_77", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1139715000, EnemyCeres, "Ceres_78", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12300:
				orderActorToFactory(1125715300, EnemyAstraea, "Astraea_79");
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
				orderActorToFactory(1112715500, EnemyMetis, "Metis_80");
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
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139715000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
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
				orderActorWithDpToFactory(1134719000, EnemyCeres, "Ceres_93", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1135719000, EnemyCeres, "Ceres_94", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1136719000, EnemyCeres, "Ceres_95", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1137719000, EnemyCeres, "Ceres_96", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1138719000, EnemyCeres, "Ceres_97", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				orderActorWithDpToFactory(1139719000, EnemyCeres, "Ceres_98", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112716500));
				orderActorToFactory(1112719500, EnemyMetis, "Metis_99");
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
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1134719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1135719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1136719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139719000);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112719500));
				orderActorToFactory(1112722500, EnemyMetis, "Metis_107");
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
				break;
			case 30000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112730000));
				break;
			case 30500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112730500));
				break;
			case 31000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112731000));
				break;
			case 31500:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112731500));
				break;
			case 32000:
				getLordActor()->addSubGroup(obtainActorFromFactory(1112732000));
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 88-1 ? _iCnt_Event+1 : _iCnt_Event);
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
