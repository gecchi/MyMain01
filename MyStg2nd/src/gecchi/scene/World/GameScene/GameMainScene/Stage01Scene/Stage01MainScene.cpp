#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,101,201,301,401,501,601,701,801,901};
	_paFrame_NextEvent = new DWORD[10];
	for (int i = 0; i < 10; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1096101", FormationCeres002, "F_Ceres002_1", "Ceres");
	orderActorFactory("ID1096201", FormationCeres002, "F_Ceres002_2", "Ceres");
	orderActorFactory("ID1096301", FormationCeres002, "F_Ceres002_3", "Ceres");
	orderActorFactory("ID1096401", FormationCeres002, "F_Ceres002_4", "Ceres");
	orderActorFactory("ID1096501", FormationCeres002, "F_Ceres002_5", "Ceres");
	orderActorFactory("ID1096601", FormationCeres002, "F_Ceres002_6", "Ceres");
	orderActorFactory("ID1096701", FormationCeres002, "F_Ceres002_7", "Ceres");
	orderActorFactory("ID1096801", FormationCeres002, "F_Ceres002_8", "Ceres");
	orderActorFactory("ID1096901", FormationCeres002, "F_Ceres002_9", "Ceres");
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
			case 201:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096201"));
				break;
			case 301:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096301"));
				break;
			case 401:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096401"));
				break;
			case 501:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096501"));
				break;
			case 601:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096601"));
				break;
			case 701:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096701"));
				break;
			case 801:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096801"));
				break;
			case 901:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096901"));
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
