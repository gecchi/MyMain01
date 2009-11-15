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
	DWORD dw[] = {1,10,20,50,70,100,130,190,250,310,370,430,490,500,530,550,560,590,610,620,650,670,730,790,850,910,970,1030,1090,1150,1210,1270,1300,1330,1390,1450,1510,1570,1630,1690,1750,1810,1870,1900,1930,1960,1990,2020,2050,2110,2170,2230,2290,2350,2410,2470,2500,2530,2560,2590,2620,2650,2710,2770,2830,2890,2950,3010,3070,3100,3130,3190,3250,3310,3370,3430,3490,3550,3610,3670,3700,3730,3790,3850,3900,3910,3930,3960,3970,3990,4020,4030,4050,4090,4150,4210,4270,4330,4390,4450,4500,4510,4530,4560,4570,4590,4620,4630,4650,4690,4750,4810,4870,4900,4930,4990,5050,5100,5110,5170,5230,5290,5350,5410,5470,5500,5530,5590,5650,5710,5770,5830,5890,5900,5930,5950,5960,5990,6010,6020,6050,6070,6130,6190,6250,6300,6310,6370,6430,6490,6500,6530,6550,6560,6590,6610,6620,6650,6670,6730,6790,6850,6900,6910,6970,7030,7090,7150,7210,7270,7330,7390,7450,7510,7570,7600,7630,7690,7750,7810,7870,7900,7930,7960,7990,8020,8050,8100,8110,8170,8200,8230,8290,8350,8410,8470,8500,8530,8560,8590,8620,8650,8700,8710,8770,8830,8890,8950,9010,9070,9130,9190,9250,9310,9370,9400,9430,9490,9500,9550,9610,9670,9730,9790,9850,9900,9910,9930,9960,9970,9990,10000,10020,10030,10050,10090,10100,10150,10210,10270,10330,10390,10450,10500,10510,10530,10560,10570,10590,10620,10630,10650,10690,10750,10810,10870,10930,10990,11050,11110,11170,11200,11230,11290,11300,11350,11410,11470,11530,11590,11650,11710,11770,11800,11830,11890,11900,11930,11950,11960,11990,12010,12020,12050,12070,12130,12190,12250,12310,12370,12430,12490,12500,12530,12550,12560,12590,12600,12610,12620,12650,12670,12730,12790,12850,12910,12970,13030,13090,13100,13150,13200,13210,13270,13330,13390,13450,13510,13570,13630,13690,13700,13750,13810,13870,13900,13930,13960,13990,14020,14050,14110,14170,14230,14290,14350,14400,14410,14470,14500,14530,14560,14590,14620,14650,14710,14770,14830,14890,14900,14950,15000,15010,15070,15100,15130,15190,15250,15310,15370,15430,15490,15500,15550,15610,15670,15730,15790,15850,15900,15910,15930,15960,15970,15990,16020,16030,16050,16090,16150,16200,16210,16270,16300,16330,16390,16450,16500,16510,16530,16560,16570,16590,16620,16630,16650,16690,16750,16800,16810,16870,16900,16930,16990,17050,17110,17170,17230,17290,17350,17410,17470,17530,17590,17600,17650,17710,17770,17830,17890,17900,17930,17950,17960,17990,18010,18020,18050,18070,18100,18130,18190,18200,18250,18310,18370,18430,18490,18500,18530,18550,18560,18590,18610,18620,18650,18670,18700,18730,18790,18850,18910,18970,19030,19090,19150,19210,19270,19330,19390,19400,19450,19510,19570,19630,19690,19750,19810,19870,19930,19990,20000,20050,20110,20170,20230,20290,20350,20410,20470,20530,20590,20650,20710,20770,20830,20890,20950,21010,21070,21130,21190,21250,21310,21370,21430,21490,21550,21610,21670,21730,21790,21850,21910,21970,22030,22090,22150,22210,22270,22330,22390,22450,22510,22570,22630,22690,22750,22810,22870,22930,22990,23050,23110,23170,23230,23290,23350,23410,23470,23530,23590,23650,23710,23770,23830,23890,23950,24010,24070,24130,24190,24250,24310,24370,24430,24490,24550,24610,24670,24730,24790,24850,24910,24970,25030,25090,25150,25210,25270,25330,25390,25450,25510,25570,25630,25690,25750,25810,25870,25930,25990,26050,26110,26170,26230,26290,26350,26410,26470,26530,26590,26650,26710,26770,26830,26890,26950,27010,27070,27130,27190,27250,27310,27370,27430,27490,27550,27610,27670,27730,27790,27850,27910,27970,28030,28090,28150,28210,28270,28330,28390,28450,28510,28570,28630,28690,28750,28810,28870,28930,28990,29050,29110,29170,29230,29290,29350,29410,29470,29530,29590,29650,29710,29770,29830,29890,29950,30010,30070,30130,30190,30250,30310,30370,30430,30490,30550,30610,30670,30730,30790,30850,30910,30970,31030,31090,31150,31210,31270,31330,31390,31450,31510,31570,31630,31690,31750,31810,31870,31930,31990};
	_paFrame_NextEvent = new DWORD[672];
	for (int i = 0; i < 672; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyVesta, "Vesta_1");
	orderActorToFactory(1105670, EnemyVesta, "Vesta_2");
	orderActorToFactory(11056130, EnemyVesta, "Vesta_3");
	orderActorToFactory(11056190, EnemyVesta, "Vesta_4");
	orderActorToFactory(11056250, EnemyVesta, "Vesta_5");
	orderActorToFactory(11056310, EnemyVesta, "Vesta_6");
	orderActorToFactory(11056370, EnemyVesta, "Vesta_7");
	orderActorToFactory(11056430, EnemyVesta, "Vesta_8");
	orderActorToFactory(11056490, EnemyVesta, "Vesta_9");
	orderActorToFactory(11056550, EnemyVesta, "Vesta_10");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_11");
	orderActorToFactory(11377500, EnemyCeres, "Ceres_12");
	orderActorToFactory(11387530, EnemyCeres, "Ceres_13");
	orderActorToFactory(11397560, EnemyCeres, "Ceres_14");
	orderActorToFactory(11407590, EnemyCeres, "Ceres_15");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_lifeframe == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_lifeframe) {
			case 1:
				break;
			case 10:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610));
				orderActorToFactory(11056610, EnemyVesta, "Vesta_16");
				break;
			case 20:
				orderActorToFactory(11417620, EnemyCeres, "Ceres_17");
				break;
			case 50:
				orderActorToFactory(11427650, EnemyCeres, "Ceres_18");
				break;
			case 70:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105670));
				orderActorToFactory(11056670, EnemyVesta, "Vesta_19");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056130));
				orderActorToFactory(11056730, EnemyVesta, "Vesta_20");
				break;
			case 190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056190));
				orderActorToFactory(11056790, EnemyVesta, "Vesta_21");
				break;
			case 250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056250));
				orderActorToFactory(11056850, EnemyVesta, "Vesta_22");
				break;
			case 310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056310));
				orderActorToFactory(11056910, EnemyVesta, "Vesta_23");
				break;
			case 370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056370));
				orderActorToFactory(11056970, EnemyVesta, "Vesta_24");
				break;
			case 430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056430));
				orderActorToFactory(110561030, EnemyVesta, "Vesta_25");
				break;
			case 490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056490));
				orderActorToFactory(110561090, EnemyVesta, "Vesta_26");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056550));
				orderActorToFactory(110561150, EnemyVesta, "Vesta_27");
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11407590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056610));
				orderActorToFactory(110561210, EnemyVesta, "Vesta_28");
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11417620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11427650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056670));
				orderActorToFactory(110561270, EnemyVesta, "Vesta_29");
				break;
			case 730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056730));
				orderActorToFactory(110561330, EnemyVesta, "Vesta_30");
				break;
			case 790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056790));
				orderActorToFactory(110561390, EnemyVesta, "Vesta_31");
				break;
			case 850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056850));
				orderActorToFactory(110561450, EnemyVesta, "Vesta_32");
				break;
			case 910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056910));
				orderActorToFactory(110561510, EnemyVesta, "Vesta_33");
				break;
			case 970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(11056970));
				orderActorToFactory(110561570, EnemyVesta, "Vesta_34");
				break;
			case 1030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561030));
				orderActorToFactory(110561630, EnemyVesta, "Vesta_35");
				break;
			case 1090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561090));
				orderActorToFactory(110561690, EnemyVesta, "Vesta_36");
				break;
			case 1150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561150));
				orderActorToFactory(110561750, EnemyVesta, "Vesta_37");
				break;
			case 1210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561210));
				orderActorToFactory(110561810, EnemyVesta, "Vesta_38");
				break;
			case 1270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561270));
				orderActorToFactory(110561870, EnemyVesta, "Vesta_39");
				break;
			case 1300:
				orderActorToFactory(110971900, EnemyAstraea, "Astraea_40");
				break;
			case 1330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561330));
				orderActorToFactory(110561930, EnemyVesta, "Vesta_41");
				break;
			case 1390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561390));
				orderActorToFactory(110561990, EnemyVesta, "Vesta_42");
				break;
			case 1450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561450));
				orderActorToFactory(110562050, EnemyVesta, "Vesta_43");
				break;
			case 1510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561510));
				orderActorToFactory(110562110, EnemyVesta, "Vesta_44");
				break;
			case 1570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561570));
				orderActorToFactory(110562170, EnemyVesta, "Vesta_45");
				break;
			case 1630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561630));
				orderActorToFactory(110562230, EnemyVesta, "Vesta_46");
				break;
			case 1690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561690));
				orderActorToFactory(110562290, EnemyVesta, "Vesta_47");
				break;
			case 1750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561750));
				orderActorToFactory(110562350, EnemyVesta, "Vesta_48");
				break;
			case 1810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561810));
				orderActorToFactory(110562410, EnemyVesta, "Vesta_49");
				break;
			case 1870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561870));
				orderActorToFactory(110562470, EnemyVesta, "Vesta_50");
				break;
			case 1900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110971900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(113772500, EnemyCeres, "Ceres_51");
				break;
			case 1930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561930));
				orderActorToFactory(110562530, EnemyVesta, "Vesta_52");
				orderActorToFactory(113872530, EnemyCeres, "Ceres_53");
				break;
			case 1960:
				orderActorToFactory(113972560, EnemyCeres, "Ceres_54");
				break;
			case 1990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110561990));
				orderActorToFactory(110562590, EnemyVesta, "Vesta_55");
				orderActorToFactory(114072590, EnemyCeres, "Ceres_56");
				break;
			case 2020:
				orderActorToFactory(114172620, EnemyCeres, "Ceres_57");
				break;
			case 2050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562050));
				orderActorToFactory(110562650, EnemyVesta, "Vesta_58");
				orderActorToFactory(114272650, EnemyCeres, "Ceres_59");
				break;
			case 2110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562110));
				orderActorToFactory(110562710, EnemyVesta, "Vesta_60");
				break;
			case 2170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562170));
				orderActorToFactory(110562770, EnemyVesta, "Vesta_61");
				break;
			case 2230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562230));
				orderActorToFactory(110562830, EnemyVesta, "Vesta_62");
				break;
			case 2290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562290));
				orderActorToFactory(110562890, EnemyVesta, "Vesta_63");
				break;
			case 2350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562350));
				orderActorToFactory(110562950, EnemyVesta, "Vesta_64");
				break;
			case 2410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562410));
				orderActorToFactory(110563010, EnemyVesta, "Vesta_65");
				break;
			case 2470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562470));
				orderActorToFactory(110563070, EnemyVesta, "Vesta_66");
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562530));
				orderActorToFactory(110563130, EnemyVesta, "Vesta_67");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113872530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113972560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562590));
				orderActorToFactory(110563190, EnemyVesta, "Vesta_68");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114072590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114172620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562650));
				orderActorToFactory(110563250, EnemyVesta, "Vesta_69");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114272650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562710));
				orderActorToFactory(110563310, EnemyVesta, "Vesta_70");
				break;
			case 2770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562770));
				orderActorToFactory(110563370, EnemyVesta, "Vesta_71");
				break;
			case 2830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562830));
				orderActorToFactory(110563430, EnemyVesta, "Vesta_72");
				break;
			case 2890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562890));
				orderActorToFactory(110563490, EnemyVesta, "Vesta_73");
				break;
			case 2950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110562950));
				orderActorToFactory(110563550, EnemyVesta, "Vesta_74");
				break;
			case 3010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563010));
				orderActorToFactory(110563610, EnemyVesta, "Vesta_75");
				break;
			case 3070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563070));
				orderActorToFactory(110563670, EnemyVesta, "Vesta_76");
				break;
			case 3100:
				orderActorToFactory(111173700, EnemyAstraea, "Astraea_77");
				break;
			case 3130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563130));
				orderActorToFactory(110563730, EnemyVesta, "Vesta_78");
				break;
			case 3190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563190));
				orderActorToFactory(110563790, EnemyVesta, "Vesta_79");
				break;
			case 3250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563250));
				orderActorToFactory(110563850, EnemyVesta, "Vesta_80");
				break;
			case 3310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563310));
				orderActorToFactory(110563910, EnemyVesta, "Vesta_81");
				break;
			case 3370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563370));
				orderActorToFactory(110563970, EnemyVesta, "Vesta_82");
				break;
			case 3430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563430));
				orderActorToFactory(110564030, EnemyVesta, "Vesta_83");
				break;
			case 3490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563490));
				orderActorToFactory(110564090, EnemyVesta, "Vesta_84");
				break;
			case 3550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563550));
				orderActorToFactory(110564150, EnemyVesta, "Vesta_85");
				break;
			case 3610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563610));
				orderActorToFactory(110564210, EnemyVesta, "Vesta_86");
				break;
			case 3670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563670));
				orderActorToFactory(110564270, EnemyVesta, "Vesta_87");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563730));
				orderActorToFactory(110564330, EnemyVesta, "Vesta_88");
				break;
			case 3790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563790));
				orderActorToFactory(110564390, EnemyVesta, "Vesta_89");
				break;
			case 3850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563850));
				orderActorToFactory(110564450, EnemyVesta, "Vesta_90");
				break;
			case 3900:
				orderActorToFactory(113774500, EnemyCeres, "Ceres_91");
				break;
			case 3910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563910));
				orderActorToFactory(110564510, EnemyVesta, "Vesta_92");
				break;
			case 3930:
				orderActorToFactory(113874530, EnemyCeres, "Ceres_93");
				break;
			case 3960:
				orderActorToFactory(113974560, EnemyCeres, "Ceres_94");
				break;
			case 3970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110563970));
				orderActorToFactory(110564570, EnemyVesta, "Vesta_95");
				break;
			case 3990:
				orderActorToFactory(114074590, EnemyCeres, "Ceres_96");
				break;
			case 4020:
				orderActorToFactory(114174620, EnemyCeres, "Ceres_97");
				break;
			case 4030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564030));
				orderActorToFactory(110564630, EnemyVesta, "Vesta_98");
				break;
			case 4050:
				orderActorToFactory(114274650, EnemyCeres, "Ceres_99");
				break;
			case 4090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564090));
				orderActorToFactory(110564690, EnemyVesta, "Vesta_100");
				break;
			case 4150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564150));
				orderActorToFactory(110564750, EnemyVesta, "Vesta_101");
				break;
			case 4210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564210));
				orderActorToFactory(110564810, EnemyVesta, "Vesta_102");
				break;
			case 4270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564270));
				orderActorToFactory(110564870, EnemyVesta, "Vesta_103");
				break;
			case 4330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564330));
				orderActorToFactory(110564930, EnemyVesta, "Vesta_104");
				break;
			case 4390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564390));
				orderActorToFactory(110564990, EnemyVesta, "Vesta_105");
				break;
			case 4450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564450));
				orderActorToFactory(110565050, EnemyVesta, "Vesta_106");
				break;
			case 4500:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_107");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564510));
				orderActorToFactory(110565110, EnemyVesta, "Vesta_108");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113874530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113974560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564570));
				orderActorToFactory(110565170, EnemyVesta, "Vesta_109");
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114074590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114174620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564630));
				orderActorToFactory(110565230, EnemyVesta, "Vesta_110");
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114274650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 4690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564690));
				orderActorToFactory(110565290, EnemyVesta, "Vesta_111");
				break;
			case 4750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564750));
				orderActorToFactory(110565350, EnemyVesta, "Vesta_112");
				break;
			case 4810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564810));
				orderActorToFactory(110565410, EnemyVesta, "Vesta_113");
				break;
			case 4870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564870));
				orderActorToFactory(110565470, EnemyVesta, "Vesta_114");
				break;
			case 4900:
				orderActorToFactory(111375500, EnemyAstraea, "Astraea_115");
				break;
			case 4930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564930));
				orderActorToFactory(110565530, EnemyVesta, "Vesta_116");
				break;
			case 4990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110564990));
				orderActorToFactory(110565590, EnemyVesta, "Vesta_117");
				break;
			case 5050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565050));
				orderActorToFactory(110565650, EnemyVesta, "Vesta_118");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565110));
				orderActorToFactory(110565710, EnemyVesta, "Vesta_119");
				break;
			case 5170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565170));
				orderActorToFactory(110565770, EnemyVesta, "Vesta_120");
				break;
			case 5230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565230));
				orderActorToFactory(110565830, EnemyVesta, "Vesta_121");
				break;
			case 5290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565290));
				orderActorToFactory(110565890, EnemyVesta, "Vesta_122");
				break;
			case 5350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565350));
				orderActorToFactory(110565950, EnemyVesta, "Vesta_123");
				break;
			case 5410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565410));
				orderActorToFactory(110566010, EnemyVesta, "Vesta_124");
				break;
			case 5470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565470));
				orderActorToFactory(110566070, EnemyVesta, "Vesta_125");
				break;
			case 5500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111375500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				break;
			case 5530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565530));
				orderActorToFactory(110566130, EnemyVesta, "Vesta_126");
				break;
			case 5590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565590));
				orderActorToFactory(110566190, EnemyVesta, "Vesta_127");
				break;
			case 5650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565650));
				orderActorToFactory(110566250, EnemyVesta, "Vesta_128");
				break;
			case 5710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565710));
				orderActorToFactory(110566310, EnemyVesta, "Vesta_129");
				break;
			case 5770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565770));
				orderActorToFactory(110566370, EnemyVesta, "Vesta_130");
				break;
			case 5830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565830));
				orderActorToFactory(110566430, EnemyVesta, "Vesta_131");
				break;
			case 5890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565890));
				orderActorToFactory(110566490, EnemyVesta, "Vesta_132");
				break;
			case 5900:
				orderActorToFactory(113776500, EnemyCeres, "Ceres_133");
				break;
			case 5930:
				orderActorToFactory(113876530, EnemyCeres, "Ceres_134");
				break;
			case 5950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110565950));
				orderActorToFactory(110566550, EnemyVesta, "Vesta_135");
				break;
			case 5960:
				orderActorToFactory(113976560, EnemyCeres, "Ceres_136");
				break;
			case 5990:
				orderActorToFactory(114076590, EnemyCeres, "Ceres_137");
				break;
			case 6010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566010));
				orderActorToFactory(110566610, EnemyVesta, "Vesta_138");
				break;
			case 6020:
				orderActorToFactory(114176620, EnemyCeres, "Ceres_139");
				break;
			case 6050:
				orderActorToFactory(114276650, EnemyCeres, "Ceres_140");
				break;
			case 6070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566070));
				orderActorToFactory(110566670, EnemyVesta, "Vesta_141");
				break;
			case 6130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566130));
				orderActorToFactory(110566730, EnemyVesta, "Vesta_142");
				break;
			case 6190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566190));
				orderActorToFactory(110566790, EnemyVesta, "Vesta_143");
				break;
			case 6250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566250));
				orderActorToFactory(110566850, EnemyVesta, "Vesta_144");
				break;
			case 6300:
				orderActorToFactory(110976900, EnemyAstraea, "Astraea_145");
				break;
			case 6310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566310));
				orderActorToFactory(110566910, EnemyVesta, "Vesta_146");
				break;
			case 6370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566370));
				orderActorToFactory(110566970, EnemyVesta, "Vesta_147");
				break;
			case 6430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566430));
				orderActorToFactory(110567030, EnemyVesta, "Vesta_148");
				break;
			case 6490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566490));
				orderActorToFactory(110567090, EnemyVesta, "Vesta_149");
				break;
			case 6500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113876530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566550));
				orderActorToFactory(110567150, EnemyVesta, "Vesta_150");
				break;
			case 6560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113976560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114076590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566610));
				orderActorToFactory(110567210, EnemyVesta, "Vesta_151");
				break;
			case 6620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114176620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114276650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 6670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566670));
				orderActorToFactory(110567270, EnemyVesta, "Vesta_152");
				break;
			case 6730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566730));
				orderActorToFactory(110567330, EnemyVesta, "Vesta_153");
				break;
			case 6790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566790));
				orderActorToFactory(110567390, EnemyVesta, "Vesta_154");
				break;
			case 6850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566850));
				orderActorToFactory(110567450, EnemyVesta, "Vesta_155");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566910));
				orderActorToFactory(110567510, EnemyVesta, "Vesta_156");
				break;
			case 6970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110566970));
				orderActorToFactory(110567570, EnemyVesta, "Vesta_157");
				break;
			case 7030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567030));
				orderActorToFactory(110567630, EnemyVesta, "Vesta_158");
				break;
			case 7090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567090));
				orderActorToFactory(110567690, EnemyVesta, "Vesta_159");
				break;
			case 7150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567150));
				orderActorToFactory(110567750, EnemyVesta, "Vesta_160");
				break;
			case 7210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567210));
				orderActorToFactory(110567810, EnemyVesta, "Vesta_161");
				break;
			case 7270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567270));
				orderActorToFactory(110567870, EnemyVesta, "Vesta_162");
				break;
			case 7330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567330));
				orderActorToFactory(110567930, EnemyVesta, "Vesta_163");
				break;
			case 7390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567390));
				orderActorToFactory(110567990, EnemyVesta, "Vesta_164");
				break;
			case 7450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567450));
				orderActorToFactory(110568050, EnemyVesta, "Vesta_165");
				break;
			case 7510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567510));
				orderActorToFactory(110568110, EnemyVesta, "Vesta_166");
				break;
			case 7570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567570));
				orderActorToFactory(110568170, EnemyVesta, "Vesta_167");
				break;
			case 7600:
				orderActorToFactory(111678200, EnemyAstraea, "Astraea_168");
				break;
			case 7630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567630));
				orderActorToFactory(110568230, EnemyVesta, "Vesta_169");
				break;
			case 7690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567690));
				orderActorToFactory(110568290, EnemyVesta, "Vesta_170");
				break;
			case 7750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567750));
				orderActorToFactory(110568350, EnemyVesta, "Vesta_171");
				break;
			case 7810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567810));
				orderActorToFactory(110568410, EnemyVesta, "Vesta_172");
				break;
			case 7870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567870));
				orderActorToFactory(110568470, EnemyVesta, "Vesta_173");
				break;
			case 7900:
				orderActorToFactory(113778500, EnemyCeres, "Ceres_174");
				break;
			case 7930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567930));
				orderActorToFactory(110568530, EnemyVesta, "Vesta_175");
				orderActorToFactory(113878530, EnemyCeres, "Ceres_176");
				break;
			case 7960:
				orderActorToFactory(113978560, EnemyCeres, "Ceres_177");
				break;
			case 7990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110567990));
				orderActorToFactory(110568590, EnemyVesta, "Vesta_178");
				orderActorToFactory(114078590, EnemyCeres, "Ceres_179");
				break;
			case 8020:
				orderActorToFactory(114178620, EnemyCeres, "Ceres_180");
				break;
			case 8050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568050));
				orderActorToFactory(110568650, EnemyVesta, "Vesta_181");
				orderActorToFactory(114278650, EnemyCeres, "Ceres_182");
				break;
			case 8100:
				orderActorToFactory(111178700, EnemyAstraea, "Astraea_183");
				break;
			case 8110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568110));
				orderActorToFactory(110568710, EnemyVesta, "Vesta_184");
				break;
			case 8170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568170));
				orderActorToFactory(110568770, EnemyVesta, "Vesta_185");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568230));
				orderActorToFactory(110568830, EnemyVesta, "Vesta_186");
				break;
			case 8290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568290));
				orderActorToFactory(110568890, EnemyVesta, "Vesta_187");
				break;
			case 8350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568350));
				orderActorToFactory(110568950, EnemyVesta, "Vesta_188");
				break;
			case 8410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568410));
				orderActorToFactory(110569010, EnemyVesta, "Vesta_189");
				break;
			case 8470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568470));
				orderActorToFactory(110569070, EnemyVesta, "Vesta_190");
				break;
			case 8500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113778500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568530));
				orderActorToFactory(110569130, EnemyVesta, "Vesta_191");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113878530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113978560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568590));
				orderActorToFactory(110569190, EnemyVesta, "Vesta_192");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114078590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114178620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568650));
				orderActorToFactory(110569250, EnemyVesta, "Vesta_193");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(114278650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568710));
				orderActorToFactory(110569310, EnemyVesta, "Vesta_194");
				break;
			case 8770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568770));
				orderActorToFactory(110569370, EnemyVesta, "Vesta_195");
				break;
			case 8830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568830));
				orderActorToFactory(110569430, EnemyVesta, "Vesta_196");
				break;
			case 8890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568890));
				orderActorToFactory(110569490, EnemyVesta, "Vesta_197");
				break;
			case 8950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110568950));
				orderActorToFactory(110569550, EnemyVesta, "Vesta_198");
				break;
			case 9010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569010));
				orderActorToFactory(110569610, EnemyVesta, "Vesta_199");
				break;
			case 9070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569070));
				orderActorToFactory(110569670, EnemyVesta, "Vesta_200");
				break;
			case 9130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569130));
				orderActorToFactory(110569730, EnemyVesta, "Vesta_201");
				break;
			case 9190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569190));
				orderActorToFactory(110569790, EnemyVesta, "Vesta_202");
				break;
			case 9250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569250));
				orderActorToFactory(110569850, EnemyVesta, "Vesta_203");
				break;
			case 9310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569310));
				orderActorToFactory(110569910, EnemyVesta, "Vesta_204");
				break;
			case 9370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569370));
				orderActorToFactory(110569970, EnemyVesta, "Vesta_205");
				break;
			case 9400:
				orderActorToFactory(1118710000, EnemyAstraea, "Astraea_206");
				break;
			case 9430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569430));
				orderActorToFactory(1105610030, EnemyVesta, "Vesta_207");
				break;
			case 9490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569490));
				orderActorToFactory(1105610090, EnemyVesta, "Vesta_208");
				break;
			case 9500:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_209");
				break;
			case 9550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569550));
				orderActorToFactory(1105610150, EnemyVesta, "Vesta_210");
				break;
			case 9610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569610));
				orderActorToFactory(1105610210, EnemyVesta, "Vesta_211");
				break;
			case 9670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569670));
				orderActorToFactory(1105610270, EnemyVesta, "Vesta_212");
				break;
			case 9730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569730));
				orderActorToFactory(1105610330, EnemyVesta, "Vesta_213");
				break;
			case 9790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569790));
				orderActorToFactory(1105610390, EnemyVesta, "Vesta_214");
				break;
			case 9850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569850));
				orderActorToFactory(1105610450, EnemyVesta, "Vesta_215");
				break;
			case 9900:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_216");
				orderActorToFactory(1137710500, EnemyCeres, "Ceres_217");
				break;
			case 9910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569910));
				orderActorToFactory(1105610510, EnemyVesta, "Vesta_218");
				break;
			case 9930:
				orderActorToFactory(1138710530, EnemyCeres, "Ceres_219");
				break;
			case 9960:
				orderActorToFactory(1139710560, EnemyCeres, "Ceres_220");
				break;
			case 9970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(110569970));
				orderActorToFactory(1105610570, EnemyVesta, "Vesta_221");
				break;
			case 9990:
				orderActorToFactory(1140710590, EnemyCeres, "Ceres_222");
				break;
			case 10000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				break;
			case 10020:
				orderActorToFactory(1141710620, EnemyCeres, "Ceres_223");
				break;
			case 10030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610030));
				orderActorToFactory(1105610630, EnemyVesta, "Vesta_224");
				break;
			case 10050:
				orderActorToFactory(1142710650, EnemyCeres, "Ceres_225");
				break;
			case 10090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610090));
				orderActorToFactory(1105610690, EnemyVesta, "Vesta_226");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610150));
				orderActorToFactory(1105610750, EnemyVesta, "Vesta_227");
				break;
			case 10210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610210));
				orderActorToFactory(1105610810, EnemyVesta, "Vesta_228");
				break;
			case 10270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610270));
				orderActorToFactory(1105610870, EnemyVesta, "Vesta_229");
				break;
			case 10330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610330));
				orderActorToFactory(1105610930, EnemyVesta, "Vesta_230");
				break;
			case 10390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610390));
				orderActorToFactory(1105610990, EnemyVesta, "Vesta_231");
				break;
			case 10450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610450));
				orderActorToFactory(1105611050, EnemyVesta, "Vesta_232");
				break;
			case 10500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137710500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610510));
				orderActorToFactory(1105611110, EnemyVesta, "Vesta_233");
				break;
			case 10530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138710530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139710560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610570));
				orderActorToFactory(1105611170, EnemyVesta, "Vesta_234");
				break;
			case 10590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140710590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141710620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610630));
				orderActorToFactory(1105611230, EnemyVesta, "Vesta_235");
				break;
			case 10650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142710650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 10690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610690));
				orderActorToFactory(1105611290, EnemyVesta, "Vesta_236");
				break;
			case 10750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610750));
				orderActorToFactory(1105611350, EnemyVesta, "Vesta_237");
				break;
			case 10810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610810));
				orderActorToFactory(1105611410, EnemyVesta, "Vesta_238");
				break;
			case 10870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610870));
				orderActorToFactory(1105611470, EnemyVesta, "Vesta_239");
				break;
			case 10930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610930));
				orderActorToFactory(1105611530, EnemyVesta, "Vesta_240");
				break;
			case 10990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105610990));
				orderActorToFactory(1105611590, EnemyVesta, "Vesta_241");
				break;
			case 11050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611050));
				orderActorToFactory(1105611650, EnemyVesta, "Vesta_242");
				break;
			case 11110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611110));
				orderActorToFactory(1105611710, EnemyVesta, "Vesta_243");
				break;
			case 11170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611170));
				orderActorToFactory(1105611770, EnemyVesta, "Vesta_244");
				break;
			case 11200:
				orderActorToFactory(1120711800, EnemyAstraea, "Astraea_245");
				break;
			case 11230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611230));
				orderActorToFactory(1105611830, EnemyVesta, "Vesta_246");
				break;
			case 11290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611290));
				orderActorToFactory(1105611890, EnemyVesta, "Vesta_247");
				break;
			case 11300:
				orderActorToFactory(1109711900, EnemyAstraea, "Astraea_248");
				break;
			case 11350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611350));
				orderActorToFactory(1105611950, EnemyVesta, "Vesta_249");
				break;
			case 11410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611410));
				orderActorToFactory(1105612010, EnemyVesta, "Vesta_250");
				break;
			case 11470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611470));
				orderActorToFactory(1105612070, EnemyVesta, "Vesta_251");
				break;
			case 11530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611530));
				orderActorToFactory(1105612130, EnemyVesta, "Vesta_252");
				break;
			case 11590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611590));
				orderActorToFactory(1105612190, EnemyVesta, "Vesta_253");
				break;
			case 11650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611650));
				orderActorToFactory(1105612250, EnemyVesta, "Vesta_254");
				break;
			case 11710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611710));
				orderActorToFactory(1105612310, EnemyVesta, "Vesta_255");
				break;
			case 11770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611770));
				orderActorToFactory(1105612370, EnemyVesta, "Vesta_256");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611830));
				orderActorToFactory(1105612430, EnemyVesta, "Vesta_257");
				break;
			case 11890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611890));
				orderActorToFactory(1105612490, EnemyVesta, "Vesta_258");
				break;
			case 11900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109711900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1137712500, EnemyCeres, "Ceres_259");
				break;
			case 11930:
				orderActorToFactory(1138712530, EnemyCeres, "Ceres_260");
				break;
			case 11950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105611950));
				orderActorToFactory(1105612550, EnemyVesta, "Vesta_261");
				break;
			case 11960:
				orderActorToFactory(1139712560, EnemyCeres, "Ceres_262");
				break;
			case 11990:
				orderActorToFactory(1140712590, EnemyCeres, "Ceres_263");
				break;
			case 12010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612010));
				orderActorToFactory(1105612610, EnemyVesta, "Vesta_264");
				break;
			case 12020:
				orderActorToFactory(1141712620, EnemyCeres, "Ceres_265");
				break;
			case 12050:
				orderActorToFactory(1142712650, EnemyCeres, "Ceres_266");
				break;
			case 12070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612070));
				orderActorToFactory(1105612670, EnemyVesta, "Vesta_267");
				break;
			case 12130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612130));
				orderActorToFactory(1105612730, EnemyVesta, "Vesta_268");
				break;
			case 12190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612190));
				orderActorToFactory(1105612790, EnemyVesta, "Vesta_269");
				break;
			case 12250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612250));
				orderActorToFactory(1105612850, EnemyVesta, "Vesta_270");
				break;
			case 12310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612310));
				orderActorToFactory(1105612910, EnemyVesta, "Vesta_271");
				break;
			case 12370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612370));
				orderActorToFactory(1105612970, EnemyVesta, "Vesta_272");
				break;
			case 12430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612430));
				orderActorToFactory(1105613030, EnemyVesta, "Vesta_273");
				break;
			case 12490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612490));
				orderActorToFactory(1105613090, EnemyVesta, "Vesta_274");
				break;
			case 12500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137712500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138712530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612550));
				orderActorToFactory(1105613150, EnemyVesta, "Vesta_275");
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139712560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140712590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12600:
				orderActorToFactory(1116713200, EnemyAstraea, "Astraea_276");
				break;
			case 12610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612610));
				orderActorToFactory(1105613210, EnemyVesta, "Vesta_277");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141712620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142712650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 12670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612670));
				orderActorToFactory(1105613270, EnemyVesta, "Vesta_278");
				break;
			case 12730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612730));
				orderActorToFactory(1105613330, EnemyVesta, "Vesta_279");
				break;
			case 12790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612790));
				orderActorToFactory(1105613390, EnemyVesta, "Vesta_280");
				break;
			case 12850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612850));
				orderActorToFactory(1105613450, EnemyVesta, "Vesta_281");
				break;
			case 12910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612910));
				orderActorToFactory(1105613510, EnemyVesta, "Vesta_282");
				break;
			case 12970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105612970));
				orderActorToFactory(1105613570, EnemyVesta, "Vesta_283");
				break;
			case 13030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613030));
				orderActorToFactory(1105613630, EnemyVesta, "Vesta_284");
				break;
			case 13090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613090));
				orderActorToFactory(1105613690, EnemyVesta, "Vesta_285");
				break;
			case 13100:
				orderActorToFactory(1111713700, EnemyAstraea, "Astraea_286");
				break;
			case 13150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613150));
				orderActorToFactory(1105613750, EnemyVesta, "Vesta_287");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613210));
				orderActorToFactory(1105613810, EnemyVesta, "Vesta_288");
				break;
			case 13270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613270));
				orderActorToFactory(1105613870, EnemyVesta, "Vesta_289");
				break;
			case 13330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613330));
				orderActorToFactory(1105613930, EnemyVesta, "Vesta_290");
				break;
			case 13390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613390));
				orderActorToFactory(1105613990, EnemyVesta, "Vesta_291");
				break;
			case 13450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613450));
				orderActorToFactory(1105614050, EnemyVesta, "Vesta_292");
				break;
			case 13510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613510));
				orderActorToFactory(1105614110, EnemyVesta, "Vesta_293");
				break;
			case 13570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613570));
				orderActorToFactory(1105614170, EnemyVesta, "Vesta_294");
				break;
			case 13630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613630));
				orderActorToFactory(1105614230, EnemyVesta, "Vesta_295");
				break;
			case 13690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613690));
				orderActorToFactory(1105614290, EnemyVesta, "Vesta_296");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613750));
				orderActorToFactory(1105614350, EnemyVesta, "Vesta_297");
				break;
			case 13810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613810));
				orderActorToFactory(1105614410, EnemyVesta, "Vesta_298");
				break;
			case 13870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613870));
				orderActorToFactory(1105614470, EnemyVesta, "Vesta_299");
				break;
			case 13900:
				orderActorToFactory(1137714500, EnemyCeres, "Ceres_300");
				break;
			case 13930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613930));
				orderActorToFactory(1105614530, EnemyVesta, "Vesta_301");
				orderActorToFactory(1138714530, EnemyCeres, "Ceres_302");
				break;
			case 13960:
				orderActorToFactory(1139714560, EnemyCeres, "Ceres_303");
				break;
			case 13990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105613990));
				orderActorToFactory(1105614590, EnemyVesta, "Vesta_304");
				orderActorToFactory(1140714590, EnemyCeres, "Ceres_305");
				break;
			case 14020:
				orderActorToFactory(1141714620, EnemyCeres, "Ceres_306");
				break;
			case 14050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614050));
				orderActorToFactory(1105614650, EnemyVesta, "Vesta_307");
				orderActorToFactory(1142714650, EnemyCeres, "Ceres_308");
				break;
			case 14110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614110));
				orderActorToFactory(1105614710, EnemyVesta, "Vesta_309");
				break;
			case 14170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614170));
				orderActorToFactory(1105614770, EnemyVesta, "Vesta_310");
				break;
			case 14230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614230));
				orderActorToFactory(1105614830, EnemyVesta, "Vesta_311");
				break;
			case 14290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614290));
				orderActorToFactory(1105614890, EnemyVesta, "Vesta_312");
				break;
			case 14350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614350));
				orderActorToFactory(1105614950, EnemyVesta, "Vesta_313");
				break;
			case 14400:
				orderActorToFactory(1118715000, EnemyAstraea, "Astraea_314");
				break;
			case 14410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614410));
				orderActorToFactory(1105615010, EnemyVesta, "Vesta_315");
				break;
			case 14470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614470));
				orderActorToFactory(1105615070, EnemyVesta, "Vesta_316");
				break;
			case 14500:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_317");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137714500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614530));
				orderActorToFactory(1105615130, EnemyVesta, "Vesta_318");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138714530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139714560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614590));
				orderActorToFactory(1105615190, EnemyVesta, "Vesta_319");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140714590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141714620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614650));
				orderActorToFactory(1105615250, EnemyVesta, "Vesta_320");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142714650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 14710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614710));
				orderActorToFactory(1105615310, EnemyVesta, "Vesta_321");
				break;
			case 14770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614770));
				orderActorToFactory(1105615370, EnemyVesta, "Vesta_322");
				break;
			case 14830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614830));
				orderActorToFactory(1105615430, EnemyVesta, "Vesta_323");
				break;
			case 14890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614890));
				orderActorToFactory(1105615490, EnemyVesta, "Vesta_324");
				break;
			case 14900:
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_325");
				break;
			case 14950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105614950));
				orderActorToFactory(1105615550, EnemyVesta, "Vesta_326");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615010));
				orderActorToFactory(1105615610, EnemyVesta, "Vesta_327");
				break;
			case 15070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615070));
				orderActorToFactory(1105615670, EnemyVesta, "Vesta_328");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615130));
				orderActorToFactory(1105615730, EnemyVesta, "Vesta_329");
				break;
			case 15190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615190));
				orderActorToFactory(1105615790, EnemyVesta, "Vesta_330");
				break;
			case 15250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615250));
				orderActorToFactory(1105615850, EnemyVesta, "Vesta_331");
				break;
			case 15310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615310));
				orderActorToFactory(1105615910, EnemyVesta, "Vesta_332");
				break;
			case 15370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615370));
				orderActorToFactory(1105615970, EnemyVesta, "Vesta_333");
				break;
			case 15430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615430));
				orderActorToFactory(1105616030, EnemyVesta, "Vesta_334");
				break;
			case 15490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615490));
				orderActorToFactory(1105616090, EnemyVesta, "Vesta_335");
				break;
			case 15500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				break;
			case 15550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615550));
				orderActorToFactory(1105616150, EnemyVesta, "Vesta_336");
				break;
			case 15610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615610));
				orderActorToFactory(1105616210, EnemyVesta, "Vesta_337");
				break;
			case 15670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615670));
				orderActorToFactory(1105616270, EnemyVesta, "Vesta_338");
				break;
			case 15730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615730));
				orderActorToFactory(1105616330, EnemyVesta, "Vesta_339");
				break;
			case 15790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615790));
				orderActorToFactory(1105616390, EnemyVesta, "Vesta_340");
				break;
			case 15850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615850));
				orderActorToFactory(1105616450, EnemyVesta, "Vesta_341");
				break;
			case 15900:
				orderActorToFactory(1137716500, EnemyCeres, "Ceres_342");
				break;
			case 15910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615910));
				orderActorToFactory(1105616510, EnemyVesta, "Vesta_343");
				break;
			case 15930:
				orderActorToFactory(1138716530, EnemyCeres, "Ceres_344");
				break;
			case 15960:
				orderActorToFactory(1139716560, EnemyCeres, "Ceres_345");
				break;
			case 15970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105615970));
				orderActorToFactory(1105616570, EnemyVesta, "Vesta_346");
				break;
			case 15990:
				orderActorToFactory(1140716590, EnemyCeres, "Ceres_347");
				break;
			case 16020:
				orderActorToFactory(1141716620, EnemyCeres, "Ceres_348");
				break;
			case 16030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616030));
				orderActorToFactory(1105616630, EnemyVesta, "Vesta_349");
				break;
			case 16050:
				orderActorToFactory(1142716650, EnemyCeres, "Ceres_350");
				break;
			case 16090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616090));
				orderActorToFactory(1105616690, EnemyVesta, "Vesta_351");
				break;
			case 16150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616150));
				orderActorToFactory(1105616750, EnemyVesta, "Vesta_352");
				break;
			case 16200:
				orderActorToFactory(1120716800, EnemyAstraea, "Astraea_353");
				break;
			case 16210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616210));
				orderActorToFactory(1105616810, EnemyVesta, "Vesta_354");
				break;
			case 16270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616270));
				orderActorToFactory(1105616870, EnemyVesta, "Vesta_355");
				break;
			case 16300:
				orderActorToFactory(1109716900, EnemyAstraea, "Astraea_356");
				break;
			case 16330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616330));
				orderActorToFactory(1105616930, EnemyVesta, "Vesta_357");
				break;
			case 16390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616390));
				orderActorToFactory(1105616990, EnemyVesta, "Vesta_358");
				break;
			case 16450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616450));
				orderActorToFactory(1105617050, EnemyVesta, "Vesta_359");
				break;
			case 16500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137716500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616510));
				orderActorToFactory(1105617110, EnemyVesta, "Vesta_360");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138716530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139716560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616570));
				orderActorToFactory(1105617170, EnemyVesta, "Vesta_361");
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140716590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141716620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616630));
				orderActorToFactory(1105617230, EnemyVesta, "Vesta_362");
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142716650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 16690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616690));
				orderActorToFactory(1105617290, EnemyVesta, "Vesta_363");
				break;
			case 16750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616750));
				orderActorToFactory(1105617350, EnemyVesta, "Vesta_364");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616810));
				orderActorToFactory(1105617410, EnemyVesta, "Vesta_365");
				break;
			case 16870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616870));
				orderActorToFactory(1105617470, EnemyVesta, "Vesta_366");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616930));
				orderActorToFactory(1105617530, EnemyVesta, "Vesta_367");
				break;
			case 16990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105616990));
				orderActorToFactory(1105617590, EnemyVesta, "Vesta_368");
				break;
			case 17050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617050));
				orderActorToFactory(1105617650, EnemyVesta, "Vesta_369");
				break;
			case 17110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617110));
				orderActorToFactory(1105617710, EnemyVesta, "Vesta_370");
				break;
			case 17170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617170));
				orderActorToFactory(1105617770, EnemyVesta, "Vesta_371");
				break;
			case 17230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617230));
				orderActorToFactory(1105617830, EnemyVesta, "Vesta_372");
				break;
			case 17290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617290));
				orderActorToFactory(1105617890, EnemyVesta, "Vesta_373");
				break;
			case 17350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617350));
				orderActorToFactory(1105617950, EnemyVesta, "Vesta_374");
				break;
			case 17410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617410));
				orderActorToFactory(1105618010, EnemyVesta, "Vesta_375");
				break;
			case 17470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617470));
				orderActorToFactory(1105618070, EnemyVesta, "Vesta_376");
				break;
			case 17530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617530));
				orderActorToFactory(1105618130, EnemyVesta, "Vesta_377");
				break;
			case 17590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617590));
				orderActorToFactory(1105618190, EnemyVesta, "Vesta_378");
				break;
			case 17600:
				orderActorToFactory(1116718200, EnemyAstraea, "Astraea_379");
				break;
			case 17650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617650));
				orderActorToFactory(1105618250, EnemyVesta, "Vesta_380");
				break;
			case 17710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617710));
				orderActorToFactory(1105618310, EnemyVesta, "Vesta_381");
				break;
			case 17770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617770));
				orderActorToFactory(1105618370, EnemyVesta, "Vesta_382");
				break;
			case 17830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617830));
				orderActorToFactory(1105618430, EnemyVesta, "Vesta_383");
				break;
			case 17890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617890));
				orderActorToFactory(1105618490, EnemyVesta, "Vesta_384");
				break;
			case 17900:
				orderActorToFactory(1137718500, EnemyCeres, "Ceres_385");
				break;
			case 17930:
				orderActorToFactory(1138718530, EnemyCeres, "Ceres_386");
				break;
			case 17950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105617950));
				orderActorToFactory(1105618550, EnemyVesta, "Vesta_387");
				break;
			case 17960:
				orderActorToFactory(1139718560, EnemyCeres, "Ceres_388");
				break;
			case 17990:
				orderActorToFactory(1140718590, EnemyCeres, "Ceres_389");
				break;
			case 18010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618010));
				orderActorToFactory(1105618610, EnemyVesta, "Vesta_390");
				break;
			case 18020:
				orderActorToFactory(1141718620, EnemyCeres, "Ceres_391");
				break;
			case 18050:
				orderActorToFactory(1142718650, EnemyCeres, "Ceres_392");
				break;
			case 18070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618070));
				orderActorToFactory(1105618670, EnemyVesta, "Vesta_393");
				break;
			case 18100:
				orderActorToFactory(1111718700, EnemyAstraea, "Astraea_394");
				break;
			case 18130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618130));
				orderActorToFactory(1105618730, EnemyVesta, "Vesta_395");
				break;
			case 18190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618190));
				orderActorToFactory(1105618790, EnemyVesta, "Vesta_396");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618250));
				orderActorToFactory(1105618850, EnemyVesta, "Vesta_397");
				break;
			case 18310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618310));
				orderActorToFactory(1105618910, EnemyVesta, "Vesta_398");
				break;
			case 18370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618370));
				orderActorToFactory(1105618970, EnemyVesta, "Vesta_399");
				break;
			case 18430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618430));
				orderActorToFactory(1105619030, EnemyVesta, "Vesta_400");
				break;
			case 18490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618490));
				orderActorToFactory(1105619090, EnemyVesta, "Vesta_401");
				break;
			case 18500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1137718500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1138718530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618550));
				orderActorToFactory(1105619150, EnemyVesta, "Vesta_402");
				break;
			case 18560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1139718560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1140718590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618610));
				orderActorToFactory(1105619210, EnemyVesta, "Vesta_403");
				break;
			case 18620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1141718620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1142718650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 18670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618670));
				orderActorToFactory(1105619270, EnemyVesta, "Vesta_404");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618730));
				orderActorToFactory(1105619330, EnemyVesta, "Vesta_405");
				break;
			case 18790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618790));
				orderActorToFactory(1105619390, EnemyVesta, "Vesta_406");
				break;
			case 18850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618850));
				orderActorToFactory(1105619450, EnemyVesta, "Vesta_407");
				break;
			case 18910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618910));
				orderActorToFactory(1105619510, EnemyVesta, "Vesta_408");
				break;
			case 18970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105618970));
				orderActorToFactory(1105619570, EnemyVesta, "Vesta_409");
				break;
			case 19030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619030));
				orderActorToFactory(1105619630, EnemyVesta, "Vesta_410");
				break;
			case 19090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619090));
				orderActorToFactory(1105619690, EnemyVesta, "Vesta_411");
				break;
			case 19150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619150));
				orderActorToFactory(1105619750, EnemyVesta, "Vesta_412");
				break;
			case 19210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619210));
				orderActorToFactory(1105619810, EnemyVesta, "Vesta_413");
				break;
			case 19270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619270));
				orderActorToFactory(1105619870, EnemyVesta, "Vesta_414");
				break;
			case 19330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619330));
				orderActorToFactory(1105619930, EnemyVesta, "Vesta_415");
				break;
			case 19390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619390));
				orderActorToFactory(1105619990, EnemyVesta, "Vesta_416");
				break;
			case 19400:
				orderActorToFactory(1118720000, EnemyAstraea, "Astraea_417");
				break;
			case 19450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619450));
				orderActorToFactory(1105620050, EnemyVesta, "Vesta_418");
				break;
			case 19510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619510));
				orderActorToFactory(1105620110, EnemyVesta, "Vesta_419");
				break;
			case 19570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619570));
				orderActorToFactory(1105620170, EnemyVesta, "Vesta_420");
				break;
			case 19630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619630));
				orderActorToFactory(1105620230, EnemyVesta, "Vesta_421");
				break;
			case 19690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619690));
				orderActorToFactory(1105620290, EnemyVesta, "Vesta_422");
				break;
			case 19750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619750));
				orderActorToFactory(1105620350, EnemyVesta, "Vesta_423");
				break;
			case 19810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619810));
				orderActorToFactory(1105620410, EnemyVesta, "Vesta_424");
				break;
			case 19870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619870));
				orderActorToFactory(1105620470, EnemyVesta, "Vesta_425");
				break;
			case 19930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619930));
				orderActorToFactory(1105620530, EnemyVesta, "Vesta_426");
				break;
			case 19990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105619990));
				orderActorToFactory(1105620590, EnemyVesta, "Vesta_427");
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
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620050));
				orderActorToFactory(1105620650, EnemyVesta, "Vesta_428");
				break;
			case 20110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620110));
				orderActorToFactory(1105620710, EnemyVesta, "Vesta_429");
				break;
			case 20170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620170));
				orderActorToFactory(1105620770, EnemyVesta, "Vesta_430");
				break;
			case 20230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620230));
				orderActorToFactory(1105620830, EnemyVesta, "Vesta_431");
				break;
			case 20290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620290));
				orderActorToFactory(1105620890, EnemyVesta, "Vesta_432");
				break;
			case 20350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620350));
				orderActorToFactory(1105620950, EnemyVesta, "Vesta_433");
				break;
			case 20410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620410));
				orderActorToFactory(1105621010, EnemyVesta, "Vesta_434");
				break;
			case 20470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620470));
				orderActorToFactory(1105621070, EnemyVesta, "Vesta_435");
				break;
			case 20530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620530));
				orderActorToFactory(1105621130, EnemyVesta, "Vesta_436");
				break;
			case 20590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620590));
				orderActorToFactory(1105621190, EnemyVesta, "Vesta_437");
				break;
			case 20650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620650));
				orderActorToFactory(1105621250, EnemyVesta, "Vesta_438");
				break;
			case 20710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620710));
				orderActorToFactory(1105621310, EnemyVesta, "Vesta_439");
				break;
			case 20770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620770));
				orderActorToFactory(1105621370, EnemyVesta, "Vesta_440");
				break;
			case 20830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620830));
				orderActorToFactory(1105621430, EnemyVesta, "Vesta_441");
				break;
			case 20890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620890));
				orderActorToFactory(1105621490, EnemyVesta, "Vesta_442");
				break;
			case 20950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105620950));
				orderActorToFactory(1105621550, EnemyVesta, "Vesta_443");
				break;
			case 21010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621010));
				orderActorToFactory(1105621610, EnemyVesta, "Vesta_444");
				break;
			case 21070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621070));
				orderActorToFactory(1105621670, EnemyVesta, "Vesta_445");
				break;
			case 21130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621130));
				orderActorToFactory(1105621730, EnemyVesta, "Vesta_446");
				break;
			case 21190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621190));
				orderActorToFactory(1105621790, EnemyVesta, "Vesta_447");
				break;
			case 21250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621250));
				orderActorToFactory(1105621850, EnemyVesta, "Vesta_448");
				break;
			case 21310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621310));
				orderActorToFactory(1105621910, EnemyVesta, "Vesta_449");
				break;
			case 21370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621370));
				orderActorToFactory(1105621970, EnemyVesta, "Vesta_450");
				break;
			case 21430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621430));
				orderActorToFactory(1105622030, EnemyVesta, "Vesta_451");
				break;
			case 21490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621490));
				orderActorToFactory(1105622090, EnemyVesta, "Vesta_452");
				break;
			case 21550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621550));
				orderActorToFactory(1105622150, EnemyVesta, "Vesta_453");
				break;
			case 21610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621610));
				orderActorToFactory(1105622210, EnemyVesta, "Vesta_454");
				break;
			case 21670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621670));
				orderActorToFactory(1105622270, EnemyVesta, "Vesta_455");
				break;
			case 21730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621730));
				orderActorToFactory(1105622330, EnemyVesta, "Vesta_456");
				break;
			case 21790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621790));
				orderActorToFactory(1105622390, EnemyVesta, "Vesta_457");
				break;
			case 21850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621850));
				orderActorToFactory(1105622450, EnemyVesta, "Vesta_458");
				break;
			case 21910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621910));
				orderActorToFactory(1105622510, EnemyVesta, "Vesta_459");
				break;
			case 21970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105621970));
				orderActorToFactory(1105622570, EnemyVesta, "Vesta_460");
				break;
			case 22030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622030));
				orderActorToFactory(1105622630, EnemyVesta, "Vesta_461");
				break;
			case 22090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622090));
				orderActorToFactory(1105622690, EnemyVesta, "Vesta_462");
				break;
			case 22150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622150));
				orderActorToFactory(1105622750, EnemyVesta, "Vesta_463");
				break;
			case 22210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622210));
				orderActorToFactory(1105622810, EnemyVesta, "Vesta_464");
				break;
			case 22270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622270));
				orderActorToFactory(1105622870, EnemyVesta, "Vesta_465");
				break;
			case 22330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622330));
				orderActorToFactory(1105622930, EnemyVesta, "Vesta_466");
				break;
			case 22390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622390));
				orderActorToFactory(1105622990, EnemyVesta, "Vesta_467");
				break;
			case 22450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622450));
				orderActorToFactory(1105623050, EnemyVesta, "Vesta_468");
				break;
			case 22510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622510));
				orderActorToFactory(1105623110, EnemyVesta, "Vesta_469");
				break;
			case 22570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622570));
				orderActorToFactory(1105623170, EnemyVesta, "Vesta_470");
				break;
			case 22630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622630));
				orderActorToFactory(1105623230, EnemyVesta, "Vesta_471");
				break;
			case 22690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622690));
				orderActorToFactory(1105623290, EnemyVesta, "Vesta_472");
				break;
			case 22750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622750));
				orderActorToFactory(1105623350, EnemyVesta, "Vesta_473");
				break;
			case 22810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622810));
				orderActorToFactory(1105623410, EnemyVesta, "Vesta_474");
				break;
			case 22870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622870));
				orderActorToFactory(1105623470, EnemyVesta, "Vesta_475");
				break;
			case 22930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622930));
				orderActorToFactory(1105623530, EnemyVesta, "Vesta_476");
				break;
			case 22990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105622990));
				orderActorToFactory(1105623590, EnemyVesta, "Vesta_477");
				break;
			case 23050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623050));
				orderActorToFactory(1105623650, EnemyVesta, "Vesta_478");
				break;
			case 23110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623110));
				orderActorToFactory(1105623710, EnemyVesta, "Vesta_479");
				break;
			case 23170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623170));
				orderActorToFactory(1105623770, EnemyVesta, "Vesta_480");
				break;
			case 23230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623230));
				orderActorToFactory(1105623830, EnemyVesta, "Vesta_481");
				break;
			case 23290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623290));
				orderActorToFactory(1105623890, EnemyVesta, "Vesta_482");
				break;
			case 23350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623350));
				orderActorToFactory(1105623950, EnemyVesta, "Vesta_483");
				break;
			case 23410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623410));
				orderActorToFactory(1105624010, EnemyVesta, "Vesta_484");
				break;
			case 23470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623470));
				orderActorToFactory(1105624070, EnemyVesta, "Vesta_485");
				break;
			case 23530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623530));
				orderActorToFactory(1105624130, EnemyVesta, "Vesta_486");
				break;
			case 23590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623590));
				orderActorToFactory(1105624190, EnemyVesta, "Vesta_487");
				break;
			case 23650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623650));
				orderActorToFactory(1105624250, EnemyVesta, "Vesta_488");
				break;
			case 23710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623710));
				orderActorToFactory(1105624310, EnemyVesta, "Vesta_489");
				break;
			case 23770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623770));
				orderActorToFactory(1105624370, EnemyVesta, "Vesta_490");
				break;
			case 23830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623830));
				orderActorToFactory(1105624430, EnemyVesta, "Vesta_491");
				break;
			case 23890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623890));
				orderActorToFactory(1105624490, EnemyVesta, "Vesta_492");
				break;
			case 23950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105623950));
				orderActorToFactory(1105624550, EnemyVesta, "Vesta_493");
				break;
			case 24010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624010));
				orderActorToFactory(1105624610, EnemyVesta, "Vesta_494");
				break;
			case 24070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624070));
				orderActorToFactory(1105624670, EnemyVesta, "Vesta_495");
				break;
			case 24130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624130));
				orderActorToFactory(1105624730, EnemyVesta, "Vesta_496");
				break;
			case 24190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624190));
				orderActorToFactory(1105624790, EnemyVesta, "Vesta_497");
				break;
			case 24250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624250));
				orderActorToFactory(1105624850, EnemyVesta, "Vesta_498");
				break;
			case 24310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624310));
				orderActorToFactory(1105624910, EnemyVesta, "Vesta_499");
				break;
			case 24370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624370));
				orderActorToFactory(1105624970, EnemyVesta, "Vesta_500");
				break;
			case 24430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624430));
				orderActorToFactory(1105625030, EnemyVesta, "Vesta_501");
				break;
			case 24490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624490));
				orderActorToFactory(1105625090, EnemyVesta, "Vesta_502");
				break;
			case 24550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624550));
				orderActorToFactory(1105625150, EnemyVesta, "Vesta_503");
				break;
			case 24610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624610));
				orderActorToFactory(1105625210, EnemyVesta, "Vesta_504");
				break;
			case 24670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624670));
				orderActorToFactory(1105625270, EnemyVesta, "Vesta_505");
				break;
			case 24730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624730));
				orderActorToFactory(1105625330, EnemyVesta, "Vesta_506");
				break;
			case 24790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624790));
				orderActorToFactory(1105625390, EnemyVesta, "Vesta_507");
				break;
			case 24850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624850));
				orderActorToFactory(1105625450, EnemyVesta, "Vesta_508");
				break;
			case 24910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624910));
				orderActorToFactory(1105625510, EnemyVesta, "Vesta_509");
				break;
			case 24970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105624970));
				orderActorToFactory(1105625570, EnemyVesta, "Vesta_510");
				break;
			case 25030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625030));
				orderActorToFactory(1105625630, EnemyVesta, "Vesta_511");
				break;
			case 25090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625090));
				orderActorToFactory(1105625690, EnemyVesta, "Vesta_512");
				break;
			case 25150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625150));
				orderActorToFactory(1105625750, EnemyVesta, "Vesta_513");
				break;
			case 25210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625210));
				orderActorToFactory(1105625810, EnemyVesta, "Vesta_514");
				break;
			case 25270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625270));
				orderActorToFactory(1105625870, EnemyVesta, "Vesta_515");
				break;
			case 25330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625330));
				orderActorToFactory(1105625930, EnemyVesta, "Vesta_516");
				break;
			case 25390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625390));
				orderActorToFactory(1105625990, EnemyVesta, "Vesta_517");
				break;
			case 25450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625450));
				orderActorToFactory(1105626050, EnemyVesta, "Vesta_518");
				break;
			case 25510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625510));
				orderActorToFactory(1105626110, EnemyVesta, "Vesta_519");
				break;
			case 25570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625570));
				orderActorToFactory(1105626170, EnemyVesta, "Vesta_520");
				break;
			case 25630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625630));
				orderActorToFactory(1105626230, EnemyVesta, "Vesta_521");
				break;
			case 25690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625690));
				orderActorToFactory(1105626290, EnemyVesta, "Vesta_522");
				break;
			case 25750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625750));
				orderActorToFactory(1105626350, EnemyVesta, "Vesta_523");
				break;
			case 25810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625810));
				orderActorToFactory(1105626410, EnemyVesta, "Vesta_524");
				break;
			case 25870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625870));
				orderActorToFactory(1105626470, EnemyVesta, "Vesta_525");
				break;
			case 25930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625930));
				orderActorToFactory(1105626530, EnemyVesta, "Vesta_526");
				break;
			case 25990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105625990));
				orderActorToFactory(1105626590, EnemyVesta, "Vesta_527");
				break;
			case 26050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626050));
				orderActorToFactory(1105626650, EnemyVesta, "Vesta_528");
				break;
			case 26110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626110));
				orderActorToFactory(1105626710, EnemyVesta, "Vesta_529");
				break;
			case 26170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626170));
				orderActorToFactory(1105626770, EnemyVesta, "Vesta_530");
				break;
			case 26230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626230));
				orderActorToFactory(1105626830, EnemyVesta, "Vesta_531");
				break;
			case 26290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626290));
				orderActorToFactory(1105626890, EnemyVesta, "Vesta_532");
				break;
			case 26350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626350));
				orderActorToFactory(1105626950, EnemyVesta, "Vesta_533");
				break;
			case 26410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626410));
				orderActorToFactory(1105627010, EnemyVesta, "Vesta_534");
				break;
			case 26470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626470));
				orderActorToFactory(1105627070, EnemyVesta, "Vesta_535");
				break;
			case 26530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626530));
				orderActorToFactory(1105627130, EnemyVesta, "Vesta_536");
				break;
			case 26590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626590));
				orderActorToFactory(1105627190, EnemyVesta, "Vesta_537");
				break;
			case 26650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626650));
				orderActorToFactory(1105627250, EnemyVesta, "Vesta_538");
				break;
			case 26710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626710));
				orderActorToFactory(1105627310, EnemyVesta, "Vesta_539");
				break;
			case 26770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626770));
				orderActorToFactory(1105627370, EnemyVesta, "Vesta_540");
				break;
			case 26830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626830));
				orderActorToFactory(1105627430, EnemyVesta, "Vesta_541");
				break;
			case 26890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626890));
				orderActorToFactory(1105627490, EnemyVesta, "Vesta_542");
				break;
			case 26950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105626950));
				orderActorToFactory(1105627550, EnemyVesta, "Vesta_543");
				break;
			case 27010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627010));
				orderActorToFactory(1105627610, EnemyVesta, "Vesta_544");
				break;
			case 27070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627070));
				orderActorToFactory(1105627670, EnemyVesta, "Vesta_545");
				break;
			case 27130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627130));
				orderActorToFactory(1105627730, EnemyVesta, "Vesta_546");
				break;
			case 27190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627190));
				orderActorToFactory(1105627790, EnemyVesta, "Vesta_547");
				break;
			case 27250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627250));
				orderActorToFactory(1105627850, EnemyVesta, "Vesta_548");
				break;
			case 27310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627310));
				orderActorToFactory(1105627910, EnemyVesta, "Vesta_549");
				break;
			case 27370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627370));
				orderActorToFactory(1105627970, EnemyVesta, "Vesta_550");
				break;
			case 27430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627430));
				orderActorToFactory(1105628030, EnemyVesta, "Vesta_551");
				break;
			case 27490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627490));
				orderActorToFactory(1105628090, EnemyVesta, "Vesta_552");
				break;
			case 27550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627550));
				orderActorToFactory(1105628150, EnemyVesta, "Vesta_553");
				break;
			case 27610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627610));
				orderActorToFactory(1105628210, EnemyVesta, "Vesta_554");
				break;
			case 27670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627670));
				orderActorToFactory(1105628270, EnemyVesta, "Vesta_555");
				break;
			case 27730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627730));
				orderActorToFactory(1105628330, EnemyVesta, "Vesta_556");
				break;
			case 27790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627790));
				orderActorToFactory(1105628390, EnemyVesta, "Vesta_557");
				break;
			case 27850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627850));
				orderActorToFactory(1105628450, EnemyVesta, "Vesta_558");
				break;
			case 27910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627910));
				orderActorToFactory(1105628510, EnemyVesta, "Vesta_559");
				break;
			case 27970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105627970));
				orderActorToFactory(1105628570, EnemyVesta, "Vesta_560");
				break;
			case 28030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628030));
				orderActorToFactory(1105628630, EnemyVesta, "Vesta_561");
				break;
			case 28090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628090));
				orderActorToFactory(1105628690, EnemyVesta, "Vesta_562");
				break;
			case 28150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628150));
				orderActorToFactory(1105628750, EnemyVesta, "Vesta_563");
				break;
			case 28210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628210));
				orderActorToFactory(1105628810, EnemyVesta, "Vesta_564");
				break;
			case 28270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628270));
				orderActorToFactory(1105628870, EnemyVesta, "Vesta_565");
				break;
			case 28330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628330));
				orderActorToFactory(1105628930, EnemyVesta, "Vesta_566");
				break;
			case 28390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628390));
				orderActorToFactory(1105628990, EnemyVesta, "Vesta_567");
				break;
			case 28450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628450));
				orderActorToFactory(1105629050, EnemyVesta, "Vesta_568");
				break;
			case 28510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628510));
				orderActorToFactory(1105629110, EnemyVesta, "Vesta_569");
				break;
			case 28570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628570));
				orderActorToFactory(1105629170, EnemyVesta, "Vesta_570");
				break;
			case 28630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628630));
				orderActorToFactory(1105629230, EnemyVesta, "Vesta_571");
				break;
			case 28690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628690));
				orderActorToFactory(1105629290, EnemyVesta, "Vesta_572");
				break;
			case 28750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628750));
				orderActorToFactory(1105629350, EnemyVesta, "Vesta_573");
				break;
			case 28810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628810));
				orderActorToFactory(1105629410, EnemyVesta, "Vesta_574");
				break;
			case 28870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628870));
				orderActorToFactory(1105629470, EnemyVesta, "Vesta_575");
				break;
			case 28930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628930));
				orderActorToFactory(1105629530, EnemyVesta, "Vesta_576");
				break;
			case 28990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105628990));
				orderActorToFactory(1105629590, EnemyVesta, "Vesta_577");
				break;
			case 29050:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629050));
				orderActorToFactory(1105629650, EnemyVesta, "Vesta_578");
				break;
			case 29110:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629110));
				orderActorToFactory(1105629710, EnemyVesta, "Vesta_579");
				break;
			case 29170:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629170));
				orderActorToFactory(1105629770, EnemyVesta, "Vesta_580");
				break;
			case 29230:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629230));
				orderActorToFactory(1105629830, EnemyVesta, "Vesta_581");
				break;
			case 29290:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629290));
				orderActorToFactory(1105629890, EnemyVesta, "Vesta_582");
				break;
			case 29350:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629350));
				orderActorToFactory(1105629950, EnemyVesta, "Vesta_583");
				break;
			case 29410:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629410));
				orderActorToFactory(1105630010, EnemyVesta, "Vesta_584");
				break;
			case 29470:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629470));
				orderActorToFactory(1105630070, EnemyVesta, "Vesta_585");
				break;
			case 29530:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629530));
				orderActorToFactory(1105630130, EnemyVesta, "Vesta_586");
				break;
			case 29590:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629590));
				orderActorToFactory(1105630190, EnemyVesta, "Vesta_587");
				break;
			case 29650:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629650));
				orderActorToFactory(1105630250, EnemyVesta, "Vesta_588");
				break;
			case 29710:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629710));
				orderActorToFactory(1105630310, EnemyVesta, "Vesta_589");
				break;
			case 29770:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629770));
				orderActorToFactory(1105630370, EnemyVesta, "Vesta_590");
				break;
			case 29830:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629830));
				orderActorToFactory(1105630430, EnemyVesta, "Vesta_591");
				break;
			case 29890:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629890));
				orderActorToFactory(1105630490, EnemyVesta, "Vesta_592");
				break;
			case 29950:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105629950));
				orderActorToFactory(1105630550, EnemyVesta, "Vesta_593");
				break;
			case 30010:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630010));
				orderActorToFactory(1105630610, EnemyVesta, "Vesta_594");
				break;
			case 30070:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630070));
				orderActorToFactory(1105630670, EnemyVesta, "Vesta_595");
				break;
			case 30130:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630130));
				orderActorToFactory(1105630730, EnemyVesta, "Vesta_596");
				break;
			case 30190:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630190));
				orderActorToFactory(1105630790, EnemyVesta, "Vesta_597");
				break;
			case 30250:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630250));
				orderActorToFactory(1105630850, EnemyVesta, "Vesta_598");
				break;
			case 30310:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630310));
				orderActorToFactory(1105630910, EnemyVesta, "Vesta_599");
				break;
			case 30370:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630370));
				orderActorToFactory(1105630970, EnemyVesta, "Vesta_600");
				break;
			case 30430:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630430));
				orderActorToFactory(1105631030, EnemyVesta, "Vesta_601");
				break;
			case 30490:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630490));
				orderActorToFactory(1105631090, EnemyVesta, "Vesta_602");
				break;
			case 30550:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630550));
				orderActorToFactory(1105631150, EnemyVesta, "Vesta_603");
				break;
			case 30610:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630610));
				orderActorToFactory(1105631210, EnemyVesta, "Vesta_604");
				break;
			case 30670:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630670));
				orderActorToFactory(1105631270, EnemyVesta, "Vesta_605");
				break;
			case 30730:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630730));
				orderActorToFactory(1105631330, EnemyVesta, "Vesta_606");
				break;
			case 30790:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630790));
				orderActorToFactory(1105631390, EnemyVesta, "Vesta_607");
				break;
			case 30850:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630850));
				orderActorToFactory(1105631450, EnemyVesta, "Vesta_608");
				break;
			case 30910:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630910));
				orderActorToFactory(1105631510, EnemyVesta, "Vesta_609");
				break;
			case 30970:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105630970));
				orderActorToFactory(1105631570, EnemyVesta, "Vesta_610");
				break;
			case 31030:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631030));
				orderActorToFactory(1105631630, EnemyVesta, "Vesta_611");
				break;
			case 31090:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631090));
				orderActorToFactory(1105631690, EnemyVesta, "Vesta_612");
				break;
			case 31150:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631150));
				orderActorToFactory(1105631750, EnemyVesta, "Vesta_613");
				break;
			case 31210:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631210));
				orderActorToFactory(1105631810, EnemyVesta, "Vesta_614");
				break;
			case 31270:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631270));
				orderActorToFactory(1105631870, EnemyVesta, "Vesta_615");
				break;
			case 31330:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631330));
				orderActorToFactory(1105631930, EnemyVesta, "Vesta_616");
				break;
			case 31390:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631390));
				orderActorToFactory(1105631990, EnemyVesta, "Vesta_617");
				break;
			case 31450:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631450));
				break;
			case 31510:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631510));
				break;
			case 31570:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631570));
				break;
			case 31630:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631630));
				break;
			case 31690:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631690));
				break;
			case 31750:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631750));
				break;
			case 31810:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631810));
				break;
			case 31870:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631870));
				break;
			case 31930:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631930));
				break;
			case 31990:
				getLordActor()->accept(KIND_ENEMY, obtainActorFromFactory(1105631990));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_lifeframe== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_lifeframe== 1) {
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
