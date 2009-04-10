#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pRot = NEW RotationActor("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeNow(); //最初非表示
        _pRot->addSubLast(pEnemyMeshShot);
    }


	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,60,80,160,240,300,320,370,390,400,440,480,510,570,580,600,650,660,680,720,760,780,840,900,920,950,960,970,1000,1040,1050,1100,1110,1150,1180,1200,1240,1250,1260,1280,1300,1320,1360,1380,1400,1440,1480,1500,1520,1530,1550,1560,1590,1600,1620,1650,1680,1700,1710,1740,1750,1770,1800,1820,1830,1840,1850,1860,1880,1890,1900,1920,1940,1960,1980,2000,2020,2040,2060,2080,2100,2110,2120,2130,2140,2150,2160,2170,2180,2190,2200,2210,2220,2230,2240,2250,2260,2270,2280,2290,2300,2310,2320,2330,2340,2350,2360,2370,2380,2390,2400,2410,2420,2430,2440,2450,2460,2470,2480,2490,2500,2520,2540,2560,2580,2600,2620,2640,2660,2680,2700,2710,2720,2730,2740,2750,2760,2770,2780,2790,2800,2810,2820,2830,2840,2850,2860,2870,2880,2890,2900,2910,2920,2930,2940,2950,2960,2970,2980,2990,3000,3010,3020,3030,3040,3050,3060,3070,3080,3090,3100};
	_paFrame_NextEvent = new DWORD[171];
	for (int i = 0; i < 171; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorWithRotToFactory(11077300, EnemyCeres, "Ceres_1", _pRot);
	orderActorWithRotToFactory(11077390, EnemyCeres, "Ceres_2", _pRot);
	orderActorWithRotToFactory(11077480, EnemyCeres, "Ceres_3", _pRot);
	orderActorWithRotToFactory(11077570, EnemyCeres, "Ceres_4", _pRot);
	orderActorWithRotToFactory(11087600, EnemyCeres, "Ceres_5", _pRot);
	// gen01 end
}

