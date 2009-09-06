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
	DWORD dw[] = {1,10,20,50,100,150,160,200,220,250,280,300,340,380,400,420,460,500,520,540,550,560,580,600,620,650,660,700,740,750,780,800,820,850,860,900,940,980,1020,1060,1100,1140,1180,1220,1260,1300,1340,1380,1420,1460,1500};
	_paFrame_NextEvent = new DWORD[51];
	for (int i = 0; i < 51; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11077500, EnemyAstraea, "Astraea_2");
	orderActorToFactory(11087520, EnemyAstraea, "Astraea_3");
	orderActorToFactory(11097540, EnemyAstraea, "Astraea_4");
	orderActorToFactory(11107560, EnemyAstraea, "Astraea_5");
	orderActorToFactory(11117580, EnemyAstraea, "Astraea_6");
	orderActorToFactory(11127600, EnemyAstraea, "Astraea_7");
	orderActorToFactory(11157500, EnemyAstraea, "Astraea_8");
	orderActorToFactory(11167520, EnemyAstraea, "Astraea_9");
	orderActorToFactory(11177540, EnemyAstraea, "Astraea_10");
	orderActorToFactory(11187560, EnemyAstraea, "Astraea_11");
	orderActorToFactory(11197580, EnemyAstraea, "Astraea_12");
	orderActorToFactory(11207600, EnemyAstraea, "Astraea_13");
	orderActorToFactory(11377100, EnemyCeres, "Ceres_14");
	orderActorToFactory(11377160, EnemyCeres, "Ceres_15");
	orderActorToFactory(11377220, EnemyCeres, "Ceres_16");
	orderActorToFactory(11377280, EnemyCeres, "Ceres_17");
	orderActorToFactory(11377340, EnemyCeres, "Ceres_18");
	orderActorToFactory(11377400, EnemyCeres, "Ceres_19");
	orderActorToFactory(11377460, EnemyCeres, "Ceres_20");
	orderActorToFactory(11387500, EnemyCeres, "Ceres_21");
	orderActorToFactory(11387550, EnemyCeres, "Ceres_22");
	orderActorToFactory(11387600, EnemyCeres, "Ceres_23");
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
				break;
			case 20:
				orderActorToFactory(11137620, EnemyAstraea, "Astraea_24");
				orderActorToFactory(11217620, EnemyAstraea, "Astraea_25");
				break;
			case 50:
				orderActorToFactory(11387650, EnemyCeres, "Ceres_26");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11387700, EnemyCeres, "Ceres_27");
				break;
			case 150:
				orderActorToFactory(11387750, EnemyCeres, "Ceres_28");
				break;
			case 160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377160);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 200:
				orderActorToFactory(11387800, EnemyCeres, "Ceres_29");
				break;
			case 220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377220);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 250:
				orderActorToFactory(11387850, EnemyCeres, "Ceres_30");
				break;
			case 280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377280);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 300:
				orderActorToFactory(11387900, EnemyCeres, "Ceres_31");
				orderActorToFactory(11397900, EnemyCeres, "Ceres_32");
				break;
			case 340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11397940, EnemyCeres, "Ceres_33");
				break;
			case 380:
				orderActorToFactory(11397980, EnemyCeres, "Ceres_34");
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				orderActorToFactory(113971020, EnemyCeres, "Ceres_35");
				break;
			case 460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113971060, EnemyCeres, "Ceres_36");
				break;
			case 500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11157500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -350000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113971100, EnemyCeres, "Ceres_37");
				break;
			case 520:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11087520);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11167520);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				break;
			case 540:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11097540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11177540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -150000;
				}
				orderActorToFactory(113971140, EnemyCeres, "Ceres_38");
				break;
			case 550:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387550);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 560:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11107560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -0;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11187560);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				break;
			case 580:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11117580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11197580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 50000;
				}
				orderActorToFactory(113971180, EnemyCeres, "Ceres_39");
				break;
			case 600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11127600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 200000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11207600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 620:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11137620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11217620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 250000;
				}
				orderActorToFactory(113971220, EnemyCeres, "Ceres_40");
				break;
			case 650:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387650);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 660:
				orderActorToFactory(113971260, EnemyCeres, "Ceres_41");
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113971300, EnemyCeres, "Ceres_42");
				break;
			case 740:
				orderActorToFactory(113971340, EnemyCeres, "Ceres_43");
				break;
			case 750:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387750);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 780:
				orderActorToFactory(113971380, EnemyCeres, "Ceres_44");
				break;
			case 800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 820:
				orderActorToFactory(113971420, EnemyCeres, "Ceres_45");
				break;
			case 850:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387850);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 860:
				orderActorToFactory(113971460, EnemyCeres, "Ceres_46");
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113971500, EnemyCeres, "Ceres_47");
				break;
			case 940:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397940);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 980:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397980);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1020:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971020);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1060:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971060);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1140:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971140);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1180:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971180);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971220);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1260:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971260);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971380);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971420);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113971500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 250000;
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
