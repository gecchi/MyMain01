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
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pRot->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->accept(KIND_ENEMY, _pRot);

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,10};
	_paFrame_NextEvent = new DWORD[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(1105610, EnemyAstraea, "Astraea_1");
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
