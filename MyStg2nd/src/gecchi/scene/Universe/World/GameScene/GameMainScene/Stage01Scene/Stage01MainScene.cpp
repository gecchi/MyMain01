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
	DWORD dw[] = {1,10,100,300,500,700,900,1100,1300,1500,1700,1900,2100,2300,2500,2700,2900,3100,3300,3500,3700,3900,4100,4300,4500,4700,4900,5100,5300,5500,5700,5900};
	_paFrame_NextEvent = new DWORD[32];
	for (int i = 0; i < 32; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11077100, EnemyAstraea, "Astraea_2");
	orderActorToFactory(11377300, EnemyCeres, "Ceres_3");
	orderActorToFactory(11377500, EnemyCeres, "Ceres_4");
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
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(11377700, EnemyCeres, "Ceres_5");
				break;
			case 300:
				orderActorToFactory(11097900, EnemyAstraea, "Astraea_6");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11377900, EnemyCeres, "Ceres_7");
				break;
			case 500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771100, EnemyCeres, "Ceres_8");
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771300, EnemyCeres, "Ceres_9");
				break;
			case 900:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11097900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771500, EnemyCeres, "Ceres_10");
				break;
			case 1100:
				orderActorToFactory(111171700, EnemyAstraea, "Astraea_11");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771700, EnemyCeres, "Ceres_12");
				break;
			case 1300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771900, EnemyCeres, "Ceres_13");
				break;
			case 1500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772100, EnemyCeres, "Ceres_14");
				break;
			case 1700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111171700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 100000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772300, EnemyCeres, "Ceres_15");
				break;
			case 1900:
				orderActorToFactory(111372500, EnemyAstraea, "Astraea_16");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772500, EnemyCeres, "Ceres_17");
				break;
			case 2100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772700, EnemyCeres, "Ceres_18");
				break;
			case 2300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113772900, EnemyCeres, "Ceres_19");
				break;
			case 2500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111372500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = 300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773100, EnemyCeres, "Ceres_20");
				break;
			case 2700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773300, EnemyCeres, "Ceres_21");
				break;
			case 2900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113772900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773500, EnemyCeres, "Ceres_22");
				break;
			case 3100:
				orderActorToFactory(111673700, EnemyAstraea, "Astraea_23");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773700, EnemyCeres, "Ceres_24");
				break;
			case 3300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113773900, EnemyCeres, "Ceres_25");
				break;
			case 3500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774100, EnemyCeres, "Ceres_26");
				break;
			case 3700:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111673700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -250000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774300, EnemyCeres, "Ceres_27");
				break;
			case 3900:
				orderActorToFactory(111874500, EnemyAstraea, "Astraea_28");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113773900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774500, EnemyCeres, "Ceres_29");
				break;
			case 4100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774700, EnemyCeres, "Ceres_30");
				break;
			case 4300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113774900, EnemyCeres, "Ceres_31");
				break;
			case 4500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(111874500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = -50000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775100, EnemyCeres, "Ceres_32");
				break;
			case 4700:
				orderActorToFactory(112075300, EnemyAstraea, "Astraea_33");
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775300, EnemyCeres, "Ceres_34");
				break;
			case 4900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113774900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775500, EnemyCeres, "Ceres_35");
				break;
			case 5100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775700, EnemyCeres, "Ceres_36");
				break;
			case 5300:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(112075300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113775900, EnemyCeres, "Ceres_37");
				break;
			case 5500:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 5700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 5900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113775900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
