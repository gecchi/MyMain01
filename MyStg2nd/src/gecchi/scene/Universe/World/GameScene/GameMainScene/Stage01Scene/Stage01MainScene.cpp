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
	DWORD dw[] = {1,100,600,1100,1600,2100,2600,3100,3600,4100,4600,5100,5600,6100,6600,7100,7600,8100,8600,9100,9600,10100,10600,11100,11600,12100,12600,13100,13600,14100,14600,15100,15600,16100,16600,17100,17600,18100,18600,19100,19600,20100,20600,21100,21600,22100,22600,23100,23600};
	_paFrame_NextEvent = new DWORD[49];
	for (int i = 0; i < 49; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorToFactory(21027100, EnemyAstraea, "Astraea_1");
	orderActorToFactory(21027600, EnemyAstraea, "Astraea_2");
	orderActorToFactory(210271100, EnemyAstraea, "Astraea_3");
	orderActorToFactory(210271600, EnemyAstraea, "Astraea_4");
	orderActorToFactory(210272100, EnemyAstraea, "Astraea_5");
	orderActorToFactory(210272600, EnemyAstraea, "Astraea_6");
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
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210273100, EnemyAstraea, "Astraea_7");
				break;
			case 600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(21027600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210273600, EnemyAstraea, "Astraea_8");
				break;
			case 1100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210271100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210274100, EnemyAstraea, "Astraea_9");
				break;
			case 1600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210271600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210274600, EnemyAstraea, "Astraea_10");
				break;
			case 2100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210272100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210275100, EnemyAstraea, "Astraea_11");
				break;
			case 2600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210272600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210275600, EnemyAstraea, "Astraea_12");
				break;
			case 3100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210273100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210276100, EnemyAstraea, "Astraea_13");
				break;
			case 3600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210273600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210276600, EnemyAstraea, "Astraea_14");
				break;
			case 4100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210274100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210277100, EnemyAstraea, "Astraea_15");
				break;
			case 4600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210274600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210277600, EnemyAstraea, "Astraea_16");
				break;
			case 5100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210275100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210278100, EnemyAstraea, "Astraea_17");
				break;
			case 5600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210275600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210278600, EnemyAstraea, "Astraea_18");
				break;
			case 6100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210276100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210279100, EnemyAstraea, "Astraea_19");
				break;
			case 6600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210276600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(210279600, EnemyAstraea, "Astraea_20");
				break;
			case 7100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210277100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102710100, EnemyAstraea, "Astraea_21");
				break;
			case 7600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210277600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102710600, EnemyAstraea, "Astraea_22");
				break;
			case 8100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210278100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102711100, EnemyAstraea, "Astraea_23");
				break;
			case 8600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210278600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102711600, EnemyAstraea, "Astraea_24");
				break;
			case 9100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210279100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102712100, EnemyAstraea, "Astraea_25");
				break;
			case 9600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(210279600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102712600, EnemyAstraea, "Astraea_26");
				break;
			case 10100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102710100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102713100, EnemyAstraea, "Astraea_27");
				break;
			case 10600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102710600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102713600, EnemyAstraea, "Astraea_28");
				break;
			case 11100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102711100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102714100, EnemyAstraea, "Astraea_29");
				break;
			case 11600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102711600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102714600, EnemyAstraea, "Astraea_30");
				break;
			case 12100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102712100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102715100, EnemyAstraea, "Astraea_31");
				break;
			case 12600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102712600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102715600, EnemyAstraea, "Astraea_32");
				break;
			case 13100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102713100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102716100, EnemyAstraea, "Astraea_33");
				break;
			case 13600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102713600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102716600, EnemyAstraea, "Astraea_34");
				break;
			case 14100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102714100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102717100, EnemyAstraea, "Astraea_35");
				break;
			case 14600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102714600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102717600, EnemyAstraea, "Astraea_36");
				break;
			case 15100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102715100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102718100, EnemyAstraea, "Astraea_37");
				break;
			case 15600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102715600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102718600, EnemyAstraea, "Astraea_38");
				break;
			case 16100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102716100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102719100, EnemyAstraea, "Astraea_39");
				break;
			case 16600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102716600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102719600, EnemyAstraea, "Astraea_40");
				break;
			case 17100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102717100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102720100, EnemyAstraea, "Astraea_41");
				break;
			case 17600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102717600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102720600, EnemyAstraea, "Astraea_42");
				break;
			case 18100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102718100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102721100, EnemyAstraea, "Astraea_43");
				break;
			case 18600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102718600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102721600, EnemyAstraea, "Astraea_44");
				break;
			case 19100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102719100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102722100, EnemyAstraea, "Astraea_45");
				break;
			case 19600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102719600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102722600, EnemyAstraea, "Astraea_46");
				break;
			case 20100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102720100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102723100, EnemyAstraea, "Astraea_47");
				break;
			case 20600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102720600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				orderActorToFactory(2102723600, EnemyAstraea, "Astraea_48");
				break;
			case 21100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102721100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 21600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102721600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 22100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102722100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 22600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102722600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 23100:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102723100);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			case 23600:
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(2102723600);
				getLordActor()->addSubGroup(pActor);
				pActor->_X = 8000000;
				pActor->_Z = -200000;
				pActor->_Y = -300000;
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 49-1 ? _iCnt_Event+1 : _iCnt_Event);
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
