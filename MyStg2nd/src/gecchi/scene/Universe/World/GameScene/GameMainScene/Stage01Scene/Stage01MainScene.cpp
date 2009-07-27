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
	DWORD dw[] = {1,10,20,60,100,140,160,180,200,220,250,260,280,300,340,350,380,400,420,450,460,500,510,520,530,540,550,560,570,580,590,600,610,620,660,700,740,780,820,860,900};
	_paFrame_NextEvent = new DWORD[41];
	for (int i = 0; i < 41; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11077500, EnemyAstraea, "Astraea_2");
	orderActorToFactory(11087510, EnemyAstraea, "Astraea_3");
	orderActorToFactory(11097520, EnemyAstraea, "Astraea_4");
	orderActorToFactory(11107530, EnemyAstraea, "Astraea_5");
	orderActorToFactory(11117540, EnemyAstraea, "Astraea_6");
	orderActorToFactory(11127550, EnemyAstraea, "Astraea_7");
	orderActorToFactory(11137560, EnemyAstraea, "Astraea_8");
	orderActorToFactory(11147570, EnemyAstraea, "Astraea_9");
	orderActorToFactory(11157580, EnemyAstraea, "Astraea_10");
	orderActorToFactory(11167590, EnemyAstraea, "Astraea_11");
	orderActorToFactory(11177600, EnemyAstraea, "Astraea_12");
	orderActorToFactory(11217500, EnemyAstraea, "Astraea_13");
	orderActorToFactory(11227510, EnemyAstraea, "Astraea_14");
	orderActorToFactory(11237520, EnemyAstraea, "Astraea_15");
	orderActorToFactory(11247530, EnemyAstraea, "Astraea_16");
	orderActorToFactory(11257540, EnemyAstraea, "Astraea_17");
	orderActorToFactory(11267550, EnemyAstraea, "Astraea_18");
	orderActorToFactory(11277560, EnemyAstraea, "Astraea_19");
	orderActorToFactory(11287570, EnemyAstraea, "Astraea_20");
	orderActorToFactory(11297580, EnemyAstraea, "Astraea_21");
	orderActorToFactory(11307590, EnemyAstraea, "Astraea_22");
	orderActorToFactory(11317600, EnemyAstraea, "Astraea_23");
	orderActorToFactory(11497100, EnemyCeres, "Ceres_24");
	orderActorToFactory(11497160, EnemyCeres, "Ceres_25");
	orderActorToFactory(11497220, EnemyCeres, "Ceres_26");
	orderActorToFactory(11497280, EnemyCeres, "Ceres_27");
	orderActorToFactory(11497340, EnemyCeres, "Ceres_28");
	orderActorToFactory(11497400, EnemyCeres, "Ceres_29");
	orderActorToFactory(11497460, EnemyCeres, "Ceres_30");
	orderActorToFactory(11507200, EnemyCeres, "Ceres_31");
	orderActorToFactory(11507250, EnemyCeres, "Ceres_32");
	orderActorToFactory(11507300, EnemyCeres, "Ceres_33");
	orderActorToFactory(11507350, EnemyCeres, "Ceres_34");
	orderActorToFactory(11507400, EnemyCeres, "Ceres_35");
	orderActorToFactory(11507450, EnemyCeres, "Ceres_36");
	orderActorToFactory(11507500, EnemyCeres, "Ceres_37");
	orderActorToFactory(11507550, EnemyCeres, "Ceres_38");
	orderActorToFactory(11507600, EnemyCeres, "Ceres_39");
	orderActorToFactory(11517300, EnemyCeres, "Ceres_40");
	orderActorToFactory(11517340, EnemyCeres, "Ceres_41");
	orderActorToFactory(11517380, EnemyCeres, "Ceres_42");
	orderActorToFactory(11517420, EnemyCeres, "Ceres_43");
	orderActorToFactory(11517460, EnemyCeres, "Ceres_44");
	orderActorToFactory(11517500, EnemyCeres, "Ceres_45");
	orderActorToFactory(11517540, EnemyCeres, "Ceres_46");
	orderActorToFactory(11517580, EnemyCeres, "Ceres_47");
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
				orderActorToFactory(11187610, EnemyAstraea, "Astraea_48");
				orderActorToFactory(11327610, EnemyAstraea, "Astraea_49");
				break;
			case 20:
				orderActorToFactory(11197620, EnemyAstraea, "Astraea_50");
				orderActorToFactory(11337620, EnemyAstraea, "Astraea_51");
				orderActorToFactory(11517620, EnemyCeres, "Ceres_52");
				break;
			case 60:
				orderActorToFactory(11517660, EnemyCeres, "Ceres_53");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11517700, EnemyCeres, "Ceres_54");
				break;
			case 140:
				orderActorToFactory(11517740, EnemyCeres, "Ceres_55");
				break;
			case 160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497160);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 180:
				orderActorToFactory(11517780, EnemyCeres, "Ceres_56");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497220);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11517820, EnemyCeres, "Ceres_57");
				break;
			case 250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 260:
				orderActorToFactory(11517860, EnemyCeres, "Ceres_58");
				break;
			case 280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497280);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11517900, EnemyCeres, "Ceres_59");
				break;
			case 340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517380);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517420);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11497460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11217500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 510:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11087510);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11227510);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				break;
			case 520:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11097520);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11237520);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -200000;
				}
				break;
			case 530:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11107530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11247530);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -150000;
				}
				break;
			case 540:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11117540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11257540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 550:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11127550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11267550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 560:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11137560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -0;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11277560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -0;
				}
				break;
			case 570:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11147570);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 50000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11287570);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 50000;
				}
				break;
			case 580:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11157580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11297580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 590:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11167590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 150000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11307590);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				break;
			case 600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11177600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11317600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 200000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11507600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 610:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11187610);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 250000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11327610);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 250000;
				}
				break;
			case 620:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11197620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11337620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517660);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517740);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517780);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 820:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517820);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 860:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517860);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11517900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
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
