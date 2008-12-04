#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,100,700,900,1500,1700,2300,2500,3100,3300,3900,4100,4900};
	_paFrame_NextEvent = new DWORD[13];
	for (int i = 0; i < 13; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
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
				orderActorFactory("1096100", FormationCeres002, "F_Ceres002_1", "Ceres");
				orderActorFactory("1096900", FormationCeres002, "F_Ceres002_1", "Ceres");
				break;
			case 100:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("1096100"));
				break;
			case 700:
				orderActorFactory("10961700", FormationCeres002, "F_Ceres002_700", "Ceres");
				break;
			case 900:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("1096900"));
				break;
			case 1500:
				orderActorFactory("10962500", FormationCeres002, "F_Ceres002_1500", "Ceres");
				break;
			case 1700:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10961700"));
				break;
			case 2300:
				orderActorFactory("10963300", FormationCeres002, "F_Ceres002_2300", "Ceres");
				break;
			case 2500:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10962500"));
				break;
			case 3100:
				orderActorFactory("10964100", FormationCeres002, "F_Ceres002_3100", "Ceres");
				break;
			case 3300:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10963300"));
				break;
			case 3900:
				orderActorFactory("10964900", FormationCeres002, "F_Ceres002_3900", "Ceres");
				break;
			case 4100:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10964100"));
				break;
			case 4900:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10964900"));
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
