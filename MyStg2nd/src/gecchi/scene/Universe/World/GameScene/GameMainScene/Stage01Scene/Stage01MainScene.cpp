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
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
    // gen01 start
	DWORD dw[] = {1,510,1510,2510,3510,4510,5510,6510,7510,8510,9510,10510,11510,12510,13510,14510,15510,16510,17510,18510,19510};
	_paFrame_NextEvent = new DWORD[21];
	for (int i = 0; i < 21; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(11257510, FormationIris002, "F002_Iris_1");
	orderActorToFactory(112571510, FormationIris002, "F002_Iris_2");
	orderActorToFactory(112572510, FormationIris002, "F002_Iris_3");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // gen02 start
	if (_frame_of_active == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_frame_of_active) {
			case 1:
				break;
			case 510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(11257510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112573510, FormationIris002, "F002_Iris_4");
				break;
			case 1510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112571510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112574510, FormationIris002, "F002_Iris_5");
				break;
			case 2510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112572510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112575510, FormationIris002, "F002_Iris_6");
				break;
			case 3510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112573510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112576510, FormationIris002, "F002_Iris_7");
				break;
			case 4510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112574510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112577510, FormationIris002, "F002_Iris_8");
				break;
			case 5510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112575510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112578510, FormationIris002, "F002_Iris_9");
				break;
			case 6510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112576510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(112579510, FormationIris002, "F002_Iris_10");
				break;
			case 7510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112577510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125710510, FormationIris002, "F002_Iris_11");
				break;
			case 8510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112578510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125711510, FormationIris002, "F002_Iris_12");
				break;
			case 9510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(112579510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125712510, FormationIris002, "F002_Iris_13");
				break;
			case 10510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125710510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125713510, FormationIris002, "F002_Iris_14");
				break;
			case 11510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125711510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125714510, FormationIris002, "F002_Iris_15");
				break;
			case 12510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125712510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125715510, FormationIris002, "F002_Iris_16");
				break;
			case 13510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125713510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125716510, FormationIris002, "F002_Iris_17");
				break;
			case 14510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125714510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125717510, FormationIris002, "F002_Iris_18");
				break;
			case 15510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125715510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125718510, FormationIris002, "F002_Iris_19");
				break;
			case 16510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125716510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				orderActorToFactory(1125719510, FormationIris002, "F002_Iris_20");
				break;
			case 17510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125717510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 18510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125718510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			case 19510:
				{
				FormationIris002* pFormationActor = (FormationIris002*)obtainActorFromFactory(1125719510);
				getLordActor()->addSubGroup(pFormationActor);
				}
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
    // gen02 end

    if (_frame_of_active== 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (_frame_of_active== 1) {
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
