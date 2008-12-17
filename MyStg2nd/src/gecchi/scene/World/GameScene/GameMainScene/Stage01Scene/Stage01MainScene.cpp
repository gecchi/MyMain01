#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,101,701,901,1501,1701,2301,2501,3301,4101,4901,5701,6501,7301};
	_paFrame_NextEvent = new DWORD[14];
	for (int i = 0; i < 14; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1096101", FormationCeres002, "F_Ceres002_1", "Ceres");
	orderActorFactory("ID1096901", FormationCeres002, "F_Ceres002_2", "Ceres");
	orderActorFactory("ID10961701", FormationCeres002, "F_Ceres002_3", "Ceres");
	orderActorFactory("ID10962501", FormationCeres002, "F_Ceres002_4", "Ceres");
	orderActorFactory("ID10963301", FormationCeres002, "F_Ceres002_5", "Ceres");
	orderActorFactory("ID10964101", FormationCeres002, "F_Ceres002_6", "Ceres");
	orderActorFactory("ID10964901", FormationCeres002, "F_Ceres002_7", "Ceres");
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
			case 701:
				orderActorFactory("ID10965701", FormationCeres002, "F_Ceres002_8", "Ceres");
				break;
			case 901:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096901"));
				break;
			case 1501:
				orderActorFactory("ID10966501", FormationCeres002, "F_Ceres002_9", "Ceres");
				break;
			case 1701:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961701"));
				break;
			case 2301:
				orderActorFactory("ID10967301", FormationCeres002, "F_Ceres002_10", "Ceres");
				break;
			case 2501:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962501"));
				break;
			case 3301:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963301"));
				break;
			case 4101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964101"));
				break;
			case 4901:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964901"));
				break;
			case 5701:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10965701"));
				break;
			case 6501:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10966501"));
				break;
			case 7301:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10967301"));
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
