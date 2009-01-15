#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage01MainScene::Stage01MainScene(string prm_name) : GgafDx9LibStg::DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,101,601,1101,1601,2101,2601,3101,3601,4101,4601};
	_paFrame_NextEvent = new DWORD[11];
	for (int i = 0; i < 11; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1096101", FormationCeres002, "F_Ceres002_1", "Ceres");
	orderActorFactory("ID1096601", FormationCeres002, "F_Ceres002_2", "Ceres");
	orderActorFactory("ID10961101", FormationCeres002, "F_Ceres002_3", "Ceres");
	orderActorFactory("ID10961601", FormationCeres002, "F_Ceres002_4", "Ceres");
	orderActorFactory("ID10962101", FormationCeres002, "F_Ceres002_5", "Ceres");
	orderActorFactory("ID10962601", FormationCeres002, "F_Ceres002_6", "Ceres");
	orderActorFactory("ID10963101", FormationCeres002, "F_Ceres002_7", "Ceres");
	orderActorFactory("ID10963601", FormationCeres002, "F_Ceres002_8", "Ceres");
	orderActorFactory("ID10964101", FormationCeres002, "F_Ceres002_9", "Ceres");
	orderActorFactory("ID10964601", FormationCeres002, "F_Ceres002_10", "Ceres");
	// gen01 end

	stopImmediately(); //GameMainSceneが解除してくれる
}

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
	// 以下の gen02 start ～ end はマクロにより自動生成されたコードです。
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				break;
			case 101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096101"));
				break;
			case 601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096601"));
				break;
			case 1101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961101"));
				break;
			case 1601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961601"));
				break;
			case 2101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962101"));
				break;
			case 2601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962601"));
				break;
			case 3101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963101"));
				break;
			case 3601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963601"));
				break;
			case 4101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964101"));
				break;
			case 4601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964601"));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {

		_TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
		// 共通シーンを配下に移動
		addSubLast(GameGlobal::_pSceneCommon->tear());

	}


}

void Stage01MainScene::processFinal() {
//	if (_dwFrame == 1) {
//		_TRACE_("Stage01MainScene::processFinally 私はいきなり停止します。GameMainSceneが解除してくれるはずー");
//		this->declareStop(); //GameMainSceneが解除してくれる
//	}
}

Stage01MainScene::~Stage01MainScene() {
}
