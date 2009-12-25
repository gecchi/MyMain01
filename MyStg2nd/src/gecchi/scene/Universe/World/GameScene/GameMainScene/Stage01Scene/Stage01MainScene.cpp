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
        pEnemyMeshShot->inactivateTreeImmediately(); //�ŏ���\��
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // �ȉ��� gen01 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // gen01 start
	DWORD dw[] = {1,10,100,110,210,310,400,410,500,510,530,560,590,610,620,650,710,810,910,1010,1110,1210,1310,1410,1500,1510,1530,1560,1590,1610,1620,1650,1710,1800,1810,1910,2010,2100,2110,2210,2300,2310,2410,2500,2510,2530,2560,2590,2610,2620,2650,2710,2810,2900,2910,3010,3110,3210,3310,3400,3410,3500,3510,3530,3560,3590,3610,3620,3650,3700,3710,3810,3910,4010,4110,4200,4210,4310,4410,4500,4510,4530,4560,4590,4610,4620,4650,4710,4800,4810,4900,4910,5010,5100,5110,5210,5300,5310,5400,5410,5500,5510,5530,5560,5590,5600,5610,5620,5650,5710,5810,5910,6010,6100,6110,6210,6310,6410,6500,6510,6530,6560,6590,6610,6620,6650,6700,6710,6800,6810,6910,7010,7100,7110,7200,7210,7300,7310,7410,7500,7510,7530,7560,7590,7610,7620,7650,7710,7810,7900,7910,8000,8010,8110,8210,8310,8400,8410,8500,8510,8530,8560,8590,8600,8610,8620,8650,8700,8710,8810,8910,9010,9100,9110,9200,9210,9310,9400,9410,9500,9510,9530,9560,9590,9610,9620,9650,9710,9800,9810,9900,9910,10010,10100,10110,10210,10300,10310,10400,10410,10500,10510,10530,10560,10590,10600,10610,10620,10650,10710,10810,10910,11000,11010,11100,11110,11210,11310,11410,11500,11510,11530,11560,11590,11610,11620,11650,11700,11710,11800,11810,11910,12010,12100,12110,12200,12210,12300,12310,12400,12410,12500,12510,12530,12560,12590,12610,12620,12650,12710,12810,12900,12910,13000,13010,13110,13210,13310,13400,13410,13500,13510,13530,13560,13590,13600,13610,13620,13650,13700,13710,13810,13910,14010,14100,14110,14200,14210,14310,14400,14410,14500,14510,14530,14560,14590,14610,14620,14650,14710,14800,14810,14900,14910,15010,15100,15110,15210,15300,15310,15400,15410,15500,15510,15530,15560,15590,15600,15610,15620,15650,15710,15810,15910,16000,16010,16100,16110,16210,16310,16410,16500,16510,16530,16560,16590,16610,16620,16650,16700,16710,16800,16810,16910,17010,17110,17200,17210,17310,17400,17410,17500,17510,17530,17560,17590,17610,17620,17650,17710,17810,17900,17910,18010,18110,18210,18310,18400,18410,18500,18510,18530,18560,18590,18600,18610,18620,18650,18710,18810,18910,19010,19100,19110,19210,19310,19410,19500,19510,19530,19560,19590,19610,19620,19650,19710,19800,19810,19910,20010,20110,20210,20310,20410,20510,20610,20710,20810,20910,21010,21110,21210,21310,21410,21510,21610,21710,21810,21910,22010,22110,22210,22310,22410,22510,22610,22710,22810,22910,23010,23110,23210,23310,23410,23510,23610,23710,23810,23910,24010,24110,24210,24310,24410,24510,24610,24710,24810,24910,25010,25110,25210,25310,25410,25510,25610,25710,25810,25910,26010,26110,26210,26310,26410,26510,26610,26710,26810,26910,27010,27110,27210,27310,27410,27510,27610,27710,27810,27910,28010,28110,28210,28310,28410,28510,28610,28710,28810,28910,29010,29110,29210,29310,29410,29510,29610,29710,29810,29910,30010,30110,30210,30310,30410,30510,30610,30710,30810,30910,31010,31110,31210,31310,31410,31510,31610,31710,31810,31910};
	_paFrame_NextEvent = new DWORD[509];
	for (int i = 0; i < 509; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105710, EnemyVesta, "Vesta_1");
	orderActorToFactory(11057110, EnemyVesta, "Vesta_2");
	orderActorToFactory(11057210, EnemyVesta, "Vesta_3");
	orderActorToFactory(11057310, EnemyVesta, "Vesta_4");
	orderActorToFactory(11057410, EnemyVesta, "Vesta_5");
	orderActorToFactory(11057510, EnemyVesta, "Vesta_6");
	orderActorToFactory(11057610, EnemyVesta, "Vesta_7");
	orderActorToFactory(11057710, EnemyVesta, "Vesta_8");
	orderActorToFactory(11057810, EnemyVesta, "Vesta_9");
	orderActorToFactory(11057910, EnemyVesta, "Vesta_10");
	orderActorToFactory(110571010, EnemyVesta, "Vesta_11");
	orderActorToFactory(110571110, EnemyVesta, "Vesta_12");
	orderActorToFactory(110571210, EnemyVesta, "Vesta_13");
	orderActorToFactory(110571310, EnemyVesta, "Vesta_14");
	orderActorToFactory(110571410, EnemyVesta, "Vesta_15");
	orderActorToFactory(110571510, EnemyVesta, "Vesta_16");
	orderActorToFactory(110571610, EnemyVesta, "Vesta_17");
	orderActorToFactory(110571710, EnemyVesta, "Vesta_18");
	orderActorToFactory(110571810, EnemyVesta, "Vesta_19");
	orderActorToFactory(110571910, EnemyVesta, "Vesta_20");
	orderActorToFactory(110572010, EnemyVesta, "Vesta_21");
	orderActorToFactory(110572110, EnemyVesta, "Vesta_22");
	orderActorToFactory(110572210, EnemyVesta, "Vesta_23");
	orderActorToFactory(110572310, EnemyVesta, "Vesta_24");
	orderActorToFactory(110572410, EnemyVesta, "Vesta_25");
	orderActorToFactory(110572510, EnemyVesta, "Vesta_26");
	orderActorToFactory(110572610, EnemyVesta, "Vesta_27");
	orderActorToFactory(110572710, EnemyVesta, "Vesta_28");
	orderActorToFactory(110572810, EnemyVesta, "Vesta_29");
	orderActorToFactory(110572910, EnemyVesta, "Vesta_30");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_31");
	orderActorToFactory(110972900, EnemyAstraea, "Astraea_32");
	orderActorToFactory(111671500, EnemyAstraea, "Astraea_33");
	orderActorToFactory(1124710, FormationIris001, "F_Iris_34");
	orderActorToFactory(11247510, FormationIris001, "F_Iris_35");
	orderActorToFactory(112471010, FormationIris001, "F_Iris_36");
	orderActorToFactory(112471510, FormationIris001, "F_Iris_37");
	orderActorToFactory(112472010, FormationIris001, "F_Iris_38");
	orderActorToFactory(112472510, FormationIris001, "F_Iris_39");
	orderActorWithDpToFactory(11277500, EnemyCeres, "Ceres_40", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112771500, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112772500, EnemyCeres, "Ceres_42", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11287530, EnemyCeres, "Ceres_43", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112871530, EnemyCeres, "Ceres_44", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112872530, EnemyCeres, "Ceres_45", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11297560, EnemyCeres, "Ceres_46", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112971560, EnemyCeres, "Ceres_47", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112972560, EnemyCeres, "Ceres_48", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11307590, EnemyCeres, "Ceres_49", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113071590, EnemyCeres, "Ceres_50", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113072590, EnemyCeres, "Ceres_51", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11317620, EnemyCeres, "Ceres_52", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113171620, EnemyCeres, "Ceres_53", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113172620, EnemyCeres, "Ceres_54", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327650, EnemyCeres, "Ceres_55", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113271650, EnemyCeres, "Ceres_56", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113272650, EnemyCeres, "Ceres_57", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // gen02 start
	if (_frame_of_active == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_frame_of_active) {
			case 1:
				break;
			case 10:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710));
				orderActorToFactory(110573010, EnemyVesta, "Vesta_58");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(1124710);
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
			case 110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057110));
				orderActorToFactory(110573110, EnemyVesta, "Vesta_59");
				break;
			case 210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057210));
				orderActorToFactory(110573210, EnemyVesta, "Vesta_60");
				break;
			case 310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057310));
				orderActorToFactory(110573310, EnemyVesta, "Vesta_61");
				break;
			case 400:
				orderActorToFactory(111773400, EnemyAstraea, "Astraea_62");
				break;
			case 410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057410));
				orderActorToFactory(110573410, EnemyVesta, "Vesta_63");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11277500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112773500, EnemyCeres, "Ceres_64", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057510));
				orderActorToFactory(110573510, EnemyVesta, "Vesta_65");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(11247510);
				getLordActor()->addSubGroup(pFormationActor);
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
				orderActorWithDpToFactory(112873530, EnemyCeres, "Ceres_66", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11297560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112973560, EnemyCeres, "Ceres_67", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11307590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113073590, EnemyCeres, "Ceres_68", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057610));
				orderActorToFactory(110573610, EnemyVesta, "Vesta_69");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11317620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113173620, EnemyCeres, "Ceres_70", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11327650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113273650, EnemyCeres, "Ceres_71", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057710));
				orderActorToFactory(110573710, EnemyVesta, "Vesta_72");
				break;
			case 810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057810));
				orderActorToFactory(110573810, EnemyVesta, "Vesta_73");
				break;
			case 910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(11057910));
				orderActorToFactory(110573910, EnemyVesta, "Vesta_74");
				break;
			case 1010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571010));
				orderActorToFactory(110574010, EnemyVesta, "Vesta_75");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112471010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571110));
				orderActorToFactory(110574110, EnemyVesta, "Vesta_76");
				break;
			case 1210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571210));
				orderActorToFactory(110574210, EnemyVesta, "Vesta_77");
				break;
			case 1310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571310));
				orderActorToFactory(110574310, EnemyVesta, "Vesta_78");
				break;
			case 1410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571410));
				orderActorToFactory(110574410, EnemyVesta, "Vesta_79");
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111671500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112771500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112774500, EnemyCeres, "Ceres_80", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571510));
				orderActorToFactory(110574510, EnemyVesta, "Vesta_81");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112471510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 1530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112871530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112874530, EnemyCeres, "Ceres_82", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112971560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112974560, EnemyCeres, "Ceres_83", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113071590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113074590, EnemyCeres, "Ceres_84", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571610));
				orderActorToFactory(110574610, EnemyVesta, "Vesta_85");
				break;
			case 1620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113171620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113174620, EnemyCeres, "Ceres_86", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113271650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113274650, EnemyCeres, "Ceres_87", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571710));
				orderActorToFactory(110574710, EnemyVesta, "Vesta_88");
				break;
			case 1800:
				orderActorToFactory(111074800, EnemyAstraea, "Astraea_89");
				break;
			case 1810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571810));
				orderActorToFactory(110574810, EnemyVesta, "Vesta_90");
				break;
			case 1910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110571910));
				orderActorToFactory(110574910, EnemyVesta, "Vesta_91");
				break;
			case 2010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572010));
				orderActorToFactory(110575010, EnemyVesta, "Vesta_92");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112472010);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2100:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_93");
				break;
			case 2110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572110));
				orderActorToFactory(110575110, EnemyVesta, "Vesta_94");
				break;
			case 2210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572210));
				orderActorToFactory(110575210, EnemyVesta, "Vesta_95");
				break;
			case 2300:
				orderActorToFactory(111875300, EnemyAstraea, "Astraea_96");
				break;
			case 2310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572310));
				orderActorToFactory(110575310, EnemyVesta, "Vesta_97");
				break;
			case 2410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572410));
				orderActorToFactory(110575410, EnemyVesta, "Vesta_98");
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112772500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112775500, EnemyCeres, "Ceres_99", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572510));
				orderActorToFactory(110575510, EnemyVesta, "Vesta_100");
				{
				FormationIris001* pFormationActor = (FormationIris001*)obtainActorFromFactory(112472510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 2530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112872530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112875530, EnemyCeres, "Ceres_101", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112972560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112975560, EnemyCeres, "Ceres_102", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113072590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113075590, EnemyCeres, "Ceres_103", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572610));
				orderActorToFactory(110575610, EnemyVesta, "Vesta_104");
				break;
			case 2620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113172620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113175620, EnemyCeres, "Ceres_105", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113272650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113275650, EnemyCeres, "Ceres_106", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572710));
				orderActorToFactory(110575710, EnemyVesta, "Vesta_107");
				break;
			case 2810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572810));
				orderActorToFactory(110575810, EnemyVesta, "Vesta_108");
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
			case 2910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110572910));
				orderActorToFactory(110575910, EnemyVesta, "Vesta_109");
				break;
			case 3010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573010));
				orderActorToFactory(110576010, EnemyVesta, "Vesta_110");
				break;
			case 3110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573110));
				orderActorToFactory(110576110, EnemyVesta, "Vesta_111");
				break;
			case 3210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573210));
				orderActorToFactory(110576210, EnemyVesta, "Vesta_112");
				break;
			case 3310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573310));
				orderActorToFactory(110576310, EnemyVesta, "Vesta_113");
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
			case 3410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573410));
				orderActorToFactory(110576410, EnemyVesta, "Vesta_114");
				break;
			case 3500:
				orderActorToFactory(111676500, EnemyAstraea, "Astraea_115");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112773500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112776500, EnemyCeres, "Ceres_116", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573510));
				orderActorToFactory(110576510, EnemyVesta, "Vesta_117");
				break;
			case 3530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112873530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112876530, EnemyCeres, "Ceres_118", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112973560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112976560, EnemyCeres, "Ceres_119", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113073590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113076590, EnemyCeres, "Ceres_120", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573610));
				orderActorToFactory(110576610, EnemyVesta, "Vesta_121");
				break;
			case 3620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113173620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113176620, EnemyCeres, "Ceres_122", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113273650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113276650, EnemyCeres, "Ceres_123", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3700:
				orderActorToFactory(111176700, EnemyAstraea, "Astraea_124");
				break;
			case 3710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573710));
				orderActorToFactory(110576710, EnemyVesta, "Vesta_125");
				break;
			case 3810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573810));
				orderActorToFactory(110576810, EnemyVesta, "Vesta_126");
				break;
			case 3910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110573910));
				orderActorToFactory(110576910, EnemyVesta, "Vesta_127");
				break;
			case 4010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574010));
				orderActorToFactory(110577010, EnemyVesta, "Vesta_128");
				break;
			case 4110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574110));
				orderActorToFactory(110577110, EnemyVesta, "Vesta_129");
				break;
			case 4200:
				orderActorToFactory(111977200, EnemyAstraea, "Astraea_130");
				break;
			case 4210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574210));
				orderActorToFactory(110577210, EnemyVesta, "Vesta_131");
				break;
			case 4310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574310));
				orderActorToFactory(110577310, EnemyVesta, "Vesta_132");
				break;
			case 4410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574410));
				orderActorToFactory(110577410, EnemyVesta, "Vesta_133");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112774500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112777500, EnemyCeres, "Ceres_134", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574510));
				orderActorToFactory(110577510, EnemyVesta, "Vesta_135");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112874530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112877530, EnemyCeres, "Ceres_136", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112974560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112977560, EnemyCeres, "Ceres_137", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113074590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113077590, EnemyCeres, "Ceres_138", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574610));
				orderActorToFactory(110577610, EnemyVesta, "Vesta_139");
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113174620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113177620, EnemyCeres, "Ceres_140", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113274650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113277650, EnemyCeres, "Ceres_141", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574710));
				orderActorToFactory(110577710, EnemyVesta, "Vesta_142");
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
				orderActorToFactory(110577810, EnemyVesta, "Vesta_143");
				break;
			case 4900:
				orderActorToFactory(110977900, EnemyAstraea, "Astraea_144");
				break;
			case 4910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110574910));
				orderActorToFactory(110577910, EnemyVesta, "Vesta_145");
				break;
			case 5010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575010));
				orderActorToFactory(110578010, EnemyVesta, "Vesta_146");
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
				orderActorToFactory(110578110, EnemyVesta, "Vesta_147");
				break;
			case 5210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575210));
				orderActorToFactory(110578210, EnemyVesta, "Vesta_148");
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
			case 5310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575310));
				orderActorToFactory(110578310, EnemyVesta, "Vesta_149");
				break;
			case 5400:
				orderActorToFactory(111778400, EnemyAstraea, "Astraea_150");
				break;
			case 5410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575410));
				orderActorToFactory(110578410, EnemyVesta, "Vesta_151");
				break;
			case 5500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112775500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112778500, EnemyCeres, "Ceres_152", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575510));
				orderActorToFactory(110578510, EnemyVesta, "Vesta_153");
				break;
			case 5530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112875530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112878530, EnemyCeres, "Ceres_154", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112975560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112978560, EnemyCeres, "Ceres_155", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113075590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113078590, EnemyCeres, "Ceres_156", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5600:
				orderActorToFactory(111278600, EnemyAstraea, "Astraea_157");
				break;
			case 5610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575610));
				orderActorToFactory(110578610, EnemyVesta, "Vesta_158");
				break;
			case 5620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113175620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113178620, EnemyCeres, "Ceres_159", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113275650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113278650, EnemyCeres, "Ceres_160", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575710));
				orderActorToFactory(110578710, EnemyVesta, "Vesta_161");
				break;
			case 5810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575810));
				orderActorToFactory(110578810, EnemyVesta, "Vesta_162");
				break;
			case 5910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110575910));
				orderActorToFactory(110578910, EnemyVesta, "Vesta_163");
				break;
			case 6010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576010));
				orderActorToFactory(110579010, EnemyVesta, "Vesta_164");
				break;
			case 6100:
				orderActorToFactory(112079100, EnemyAstraea, "Astraea_165");
				break;
			case 6110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576110));
				orderActorToFactory(110579110, EnemyVesta, "Vesta_166");
				break;
			case 6210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576210));
				orderActorToFactory(110579210, EnemyVesta, "Vesta_167");
				break;
			case 6310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576310));
				orderActorToFactory(110579310, EnemyVesta, "Vesta_168");
				break;
			case 6410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576410));
				orderActorToFactory(110579410, EnemyVesta, "Vesta_169");
				break;
			case 6500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111676500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112776500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112779500, EnemyCeres, "Ceres_170", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576510));
				orderActorToFactory(110579510, EnemyVesta, "Vesta_171");
				break;
			case 6530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112876530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112879530, EnemyCeres, "Ceres_172", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112976560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112979560, EnemyCeres, "Ceres_173", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113076590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113079590, EnemyCeres, "Ceres_174", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576610));
				orderActorToFactory(110579610, EnemyVesta, "Vesta_175");
				break;
			case 6620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113176620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113179620, EnemyCeres, "Ceres_176", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113276650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113279650, EnemyCeres, "Ceres_177", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
			case 6710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576710));
				orderActorToFactory(110579710, EnemyVesta, "Vesta_178");
				break;
			case 6800:
				orderActorToFactory(111079800, EnemyAstraea, "Astraea_179");
				break;
			case 6810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576810));
				orderActorToFactory(110579810, EnemyVesta, "Vesta_180");
				break;
			case 6910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110576910));
				orderActorToFactory(110579910, EnemyVesta, "Vesta_181");
				break;
			case 7010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577010));
				orderActorToFactory(1105710010, EnemyVesta, "Vesta_182");
				break;
			case 7100:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_183");
				break;
			case 7110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577110));
				orderActorToFactory(1105710110, EnemyVesta, "Vesta_184");
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
				orderActorToFactory(1105710210, EnemyVesta, "Vesta_185");
				break;
			case 7300:
				orderActorToFactory(1118710300, EnemyAstraea, "Astraea_186");
				break;
			case 7310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577310));
				orderActorToFactory(1105710310, EnemyVesta, "Vesta_187");
				break;
			case 7410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577410));
				orderActorToFactory(1105710410, EnemyVesta, "Vesta_188");
				break;
			case 7500:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_189");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112777500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127710500, EnemyCeres, "Ceres_190", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577510));
				orderActorToFactory(1105710510, EnemyVesta, "Vesta_191");
				break;
			case 7530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112877530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128710530, EnemyCeres, "Ceres_192", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112977560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129710560, EnemyCeres, "Ceres_193", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113077590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130710590, EnemyCeres, "Ceres_194", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577610));
				orderActorToFactory(1105710610, EnemyVesta, "Vesta_195");
				break;
			case 7620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113177620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131710620, EnemyCeres, "Ceres_196", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113277650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132710650, EnemyCeres, "Ceres_197", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577710));
				orderActorToFactory(1105710710, EnemyVesta, "Vesta_198");
				break;
			case 7810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577810));
				orderActorToFactory(1105710810, EnemyVesta, "Vesta_199");
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
			case 7910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110577910));
				orderActorToFactory(1105710910, EnemyVesta, "Vesta_200");
				break;
			case 8000:
				orderActorToFactory(1121711000, EnemyAstraea, "Astraea_201");
				break;
			case 8010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578010));
				orderActorToFactory(1105711010, EnemyVesta, "Vesta_202");
				break;
			case 8110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578110));
				orderActorToFactory(1105711110, EnemyVesta, "Vesta_203");
				break;
			case 8210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578210));
				orderActorToFactory(1105711210, EnemyVesta, "Vesta_204");
				break;
			case 8310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578310));
				orderActorToFactory(1105711310, EnemyVesta, "Vesta_205");
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
				orderActorToFactory(1105711410, EnemyVesta, "Vesta_206");
				break;
			case 8500:
				orderActorToFactory(1116711500, EnemyAstraea, "Astraea_207");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112778500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127711500, EnemyCeres, "Ceres_208", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578510));
				orderActorToFactory(1105711510, EnemyVesta, "Vesta_209");
				break;
			case 8530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112878530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128711530, EnemyCeres, "Ceres_210", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112978560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129711560, EnemyCeres, "Ceres_211", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113078590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130711590, EnemyCeres, "Ceres_212", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
			case 8610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578610));
				orderActorToFactory(1105711610, EnemyVesta, "Vesta_213");
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113178620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131711620, EnemyCeres, "Ceres_214", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113278650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132711650, EnemyCeres, "Ceres_215", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8700:
				orderActorToFactory(1111711700, EnemyAstraea, "Astraea_216");
				break;
			case 8710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578710));
				orderActorToFactory(1105711710, EnemyVesta, "Vesta_217");
				break;
			case 8810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578810));
				orderActorToFactory(1105711810, EnemyVesta, "Vesta_218");
				break;
			case 8910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110578910));
				orderActorToFactory(1105711910, EnemyVesta, "Vesta_219");
				break;
			case 9010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579010));
				orderActorToFactory(1105712010, EnemyVesta, "Vesta_220");
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
			case 9110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579110));
				orderActorToFactory(1105712110, EnemyVesta, "Vesta_221");
				break;
			case 9200:
				orderActorToFactory(1119712200, EnemyAstraea, "Astraea_222");
				break;
			case 9210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579210));
				orderActorToFactory(1105712210, EnemyVesta, "Vesta_223");
				break;
			case 9310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579310));
				orderActorToFactory(1105712310, EnemyVesta, "Vesta_224");
				break;
			case 9400:
				orderActorToFactory(1114712400, EnemyAstraea, "Astraea_225");
				break;
			case 9410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579410));
				orderActorToFactory(1105712410, EnemyVesta, "Vesta_226");
				break;
			case 9500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112779500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127712500, EnemyCeres, "Ceres_227", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579510));
				orderActorToFactory(1105712510, EnemyVesta, "Vesta_228");
				break;
			case 9530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112879530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128712530, EnemyCeres, "Ceres_229", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112979560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129712560, EnemyCeres, "Ceres_230", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113079590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130712590, EnemyCeres, "Ceres_231", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579610));
				orderActorToFactory(1105712610, EnemyVesta, "Vesta_232");
				break;
			case 9620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113179620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131712620, EnemyCeres, "Ceres_233", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113279650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132712650, EnemyCeres, "Ceres_234", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579710));
				orderActorToFactory(1105712710, EnemyVesta, "Vesta_235");
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
			case 9810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579810));
				orderActorToFactory(1105712810, EnemyVesta, "Vesta_236");
				break;
			case 9900:
				orderActorToFactory(1109712900, EnemyAstraea, "Astraea_237");
				break;
			case 9910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(110579910));
				orderActorToFactory(1105712910, EnemyVesta, "Vesta_238");
				break;
			case 10010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710010));
				orderActorToFactory(1105713010, EnemyVesta, "Vesta_239");
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
			case 10110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710110));
				orderActorToFactory(1105713110, EnemyVesta, "Vesta_240");
				break;
			case 10210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710210));
				orderActorToFactory(1105713210, EnemyVesta, "Vesta_241");
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
			case 10310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710310));
				orderActorToFactory(1105713310, EnemyVesta, "Vesta_242");
				break;
			case 10400:
				orderActorToFactory(1117713400, EnemyAstraea, "Astraea_243");
				break;
			case 10410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710410));
				orderActorToFactory(1105713410, EnemyVesta, "Vesta_244");
				break;
			case 10500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127710500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127713500, EnemyCeres, "Ceres_245", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710510));
				orderActorToFactory(1105713510, EnemyVesta, "Vesta_246");
				break;
			case 10530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128710530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128713530, EnemyCeres, "Ceres_247", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129710560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129713560, EnemyCeres, "Ceres_248", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130710590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130713590, EnemyCeres, "Ceres_249", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10600:
				orderActorToFactory(1112713600, EnemyAstraea, "Astraea_250");
				break;
			case 10610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710610));
				orderActorToFactory(1105713610, EnemyVesta, "Vesta_251");
				break;
			case 10620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131710620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131713620, EnemyCeres, "Ceres_252", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132710650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132713650, EnemyCeres, "Ceres_253", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710710));
				orderActorToFactory(1105713710, EnemyVesta, "Vesta_254");
				break;
			case 10810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710810));
				orderActorToFactory(1105713810, EnemyVesta, "Vesta_255");
				break;
			case 10910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105710910));
				orderActorToFactory(1105713910, EnemyVesta, "Vesta_256");
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
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711010));
				orderActorToFactory(1105714010, EnemyVesta, "Vesta_257");
				break;
			case 11100:
				orderActorToFactory(1120714100, EnemyAstraea, "Astraea_258");
				break;
			case 11110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711110));
				orderActorToFactory(1105714110, EnemyVesta, "Vesta_259");
				break;
			case 11210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711210));
				orderActorToFactory(1105714210, EnemyVesta, "Vesta_260");
				break;
			case 11310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711310));
				orderActorToFactory(1105714310, EnemyVesta, "Vesta_261");
				break;
			case 11410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711410));
				orderActorToFactory(1105714410, EnemyVesta, "Vesta_262");
				break;
			case 11500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116711500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127711500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127714500, EnemyCeres, "Ceres_263", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711510));
				orderActorToFactory(1105714510, EnemyVesta, "Vesta_264");
				break;
			case 11530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128711530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128714530, EnemyCeres, "Ceres_265", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129711560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129714560, EnemyCeres, "Ceres_266", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130711590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130714590, EnemyCeres, "Ceres_267", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711610));
				orderActorToFactory(1105714610, EnemyVesta, "Vesta_268");
				break;
			case 11620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131711620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131714620, EnemyCeres, "Ceres_269", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132711650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132714650, EnemyCeres, "Ceres_270", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorToFactory(1105714710, EnemyVesta, "Vesta_271");
				break;
			case 11800:
				orderActorToFactory(1110714800, EnemyAstraea, "Astraea_272");
				break;
			case 11810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711810));
				orderActorToFactory(1105714810, EnemyVesta, "Vesta_273");
				break;
			case 11910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105711910));
				orderActorToFactory(1105714910, EnemyVesta, "Vesta_274");
				break;
			case 12010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712010));
				orderActorToFactory(1105715010, EnemyVesta, "Vesta_275");
				break;
			case 12100:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_276");
				break;
			case 12110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712110));
				orderActorToFactory(1105715110, EnemyVesta, "Vesta_277");
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
			case 12210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712210));
				orderActorToFactory(1105715210, EnemyVesta, "Vesta_278");
				break;
			case 12300:
				orderActorToFactory(1118715300, EnemyAstraea, "Astraea_279");
				break;
			case 12310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712310));
				orderActorToFactory(1105715310, EnemyVesta, "Vesta_280");
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
			case 12410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712410));
				orderActorToFactory(1105715410, EnemyVesta, "Vesta_281");
				break;
			case 12500:
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_282");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127712500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127715500, EnemyCeres, "Ceres_283", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712510));
				orderActorToFactory(1105715510, EnemyVesta, "Vesta_284");
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128712530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128715530, EnemyCeres, "Ceres_285", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129712560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129715560, EnemyCeres, "Ceres_286", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130712590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130715590, EnemyCeres, "Ceres_287", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712610));
				orderActorToFactory(1105715610, EnemyVesta, "Vesta_288");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131712620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131715620, EnemyCeres, "Ceres_289", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132712650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132715650, EnemyCeres, "Ceres_290", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712710));
				orderActorToFactory(1105715710, EnemyVesta, "Vesta_291");
				break;
			case 12810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105712810));
				orderActorToFactory(1105715810, EnemyVesta, "Vesta_292");
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
				orderActorToFactory(1105715910, EnemyVesta, "Vesta_293");
				break;
			case 13000:
				orderActorToFactory(1121716000, EnemyAstraea, "Astraea_294");
				break;
			case 13010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713010));
				orderActorToFactory(1105716010, EnemyVesta, "Vesta_295");
				break;
			case 13110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713110));
				orderActorToFactory(1105716110, EnemyVesta, "Vesta_296");
				break;
			case 13210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713210));
				orderActorToFactory(1105716210, EnemyVesta, "Vesta_297");
				break;
			case 13310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713310));
				orderActorToFactory(1105716310, EnemyVesta, "Vesta_298");
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
			case 13410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713410));
				orderActorToFactory(1105716410, EnemyVesta, "Vesta_299");
				break;
			case 13500:
				orderActorToFactory(1116716500, EnemyAstraea, "Astraea_300");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127713500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127716500, EnemyCeres, "Ceres_301", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713510));
				orderActorToFactory(1105716510, EnemyVesta, "Vesta_302");
				break;
			case 13530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128713530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128716530, EnemyCeres, "Ceres_303", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129713560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129716560, EnemyCeres, "Ceres_304", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130713590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130716590, EnemyCeres, "Ceres_305", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
			case 13610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713610));
				orderActorToFactory(1105716610, EnemyVesta, "Vesta_306");
				break;
			case 13620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131713620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131716620, EnemyCeres, "Ceres_307", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132713650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132716650, EnemyCeres, "Ceres_308", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13700:
				orderActorToFactory(1111716700, EnemyAstraea, "Astraea_309");
				break;
			case 13710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713710));
				orderActorToFactory(1105716710, EnemyVesta, "Vesta_310");
				break;
			case 13810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713810));
				orderActorToFactory(1105716810, EnemyVesta, "Vesta_311");
				break;
			case 13910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105713910));
				orderActorToFactory(1105716910, EnemyVesta, "Vesta_312");
				break;
			case 14010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714010));
				orderActorToFactory(1105717010, EnemyVesta, "Vesta_313");
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
				orderActorToFactory(1105717110, EnemyVesta, "Vesta_314");
				break;
			case 14200:
				orderActorToFactory(1119717200, EnemyAstraea, "Astraea_315");
				break;
			case 14210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714210));
				orderActorToFactory(1105717210, EnemyVesta, "Vesta_316");
				break;
			case 14310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714310));
				orderActorToFactory(1105717310, EnemyVesta, "Vesta_317");
				break;
			case 14400:
				orderActorToFactory(1114717400, EnemyAstraea, "Astraea_318");
				break;
			case 14410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714410));
				orderActorToFactory(1105717410, EnemyVesta, "Vesta_319");
				break;
			case 14500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127714500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127717500, EnemyCeres, "Ceres_320", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714510));
				orderActorToFactory(1105717510, EnemyVesta, "Vesta_321");
				break;
			case 14530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128714530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128717530, EnemyCeres, "Ceres_322", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129714560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129717560, EnemyCeres, "Ceres_323", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130714590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130717590, EnemyCeres, "Ceres_324", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714610));
				orderActorToFactory(1105717610, EnemyVesta, "Vesta_325");
				break;
			case 14620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131714620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131717620, EnemyCeres, "Ceres_326", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132714650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132717650, EnemyCeres, "Ceres_327", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714710));
				orderActorToFactory(1105717710, EnemyVesta, "Vesta_328");
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
			case 14810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714810));
				orderActorToFactory(1105717810, EnemyVesta, "Vesta_329");
				break;
			case 14900:
				orderActorToFactory(1109717900, EnemyAstraea, "Astraea_330");
				break;
			case 14910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105714910));
				orderActorToFactory(1105717910, EnemyVesta, "Vesta_331");
				break;
			case 15010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715010));
				orderActorToFactory(1105718010, EnemyVesta, "Vesta_332");
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
			case 15110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715110));
				orderActorToFactory(1105718110, EnemyVesta, "Vesta_333");
				break;
			case 15210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715210));
				orderActorToFactory(1105718210, EnemyVesta, "Vesta_334");
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
				orderActorToFactory(1105718310, EnemyVesta, "Vesta_335");
				break;
			case 15400:
				orderActorToFactory(1117718400, EnemyAstraea, "Astraea_336");
				break;
			case 15410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715410));
				orderActorToFactory(1105718410, EnemyVesta, "Vesta_337");
				break;
			case 15500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127715500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127718500, EnemyCeres, "Ceres_338", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715510));
				orderActorToFactory(1105718510, EnemyVesta, "Vesta_339");
				break;
			case 15530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128715530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128718530, EnemyCeres, "Ceres_340", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129715560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129718560, EnemyCeres, "Ceres_341", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130715590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130718590, EnemyCeres, "Ceres_342", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15600:
				orderActorToFactory(1112718600, EnemyAstraea, "Astraea_343");
				break;
			case 15610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715610));
				orderActorToFactory(1105718610, EnemyVesta, "Vesta_344");
				break;
			case 15620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131715620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131718620, EnemyCeres, "Ceres_345", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132715650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132718650, EnemyCeres, "Ceres_346", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715710));
				orderActorToFactory(1105718710, EnemyVesta, "Vesta_347");
				break;
			case 15810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715810));
				orderActorToFactory(1105718810, EnemyVesta, "Vesta_348");
				break;
			case 15910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105715910));
				orderActorToFactory(1105718910, EnemyVesta, "Vesta_349");
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
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716010));
				orderActorToFactory(1105719010, EnemyVesta, "Vesta_350");
				break;
			case 16100:
				orderActorToFactory(1120719100, EnemyAstraea, "Astraea_351");
				break;
			case 16110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716110));
				orderActorToFactory(1105719110, EnemyVesta, "Vesta_352");
				break;
			case 16210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716210));
				orderActorToFactory(1105719210, EnemyVesta, "Vesta_353");
				break;
			case 16310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716310));
				orderActorToFactory(1105719310, EnemyVesta, "Vesta_354");
				break;
			case 16410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716410));
				orderActorToFactory(1105719410, EnemyVesta, "Vesta_355");
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
				orderActorWithDpToFactory(1127719500, EnemyCeres, "Ceres_356", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716510));
				orderActorToFactory(1105719510, EnemyVesta, "Vesta_357");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128716530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128719530, EnemyCeres, "Ceres_358", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129716560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129719560, EnemyCeres, "Ceres_359", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130716590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130719590, EnemyCeres, "Ceres_360", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716610));
				orderActorToFactory(1105719610, EnemyVesta, "Vesta_361");
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131716620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131719620, EnemyCeres, "Ceres_362", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132716650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132719650, EnemyCeres, "Ceres_363", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
			case 16710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716710));
				orderActorToFactory(1105719710, EnemyVesta, "Vesta_364");
				break;
			case 16800:
				orderActorToFactory(1110719800, EnemyAstraea, "Astraea_365");
				break;
			case 16810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716810));
				orderActorToFactory(1105719810, EnemyVesta, "Vesta_366");
				break;
			case 16910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105716910));
				orderActorToFactory(1105719910, EnemyVesta, "Vesta_367");
				break;
			case 17010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717010));
				orderActorToFactory(1105720010, EnemyVesta, "Vesta_368");
				break;
			case 17110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717110));
				orderActorToFactory(1105720110, EnemyVesta, "Vesta_369");
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
			case 17210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717210));
				orderActorToFactory(1105720210, EnemyVesta, "Vesta_370");
				break;
			case 17310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717310));
				orderActorToFactory(1105720310, EnemyVesta, "Vesta_371");
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
				orderActorToFactory(1105720410, EnemyVesta, "Vesta_372");
				break;
			case 17500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127717500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717510));
				orderActorToFactory(1105720510, EnemyVesta, "Vesta_373");
				break;
			case 17530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128717530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129717560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130717590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717610));
				orderActorToFactory(1105720610, EnemyVesta, "Vesta_374");
				break;
			case 17620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131717620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132717650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717710));
				orderActorToFactory(1105720710, EnemyVesta, "Vesta_375");
				break;
			case 17810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717810));
				orderActorToFactory(1105720810, EnemyVesta, "Vesta_376");
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
			case 17910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105717910));
				orderActorToFactory(1105720910, EnemyVesta, "Vesta_377");
				break;
			case 18010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718010));
				orderActorToFactory(1105721010, EnemyVesta, "Vesta_378");
				break;
			case 18110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718110));
				orderActorToFactory(1105721110, EnemyVesta, "Vesta_379");
				break;
			case 18210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718210));
				orderActorToFactory(1105721210, EnemyVesta, "Vesta_380");
				break;
			case 18310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718310));
				orderActorToFactory(1105721310, EnemyVesta, "Vesta_381");
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
			case 18410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718410));
				orderActorToFactory(1105721410, EnemyVesta, "Vesta_382");
				break;
			case 18500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127718500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718510));
				orderActorToFactory(1105721510, EnemyVesta, "Vesta_383");
				break;
			case 18530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128718530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129718560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130718590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
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
				orderActorToFactory(1105721610, EnemyVesta, "Vesta_384");
				break;
			case 18620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131718620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132718650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718710));
				orderActorToFactory(1105721710, EnemyVesta, "Vesta_385");
				break;
			case 18810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718810));
				orderActorToFactory(1105721810, EnemyVesta, "Vesta_386");
				break;
			case 18910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105718910));
				orderActorToFactory(1105721910, EnemyVesta, "Vesta_387");
				break;
			case 19010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719010));
				orderActorToFactory(1105722010, EnemyVesta, "Vesta_388");
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
			case 19110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719110));
				orderActorToFactory(1105722110, EnemyVesta, "Vesta_389");
				break;
			case 19210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719210));
				orderActorToFactory(1105722210, EnemyVesta, "Vesta_390");
				break;
			case 19310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719310));
				orderActorToFactory(1105722310, EnemyVesta, "Vesta_391");
				break;
			case 19410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719410));
				orderActorToFactory(1105722410, EnemyVesta, "Vesta_392");
				break;
			case 19500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127719500);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719510));
				orderActorToFactory(1105722510, EnemyVesta, "Vesta_393");
				break;
			case 19530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128719530);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129719560);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130719590);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719610));
				orderActorToFactory(1105722610, EnemyVesta, "Vesta_394");
				break;
			case 19620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131719620);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132719650);
				getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719710));
				orderActorToFactory(1105722710, EnemyVesta, "Vesta_395");
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
				orderActorToFactory(1105722810, EnemyVesta, "Vesta_396");
				break;
			case 19910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105719910));
				orderActorToFactory(1105722910, EnemyVesta, "Vesta_397");
				break;
			case 20010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720010));
				orderActorToFactory(1105723010, EnemyVesta, "Vesta_398");
				break;
			case 20110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720110));
				orderActorToFactory(1105723110, EnemyVesta, "Vesta_399");
				break;
			case 20210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720210));
				orderActorToFactory(1105723210, EnemyVesta, "Vesta_400");
				break;
			case 20310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720310));
				orderActorToFactory(1105723310, EnemyVesta, "Vesta_401");
				break;
			case 20410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720410));
				orderActorToFactory(1105723410, EnemyVesta, "Vesta_402");
				break;
			case 20510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720510));
				orderActorToFactory(1105723510, EnemyVesta, "Vesta_403");
				break;
			case 20610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720610));
				orderActorToFactory(1105723610, EnemyVesta, "Vesta_404");
				break;
			case 20710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720710));
				orderActorToFactory(1105723710, EnemyVesta, "Vesta_405");
				break;
			case 20810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720810));
				orderActorToFactory(1105723810, EnemyVesta, "Vesta_406");
				break;
			case 20910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105720910));
				orderActorToFactory(1105723910, EnemyVesta, "Vesta_407");
				break;
			case 21010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721010));
				orderActorToFactory(1105724010, EnemyVesta, "Vesta_408");
				break;
			case 21110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721110));
				orderActorToFactory(1105724110, EnemyVesta, "Vesta_409");
				break;
			case 21210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721210));
				orderActorToFactory(1105724210, EnemyVesta, "Vesta_410");
				break;
			case 21310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721310));
				orderActorToFactory(1105724310, EnemyVesta, "Vesta_411");
				break;
			case 21410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721410));
				orderActorToFactory(1105724410, EnemyVesta, "Vesta_412");
				break;
			case 21510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721510));
				orderActorToFactory(1105724510, EnemyVesta, "Vesta_413");
				break;
			case 21610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721610));
				orderActorToFactory(1105724610, EnemyVesta, "Vesta_414");
				break;
			case 21710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721710));
				orderActorToFactory(1105724710, EnemyVesta, "Vesta_415");
				break;
			case 21810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721810));
				orderActorToFactory(1105724810, EnemyVesta, "Vesta_416");
				break;
			case 21910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105721910));
				orderActorToFactory(1105724910, EnemyVesta, "Vesta_417");
				break;
			case 22010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722010));
				orderActorToFactory(1105725010, EnemyVesta, "Vesta_418");
				break;
			case 22110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722110));
				orderActorToFactory(1105725110, EnemyVesta, "Vesta_419");
				break;
			case 22210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722210));
				orderActorToFactory(1105725210, EnemyVesta, "Vesta_420");
				break;
			case 22310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722310));
				orderActorToFactory(1105725310, EnemyVesta, "Vesta_421");
				break;
			case 22410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722410));
				orderActorToFactory(1105725410, EnemyVesta, "Vesta_422");
				break;
			case 22510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722510));
				orderActorToFactory(1105725510, EnemyVesta, "Vesta_423");
				break;
			case 22610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722610));
				orderActorToFactory(1105725610, EnemyVesta, "Vesta_424");
				break;
			case 22710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722710));
				orderActorToFactory(1105725710, EnemyVesta, "Vesta_425");
				break;
			case 22810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722810));
				orderActorToFactory(1105725810, EnemyVesta, "Vesta_426");
				break;
			case 22910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105722910));
				orderActorToFactory(1105725910, EnemyVesta, "Vesta_427");
				break;
			case 23010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723010));
				orderActorToFactory(1105726010, EnemyVesta, "Vesta_428");
				break;
			case 23110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723110));
				orderActorToFactory(1105726110, EnemyVesta, "Vesta_429");
				break;
			case 23210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723210));
				orderActorToFactory(1105726210, EnemyVesta, "Vesta_430");
				break;
			case 23310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723310));
				orderActorToFactory(1105726310, EnemyVesta, "Vesta_431");
				break;
			case 23410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723410));
				orderActorToFactory(1105726410, EnemyVesta, "Vesta_432");
				break;
			case 23510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723510));
				orderActorToFactory(1105726510, EnemyVesta, "Vesta_433");
				break;
			case 23610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723610));
				orderActorToFactory(1105726610, EnemyVesta, "Vesta_434");
				break;
			case 23710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723710));
				orderActorToFactory(1105726710, EnemyVesta, "Vesta_435");
				break;
			case 23810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723810));
				orderActorToFactory(1105726810, EnemyVesta, "Vesta_436");
				break;
			case 23910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105723910));
				orderActorToFactory(1105726910, EnemyVesta, "Vesta_437");
				break;
			case 24010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724010));
				orderActorToFactory(1105727010, EnemyVesta, "Vesta_438");
				break;
			case 24110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724110));
				orderActorToFactory(1105727110, EnemyVesta, "Vesta_439");
				break;
			case 24210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724210));
				orderActorToFactory(1105727210, EnemyVesta, "Vesta_440");
				break;
			case 24310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724310));
				orderActorToFactory(1105727310, EnemyVesta, "Vesta_441");
				break;
			case 24410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724410));
				orderActorToFactory(1105727410, EnemyVesta, "Vesta_442");
				break;
			case 24510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724510));
				orderActorToFactory(1105727510, EnemyVesta, "Vesta_443");
				break;
			case 24610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724610));
				orderActorToFactory(1105727610, EnemyVesta, "Vesta_444");
				break;
			case 24710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724710));
				orderActorToFactory(1105727710, EnemyVesta, "Vesta_445");
				break;
			case 24810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724810));
				orderActorToFactory(1105727810, EnemyVesta, "Vesta_446");
				break;
			case 24910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105724910));
				orderActorToFactory(1105727910, EnemyVesta, "Vesta_447");
				break;
			case 25010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725010));
				orderActorToFactory(1105728010, EnemyVesta, "Vesta_448");
				break;
			case 25110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725110));
				orderActorToFactory(1105728110, EnemyVesta, "Vesta_449");
				break;
			case 25210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725210));
				orderActorToFactory(1105728210, EnemyVesta, "Vesta_450");
				break;
			case 25310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725310));
				orderActorToFactory(1105728310, EnemyVesta, "Vesta_451");
				break;
			case 25410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725410));
				orderActorToFactory(1105728410, EnemyVesta, "Vesta_452");
				break;
			case 25510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725510));
				orderActorToFactory(1105728510, EnemyVesta, "Vesta_453");
				break;
			case 25610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725610));
				orderActorToFactory(1105728610, EnemyVesta, "Vesta_454");
				break;
			case 25710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725710));
				orderActorToFactory(1105728710, EnemyVesta, "Vesta_455");
				break;
			case 25810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725810));
				orderActorToFactory(1105728810, EnemyVesta, "Vesta_456");
				break;
			case 25910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105725910));
				orderActorToFactory(1105728910, EnemyVesta, "Vesta_457");
				break;
			case 26010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726010));
				orderActorToFactory(1105729010, EnemyVesta, "Vesta_458");
				break;
			case 26110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726110));
				orderActorToFactory(1105729110, EnemyVesta, "Vesta_459");
				break;
			case 26210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726210));
				orderActorToFactory(1105729210, EnemyVesta, "Vesta_460");
				break;
			case 26310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726310));
				orderActorToFactory(1105729310, EnemyVesta, "Vesta_461");
				break;
			case 26410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726410));
				orderActorToFactory(1105729410, EnemyVesta, "Vesta_462");
				break;
			case 26510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726510));
				orderActorToFactory(1105729510, EnemyVesta, "Vesta_463");
				break;
			case 26610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726610));
				orderActorToFactory(1105729610, EnemyVesta, "Vesta_464");
				break;
			case 26710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726710));
				orderActorToFactory(1105729710, EnemyVesta, "Vesta_465");
				break;
			case 26810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726810));
				orderActorToFactory(1105729810, EnemyVesta, "Vesta_466");
				break;
			case 26910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105726910));
				orderActorToFactory(1105729910, EnemyVesta, "Vesta_467");
				break;
			case 27010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727010));
				orderActorToFactory(1105730010, EnemyVesta, "Vesta_468");
				break;
			case 27110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727110));
				orderActorToFactory(1105730110, EnemyVesta, "Vesta_469");
				break;
			case 27210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727210));
				orderActorToFactory(1105730210, EnemyVesta, "Vesta_470");
				break;
			case 27310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727310));
				orderActorToFactory(1105730310, EnemyVesta, "Vesta_471");
				break;
			case 27410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727410));
				orderActorToFactory(1105730410, EnemyVesta, "Vesta_472");
				break;
			case 27510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727510));
				orderActorToFactory(1105730510, EnemyVesta, "Vesta_473");
				break;
			case 27610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727610));
				orderActorToFactory(1105730610, EnemyVesta, "Vesta_474");
				break;
			case 27710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727710));
				orderActorToFactory(1105730710, EnemyVesta, "Vesta_475");
				break;
			case 27810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727810));
				orderActorToFactory(1105730810, EnemyVesta, "Vesta_476");
				break;
			case 27910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105727910));
				orderActorToFactory(1105730910, EnemyVesta, "Vesta_477");
				break;
			case 28010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728010));
				orderActorToFactory(1105731010, EnemyVesta, "Vesta_478");
				break;
			case 28110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728110));
				orderActorToFactory(1105731110, EnemyVesta, "Vesta_479");
				break;
			case 28210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728210));
				orderActorToFactory(1105731210, EnemyVesta, "Vesta_480");
				break;
			case 28310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728310));
				orderActorToFactory(1105731310, EnemyVesta, "Vesta_481");
				break;
			case 28410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728410));
				orderActorToFactory(1105731410, EnemyVesta, "Vesta_482");
				break;
			case 28510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728510));
				orderActorToFactory(1105731510, EnemyVesta, "Vesta_483");
				break;
			case 28610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728610));
				orderActorToFactory(1105731610, EnemyVesta, "Vesta_484");
				break;
			case 28710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728710));
				orderActorToFactory(1105731710, EnemyVesta, "Vesta_485");
				break;
			case 28810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728810));
				orderActorToFactory(1105731810, EnemyVesta, "Vesta_486");
				break;
			case 28910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105728910));
				orderActorToFactory(1105731910, EnemyVesta, "Vesta_487");
				break;
			case 29010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729010));
				break;
			case 29110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729110));
				break;
			case 29210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729210));
				break;
			case 29310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729310));
				break;
			case 29410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729410));
				break;
			case 29510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729510));
				break;
			case 29610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729610));
				break;
			case 29710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729710));
				break;
			case 29810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729810));
				break;
			case 29910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105729910));
				break;
			case 30010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730010));
				break;
			case 30110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730110));
				break;
			case 30210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730210));
				break;
			case 30310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730310));
				break;
			case 30410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730410));
				break;
			case 30510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730510));
				break;
			case 30610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730610));
				break;
			case 30710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730710));
				break;
			case 30810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730810));
				break;
			case 30910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105730910));
				break;
			case 31010:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731010));
				break;
			case 31110:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731110));
				break;
			case 31210:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731210));
				break;
			case 31310:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731310));
				break;
			case 31410:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731410));
				break;
			case 31510:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731510));
				break;
			case 31610:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731610));
				break;
			case 31710:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731710));
				break;
			case 31810:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731810));
				break;
			case 31910:
				getLordActor()->addSubGroup(KIND_ENEMY_BODY, obtainActorFromFactory(1105731910));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_frame_of_active== 2) {

        _TRACE_("Stage01MainScene::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
        // ���ʃV�[����z���Ɉړ�
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_frame_of_active== 1) {
    //		_TRACE_("Stage01MainScene::processFinally ���͂����Ȃ��~���܂��BGameMainScene���������Ă����͂��[");
    //		this->inactivateTree(); //GameMainScene���������Ă����
    //	}
}

Stage01MainScene::~Stage01MainScene() {
    //NEW����processBehavior�܂ł̊Ԃɋ����I�����ꂽ�ꍇ�A
    //_pDispatcher�͂ǂ̃c���[�ɂ��������Ă��Ȃ��B
    if (_pDispatcher->getParent() == NULL) {
        _TRACE_("_pDispatcher���������̂��ߓƎ�delete");
        DELETE_IMPOSSIBLE_NULL(_pDispatcher);
    }
}
