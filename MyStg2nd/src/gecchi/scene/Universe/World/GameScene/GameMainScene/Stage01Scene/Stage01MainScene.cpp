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
	DWORD dw[] = {1,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1550,1600,1650,1700,1750,1800,1850,1900,1950,2000,2050,2100,2150,2200,2250,2300,2350,2400,2450,2500,2550,2600,2650,2700,2750,2800,2850,2900,2950,3000,3050,3100,3150,3200,3250,3300,3350,3400,3450,3500,3550,3600,3650,3700,3750,3800,3850,3900,3950,4000,4050,4100,4150,4200,4250,4300,4350,4400,4450,4500,4550,4600,4650,4700,4750,4800,4850,4900,4950,5000,5050,5100,5150,5200,5250,5300,5350,5400,5450,5500,5550,5600,5650,5700,5750,5800,5850,5900,5950,6000,6050,6100,6150,6200,6250,6300,6350,6400,6450,6500,6550,6600,6650,6700,6750,6800,6850,6900,6950,7000,7050,7100,7150,7200,7250,7300,7350,7400,7450,7500,7550,7600,7650,7700,7750,7800,7850,7900,7950,8000};
	_paFrame_NextEvent = new DWORD[161];
	for (int i = 0; i < 161; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11377600, EnemyCeres, "Ceres_1");
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
			case 50:
				orderActorToFactory(11377650, EnemyCeres, "Ceres_2");
				break;
			case 100:
				orderActorToFactory(11377700, EnemyCeres, "Ceres_3");
				break;
			case 150:
				orderActorToFactory(11377750, EnemyCeres, "Ceres_4");
				break;
			case 200:
				orderActorToFactory(11377800, EnemyCeres, "Ceres_5");
				break;
			case 250:
				orderActorToFactory(11377850, EnemyCeres, "Ceres_6");
				break;
			case 300:
				orderActorToFactory(11377900, EnemyCeres, "Ceres_7");
				break;
			case 350:
				orderActorToFactory(11377950, EnemyCeres, "Ceres_8");
				break;
			case 400:
				orderActorToFactory(113771000, EnemyCeres, "Ceres_9");
				break;
			case 450:
				orderActorToFactory(113771050, EnemyCeres, "Ceres_10");
				break;
			case 500:
				orderActorToFactory(113771100, EnemyCeres, "Ceres_11");
				break;
			case 550:
				orderActorToFactory(113771150, EnemyCeres, "Ceres_12");
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771200, EnemyCeres, "Ceres_13");
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771250, EnemyCeres, "Ceres_14");
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771300, EnemyCeres, "Ceres_15");
				break;
			case 750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771350, EnemyCeres, "Ceres_16");
				break;
			case 800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771400, EnemyCeres, "Ceres_17");
				break;
			case 850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771450, EnemyCeres, "Ceres_18");
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771500, EnemyCeres, "Ceres_19");
				break;
			case 950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771550, EnemyCeres, "Ceres_20");
				break;
			case 1000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771600, EnemyCeres, "Ceres_21");
				break;
			case 1050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771650, EnemyCeres, "Ceres_22");
				break;
			case 1100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771700, EnemyCeres, "Ceres_23");
				break;
			case 1150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771750, EnemyCeres, "Ceres_24");
				break;
			case 1200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771800, EnemyCeres, "Ceres_25");
				break;
			case 1250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771850, EnemyCeres, "Ceres_26");
				break;
			case 1300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771900, EnemyCeres, "Ceres_27");
				break;
			case 1350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771950, EnemyCeres, "Ceres_28");
				break;
			case 1400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772000, EnemyCeres, "Ceres_29");
				break;
			case 1450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772050, EnemyCeres, "Ceres_30");
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772100, EnemyCeres, "Ceres_31");
				break;
			case 1550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772150, EnemyCeres, "Ceres_32");
				break;
			case 1600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772200, EnemyCeres, "Ceres_33");
				break;
			case 1650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772250, EnemyCeres, "Ceres_34");
				break;
			case 1700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772300, EnemyCeres, "Ceres_35");
				break;
			case 1750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772350, EnemyCeres, "Ceres_36");
				break;
			case 1800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772400, EnemyCeres, "Ceres_37");
				break;
			case 1850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772450, EnemyCeres, "Ceres_38");
				break;
			case 1900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772500, EnemyCeres, "Ceres_39");
				break;
			case 1950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772550, EnemyCeres, "Ceres_40");
				break;
			case 2000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772600, EnemyCeres, "Ceres_41");
				break;
			case 2050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772650, EnemyCeres, "Ceres_42");
				break;
			case 2100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772700, EnemyCeres, "Ceres_43");
				break;
			case 2150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772750, EnemyCeres, "Ceres_44");
				break;
			case 2200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772800, EnemyCeres, "Ceres_45");
				break;
			case 2250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772850, EnemyCeres, "Ceres_46");
				break;
			case 2300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772900, EnemyCeres, "Ceres_47");
				break;
			case 2350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772950, EnemyCeres, "Ceres_48");
				break;
			case 2400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773000, EnemyCeres, "Ceres_49");
				break;
			case 2450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773050, EnemyCeres, "Ceres_50");
				break;
			case 2500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773100, EnemyCeres, "Ceres_51");
				break;
			case 2550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773150, EnemyCeres, "Ceres_52");
				break;
			case 2600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773200, EnemyCeres, "Ceres_53");
				break;
			case 2650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773250, EnemyCeres, "Ceres_54");
				break;
			case 2700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773300, EnemyCeres, "Ceres_55");
				break;
			case 2750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773350, EnemyCeres, "Ceres_56");
				break;
			case 2800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773400, EnemyCeres, "Ceres_57");
				break;
			case 2850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773450, EnemyCeres, "Ceres_58");
				break;
			case 2900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773500, EnemyCeres, "Ceres_59");
				break;
			case 2950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773550, EnemyCeres, "Ceres_60");
				break;
			case 3000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773600, EnemyCeres, "Ceres_61");
				break;
			case 3050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773650, EnemyCeres, "Ceres_62");
				break;
			case 3100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773700, EnemyCeres, "Ceres_63");
				break;
			case 3150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773750, EnemyCeres, "Ceres_64");
				break;
			case 3200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773800, EnemyCeres, "Ceres_65");
				break;
			case 3250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773850, EnemyCeres, "Ceres_66");
				break;
			case 3300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773900, EnemyCeres, "Ceres_67");
				break;
			case 3350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773950, EnemyCeres, "Ceres_68");
				break;
			case 3400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774000, EnemyCeres, "Ceres_69");
				break;
			case 3450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774050, EnemyCeres, "Ceres_70");
				break;
			case 3500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774100, EnemyCeres, "Ceres_71");
				break;
			case 3550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774150, EnemyCeres, "Ceres_72");
				break;
			case 3600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774200, EnemyCeres, "Ceres_73");
				break;
			case 3650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774250, EnemyCeres, "Ceres_74");
				break;
			case 3700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774300, EnemyCeres, "Ceres_75");
				break;
			case 3750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774350, EnemyCeres, "Ceres_76");
				break;
			case 3800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774400, EnemyCeres, "Ceres_77");
				break;
			case 3850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774450, EnemyCeres, "Ceres_78");
				break;
			case 3900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774500, EnemyCeres, "Ceres_79");
				break;
			case 3950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774550, EnemyCeres, "Ceres_80");
				break;
			case 4000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774600, EnemyCeres, "Ceres_81");
				break;
			case 4050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774650, EnemyCeres, "Ceres_82");
				break;
			case 4100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774700, EnemyCeres, "Ceres_83");
				break;
			case 4150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774750, EnemyCeres, "Ceres_84");
				break;
			case 4200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774800, EnemyCeres, "Ceres_85");
				break;
			case 4250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774850, EnemyCeres, "Ceres_86");
				break;
			case 4300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774900, EnemyCeres, "Ceres_87");
				break;
			case 4350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774950, EnemyCeres, "Ceres_88");
				break;
			case 4400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775000, EnemyCeres, "Ceres_89");
				break;
			case 4450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775050, EnemyCeres, "Ceres_90");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775100, EnemyCeres, "Ceres_91");
				break;
			case 4550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775150, EnemyCeres, "Ceres_92");
				break;
			case 4600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775200, EnemyCeres, "Ceres_93");
				break;
			case 4650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775250, EnemyCeres, "Ceres_94");
				break;
			case 4700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775300, EnemyCeres, "Ceres_95");
				break;
			case 4750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775350, EnemyCeres, "Ceres_96");
				break;
			case 4800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775400, EnemyCeres, "Ceres_97");
				break;
			case 4850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775450, EnemyCeres, "Ceres_98");
				break;
			case 4900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775500, EnemyCeres, "Ceres_99");
				break;
			case 4950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775550, EnemyCeres, "Ceres_100");
				break;
			case 5000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775600, EnemyCeres, "Ceres_101");
				break;
			case 5050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775650, EnemyCeres, "Ceres_102");
				break;
			case 5100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775700, EnemyCeres, "Ceres_103");
				break;
			case 5150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775750, EnemyCeres, "Ceres_104");
				break;
			case 5200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775800, EnemyCeres, "Ceres_105");
				break;
			case 5250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775850, EnemyCeres, "Ceres_106");
				break;
			case 5300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775900, EnemyCeres, "Ceres_107");
				break;
			case 5350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775950, EnemyCeres, "Ceres_108");
				break;
			case 5400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776000, EnemyCeres, "Ceres_109");
				break;
			case 5450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776050, EnemyCeres, "Ceres_110");
				break;
			case 5500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776100, EnemyCeres, "Ceres_111");
				break;
			case 5550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776150, EnemyCeres, "Ceres_112");
				break;
			case 5600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776200, EnemyCeres, "Ceres_113");
				break;
			case 5650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776250, EnemyCeres, "Ceres_114");
				break;
			case 5700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776300, EnemyCeres, "Ceres_115");
				break;
			case 5750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776350, EnemyCeres, "Ceres_116");
				break;
			case 5800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776400, EnemyCeres, "Ceres_117");
				break;
			case 5850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776450, EnemyCeres, "Ceres_118");
				break;
			case 5900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776500, EnemyCeres, "Ceres_119");
				break;
			case 5950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776550, EnemyCeres, "Ceres_120");
				break;
			case 6000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776600, EnemyCeres, "Ceres_121");
				break;
			case 6050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776650, EnemyCeres, "Ceres_122");
				break;
			case 6100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776700, EnemyCeres, "Ceres_123");
				break;
			case 6150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776750, EnemyCeres, "Ceres_124");
				break;
			case 6200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776800, EnemyCeres, "Ceres_125");
				break;
			case 6250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776850, EnemyCeres, "Ceres_126");
				break;
			case 6300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776900, EnemyCeres, "Ceres_127");
				break;
			case 6350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776950, EnemyCeres, "Ceres_128");
				break;
			case 6400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777000, EnemyCeres, "Ceres_129");
				break;
			case 6450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777050, EnemyCeres, "Ceres_130");
				break;
			case 6500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777100, EnemyCeres, "Ceres_131");
				break;
			case 6550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777150, EnemyCeres, "Ceres_132");
				break;
			case 6600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777200, EnemyCeres, "Ceres_133");
				break;
			case 6650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777250, EnemyCeres, "Ceres_134");
				break;
			case 6700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777300, EnemyCeres, "Ceres_135");
				break;
			case 6750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777350, EnemyCeres, "Ceres_136");
				break;
			case 6800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777400, EnemyCeres, "Ceres_137");
				break;
			case 6850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777450, EnemyCeres, "Ceres_138");
				break;
			case 6900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777500, EnemyCeres, "Ceres_139");
				break;
			case 6950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777550, EnemyCeres, "Ceres_140");
				break;
			case 7000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777600, EnemyCeres, "Ceres_141");
				break;
			case 7050:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777050);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777650, EnemyCeres, "Ceres_142");
				break;
			case 7100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777700, EnemyCeres, "Ceres_143");
				break;
			case 7150:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777150);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777750, EnemyCeres, "Ceres_144");
				break;
			case 7200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777800, EnemyCeres, "Ceres_145");
				break;
			case 7250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777850, EnemyCeres, "Ceres_146");
				break;
			case 7300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777900, EnemyCeres, "Ceres_147");
				break;
			case 7350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777950, EnemyCeres, "Ceres_148");
				break;
			case 7400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113778000, EnemyCeres, "Ceres_149");
				break;
			case 7450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 7950:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777950);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 8000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113778000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
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
