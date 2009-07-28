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
	DWORD dw[] = {1,10,20,60,100,140,160,180,200,220,250,260,280,300,340,350,380,400,420,450,460,500,520,540,550,560,580,600,620,660,700,740,780,820,860,900};
	_paFrame_NextEvent = new DWORD[36];
	for (int i = 0; i < 36; i++) {
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
	orderActorToFactory(11387200, EnemyCeres, "Ceres_21");
	orderActorToFactory(11387250, EnemyCeres, "Ceres_22");
	orderActorToFactory(11387300, EnemyCeres, "Ceres_23");
	orderActorToFactory(11387350, EnemyCeres, "Ceres_24");
	orderActorToFactory(11387400, EnemyCeres, "Ceres_25");
	orderActorToFactory(11387450, EnemyCeres, "Ceres_26");
	orderActorToFactory(11387500, EnemyCeres, "Ceres_27");
	orderActorToFactory(11387550, EnemyCeres, "Ceres_28");
	orderActorToFactory(11387600, EnemyCeres, "Ceres_29");
	orderActorToFactory(11397300, EnemyCeres, "Ceres_30");
	orderActorToFactory(11397340, EnemyCeres, "Ceres_31");
	orderActorToFactory(11397380, EnemyCeres, "Ceres_32");
	orderActorToFactory(11397420, EnemyCeres, "Ceres_33");
	orderActorToFactory(11397460, EnemyCeres, "Ceres_34");
	orderActorToFactory(11397500, EnemyCeres, "Ceres_35");
	orderActorToFactory(11397540, EnemyCeres, "Ceres_36");
	orderActorToFactory(11397580, EnemyCeres, "Ceres_37");
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
				orderActorToFactory(11137620, EnemyAstraea, "Astraea_38");
				orderActorToFactory(11217620, EnemyAstraea, "Astraea_39");
				orderActorToFactory(11397620, EnemyCeres, "Ceres_40");
				break;
			case 60:
				orderActorToFactory(11397660, EnemyCeres, "Ceres_41");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11397700, EnemyCeres, "Ceres_42");
				break;
			case 140:
				orderActorToFactory(11397740, EnemyCeres, "Ceres_43");
				break;
			case 160:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377160);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 180:
				orderActorToFactory(11397780, EnemyCeres, "Ceres_44");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 220:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377220);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11397820, EnemyCeres, "Ceres_45");
				break;
			case 250:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387250);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 260:
				orderActorToFactory(11397860, EnemyCeres, "Ceres_46");
				break;
			case 280:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377280);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11397900, EnemyCeres, "Ceres_47");
				break;
			case 340:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397340);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 350:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387350);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 380:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397380);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 420:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397420);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 450:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387450);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 460:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -150000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397460);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11157500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11387500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 0;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -200000;
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397540);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = -0;
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397580);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 200000;
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
				pActor->_X = 800000;
				pActor->_Z = 200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397620);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 660:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397660);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 740:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397740);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 780:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397780);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 820:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397820);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 860:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397860);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = 150000;
				pActor->_veloBegin = 9000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11397900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
