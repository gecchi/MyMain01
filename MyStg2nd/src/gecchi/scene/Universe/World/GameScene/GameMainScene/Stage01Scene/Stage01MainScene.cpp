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
	DWORD dw[] = {1,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6900,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000};
	_paFrame_NextEvent = new DWORD[81];
	for (int i = 0; i < 81; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11077300, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11377600, EnemyCeres, "Ceres_2");
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
			case 100:
				orderActorToFactory(11097700, EnemyAstraea, "Astraea_3");
				orderActorToFactory(11377700, EnemyCeres, "Ceres_4");
				break;
			case 200:
				orderActorToFactory(11377800, EnemyCeres, "Ceres_5");
				break;
			case 300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(11377900, EnemyCeres, "Ceres_6");
				break;
			case 400:
				orderActorToFactory(113771000, EnemyCeres, "Ceres_7");
				break;
			case 500:
				orderActorToFactory(111171100, EnemyAstraea, "Astraea_8");
				orderActorToFactory(113771100, EnemyCeres, "Ceres_9");
				break;
			case 600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771200, EnemyCeres, "Ceres_10");
				break;
			case 700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11097700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771300, EnemyCeres, "Ceres_11");
				break;
			case 800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771400, EnemyCeres, "Ceres_12");
				break;
			case 900:
				orderActorToFactory(111371500, EnemyAstraea, "Astraea_13");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771500, EnemyCeres, "Ceres_14");
				break;
			case 1000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771600, EnemyCeres, "Ceres_15");
				break;
			case 1100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111171100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771700, EnemyCeres, "Ceres_16");
				break;
			case 1200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771800, EnemyCeres, "Ceres_17");
				break;
			case 1300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771900, EnemyCeres, "Ceres_18");
				break;
			case 1400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772000, EnemyCeres, "Ceres_19");
				break;
			case 1500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111371500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				orderActorToFactory(111672100, EnemyAstraea, "Astraea_20");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772100, EnemyCeres, "Ceres_21");
				break;
			case 1600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772200, EnemyCeres, "Ceres_22");
				break;
			case 1700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772300, EnemyCeres, "Ceres_23");
				break;
			case 1800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772400, EnemyCeres, "Ceres_24");
				break;
			case 1900:
				orderActorToFactory(111872500, EnemyAstraea, "Astraea_25");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772500, EnemyCeres, "Ceres_26");
				break;
			case 2000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772600, EnemyCeres, "Ceres_27");
				break;
			case 2100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111672100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772700, EnemyCeres, "Ceres_28");
				break;
			case 2200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772800, EnemyCeres, "Ceres_29");
				break;
			case 2300:
				orderActorToFactory(112072900, EnemyAstraea, "Astraea_30");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772900, EnemyCeres, "Ceres_31");
				break;
			case 2400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773000, EnemyCeres, "Ceres_32");
				break;
			case 2500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111872500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773100, EnemyCeres, "Ceres_33");
				break;
			case 2600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773200, EnemyCeres, "Ceres_34");
				break;
			case 2700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773300, EnemyCeres, "Ceres_35");
				break;
			case 2800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773400, EnemyCeres, "Ceres_36");
				break;
			case 2900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112072900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773500, EnemyCeres, "Ceres_37");
				break;
			case 3000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773600, EnemyCeres, "Ceres_38");
				break;
			case 3100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773700, EnemyCeres, "Ceres_39");
				break;
			case 3200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773800, EnemyCeres, "Ceres_40");
				break;
			case 3300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773900, EnemyCeres, "Ceres_41");
				break;
			case 3400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774000, EnemyCeres, "Ceres_42");
				break;
			case 3500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774100, EnemyCeres, "Ceres_43");
				break;
			case 3600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774200, EnemyCeres, "Ceres_44");
				break;
			case 3700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774300, EnemyCeres, "Ceres_45");
				break;
			case 3800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774400, EnemyCeres, "Ceres_46");
				break;
			case 3900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774500, EnemyCeres, "Ceres_47");
				break;
			case 4000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774600, EnemyCeres, "Ceres_48");
				break;
			case 4100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774700, EnemyCeres, "Ceres_49");
				break;
			case 4200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774800, EnemyCeres, "Ceres_50");
				break;
			case 4300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774900, EnemyCeres, "Ceres_51");
				break;
			case 4400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775000, EnemyCeres, "Ceres_52");
				break;
			case 4500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775100, EnemyCeres, "Ceres_53");
				break;
			case 4600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775200, EnemyCeres, "Ceres_54");
				break;
			case 4700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775300, EnemyCeres, "Ceres_55");
				break;
			case 4800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775400, EnemyCeres, "Ceres_56");
				break;
			case 4900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775500, EnemyCeres, "Ceres_57");
				break;
			case 5000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775600, EnemyCeres, "Ceres_58");
				break;
			case 5100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775700, EnemyCeres, "Ceres_59");
				break;
			case 5200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775800, EnemyCeres, "Ceres_60");
				break;
			case 5300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775900, EnemyCeres, "Ceres_61");
				break;
			case 5400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776000, EnemyCeres, "Ceres_62");
				break;
			case 5500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776100, EnemyCeres, "Ceres_63");
				break;
			case 5600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776200, EnemyCeres, "Ceres_64");
				break;
			case 5700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776300, EnemyCeres, "Ceres_65");
				break;
			case 5800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776400, EnemyCeres, "Ceres_66");
				break;
			case 5900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776500, EnemyCeres, "Ceres_67");
				break;
			case 6000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776600, EnemyCeres, "Ceres_68");
				break;
			case 6100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776700, EnemyCeres, "Ceres_69");
				break;
			case 6200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776800, EnemyCeres, "Ceres_70");
				break;
			case 6300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113776900, EnemyCeres, "Ceres_71");
				break;
			case 6400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777000, EnemyCeres, "Ceres_72");
				break;
			case 6500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777100, EnemyCeres, "Ceres_73");
				break;
			case 6600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777200, EnemyCeres, "Ceres_74");
				break;
			case 6700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777300, EnemyCeres, "Ceres_75");
				break;
			case 6800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777400, EnemyCeres, "Ceres_76");
				break;
			case 6900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113776900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777500, EnemyCeres, "Ceres_77");
				break;
			case 7000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777600, EnemyCeres, "Ceres_78");
				break;
			case 7100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777700, EnemyCeres, "Ceres_79");
				break;
			case 7200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777800, EnemyCeres, "Ceres_80");
				break;
			case 7300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113777900, EnemyCeres, "Ceres_81");
				break;
			case 7400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113778000, EnemyCeres, "Ceres_82");
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
			case 7600:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
			case 7800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113777800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