void Stage01MainScene::initialize() {
    getLordActor()->accept(KIND_ENEMY, _pRot);
}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_lifeframe== _paFrame_NextEvent[_iCnt_Event]) {
		switch (_lifeframe) {
			case 1:
				break;
			case 60:
				orderActorWithRotToFactory(11077660, EnemyCeres, "Ceres_6", _pRot);
				break;
			case 80:
				orderActorWithRotToFactory(11087680, EnemyCeres, "Ceres_7", _pRot);
				break;
			case 160:
				orderActorWithRotToFactory(11087760, EnemyCeres, "Ceres_8", _pRot);
				break;
			case 240:
				orderActorWithRotToFactory(11087840, EnemyCeres, "Ceres_9", _pRot);
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(11097900, EnemyCeres, "Ceres_10", _pRot);
				break;
			case 320:
				orderActorWithRotToFactory(11087920, EnemyCeres, "Ceres_11", _pRot);
				break;
			case 370:
				orderActorWithRotToFactory(11097970, EnemyCeres, "Ceres_12", _pRot);
				break;
			case 390:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077390);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 400:
				orderActorWithRotToFactory(110871000, EnemyCeres, "Ceres_13", _pRot);
				break;
			case 440:
				orderActorWithRotToFactory(110971040, EnemyCeres, "Ceres_14", _pRot);
				break;
			case 480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077480);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 510:
				orderActorWithRotToFactory(110971110, EnemyCeres, "Ceres_15", _pRot);
				break;
			case 570:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077570);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 580:
				orderActorWithRotToFactory(110971180, EnemyCeres, "Ceres_16", _pRot);
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111071200, EnemyCeres, "Ceres_17", _pRot);
				break;
			case 650:
				orderActorWithRotToFactory(110971250, EnemyCeres, "Ceres_18", _pRot);
				break;
			case 660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077660);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111071260, EnemyCeres, "Ceres_19", _pRot);
				break;
			case 680:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087680);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 720:
				orderActorWithRotToFactory(111071320, EnemyCeres, "Ceres_20", _pRot);
				break;
			case 760:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087760);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 780:
				orderActorWithRotToFactory(111071380, EnemyCeres, "Ceres_21", _pRot);
				break;
			case 840:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087840);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111071440, EnemyCeres, "Ceres_22", _pRot);
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111071500, EnemyCeres, "Ceres_23", _pRot);
				orderActorWithRotToFactory(111171500, EnemyCeres, "Ceres_24", _pRot);
				break;
			case 920:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087920);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 950:
				orderActorWithRotToFactory(111171550, EnemyCeres, "Ceres_25", _pRot);
				break;
			case 960:
				orderActorWithRotToFactory(111071560, EnemyCeres, "Ceres_26", _pRot);
				break;
			case 970:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097970);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110871000);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171600, EnemyCeres, "Ceres_27", _pRot);
				break;
			case 1040:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971040);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1050:
				orderActorWithRotToFactory(111171650, EnemyCeres, "Ceres_28", _pRot);
				break;
			case 1100:
				orderActorWithRotToFactory(111171700, EnemyCeres, "Ceres_29", _pRot);
				break;
			case 1110:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971110);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1150:
				orderActorWithRotToFactory(111171750, EnemyCeres, "Ceres_30", _pRot);
				break;
			case 1180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971180);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171800, EnemyCeres, "Ceres_31", _pRot);
				orderActorWithRotToFactory(111271800, EnemyCeres, "Ceres_32", _pRot);
				break;
			case 1240:
				orderActorWithRotToFactory(111271840, EnemyCeres, "Ceres_33", _pRot);
				break;
			case 1250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971250);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171850, EnemyCeres, "Ceres_34", _pRot);
				break;
			case 1260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071260);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1280:
				orderActorWithRotToFactory(111271880, EnemyCeres, "Ceres_35", _pRot);
				break;
			case 1300:
				orderActorWithRotToFactory(111171900, EnemyCeres, "Ceres_36", _pRot);
				break;
			case 1320:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071320);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111271920, EnemyCeres, "Ceres_37", _pRot);
				break;
			case 1360:
				orderActorWithRotToFactory(111271960, EnemyCeres, "Ceres_38", _pRot);
				break;
			case 1380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071380);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1400:
				orderActorWithRotToFactory(111272000, EnemyCeres, "Ceres_39", _pRot);
				break;
			case 1440:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071440);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111272040, EnemyCeres, "Ceres_40", _pRot);
				break;
			case 1480:
				orderActorWithRotToFactory(111272080, EnemyCeres, "Ceres_41", _pRot);
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111372100, EnemyCeres, "Ceres_42", _pRot);
				break;
			case 1520:
				orderActorWithRotToFactory(111272120, EnemyCeres, "Ceres_43", _pRot);
				break;
			case 1530:
				orderActorWithRotToFactory(111372130, EnemyCeres, "Ceres_44", _pRot);
				break;
			case 1550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171550);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071560);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111272160, EnemyCeres, "Ceres_45", _pRot);
				orderActorWithRotToFactory(111372160, EnemyCeres, "Ceres_46", _pRot);
				break;
			case 1590:
				orderActorWithRotToFactory(111372190, EnemyCeres, "Ceres_47", _pRot);
				break;
			case 1600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111272200, EnemyCeres, "Ceres_48", _pRot);
				break;
			case 1620:
				orderActorWithRotToFactory(111372220, EnemyCeres, "Ceres_49", _pRot);
				break;
			case 1650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171650);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111372250, EnemyCeres, "Ceres_50", _pRot);
				break;
			case 1680:
				orderActorWithRotToFactory(111372280, EnemyCeres, "Ceres_51", _pRot);
				break;
			case 1700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171700);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1710:
				orderActorWithRotToFactory(111372310, EnemyCeres, "Ceres_52", _pRot);
				break;
			case 1740:
				orderActorWithRotToFactory(111372340, EnemyCeres, "Ceres_53", _pRot);
				break;
			case 1750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171750);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1770:
				orderActorWithRotToFactory(111372370, EnemyCeres, "Ceres_54", _pRot);
				break;
			case 1800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111372400, EnemyCeres, "Ceres_55", _pRot);
				orderActorWithRotToFactory(111472400, EnemyCeres, "Ceres_56", _pRot);
				break;
			case 1820:
				orderActorWithRotToFactory(111472420, EnemyCeres, "Ceres_57", _pRot);
				break;
			case 1830:
				orderActorWithRotToFactory(111372430, EnemyCeres, "Ceres_58", _pRot);
				break;
			case 1840:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271840);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472440, EnemyCeres, "Ceres_59", _pRot);
				break;
			case 1850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171850);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1860:
				orderActorWithRotToFactory(111372460, EnemyCeres, "Ceres_60", _pRot);
				orderActorWithRotToFactory(111472460, EnemyCeres, "Ceres_61", _pRot);
				break;
			case 1880:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271880);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472480, EnemyCeres, "Ceres_62", _pRot);
				break;
			case 1890:
				orderActorWithRotToFactory(111372490, EnemyCeres, "Ceres_63", _pRot);
				break;
			case 1900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472500, EnemyCeres, "Ceres_64", _pRot);
				break;
			case 1920:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271920);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472520, EnemyCeres, "Ceres_65", _pRot);
				break;
			case 1940:
				orderActorWithRotToFactory(111472540, EnemyCeres, "Ceres_66", _pRot);
				break;
			case 1960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271960);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472560, EnemyCeres, "Ceres_67", _pRot);
				break;
			case 1980:
				orderActorWithRotToFactory(111472580, EnemyCeres, "Ceres_68", _pRot);
				break;
			case 2000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272000);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472600, EnemyCeres, "Ceres_69", _pRot);
				break;
			case 2020:
				orderActorWithRotToFactory(111472620, EnemyCeres, "Ceres_70", _pRot);
				break;
			case 2040:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272040);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472640, EnemyCeres, "Ceres_71", _pRot);
				break;
			case 2060:
				orderActorWithRotToFactory(111472660, EnemyCeres, "Ceres_72", _pRot);
				break;
			case 2080:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272080);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472680, EnemyCeres, "Ceres_73", _pRot);
				break;
			case 2100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472700, EnemyCeres, "Ceres_74", _pRot);
				orderActorWithRotToFactory(111572700, EnemyCeres, "Ceres_75", _pRot);
				break;
			case 2110:
				orderActorWithRotToFactory(111572710, EnemyCeres, "Ceres_76", _pRot);
				break;
			case 2120:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272120);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472720, EnemyCeres, "Ceres_77", _pRot);
				orderActorWithRotToFactory(111572720, EnemyCeres, "Ceres_78", _pRot);
				break;
			case 2130:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372130);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572730, EnemyCeres, "Ceres_79", _pRot);
				break;
			case 2140:
				orderActorWithRotToFactory(111472740, EnemyCeres, "Ceres_80", _pRot);
				orderActorWithRotToFactory(111572740, EnemyCeres, "Ceres_81", _pRot);
				break;
			case 2150:
				orderActorWithRotToFactory(111572750, EnemyCeres, "Ceres_82", _pRot);
				break;
			case 2160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272160);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372160);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472760, EnemyCeres, "Ceres_83", _pRot);
				orderActorWithRotToFactory(111572760, EnemyCeres, "Ceres_84", _pRot);
				break;
			case 2170:
				orderActorWithRotToFactory(111572770, EnemyCeres, "Ceres_85", _pRot);
				break;
			case 2180:
				orderActorWithRotToFactory(111472780, EnemyCeres, "Ceres_86", _pRot);
				orderActorWithRotToFactory(111572780, EnemyCeres, "Ceres_87", _pRot);
				break;
			case 2190:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372190);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572790, EnemyCeres, "Ceres_88", _pRot);
				break;
			case 2200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472800, EnemyCeres, "Ceres_89", _pRot);
				orderActorWithRotToFactory(111572800, EnemyCeres, "Ceres_90", _pRot);
				break;
			case 2210:
				orderActorWithRotToFactory(111572810, EnemyCeres, "Ceres_91", _pRot);
				break;
			case 2220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572820, EnemyCeres, "Ceres_92", _pRot);
				break;
			case 2230:
				orderActorWithRotToFactory(111572830, EnemyCeres, "Ceres_93", _pRot);
				break;
			case 2240:
				orderActorWithRotToFactory(111572840, EnemyCeres, "Ceres_94", _pRot);
				break;
			case 2250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372250);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572850, EnemyCeres, "Ceres_95", _pRot);
				break;
			case 2260:
				orderActorWithRotToFactory(111572860, EnemyCeres, "Ceres_96", _pRot);
				break;
			case 2270:
				orderActorWithRotToFactory(111572870, EnemyCeres, "Ceres_97", _pRot);
				break;
			case 2280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372280);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572880, EnemyCeres, "Ceres_98", _pRot);
				break;
			case 2290:
				orderActorWithRotToFactory(111572890, EnemyCeres, "Ceres_99", _pRot);
				break;
			case 2300:
				orderActorWithRotToFactory(111572900, EnemyCeres, "Ceres_100", _pRot);
				break;
			case 2310:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372310);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572910, EnemyCeres, "Ceres_101", _pRot);
				break;
			case 2320:
				orderActorWithRotToFactory(111572920, EnemyCeres, "Ceres_102", _pRot);
				break;
			case 2330:
				orderActorWithRotToFactory(111572930, EnemyCeres, "Ceres_103", _pRot);
				break;
			case 2340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572940, EnemyCeres, "Ceres_104", _pRot);
				break;
			case 2350:
				orderActorWithRotToFactory(111572950, EnemyCeres, "Ceres_105", _pRot);
				break;
			case 2360:
				orderActorWithRotToFactory(111572960, EnemyCeres, "Ceres_106", _pRot);
				break;
			case 2370:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372370);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572970, EnemyCeres, "Ceres_107", _pRot);
				break;
			case 2380:
				orderActorWithRotToFactory(111572980, EnemyCeres, "Ceres_108", _pRot);
				break;
			case 2390:
				orderActorWithRotToFactory(111572990, EnemyCeres, "Ceres_109", _pRot);
				break;
			case 2400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573000, EnemyCeres, "Ceres_110", _pRot);
				break;
			case 2410:
				orderActorWithRotToFactory(111573010, EnemyCeres, "Ceres_111", _pRot);
				break;
			case 2420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472420);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573020, EnemyCeres, "Ceres_112", _pRot);
				break;
			case 2430:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372430);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573030, EnemyCeres, "Ceres_113", _pRot);
				break;
			case 2440:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472440);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573040, EnemyCeres, "Ceres_114", _pRot);
				break;
			case 2450:
				orderActorWithRotToFactory(111573050, EnemyCeres, "Ceres_115", _pRot);
				break;
			case 2460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372460);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472460);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573060, EnemyCeres, "Ceres_116", _pRot);
				break;
			case 2470:
				orderActorWithRotToFactory(111573070, EnemyCeres, "Ceres_117", _pRot);
				break;
			case 2480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472480);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573080, EnemyCeres, "Ceres_118", _pRot);
				break;
			case 2490:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372490);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573090, EnemyCeres, "Ceres_119", _pRot);
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573100, EnemyCeres, "Ceres_120", _pRot);
				break;
			case 2520:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472520);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2540:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472540);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472560);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2580:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472580);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472620);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2640:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472640);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472660);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2680:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472680);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472700);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572700);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2710:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572710);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2720:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472720);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572720);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2730:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572730);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472740);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572740);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572750);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2760:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472760);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572760);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2770:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572770);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2790:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572790);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2810:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572810);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2820:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572820);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2830:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572830);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2840:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572840);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572850);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2860:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572860);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2870:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572870);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2880:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572880);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2890:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572890);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2910:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572910);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2920:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572920);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2930:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572930);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2940:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572940);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572950);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572960);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2970:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572970);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2980:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572980);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2990:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572990);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573000);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3010:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573010);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3020:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573020);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3030:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573030);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3040:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573040);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573050);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3060:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573060);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3070:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573070);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3080:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573080);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3090:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573090);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 3100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
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
        addSubLast(GameGlobal::_pSceneCommon->breakAwayFromTree());

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
    //_pRotはどのツリーにも所属していない。
    if (_pRot->getParent() == NULL) {
        _TRACE_("_pRotが未所属のため独自delete");
        DELETE_IMPOSSIBLE_NULL(_pRot);
    }
}
