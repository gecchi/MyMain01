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
	DWORD dw[] = {1,10,20,100,310,400,500,530,560,590,610,620,650,910,1010,1020,1210,1500,1510,1530,1560,1590,1620,1650,1800,1810,2010,2020,2100,2110,2300,2410,2710,2900,3010,3020,3310,3400,3500,3610,3700,3910,4010,4020,4200,4210,4500,4510,4530,4560,4590,4620,4650,4800,4810,4900,5010,5020,5100,5110,5300,5400,5410,5500,5530,5560,5590,5600,5620,5650,5710,6010,6020,6100,6310,6500,6610,6700,6800,6910,7010,7020,7100,7200,7210,7300,7500,7510,7810,7900,8000,8010,8020,8110,8400,8410,8500,8530,8560,8590,8600,8620,8650,8700,8710,9010,9020,9100,9200,9310,9400,9500,9530,9560,9590,9610,9620,9650,9800,9900,9910,10010,10020,10100,10210,10300,10400,10500,10510,10600,10810,11000,11010,11020,11100,11110,11410,11500,11700,11710,11800,12010,12020,12100,12200,12300,12310,12400,12500,12530,12560,12590,12610,12620,12650,12900,12910,13000,13010,13020,13210,13400,13500,13510,13530,13560,13590,13600,13620,13650,13700,13810,14010,14020,14100,14110,14200,14400,14410,14710,14800,14900,15010,15020,15100,15300,15310,15400,15500,15600,15610,15910,16000,16010,16020,16100,16210,16500,16510,16530,16560,16590,16620,16650,16700,16800,16810,17110,17200,17400,17410,17710,17900,18010,18020,18310,18400,18600,18610,18910,19100,19210,19510,19800,19810,20110,20410,20710,21010,21310,21610,21910,22210,22510,22810,23110,23410,23710,24010,24310,24610,24910,25210,25510,25810,26110,26410,26710,27010,27310,27610,27910,28210,28510,28810,29110,29410,29710,30010,30310,30610,30910,31210,31510,31810};
	_paFrame_NextEvent = new DWORD[265];
	for (int i = 0; i < 265; i++) {
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
	orderActorToFactory(112472010, FormationIris001, "F001_Iris_15");
	orderActorToFactory(1125720, FormationIris002, "F002_Iris_16");
	orderActorToFactory(112572020, FormationIris002, "F002_Iris_17");
	orderActorWithDpToFactory(11277500, EnemyCeres, "Ceres_18", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11287530, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11297560, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11307590, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11317620, EnemyCeres, "Ceres_22", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327650, EnemyCeres, "Ceres_23", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorToFactory(110573010, EnemyVesta, "Vesta_24");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 20:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125720);
				getLordActor()->addSubGroup(pFormationActor);
				}
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
			case 310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057310));
				orderActorToFactory(110573310, EnemyVesta, "Vesta_25");
				break;
			case 400:
				orderActorToFactory(111773400, EnemyAstraea, "Astraea_26");
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
				orderActorToFactory(110573610, EnemyVesta, "Vesta_27");
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
				orderActorToFactory(110573910, EnemyVesta, "Vesta_28");
				break;
			case 1010:
				orderActorToFactory(112474010, FormationIris001, "F001_Iris_29");
				break;
			case 1020:
				orderActorToFactory(112574020, FormationIris002, "F002_Iris_30");
				break;
			case 1210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571210));
				orderActorToFactory(110574210, EnemyVesta, "Vesta_31");
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111671500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorWithDpToFactory(112774500, EnemyCeres, "Ceres_32", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571510));
				orderActorToFactory(110574510, EnemyVesta, "Vesta_33");
				break;
			case 1530:
				orderActorWithDpToFactory(112874530, EnemyCeres, "Ceres_34", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1560:
				orderActorWithDpToFactory(112974560, EnemyCeres, "Ceres_35", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1590:
				orderActorWithDpToFactory(113074590, EnemyCeres, "Ceres_36", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1620:
				orderActorWithDpToFactory(113174620, EnemyCeres, "Ceres_37", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1650:
				orderActorWithDpToFactory(113274650, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1800:
				orderActorToFactory(111074800, EnemyAstraea, "Astraea_39");
				break;
			case 1810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571810));
				orderActorToFactory(110574810, EnemyVesta, "Vesta_40");
				break;
			case 2010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112472010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112572020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2100:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_41");
				break;
			case 2110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572110));
				orderActorToFactory(110575110, EnemyVesta, "Vesta_42");
				break;
			case 2300:
				orderActorToFactory(111875300, EnemyAstraea, "Astraea_43");
				break;
			case 2410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572410));
				orderActorToFactory(110575410, EnemyVesta, "Vesta_44");
				break;
			case 2710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572710));
				orderActorToFactory(110575710, EnemyVesta, "Vesta_45");
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
				orderActorToFactory(110576010, EnemyVesta, "Vesta_46");
				orderActorToFactory(112476010, FormationIris001, "F001_Iris_47");
				break;
			case 3020:
				orderActorToFactory(112576020, FormationIris002, "F002_Iris_48");
				break;
			case 3310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573310));
				orderActorToFactory(110576310, EnemyVesta, "Vesta_49");
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
				orderActorToFactory(111676500, EnemyAstraea, "Astraea_50");
				break;
			case 3610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573610));
				orderActorToFactory(110576610, EnemyVesta, "Vesta_51");
				break;
			case 3700:
				orderActorToFactory(111176700, EnemyAstraea, "Astraea_52");
				break;
			case 3910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573910));
				orderActorToFactory(110576910, EnemyVesta, "Vesta_53");
				break;
			case 4010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112474010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112574020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 4200:
				orderActorToFactory(111977200, EnemyAstraea, "Astraea_54");
				break;
			case 4210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574210));
				orderActorToFactory(110577210, EnemyVesta, "Vesta_55");
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
				orderActorToFactory(110577510, EnemyVesta, "Vesta_56");
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
				orderActorToFactory(110577810, EnemyVesta, "Vesta_57");
				break;
			case 4900:
				orderActorToFactory(110977900, EnemyAstraea, "Astraea_58");
				break;
			case 5010:
				orderActorToFactory(112478010, FormationIris001, "F001_Iris_59");
				break;
			case 5020:
				orderActorToFactory(112578020, FormationIris002, "F002_Iris_60");
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
				orderActorToFactory(110578110, EnemyVesta, "Vesta_61");
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111875300);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 5400:
				orderActorToFactory(111778400, EnemyAstraea, "Astraea_62");
				break;
			case 5410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575410));
				orderActorToFactory(110578410, EnemyVesta, "Vesta_63");
				break;
			case 5500:
				orderActorWithDpToFactory(112778500, EnemyCeres, "Ceres_64", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5530:
				orderActorWithDpToFactory(112878530, EnemyCeres, "Ceres_65", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				orderActorWithDpToFactory(112978560, EnemyCeres, "Ceres_66", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				orderActorWithDpToFactory(113078590, EnemyCeres, "Ceres_67", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5600:
				orderActorToFactory(111278600, EnemyAstraea, "Astraea_68");
				break;
			case 5620:
				orderActorWithDpToFactory(113178620, EnemyCeres, "Ceres_69", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				orderActorWithDpToFactory(113278650, EnemyCeres, "Ceres_70", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575710));
				orderActorToFactory(110578710, EnemyVesta, "Vesta_71");
				break;
			case 6010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576010));
				orderActorToFactory(110579010, EnemyVesta, "Vesta_72");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112476010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112576020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 6100:
				orderActorToFactory(112079100, EnemyAstraea, "Astraea_73");
				break;
			case 6310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576310));
				orderActorToFactory(110579310, EnemyVesta, "Vesta_74");
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
				orderActorToFactory(110579610, EnemyVesta, "Vesta_75");
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
				orderActorToFactory(111079800, EnemyAstraea, "Astraea_76");
				break;
			case 6910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576910));
				orderActorToFactory(110579910, EnemyVesta, "Vesta_77");
				break;
			case 7010:
				orderActorToFactory(1124710010, FormationIris001, "F001_Iris_78");
				break;
			case 7020:
				orderActorToFactory(1125710020, FormationIris002, "F002_Iris_79");
				break;
			case 7100:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_80");
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
				orderActorToFactory(1105710210, EnemyVesta, "Vesta_81");
				break;
			case 7300:
				orderActorToFactory(1118710300, EnemyAstraea, "Astraea_82");
				break;
			case 7500:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_83");
				break;
			case 7510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577510));
				orderActorToFactory(1105710510, EnemyVesta, "Vesta_84");
				break;
			case 7810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577810));
				orderActorToFactory(1105710810, EnemyVesta, "Vesta_85");
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
				orderActorToFactory(1121711000, EnemyAstraea, "Astraea_86");
				break;
			case 8010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112478010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112578020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 8110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578110));
				orderActorToFactory(1105711110, EnemyVesta, "Vesta_87");
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
				orderActorToFactory(1105711410, EnemyVesta, "Vesta_88");
				break;
			case 8500:
				orderActorToFactory(1116711500, EnemyAstraea, "Astraea_89");
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
				orderActorToFactory(1111711700, EnemyAstraea, "Astraea_90");
				break;
			case 8710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578710));
				orderActorToFactory(1105711710, EnemyVesta, "Vesta_91");
				break;
			case 9010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579010));
				orderActorToFactory(1105712010, EnemyVesta, "Vesta_92");
				orderActorToFactory(1124712010, FormationIris001, "F001_Iris_93");
				break;
			case 9020:
				orderActorToFactory(1125712020, FormationIris002, "F002_Iris_94");
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
				orderActorToFactory(1119712200, EnemyAstraea, "Astraea_95");
				break;
			case 9310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579310));
				orderActorToFactory(1105712310, EnemyVesta, "Vesta_96");
				break;
			case 9400:
				orderActorToFactory(1114712400, EnemyAstraea, "Astraea_97");
				break;
			case 9500:
				orderActorWithDpToFactory(1127712500, EnemyCeres, "Ceres_98", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9530:
				orderActorWithDpToFactory(1128712530, EnemyCeres, "Ceres_99", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9560:
				orderActorWithDpToFactory(1129712560, EnemyCeres, "Ceres_100", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				orderActorWithDpToFactory(1130712590, EnemyCeres, "Ceres_101", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579610));
				orderActorToFactory(1105712610, EnemyVesta, "Vesta_102");
				break;
			case 9620:
				orderActorWithDpToFactory(1131712620, EnemyCeres, "Ceres_103", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				orderActorWithDpToFactory(1132712650, EnemyCeres, "Ceres_104", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorToFactory(1109712900, EnemyAstraea, "Astraea_105");
				break;
			case 9910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579910));
				orderActorToFactory(1105712910, EnemyVesta, "Vesta_106");
				break;
			case 10010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 10020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125710020);
				getLordActor()->addSubGroup(pFormationActor);
				}
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
				orderActorToFactory(1105713210, EnemyVesta, "Vesta_107");
				break;
			case 10300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710300);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 10400:
				orderActorToFactory(1117713400, EnemyAstraea, "Astraea_108");
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
				orderActorToFactory(1105713510, EnemyVesta, "Vesta_109");
				break;
			case 10600:
				orderActorToFactory(1112713600, EnemyAstraea, "Astraea_110");
				break;
			case 10810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710810));
				orderActorToFactory(1105713810, EnemyVesta, "Vesta_111");
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
				orderActorToFactory(1124714010, FormationIris001, "F001_Iris_112");
				break;
			case 11020:
				orderActorToFactory(1125714020, FormationIris002, "F002_Iris_113");
				break;
			case 11100:
				orderActorToFactory(1120714100, EnemyAstraea, "Astraea_114");
				break;
			case 11110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711110));
				orderActorToFactory(1105714110, EnemyVesta, "Vesta_115");
				break;
			case 11410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711410));
				orderActorToFactory(1105714410, EnemyVesta, "Vesta_116");
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
				orderActorToFactory(1105714710, EnemyVesta, "Vesta_117");
				break;
			case 11800:
				orderActorToFactory(1110714800, EnemyAstraea, "Astraea_118");
				break;
			case 12010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712010));
				orderActorToFactory(1105715010, EnemyVesta, "Vesta_119");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124712010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125712020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 12100:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_120");
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
				orderActorToFactory(1118715300, EnemyAstraea, "Astraea_121");
				break;
			case 12310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712310));
				orderActorToFactory(1105715310, EnemyVesta, "Vesta_122");
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
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_123");
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
				orderActorToFactory(1105715610, EnemyVesta, "Vesta_124");
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
				orderActorToFactory(1105715910, EnemyVesta, "Vesta_125");
				break;
			case 13000:
				orderActorToFactory(1121716000, EnemyAstraea, "Astraea_126");
				break;
			case 13010:
				orderActorToFactory(1124716010, FormationIris001, "F001_Iris_127");
				break;
			case 13020:
				orderActorToFactory(1125716020, FormationIris002, "F002_Iris_128");
				break;
			case 13210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713210));
				orderActorToFactory(1105716210, EnemyVesta, "Vesta_129");
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
				orderActorToFactory(1116716500, EnemyAstraea, "Astraea_130");
				orderActorWithDpToFactory(1127716500, EnemyCeres, "Ceres_131", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713510));
				orderActorToFactory(1105716510, EnemyVesta, "Vesta_132");
				break;
			case 13530:
				orderActorWithDpToFactory(1128716530, EnemyCeres, "Ceres_133", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				orderActorWithDpToFactory(1129716560, EnemyCeres, "Ceres_134", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13590:
				orderActorWithDpToFactory(1130716590, EnemyCeres, "Ceres_135", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorWithDpToFactory(1131716620, EnemyCeres, "Ceres_136", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13650:
				orderActorWithDpToFactory(1132716650, EnemyCeres, "Ceres_137", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13700:
				orderActorToFactory(1111716700, EnemyAstraea, "Astraea_138");
				break;
			case 13810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713810));
				orderActorToFactory(1105716810, EnemyVesta, "Vesta_139");
				break;
			case 14010:
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124714010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 14020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125714020);
				getLordActor()->addSubGroup(pFormationActor);
				}
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
				orderActorToFactory(1105717110, EnemyVesta, "Vesta_140");
				break;
			case 14200:
				orderActorToFactory(1119717200, EnemyAstraea, "Astraea_141");
				break;
			case 14400:
				orderActorToFactory(1114717400, EnemyAstraea, "Astraea_142");
				break;
			case 14410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714410));
				orderActorToFactory(1105717410, EnemyVesta, "Vesta_143");
				break;
			case 14710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714710));
				orderActorToFactory(1105717710, EnemyVesta, "Vesta_144");
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
				orderActorToFactory(1109717900, EnemyAstraea, "Astraea_145");
				break;
			case 15010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715010));
				orderActorToFactory(1105718010, EnemyVesta, "Vesta_146");
				orderActorToFactory(1124718010, FormationIris001, "F001_Iris_147");
				break;
			case 15020:
				orderActorToFactory(1125718020, FormationIris002, "F002_Iris_148");
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
				break;
			case 15310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715310));
				orderActorToFactory(1105718310, EnemyVesta, "Vesta_149");
				break;
			case 15400:
				orderActorToFactory(1117718400, EnemyAstraea, "Astraea_150");
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
				orderActorToFactory(1112718600, EnemyAstraea, "Astraea_151");
				break;
			case 15610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715610));
				orderActorToFactory(1105718610, EnemyVesta, "Vesta_152");
				break;
			case 15910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715910));
				orderActorToFactory(1105718910, EnemyVesta, "Vesta_153");
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
				break;
			case 16020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125716020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 16100:
				orderActorToFactory(1120719100, EnemyAstraea, "Astraea_154");
				break;
			case 16210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716210));
				orderActorToFactory(1105719210, EnemyVesta, "Vesta_155");
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
				orderActorToFactory(1105719510, EnemyVesta, "Vesta_156");
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
				orderActorToFactory(1110719800, EnemyAstraea, "Astraea_157");
				break;
			case 16810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716810));
				orderActorToFactory(1105719810, EnemyVesta, "Vesta_158");
				break;
			case 17110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717110));
				orderActorToFactory(1105720110, EnemyVesta, "Vesta_159");
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
				orderActorToFactory(1105720410, EnemyVesta, "Vesta_160");
				break;
			case 17710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717710));
				orderActorToFactory(1105720710, EnemyVesta, "Vesta_161");
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
				orderActorToFactory(1105721010, EnemyVesta, "Vesta_162");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124718010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18020:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125718020);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718310));
				orderActorToFactory(1105721310, EnemyVesta, "Vesta_163");
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
				orderActorToFactory(1105721610, EnemyVesta, "Vesta_164");
				break;
			case 18910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718910));
				orderActorToFactory(1105721910, EnemyVesta, "Vesta_165");
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
				orderActorToFactory(1105722210, EnemyVesta, "Vesta_166");
				break;
			case 19510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719510));
				orderActorToFactory(1105722510, EnemyVesta, "Vesta_167");
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
				orderActorToFactory(1105722810, EnemyVesta, "Vesta_168");
				break;
			case 20110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720110));
				orderActorToFactory(1105723110, EnemyVesta, "Vesta_169");
				break;
			case 20410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720410));
				orderActorToFactory(1105723410, EnemyVesta, "Vesta_170");
				break;
			case 20710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720710));
				orderActorToFactory(1105723710, EnemyVesta, "Vesta_171");
				break;
			case 21010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721010));
				orderActorToFactory(1105724010, EnemyVesta, "Vesta_172");
				break;
			case 21310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721310));
				orderActorToFactory(1105724310, EnemyVesta, "Vesta_173");
				break;
			case 21610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721610));
				orderActorToFactory(1105724610, EnemyVesta, "Vesta_174");
				break;
			case 21910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721910));
				orderActorToFactory(1105724910, EnemyVesta, "Vesta_175");
				break;
			case 22210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722210));
				orderActorToFactory(1105725210, EnemyVesta, "Vesta_176");
				break;
			case 22510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722510));
				orderActorToFactory(1105725510, EnemyVesta, "Vesta_177");
				break;
			case 22810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722810));
				orderActorToFactory(1105725810, EnemyVesta, "Vesta_178");
				break;
			case 23110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723110));
				orderActorToFactory(1105726110, EnemyVesta, "Vesta_179");
				break;
			case 23410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723410));
				orderActorToFactory(1105726410, EnemyVesta, "Vesta_180");
				break;
			case 23710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723710));
				orderActorToFactory(1105726710, EnemyVesta, "Vesta_181");
				break;
			case 24010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724010));
				orderActorToFactory(1105727010, EnemyVesta, "Vesta_182");
				break;
			case 24310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724310));
				orderActorToFactory(1105727310, EnemyVesta, "Vesta_183");
				break;
			case 24610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724610));
				orderActorToFactory(1105727610, EnemyVesta, "Vesta_184");
				break;
			case 24910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724910));
				orderActorToFactory(1105727910, EnemyVesta, "Vesta_185");
				break;
			case 25210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725210));
				orderActorToFactory(1105728210, EnemyVesta, "Vesta_186");
				break;
			case 25510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725510));
				orderActorToFactory(1105728510, EnemyVesta, "Vesta_187");
				break;
			case 25810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725810));
				orderActorToFactory(1105728810, EnemyVesta, "Vesta_188");
				break;
			case 26110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726110));
				orderActorToFactory(1105729110, EnemyVesta, "Vesta_189");
				break;
			case 26410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726410));
				orderActorToFactory(1105729410, EnemyVesta, "Vesta_190");
				break;
			case 26710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726710));
				orderActorToFactory(1105729710, EnemyVesta, "Vesta_191");
				break;
			case 27010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727010));
				orderActorToFactory(1105730010, EnemyVesta, "Vesta_192");
				break;
			case 27310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727310));
				orderActorToFactory(1105730310, EnemyVesta, "Vesta_193");
				break;
			case 27610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727610));
				orderActorToFactory(1105730610, EnemyVesta, "Vesta_194");
				break;
			case 27910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727910));
				orderActorToFactory(1105730910, EnemyVesta, "Vesta_195");
				break;
			case 28210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728210));
				orderActorToFactory(1105731210, EnemyVesta, "Vesta_196");
				break;
			case 28510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728510));
				orderActorToFactory(1105731510, EnemyVesta, "Vesta_197");
				break;
			case 28810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728810));
				orderActorToFactory(1105731810, EnemyVesta, "Vesta_198");
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
