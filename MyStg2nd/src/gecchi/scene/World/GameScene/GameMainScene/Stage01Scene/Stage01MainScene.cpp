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
        //pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot", "M/Ceres");
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot", "X/Ceres", "default");
        pEnemyMeshShot->inactImmediately(); //最初非表示
        _pRot->addSubLast(pEnemyMeshShot);
    }


	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,100,200,300,390,400,480,500,570,600,660,680,690,700,760,780,840,870,900,920,960,970,980,1000,1040,1060,1110,1140,1180,1200,1220,1250,1260,1270,1300,1320,1340,1380,1410,1440,1480,1500,1550,1560,1600,1620,1650,1680,1700,1740,1750,1800,1840,1850,1860,1880,1900,1920,1950,1960,2000,2040,2050,2080,2100,2120,2130,2140,2150,2160,2180,2190,2200,2220,2250,2260,2280,2300,2310,2340,2370,2380,2400,2420,2430,2440,2460,2480,2490,2500,2520,2540,2550,2560,2580,2600,2610,2620,2640,2660,2670,2680,2700,2720,2730,2740,2760,2780,2790,2800,2820,2840,2860,2880,2900,2920,2940,2960,2980,3000,3020,3040,3060,3080,3100};
	_paFrame_NextEvent = new DWORD[125];
	for (int i = 0; i < 125; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorWithRotToFactory(11077300, EnemyCeres, "Ceres_1", "M/Ceres", _pRot);
	// gen01 end
}

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				break;
			case 100:
				getLordActor()->accept(KIND_ENEMY, _pRot);
				orderActorWithRotToFactory(11077400, EnemyCeres, "Ceres_2", "M/Ceres", _pRot);
				break;
			case 200:
				orderActorWithRotToFactory(11077500, EnemyCeres, "Ceres_3", "M/Ceres", _pRot);
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(11077600, EnemyCeres, "Ceres_4", "M/Ceres", _pRot);
				orderActorWithRotToFactory(11087600, EnemyCeres, "Ceres_5", "M/Ceres", _pRot);
				break;
			case 390:
				orderActorWithRotToFactory(11087690, EnemyCeres, "Ceres_6", "M/Ceres", _pRot);
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(11077700, EnemyCeres, "Ceres_7", "M/Ceres", _pRot);
				break;
			case 480:
				orderActorWithRotToFactory(11087780, EnemyCeres, "Ceres_8", "M/Ceres", _pRot);
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 570:
				orderActorWithRotToFactory(11087870, EnemyCeres, "Ceres_9", "M/Ceres", _pRot);
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087600);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(11097900, EnemyCeres, "Ceres_10", "M/Ceres", _pRot);
				break;
			case 660:
				orderActorWithRotToFactory(11087960, EnemyCeres, "Ceres_11", "M/Ceres", _pRot);
				break;
			case 680:
				orderActorWithRotToFactory(11097980, EnemyCeres, "Ceres_12", "M/Ceres", _pRot);
				break;
			case 690:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087690);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11077700);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -300000;
				pActor->_veloBegin = 5000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 760:
				orderActorWithRotToFactory(110971060, EnemyCeres, "Ceres_13", "M/Ceres", _pRot);
				break;
			case 780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 840:
				orderActorWithRotToFactory(110971140, EnemyCeres, "Ceres_14", "M/Ceres", _pRot);
				break;
			case 870:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087870);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111071200, EnemyCeres, "Ceres_15", "M/Ceres", _pRot);
				break;
			case 920:
				orderActorWithRotToFactory(110971220, EnemyCeres, "Ceres_16", "M/Ceres", _pRot);
				break;
			case 960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11087960);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 6000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 970:
				orderActorWithRotToFactory(111071270, EnemyCeres, "Ceres_17", "M/Ceres", _pRot);
				break;
			case 980:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11097980);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1000:
				orderActorWithRotToFactory(110971300, EnemyCeres, "Ceres_18", "M/Ceres", _pRot);
				break;
			case 1040:
				orderActorWithRotToFactory(111071340, EnemyCeres, "Ceres_19", "M/Ceres", _pRot);
				break;
			case 1060:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971060);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1110:
				orderActorWithRotToFactory(111071410, EnemyCeres, "Ceres_20", "M/Ceres", _pRot);
				break;
			case 1140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971140);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1180:
				orderActorWithRotToFactory(111071480, EnemyCeres, "Ceres_21", "M/Ceres", _pRot);
				break;
			case 1200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171500, EnemyCeres, "Ceres_22", "M/Ceres", _pRot);
				break;
			case 1220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1250:
				orderActorWithRotToFactory(111071550, EnemyCeres, "Ceres_23", "M/Ceres", _pRot);
				break;
			case 1260:
				orderActorWithRotToFactory(111171560, EnemyCeres, "Ceres_24", "M/Ceres", _pRot);
				break;
			case 1270:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071270);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(110971300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -200000;
				pActor->_veloBegin = 7000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1320:
				orderActorWithRotToFactory(111171620, EnemyCeres, "Ceres_25", "M/Ceres", _pRot);
				break;
			case 1340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1380:
				orderActorWithRotToFactory(111171680, EnemyCeres, "Ceres_26", "M/Ceres", _pRot);
				break;
			case 1410:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071410);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1440:
				orderActorWithRotToFactory(111171740, EnemyCeres, "Ceres_27", "M/Ceres", _pRot);
				break;
			case 1480:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071480);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171800, EnemyCeres, "Ceres_28", "M/Ceres", _pRot);
				orderActorWithRotToFactory(111271800, EnemyCeres, "Ceres_29", "M/Ceres", _pRot);
				break;
			case 1550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111071550);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111271850, EnemyCeres, "Ceres_30", "M/Ceres", _pRot);
				break;
			case 1560:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171560);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111171860, EnemyCeres, "Ceres_31", "M/Ceres", _pRot);
				break;
			case 1600:
				orderActorWithRotToFactory(111271900, EnemyCeres, "Ceres_32", "M/Ceres", _pRot);
				break;
			case 1620:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171620);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1650:
				orderActorWithRotToFactory(111271950, EnemyCeres, "Ceres_33", "M/Ceres", _pRot);
				break;
			case 1680:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171680);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1700:
				orderActorWithRotToFactory(111272000, EnemyCeres, "Ceres_34", "M/Ceres", _pRot);
				break;
			case 1740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171740);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1750:
				orderActorWithRotToFactory(111272050, EnemyCeres, "Ceres_35", "M/Ceres", _pRot);
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
				orderActorWithRotToFactory(111272100, EnemyCeres, "Ceres_36", "M/Ceres", _pRot);
				orderActorWithRotToFactory(111372100, EnemyCeres, "Ceres_37", "M/Ceres", _pRot);
				break;
			case 1840:
				orderActorWithRotToFactory(111372140, EnemyCeres, "Ceres_38", "M/Ceres", _pRot);
				break;
			case 1850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271850);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111272150, EnemyCeres, "Ceres_39", "M/Ceres", _pRot);
				break;
			case 1860:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111171860);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1880:
				orderActorWithRotToFactory(111372180, EnemyCeres, "Ceres_40", "M/Ceres", _pRot);
				break;
			case 1900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271900);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111272200, EnemyCeres, "Ceres_41", "M/Ceres", _pRot);
				break;
			case 1920:
				orderActorWithRotToFactory(111372220, EnemyCeres, "Ceres_42", "M/Ceres", _pRot);
				break;
			case 1950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111271950);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1960:
				orderActorWithRotToFactory(111372260, EnemyCeres, "Ceres_43", "M/Ceres", _pRot);
				break;
			case 2000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272000);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111372300, EnemyCeres, "Ceres_44", "M/Ceres", _pRot);
				break;
			case 2040:
				orderActorWithRotToFactory(111372340, EnemyCeres, "Ceres_45", "M/Ceres", _pRot);
				break;
			case 2050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272050);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2080:
				orderActorWithRotToFactory(111372380, EnemyCeres, "Ceres_46", "M/Ceres", _pRot);
				break;
			case 2100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372100);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472400, EnemyCeres, "Ceres_47", "M/Ceres", _pRot);
				break;
			case 2120:
				orderActorWithRotToFactory(111372420, EnemyCeres, "Ceres_48", "M/Ceres", _pRot);
				break;
			case 2130:
				orderActorWithRotToFactory(111472430, EnemyCeres, "Ceres_49", "M/Ceres", _pRot);
				break;
			case 2140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372140);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272150);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2160:
				orderActorWithRotToFactory(111372460, EnemyCeres, "Ceres_50", "M/Ceres", _pRot);
				orderActorWithRotToFactory(111472460, EnemyCeres, "Ceres_51", "M/Ceres", _pRot);
				break;
			case 2180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372180);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2190:
				orderActorWithRotToFactory(111472490, EnemyCeres, "Ceres_52", "M/Ceres", _pRot);
				break;
			case 2200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111272200);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 10000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111372500, EnemyCeres, "Ceres_53", "M/Ceres", _pRot);
				break;
			case 2220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372220);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472520, EnemyCeres, "Ceres_54", "M/Ceres", _pRot);
				break;
			case 2250:
				orderActorWithRotToFactory(111472550, EnemyCeres, "Ceres_55", "M/Ceres", _pRot);
				break;
			case 2260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372260);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2280:
				orderActorWithRotToFactory(111472580, EnemyCeres, "Ceres_56", "M/Ceres", _pRot);
				break;
			case 2300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372300);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2310:
				orderActorWithRotToFactory(111472610, EnemyCeres, "Ceres_57", "M/Ceres", _pRot);
				break;
			case 2340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372340);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472640, EnemyCeres, "Ceres_58", "M/Ceres", _pRot);
				break;
			case 2370:
				orderActorWithRotToFactory(111472670, EnemyCeres, "Ceres_59", "M/Ceres", _pRot);
				break;
			case 2380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372380);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472400);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472700, EnemyCeres, "Ceres_60", "M/Ceres", _pRot);
				orderActorWithRotToFactory(111572700, EnemyCeres, "Ceres_61", "M/Ceres", _pRot);
				break;
			case 2420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372420);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572720, EnemyCeres, "Ceres_62", "M/Ceres", _pRot);
				break;
			case 2430:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472430);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472730, EnemyCeres, "Ceres_63", "M/Ceres", _pRot);
				break;
			case 2440:
				orderActorWithRotToFactory(111572740, EnemyCeres, "Ceres_64", "M/Ceres", _pRot);
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
				orderActorWithRotToFactory(111472760, EnemyCeres, "Ceres_65", "M/Ceres", _pRot);
				orderActorWithRotToFactory(111572760, EnemyCeres, "Ceres_66", "M/Ceres", _pRot);
				break;
			case 2480:
				orderActorWithRotToFactory(111572780, EnemyCeres, "Ceres_67", "M/Ceres", _pRot);
				break;
			case 2490:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472490);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111472790, EnemyCeres, "Ceres_68", "M/Ceres", _pRot);
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111372500);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 200000;
				pActor->_veloBegin = 11000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572800, EnemyCeres, "Ceres_69", "M/Ceres", _pRot);
				break;
			case 2520:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472520);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572820, EnemyCeres, "Ceres_70", "M/Ceres", _pRot);
				break;
			case 2540:
				orderActorWithRotToFactory(111572840, EnemyCeres, "Ceres_71", "M/Ceres", _pRot);
				break;
			case 2550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472550);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2560:
				orderActorWithRotToFactory(111572860, EnemyCeres, "Ceres_72", "M/Ceres", _pRot);
				break;
			case 2580:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472580);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572880, EnemyCeres, "Ceres_73", "M/Ceres", _pRot);
				break;
			case 2600:
				orderActorWithRotToFactory(111572900, EnemyCeres, "Ceres_74", "M/Ceres", _pRot);
				break;
			case 2610:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472610);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2620:
				orderActorWithRotToFactory(111572920, EnemyCeres, "Ceres_75", "M/Ceres", _pRot);
				break;
			case 2640:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472640);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111572940, EnemyCeres, "Ceres_76", "M/Ceres", _pRot);
				break;
			case 2660:
				orderActorWithRotToFactory(111572960, EnemyCeres, "Ceres_77", "M/Ceres", _pRot);
				break;
			case 2670:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472670);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2680:
				orderActorWithRotToFactory(111572980, EnemyCeres, "Ceres_78", "M/Ceres", _pRot);
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
				orderActorWithRotToFactory(111573000, EnemyCeres, "Ceres_79", "M/Ceres", _pRot);
				break;
			case 2720:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572720);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573020, EnemyCeres, "Ceres_80", "M/Ceres", _pRot);
				break;
			case 2730:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472730);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572740);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573040, EnemyCeres, "Ceres_81", "M/Ceres", _pRot);
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
				orderActorWithRotToFactory(111573060, EnemyCeres, "Ceres_82", "M/Ceres", _pRot);
				break;
			case 2780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572780);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573080, EnemyCeres, "Ceres_83", "M/Ceres", _pRot);
				break;
			case 2790:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111472790);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 12000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 2800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572800);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 300000;
				pActor->_veloBegin = 13000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorWithRotToFactory(111573100, EnemyCeres, "Ceres_84", "M/Ceres", _pRot);
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
			case 2840:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572840);
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
			case 2880:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572880);
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
			case 2920:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572920);
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
			case 2960:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111572960);
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
			case 3000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573000);
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
			case 3040:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573040);
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
			case 3080:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(111573080);
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

    if (_dwFrame == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->tear());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_dwFrame == 1) {
    //		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
    //		this->inact(); //GameMainSceneが解除してくれる
    //	}
}

Stage01MainScene::~Stage01MainScene() {
}
