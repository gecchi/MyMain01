#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01MainScene::Stage01MainScene(const char* prm_name) : DefaultScene(prm_name) {

    _pDispatcher = NEW GgafActorDispatcher("RotEnemyMeshS001");
    EnemyMeshShot001* pEnemyMeshShot;
    for (int i = 0; i < 100; i++) {
        Sleep(1);
        pEnemyMeshShot = NEW EnemyMeshShot001("EnemyMeshShot");
        pEnemyMeshShot->inactivateTreeImmediately(); //最初非表示
        _pDispatcher->addSubLast(pEnemyMeshShot);
    }
    getLordActor()->addSubGroup(KIND_ENEMY_SHOT_CHOKI, _pDispatcher);

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen01 start
	DWORD dw[] = {1,100,3100,6100,9100,12100,15100,18100,21100};
	_paFrame_NextEvent = new DWORD[9];
	for (int i = 0; i < 9; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(21027100, EnemyAstraea, "Astraea_1");
    // gen01 end
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
    // 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
    // コード変更は「シーンCreater.xls」を開いて、そこから行うこと（整合性確保のため）。
    // gen02 start
	if (getPartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getPartFrame()) {
			case 1:
				break;
			case 100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(21027100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210273100, EnemyAstraea, "Astraea_2");
				break;
			case 3100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210273100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210276100, EnemyAstraea, "Astraea_3");
				break;
			case 6100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210276100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210279100, EnemyAstraea, "Astraea_4");
				break;
			case 9100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210279100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102712100, EnemyAstraea, "Astraea_5");
				break;
			case 12100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102712100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102715100, EnemyAstraea, "Astraea_6");
				break;
			case 15100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102715100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102718100, EnemyAstraea, "Astraea_7");
				break;
			case 18100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102718100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102721100, EnemyAstraea, "Astraea_8");
				break;
			case 21100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102721100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 9-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (getBehaveingFrame() == 2) {

        _TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
        // 共通シーンを配下に移動
        addSubLast(GameGlobal::_pSceneCommon->extract());

    }

}

void Stage01MainScene::processFinal() {
    //	if (getBehaveingFrame() == 1) {
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
