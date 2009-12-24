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
	DWORD dw[] = {1,10,70,100,130,160,190,220,250,280,310,340,370,400,430,460,490,500,520,530,550,560,580,590,610,620,640,650,670,700,730,760,790,820,850,880,900,910,940,970,1000,1030,1060,1090,1120,1150,1180,1210,1240,1270,1300,1330,1360,1390,1400,1420,1450,1480,1500,1510,1530,1540,1560,1570,1590,1600,1620,1630,1650,1660,1690,1720,1750,1780,1800,1810,1840,1870,1900,1930,1960,1990,2050,2100,2110,2170,2230,2290,2300,2350,2400,2410,2470,2500,2530,2560,2590,2620,2650,2710,2770,2800,2830,2890,2900,2950,3010,3070,3130,3190,3250,3300,3310,3370,3400,3430,3490,3500,3530,3550,3560,3590,3610,3620,3650,3670,3700,3730,3790,3800,3850,3900,3910,3970,4030,4090,4150,4200,4210,4270,4300,4330,4390,4400,4450,4500,4510,4530,4560,4570,4590,4620,4630,4650,4690,4700,4750,4800,4810,4870,4900,4930,4990,5050,5100,5110,5170,5200,5230,5290,5300,5350,5400,5410,5470,5500,5530,5560,5590,5600,5620,5650,5700,5710,5770,5800,5830,5890,5900,5950,6010,6070,6100,6130,6190,6200,6250,6300,6310,6370,6400,6430,6490,6500,6530,6550,6560,6590,6600,6610,6620,6650,6670,6700,6730,6790,6800,6850,6900,6910,6970,7030,7090,7100,7150,7200,7210,7270,7300,7330,7390,7400,7450,7500,7510,7530,7560,7570,7590,7600,7620,7630,7650,7690,7700,7750,7800,7810,7870,7900,7930,7990,8000,8050,8100,8110,8170,8200,8230,8290,8300,8350,8400,8410,8470,8500,8530,8560,8590,8600,8620,8650,8700,8710,8770,8800,8830,8890,8900,8950,9000,9010,9070,9100,9130,9190,9200,9250,9300,9310,9370,9400,9430,9490,9500,9530,9550,9560,9590,9600,9610,9620,9650,9670,9700,9730,9790,9800,9850,9900,9910,9970,10000,10030,10090,10100,10150,10200,10210,10270,10300,10330,10390,10400,10450,10500,10510,10530,10560,10570,10590,10600,10620,10630,10650,10690,10700,10750,10800,10810,10870,10900,10930,10990,11000,11050,11100,11110,11170,11200,11230,11290,11300,11350,11400,11410,11470,11500,11530,11560,11590,11600,11620,11650,11700,11710,11770,11800,11830,11890,11900,11950,12000,12010,12070,12100,12130,12190,12200,12250,12300,12310,12370,12400,12430,12490,12500,12530,12550,12560,12590,12600,12610,12620,12650,12670,12700,12730,12790,12800,12850,12900,12910,12970,13000,13030,13090,13100,13150,13200,13210,13270,13300,13330,13390,13400,13450,13500,13510,13530,13560,13570,13590,13600,13620,13630,13650,13690,13700,13750,13800,13810,13870,13900,13930,13990,14000,14050,14100,14110,14170,14200,14230,14290,14300,14350,14400,14410,14470,14500,14530,14560,14590,14600,14620,14650,14700,14710,14770,14800,14830,14890,14900,14950,15000,15010,15070,15100,15130,15190,15200,15250,15300,15310,15370,15400,15430,15490,15500,15530,15550,15560,15590,15600,15610,15620,15650,15670,15700,15730,15790,15800,15850,15900,15910,15970,16000,16030,16090,16100,16150,16200,16210,16270,16300,16330,16390,16400,16450,16500,16510,16530,16560,16570,16590,16600,16620,16630,16650,16690,16700,16750,16800,16810,16870,16900,16930,16990,17000,17050,17100,17110,17170,17200,17230,17290,17300,17350,17400,17410,17470,17500,17530,17560,17590,17600,17620,17650,17700,17710,17770,17800,17830,17890,17900,17950,18000,18010,18070,18100,18130,18190,18200,18250,18300,18310,18370,18400,18430,18490,18500,18530,18550,18560,18590,18600,18610,18620,18650,18670,18700,18730,18790,18800,18850,18900,18910,18970,19000,19030,19090,19100,19150,19200,19210,19270,19300,19330,19390,19400,19450,19500,19510,19530,19560,19570,19590,19600,19620,19630,19650,19690,19700,19750,19800,19810,19870,19900,19930,19990,20000,20050,20110,20170,20230,20290,20350,20410,20470,20530,20590,20650,20710,20770,20830,20890,20950,21010,21070,21130,21190,21250,21310,21370,21430,21490,21550,21610,21670,21730,21790,21850,21910,21970,22030,22090,22150,22210,22270,22330,22390,22450,22510,22570,22630,22690,22750,22810,22870,22930,22990,23050,23110,23170,23230,23290,23350,23410,23470,23530,23590,23650,23710,23770,23830,23890,23950,24010,24070,24130,24190,24250,24310,24370,24430,24490,24550,24610,24670,24730,24790,24850,24910,24970,25030,25090,25150,25210,25270,25330,25390,25450,25510,25570,25630,25690,25750,25810,25870,25930,25990,26050,26110,26170,26230,26290,26350,26410,26470,26530,26590,26650,26710,26770,26830,26890,26950,27010,27070,27130,27190,27250,27310,27370,27430,27490,27550,27610,27670,27730,27790,27850,27910,27970,28030,28090,28150,28210,28270,28330,28390,28450,28510,28570,28630,28690,28750,28810,28870,28930,28990,29050,29110,29170,29230,29290,29350,29410,29470,29530,29590,29650,29710,29770,29830,29890,29950,30010,30070,30130,30190,30250,30310,30370,30430,30490,30550,30610,30670,30730,30790,30850,30910,30970,31030,31090,31150,31210,31270,31330,31390,31450,31510,31570,31630,31690,31750,31810,31870,31930,31990};
	_paFrame_NextEvent = new DWORD[821];
	for (int i = 0; i < 821; i++) {
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
	orderActorToFactory(11057610, EnemyVesta, "Vesta_11");
	orderActorToFactory(11057670, EnemyVesta, "Vesta_12");
	orderActorToFactory(11057730, EnemyVesta, "Vesta_13");
	orderActorToFactory(11057790, EnemyVesta, "Vesta_14");
	orderActorToFactory(11057850, EnemyVesta, "Vesta_15");
	orderActorToFactory(11057910, EnemyVesta, "Vesta_16");
	orderActorToFactory(11057970, EnemyVesta, "Vesta_17");
	orderActorToFactory(110571030, EnemyVesta, "Vesta_18");
	orderActorToFactory(110571090, EnemyVesta, "Vesta_19");
	orderActorToFactory(110571150, EnemyVesta, "Vesta_20");
	orderActorToFactory(110571210, EnemyVesta, "Vesta_21");
	orderActorToFactory(110571270, EnemyVesta, "Vesta_22");
	orderActorToFactory(110571330, EnemyVesta, "Vesta_23");
	orderActorToFactory(110571390, EnemyVesta, "Vesta_24");
	orderActorToFactory(110571450, EnemyVesta, "Vesta_25");
	orderActorToFactory(110571510, EnemyVesta, "Vesta_26");
	orderActorToFactory(110571570, EnemyVesta, "Vesta_27");
	orderActorToFactory(110571630, EnemyVesta, "Vesta_28");
	orderActorToFactory(110571690, EnemyVesta, "Vesta_29");
	orderActorToFactory(110571750, EnemyVesta, "Vesta_30");
	orderActorToFactory(110571810, EnemyVesta, "Vesta_31");
	orderActorToFactory(110571870, EnemyVesta, "Vesta_32");
	orderActorToFactory(110571930, EnemyVesta, "Vesta_33");
	orderActorToFactory(110571990, EnemyVesta, "Vesta_34");
	orderActorToFactory(110572050, EnemyVesta, "Vesta_35");
	orderActorToFactory(110572110, EnemyVesta, "Vesta_36");
	orderActorToFactory(110572170, EnemyVesta, "Vesta_37");
	orderActorToFactory(110572230, EnemyVesta, "Vesta_38");
	orderActorToFactory(110572290, EnemyVesta, "Vesta_39");
	orderActorToFactory(110572350, EnemyVesta, "Vesta_40");
	orderActorToFactory(110572410, EnemyVesta, "Vesta_41");
	orderActorToFactory(110572470, EnemyVesta, "Vesta_42");
	orderActorToFactory(110572530, EnemyVesta, "Vesta_43");
	orderActorToFactory(110572590, EnemyVesta, "Vesta_44");
	orderActorToFactory(110572650, EnemyVesta, "Vesta_45");
	orderActorToFactory(110572710, EnemyVesta, "Vesta_46");
	orderActorToFactory(110572770, EnemyVesta, "Vesta_47");
	orderActorToFactory(110572830, EnemyVesta, "Vesta_48");
	orderActorToFactory(110572890, EnemyVesta, "Vesta_49");
	orderActorToFactory(110572950, EnemyVesta, "Vesta_50");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_51");
	orderActorToFactory(110972900, EnemyAstraea, "Astraea_52");
	orderActorToFactory(111671500, EnemyAstraea, "Astraea_53");
	orderActorToFactory(111672500, EnemyAstraea, "Astraea_54");
	orderActorToFactory(11247100, EnemyIris, "Iris_55");
	orderActorToFactory(11247130, EnemyIris, "Iris_56");
	orderActorToFactory(11247160, EnemyIris, "Iris_57");
	orderActorToFactory(11247190, EnemyIris, "Iris_58");
	orderActorToFactory(11247220, EnemyIris, "Iris_59");
	orderActorToFactory(11247250, EnemyIris, "Iris_60");
	orderActorToFactory(11247280, EnemyIris, "Iris_61");
	orderActorToFactory(11247310, EnemyIris, "Iris_62");
	orderActorToFactory(11247340, EnemyIris, "Iris_63");
	orderActorToFactory(11247370, EnemyIris, "Iris_64");
	orderActorToFactory(11247400, EnemyIris, "Iris_65");
	orderActorToFactory(11247430, EnemyIris, "Iris_66");
	orderActorToFactory(11247460, EnemyIris, "Iris_67");
	orderActorToFactory(11247490, EnemyIris, "Iris_68");
	orderActorToFactory(11247520, EnemyIris, "Iris_69");
	orderActorToFactory(11247550, EnemyIris, "Iris_70");
	orderActorToFactory(11247580, EnemyIris, "Iris_71");
	orderActorToFactory(11247610, EnemyIris, "Iris_72");
	orderActorToFactory(11247640, EnemyIris, "Iris_73");
	orderActorToFactory(11247670, EnemyIris, "Iris_74");
	orderActorToFactory(11247700, EnemyIris, "Iris_75");
	orderActorToFactory(11247730, EnemyIris, "Iris_76");
	orderActorToFactory(11247760, EnemyIris, "Iris_77");
	orderActorToFactory(11247790, EnemyIris, "Iris_78");
	orderActorToFactory(11247820, EnemyIris, "Iris_79");
	orderActorToFactory(11247850, EnemyIris, "Iris_80");
	orderActorToFactory(11247880, EnemyIris, "Iris_81");
	orderActorToFactory(11247910, EnemyIris, "Iris_82");
	orderActorToFactory(11247940, EnemyIris, "Iris_83");
	orderActorToFactory(11247970, EnemyIris, "Iris_84");
	orderActorToFactory(112471000, EnemyIris, "Iris_85");
	orderActorToFactory(112471030, EnemyIris, "Iris_86");
	orderActorToFactory(112471060, EnemyIris, "Iris_87");
	orderActorToFactory(112471090, EnemyIris, "Iris_88");
	orderActorToFactory(112471120, EnemyIris, "Iris_89");
	orderActorToFactory(112471150, EnemyIris, "Iris_90");
	orderActorToFactory(112471180, EnemyIris, "Iris_91");
	orderActorToFactory(112471210, EnemyIris, "Iris_92");
	orderActorToFactory(112471240, EnemyIris, "Iris_93");
	orderActorToFactory(112471270, EnemyIris, "Iris_94");
	orderActorToFactory(112471300, EnemyIris, "Iris_95");
	orderActorToFactory(112471330, EnemyIris, "Iris_96");
	orderActorToFactory(112471360, EnemyIris, "Iris_97");
	orderActorToFactory(112471390, EnemyIris, "Iris_98");
	orderActorToFactory(112471420, EnemyIris, "Iris_99");
	orderActorToFactory(112471450, EnemyIris, "Iris_100");
	orderActorToFactory(112471480, EnemyIris, "Iris_101");
	orderActorToFactory(112471510, EnemyIris, "Iris_102");
	orderActorToFactory(112471540, EnemyIris, "Iris_103");
	orderActorToFactory(112471570, EnemyIris, "Iris_104");
	orderActorToFactory(112471600, EnemyIris, "Iris_105");
	orderActorToFactory(112471630, EnemyIris, "Iris_106");
	orderActorToFactory(112471660, EnemyIris, "Iris_107");
	orderActorToFactory(112471690, EnemyIris, "Iris_108");
	orderActorToFactory(112471720, EnemyIris, "Iris_109");
	orderActorToFactory(112471750, EnemyIris, "Iris_110");
	orderActorToFactory(112471780, EnemyIris, "Iris_111");
	orderActorToFactory(112471810, EnemyIris, "Iris_112");
	orderActorToFactory(112471840, EnemyIris, "Iris_113");
	orderActorToFactory(112471870, EnemyIris, "Iris_114");
	orderActorToFactory(112471900, EnemyIris, "Iris_115");
	orderActorToFactory(112471930, EnemyIris, "Iris_116");
	orderActorToFactory(112471960, EnemyIris, "Iris_117");
	orderActorToFactory(112471990, EnemyIris, "Iris_118");
	orderActorWithDpToFactory(11277500, EnemyCeres, "Ceres_119", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112771500, EnemyCeres, "Ceres_120", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112772500, EnemyCeres, "Ceres_121", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11287530, EnemyCeres, "Ceres_122", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112871530, EnemyCeres, "Ceres_123", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112872530, EnemyCeres, "Ceres_124", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11297560, EnemyCeres, "Ceres_125", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112971560, EnemyCeres, "Ceres_126", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(112972560, EnemyCeres, "Ceres_127", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11307590, EnemyCeres, "Ceres_128", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113071590, EnemyCeres, "Ceres_129", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113072590, EnemyCeres, "Ceres_130", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11317620, EnemyCeres, "Ceres_131", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113171620, EnemyCeres, "Ceres_132", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113172620, EnemyCeres, "Ceres_133", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(11327650, EnemyCeres, "Ceres_134", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113271650, EnemyCeres, "Ceres_135", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
	orderActorWithDpToFactory(113272650, EnemyCeres, "Ceres_136", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
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
				orderActorToFactory(110573010, EnemyVesta, "Vesta_137");
				break;
			case 70:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105770));
				orderActorToFactory(110573070, EnemyVesta, "Vesta_138");
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057130));
				orderActorToFactory(110573130, EnemyVesta, "Vesta_139");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247130);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 160:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247160);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057190));
				orderActorToFactory(110573190, EnemyVesta, "Vesta_140");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247190);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 220:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247220);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057250));
				orderActorToFactory(110573250, EnemyVesta, "Vesta_141");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247250);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 280:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247280);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057310));
				orderActorToFactory(110573310, EnemyVesta, "Vesta_142");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247310);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 340:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247340);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057370));
				orderActorToFactory(110573370, EnemyVesta, "Vesta_143");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247370);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 400:
				orderActorToFactory(111773400, EnemyAstraea, "Astraea_144");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057430));
				orderActorToFactory(110573430, EnemyVesta, "Vesta_145");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247430);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 460:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247460);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057490));
				orderActorToFactory(110573490, EnemyVesta, "Vesta_146");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247490);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 500:
				orderActorToFactory(111673500, EnemyAstraea, "Astraea_147");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11277500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112773500, EnemyCeres, "Ceres_148", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 520:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247520);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11287530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112873530, EnemyCeres, "Ceres_149", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057550));
				orderActorToFactory(110573550, EnemyVesta, "Vesta_150");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247550);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11297560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112973560, EnemyCeres, "Ceres_151", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 580:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247580);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11307590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113073590, EnemyCeres, "Ceres_152", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057610));
				orderActorToFactory(110573610, EnemyVesta, "Vesta_153");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247610);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11317620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113173620, EnemyCeres, "Ceres_154", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 640:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247640);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11327650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113273650, EnemyCeres, "Ceres_155", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057670));
				orderActorToFactory(110573670, EnemyVesta, "Vesta_156");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247670);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 700:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057730));
				orderActorToFactory(110573730, EnemyVesta, "Vesta_157");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247730);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 760:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247760);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057790));
				orderActorToFactory(110573790, EnemyVesta, "Vesta_158");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247790);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 820:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247820);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057850));
				orderActorToFactory(110573850, EnemyVesta, "Vesta_159");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247850);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 880:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247880);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 900:
				orderActorToFactory(110973900, EnemyAstraea, "Astraea_160");
				break;
			case 910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057910));
				orderActorToFactory(110573910, EnemyVesta, "Vesta_161");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247910);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 940:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247940);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(11057970));
				orderActorToFactory(110573970, EnemyVesta, "Vesta_162");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(11247970);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1000:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571030));
				orderActorToFactory(110574030, EnemyVesta, "Vesta_163");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471030);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1060:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471060);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571090));
				orderActorToFactory(110574090, EnemyVesta, "Vesta_164");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471090);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1120:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471120);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571150));
				orderActorToFactory(110574150, EnemyVesta, "Vesta_165");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471150);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1180:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471180);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571210));
				orderActorToFactory(110574210, EnemyVesta, "Vesta_166");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471210);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1240:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471240);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571270));
				orderActorToFactory(110574270, EnemyVesta, "Vesta_167");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471270);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1300:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571330));
				orderActorToFactory(110574330, EnemyVesta, "Vesta_168");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471330);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1360:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471360);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571390));
				orderActorToFactory(110574390, EnemyVesta, "Vesta_169");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471390);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1400:
				orderActorToFactory(111774400, EnemyAstraea, "Astraea_170");
				break;
			case 1420:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471420);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571450));
				orderActorToFactory(110574450, EnemyVesta, "Vesta_171");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471450);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1480:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471480);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111671500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111674500, EnemyAstraea, "Astraea_172");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112771500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112774500, EnemyCeres, "Ceres_173", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571510));
				orderActorToFactory(110574510, EnemyVesta, "Vesta_174");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471510);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112871530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112874530, EnemyCeres, "Ceres_175", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1540:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471540);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112971560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112974560, EnemyCeres, "Ceres_176", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571570));
				orderActorToFactory(110574570, EnemyVesta, "Vesta_177");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471570);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113071590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113074590, EnemyCeres, "Ceres_178", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1600:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113171620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113174620, EnemyCeres, "Ceres_179", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571630));
				orderActorToFactory(110574630, EnemyVesta, "Vesta_180");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471630);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113271650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113274650, EnemyCeres, "Ceres_181", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 1660:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471660);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571690));
				orderActorToFactory(110574690, EnemyVesta, "Vesta_182");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471690);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1720:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471720);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571750));
				orderActorToFactory(110574750, EnemyVesta, "Vesta_183");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471750);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1780:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471780);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1800:
				orderActorToFactory(111074800, EnemyAstraea, "Astraea_184");
				break;
			case 1810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571810));
				orderActorToFactory(110574810, EnemyVesta, "Vesta_185");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471810);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1840:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471840);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571870));
				orderActorToFactory(110574870, EnemyVesta, "Vesta_186");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471870);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1900:
				orderActorToFactory(110974900, EnemyAstraea, "Astraea_187");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571930));
				orderActorToFactory(110574930, EnemyVesta, "Vesta_188");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471930);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1960:
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471960);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 1990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110571990));
				orderActorToFactory(110574990, EnemyVesta, "Vesta_189");
				{
				EnemyIris* pActor = (EnemyIris*)obtainActorFromFactory(112471990);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				}
				break;
			case 2050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572050));
				orderActorToFactory(110575050, EnemyVesta, "Vesta_190");
				break;
			case 2100:
				orderActorToFactory(110775100, EnemyAstraea, "Astraea_191");
				break;
			case 2110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572110));
				orderActorToFactory(110575110, EnemyVesta, "Vesta_192");
				break;
			case 2170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572170));
				orderActorToFactory(110575170, EnemyVesta, "Vesta_193");
				break;
			case 2230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572230));
				orderActorToFactory(110575230, EnemyVesta, "Vesta_194");
				break;
			case 2290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572290));
				orderActorToFactory(110575290, EnemyVesta, "Vesta_195");
				break;
			case 2300:
				orderActorToFactory(111875300, EnemyAstraea, "Astraea_196");
				break;
			case 2350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572350));
				orderActorToFactory(110575350, EnemyVesta, "Vesta_197");
				break;
			case 2400:
				orderActorToFactory(111775400, EnemyAstraea, "Astraea_198");
				break;
			case 2410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572410));
				orderActorToFactory(110575410, EnemyVesta, "Vesta_199");
				break;
			case 2470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572470));
				orderActorToFactory(110575470, EnemyVesta, "Vesta_200");
				break;
			case 2500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111672500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111675500, EnemyAstraea, "Astraea_201");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112772500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112775500, EnemyCeres, "Ceres_202", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572530));
				orderActorToFactory(110575530, EnemyVesta, "Vesta_203");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112872530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112875530, EnemyCeres, "Ceres_204", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112972560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112975560, EnemyCeres, "Ceres_205", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572590));
				orderActorToFactory(110575590, EnemyVesta, "Vesta_206");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113072590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113075590, EnemyCeres, "Ceres_207", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113172620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113175620, EnemyCeres, "Ceres_208", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572650));
				orderActorToFactory(110575650, EnemyVesta, "Vesta_209");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113272650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113275650, EnemyCeres, "Ceres_210", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 2710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572710));
				orderActorToFactory(110575710, EnemyVesta, "Vesta_211");
				break;
			case 2770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572770));
				orderActorToFactory(110575770, EnemyVesta, "Vesta_212");
				break;
			case 2800:
				orderActorToFactory(111075800, EnemyAstraea, "Astraea_213");
				break;
			case 2830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572830));
				orderActorToFactory(110575830, EnemyVesta, "Vesta_214");
				break;
			case 2890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572890));
				orderActorToFactory(110575890, EnemyVesta, "Vesta_215");
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110972900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(110975900, EnemyAstraea, "Astraea_216");
				break;
			case 2950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110572950));
				orderActorToFactory(110575950, EnemyVesta, "Vesta_217");
				break;
			case 3010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573010));
				orderActorToFactory(110576010, EnemyVesta, "Vesta_218");
				break;
			case 3070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573070));
				orderActorToFactory(110576070, EnemyVesta, "Vesta_219");
				break;
			case 3130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573130));
				orderActorToFactory(110576130, EnemyVesta, "Vesta_220");
				break;
			case 3190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573190));
				orderActorToFactory(110576190, EnemyVesta, "Vesta_221");
				break;
			case 3250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573250));
				orderActorToFactory(110576250, EnemyVesta, "Vesta_222");
				break;
			case 3300:
				orderActorToFactory(111876300, EnemyAstraea, "Astraea_223");
				break;
			case 3310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573310));
				orderActorToFactory(110576310, EnemyVesta, "Vesta_224");
				break;
			case 3370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573370));
				orderActorToFactory(110576370, EnemyVesta, "Vesta_225");
				break;
			case 3400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111773400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(111776400, EnemyAstraea, "Astraea_226");
				break;
			case 3430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573430));
				orderActorToFactory(110576430, EnemyVesta, "Vesta_227");
				break;
			case 3490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573490));
				orderActorToFactory(110576490, EnemyVesta, "Vesta_228");
				break;
			case 3500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111673500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111676500, EnemyAstraea, "Astraea_229");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112773500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112776500, EnemyCeres, "Ceres_230", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112873530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112876530, EnemyCeres, "Ceres_231", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573550));
				orderActorToFactory(110576550, EnemyVesta, "Vesta_232");
				break;
			case 3560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112973560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112976560, EnemyCeres, "Ceres_233", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113073590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113076590, EnemyCeres, "Ceres_234", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573610));
				orderActorToFactory(110576610, EnemyVesta, "Vesta_235");
				break;
			case 3620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113173620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113176620, EnemyCeres, "Ceres_236", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113273650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113276650, EnemyCeres, "Ceres_237", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 3670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573670));
				orderActorToFactory(110576670, EnemyVesta, "Vesta_238");
				break;
			case 3700:
				orderActorToFactory(111176700, EnemyAstraea, "Astraea_239");
				break;
			case 3730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573730));
				orderActorToFactory(110576730, EnemyVesta, "Vesta_240");
				break;
			case 3790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573790));
				orderActorToFactory(110576790, EnemyVesta, "Vesta_241");
				break;
			case 3800:
				orderActorToFactory(111076800, EnemyAstraea, "Astraea_242");
				break;
			case 3850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573850));
				orderActorToFactory(110576850, EnemyVesta, "Vesta_243");
				break;
			case 3900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110973900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(110976900, EnemyAstraea, "Astraea_244");
				break;
			case 3910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573910));
				orderActorToFactory(110576910, EnemyVesta, "Vesta_245");
				break;
			case 3970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110573970));
				orderActorToFactory(110576970, EnemyVesta, "Vesta_246");
				break;
			case 4030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574030));
				orderActorToFactory(110577030, EnemyVesta, "Vesta_247");
				break;
			case 4090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574090));
				orderActorToFactory(110577090, EnemyVesta, "Vesta_248");
				break;
			case 4150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574150));
				orderActorToFactory(110577150, EnemyVesta, "Vesta_249");
				break;
			case 4200:
				orderActorToFactory(111977200, EnemyAstraea, "Astraea_250");
				break;
			case 4210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574210));
				orderActorToFactory(110577210, EnemyVesta, "Vesta_251");
				break;
			case 4270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574270));
				orderActorToFactory(110577270, EnemyVesta, "Vesta_252");
				break;
			case 4300:
				orderActorToFactory(111877300, EnemyAstraea, "Astraea_253");
				break;
			case 4330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574330));
				orderActorToFactory(110577330, EnemyVesta, "Vesta_254");
				break;
			case 4390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574390));
				orderActorToFactory(110577390, EnemyVesta, "Vesta_255");
				break;
			case 4400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111774400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(111777400, EnemyAstraea, "Astraea_256");
				break;
			case 4450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574450));
				orderActorToFactory(110577450, EnemyVesta, "Vesta_257");
				break;
			case 4500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111674500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111677500, EnemyAstraea, "Astraea_258");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112774500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112777500, EnemyCeres, "Ceres_259", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574510));
				orderActorToFactory(110577510, EnemyVesta, "Vesta_260");
				break;
			case 4530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112874530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112877530, EnemyCeres, "Ceres_261", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112974560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112977560, EnemyCeres, "Ceres_262", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574570));
				orderActorToFactory(110577570, EnemyVesta, "Vesta_263");
				break;
			case 4590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113074590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113077590, EnemyCeres, "Ceres_264", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113174620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113177620, EnemyCeres, "Ceres_265", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574630));
				orderActorToFactory(110577630, EnemyVesta, "Vesta_266");
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113274650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113277650, EnemyCeres, "Ceres_267", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 4690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574690));
				orderActorToFactory(110577690, EnemyVesta, "Vesta_268");
				break;
			case 4700:
				orderActorToFactory(111177700, EnemyAstraea, "Astraea_269");
				break;
			case 4750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574750));
				orderActorToFactory(110577750, EnemyVesta, "Vesta_270");
				break;
			case 4800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111074800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(111077800, EnemyAstraea, "Astraea_271");
				break;
			case 4810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574810));
				orderActorToFactory(110577810, EnemyVesta, "Vesta_272");
				break;
			case 4870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574870));
				orderActorToFactory(110577870, EnemyVesta, "Vesta_273");
				break;
			case 4900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110974900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(110977900, EnemyAstraea, "Astraea_274");
				break;
			case 4930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574930));
				orderActorToFactory(110577930, EnemyVesta, "Vesta_275");
				break;
			case 4990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110574990));
				orderActorToFactory(110577990, EnemyVesta, "Vesta_276");
				break;
			case 5050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575050));
				orderActorToFactory(110578050, EnemyVesta, "Vesta_277");
				break;
			case 5100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110775100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 5110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575110));
				orderActorToFactory(110578110, EnemyVesta, "Vesta_278");
				break;
			case 5170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575170));
				orderActorToFactory(110578170, EnemyVesta, "Vesta_279");
				break;
			case 5200:
				orderActorToFactory(111978200, EnemyAstraea, "Astraea_280");
				break;
			case 5230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575230));
				orderActorToFactory(110578230, EnemyVesta, "Vesta_281");
				break;
			case 5290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575290));
				orderActorToFactory(110578290, EnemyVesta, "Vesta_282");
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111875300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(111878300, EnemyAstraea, "Astraea_283");
				break;
			case 5350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575350));
				orderActorToFactory(110578350, EnemyVesta, "Vesta_284");
				break;
			case 5400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111775400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(111778400, EnemyAstraea, "Astraea_285");
				break;
			case 5410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575410));
				orderActorToFactory(110578410, EnemyVesta, "Vesta_286");
				break;
			case 5470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575470));
				orderActorToFactory(110578470, EnemyVesta, "Vesta_287");
				break;
			case 5500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111675500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111678500, EnemyAstraea, "Astraea_288");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112775500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112778500, EnemyCeres, "Ceres_289", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575530));
				orderActorToFactory(110578530, EnemyVesta, "Vesta_290");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112875530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112878530, EnemyCeres, "Ceres_291", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112975560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112978560, EnemyCeres, "Ceres_292", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575590));
				orderActorToFactory(110578590, EnemyVesta, "Vesta_293");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113075590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113078590, EnemyCeres, "Ceres_294", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5600:
				orderActorToFactory(111278600, EnemyAstraea, "Astraea_295");
				break;
			case 5620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113175620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113178620, EnemyCeres, "Ceres_296", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575650));
				orderActorToFactory(110578650, EnemyVesta, "Vesta_297");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113275650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113278650, EnemyCeres, "Ceres_298", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 5700:
				orderActorToFactory(111178700, EnemyAstraea, "Astraea_299");
				break;
			case 5710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575710));
				orderActorToFactory(110578710, EnemyVesta, "Vesta_300");
				break;
			case 5770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575770));
				orderActorToFactory(110578770, EnemyVesta, "Vesta_301");
				break;
			case 5800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111075800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(111078800, EnemyAstraea, "Astraea_302");
				break;
			case 5830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575830));
				orderActorToFactory(110578830, EnemyVesta, "Vesta_303");
				break;
			case 5890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575890));
				orderActorToFactory(110578890, EnemyVesta, "Vesta_304");
				break;
			case 5900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110975900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(110978900, EnemyAstraea, "Astraea_305");
				break;
			case 5950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110575950));
				orderActorToFactory(110578950, EnemyVesta, "Vesta_306");
				break;
			case 6010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576010));
				orderActorToFactory(110579010, EnemyVesta, "Vesta_307");
				break;
			case 6070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576070));
				orderActorToFactory(110579070, EnemyVesta, "Vesta_308");
				break;
			case 6100:
				orderActorToFactory(112079100, EnemyAstraea, "Astraea_309");
				break;
			case 6130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576130));
				orderActorToFactory(110579130, EnemyVesta, "Vesta_310");
				break;
			case 6190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576190));
				orderActorToFactory(110579190, EnemyVesta, "Vesta_311");
				break;
			case 6200:
				orderActorToFactory(111979200, EnemyAstraea, "Astraea_312");
				break;
			case 6250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576250));
				orderActorToFactory(110579250, EnemyVesta, "Vesta_313");
				break;
			case 6300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111876300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(111879300, EnemyAstraea, "Astraea_314");
				break;
			case 6310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576310));
				orderActorToFactory(110579310, EnemyVesta, "Vesta_315");
				break;
			case 6370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576370));
				orderActorToFactory(110579370, EnemyVesta, "Vesta_316");
				break;
			case 6400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111776400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(111779400, EnemyAstraea, "Astraea_317");
				break;
			case 6430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576430));
				orderActorToFactory(110579430, EnemyVesta, "Vesta_318");
				break;
			case 6490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576490));
				orderActorToFactory(110579490, EnemyVesta, "Vesta_319");
				break;
			case 6500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111676500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(111679500, EnemyAstraea, "Astraea_320");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112776500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112779500, EnemyCeres, "Ceres_321", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112876530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112879530, EnemyCeres, "Ceres_322", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576550));
				orderActorToFactory(110579550, EnemyVesta, "Vesta_323");
				break;
			case 6560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112976560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(112979560, EnemyCeres, "Ceres_324", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113076590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113079590, EnemyCeres, "Ceres_325", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6600:
				orderActorToFactory(111279600, EnemyAstraea, "Astraea_326");
				break;
			case 6610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576610));
				orderActorToFactory(110579610, EnemyVesta, "Vesta_327");
				break;
			case 6620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113176620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113179620, EnemyCeres, "Ceres_328", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113276650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(113279650, EnemyCeres, "Ceres_329", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 6670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576670));
				orderActorToFactory(110579670, EnemyVesta, "Vesta_330");
				break;
			case 6700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111176700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(111179700, EnemyAstraea, "Astraea_331");
				break;
			case 6730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576730));
				orderActorToFactory(110579730, EnemyVesta, "Vesta_332");
				break;
			case 6790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576790));
				orderActorToFactory(110579790, EnemyVesta, "Vesta_333");
				break;
			case 6800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111076800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(111079800, EnemyAstraea, "Astraea_334");
				break;
			case 6850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576850));
				orderActorToFactory(110579850, EnemyVesta, "Vesta_335");
				break;
			case 6900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110976900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(110979900, EnemyAstraea, "Astraea_336");
				break;
			case 6910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576910));
				orderActorToFactory(110579910, EnemyVesta, "Vesta_337");
				break;
			case 6970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110576970));
				orderActorToFactory(110579970, EnemyVesta, "Vesta_338");
				break;
			case 7030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577030));
				orderActorToFactory(1105710030, EnemyVesta, "Vesta_339");
				break;
			case 7090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577090));
				orderActorToFactory(1105710090, EnemyVesta, "Vesta_340");
				break;
			case 7100:
				orderActorToFactory(1107710100, EnemyAstraea, "Astraea_341");
				orderActorToFactory(1120710100, EnemyAstraea, "Astraea_342");
				break;
			case 7150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577150));
				orderActorToFactory(1105710150, EnemyVesta, "Vesta_343");
				break;
			case 7200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111977200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119710200, EnemyAstraea, "Astraea_344");
				break;
			case 7210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577210));
				orderActorToFactory(1105710210, EnemyVesta, "Vesta_345");
				break;
			case 7270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577270));
				orderActorToFactory(1105710270, EnemyVesta, "Vesta_346");
				break;
			case 7300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111877300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118710300, EnemyAstraea, "Astraea_347");
				break;
			case 7330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577330));
				orderActorToFactory(1105710330, EnemyVesta, "Vesta_348");
				break;
			case 7390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577390));
				orderActorToFactory(1105710390, EnemyVesta, "Vesta_349");
				break;
			case 7400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111777400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117710400, EnemyAstraea, "Astraea_350");
				break;
			case 7450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577450));
				orderActorToFactory(1105710450, EnemyVesta, "Vesta_351");
				break;
			case 7500:
				orderActorToFactory(1113710500, EnemyAstraea, "Astraea_352");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111677500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116710500, EnemyAstraea, "Astraea_353");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112777500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127710500, EnemyCeres, "Ceres_354", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577510));
				orderActorToFactory(1105710510, EnemyVesta, "Vesta_355");
				break;
			case 7530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112877530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128710530, EnemyCeres, "Ceres_356", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112977560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129710560, EnemyCeres, "Ceres_357", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577570));
				orderActorToFactory(1105710570, EnemyVesta, "Vesta_358");
				break;
			case 7590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113077590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130710590, EnemyCeres, "Ceres_359", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7600:
				orderActorToFactory(1112710600, EnemyAstraea, "Astraea_360");
				break;
			case 7620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113177620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131710620, EnemyCeres, "Ceres_361", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577630));
				orderActorToFactory(1105710630, EnemyVesta, "Vesta_362");
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113277650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132710650, EnemyCeres, "Ceres_363", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 7690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577690));
				orderActorToFactory(1105710690, EnemyVesta, "Vesta_364");
				break;
			case 7700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111177700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111710700, EnemyAstraea, "Astraea_365");
				break;
			case 7750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577750));
				orderActorToFactory(1105710750, EnemyVesta, "Vesta_366");
				break;
			case 7800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111077800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110710800, EnemyAstraea, "Astraea_367");
				break;
			case 7810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577810));
				orderActorToFactory(1105710810, EnemyVesta, "Vesta_368");
				break;
			case 7870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577870));
				orderActorToFactory(1105710870, EnemyVesta, "Vesta_369");
				break;
			case 7900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110977900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109710900, EnemyAstraea, "Astraea_370");
				break;
			case 7930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577930));
				orderActorToFactory(1105710930, EnemyVesta, "Vesta_371");
				break;
			case 7990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110577990));
				orderActorToFactory(1105710990, EnemyVesta, "Vesta_372");
				break;
			case 8000:
				orderActorToFactory(1121711000, EnemyAstraea, "Astraea_373");
				break;
			case 8050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578050));
				orderActorToFactory(1105711050, EnemyVesta, "Vesta_374");
				break;
			case 8100:
				orderActorToFactory(1120711100, EnemyAstraea, "Astraea_375");
				break;
			case 8110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578110));
				orderActorToFactory(1105711110, EnemyVesta, "Vesta_376");
				break;
			case 8170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578170));
				orderActorToFactory(1105711170, EnemyVesta, "Vesta_377");
				break;
			case 8200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111978200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119711200, EnemyAstraea, "Astraea_378");
				break;
			case 8230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578230));
				orderActorToFactory(1105711230, EnemyVesta, "Vesta_379");
				break;
			case 8290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578290));
				orderActorToFactory(1105711290, EnemyVesta, "Vesta_380");
				break;
			case 8300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111878300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118711300, EnemyAstraea, "Astraea_381");
				break;
			case 8350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578350));
				orderActorToFactory(1105711350, EnemyVesta, "Vesta_382");
				break;
			case 8400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111778400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117711400, EnemyAstraea, "Astraea_383");
				break;
			case 8410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578410));
				orderActorToFactory(1105711410, EnemyVesta, "Vesta_384");
				break;
			case 8470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578470));
				orderActorToFactory(1105711470, EnemyVesta, "Vesta_385");
				break;
			case 8500:
				orderActorToFactory(1113711500, EnemyAstraea, "Astraea_386");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111678500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116711500, EnemyAstraea, "Astraea_387");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112778500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127711500, EnemyCeres, "Ceres_388", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578530));
				orderActorToFactory(1105711530, EnemyVesta, "Vesta_389");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112878530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128711530, EnemyCeres, "Ceres_390", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112978560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129711560, EnemyCeres, "Ceres_391", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578590));
				orderActorToFactory(1105711590, EnemyVesta, "Vesta_392");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113078590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130711590, EnemyCeres, "Ceres_393", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111278600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112711600, EnemyAstraea, "Astraea_394");
				break;
			case 8620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113178620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131711620, EnemyCeres, "Ceres_395", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578650));
				orderActorToFactory(1105711650, EnemyVesta, "Vesta_396");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113278650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132711650, EnemyCeres, "Ceres_397", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 8700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111178700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111711700, EnemyAstraea, "Astraea_398");
				break;
			case 8710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578710));
				orderActorToFactory(1105711710, EnemyVesta, "Vesta_399");
				break;
			case 8770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578770));
				orderActorToFactory(1105711770, EnemyVesta, "Vesta_400");
				break;
			case 8800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111078800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110711800, EnemyAstraea, "Astraea_401");
				break;
			case 8830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578830));
				orderActorToFactory(1105711830, EnemyVesta, "Vesta_402");
				break;
			case 8890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578890));
				orderActorToFactory(1105711890, EnemyVesta, "Vesta_403");
				break;
			case 8900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110978900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109711900, EnemyAstraea, "Astraea_404");
				break;
			case 8950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110578950));
				orderActorToFactory(1105711950, EnemyVesta, "Vesta_405");
				break;
			case 9000:
				orderActorToFactory(1121712000, EnemyAstraea, "Astraea_406");
				break;
			case 9010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579010));
				orderActorToFactory(1105712010, EnemyVesta, "Vesta_407");
				break;
			case 9070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579070));
				orderActorToFactory(1105712070, EnemyVesta, "Vesta_408");
				break;
			case 9100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112079100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120712100, EnemyAstraea, "Astraea_409");
				break;
			case 9130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579130));
				orderActorToFactory(1105712130, EnemyVesta, "Vesta_410");
				break;
			case 9190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579190));
				orderActorToFactory(1105712190, EnemyVesta, "Vesta_411");
				break;
			case 9200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111979200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119712200, EnemyAstraea, "Astraea_412");
				break;
			case 9250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579250));
				orderActorToFactory(1105712250, EnemyVesta, "Vesta_413");
				break;
			case 9300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111879300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118712300, EnemyAstraea, "Astraea_414");
				break;
			case 9310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579310));
				orderActorToFactory(1105712310, EnemyVesta, "Vesta_415");
				break;
			case 9370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579370));
				orderActorToFactory(1105712370, EnemyVesta, "Vesta_416");
				break;
			case 9400:
				orderActorToFactory(1114712400, EnemyAstraea, "Astraea_417");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111779400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117712400, EnemyAstraea, "Astraea_418");
				break;
			case 9430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579430));
				orderActorToFactory(1105712430, EnemyVesta, "Vesta_419");
				break;
			case 9490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579490));
				orderActorToFactory(1105712490, EnemyVesta, "Vesta_420");
				break;
			case 9500:
				orderActorToFactory(1113712500, EnemyAstraea, "Astraea_421");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111679500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116712500, EnemyAstraea, "Astraea_422");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112779500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127712500, EnemyCeres, "Ceres_423", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112879530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128712530, EnemyCeres, "Ceres_424", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579550));
				orderActorToFactory(1105712550, EnemyVesta, "Vesta_425");
				break;
			case 9560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(112979560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129712560, EnemyCeres, "Ceres_426", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113079590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130712590, EnemyCeres, "Ceres_427", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111279600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112712600, EnemyAstraea, "Astraea_428");
				break;
			case 9610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579610));
				orderActorToFactory(1105712610, EnemyVesta, "Vesta_429");
				break;
			case 9620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113179620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131712620, EnemyCeres, "Ceres_430", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113279650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132712650, EnemyCeres, "Ceres_431", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 9670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579670));
				orderActorToFactory(1105712670, EnemyVesta, "Vesta_432");
				break;
			case 9700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111179700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111712700, EnemyAstraea, "Astraea_433");
				break;
			case 9730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579730));
				orderActorToFactory(1105712730, EnemyVesta, "Vesta_434");
				break;
			case 9790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579790));
				orderActorToFactory(1105712790, EnemyVesta, "Vesta_435");
				break;
			case 9800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111079800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110712800, EnemyAstraea, "Astraea_436");
				break;
			case 9850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579850));
				orderActorToFactory(1105712850, EnemyVesta, "Vesta_437");
				break;
			case 9900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(110979900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109712900, EnemyAstraea, "Astraea_438");
				break;
			case 9910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579910));
				orderActorToFactory(1105712910, EnemyVesta, "Vesta_439");
				break;
			case 9970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(110579970));
				orderActorToFactory(1105712970, EnemyVesta, "Vesta_440");
				break;
			case 10000:
				orderActorToFactory(1121713000, EnemyAstraea, "Astraea_441");
				break;
			case 10030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710030));
				orderActorToFactory(1105713030, EnemyVesta, "Vesta_442");
				break;
			case 10090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710090));
				orderActorToFactory(1105713090, EnemyVesta, "Vesta_443");
				break;
			case 10100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107710100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120710100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120713100, EnemyAstraea, "Astraea_444");
				break;
			case 10150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710150));
				orderActorToFactory(1105713150, EnemyVesta, "Vesta_445");
				break;
			case 10200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119710200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119713200, EnemyAstraea, "Astraea_446");
				break;
			case 10210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710210));
				orderActorToFactory(1105713210, EnemyVesta, "Vesta_447");
				break;
			case 10270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710270));
				orderActorToFactory(1105713270, EnemyVesta, "Vesta_448");
				break;
			case 10300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118710300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118713300, EnemyAstraea, "Astraea_449");
				break;
			case 10330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710330));
				orderActorToFactory(1105713330, EnemyVesta, "Vesta_450");
				break;
			case 10390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710390));
				orderActorToFactory(1105713390, EnemyVesta, "Vesta_451");
				break;
			case 10400:
				orderActorToFactory(1114713400, EnemyAstraea, "Astraea_452");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117710400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117713400, EnemyAstraea, "Astraea_453");
				break;
			case 10450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710450));
				orderActorToFactory(1105713450, EnemyVesta, "Vesta_454");
				break;
			case 10500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113710500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113713500, EnemyAstraea, "Astraea_455");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116710500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116713500, EnemyAstraea, "Astraea_456");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127710500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127713500, EnemyCeres, "Ceres_457", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710510));
				orderActorToFactory(1105713510, EnemyVesta, "Vesta_458");
				break;
			case 10530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128710530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128713530, EnemyCeres, "Ceres_459", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129710560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129713560, EnemyCeres, "Ceres_460", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710570));
				orderActorToFactory(1105713570, EnemyVesta, "Vesta_461");
				break;
			case 10590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130710590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130713590, EnemyCeres, "Ceres_462", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112710600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112713600, EnemyAstraea, "Astraea_463");
				break;
			case 10620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131710620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131713620, EnemyCeres, "Ceres_464", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710630));
				orderActorToFactory(1105713630, EnemyVesta, "Vesta_465");
				break;
			case 10650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132710650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132713650, EnemyCeres, "Ceres_466", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 10690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710690));
				orderActorToFactory(1105713690, EnemyVesta, "Vesta_467");
				break;
			case 10700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111710700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111713700, EnemyAstraea, "Astraea_468");
				break;
			case 10750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710750));
				orderActorToFactory(1105713750, EnemyVesta, "Vesta_469");
				break;
			case 10800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110710800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110713800, EnemyAstraea, "Astraea_470");
				break;
			case 10810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710810));
				orderActorToFactory(1105713810, EnemyVesta, "Vesta_471");
				break;
			case 10870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710870));
				orderActorToFactory(1105713870, EnemyVesta, "Vesta_472");
				break;
			case 10900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109710900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109713900, EnemyAstraea, "Astraea_473");
				break;
			case 10930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710930));
				orderActorToFactory(1105713930, EnemyVesta, "Vesta_474");
				break;
			case 10990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105710990));
				orderActorToFactory(1105713990, EnemyVesta, "Vesta_475");
				break;
			case 11000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121711000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121714000, EnemyAstraea, "Astraea_476");
				break;
			case 11050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711050));
				orderActorToFactory(1105714050, EnemyVesta, "Vesta_477");
				break;
			case 11100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120711100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120714100, EnemyAstraea, "Astraea_478");
				break;
			case 11110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711110));
				orderActorToFactory(1105714110, EnemyVesta, "Vesta_479");
				break;
			case 11170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711170));
				orderActorToFactory(1105714170, EnemyVesta, "Vesta_480");
				break;
			case 11200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119711200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119714200, EnemyAstraea, "Astraea_481");
				break;
			case 11230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711230));
				orderActorToFactory(1105714230, EnemyVesta, "Vesta_482");
				break;
			case 11290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711290));
				orderActorToFactory(1105714290, EnemyVesta, "Vesta_483");
				break;
			case 11300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118711300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118714300, EnemyAstraea, "Astraea_484");
				break;
			case 11350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711350));
				orderActorToFactory(1105714350, EnemyVesta, "Vesta_485");
				break;
			case 11400:
				orderActorToFactory(1114714400, EnemyAstraea, "Astraea_486");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117711400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117714400, EnemyAstraea, "Astraea_487");
				break;
			case 11410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711410));
				orderActorToFactory(1105714410, EnemyVesta, "Vesta_488");
				break;
			case 11470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711470));
				orderActorToFactory(1105714470, EnemyVesta, "Vesta_489");
				break;
			case 11500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113711500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113714500, EnemyAstraea, "Astraea_490");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116711500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116714500, EnemyAstraea, "Astraea_491");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127711500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127714500, EnemyCeres, "Ceres_492", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711530));
				orderActorToFactory(1105714530, EnemyVesta, "Vesta_493");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128711530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128714530, EnemyCeres, "Ceres_494", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129711560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129714560, EnemyCeres, "Ceres_495", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711590));
				orderActorToFactory(1105714590, EnemyVesta, "Vesta_496");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130711590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130714590, EnemyCeres, "Ceres_497", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112711600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112714600, EnemyAstraea, "Astraea_498");
				break;
			case 11620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131711620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131714620, EnemyCeres, "Ceres_499", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711650));
				orderActorToFactory(1105714650, EnemyVesta, "Vesta_500");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132711650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132714650, EnemyCeres, "Ceres_501", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 11700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111711700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111714700, EnemyAstraea, "Astraea_502");
				break;
			case 11710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711710));
				orderActorToFactory(1105714710, EnemyVesta, "Vesta_503");
				break;
			case 11770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711770));
				orderActorToFactory(1105714770, EnemyVesta, "Vesta_504");
				break;
			case 11800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110711800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110714800, EnemyAstraea, "Astraea_505");
				break;
			case 11830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711830));
				orderActorToFactory(1105714830, EnemyVesta, "Vesta_506");
				break;
			case 11890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711890));
				orderActorToFactory(1105714890, EnemyVesta, "Vesta_507");
				break;
			case 11900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109711900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109714900, EnemyAstraea, "Astraea_508");
				break;
			case 11950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105711950));
				orderActorToFactory(1105714950, EnemyVesta, "Vesta_509");
				break;
			case 12000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121712000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121715000, EnemyAstraea, "Astraea_510");
				break;
			case 12010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712010));
				orderActorToFactory(1105715010, EnemyVesta, "Vesta_511");
				break;
			case 12070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712070));
				orderActorToFactory(1105715070, EnemyVesta, "Vesta_512");
				break;
			case 12100:
				orderActorToFactory(1107715100, EnemyAstraea, "Astraea_513");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120712100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120715100, EnemyAstraea, "Astraea_514");
				break;
			case 12130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712130));
				orderActorToFactory(1105715130, EnemyVesta, "Vesta_515");
				break;
			case 12190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712190));
				orderActorToFactory(1105715190, EnemyVesta, "Vesta_516");
				break;
			case 12200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119712200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119715200, EnemyAstraea, "Astraea_517");
				break;
			case 12250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712250));
				orderActorToFactory(1105715250, EnemyVesta, "Vesta_518");
				break;
			case 12300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118712300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118715300, EnemyAstraea, "Astraea_519");
				break;
			case 12310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712310));
				orderActorToFactory(1105715310, EnemyVesta, "Vesta_520");
				break;
			case 12370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712370));
				orderActorToFactory(1105715370, EnemyVesta, "Vesta_521");
				break;
			case 12400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114712400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				orderActorToFactory(1114715400, EnemyAstraea, "Astraea_522");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117712400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117715400, EnemyAstraea, "Astraea_523");
				break;
			case 12430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712430));
				orderActorToFactory(1105715430, EnemyVesta, "Vesta_524");
				break;
			case 12490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712490));
				orderActorToFactory(1105715490, EnemyVesta, "Vesta_525");
				break;
			case 12500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113712500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113715500, EnemyAstraea, "Astraea_526");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116712500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116715500, EnemyAstraea, "Astraea_527");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127712500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127715500, EnemyCeres, "Ceres_528", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128712530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128715530, EnemyCeres, "Ceres_529", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712550));
				orderActorToFactory(1105715550, EnemyVesta, "Vesta_530");
				break;
			case 12560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129712560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129715560, EnemyCeres, "Ceres_531", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130712590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130715590, EnemyCeres, "Ceres_532", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112712600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112715600, EnemyAstraea, "Astraea_533");
				break;
			case 12610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712610));
				orderActorToFactory(1105715610, EnemyVesta, "Vesta_534");
				break;
			case 12620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131712620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131715620, EnemyCeres, "Ceres_535", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132712650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132715650, EnemyCeres, "Ceres_536", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 12670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712670));
				orderActorToFactory(1105715670, EnemyVesta, "Vesta_537");
				break;
			case 12700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111712700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111715700, EnemyAstraea, "Astraea_538");
				break;
			case 12730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712730));
				orderActorToFactory(1105715730, EnemyVesta, "Vesta_539");
				break;
			case 12790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712790));
				orderActorToFactory(1105715790, EnemyVesta, "Vesta_540");
				break;
			case 12800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110712800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110715800, EnemyAstraea, "Astraea_541");
				break;
			case 12850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712850));
				orderActorToFactory(1105715850, EnemyVesta, "Vesta_542");
				break;
			case 12900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109712900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109715900, EnemyAstraea, "Astraea_543");
				break;
			case 12910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712910));
				orderActorToFactory(1105715910, EnemyVesta, "Vesta_544");
				break;
			case 12970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105712970));
				orderActorToFactory(1105715970, EnemyVesta, "Vesta_545");
				break;
			case 13000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121713000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121716000, EnemyAstraea, "Astraea_546");
				break;
			case 13030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713030));
				orderActorToFactory(1105716030, EnemyVesta, "Vesta_547");
				break;
			case 13090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713090));
				orderActorToFactory(1105716090, EnemyVesta, "Vesta_548");
				break;
			case 13100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120713100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120716100, EnemyAstraea, "Astraea_549");
				break;
			case 13150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713150));
				orderActorToFactory(1105716150, EnemyVesta, "Vesta_550");
				break;
			case 13200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119713200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119716200, EnemyAstraea, "Astraea_551");
				break;
			case 13210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713210));
				orderActorToFactory(1105716210, EnemyVesta, "Vesta_552");
				break;
			case 13270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713270));
				orderActorToFactory(1105716270, EnemyVesta, "Vesta_553");
				break;
			case 13300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118713300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118716300, EnemyAstraea, "Astraea_554");
				break;
			case 13330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713330));
				orderActorToFactory(1105716330, EnemyVesta, "Vesta_555");
				break;
			case 13390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713390));
				orderActorToFactory(1105716390, EnemyVesta, "Vesta_556");
				break;
			case 13400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114713400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				orderActorToFactory(1114716400, EnemyAstraea, "Astraea_557");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117713400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117716400, EnemyAstraea, "Astraea_558");
				break;
			case 13450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713450));
				orderActorToFactory(1105716450, EnemyVesta, "Vesta_559");
				break;
			case 13500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113713500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113716500, EnemyAstraea, "Astraea_560");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116713500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116716500, EnemyAstraea, "Astraea_561");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127713500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127716500, EnemyCeres, "Ceres_562", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713510));
				orderActorToFactory(1105716510, EnemyVesta, "Vesta_563");
				break;
			case 13530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128713530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128716530, EnemyCeres, "Ceres_564", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129713560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129716560, EnemyCeres, "Ceres_565", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713570));
				orderActorToFactory(1105716570, EnemyVesta, "Vesta_566");
				break;
			case 13590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130713590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130716590, EnemyCeres, "Ceres_567", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112713600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112716600, EnemyAstraea, "Astraea_568");
				break;
			case 13620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131713620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131716620, EnemyCeres, "Ceres_569", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713630));
				orderActorToFactory(1105716630, EnemyVesta, "Vesta_570");
				break;
			case 13650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132713650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132716650, EnemyCeres, "Ceres_571", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 13690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713690));
				orderActorToFactory(1105716690, EnemyVesta, "Vesta_572");
				break;
			case 13700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111713700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111716700, EnemyAstraea, "Astraea_573");
				break;
			case 13750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713750));
				orderActorToFactory(1105716750, EnemyVesta, "Vesta_574");
				break;
			case 13800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110713800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110716800, EnemyAstraea, "Astraea_575");
				break;
			case 13810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713810));
				orderActorToFactory(1105716810, EnemyVesta, "Vesta_576");
				break;
			case 13870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713870));
				orderActorToFactory(1105716870, EnemyVesta, "Vesta_577");
				break;
			case 13900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109713900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109716900, EnemyAstraea, "Astraea_578");
				break;
			case 13930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713930));
				orderActorToFactory(1105716930, EnemyVesta, "Vesta_579");
				break;
			case 13990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105713990));
				orderActorToFactory(1105716990, EnemyVesta, "Vesta_580");
				break;
			case 14000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121714000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121717000, EnemyAstraea, "Astraea_581");
				break;
			case 14050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714050));
				orderActorToFactory(1105717050, EnemyVesta, "Vesta_582");
				break;
			case 14100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120714100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120717100, EnemyAstraea, "Astraea_583");
				break;
			case 14110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714110));
				orderActorToFactory(1105717110, EnemyVesta, "Vesta_584");
				break;
			case 14170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714170));
				orderActorToFactory(1105717170, EnemyVesta, "Vesta_585");
				break;
			case 14200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119714200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119717200, EnemyAstraea, "Astraea_586");
				break;
			case 14230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714230));
				orderActorToFactory(1105717230, EnemyVesta, "Vesta_587");
				break;
			case 14290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714290));
				orderActorToFactory(1105717290, EnemyVesta, "Vesta_588");
				break;
			case 14300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118714300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118717300, EnemyAstraea, "Astraea_589");
				break;
			case 14350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714350));
				orderActorToFactory(1105717350, EnemyVesta, "Vesta_590");
				break;
			case 14400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114714400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				orderActorToFactory(1114717400, EnemyAstraea, "Astraea_591");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117714400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117717400, EnemyAstraea, "Astraea_592");
				break;
			case 14410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714410));
				orderActorToFactory(1105717410, EnemyVesta, "Vesta_593");
				break;
			case 14470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714470));
				orderActorToFactory(1105717470, EnemyVesta, "Vesta_594");
				break;
			case 14500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113714500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113717500, EnemyAstraea, "Astraea_595");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116714500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116717500, EnemyAstraea, "Astraea_596");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127714500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127717500, EnemyCeres, "Ceres_597", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714530));
				orderActorToFactory(1105717530, EnemyVesta, "Vesta_598");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128714530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128717530, EnemyCeres, "Ceres_599", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129714560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129717560, EnemyCeres, "Ceres_600", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714590));
				orderActorToFactory(1105717590, EnemyVesta, "Vesta_601");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130714590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130717590, EnemyCeres, "Ceres_602", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112714600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112717600, EnemyAstraea, "Astraea_603");
				break;
			case 14620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131714620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131717620, EnemyCeres, "Ceres_604", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714650));
				orderActorToFactory(1105717650, EnemyVesta, "Vesta_605");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132714650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132717650, EnemyCeres, "Ceres_606", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 14700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111714700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111717700, EnemyAstraea, "Astraea_607");
				break;
			case 14710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714710));
				orderActorToFactory(1105717710, EnemyVesta, "Vesta_608");
				break;
			case 14770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714770));
				orderActorToFactory(1105717770, EnemyVesta, "Vesta_609");
				break;
			case 14800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110714800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110717800, EnemyAstraea, "Astraea_610");
				break;
			case 14830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714830));
				orderActorToFactory(1105717830, EnemyVesta, "Vesta_611");
				break;
			case 14890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714890));
				orderActorToFactory(1105717890, EnemyVesta, "Vesta_612");
				break;
			case 14900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109714900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109717900, EnemyAstraea, "Astraea_613");
				break;
			case 14950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105714950));
				orderActorToFactory(1105717950, EnemyVesta, "Vesta_614");
				break;
			case 15000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121715000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121718000, EnemyAstraea, "Astraea_615");
				break;
			case 15010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715010));
				orderActorToFactory(1105718010, EnemyVesta, "Vesta_616");
				break;
			case 15070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715070));
				orderActorToFactory(1105718070, EnemyVesta, "Vesta_617");
				break;
			case 15100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1107715100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120715100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120718100, EnemyAstraea, "Astraea_618");
				break;
			case 15130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715130));
				orderActorToFactory(1105718130, EnemyVesta, "Vesta_619");
				break;
			case 15190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715190));
				orderActorToFactory(1105718190, EnemyVesta, "Vesta_620");
				break;
			case 15200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119715200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119718200, EnemyAstraea, "Astraea_621");
				break;
			case 15250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715250));
				orderActorToFactory(1105718250, EnemyVesta, "Vesta_622");
				break;
			case 15300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118715300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118718300, EnemyAstraea, "Astraea_623");
				break;
			case 15310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715310));
				orderActorToFactory(1105718310, EnemyVesta, "Vesta_624");
				break;
			case 15370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715370));
				orderActorToFactory(1105718370, EnemyVesta, "Vesta_625");
				break;
			case 15400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114715400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				orderActorToFactory(1114718400, EnemyAstraea, "Astraea_626");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117715400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117718400, EnemyAstraea, "Astraea_627");
				break;
			case 15430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715430));
				orderActorToFactory(1105718430, EnemyVesta, "Vesta_628");
				break;
			case 15490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715490));
				orderActorToFactory(1105718490, EnemyVesta, "Vesta_629");
				break;
			case 15500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113715500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113718500, EnemyAstraea, "Astraea_630");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116715500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116718500, EnemyAstraea, "Astraea_631");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127715500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127718500, EnemyCeres, "Ceres_632", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128715530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128718530, EnemyCeres, "Ceres_633", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715550));
				orderActorToFactory(1105718550, EnemyVesta, "Vesta_634");
				break;
			case 15560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129715560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129718560, EnemyCeres, "Ceres_635", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130715590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130718590, EnemyCeres, "Ceres_636", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112715600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112718600, EnemyAstraea, "Astraea_637");
				break;
			case 15610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715610));
				orderActorToFactory(1105718610, EnemyVesta, "Vesta_638");
				break;
			case 15620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131715620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131718620, EnemyCeres, "Ceres_639", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132715650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132718650, EnemyCeres, "Ceres_640", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 15670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715670));
				orderActorToFactory(1105718670, EnemyVesta, "Vesta_641");
				break;
			case 15700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111715700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111718700, EnemyAstraea, "Astraea_642");
				break;
			case 15730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715730));
				orderActorToFactory(1105718730, EnemyVesta, "Vesta_643");
				break;
			case 15790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715790));
				orderActorToFactory(1105718790, EnemyVesta, "Vesta_644");
				break;
			case 15800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110715800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110718800, EnemyAstraea, "Astraea_645");
				break;
			case 15850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715850));
				orderActorToFactory(1105718850, EnemyVesta, "Vesta_646");
				break;
			case 15900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109715900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109718900, EnemyAstraea, "Astraea_647");
				break;
			case 15910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715910));
				orderActorToFactory(1105718910, EnemyVesta, "Vesta_648");
				break;
			case 15970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105715970));
				orderActorToFactory(1105718970, EnemyVesta, "Vesta_649");
				break;
			case 16000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121716000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121719000, EnemyAstraea, "Astraea_650");
				break;
			case 16030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716030));
				orderActorToFactory(1105719030, EnemyVesta, "Vesta_651");
				break;
			case 16090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716090));
				orderActorToFactory(1105719090, EnemyVesta, "Vesta_652");
				break;
			case 16100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120716100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				orderActorToFactory(1120719100, EnemyAstraea, "Astraea_653");
				break;
			case 16150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716150));
				orderActorToFactory(1105719150, EnemyVesta, "Vesta_654");
				break;
			case 16200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119716200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				orderActorToFactory(1119719200, EnemyAstraea, "Astraea_655");
				break;
			case 16210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716210));
				orderActorToFactory(1105719210, EnemyVesta, "Vesta_656");
				break;
			case 16270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716270));
				orderActorToFactory(1105719270, EnemyVesta, "Vesta_657");
				break;
			case 16300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118716300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				orderActorToFactory(1118719300, EnemyAstraea, "Astraea_658");
				break;
			case 16330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716330));
				orderActorToFactory(1105719330, EnemyVesta, "Vesta_659");
				break;
			case 16390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716390));
				orderActorToFactory(1105719390, EnemyVesta, "Vesta_660");
				break;
			case 16400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114716400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				orderActorToFactory(1114719400, EnemyAstraea, "Astraea_661");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117716400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				orderActorToFactory(1117719400, EnemyAstraea, "Astraea_662");
				break;
			case 16450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716450));
				orderActorToFactory(1105719450, EnemyVesta, "Vesta_663");
				break;
			case 16500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113716500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				orderActorToFactory(1113719500, EnemyAstraea, "Astraea_664");
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116716500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				orderActorToFactory(1116719500, EnemyAstraea, "Astraea_665");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127716500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1127719500, EnemyCeres, "Ceres_666", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716510));
				orderActorToFactory(1105719510, EnemyVesta, "Vesta_667");
				break;
			case 16530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128716530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1128719530, EnemyCeres, "Ceres_668", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129716560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1129719560, EnemyCeres, "Ceres_669", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716570));
				orderActorToFactory(1105719570, EnemyVesta, "Vesta_670");
				break;
			case 16590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130716590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1130719590, EnemyCeres, "Ceres_671", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112716600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				orderActorToFactory(1112719600, EnemyAstraea, "Astraea_672");
				break;
			case 16620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131716620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1131719620, EnemyCeres, "Ceres_673", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716630));
				orderActorToFactory(1105719630, EnemyVesta, "Vesta_674");
				break;
			case 16650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132716650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				orderActorWithDpToFactory(1132719650, EnemyCeres, "Ceres_675", GameGlobal::_pSceneCommon->_pDispatcher_EnemyShots001);
				break;
			case 16690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716690));
				orderActorToFactory(1105719690, EnemyVesta, "Vesta_676");
				break;
			case 16700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111716700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				orderActorToFactory(1111719700, EnemyAstraea, "Astraea_677");
				break;
			case 16750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716750));
				orderActorToFactory(1105719750, EnemyVesta, "Vesta_678");
				break;
			case 16800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110716800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				orderActorToFactory(1110719800, EnemyAstraea, "Astraea_679");
				break;
			case 16810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716810));
				orderActorToFactory(1105719810, EnemyVesta, "Vesta_680");
				break;
			case 16870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716870));
				orderActorToFactory(1105719870, EnemyVesta, "Vesta_681");
				break;
			case 16900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109716900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				orderActorToFactory(1109719900, EnemyAstraea, "Astraea_682");
				break;
			case 16930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716930));
				orderActorToFactory(1105719930, EnemyVesta, "Vesta_683");
				break;
			case 16990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105716990));
				orderActorToFactory(1105719990, EnemyVesta, "Vesta_684");
				break;
			case 17000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121717000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				orderActorToFactory(1121720000, EnemyAstraea, "Astraea_685");
				break;
			case 17050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717050));
				orderActorToFactory(1105720050, EnemyVesta, "Vesta_686");
				break;
			case 17100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120717100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 17110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717110));
				orderActorToFactory(1105720110, EnemyVesta, "Vesta_687");
				break;
			case 17170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717170));
				orderActorToFactory(1105720170, EnemyVesta, "Vesta_688");
				break;
			case 17200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119717200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 17230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717230));
				orderActorToFactory(1105720230, EnemyVesta, "Vesta_689");
				break;
			case 17290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717290));
				orderActorToFactory(1105720290, EnemyVesta, "Vesta_690");
				break;
			case 17300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118717300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 17350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717350));
				orderActorToFactory(1105720350, EnemyVesta, "Vesta_691");
				break;
			case 17400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114717400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117717400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 17410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717410));
				orderActorToFactory(1105720410, EnemyVesta, "Vesta_692");
				break;
			case 17470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717470));
				orderActorToFactory(1105720470, EnemyVesta, "Vesta_693");
				break;
			case 17500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113717500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116717500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127717500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717530));
				orderActorToFactory(1105720530, EnemyVesta, "Vesta_694");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128717530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129717560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717590));
				orderActorToFactory(1105720590, EnemyVesta, "Vesta_695");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130717590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112717600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 17620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131717620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717650));
				orderActorToFactory(1105720650, EnemyVesta, "Vesta_696");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132717650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 17700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111717700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 17710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717710));
				orderActorToFactory(1105720710, EnemyVesta, "Vesta_697");
				break;
			case 17770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717770));
				orderActorToFactory(1105720770, EnemyVesta, "Vesta_698");
				break;
			case 17800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110717800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 17830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717830));
				orderActorToFactory(1105720830, EnemyVesta, "Vesta_699");
				break;
			case 17890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717890));
				orderActorToFactory(1105720890, EnemyVesta, "Vesta_700");
				break;
			case 17900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109717900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 17950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105717950));
				orderActorToFactory(1105720950, EnemyVesta, "Vesta_701");
				break;
			case 18000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121718000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				break;
			case 18010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718010));
				orderActorToFactory(1105721010, EnemyVesta, "Vesta_702");
				break;
			case 18070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718070));
				orderActorToFactory(1105721070, EnemyVesta, "Vesta_703");
				break;
			case 18100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120718100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 18130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718130));
				orderActorToFactory(1105721130, EnemyVesta, "Vesta_704");
				break;
			case 18190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718190));
				orderActorToFactory(1105721190, EnemyVesta, "Vesta_705");
				break;
			case 18200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119718200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 18250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718250));
				orderActorToFactory(1105721250, EnemyVesta, "Vesta_706");
				break;
			case 18300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118718300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 18310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718310));
				orderActorToFactory(1105721310, EnemyVesta, "Vesta_707");
				break;
			case 18370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718370));
				orderActorToFactory(1105721370, EnemyVesta, "Vesta_708");
				break;
			case 18400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114718400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117718400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 18430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718430));
				orderActorToFactory(1105721430, EnemyVesta, "Vesta_709");
				break;
			case 18490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718490));
				orderActorToFactory(1105721490, EnemyVesta, "Vesta_710");
				break;
			case 18500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113718500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116718500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127718500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128718530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718550));
				orderActorToFactory(1105721550, EnemyVesta, "Vesta_711");
				break;
			case 18560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129718560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130718590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112718600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 18610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718610));
				orderActorToFactory(1105721610, EnemyVesta, "Vesta_712");
				break;
			case 18620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131718620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132718650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 18670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718670));
				orderActorToFactory(1105721670, EnemyVesta, "Vesta_713");
				break;
			case 18700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111718700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 18730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718730));
				orderActorToFactory(1105721730, EnemyVesta, "Vesta_714");
				break;
			case 18790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718790));
				orderActorToFactory(1105721790, EnemyVesta, "Vesta_715");
				break;
			case 18800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110718800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 18850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718850));
				orderActorToFactory(1105721850, EnemyVesta, "Vesta_716");
				break;
			case 18900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109718900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 18910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718910));
				orderActorToFactory(1105721910, EnemyVesta, "Vesta_717");
				break;
			case 18970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105718970));
				orderActorToFactory(1105721970, EnemyVesta, "Vesta_718");
				break;
			case 19000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121719000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				break;
			case 19030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719030));
				orderActorToFactory(1105722030, EnemyVesta, "Vesta_719");
				break;
			case 19090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719090));
				orderActorToFactory(1105722090, EnemyVesta, "Vesta_720");
				break;
			case 19100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1120719100);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = 920004;
				pActor->_Y = -650004;
				}
				break;
			case 19150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719150));
				orderActorToFactory(1105722150, EnemyVesta, "Vesta_721");
				break;
			case 19200:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1119719200);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = 920003;
				pActor->_Y = -550003;
				}
				break;
			case 19210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719210));
				orderActorToFactory(1105722210, EnemyVesta, "Vesta_722");
				break;
			case 19270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719270));
				orderActorToFactory(1105722270, EnemyVesta, "Vesta_723");
				break;
			case 19300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1118719300);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = 920002;
				pActor->_Y = -450002;
				}
				break;
			case 19330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719330));
				orderActorToFactory(1105722330, EnemyVesta, "Vesta_724");
				break;
			case 19390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719390));
				orderActorToFactory(1105722390, EnemyVesta, "Vesta_725");
				break;
			case 19400:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1114719400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = -900005;
				pActor->_Y = -700005;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1117719400);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = 920001;
				pActor->_Y = -350001;
				}
				break;
			case 19450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719450));
				orderActorToFactory(1105722450, EnemyVesta, "Vesta_726");
				break;
			case 19500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1113719500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000004;
				pActor->_Z = -900004;
				pActor->_Y = -580004;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1116719500);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = 920000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1127719500);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719510));
				orderActorToFactory(1105722510, EnemyVesta, "Vesta_727");
				break;
			case 19530:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1128719530);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1129719560);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719570));
				orderActorToFactory(1105722570, EnemyVesta, "Vesta_728");
				break;
			case 19590:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1130719590);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1112719600);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000003;
				pActor->_Z = -900003;
				pActor->_Y = -460003;
				}
				break;
			case 19620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1131719620);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719630));
				orderActorToFactory(1105722630, EnemyVesta, "Vesta_729");
				break;
			case 19650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(1132719650);
				getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				}
				break;
			case 19690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719690));
				orderActorToFactory(1105722690, EnemyVesta, "Vesta_730");
				break;
			case 19700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1111719700);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000002;
				pActor->_Z = -900002;
				pActor->_Y = -340002;
				}
				break;
			case 19750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719750));
				orderActorToFactory(1105722750, EnemyVesta, "Vesta_731");
				break;
			case 19800:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1110719800);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000001;
				pActor->_Z = -900001;
				pActor->_Y = -220001;
				}
				break;
			case 19810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719810));
				orderActorToFactory(1105722810, EnemyVesta, "Vesta_732");
				break;
			case 19870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719870));
				orderActorToFactory(1105722870, EnemyVesta, "Vesta_733");
				break;
			case 19900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1109719900);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000000;
				pActor->_Z = -900000;
				pActor->_Y = -100000;
				}
				break;
			case 19930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719930));
				orderActorToFactory(1105722930, EnemyVesta, "Vesta_734");
				break;
			case 19990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105719990));
				orderActorToFactory(1105722990, EnemyVesta, "Vesta_735");
				break;
			case 20000:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(1121720000);
				getLordActor()->accept(KIND_ENEMY_BODY, pActor);
				pActor->_X = 9000005;
				pActor->_Z = 920005;
				pActor->_Y = -750005;
				}
				break;
			case 20050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720050));
				orderActorToFactory(1105723050, EnemyVesta, "Vesta_736");
				break;
			case 20110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720110));
				orderActorToFactory(1105723110, EnemyVesta, "Vesta_737");
				break;
			case 20170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720170));
				orderActorToFactory(1105723170, EnemyVesta, "Vesta_738");
				break;
			case 20230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720230));
				orderActorToFactory(1105723230, EnemyVesta, "Vesta_739");
				break;
			case 20290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720290));
				orderActorToFactory(1105723290, EnemyVesta, "Vesta_740");
				break;
			case 20350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720350));
				orderActorToFactory(1105723350, EnemyVesta, "Vesta_741");
				break;
			case 20410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720410));
				orderActorToFactory(1105723410, EnemyVesta, "Vesta_742");
				break;
			case 20470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720470));
				orderActorToFactory(1105723470, EnemyVesta, "Vesta_743");
				break;
			case 20530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720530));
				orderActorToFactory(1105723530, EnemyVesta, "Vesta_744");
				break;
			case 20590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720590));
				orderActorToFactory(1105723590, EnemyVesta, "Vesta_745");
				break;
			case 20650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720650));
				orderActorToFactory(1105723650, EnemyVesta, "Vesta_746");
				break;
			case 20710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720710));
				orderActorToFactory(1105723710, EnemyVesta, "Vesta_747");
				break;
			case 20770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720770));
				orderActorToFactory(1105723770, EnemyVesta, "Vesta_748");
				break;
			case 20830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720830));
				orderActorToFactory(1105723830, EnemyVesta, "Vesta_749");
				break;
			case 20890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720890));
				orderActorToFactory(1105723890, EnemyVesta, "Vesta_750");
				break;
			case 20950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105720950));
				orderActorToFactory(1105723950, EnemyVesta, "Vesta_751");
				break;
			case 21010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721010));
				orderActorToFactory(1105724010, EnemyVesta, "Vesta_752");
				break;
			case 21070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721070));
				orderActorToFactory(1105724070, EnemyVesta, "Vesta_753");
				break;
			case 21130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721130));
				orderActorToFactory(1105724130, EnemyVesta, "Vesta_754");
				break;
			case 21190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721190));
				orderActorToFactory(1105724190, EnemyVesta, "Vesta_755");
				break;
			case 21250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721250));
				orderActorToFactory(1105724250, EnemyVesta, "Vesta_756");
				break;
			case 21310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721310));
				orderActorToFactory(1105724310, EnemyVesta, "Vesta_757");
				break;
			case 21370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721370));
				orderActorToFactory(1105724370, EnemyVesta, "Vesta_758");
				break;
			case 21430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721430));
				orderActorToFactory(1105724430, EnemyVesta, "Vesta_759");
				break;
			case 21490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721490));
				orderActorToFactory(1105724490, EnemyVesta, "Vesta_760");
				break;
			case 21550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721550));
				orderActorToFactory(1105724550, EnemyVesta, "Vesta_761");
				break;
			case 21610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721610));
				orderActorToFactory(1105724610, EnemyVesta, "Vesta_762");
				break;
			case 21670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721670));
				orderActorToFactory(1105724670, EnemyVesta, "Vesta_763");
				break;
			case 21730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721730));
				orderActorToFactory(1105724730, EnemyVesta, "Vesta_764");
				break;
			case 21790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721790));
				orderActorToFactory(1105724790, EnemyVesta, "Vesta_765");
				break;
			case 21850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721850));
				orderActorToFactory(1105724850, EnemyVesta, "Vesta_766");
				break;
			case 21910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721910));
				orderActorToFactory(1105724910, EnemyVesta, "Vesta_767");
				break;
			case 21970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105721970));
				orderActorToFactory(1105724970, EnemyVesta, "Vesta_768");
				break;
			case 22030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722030));
				orderActorToFactory(1105725030, EnemyVesta, "Vesta_769");
				break;
			case 22090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722090));
				orderActorToFactory(1105725090, EnemyVesta, "Vesta_770");
				break;
			case 22150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722150));
				orderActorToFactory(1105725150, EnemyVesta, "Vesta_771");
				break;
			case 22210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722210));
				orderActorToFactory(1105725210, EnemyVesta, "Vesta_772");
				break;
			case 22270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722270));
				orderActorToFactory(1105725270, EnemyVesta, "Vesta_773");
				break;
			case 22330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722330));
				orderActorToFactory(1105725330, EnemyVesta, "Vesta_774");
				break;
			case 22390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722390));
				orderActorToFactory(1105725390, EnemyVesta, "Vesta_775");
				break;
			case 22450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722450));
				orderActorToFactory(1105725450, EnemyVesta, "Vesta_776");
				break;
			case 22510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722510));
				orderActorToFactory(1105725510, EnemyVesta, "Vesta_777");
				break;
			case 22570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722570));
				orderActorToFactory(1105725570, EnemyVesta, "Vesta_778");
				break;
			case 22630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722630));
				orderActorToFactory(1105725630, EnemyVesta, "Vesta_779");
				break;
			case 22690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722690));
				orderActorToFactory(1105725690, EnemyVesta, "Vesta_780");
				break;
			case 22750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722750));
				orderActorToFactory(1105725750, EnemyVesta, "Vesta_781");
				break;
			case 22810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722810));
				orderActorToFactory(1105725810, EnemyVesta, "Vesta_782");
				break;
			case 22870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722870));
				orderActorToFactory(1105725870, EnemyVesta, "Vesta_783");
				break;
			case 22930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722930));
				orderActorToFactory(1105725930, EnemyVesta, "Vesta_784");
				break;
			case 22990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105722990));
				orderActorToFactory(1105725990, EnemyVesta, "Vesta_785");
				break;
			case 23050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723050));
				orderActorToFactory(1105726050, EnemyVesta, "Vesta_786");
				break;
			case 23110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723110));
				orderActorToFactory(1105726110, EnemyVesta, "Vesta_787");
				break;
			case 23170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723170));
				orderActorToFactory(1105726170, EnemyVesta, "Vesta_788");
				break;
			case 23230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723230));
				orderActorToFactory(1105726230, EnemyVesta, "Vesta_789");
				break;
			case 23290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723290));
				orderActorToFactory(1105726290, EnemyVesta, "Vesta_790");
				break;
			case 23350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723350));
				orderActorToFactory(1105726350, EnemyVesta, "Vesta_791");
				break;
			case 23410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723410));
				orderActorToFactory(1105726410, EnemyVesta, "Vesta_792");
				break;
			case 23470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723470));
				orderActorToFactory(1105726470, EnemyVesta, "Vesta_793");
				break;
			case 23530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723530));
				orderActorToFactory(1105726530, EnemyVesta, "Vesta_794");
				break;
			case 23590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723590));
				orderActorToFactory(1105726590, EnemyVesta, "Vesta_795");
				break;
			case 23650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723650));
				orderActorToFactory(1105726650, EnemyVesta, "Vesta_796");
				break;
			case 23710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723710));
				orderActorToFactory(1105726710, EnemyVesta, "Vesta_797");
				break;
			case 23770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723770));
				orderActorToFactory(1105726770, EnemyVesta, "Vesta_798");
				break;
			case 23830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723830));
				orderActorToFactory(1105726830, EnemyVesta, "Vesta_799");
				break;
			case 23890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723890));
				orderActorToFactory(1105726890, EnemyVesta, "Vesta_800");
				break;
			case 23950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105723950));
				orderActorToFactory(1105726950, EnemyVesta, "Vesta_801");
				break;
			case 24010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724010));
				orderActorToFactory(1105727010, EnemyVesta, "Vesta_802");
				break;
			case 24070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724070));
				orderActorToFactory(1105727070, EnemyVesta, "Vesta_803");
				break;
			case 24130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724130));
				orderActorToFactory(1105727130, EnemyVesta, "Vesta_804");
				break;
			case 24190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724190));
				orderActorToFactory(1105727190, EnemyVesta, "Vesta_805");
				break;
			case 24250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724250));
				orderActorToFactory(1105727250, EnemyVesta, "Vesta_806");
				break;
			case 24310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724310));
				orderActorToFactory(1105727310, EnemyVesta, "Vesta_807");
				break;
			case 24370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724370));
				orderActorToFactory(1105727370, EnemyVesta, "Vesta_808");
				break;
			case 24430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724430));
				orderActorToFactory(1105727430, EnemyVesta, "Vesta_809");
				break;
			case 24490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724490));
				orderActorToFactory(1105727490, EnemyVesta, "Vesta_810");
				break;
			case 24550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724550));
				orderActorToFactory(1105727550, EnemyVesta, "Vesta_811");
				break;
			case 24610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724610));
				orderActorToFactory(1105727610, EnemyVesta, "Vesta_812");
				break;
			case 24670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724670));
				orderActorToFactory(1105727670, EnemyVesta, "Vesta_813");
				break;
			case 24730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724730));
				orderActorToFactory(1105727730, EnemyVesta, "Vesta_814");
				break;
			case 24790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724790));
				orderActorToFactory(1105727790, EnemyVesta, "Vesta_815");
				break;
			case 24850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724850));
				orderActorToFactory(1105727850, EnemyVesta, "Vesta_816");
				break;
			case 24910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724910));
				orderActorToFactory(1105727910, EnemyVesta, "Vesta_817");
				break;
			case 24970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105724970));
				orderActorToFactory(1105727970, EnemyVesta, "Vesta_818");
				break;
			case 25030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725030));
				orderActorToFactory(1105728030, EnemyVesta, "Vesta_819");
				break;
			case 25090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725090));
				orderActorToFactory(1105728090, EnemyVesta, "Vesta_820");
				break;
			case 25150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725150));
				orderActorToFactory(1105728150, EnemyVesta, "Vesta_821");
				break;
			case 25210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725210));
				orderActorToFactory(1105728210, EnemyVesta, "Vesta_822");
				break;
			case 25270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725270));
				orderActorToFactory(1105728270, EnemyVesta, "Vesta_823");
				break;
			case 25330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725330));
				orderActorToFactory(1105728330, EnemyVesta, "Vesta_824");
				break;
			case 25390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725390));
				orderActorToFactory(1105728390, EnemyVesta, "Vesta_825");
				break;
			case 25450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725450));
				orderActorToFactory(1105728450, EnemyVesta, "Vesta_826");
				break;
			case 25510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725510));
				orderActorToFactory(1105728510, EnemyVesta, "Vesta_827");
				break;
			case 25570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725570));
				orderActorToFactory(1105728570, EnemyVesta, "Vesta_828");
				break;
			case 25630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725630));
				orderActorToFactory(1105728630, EnemyVesta, "Vesta_829");
				break;
			case 25690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725690));
				orderActorToFactory(1105728690, EnemyVesta, "Vesta_830");
				break;
			case 25750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725750));
				orderActorToFactory(1105728750, EnemyVesta, "Vesta_831");
				break;
			case 25810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725810));
				orderActorToFactory(1105728810, EnemyVesta, "Vesta_832");
				break;
			case 25870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725870));
				orderActorToFactory(1105728870, EnemyVesta, "Vesta_833");
				break;
			case 25930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725930));
				orderActorToFactory(1105728930, EnemyVesta, "Vesta_834");
				break;
			case 25990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105725990));
				orderActorToFactory(1105728990, EnemyVesta, "Vesta_835");
				break;
			case 26050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726050));
				orderActorToFactory(1105729050, EnemyVesta, "Vesta_836");
				break;
			case 26110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726110));
				orderActorToFactory(1105729110, EnemyVesta, "Vesta_837");
				break;
			case 26170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726170));
				orderActorToFactory(1105729170, EnemyVesta, "Vesta_838");
				break;
			case 26230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726230));
				orderActorToFactory(1105729230, EnemyVesta, "Vesta_839");
				break;
			case 26290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726290));
				orderActorToFactory(1105729290, EnemyVesta, "Vesta_840");
				break;
			case 26350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726350));
				orderActorToFactory(1105729350, EnemyVesta, "Vesta_841");
				break;
			case 26410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726410));
				orderActorToFactory(1105729410, EnemyVesta, "Vesta_842");
				break;
			case 26470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726470));
				orderActorToFactory(1105729470, EnemyVesta, "Vesta_843");
				break;
			case 26530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726530));
				orderActorToFactory(1105729530, EnemyVesta, "Vesta_844");
				break;
			case 26590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726590));
				orderActorToFactory(1105729590, EnemyVesta, "Vesta_845");
				break;
			case 26650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726650));
				orderActorToFactory(1105729650, EnemyVesta, "Vesta_846");
				break;
			case 26710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726710));
				orderActorToFactory(1105729710, EnemyVesta, "Vesta_847");
				break;
			case 26770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726770));
				orderActorToFactory(1105729770, EnemyVesta, "Vesta_848");
				break;
			case 26830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726830));
				orderActorToFactory(1105729830, EnemyVesta, "Vesta_849");
				break;
			case 26890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726890));
				orderActorToFactory(1105729890, EnemyVesta, "Vesta_850");
				break;
			case 26950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105726950));
				orderActorToFactory(1105729950, EnemyVesta, "Vesta_851");
				break;
			case 27010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727010));
				orderActorToFactory(1105730010, EnemyVesta, "Vesta_852");
				break;
			case 27070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727070));
				orderActorToFactory(1105730070, EnemyVesta, "Vesta_853");
				break;
			case 27130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727130));
				orderActorToFactory(1105730130, EnemyVesta, "Vesta_854");
				break;
			case 27190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727190));
				orderActorToFactory(1105730190, EnemyVesta, "Vesta_855");
				break;
			case 27250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727250));
				orderActorToFactory(1105730250, EnemyVesta, "Vesta_856");
				break;
			case 27310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727310));
				orderActorToFactory(1105730310, EnemyVesta, "Vesta_857");
				break;
			case 27370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727370));
				orderActorToFactory(1105730370, EnemyVesta, "Vesta_858");
				break;
			case 27430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727430));
				orderActorToFactory(1105730430, EnemyVesta, "Vesta_859");
				break;
			case 27490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727490));
				orderActorToFactory(1105730490, EnemyVesta, "Vesta_860");
				break;
			case 27550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727550));
				orderActorToFactory(1105730550, EnemyVesta, "Vesta_861");
				break;
			case 27610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727610));
				orderActorToFactory(1105730610, EnemyVesta, "Vesta_862");
				break;
			case 27670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727670));
				orderActorToFactory(1105730670, EnemyVesta, "Vesta_863");
				break;
			case 27730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727730));
				orderActorToFactory(1105730730, EnemyVesta, "Vesta_864");
				break;
			case 27790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727790));
				orderActorToFactory(1105730790, EnemyVesta, "Vesta_865");
				break;
			case 27850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727850));
				orderActorToFactory(1105730850, EnemyVesta, "Vesta_866");
				break;
			case 27910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727910));
				orderActorToFactory(1105730910, EnemyVesta, "Vesta_867");
				break;
			case 27970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105727970));
				orderActorToFactory(1105730970, EnemyVesta, "Vesta_868");
				break;
			case 28030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728030));
				orderActorToFactory(1105731030, EnemyVesta, "Vesta_869");
				break;
			case 28090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728090));
				orderActorToFactory(1105731090, EnemyVesta, "Vesta_870");
				break;
			case 28150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728150));
				orderActorToFactory(1105731150, EnemyVesta, "Vesta_871");
				break;
			case 28210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728210));
				orderActorToFactory(1105731210, EnemyVesta, "Vesta_872");
				break;
			case 28270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728270));
				orderActorToFactory(1105731270, EnemyVesta, "Vesta_873");
				break;
			case 28330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728330));
				orderActorToFactory(1105731330, EnemyVesta, "Vesta_874");
				break;
			case 28390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728390));
				orderActorToFactory(1105731390, EnemyVesta, "Vesta_875");
				break;
			case 28450:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728450));
				orderActorToFactory(1105731450, EnemyVesta, "Vesta_876");
				break;
			case 28510:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728510));
				orderActorToFactory(1105731510, EnemyVesta, "Vesta_877");
				break;
			case 28570:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728570));
				orderActorToFactory(1105731570, EnemyVesta, "Vesta_878");
				break;
			case 28630:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728630));
				orderActorToFactory(1105731630, EnemyVesta, "Vesta_879");
				break;
			case 28690:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728690));
				orderActorToFactory(1105731690, EnemyVesta, "Vesta_880");
				break;
			case 28750:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728750));
				orderActorToFactory(1105731750, EnemyVesta, "Vesta_881");
				break;
			case 28810:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728810));
				orderActorToFactory(1105731810, EnemyVesta, "Vesta_882");
				break;
			case 28870:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728870));
				orderActorToFactory(1105731870, EnemyVesta, "Vesta_883");
				break;
			case 28930:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728930));
				orderActorToFactory(1105731930, EnemyVesta, "Vesta_884");
				break;
			case 28990:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105728990));
				orderActorToFactory(1105731990, EnemyVesta, "Vesta_885");
				break;
			case 29050:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729050));
				break;
			case 29110:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729110));
				break;
			case 29170:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729170));
				break;
			case 29230:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729230));
				break;
			case 29290:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729290));
				break;
			case 29350:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729350));
				break;
			case 29410:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729410));
				break;
			case 29470:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729470));
				break;
			case 29530:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729530));
				break;
			case 29590:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729590));
				break;
			case 29650:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729650));
				break;
			case 29710:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729710));
				break;
			case 29770:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729770));
				break;
			case 29830:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729830));
				break;
			case 29890:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729890));
				break;
			case 29950:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105729950));
				break;
			case 30010:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730010));
				break;
			case 30070:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730070));
				break;
			case 30130:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730130));
				break;
			case 30190:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730190));
				break;
			case 30250:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730250));
				break;
			case 30310:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730310));
				break;
			case 30370:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730370));
				break;
			case 30430:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730430));
				break;
			case 30490:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730490));
				break;
			case 30550:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730550));
				break;
			case 30610:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730610));
				break;
			case 30670:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730670));
				break;
			case 30730:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730730));
				break;
			case 30790:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730790));
				break;
			case 30850:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730850));
				break;
			case 30910:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730910));
				break;
			case 30970:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105730970));
				break;
			case 31030:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731030));
				break;
			case 31090:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731090));
				break;
			case 31150:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731150));
				break;
			case 31210:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731210));
				break;
			case 31270:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731270));
				break;
			case 31330:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731330));
				break;
			case 31390:
				getLordActor()->accept(KIND_ENEMY_BODY, obtainActorFromFactory(1105731390));
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
