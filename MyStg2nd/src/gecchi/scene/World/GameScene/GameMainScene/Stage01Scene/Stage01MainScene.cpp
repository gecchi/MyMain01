#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,300,600,900,1200,1500,1800,2100,2400,2700,3000};
	_paFrame_NextEvent = new DWORD[11];
	for (int i = 0; i < 11; i++) {
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
				orderActorFactory("1096300", FormationCeres002, "F_Ceres002_1", "pot");
				break;
			case 300:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("1096300"));
				orderActorFactory("1096600", FormationCeres002, "F_Ceres002_300", "ebi");
				break;
			case 600:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("1096600"));
				orderActorFactory("1096900", FormationCeres002, "F_Ceres002_600", "vic2");
				break;
			case 900:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("1096900"));
				orderActorFactory("10961200", FormationCeres002, "F_Ceres002_900", "pot");
				break;
			case 1200:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10961200"));
				orderActorFactory("10961500", FormationCeres002, "F_Ceres002_1200", "tamago");
				break;
			case 1500:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10961500"));
				orderActorFactory("10961800", FormationCeres002, "F_Ceres002_1500", "cakeBerry");
				break;
			case 1800:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10961800"));
				orderActorFactory("10962100", FormationCeres002, "F_Ceres002_1800", "Ceres");
				break;
			case 2100:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10962100"));
				orderActorFactory("10962400", FormationCeres002, "F_Ceres002_2100", "Ceres");
				break;
			case 2400:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10962400"));
				orderActorFactory("10962700", FormationCeres002, "F_Ceres002_2400", "Ceres");
				break;
			case 2700:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10962700"));
				orderActorFactory("10963000", FormationCeres002, "F_Ceres002_2700", "Ceres");
				break;
			case 3000:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("10963000"));
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
