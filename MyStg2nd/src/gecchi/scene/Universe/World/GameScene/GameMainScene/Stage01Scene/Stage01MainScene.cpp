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
    getLordActor()->accept(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
    // gen01 start
	DWORD dw[] = {1,10,70,100,130,190,250,310,370,430,490,500,530,550,560,590,610,620,650,670,730,790,850,910,970,1030,1090,1150,1210,1270,1330,1390,1450,1500,1510,1530,1560,1570,1590,1620,1630,1650,1690,1700,1750,1810,1870,1900,1930,1990,2050,2110,2170,2230,2290,2350,2410,2470,2500,2530,2560,2590,2620,2650,2710,2770,2830,2890,2950,3010,3070,3100,3130,3190,3250,3310,3370,3430,3490,3500,3530,3550,3560,3590,3610,3620,3650,3670,3700,3730,3790,3850,3910,3970,4030,4090,4150,4210,4270,4330,4390,4450,4500,4510,4530,4560,4570,4590,4620,4630,4650,4690,4750,4810,4870,4900,4930,4990,5050,5100,5110,5170,5230,5290,5350,5410,5470,5500,5530,5560,5590,5620,5650,5710,5770,5830,5890,5950,6010,6070,6130,6190,6200,6250,6310,6370,6430,6490,6500,6530,6550,6560,6590,6610,6620,6650,6670,6700,6730,6790,6850,6900,6910,6970,7030,7090,7150,7210,7270,7330,7390,7450,7500,7510,7530,7560,7570,7590,7620,7630,7650,7690,7750,7810,7870,7930,7990,8000,8050,8100,8110,8170,8200,8230,8290,8350,8410,8470,8500,8530,8560,8590,8620,8650,8700,8710,8770,8830,8890,8950,9010,9070,9130,9190,9250,9310,9370,9430,9490,9500,9530,9550,9560,9590,9610,9620,9650,9670,9730,9790,9800,9850,9900,9910,9970,10000,10030,10090,10100,10150,10210,10270,10330,10390,10450,10500,10510,10530,10560,10570,10590,10620,10630,10650,10690,10750,10810,10870,10930,10990,11050,11110,11170,11200,11230,11290,11350,11410,11470,11500,11530,11560,11590,11620,11650,11700,11710,11770,11800,11830,11890,11900,11950,12010,12070,12130,12190,12250,12310,12370,12430,12490,12500,12530,12550,12560,12590,12610,12620,12650,12670,12730,12790,12850,12910,12970,13000,13030,13090,13100,13150,13200,13210,13270,13330,13390,13450,13500,13510,13530,13560,13570,13590,13620,13630,13650,13690,13700,13750,13810,13870,13930,13990,14050,14110,14170,14230,14290,14350,14410,14470,14500,14530,14560,14590,14620,14650,14710,14770,14800,14830,14890,14900,14950,15000,15010,15070,15100,15130,15190,15250,15310,15370,15430,15490,15500,15530,15550,15560,15590,15610,15620,15650,15670,15730,15790,15850,15910,15970,16030,16090,16150,16200,16210,16270,16330,16390,16450,16500,16510,16530,16560,16570,16590,16620,16630,16650,16690,16700,16750,16800,16810,16870,16900,16930,16990,17050,17110,17170,17230,17290,17350,17410,17470,17500,17530,17560,17590,17620,17650,17710,17770,17830,17890,17950,18000,18010,18070,18130,18190,18200,18250,18310,18370,18430,18490,18500,18530,18550,18560,18590,18610,18620,18650,18670,18700,18730,18790,18850,18910,18970,19030,19090,19150,19210,19270,19330,19390,19450,19500,19510,19530,19560,19570,19590,19620,19630,19650,19690,19750,19810,19870,19930,19990,20000,20050,20110,20170,20230,20290,20350,20410,20470,20530,20590,20650,20710,20770,20830,20890,20950,21010,21070,21130,21190,21250,21310,21370,21430,21490,21550,21610,21670,21730,21790,21850,21910,21970,22030,22090,22150,22210,22270,22330,22390,22450,22510,22570,22630,22690,22750,22810,22870,22930,22990,23050,23110,23170,23230,23290,23350,23410,23470,23530,23590,23650,23710,23770,23830,23890,23950,24010,24070,24130,24190,24250,24310,24370,24430,24490,24550,24610,24670,24730,24790,24850,24910,24970,25030,25090,25150,25210,25270,25330,25390,25450,25510,25570,25630,25690,25750,25810,25870,25930,25990,26050,26110,26170,26230,26290,26350,26410,26470,26530,26590,26650,26710,26770,26830,26890,26950,27010,27070,27130,27190,27250,27310,27370,27430,27490,27550,27610,27670,27730,27790,27850,27910,27970,28030,28090,28150,28210,28270,28330,28390,28450,28510,28570,28630,28690,28750,28810,28870,28930,28990,29050,29110,29170,29230,29290,29350,29410,29470,29530,29590,29650,29710,29770,29830,29890,29950,30010,30070,30130,30190,30250,30310,30370,30430,30490,30550,30610,30670,30730,30790,30850,30910,30970,31030,31090,31150,31210,31270,31330,31390,31450,31510,31570,31630,31690,31750,31810,31870,31930,31990};
	_paFrame_NextEvent = new DWORD[675];
	for (int i = 0; i < 675; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105710, EnemyVesta, "Vesta_1");
	orderActorToFactory(1105770, EnemyVesta, "Vesta_2");
	orderActorToFactory(11057130, EnemyVesta, "Vesta_3");
	orderActorToFactory(11057190, EnemyVesta, "Vesta_4");
	orderActorToFactory(11057250, EnemyVesta, "Vesta_5");
	orderActorToFactory(11057310, EnemyVesta, "Vesta_6");
	orderActorToFactory(11057370, EnemyVesta, "Vesta_7");
	orderActorToFactory(11057430, EnemyVesta, "Vesta_8");
	orderActorToFactory(11057490, EnemyVesta, "Vesta_9");
	orderActorToFactory(11057550, EnemyVesta, "Vesta_10");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_11");
	orderActorToFactory(110971900, EnemyAstraea, "Astraea_12");
	orderActorWithDpToFactory(11377500, EnemyCeres, "Ceres_13", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113771500, EnemyCeres, "Ceres_14", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11387530, EnemyCeres, "Ceres_15", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113871530, EnemyCeres, "Ceres_16", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11397560, EnemyCeres, "Ceres_17", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113971560, EnemyCeres, "Ceres_18", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11407590, EnemyCeres, "Ceres_19", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(114071590, EnemyCeres, "Ceres_20", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11417620, EnemyCeres, "Ceres_21", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(114171620, EnemyCeres, "Ceres_22", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11427650, EnemyCeres, "Ceres_23", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(114271650, EnemyCeres, "Ceres_24", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_frame_of_life == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_frame_of_life) {
			case 1:
				break;
			case 10:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710));
				orderActorToFactory(11057610, EnemyVesta, "Vesta_25");
				break;
			case 70:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105770));
				orderActorToFactory(11057670, EnemyVesta, "Vesta_26");
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057130));
				orderActorToFactory(11057730, EnemyVesta, "Vesta_27");
				break;
			case 190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057190));
				orderActorToFactory(11057790, EnemyVesta, "Vesta_28");
				break;
			case 250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057250));
				orderActorToFactory(11057850, EnemyVesta, "Vesta_29");
				break;
			case 310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057310));
				orderActorToFactory(11057910, EnemyVesta, "Vesta_30");
				break;
			case 370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057370));
				orderActorToFactory(11057970, EnemyVesta, "Vesta_31");
				break;
			case 430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057430));
				orderActorToFactory(110571030, EnemyVesta, "Vesta_32");
				break;
			case 490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057490));
				orderActorToFactory(110571090, EnemyVesta, "Vesta_33");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113772500, EnemyCeres, "Ceres_34", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113872530, EnemyCeres, "Ceres_35", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057550));
				orderActorToFactory(110571150, EnemyVesta, "Vesta_36");
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113972560, EnemyCeres, "Ceres_37", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11407590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114072590, EnemyCeres, "Ceres_38", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057610));
				orderActorToFactory(110571210, EnemyVesta, "Vesta_39");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11417620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114172620, EnemyCeres, "Ceres_40", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11427650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114272650, EnemyCeres, "Ceres_41", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057670));
				orderActorToFactory(110571270, EnemyVesta, "Vesta_42");
				break;
			case 730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057730));
				orderActorToFactory(110571330, EnemyVesta, "Vesta_43");
				break;
			case 790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057790));
				orderActorToFactory(110571390, EnemyVesta, "Vesta_44");
				break;
			case 850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057850));
				orderActorToFactory(110571450, EnemyVesta, "Vesta_45");
				break;
			case 910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057910));
				orderActorToFactory(110571510, EnemyVesta, "Vesta_46");
				break;
			case 970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057970));
				orderActorToFactory(110571570, EnemyVesta, "Vesta_47");
				break;
			case 1030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571030));
				orderActorToFactory(110571630, EnemyVesta, "Vesta_48");
				break;
			case 1090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571090));
				orderActorToFactory(110571690, EnemyVesta, "Vesta_49");
				break;
			case 1150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571150));
				orderActorToFactory(110571750, EnemyVesta, "Vesta_50");
				break;
			case 1210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571210));
				orderActorToFactory(110571810, EnemyVesta, "Vesta_51");
				break;
			case 1270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571270));
				orderActorToFactory(110571870, EnemyVesta, "Vesta_52");
				break;
			case 1330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571330));
				orderActorToFactory(110571930, EnemyVesta, "Vesta_53");
				break;
			case 1390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571390));
				orderActorToFactory(110571990, EnemyVesta, "Vesta_54");
				break;
			case 1450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571450));
				orderActorToFactory(110572050, EnemyVesta, "Vesta_55");
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113773500, EnemyCeres, "Ceres_56", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571510));
				orderActorToFactory(110572110, EnemyVesta, "Vesta_57");
				break;
			case 1530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113871530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113873530, EnemyCeres, "Ceres_58", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113973560, EnemyCeres, "Ceres_59", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571570));
				orderActorToFactory(110572170, EnemyVesta, "Vesta_60");
				break;
			case 1590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114071590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114073590, EnemyCeres, "Ceres_61", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114171620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114173620, EnemyCeres, "Ceres_62", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571630));
				orderActorToFactory(110572230, EnemyVesta, "Vesta_63");
				break;
			case 1650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114271650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114273650, EnemyCeres, "Ceres_64", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571690));
				orderActorToFactory(110572290, EnemyVesta, "Vesta_65");
				break;
			case 1700:
				orderActorToFactory(111173700, EnemyAstraea, "Astraea_66");
				break;
			case 1750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571750));
				orderActorToFactory(110572350, EnemyVesta, "Vesta_67");
				break;
			case 1810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571810));
				orderActorToFactory(110572410, EnemyVesta, "Vesta_68");
				break;
			case 1870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571870));
				orderActorToFactory(110572470, EnemyVesta, "Vesta_69");
				break;
			case 1900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110971900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				break;
			case 1930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571930));
				orderActorToFactory(110572530, EnemyVesta, "Vesta_70");
				break;
			case 1990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571990));
				orderActorToFactory(110572590, EnemyVesta, "Vesta_71");
				break;
			case 2050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572050));
				orderActorToFactory(110572650, EnemyVesta, "Vesta_72");
				break;
			case 2110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572110));
				orderActorToFactory(110572710, EnemyVesta, "Vesta_73");
				break;
			case 2170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572170));
				orderActorToFactory(110572770, EnemyVesta, "Vesta_74");
				break;
			case 2230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572230));
				orderActorToFactory(110572830, EnemyVesta, "Vesta_75");
				break;
			case 2290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572290));
				orderActorToFactory(110572890, EnemyVesta, "Vesta_76");
				break;
			case 2350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572350));
				orderActorToFactory(110572950, EnemyVesta, "Vesta_77");
				break;
			case 2410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572410));
				orderActorToFactory(110573010, EnemyVesta, "Vesta_78");
				break;
			case 2470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572470));
				orderActorToFactory(110573070, EnemyVesta, "Vesta_79");
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113774500, EnemyCeres, "Ceres_80", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572530));
				orderActorToFactory(110573130, EnemyVesta, "Vesta_81");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113872530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113874530, EnemyCeres, "Ceres_82", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113972560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113974560, EnemyCeres, "Ceres_83", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572590));
				orderActorToFactory(110573190, EnemyVesta, "Vesta_84");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114072590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114074590, EnemyCeres, "Ceres_85", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114172620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114174620, EnemyCeres, "Ceres_86", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572650));
				orderActorToFactory(110573250, EnemyVesta, "Vesta_87");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114272650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114274650, EnemyCeres, "Ceres_88", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572710));
				orderActorToFactory(110573310, EnemyVesta, "Vesta_89");
				break;
			case 2770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572770));
				orderActorToFactory(110573370, EnemyVesta, "Vesta_90");
				break;
			case 2830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572830));
				orderActorToFactory(110573430, EnemyVesta, "Vesta_91");
				break;
			case 2890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572890));
				orderActorToFactory(110573490, EnemyVesta, "Vesta_92");
				break;
			case 2950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572950));
				orderActorToFactory(110573550, EnemyVesta, "Vesta_93");
				break;
			case 3010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573010));
				orderActorToFactory(110573610, EnemyVesta, "Vesta_94");
				break;
			case 3070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573070));
				orderActorToFactory(110573670, EnemyVesta, "Vesta_95");
				break;
			case 3100:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_96");
				break;
			case 3130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573130));
				orderActorToFactory(110573730, EnemyVesta, "Vesta_97");
				break;
			case 3190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573190));
				orderActorToFactory(110573790, EnemyVesta, "Vesta_98");
				break;
			case 3250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573250));
				orderActorToFactory(110573850, EnemyVesta, "Vesta_99");
				break;
			case 3310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573310));
				orderActorToFactory(110573910, EnemyVesta, "Vesta_100");
				break;
			case 3370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573370));
				orderActorToFactory(110573970, EnemyVesta, "Vesta_101");
				break;
			case 3430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573430));
				orderActorToFactory(110574030, EnemyVesta, "Vesta_102");
				break;
			case 3490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573490));
				orderActorToFactory(110574090, EnemyVesta, "Vesta_103");
				break;
			case 3500:
				orderActorToFactory(111375500, EnemyAstraea, "Astraea_104");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113775500, EnemyCeres, "Ceres_105", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113873530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113875530, EnemyCeres, "Ceres_106", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573550));
				orderActorToFactory(110574150, EnemyVesta, "Vesta_107");
				break;
			case 3560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113973560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113975560, EnemyCeres, "Ceres_108", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114073590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114075590, EnemyCeres, "Ceres_109", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573610));
				orderActorToFactory(110574210, EnemyVesta, "Vesta_110");
				break;
			case 3620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114173620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114175620, EnemyCeres, "Ceres_111", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114273650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114275650, EnemyCeres, "Ceres_112", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573670));
				orderActorToFactory(110574270, EnemyVesta, "Vesta_113");
				break;
			case 3700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111173700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				break;
			case 3730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573730));
				orderActorToFactory(110574330, EnemyVesta, "Vesta_114");
				break;
			case 3790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573790));
				orderActorToFactory(110574390, EnemyVesta, "Vesta_115");
				break;
			case 3850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573850));
				orderActorToFactory(110574450, EnemyVesta, "Vesta_116");
				break;
			case 3910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573910));
				orderActorToFactory(110574510, EnemyVesta, "Vesta_117");
				break;
			case 3970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573970));
				orderActorToFactory(110574570, EnemyVesta, "Vesta_118");
				break;
			case 4030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574030));
				orderActorToFactory(110574630, EnemyVesta, "Vesta_119");
				break;
			case 4090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574090));
				orderActorToFactory(110574690, EnemyVesta, "Vesta_120");
				break;
			case 4150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574150));
				orderActorToFactory(110574750, EnemyVesta, "Vesta_121");
				break;
			case 4210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574210));
				orderActorToFactory(110574810, EnemyVesta, "Vesta_122");
				break;
			case 4270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574270));
				orderActorToFactory(110574870, EnemyVesta, "Vesta_123");
				break;
			case 4330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574330));
				orderActorToFactory(110574930, EnemyVesta, "Vesta_124");
				break;
			case 4390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574390));
				orderActorToFactory(110574990, EnemyVesta, "Vesta_125");
				break;
			case 4450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574450));
				orderActorToFactory(110575050, EnemyVesta, "Vesta_126");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113776500, EnemyCeres, "Ceres_127", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574510));
				orderActorToFactory(110575110, EnemyVesta, "Vesta_128");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113874530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113876530, EnemyCeres, "Ceres_129", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113974560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113976560, EnemyCeres, "Ceres_130", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574570));
				orderActorToFactory(110575170, EnemyVesta, "Vesta_131");
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114074590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114076590, EnemyCeres, "Ceres_132", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114174620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114176620, EnemyCeres, "Ceres_133", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574630));
				orderActorToFactory(110575230, EnemyVesta, "Vesta_134");
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114274650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114276650, EnemyCeres, "Ceres_135", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574690));
				orderActorToFactory(110575290, EnemyVesta, "Vesta_136");
				break;
			case 4750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574750));
				orderActorToFactory(110575350, EnemyVesta, "Vesta_137");
				break;
			case 4810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574810));
				orderActorToFactory(110575410, EnemyVesta, "Vesta_138");
				break;
			case 4870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574870));
				orderActorToFactory(110575470, EnemyVesta, "Vesta_139");
				break;
			case 4900:
				orderActorToFactory(110976900, EnemyAstraea, "Astraea_140");
				break;
			case 4930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574930));
				orderActorToFactory(110575530, EnemyVesta, "Vesta_141");
				break;
			case 4990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574990));
				orderActorToFactory(110575590, EnemyVesta, "Vesta_142");
				break;
			case 5050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575050));
				orderActorToFactory(110575650, EnemyVesta, "Vesta_143");
				break;
			case 5100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110775100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 5110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575110));
				orderActorToFactory(110575710, EnemyVesta, "Vesta_144");
				break;
			case 5170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575170));
				orderActorToFactory(110575770, EnemyVesta, "Vesta_145");
				break;
			case 5230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575230));
				orderActorToFactory(110575830, EnemyVesta, "Vesta_146");
				break;
			case 5290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575290));
				orderActorToFactory(110575890, EnemyVesta, "Vesta_147");
				break;
			case 5350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575350));
				orderActorToFactory(110575950, EnemyVesta, "Vesta_148");
				break;
			case 5410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575410));
				orderActorToFactory(110576010, EnemyVesta, "Vesta_149");
				break;
			case 5470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575470));
				orderActorToFactory(110576070, EnemyVesta, "Vesta_150");
				break;
			case 5500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111375500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113777500, EnemyCeres, "Ceres_151", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575530));
				orderActorToFactory(110576130, EnemyVesta, "Vesta_152");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113875530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113877530, EnemyCeres, "Ceres_153", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113975560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113977560, EnemyCeres, "Ceres_154", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575590));
				orderActorToFactory(110576190, EnemyVesta, "Vesta_155");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114075590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114077590, EnemyCeres, "Ceres_156", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114175620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114177620, EnemyCeres, "Ceres_157", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575650));
				orderActorToFactory(110576250, EnemyVesta, "Vesta_158");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114275650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114277650, EnemyCeres, "Ceres_159", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575710));
				orderActorToFactory(110576310, EnemyVesta, "Vesta_160");
				break;
			case 5770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575770));
				orderActorToFactory(110576370, EnemyVesta, "Vesta_161");
				break;
			case 5830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575830));
				orderActorToFactory(110576430, EnemyVesta, "Vesta_162");
				break;
			case 5890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575890));
				orderActorToFactory(110576490, EnemyVesta, "Vesta_163");
				break;
			case 5950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575950));
				orderActorToFactory(110576550, EnemyVesta, "Vesta_164");
				break;
			case 6010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576010));
				orderActorToFactory(110576610, EnemyVesta, "Vesta_165");
				break;
			case 6070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576070));
				orderActorToFactory(110576670, EnemyVesta, "Vesta_166");
				break;
			case 6130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576130));
				orderActorToFactory(110576730, EnemyVesta, "Vesta_167");
				break;
			case 6190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576190));
				orderActorToFactory(110576790, EnemyVesta, "Vesta_168");
				break;
			case 6200:
				orderActorToFactory(111678200, EnemyAstraea, "Astraea_169");
				break;
			case 6250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576250));
				orderActorToFactory(110576850, EnemyVesta, "Vesta_170");
				break;
			case 6310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576310));
				orderActorToFactory(110576910, EnemyVesta, "Vesta_171");
				break;
			case 6370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576370));
				orderActorToFactory(110576970, EnemyVesta, "Vesta_172");
				break;
			case 6430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576430));
				orderActorToFactory(110577030, EnemyVesta, "Vesta_173");
				break;
			case 6490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576490));
				orderActorToFactory(110577090, EnemyVesta, "Vesta_174");
				break;
			case 6500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113778500, EnemyCeres, "Ceres_175", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113876530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113878530, EnemyCeres, "Ceres_176", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576550));
				orderActorToFactory(110577150, EnemyVesta, "Vesta_177");
				break;
			case 6560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113976560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113978560, EnemyCeres, "Ceres_178", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114076590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114078590, EnemyCeres, "Ceres_179", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576610));
				orderActorToFactory(110577210, EnemyVesta, "Vesta_180");
				break;
			case 6620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114176620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114178620, EnemyCeres, "Ceres_181", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114276650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114278650, EnemyCeres, "Ceres_182", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576670));
				orderActorToFactory(110577270, EnemyVesta, "Vesta_183");
				break;
			case 6700:
				orderActorToFactory(111178700, EnemyAstraea, "Astraea_184");
				break;
			case 6730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576730));
				orderActorToFactory(110577330, EnemyVesta, "Vesta_185");
				break;
			case 6790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576790));
				orderActorToFactory(110577390, EnemyVesta, "Vesta_186");
				break;
			case 6850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576850));
				orderActorToFactory(110577450, EnemyVesta, "Vesta_187");
				break;
			case 6900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110976900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				break;
			case 6910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576910));
				orderActorToFactory(110577510, EnemyVesta, "Vesta_188");
				break;
			case 6970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576970));
				orderActorToFactory(110577570, EnemyVesta, "Vesta_189");
				break;
			case 7030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577030));
				orderActorToFactory(110577630, EnemyVesta, "Vesta_190");
				break;
			case 7090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577090));
				orderActorToFactory(110577690, EnemyVesta, "Vesta_191");
				break;
			case 7150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577150));
				orderActorToFactory(110577750, EnemyVesta, "Vesta_192");
				break;
			case 7210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577210));
				orderActorToFactory(110577810, EnemyVesta, "Vesta_193");
				break;
			case 7270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577270));
				orderActorToFactory(110577870, EnemyVesta, "Vesta_194");
				break;
			case 7330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577330));
				orderActorToFactory(110577930, EnemyVesta, "Vesta_195");
				break;
			case 7390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577390));
				orderActorToFactory(110577990, EnemyVesta, "Vesta_196");
				break;
			case 7450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577450));
				orderActorToFactory(110578050, EnemyVesta, "Vesta_197");
				break;
			case 7500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113779500, EnemyCeres, "Ceres_198", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577510));
				orderActorToFactory(110578110, EnemyVesta, "Vesta_199");
				break;
			case 7530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113877530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113879530, EnemyCeres, "Ceres_200", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113977560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(113979560, EnemyCeres, "Ceres_201", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577570));
				orderActorToFactory(110578170, EnemyVesta, "Vesta_202");
				break;
			case 7590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114077590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114079590, EnemyCeres, "Ceres_203", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114177620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114179620, EnemyCeres, "Ceres_204", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577630));
				orderActorToFactory(110578230, EnemyVesta, "Vesta_205");
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114277650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(114279650, EnemyCeres, "Ceres_206", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577690));
				orderActorToFactory(110578290, EnemyVesta, "Vesta_207");
				break;
			case 7750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577750));
				orderActorToFactory(110578350, EnemyVesta, "Vesta_208");
				break;
			case 7810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577810));
				orderActorToFactory(110578410, EnemyVesta, "Vesta_209");
				break;
			case 7870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577870));
				orderActorToFactory(110578470, EnemyVesta, "Vesta_210");
				break;
			case 7930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577930));
				orderActorToFactory(110578530, EnemyVesta, "Vesta_211");
				break;
			case 7990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577990));
				orderActorToFactory(110578590, EnemyVesta, "Vesta_212");
				break;
			case 8000:
				orderActorToFactory(1118710000, EnemyAstraea, "Astraea_213");
				break;
			case 8050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578050));
				orderActorToFactory(110578650, EnemyVesta, "Vesta_214");
				break;
			case 8100:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_215");
				break;
			case 8110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578110));
				orderActorToFactory(110578710, EnemyVesta, "Vesta_216");
				break;
			case 8170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578170));
				orderActorToFactory(110578770, EnemyVesta, "Vesta_217");
				break;
			case 8200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111678200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				break;
			case 8230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578230));
				orderActorToFactory(110578830, EnemyVesta, "Vesta_218");
				break;
			case 8290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578290));
				orderActorToFactory(110578890, EnemyVesta, "Vesta_219");
				break;
			case 8350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578350));
				orderActorToFactory(110578950, EnemyVesta, "Vesta_220");
				break;
			case 8410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578410));
				orderActorToFactory(110579010, EnemyVesta, "Vesta_221");
				break;
			case 8470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578470));
				orderActorToFactory(110579070, EnemyVesta, "Vesta_222");
				break;
			case 8500:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_223");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113778500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137710500, EnemyCeres, "Ceres_224", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578530));
				orderActorToFactory(110579130, EnemyVesta, "Vesta_225");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113878530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138710530, EnemyCeres, "Ceres_226", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113978560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139710560, EnemyCeres, "Ceres_227", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578590));
				orderActorToFactory(110579190, EnemyVesta, "Vesta_228");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114078590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140710590, EnemyCeres, "Ceres_229", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114178620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141710620, EnemyCeres, "Ceres_230", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578650));
				orderActorToFactory(110579250, EnemyVesta, "Vesta_231");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114278650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142710650, EnemyCeres, "Ceres_232", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111178700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				break;
			case 8710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578710));
				orderActorToFactory(110579310, EnemyVesta, "Vesta_233");
				break;
			case 8770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578770));
				orderActorToFactory(110579370, EnemyVesta, "Vesta_234");
				break;
			case 8830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578830));
				orderActorToFactory(110579430, EnemyVesta, "Vesta_235");
				break;
			case 8890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578890));
				orderActorToFactory(110579490, EnemyVesta, "Vesta_236");
				break;
			case 8950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578950));
				orderActorToFactory(110579550, EnemyVesta, "Vesta_237");
				break;
			case 9010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579010));
				orderActorToFactory(110579610, EnemyVesta, "Vesta_238");
				break;
			case 9070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579070));
				orderActorToFactory(110579670, EnemyVesta, "Vesta_239");
				break;
			case 9130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579130));
				orderActorToFactory(110579730, EnemyVesta, "Vesta_240");
				break;
			case 9190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579190));
				orderActorToFactory(110579790, EnemyVesta, "Vesta_241");
				break;
			case 9250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579250));
				orderActorToFactory(110579850, EnemyVesta, "Vesta_242");
				break;
			case 9310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579310));
				orderActorToFactory(110579910, EnemyVesta, "Vesta_243");
				break;
			case 9370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579370));
				orderActorToFactory(110579970, EnemyVesta, "Vesta_244");
				break;
			case 9430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579430));
				orderActorToFactory(1105710030, EnemyVesta, "Vesta_245");
				break;
			case 9490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579490));
				orderActorToFactory(1105710090, EnemyVesta, "Vesta_246");
				break;
			case 9500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113779500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137711500, EnemyCeres, "Ceres_247", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113879530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138711530, EnemyCeres, "Ceres_248", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579550));
				orderActorToFactory(1105710150, EnemyVesta, "Vesta_249");
				break;
			case 9560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113979560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139711560, EnemyCeres, "Ceres_250", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114079590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140711590, EnemyCeres, "Ceres_251", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579610));
				orderActorToFactory(1105710210, EnemyVesta, "Vesta_252");
				break;
			case 9620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114179620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141711620, EnemyCeres, "Ceres_253", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114279650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142711650, EnemyCeres, "Ceres_254", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579670));
				orderActorToFactory(1105710270, EnemyVesta, "Vesta_255");
				break;
			case 9730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579730));
				orderActorToFactory(1105710330, EnemyVesta, "Vesta_256");
				break;
			case 9790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579790));
				orderActorToFactory(1105710390, EnemyVesta, "Vesta_257");
				break;
			case 9800:
				orderActorToFactory(1120711800, EnemyAstraea, "Astraea_258");
				break;
			case 9850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579850));
				orderActorToFactory(1105710450, EnemyVesta, "Vesta_259");
				break;
			case 9900:
				orderActorToFactory(1109711900, EnemyAstraea, "Astraea_260");
				break;
			case 9910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579910));
				orderActorToFactory(1105710510, EnemyVesta, "Vesta_261");
				break;
			case 9970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579970));
				orderActorToFactory(1105710570, EnemyVesta, "Vesta_262");
				break;
			case 10000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				break;
			case 10030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710030));
				orderActorToFactory(1105710630, EnemyVesta, "Vesta_263");
				break;
			case 10090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710090));
				orderActorToFactory(1105710690, EnemyVesta, "Vesta_264");
				break;
			case 10100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107710100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 10150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710150));
				orderActorToFactory(1105710750, EnemyVesta, "Vesta_265");
				break;
			case 10210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710210));
				orderActorToFactory(1105710810, EnemyVesta, "Vesta_266");
				break;
			case 10270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710270));
				orderActorToFactory(1105710870, EnemyVesta, "Vesta_267");
				break;
			case 10330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710330));
				orderActorToFactory(1105710930, EnemyVesta, "Vesta_268");
				break;
			case 10390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710390));
				orderActorToFactory(1105710990, EnemyVesta, "Vesta_269");
				break;
			case 10450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710450));
				orderActorToFactory(1105711050, EnemyVesta, "Vesta_270");
				break;
			case 10500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137710500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137712500, EnemyCeres, "Ceres_271", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710510));
				orderActorToFactory(1105711110, EnemyVesta, "Vesta_272");
				break;
			case 10530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138710530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138712530, EnemyCeres, "Ceres_273", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139710560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139712560, EnemyCeres, "Ceres_274", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710570));
				orderActorToFactory(1105711170, EnemyVesta, "Vesta_275");
				break;
			case 10590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140710590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140712590, EnemyCeres, "Ceres_276", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141710620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141712620, EnemyCeres, "Ceres_277", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710630));
				orderActorToFactory(1105711230, EnemyVesta, "Vesta_278");
				break;
			case 10650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142710650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142712650, EnemyCeres, "Ceres_279", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710690));
				orderActorToFactory(1105711290, EnemyVesta, "Vesta_280");
				break;
			case 10750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710750));
				orderActorToFactory(1105711350, EnemyVesta, "Vesta_281");
				break;
			case 10810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710810));
				orderActorToFactory(1105711410, EnemyVesta, "Vesta_282");
				break;
			case 10870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710870));
				orderActorToFactory(1105711470, EnemyVesta, "Vesta_283");
				break;
			case 10930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710930));
				orderActorToFactory(1105711530, EnemyVesta, "Vesta_284");
				break;
			case 10990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710990));
				orderActorToFactory(1105711590, EnemyVesta, "Vesta_285");
				break;
			case 11050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711050));
				orderActorToFactory(1105711650, EnemyVesta, "Vesta_286");
				break;
			case 11110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711110));
				orderActorToFactory(1105711710, EnemyVesta, "Vesta_287");
				break;
			case 11170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711170));
				orderActorToFactory(1105711770, EnemyVesta, "Vesta_288");
				break;
			case 11200:
				orderActorToFactory(1116713200, EnemyAstraea, "Astraea_289");
				break;
			case 11230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711230));
				orderActorToFactory(1105711830, EnemyVesta, "Vesta_290");
				break;
			case 11290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711290));
				orderActorToFactory(1105711890, EnemyVesta, "Vesta_291");
				break;
			case 11350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711350));
				orderActorToFactory(1105711950, EnemyVesta, "Vesta_292");
				break;
			case 11410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711410));
				orderActorToFactory(1105712010, EnemyVesta, "Vesta_293");
				break;
			case 11470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711470));
				orderActorToFactory(1105712070, EnemyVesta, "Vesta_294");
				break;
			case 11500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137711500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137713500, EnemyCeres, "Ceres_295", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711530));
				orderActorToFactory(1105712130, EnemyVesta, "Vesta_296");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138711530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138713530, EnemyCeres, "Ceres_297", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139711560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139713560, EnemyCeres, "Ceres_298", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711590));
				orderActorToFactory(1105712190, EnemyVesta, "Vesta_299");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140711590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140713590, EnemyCeres, "Ceres_300", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141711620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141713620, EnemyCeres, "Ceres_301", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711650));
				orderActorToFactory(1105712250, EnemyVesta, "Vesta_302");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142711650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142713650, EnemyCeres, "Ceres_303", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11700:
				orderActorToFactory(1111713700, EnemyAstraea, "Astraea_304");
				break;
			case 11710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711710));
				orderActorToFactory(1105712310, EnemyVesta, "Vesta_305");
				break;
			case 11770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711770));
				orderActorToFactory(1105712370, EnemyVesta, "Vesta_306");
				break;
			case 11800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120711800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				break;
			case 11830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711830));
				orderActorToFactory(1105712430, EnemyVesta, "Vesta_307");
				break;
			case 11890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711890));
				orderActorToFactory(1105712490, EnemyVesta, "Vesta_308");
				break;
			case 11900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109711900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				break;
			case 11950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711950));
				orderActorToFactory(1105712550, EnemyVesta, "Vesta_309");
				break;
			case 12010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712010));
				orderActorToFactory(1105712610, EnemyVesta, "Vesta_310");
				break;
			case 12070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712070));
				orderActorToFactory(1105712670, EnemyVesta, "Vesta_311");
				break;
			case 12130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712130));
				orderActorToFactory(1105712730, EnemyVesta, "Vesta_312");
				break;
			case 12190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712190));
				orderActorToFactory(1105712790, EnemyVesta, "Vesta_313");
				break;
			case 12250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712250));
				orderActorToFactory(1105712850, EnemyVesta, "Vesta_314");
				break;
			case 12310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712310));
				orderActorToFactory(1105712910, EnemyVesta, "Vesta_315");
				break;
			case 12370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712370));
				orderActorToFactory(1105712970, EnemyVesta, "Vesta_316");
				break;
			case 12430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712430));
				orderActorToFactory(1105713030, EnemyVesta, "Vesta_317");
				break;
			case 12490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712490));
				orderActorToFactory(1105713090, EnemyVesta, "Vesta_318");
				break;
			case 12500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137712500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137714500, EnemyCeres, "Ceres_319", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138712530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138714530, EnemyCeres, "Ceres_320", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712550));
				orderActorToFactory(1105713150, EnemyVesta, "Vesta_321");
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139712560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139714560, EnemyCeres, "Ceres_322", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140712590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140714590, EnemyCeres, "Ceres_323", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712610));
				orderActorToFactory(1105713210, EnemyVesta, "Vesta_324");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141712620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141714620, EnemyCeres, "Ceres_325", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142712650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142714650, EnemyCeres, "Ceres_326", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712670));
				orderActorToFactory(1105713270, EnemyVesta, "Vesta_327");
				break;
			case 12730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712730));
				orderActorToFactory(1105713330, EnemyVesta, "Vesta_328");
				break;
			case 12790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712790));
				orderActorToFactory(1105713390, EnemyVesta, "Vesta_329");
				break;
			case 12850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712850));
				orderActorToFactory(1105713450, EnemyVesta, "Vesta_330");
				break;
			case 12910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712910));
				orderActorToFactory(1105713510, EnemyVesta, "Vesta_331");
				break;
			case 12970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712970));
				orderActorToFactory(1105713570, EnemyVesta, "Vesta_332");
				break;
			case 13000:
				orderActorToFactory(1118715000, EnemyAstraea, "Astraea_333");
				break;
			case 13030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713030));
				orderActorToFactory(1105713630, EnemyVesta, "Vesta_334");
				break;
			case 13090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713090));
				orderActorToFactory(1105713690, EnemyVesta, "Vesta_335");
				break;
			case 13100:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_336");
				break;
			case 13150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713150));
				orderActorToFactory(1105713750, EnemyVesta, "Vesta_337");
				break;
			case 13200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116713200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				break;
			case 13210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713210));
				orderActorToFactory(1105713810, EnemyVesta, "Vesta_338");
				break;
			case 13270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713270));
				orderActorToFactory(1105713870, EnemyVesta, "Vesta_339");
				break;
			case 13330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713330));
				orderActorToFactory(1105713930, EnemyVesta, "Vesta_340");
				break;
			case 13390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713390));
				orderActorToFactory(1105713990, EnemyVesta, "Vesta_341");
				break;
			case 13450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713450));
				orderActorToFactory(1105714050, EnemyVesta, "Vesta_342");
				break;
			case 13500:
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_343");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137713500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137715500, EnemyCeres, "Ceres_344", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713510));
				orderActorToFactory(1105714110, EnemyVesta, "Vesta_345");
				break;
			case 13530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138713530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138715530, EnemyCeres, "Ceres_346", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139713560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139715560, EnemyCeres, "Ceres_347", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713570));
				orderActorToFactory(1105714170, EnemyVesta, "Vesta_348");
				break;
			case 13590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140713590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140715590, EnemyCeres, "Ceres_349", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141713620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141715620, EnemyCeres, "Ceres_350", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713630));
				orderActorToFactory(1105714230, EnemyVesta, "Vesta_351");
				break;
			case 13650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142713650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142715650, EnemyCeres, "Ceres_352", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713690));
				orderActorToFactory(1105714290, EnemyVesta, "Vesta_353");
				break;
			case 13700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111713700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				break;
			case 13750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713750));
				orderActorToFactory(1105714350, EnemyVesta, "Vesta_354");
				break;
			case 13810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713810));
				orderActorToFactory(1105714410, EnemyVesta, "Vesta_355");
				break;
			case 13870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713870));
				orderActorToFactory(1105714470, EnemyVesta, "Vesta_356");
				break;
			case 13930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713930));
				orderActorToFactory(1105714530, EnemyVesta, "Vesta_357");
				break;
			case 13990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713990));
				orderActorToFactory(1105714590, EnemyVesta, "Vesta_358");
				break;
			case 14050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714050));
				orderActorToFactory(1105714650, EnemyVesta, "Vesta_359");
				break;
			case 14110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714110));
				orderActorToFactory(1105714710, EnemyVesta, "Vesta_360");
				break;
			case 14170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714170));
				orderActorToFactory(1105714770, EnemyVesta, "Vesta_361");
				break;
			case 14230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714230));
				orderActorToFactory(1105714830, EnemyVesta, "Vesta_362");
				break;
			case 14290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714290));
				orderActorToFactory(1105714890, EnemyVesta, "Vesta_363");
				break;
			case 14350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714350));
				orderActorToFactory(1105714950, EnemyVesta, "Vesta_364");
				break;
			case 14410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714410));
				orderActorToFactory(1105715010, EnemyVesta, "Vesta_365");
				break;
			case 14470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714470));
				orderActorToFactory(1105715070, EnemyVesta, "Vesta_366");
				break;
			case 14500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137714500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137716500, EnemyCeres, "Ceres_367", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714530));
				orderActorToFactory(1105715130, EnemyVesta, "Vesta_368");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138714530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138716530, EnemyCeres, "Ceres_369", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139714560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139716560, EnemyCeres, "Ceres_370", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714590));
				orderActorToFactory(1105715190, EnemyVesta, "Vesta_371");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140714590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140716590, EnemyCeres, "Ceres_372", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141714620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141716620, EnemyCeres, "Ceres_373", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714650));
				orderActorToFactory(1105715250, EnemyVesta, "Vesta_374");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142714650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142716650, EnemyCeres, "Ceres_375", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714710));
				orderActorToFactory(1105715310, EnemyVesta, "Vesta_376");
				break;
			case 14770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714770));
				orderActorToFactory(1105715370, EnemyVesta, "Vesta_377");
				break;
			case 14800:
				orderActorToFactory(1120716800, EnemyAstraea, "Astraea_378");
				break;
			case 14830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714830));
				orderActorToFactory(1105715430, EnemyVesta, "Vesta_379");
				break;
			case 14890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714890));
				orderActorToFactory(1105715490, EnemyVesta, "Vesta_380");
				break;
			case 14900:
				orderActorToFactory(1109716900, EnemyAstraea, "Astraea_381");
				break;
			case 14950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714950));
				orderActorToFactory(1105715550, EnemyVesta, "Vesta_382");
				break;
			case 15000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118715000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				break;
			case 15010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715010));
				orderActorToFactory(1105715610, EnemyVesta, "Vesta_383");
				break;
			case 15070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715070));
				orderActorToFactory(1105715670, EnemyVesta, "Vesta_384");
				break;
			case 15100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107715100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 15130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715130));
				orderActorToFactory(1105715730, EnemyVesta, "Vesta_385");
				break;
			case 15190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715190));
				orderActorToFactory(1105715790, EnemyVesta, "Vesta_386");
				break;
			case 15250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715250));
				orderActorToFactory(1105715850, EnemyVesta, "Vesta_387");
				break;
			case 15310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715310));
				orderActorToFactory(1105715910, EnemyVesta, "Vesta_388");
				break;
			case 15370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715370));
				orderActorToFactory(1105715970, EnemyVesta, "Vesta_389");
				break;
			case 15430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715430));
				orderActorToFactory(1105716030, EnemyVesta, "Vesta_390");
				break;
			case 15490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715490));
				orderActorToFactory(1105716090, EnemyVesta, "Vesta_391");
				break;
			case 15500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137715500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137717500, EnemyCeres, "Ceres_392", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138715530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138717530, EnemyCeres, "Ceres_393", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715550));
				orderActorToFactory(1105716150, EnemyVesta, "Vesta_394");
				break;
			case 15560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139715560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139717560, EnemyCeres, "Ceres_395", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140715590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140717590, EnemyCeres, "Ceres_396", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715610));
				orderActorToFactory(1105716210, EnemyVesta, "Vesta_397");
				break;
			case 15620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141715620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141717620, EnemyCeres, "Ceres_398", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142715650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142717650, EnemyCeres, "Ceres_399", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715670));
				orderActorToFactory(1105716270, EnemyVesta, "Vesta_400");
				break;
			case 15730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715730));
				orderActorToFactory(1105716330, EnemyVesta, "Vesta_401");
				break;
			case 15790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715790));
				orderActorToFactory(1105716390, EnemyVesta, "Vesta_402");
				break;
			case 15850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715850));
				orderActorToFactory(1105716450, EnemyVesta, "Vesta_403");
				break;
			case 15910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715910));
				orderActorToFactory(1105716510, EnemyVesta, "Vesta_404");
				break;
			case 15970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715970));
				orderActorToFactory(1105716570, EnemyVesta, "Vesta_405");
				break;
			case 16030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716030));
				orderActorToFactory(1105716630, EnemyVesta, "Vesta_406");
				break;
			case 16090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716090));
				orderActorToFactory(1105716690, EnemyVesta, "Vesta_407");
				break;
			case 16150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716150));
				orderActorToFactory(1105716750, EnemyVesta, "Vesta_408");
				break;
			case 16200:
				orderActorToFactory(1116718200, EnemyAstraea, "Astraea_409");
				break;
			case 16210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716210));
				orderActorToFactory(1105716810, EnemyVesta, "Vesta_410");
				break;
			case 16270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716270));
				orderActorToFactory(1105716870, EnemyVesta, "Vesta_411");
				break;
			case 16330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716330));
				orderActorToFactory(1105716930, EnemyVesta, "Vesta_412");
				break;
			case 16390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716390));
				orderActorToFactory(1105716990, EnemyVesta, "Vesta_413");
				break;
			case 16450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716450));
				orderActorToFactory(1105717050, EnemyVesta, "Vesta_414");
				break;
			case 16500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137716500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137718500, EnemyCeres, "Ceres_415", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716510));
				orderActorToFactory(1105717110, EnemyVesta, "Vesta_416");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138716530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138718530, EnemyCeres, "Ceres_417", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139716560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139718560, EnemyCeres, "Ceres_418", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716570));
				orderActorToFactory(1105717170, EnemyVesta, "Vesta_419");
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140716590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140718590, EnemyCeres, "Ceres_420", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141716620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141718620, EnemyCeres, "Ceres_421", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716630));
				orderActorToFactory(1105717230, EnemyVesta, "Vesta_422");
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142716650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142718650, EnemyCeres, "Ceres_423", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716690));
				orderActorToFactory(1105717290, EnemyVesta, "Vesta_424");
				break;
			case 16700:
				orderActorToFactory(1111718700, EnemyAstraea, "Astraea_425");
				break;
			case 16750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716750));
				orderActorToFactory(1105717350, EnemyVesta, "Vesta_426");
				break;
			case 16800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120716800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				break;
			case 16810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716810));
				orderActorToFactory(1105717410, EnemyVesta, "Vesta_427");
				break;
			case 16870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716870));
				orderActorToFactory(1105717470, EnemyVesta, "Vesta_428");
				break;
			case 16900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109716900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				break;
			case 16930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716930));
				orderActorToFactory(1105717530, EnemyVesta, "Vesta_429");
				break;
			case 16990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716990));
				orderActorToFactory(1105717590, EnemyVesta, "Vesta_430");
				break;
			case 17050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717050));
				orderActorToFactory(1105717650, EnemyVesta, "Vesta_431");
				break;
			case 17110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717110));
				orderActorToFactory(1105717710, EnemyVesta, "Vesta_432");
				break;
			case 17170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717170));
				orderActorToFactory(1105717770, EnemyVesta, "Vesta_433");
				break;
			case 17230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717230));
				orderActorToFactory(1105717830, EnemyVesta, "Vesta_434");
				break;
			case 17290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717290));
				orderActorToFactory(1105717890, EnemyVesta, "Vesta_435");
				break;
			case 17350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717350));
				orderActorToFactory(1105717950, EnemyVesta, "Vesta_436");
				break;
			case 17410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717410));
				orderActorToFactory(1105718010, EnemyVesta, "Vesta_437");
				break;
			case 17470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717470));
				orderActorToFactory(1105718070, EnemyVesta, "Vesta_438");
				break;
			case 17500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137717500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1137719500, EnemyCeres, "Ceres_439", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717530));
				orderActorToFactory(1105718130, EnemyVesta, "Vesta_440");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138717530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1138719530, EnemyCeres, "Ceres_441", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139717560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1139719560, EnemyCeres, "Ceres_442", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717590));
				orderActorToFactory(1105718190, EnemyVesta, "Vesta_443");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140717590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1140719590, EnemyCeres, "Ceres_444", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141717620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1141719620, EnemyCeres, "Ceres_445", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717650));
				orderActorToFactory(1105718250, EnemyVesta, "Vesta_446");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142717650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithDpToFactory(1142719650, EnemyCeres, "Ceres_447", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 17710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717710));
				orderActorToFactory(1105718310, EnemyVesta, "Vesta_448");
				break;
			case 17770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717770));
				orderActorToFactory(1105718370, EnemyVesta, "Vesta_449");
				break;
			case 17830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717830));
				orderActorToFactory(1105718430, EnemyVesta, "Vesta_450");
				break;
			case 17890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717890));
				orderActorToFactory(1105718490, EnemyVesta, "Vesta_451");
				break;
			case 17950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717950));
				orderActorToFactory(1105718550, EnemyVesta, "Vesta_452");
				break;
			case 18000:
				orderActorToFactory(1118720000, EnemyAstraea, "Astraea_453");
				break;
			case 18010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718010));
				orderActorToFactory(1105718610, EnemyVesta, "Vesta_454");
				break;
			case 18070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718070));
				orderActorToFactory(1105718670, EnemyVesta, "Vesta_455");
				break;
			case 18130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718130));
				orderActorToFactory(1105718730, EnemyVesta, "Vesta_456");
				break;
			case 18190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718190));
				orderActorToFactory(1105718790, EnemyVesta, "Vesta_457");
				break;
			case 18200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116718200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				break;
			case 18250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718250));
				orderActorToFactory(1105718850, EnemyVesta, "Vesta_458");
				break;
			case 18310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718310));
				orderActorToFactory(1105718910, EnemyVesta, "Vesta_459");
				break;
			case 18370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718370));
				orderActorToFactory(1105718970, EnemyVesta, "Vesta_460");
				break;
			case 18430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718430));
				orderActorToFactory(1105719030, EnemyVesta, "Vesta_461");
				break;
			case 18490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718490));
				orderActorToFactory(1105719090, EnemyVesta, "Vesta_462");
				break;
			case 18500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137718500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138718530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718550));
				orderActorToFactory(1105719150, EnemyVesta, "Vesta_463");
				break;
			case 18560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139718560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140718590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718610));
				orderActorToFactory(1105719210, EnemyVesta, "Vesta_464");
				break;
			case 18620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141718620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142718650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718670));
				orderActorToFactory(1105719270, EnemyVesta, "Vesta_465");
				break;
			case 18700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111718700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				break;
			case 18730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718730));
				orderActorToFactory(1105719330, EnemyVesta, "Vesta_466");
				break;
			case 18790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718790));
				orderActorToFactory(1105719390, EnemyVesta, "Vesta_467");
				break;
			case 18850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718850));
				orderActorToFactory(1105719450, EnemyVesta, "Vesta_468");
				break;
			case 18910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718910));
				orderActorToFactory(1105719510, EnemyVesta, "Vesta_469");
				break;
			case 18970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718970));
				orderActorToFactory(1105719570, EnemyVesta, "Vesta_470");
				break;
			case 19030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719030));
				orderActorToFactory(1105719630, EnemyVesta, "Vesta_471");
				break;
			case 19090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719090));
				orderActorToFactory(1105719690, EnemyVesta, "Vesta_472");
				break;
			case 19150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719150));
				orderActorToFactory(1105719750, EnemyVesta, "Vesta_473");
				break;
			case 19210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719210));
				orderActorToFactory(1105719810, EnemyVesta, "Vesta_474");
				break;
			case 19270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719270));
				orderActorToFactory(1105719870, EnemyVesta, "Vesta_475");
				break;
			case 19330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719330));
				orderActorToFactory(1105719930, EnemyVesta, "Vesta_476");
				break;
			case 19390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719390));
				orderActorToFactory(1105719990, EnemyVesta, "Vesta_477");
				break;
			case 19450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719450));
				orderActorToFactory(1105720050, EnemyVesta, "Vesta_478");
				break;
			case 19500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137719500); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719510));
				orderActorToFactory(1105720110, EnemyVesta, "Vesta_479");
				break;
			case 19530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138719530); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139719560); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719570));
				orderActorToFactory(1105720170, EnemyVesta, "Vesta_480");
				break;
			case 19590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140719590); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141719620); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719630));
				orderActorToFactory(1105720230, EnemyVesta, "Vesta_481");
				break;
			case 19650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142719650); getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 19690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719690));
				orderActorToFactory(1105720290, EnemyVesta, "Vesta_482");
				break;
			case 19750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719750));
				orderActorToFactory(1105720350, EnemyVesta, "Vesta_483");
				break;
			case 19810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719810));
				orderActorToFactory(1105720410, EnemyVesta, "Vesta_484");
				break;
			case 19870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719870));
				orderActorToFactory(1105720470, EnemyVesta, "Vesta_485");
				break;
			case 19930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719930));
				orderActorToFactory(1105720530, EnemyVesta, "Vesta_486");
				break;
			case 19990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719990));
				orderActorToFactory(1105720590, EnemyVesta, "Vesta_487");
				break;
			case 20000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118720000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				break;
			case 20050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720050));
				orderActorToFactory(1105720650, EnemyVesta, "Vesta_488");
				break;
			case 20110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720110));
				orderActorToFactory(1105720710, EnemyVesta, "Vesta_489");
				break;
			case 20170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720170));
				orderActorToFactory(1105720770, EnemyVesta, "Vesta_490");
				break;
			case 20230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720230));
				orderActorToFactory(1105720830, EnemyVesta, "Vesta_491");
				break;
			case 20290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720290));
				orderActorToFactory(1105720890, EnemyVesta, "Vesta_492");
				break;
			case 20350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720350));
				orderActorToFactory(1105720950, EnemyVesta, "Vesta_493");
				break;
			case 20410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720410));
				orderActorToFactory(1105721010, EnemyVesta, "Vesta_494");
				break;
			case 20470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720470));
				orderActorToFactory(1105721070, EnemyVesta, "Vesta_495");
				break;
			case 20530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720530));
				orderActorToFactory(1105721130, EnemyVesta, "Vesta_496");
				break;
			case 20590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720590));
				orderActorToFactory(1105721190, EnemyVesta, "Vesta_497");
				break;
			case 20650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720650));
				orderActorToFactory(1105721250, EnemyVesta, "Vesta_498");
				break;
			case 20710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720710));
				orderActorToFactory(1105721310, EnemyVesta, "Vesta_499");
				break;
			case 20770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720770));
				orderActorToFactory(1105721370, EnemyVesta, "Vesta_500");
				break;
			case 20830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720830));
				orderActorToFactory(1105721430, EnemyVesta, "Vesta_501");
				break;
			case 20890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720890));
				orderActorToFactory(1105721490, EnemyVesta, "Vesta_502");
				break;
			case 20950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720950));
				orderActorToFactory(1105721550, EnemyVesta, "Vesta_503");
				break;
			case 21010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721010));
				orderActorToFactory(1105721610, EnemyVesta, "Vesta_504");
				break;
			case 21070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721070));
				orderActorToFactory(1105721670, EnemyVesta, "Vesta_505");
				break;
			case 21130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721130));
				orderActorToFactory(1105721730, EnemyVesta, "Vesta_506");
				break;
			case 21190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721190));
				orderActorToFactory(1105721790, EnemyVesta, "Vesta_507");
				break;
			case 21250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721250));
				orderActorToFactory(1105721850, EnemyVesta, "Vesta_508");
				break;
			case 21310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721310));
				orderActorToFactory(1105721910, EnemyVesta, "Vesta_509");
				break;
			case 21370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721370));
				orderActorToFactory(1105721970, EnemyVesta, "Vesta_510");
				break;
			case 21430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721430));
				orderActorToFactory(1105722030, EnemyVesta, "Vesta_511");
				break;
			case 21490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721490));
				orderActorToFactory(1105722090, EnemyVesta, "Vesta_512");
				break;
			case 21550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721550));
				orderActorToFactory(1105722150, EnemyVesta, "Vesta_513");
				break;
			case 21610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721610));
				orderActorToFactory(1105722210, EnemyVesta, "Vesta_514");
				break;
			case 21670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721670));
				orderActorToFactory(1105722270, EnemyVesta, "Vesta_515");
				break;
			case 21730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721730));
				orderActorToFactory(1105722330, EnemyVesta, "Vesta_516");
				break;
			case 21790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721790));
				orderActorToFactory(1105722390, EnemyVesta, "Vesta_517");
				break;
			case 21850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721850));
				orderActorToFactory(1105722450, EnemyVesta, "Vesta_518");
				break;
			case 21910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721910));
				orderActorToFactory(1105722510, EnemyVesta, "Vesta_519");
				break;
			case 21970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721970));
				orderActorToFactory(1105722570, EnemyVesta, "Vesta_520");
				break;
			case 22030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722030));
				orderActorToFactory(1105722630, EnemyVesta, "Vesta_521");
				break;
			case 22090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722090));
				orderActorToFactory(1105722690, EnemyVesta, "Vesta_522");
				break;
			case 22150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722150));
				orderActorToFactory(1105722750, EnemyVesta, "Vesta_523");
				break;
			case 22210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722210));
				orderActorToFactory(1105722810, EnemyVesta, "Vesta_524");
				break;
			case 22270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722270));
				orderActorToFactory(1105722870, EnemyVesta, "Vesta_525");
				break;
			case 22330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722330));
				orderActorToFactory(1105722930, EnemyVesta, "Vesta_526");
				break;
			case 22390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722390));
				orderActorToFactory(1105722990, EnemyVesta, "Vesta_527");
				break;
			case 22450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722450));
				orderActorToFactory(1105723050, EnemyVesta, "Vesta_528");
				break;
			case 22510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722510));
				orderActorToFactory(1105723110, EnemyVesta, "Vesta_529");
				break;
			case 22570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722570));
				orderActorToFactory(1105723170, EnemyVesta, "Vesta_530");
				break;
			case 22630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722630));
				orderActorToFactory(1105723230, EnemyVesta, "Vesta_531");
				break;
			case 22690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722690));
				orderActorToFactory(1105723290, EnemyVesta, "Vesta_532");
				break;
			case 22750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722750));
				orderActorToFactory(1105723350, EnemyVesta, "Vesta_533");
				break;
			case 22810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722810));
				orderActorToFactory(1105723410, EnemyVesta, "Vesta_534");
				break;
			case 22870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722870));
				orderActorToFactory(1105723470, EnemyVesta, "Vesta_535");
				break;
			case 22930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722930));
				orderActorToFactory(1105723530, EnemyVesta, "Vesta_536");
				break;
			case 22990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722990));
				orderActorToFactory(1105723590, EnemyVesta, "Vesta_537");
				break;
			case 23050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723050));
				orderActorToFactory(1105723650, EnemyVesta, "Vesta_538");
				break;
			case 23110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723110));
				orderActorToFactory(1105723710, EnemyVesta, "Vesta_539");
				break;
			case 23170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723170));
				orderActorToFactory(1105723770, EnemyVesta, "Vesta_540");
				break;
			case 23230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723230));
				orderActorToFactory(1105723830, EnemyVesta, "Vesta_541");
				break;
			case 23290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723290));
				orderActorToFactory(1105723890, EnemyVesta, "Vesta_542");
				break;
			case 23350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723350));
				orderActorToFactory(1105723950, EnemyVesta, "Vesta_543");
				break;
			case 23410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723410));
				orderActorToFactory(1105724010, EnemyVesta, "Vesta_544");
				break;
			case 23470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723470));
				orderActorToFactory(1105724070, EnemyVesta, "Vesta_545");
				break;
			case 23530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723530));
				orderActorToFactory(1105724130, EnemyVesta, "Vesta_546");
				break;
			case 23590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723590));
				orderActorToFactory(1105724190, EnemyVesta, "Vesta_547");
				break;
			case 23650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723650));
				orderActorToFactory(1105724250, EnemyVesta, "Vesta_548");
				break;
			case 23710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723710));
				orderActorToFactory(1105724310, EnemyVesta, "Vesta_549");
				break;
			case 23770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723770));
				orderActorToFactory(1105724370, EnemyVesta, "Vesta_550");
				break;
			case 23830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723830));
				orderActorToFactory(1105724430, EnemyVesta, "Vesta_551");
				break;
			case 23890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723890));
				orderActorToFactory(1105724490, EnemyVesta, "Vesta_552");
				break;
			case 23950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723950));
				orderActorToFactory(1105724550, EnemyVesta, "Vesta_553");
				break;
			case 24010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724010));
				orderActorToFactory(1105724610, EnemyVesta, "Vesta_554");
				break;
			case 24070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724070));
				orderActorToFactory(1105724670, EnemyVesta, "Vesta_555");
				break;
			case 24130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724130));
				orderActorToFactory(1105724730, EnemyVesta, "Vesta_556");
				break;
			case 24190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724190));
				orderActorToFactory(1105724790, EnemyVesta, "Vesta_557");
				break;
			case 24250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724250));
				orderActorToFactory(1105724850, EnemyVesta, "Vesta_558");
				break;
			case 24310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724310));
				orderActorToFactory(1105724910, EnemyVesta, "Vesta_559");
				break;
			case 24370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724370));
				orderActorToFactory(1105724970, EnemyVesta, "Vesta_560");
				break;
			case 24430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724430));
				orderActorToFactory(1105725030, EnemyVesta, "Vesta_561");
				break;
			case 24490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724490));
				orderActorToFactory(1105725090, EnemyVesta, "Vesta_562");
				break;
			case 24550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724550));
				orderActorToFactory(1105725150, EnemyVesta, "Vesta_563");
				break;
			case 24610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724610));
				orderActorToFactory(1105725210, EnemyVesta, "Vesta_564");
				break;
			case 24670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724670));
				orderActorToFactory(1105725270, EnemyVesta, "Vesta_565");
				break;
			case 24730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724730));
				orderActorToFactory(1105725330, EnemyVesta, "Vesta_566");
				break;
			case 24790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724790));
				orderActorToFactory(1105725390, EnemyVesta, "Vesta_567");
				break;
			case 24850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724850));
				orderActorToFactory(1105725450, EnemyVesta, "Vesta_568");
				break;
			case 24910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724910));
				orderActorToFactory(1105725510, EnemyVesta, "Vesta_569");
				break;
			case 24970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724970));
				orderActorToFactory(1105725570, EnemyVesta, "Vesta_570");
				break;
			case 25030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725030));
				orderActorToFactory(1105725630, EnemyVesta, "Vesta_571");
				break;
			case 25090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725090));
				orderActorToFactory(1105725690, EnemyVesta, "Vesta_572");
				break;
			case 25150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725150));
				orderActorToFactory(1105725750, EnemyVesta, "Vesta_573");
				break;
			case 25210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725210));
				orderActorToFactory(1105725810, EnemyVesta, "Vesta_574");
				break;
			case 25270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725270));
				orderActorToFactory(1105725870, EnemyVesta, "Vesta_575");
				break;
			case 25330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725330));
				orderActorToFactory(1105725930, EnemyVesta, "Vesta_576");
				break;
			case 25390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725390));
				orderActorToFactory(1105725990, EnemyVesta, "Vesta_577");
				break;
			case 25450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725450));
				orderActorToFactory(1105726050, EnemyVesta, "Vesta_578");
				break;
			case 25510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725510));
				orderActorToFactory(1105726110, EnemyVesta, "Vesta_579");
				break;
			case 25570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725570));
				orderActorToFactory(1105726170, EnemyVesta, "Vesta_580");
				break;
			case 25630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725630));
				orderActorToFactory(1105726230, EnemyVesta, "Vesta_581");
				break;
			case 25690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725690));
				orderActorToFactory(1105726290, EnemyVesta, "Vesta_582");
				break;
			case 25750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725750));
				orderActorToFactory(1105726350, EnemyVesta, "Vesta_583");
				break;
			case 25810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725810));
				orderActorToFactory(1105726410, EnemyVesta, "Vesta_584");
				break;
			case 25870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725870));
				orderActorToFactory(1105726470, EnemyVesta, "Vesta_585");
				break;
			case 25930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725930));
				orderActorToFactory(1105726530, EnemyVesta, "Vesta_586");
				break;
			case 25990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725990));
				orderActorToFactory(1105726590, EnemyVesta, "Vesta_587");
				break;
			case 26050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726050));
				orderActorToFactory(1105726650, EnemyVesta, "Vesta_588");
				break;
			case 26110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726110));
				orderActorToFactory(1105726710, EnemyVesta, "Vesta_589");
				break;
			case 26170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726170));
				orderActorToFactory(1105726770, EnemyVesta, "Vesta_590");
				break;
			case 26230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726230));
				orderActorToFactory(1105726830, EnemyVesta, "Vesta_591");
				break;
			case 26290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726290));
				orderActorToFactory(1105726890, EnemyVesta, "Vesta_592");
				break;
			case 26350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726350));
				orderActorToFactory(1105726950, EnemyVesta, "Vesta_593");
				break;
			case 26410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726410));
				orderActorToFactory(1105727010, EnemyVesta, "Vesta_594");
				break;
			case 26470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726470));
				orderActorToFactory(1105727070, EnemyVesta, "Vesta_595");
				break;
			case 26530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726530));
				orderActorToFactory(1105727130, EnemyVesta, "Vesta_596");
				break;
			case 26590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726590));
				orderActorToFactory(1105727190, EnemyVesta, "Vesta_597");
				break;
			case 26650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726650));
				orderActorToFactory(1105727250, EnemyVesta, "Vesta_598");
				break;
			case 26710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726710));
				orderActorToFactory(1105727310, EnemyVesta, "Vesta_599");
				break;
			case 26770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726770));
				orderActorToFactory(1105727370, EnemyVesta, "Vesta_600");
				break;
			case 26830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726830));
				orderActorToFactory(1105727430, EnemyVesta, "Vesta_601");
				break;
			case 26890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726890));
				orderActorToFactory(1105727490, EnemyVesta, "Vesta_602");
				break;
			case 26950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726950));
				orderActorToFactory(1105727550, EnemyVesta, "Vesta_603");
				break;
			case 27010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727010));
				orderActorToFactory(1105727610, EnemyVesta, "Vesta_604");
				break;
			case 27070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727070));
				orderActorToFactory(1105727670, EnemyVesta, "Vesta_605");
				break;
			case 27130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727130));
				orderActorToFactory(1105727730, EnemyVesta, "Vesta_606");
				break;
			case 27190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727190));
				orderActorToFactory(1105727790, EnemyVesta, "Vesta_607");
				break;
			case 27250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727250));
				orderActorToFactory(1105727850, EnemyVesta, "Vesta_608");
				break;
			case 27310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727310));
				orderActorToFactory(1105727910, EnemyVesta, "Vesta_609");
				break;
			case 27370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727370));
				orderActorToFactory(1105727970, EnemyVesta, "Vesta_610");
				break;
			case 27430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727430));
				orderActorToFactory(1105728030, EnemyVesta, "Vesta_611");
				break;
			case 27490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727490));
				orderActorToFactory(1105728090, EnemyVesta, "Vesta_612");
				break;
			case 27550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727550));
				orderActorToFactory(1105728150, EnemyVesta, "Vesta_613");
				break;
			case 27610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727610));
				orderActorToFactory(1105728210, EnemyVesta, "Vesta_614");
				break;
			case 27670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727670));
				orderActorToFactory(1105728270, EnemyVesta, "Vesta_615");
				break;
			case 27730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727730));
				orderActorToFactory(1105728330, EnemyVesta, "Vesta_616");
				break;
			case 27790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727790));
				orderActorToFactory(1105728390, EnemyVesta, "Vesta_617");
				break;
			case 27850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727850));
				orderActorToFactory(1105728450, EnemyVesta, "Vesta_618");
				break;
			case 27910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727910));
				orderActorToFactory(1105728510, EnemyVesta, "Vesta_619");
				break;
			case 27970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727970));
				orderActorToFactory(1105728570, EnemyVesta, "Vesta_620");
				break;
			case 28030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728030));
				orderActorToFactory(1105728630, EnemyVesta, "Vesta_621");
				break;
			case 28090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728090));
				orderActorToFactory(1105728690, EnemyVesta, "Vesta_622");
				break;
			case 28150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728150));
				orderActorToFactory(1105728750, EnemyVesta, "Vesta_623");
				break;
			case 28210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728210));
				orderActorToFactory(1105728810, EnemyVesta, "Vesta_624");
				break;
			case 28270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728270));
				orderActorToFactory(1105728870, EnemyVesta, "Vesta_625");
				break;
			case 28330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728330));
				orderActorToFactory(1105728930, EnemyVesta, "Vesta_626");
				break;
			case 28390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728390));
				orderActorToFactory(1105728990, EnemyVesta, "Vesta_627");
				break;
			case 28450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728450));
				orderActorToFactory(1105729050, EnemyVesta, "Vesta_628");
				break;
			case 28510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728510));
				orderActorToFactory(1105729110, EnemyVesta, "Vesta_629");
				break;
			case 28570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728570));
				orderActorToFactory(1105729170, EnemyVesta, "Vesta_630");
				break;
			case 28630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728630));
				orderActorToFactory(1105729230, EnemyVesta, "Vesta_631");
				break;
			case 28690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728690));
				orderActorToFactory(1105729290, EnemyVesta, "Vesta_632");
				break;
			case 28750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728750));
				orderActorToFactory(1105729350, EnemyVesta, "Vesta_633");
				break;
			case 28810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728810));
				orderActorToFactory(1105729410, EnemyVesta, "Vesta_634");
				break;
			case 28870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728870));
				orderActorToFactory(1105729470, EnemyVesta, "Vesta_635");
				break;
			case 28930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728930));
				orderActorToFactory(1105729530, EnemyVesta, "Vesta_636");
				break;
			case 28990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728990));
				orderActorToFactory(1105729590, EnemyVesta, "Vesta_637");
				break;
			case 29050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729050));
				orderActorToFactory(1105729650, EnemyVesta, "Vesta_638");
				break;
			case 29110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729110));
				orderActorToFactory(1105729710, EnemyVesta, "Vesta_639");
				break;
			case 29170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729170));
				orderActorToFactory(1105729770, EnemyVesta, "Vesta_640");
				break;
			case 29230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729230));
				orderActorToFactory(1105729830, EnemyVesta, "Vesta_641");
				break;
			case 29290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729290));
				orderActorToFactory(1105729890, EnemyVesta, "Vesta_642");
				break;
			case 29350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729350));
				orderActorToFactory(1105729950, EnemyVesta, "Vesta_643");
				break;
			case 29410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729410));
				orderActorToFactory(1105730010, EnemyVesta, "Vesta_644");
				break;
			case 29470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729470));
				orderActorToFactory(1105730070, EnemyVesta, "Vesta_645");
				break;
			case 29530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729530));
				orderActorToFactory(1105730130, EnemyVesta, "Vesta_646");
				break;
			case 29590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729590));
				orderActorToFactory(1105730190, EnemyVesta, "Vesta_647");
				break;
			case 29650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729650));
				orderActorToFactory(1105730250, EnemyVesta, "Vesta_648");
				break;
			case 29710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729710));
				orderActorToFactory(1105730310, EnemyVesta, "Vesta_649");
				break;
			case 29770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729770));
				orderActorToFactory(1105730370, EnemyVesta, "Vesta_650");
				break;
			case 29830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729830));
				orderActorToFactory(1105730430, EnemyVesta, "Vesta_651");
				break;
			case 29890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729890));
				orderActorToFactory(1105730490, EnemyVesta, "Vesta_652");
				break;
			case 29950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729950));
				orderActorToFactory(1105730550, EnemyVesta, "Vesta_653");
				break;
			case 30010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730010));
				orderActorToFactory(1105730610, EnemyVesta, "Vesta_654");
				break;
			case 30070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730070));
				orderActorToFactory(1105730670, EnemyVesta, "Vesta_655");
				break;
			case 30130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730130));
				orderActorToFactory(1105730730, EnemyVesta, "Vesta_656");
				break;
			case 30190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730190));
				orderActorToFactory(1105730790, EnemyVesta, "Vesta_657");
				break;
			case 30250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730250));
				orderActorToFactory(1105730850, EnemyVesta, "Vesta_658");
				break;
			case 30310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730310));
				orderActorToFactory(1105730910, EnemyVesta, "Vesta_659");
				break;
			case 30370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730370));
				orderActorToFactory(1105730970, EnemyVesta, "Vesta_660");
				break;
			case 30430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730430));
				orderActorToFactory(1105731030, EnemyVesta, "Vesta_661");
				break;
			case 30490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730490));
				orderActorToFactory(1105731090, EnemyVesta, "Vesta_662");
				break;
			case 30550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730550));
				orderActorToFactory(1105731150, EnemyVesta, "Vesta_663");
				break;
			case 30610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730610));
				orderActorToFactory(1105731210, EnemyVesta, "Vesta_664");
				break;
			case 30670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730670));
				orderActorToFactory(1105731270, EnemyVesta, "Vesta_665");
				break;
			case 30730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730730));
				orderActorToFactory(1105731330, EnemyVesta, "Vesta_666");
				break;
			case 30790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730790));
				orderActorToFactory(1105731390, EnemyVesta, "Vesta_667");
				break;
			case 30850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730850));
				orderActorToFactory(1105731450, EnemyVesta, "Vesta_668");
				break;
			case 30910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730910));
				orderActorToFactory(1105731510, EnemyVesta, "Vesta_669");
				break;
			case 30970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730970));
				orderActorToFactory(1105731570, EnemyVesta, "Vesta_670");
				break;
			case 31030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731030));
				orderActorToFactory(1105731630, EnemyVesta, "Vesta_671");
				break;
			case 31090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731090));
				orderActorToFactory(1105731690, EnemyVesta, "Vesta_672");
				break;
			case 31150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731150));
				orderActorToFactory(1105731750, EnemyVesta, "Vesta_673");
				break;
			case 31210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731210));
				orderActorToFactory(1105731810, EnemyVesta, "Vesta_674");
				break;
			case 31270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731270));
				orderActorToFactory(1105731870, EnemyVesta, "Vesta_675");
				break;
			case 31330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731330));
				orderActorToFactory(1105731930, EnemyVesta, "Vesta_676");
				break;
			case 31390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731390));
				orderActorToFactory(1105731990, EnemyVesta, "Vesta_677");
				break;
			case 31450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731450));
				break;
			case 31510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731510));
				break;
			case 31570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731570));
				break;
			case 31630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731630));
				break;
			case 31690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731690));
				break;
			case 31750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731750));
				break;
			case 31810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731810));
				break;
			case 31870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731870));
				break;
			case 31930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731930));
				break;
			case 31990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731990));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_frame_of_life== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_frame_of_life== 1) {
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
