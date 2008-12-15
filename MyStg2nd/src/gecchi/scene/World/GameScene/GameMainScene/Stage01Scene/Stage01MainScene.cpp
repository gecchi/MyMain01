#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,100,102,500,1000,1102,1400,1900,2102,2300,2800,3700,4102,4600,5500,6102,6400,7300};
	_paFrame_NextEvent = new DWORD[18];
	for (int i = 0; i < 18; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1116102", FormationVesta001, "F_Ceres001_7", "ebi");
	orderActorFactory("ID1096100", FormationCeres002, "F_Ceres002_1", "Ceres");
	orderActorFactory("ID10961000", FormationCeres002, "F_Ceres002_2", "Ceres");
	orderActorFactory("ID10961900", FormationCeres002, "F_Ceres002_3", "Ceres");
	orderActorFactory("ID10962800", FormationCeres002, "F_Ceres002_4", "Ceres");
	orderActorFactory("ID10963700", FormationCeres002, "F_Ceres002_5", "Ceres");
	orderActorFactory("ID10964600", FormationCeres002, "F_Ceres002_6", "Ceres");

	orderActorFactory("ID11162102", FormationVesta001, "F_Ceres001_8", "ebi");
	orderActorFactory("ID11164102", FormationVesta001, "F_Ceres001_9", "ebi");
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
			case 100:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096100"));
				break;
			case 102:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1116102"));
				break;
			case 500:
				orderActorFactory("ID10965500", FormationCeres002, "F_Ceres002_10", "Ceres");
				break;
			case 1000:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961000"));
				break;
			case 1102:
				orderActorFactory("ID11166102", FormationVesta001, "F_Ceres001_11", "ebi");
				break;
			case 1400:
				orderActorFactory("ID10966400", FormationCeres002, "F_Ceres002_12", "Ceres");
				break;
			case 1900:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961900"));
				break;
			case 2102:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID11162102"));
				break;
			case 2300:
				orderActorFactory("ID10967300", FormationCeres002, "F_Ceres002_13", "Ceres");
				break;
			case 2800:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962800"));
				break;
			case 3700:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963700"));
				break;
			case 4102:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID11164102"));
				break;
			case 4600:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964600"));
				break;
			case 5500:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10965500"));
				break;
			case 6102:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID11166102"));
				break;
			case 6400:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10966400"));
				break;
			case 7300:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10967300"));
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
