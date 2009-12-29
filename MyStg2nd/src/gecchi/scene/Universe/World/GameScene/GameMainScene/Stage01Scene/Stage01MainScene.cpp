#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW ActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
    // gen01 start
	DWORD dw[] = {1,10,100,300,310,400,500,530,560,590,610,620,650,910,1010,1210,1300,1500,1510,1530,1560,1590,1620,1650,1800,1810,2010,2100,2110,2300,2410,2710,2900,3010,3300,3310,3400,3500,3610,3700,3910,4010,4200,4210,4300,4500,4510,4530,4560,4590,4620,4650,4800,4810,4900,5010,5100,5110,5300,5400,5410,5500,5530,5560,5590,5600,5620,5650,5710,6010,6100,6300,6310,6500,6610,6700,6800,6910,7010,7100,7200,7210,7300,7500,7510,7810,7900,8000,8010,8110,8300,8400,8410,8500,8530,8560,8590,8600,8620,8650,8700,8710,9010,9100,9200,9300,9310,9400,9500,9530,9560,9590,9610,9620,9650,9800,9900,9910,10010,10100,10210,10300,10400,10500,10510,10600,10810,11000,11010,11100,11110,11300,11410,11500,11700,11710,11800,12010,12100,12200,12300,12310,12400,12500,12530,12560,12590,12610,12620,12650,12900,12910,13000,13010,13210,13300,13400,13500,13510,13530,13560,13590,13600,13620,13650,13700,13810,14010,14100,14110,14200,14300,14400,14410,14710,14800,14900,15010,15100,15300,15310,15400,15500,15600,15610,15910,16000,16010,16100,16210,16300,16500,16510,16530,16560,16590,16620,16650,16700,16800,16810,17010,17110,17200,17300,17400,17410,17710,17900,18010,18300,18310,18400,18600,18610,18910,19010,19100,19210,19300,19510,19800,19810,20110,20410,20710,21010,21310,21610,21910,22210,22510,22810,23110,23410,23710,24010,24310,24610,24910,25210,25510,25810,26110,26410,26710,27010,27310,27610,27910,28210,28510,28810,29110,29410,29710,30010,30310,30610,30910,31210,31510,31810};
	_paFrame_NextEvent = new DWORD[263];
	for (int i = 0; i < 263; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105710, EnemyVesta, "Vesta_1");
	orderActorToFactory(11057310, EnemyVesta, "Vesta_2");
	orderActorToFactory(11057610, EnemyVesta, "Vesta_3");
	orderActorToFactory(11057910, EnemyVesta, "Vesta_4");
	orderActorToFactory(110571210, EnemyVesta, "Vesta_5");
	orderActorToFactory(110571510, EnemyVesta, "Vesta_6");
	orderActorToFactory(110571810, EnemyVesta, "Vesta_7");
	orderActorToFactory(110572110, EnemyVesta, "Vesta_8");
	orderActorToFactory(110572410, EnemyVesta, "Vesta_9");
	orderActorToFactory(110572710, EnemyVesta, "Vesta_10");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_11");
	orderActorToFactory(110972900, EnemyAstraea, "Astraea_12");
	orderActorToFactory(111671500, EnemyAstraea, "Astraea_13");
	orderActorToFactory(1124710, FormationIris001, "F001_Iris_14");
	orderActorToFactory(112471010, FormationIris001, "F001_Iris_15");
	orderActorToFactory(112472010, FormationIris001, "F001_Iris_16");
	orderActorToFactory(11257300, FormationIris002, "F002_Iris_17");
	orderActorToFactory(112571300, FormationIris002, "F002_Iris_18");
	orderActorToFactory(112572300, FormationIris002, "F002_Iris_19");
	orderActorWithDpToFactory(11277500, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11287530, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11297560, EnemyCeres, "Ceres_22", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11307590, EnemyCeres, "Ceres_23", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11317620, EnemyCeres, "Ceres_24", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327650, EnemyCeres, "Ceres_25", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_frame_of_active == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_frame_of_active) {
			case 1:
				break;
			case 10:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710));
				orderActorToFactory(110573010, EnemyVesta, "Vesta_26");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112473010, FormationIris001, "F001_Iris_27");
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(11257300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112573300, FormationIris002, "F002_Iris_28");
				break;
			case 310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057310));
				orderActorToFactory(110573310, EnemyVesta, "Vesta_29");
				break;
			case 400:
				orderActorToFactory(111773400, EnemyAstraea, "Astraea_30");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11277500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11287530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11297560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11307590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057610));
				orderActorToFactory(110573610, EnemyVesta, "Vesta_31");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11317620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11327650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057910));
				orderActorToFactory(110573910, EnemyVesta, "Vesta_32");
				break;
			case 1010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112471010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112474010, FormationIris001, "F001_Iris_33");
				break;
			case 1210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571210));
				orderActorToFactory(110574210, EnemyVesta, "Vesta_34");
				break;
			case 1300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112571300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112574300, FormationIris002, "F002_Iris_35");
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111671500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorWithDpToFactory(112774500, EnemyCeres, "Ceres_36", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571510));
				orderActorToFactory(110574510, EnemyVesta, "Vesta_37");
				break;
			case 1530:
				orderActorWithDpToFactory(112874530, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1560:
				orderActorWithDpToFactory(112974560, EnemyCeres, "Ceres_39", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1590:
				orderActorWithDpToFactory(113074590, EnemyCeres, "Ceres_40", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1620:
				orderActorWithDpToFactory(113174620, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1650:
				orderActorWithDpToFactory(113274650, EnemyCeres, "Ceres_42", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1800:
				orderActorToFactory(111074800, EnemyAstraea, "Astraea_43");
				break;
			case 1810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571810));
				orderActorToFactory(110574810, EnemyVesta, "Vesta_44");
				break;
			case 2010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112472010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112475010, FormationIris001, "F001_Iris_45");
				break;
			case 2100:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_46");
				break;
			case 2110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572110));
				orderActorToFactory(110575110, EnemyVesta, "Vesta_47");
				break;
			case 2300:
				orderActorToFactory(111875300, EnemyAstraea, "Astraea_48");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112572300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112575300, FormationIris002, "F002_Iris_49");
				break;
			case 2410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572410));
				orderActorToFactory(110575410, EnemyVesta, "Vesta_50");
				break;
			case 2710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572710));
				orderActorToFactory(110575710, EnemyVesta, "Vesta_51");
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110972900);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 3010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573010));
				orderActorToFactory(110576010, EnemyVesta, "Vesta_52");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112473010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112476010, FormationIris001, "F001_Iris_53");
				break;
			case 3300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112573300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112576300, FormationIris002, "F002_Iris_54");
				break;
			case 3310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573310));
				orderActorToFactory(110576310, EnemyVesta, "Vesta_55");
				break;
			case 3400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111773400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 3500:
				orderActorToFactory(111676500, EnemyAstraea, "Astraea_56");
				break;
			case 3610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573610));
				orderActorToFactory(110576610, EnemyVesta, "Vesta_57");
				break;
			case 3700:
				orderActorToFactory(111176700, EnemyAstraea, "Astraea_58");
				break;
			case 3910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573910));
				orderActorToFactory(110576910, EnemyVesta, "Vesta_59");
				break;
			case 4010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112474010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112477010, FormationIris001, "F001_Iris_60");
				break;
			case 4200:
				orderActorToFactory(111977200, EnemyAstraea, "Astraea_61");
				break;
			case 4210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574210));
				orderActorToFactory(110577210, EnemyVesta, "Vesta_62");
				break;
			case 4300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112574300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112577300, FormationIris002, "F002_Iris_63");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112774500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574510));
				orderActorToFactory(110577510, EnemyVesta, "Vesta_64");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112874530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112974560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113074590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113174620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113274650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 4800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111074800);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 4810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574810));
				orderActorToFactory(110577810, EnemyVesta, "Vesta_65");
				break;
			case 4900:
				orderActorToFactory(110977900, EnemyAstraea, "Astraea_66");
				break;
			case 5010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112475010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112478010, FormationIris001, "F001_Iris_67");
				break;
			case 5100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110775100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 5110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575110));
				orderActorToFactory(110578110, EnemyVesta, "Vesta_68");
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111875300);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112575300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112578300, FormationIris002, "F002_Iris_69");
				break;
			case 5400:
				orderActorToFactory(111778400, EnemyAstraea, "Astraea_70");
				break;
			case 5410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575410));
				orderActorToFactory(110578410, EnemyVesta, "Vesta_71");
				break;
			case 5500:
				orderActorWithDpToFactory(112778500, EnemyCeres, "Ceres_72", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5530:
				orderActorWithDpToFactory(112878530, EnemyCeres, "Ceres_73", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				orderActorWithDpToFactory(112978560, EnemyCeres, "Ceres_74", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				orderActorWithDpToFactory(113078590, EnemyCeres, "Ceres_75", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5600:
				orderActorToFactory(111278600, EnemyAstraea, "Astraea_76");
				break;
			case 5620:
				orderActorWithDpToFactory(113178620, EnemyCeres, "Ceres_77", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				orderActorWithDpToFactory(113278650, EnemyCeres, "Ceres_78", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575710));
				orderActorToFactory(110578710, EnemyVesta, "Vesta_79");
				break;
			case 6010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576010));
				orderActorToFactory(110579010, EnemyVesta, "Vesta_80");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112476010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112479010, FormationIris001, "F001_Iris_81");
				break;
			case 6100:
				orderActorToFactory(112079100, EnemyAstraea, "Astraea_82");
				break;
			case 6300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112576300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112579300, FormationIris002, "F002_Iris_83");
				break;
			case 6310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576310));
				orderActorToFactory(110579310, EnemyVesta, "Vesta_84");
				break;
			case 6500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111676500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				break;
			case 6610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576610));
				orderActorToFactory(110579610, EnemyVesta, "Vesta_85");
				break;
			case 6700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111176700);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 6800:
				orderActorToFactory(111079800, EnemyAstraea, "Astraea_86");
				break;
			case 6910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576910));
				orderActorToFactory(110579910, EnemyVesta, "Vesta_87");
				break;
			case 7010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112477010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124710010, FormationIris001, "F001_Iris_88");
				break;
			case 7100:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_89");
				break;
			case 7200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111977200);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 7210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577210));
				orderActorToFactory(1105710210, EnemyVesta, "Vesta_90");
				break;
			case 7300:
				orderActorToFactory(1118710300, EnemyAstraea, "Astraea_91");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112577300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125710300, FormationIris002, "F002_Iris_92");
				break;
			case 7500:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_93");
				break;
			case 7510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577510));
				orderActorToFactory(1105710510, EnemyVesta, "Vesta_94");
				break;
			case 7810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577810));
				orderActorToFactory(1105710810, EnemyVesta, "Vesta_95");
				break;
			case 7900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110977900);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 8000:
				orderActorToFactory(1121711000, EnemyAstraea, "Astraea_96");
				break;
			case 8010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112478010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124711010, FormationIris001, "F001_Iris_97");
				break;
			case 8110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578110));
				orderActorToFactory(1105711110, EnemyVesta, "Vesta_98");
				break;
			case 8300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112578300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125711300, FormationIris002, "F002_Iris_99");
				break;
			case 8400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111778400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 8410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578410));
				orderActorToFactory(1105711410, EnemyVesta, "Vesta_100");
				break;
			case 8500:
				orderActorToFactory(1116711500, EnemyAstraea, "Astraea_101");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112778500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112878530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112978560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113078590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111278600);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113178620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113278650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 8700:
				orderActorToFactory(1111711700, EnemyAstraea, "Astraea_102");
				break;
			case 8710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578710));
				orderActorToFactory(1105711710, EnemyVesta, "Vesta_103");
				break;
			case 9010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579010));
				orderActorToFactory(1105712010, EnemyVesta, "Vesta_104");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112479010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124712010, FormationIris001, "F001_Iris_105");
				break;
			case 9100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112079100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 9200:
				orderActorToFactory(1119712200, EnemyAstraea, "Astraea_106");
				break;
			case 9300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112579300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125712300, FormationIris002, "F002_Iris_107");
				break;
			case 9310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579310));
				orderActorToFactory(1105712310, EnemyVesta, "Vesta_108");
				break;
			case 9400:
				orderActorToFactory(1114712400, EnemyAstraea, "Astraea_109");
				break;
			case 9500:
				orderActorWithDpToFactory(1127712500, EnemyCeres, "Ceres_110", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9530:
				orderActorWithDpToFactory(1128712530, EnemyCeres, "Ceres_111", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9560:
				orderActorWithDpToFactory(1129712560, EnemyCeres, "Ceres_112", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				orderActorWithDpToFactory(1130712590, EnemyCeres, "Ceres_113", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579610));
				orderActorToFactory(1105712610, EnemyVesta, "Vesta_114");
				break;
			case 9620:
				orderActorWithDpToFactory(1131712620, EnemyCeres, "Ceres_115", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				orderActorWithDpToFactory(1132712650, EnemyCeres, "Ceres_116", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111079800);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 9900:
				orderActorToFactory(1109712900, EnemyAstraea, "Astraea_117");
				break;
			case 9910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579910));
				orderActorToFactory(1105712910, EnemyVesta, "Vesta_118");
				break;
			case 10010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124713010, FormationIris001, "F001_Iris_119");
				break;
			case 10100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107710100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 10210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710210));
				orderActorToFactory(1105713210, EnemyVesta, "Vesta_120");
				break;
			case 10300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710300);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125710300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125713300, FormationIris002, "F002_Iris_121");
				break;
			case 10400:
				orderActorToFactory(1117713400, EnemyAstraea, "Astraea_122");
				break;
			case 10500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				break;
			case 10510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710510));
				orderActorToFactory(1105713510, EnemyVesta, "Vesta_123");
				break;
			case 10600:
				orderActorToFactory(1112713600, EnemyAstraea, "Astraea_124");
				break;
			case 10810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710810));
				orderActorToFactory(1105713810, EnemyVesta, "Vesta_125");
				break;
			case 11000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121711000);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				break;
			case 11010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124711010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124714010, FormationIris001, "F001_Iris_126");
				break;
			case 11100:
				orderActorToFactory(1120714100, EnemyAstraea, "Astraea_127");
				break;
			case 11110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711110));
				orderActorToFactory(1105714110, EnemyVesta, "Vesta_128");
				break;
			case 11300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125711300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125714300, FormationIris002, "F002_Iris_129");
				break;
			case 11410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711410));
				orderActorToFactory(1105714410, EnemyVesta, "Vesta_130");
				break;
			case 11500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116711500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				break;
			case 11700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111711700);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 11710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711710));
				orderActorToFactory(1105714710, EnemyVesta, "Vesta_131");
				break;
			case 11800:
				orderActorToFactory(1110714800, EnemyAstraea, "Astraea_132");
				break;
			case 12010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712010));
				orderActorToFactory(1105715010, EnemyVesta, "Vesta_133");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124712010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124715010, FormationIris001, "F001_Iris_134");
				break;
			case 12100:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_135");
				break;
			case 12200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119712200);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 12300:
				orderActorToFactory(1118715300, EnemyAstraea, "Astraea_136");
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125712300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125715300, FormationIris002, "F002_Iris_137");
				break;
			case 12310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712310));
				orderActorToFactory(1105715310, EnemyVesta, "Vesta_138");
				break;
			case 12400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114712400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 12500:
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_139");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127712500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128712530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129712560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130712590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712610));
				orderActorToFactory(1105715610, EnemyVesta, "Vesta_140");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131712620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132712650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 12900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109712900);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 12910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712910));
				orderActorToFactory(1105715910, EnemyVesta, "Vesta_141");
				break;
			case 13000:
				orderActorToFactory(1121716000, EnemyAstraea, "Astraea_142");
				break;
			case 13010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124713010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124716010, FormationIris001, "F001_Iris_143");
				break;
			case 13210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713210));
				orderActorToFactory(1105716210, EnemyVesta, "Vesta_144");
				break;
			case 13300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125713300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125716300, FormationIris002, "F002_Iris_145");
				break;
			case 13400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117713400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 13500:
				orderActorToFactory(1116716500, EnemyAstraea, "Astraea_146");
				orderActorWithDpToFactory(1127716500, EnemyCeres, "Ceres_147", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713510));
				orderActorToFactory(1105716510, EnemyVesta, "Vesta_148");
				break;
			case 13530:
				orderActorWithDpToFactory(1128716530, EnemyCeres, "Ceres_149", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				orderActorWithDpToFactory(1129716560, EnemyCeres, "Ceres_150", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13590:
				orderActorWithDpToFactory(1130716590, EnemyCeres, "Ceres_151", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112713600);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 13620:
				orderActorWithDpToFactory(1131716620, EnemyCeres, "Ceres_152", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13650:
				orderActorWithDpToFactory(1132716650, EnemyCeres, "Ceres_153", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13700:
				orderActorToFactory(1111716700, EnemyAstraea, "Astraea_154");
				break;
			case 13810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713810));
				orderActorToFactory(1105716810, EnemyVesta, "Vesta_155");
				break;
			case 14010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124714010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124717010, FormationIris001, "F001_Iris_156");
				break;
			case 14100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120714100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 14110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714110));
				orderActorToFactory(1105717110, EnemyVesta, "Vesta_157");
				break;
			case 14200:
				orderActorToFactory(1119717200, EnemyAstraea, "Astraea_158");
				break;
			case 14300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125714300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125717300, FormationIris002, "F002_Iris_159");
				break;
			case 14400:
				orderActorToFactory(1114717400, EnemyAstraea, "Astraea_160");
				break;
			case 14410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714410));
				orderActorToFactory(1105717410, EnemyVesta, "Vesta_161");
				break;
			case 14710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714710));
				orderActorToFactory(1105717710, EnemyVesta, "Vesta_162");
				break;
			case 14800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110714800);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 14900:
				orderActorToFactory(1109717900, EnemyAstraea, "Astraea_163");
				break;
			case 15010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715010));
				orderActorToFactory(1105718010, EnemyVesta, "Vesta_164");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124715010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124718010, FormationIris001, "F001_Iris_165");
				break;
			case 15100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107715100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 15300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118715300);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125715300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125718300, FormationIris002, "F002_Iris_166");
				break;
			case 15310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715310));
				orderActorToFactory(1105718310, EnemyVesta, "Vesta_167");
				break;
			case 15400:
				orderActorToFactory(1117718400, EnemyAstraea, "Astraea_168");
				break;
			case 15500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				break;
			case 15600:
				orderActorToFactory(1112718600, EnemyAstraea, "Astraea_169");
				break;
			case 15610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715610));
				orderActorToFactory(1105718610, EnemyVesta, "Vesta_170");
				break;
			case 15910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715910));
				orderActorToFactory(1105718910, EnemyVesta, "Vesta_171");
				break;
			case 16000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121716000);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				break;
			case 16010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124716010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1124719010, FormationIris001, "F001_Iris_172");
				break;
			case 16100:
				orderActorToFactory(1120719100, EnemyAstraea, "Astraea_173");
				break;
			case 16210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716210));
				orderActorToFactory(1105719210, EnemyVesta, "Vesta_174");
				break;
			case 16300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125716300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125719300, FormationIris002, "F002_Iris_175");
				break;
			case 16500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116716500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127716500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716510));
				orderActorToFactory(1105719510, EnemyVesta, "Vesta_176");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128716530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129716560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130716590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131716620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132716650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 16700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111716700);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 16800:
				orderActorToFactory(1110719800, EnemyAstraea, "Astraea_177");
				break;
			case 16810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716810));
				orderActorToFactory(1105719810, EnemyVesta, "Vesta_178");
				break;
			case 17010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124717010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 17110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717110));
				orderActorToFactory(1105720110, EnemyVesta, "Vesta_179");
				break;
			case 17200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119717200);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 17300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125717300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 17400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114717400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				break;
			case 17410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717410));
				orderActorToFactory(1105720410, EnemyVesta, "Vesta_180");
				break;
			case 17710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717710));
				orderActorToFactory(1105720710, EnemyVesta, "Vesta_181");
				break;
			case 17900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109717900);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 18010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718010));
				orderActorToFactory(1105721010, EnemyVesta, "Vesta_182");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124718010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125718300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718310));
				orderActorToFactory(1105721310, EnemyVesta, "Vesta_183");
				break;
			case 18400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117718400);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 18600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112718600);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 18610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718610));
				orderActorToFactory(1105721610, EnemyVesta, "Vesta_184");
				break;
			case 18910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718910));
				orderActorToFactory(1105721910, EnemyVesta, "Vesta_185");
				break;
			case 19010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124719010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 19100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120719100);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 19210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719210));
				orderActorToFactory(1105722210, EnemyVesta, "Vesta_186");
				break;
			case 19300:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125719300);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 19510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719510));
				orderActorToFactory(1105722510, EnemyVesta, "Vesta_187");
				break;
			case 19800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110719800);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 19810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719810));
				orderActorToFactory(1105722810, EnemyVesta, "Vesta_188");
				break;
			case 20110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720110));
				orderActorToFactory(1105723110, EnemyVesta, "Vesta_189");
				break;
			case 20410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720410));
				orderActorToFactory(1105723410, EnemyVesta, "Vesta_190");
				break;
			case 20710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720710));
				orderActorToFactory(1105723710, EnemyVesta, "Vesta_191");
				break;
			case 21010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721010));
				orderActorToFactory(1105724010, EnemyVesta, "Vesta_192");
				break;
			case 21310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721310));
				orderActorToFactory(1105724310, EnemyVesta, "Vesta_193");
				break;
			case 21610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721610));
				orderActorToFactory(1105724610, EnemyVesta, "Vesta_194");
				break;
			case 21910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721910));
				orderActorToFactory(1105724910, EnemyVesta, "Vesta_195");
				break;
			case 22210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722210));
				orderActorToFactory(1105725210, EnemyVesta, "Vesta_196");
				break;
			case 22510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722510));
				orderActorToFactory(1105725510, EnemyVesta, "Vesta_197");
				break;
			case 22810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722810));
				orderActorToFactory(1105725810, EnemyVesta, "Vesta_198");
				break;
			case 23110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723110));
				orderActorToFactory(1105726110, EnemyVesta, "Vesta_199");
				break;
			case 23410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723410));
				orderActorToFactory(1105726410, EnemyVesta, "Vesta_200");
				break;
			case 23710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723710));
				orderActorToFactory(1105726710, EnemyVesta, "Vesta_201");
				break;
			case 24010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724010));
				orderActorToFactory(1105727010, EnemyVesta, "Vesta_202");
				break;
			case 24310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724310));
				orderActorToFactory(1105727310, EnemyVesta, "Vesta_203");
				break;
			case 24610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724610));
				orderActorToFactory(1105727610, EnemyVesta, "Vesta_204");
				break;
			case 24910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724910));
				orderActorToFactory(1105727910, EnemyVesta, "Vesta_205");
				break;
			case 25210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725210));
				orderActorToFactory(1105728210, EnemyVesta, "Vesta_206");
				break;
			case 25510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725510));
				orderActorToFactory(1105728510, EnemyVesta, "Vesta_207");
				break;
			case 25810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725810));
				orderActorToFactory(1105728810, EnemyVesta, "Vesta_208");
				break;
			case 26110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726110));
				orderActorToFactory(1105729110, EnemyVesta, "Vesta_209");
				break;
			case 26410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726410));
				orderActorToFactory(1105729410, EnemyVesta, "Vesta_210");
				break;
			case 26710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726710));
				orderActorToFactory(1105729710, EnemyVesta, "Vesta_211");
				break;
			case 27010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727010));
				orderActorToFactory(1105730010, EnemyVesta, "Vesta_212");
				break;
			case 27310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727310));
				orderActorToFactory(1105730310, EnemyVesta, "Vesta_213");
				break;
			case 27610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727610));
				orderActorToFactory(1105730610, EnemyVesta, "Vesta_214");
				break;
			case 27910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727910));
				orderActorToFactory(1105730910, EnemyVesta, "Vesta_215");
				break;
			case 28210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728210));
				orderActorToFactory(1105731210, EnemyVesta, "Vesta_216");
				break;
			case 28510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728510));
				orderActorToFactory(1105731510, EnemyVesta, "Vesta_217");
				break;
			case 28810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728810));
				orderActorToFactory(1105731810, EnemyVesta, "Vesta_218");
				break;
			case 29110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729110));
				break;
			case 29410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729410));
				break;
			case 29710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729710));
				break;
			case 30010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730010));
				break;
			case 30310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730310));
				break;
			case 30610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730610));
				break;
			case 30910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730910));
				break;
			case 31210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731210));
				break;
			case 31510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731510));
				break;
			case 31810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731810));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_frame_of_active== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_frame_of_active== 1) {
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
