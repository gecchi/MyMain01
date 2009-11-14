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
	DWORD dw[] = {1,10,20,100,200,300,400,500,520,540,560,580,600,620,700,800,900,1000};
	_paFrame_NextEvent = new DWORD[18];
	for (int i = 0; i < 18; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
	orderActorToFactory(11077500, EnemyAstraea, "Astraea_2");
	orderActorToFactory(11097540, EnemyAstraea, "Astraea_3");
	orderActorToFactory(11117580, EnemyAstraea, "Astraea_4");
	orderActorToFactory(11167520, EnemyAstraea, "Astraea_5");
	orderActorToFactory(11187560, EnemyAstraea, "Astraea_6");
	orderActorToFactory(11207600, EnemyAstraea, "Astraea_7");
	orderActorToFactory(11377100, EnemyCeres, "Ceres_8");
	orderActorToFactory(11377200, EnemyCeres, "Ceres_9");
	orderActorToFactory(11377300, EnemyCeres, "Ceres_10");
	orderActorToFactory(11377400, EnemyCeres, "Ceres_11");
	orderActorToFactory(11377500, EnemyCeres, "Ceres_12");
	orderActorToFactory(11377600, EnemyCeres, "Ceres_13");
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
				orderActorToFactory(11137620, EnemyAstraea, "Astraea_14");
				break;
			case 100:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377100);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11377700, EnemyCeres, "Ceres_15");
				break;
			case 200:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377200);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11377800, EnemyCeres, "Ceres_16");
				break;
			case 300:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377300);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(11377900, EnemyCeres, "Ceres_17");
				break;
			case 400:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377400);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				orderActorToFactory(113771000, EnemyCeres, "Ceres_18");
				break;
			case 500:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11077500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 800000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377500);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 520:
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
				break;
			case 560:
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
				break;
			case 600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11207600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_X = 900000;
				pActor->_Z = 200000;
				pActor->_Y = 150000;
				}
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377600);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
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
				break;
			case 700:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377700);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 800:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377800);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 900:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(11377900);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
				pActor->_Z = -1500000;
				pActor->_Y_turn = -250000;
				pActor->_veloBegin = 8000;
				getLordActor()->accept(KIND_ENEMY, pActor);
				}
				break;
			case 1000:
				{
				EnemyCeres* pActor = (EnemyCeres*)obtainActorFromFactory(113771000);  getLordActor()->accept(KIND_ENEMY_BODY,  pActor);
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
