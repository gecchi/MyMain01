#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen01 start ～ end はマクロにより自動生成されたコードです。
	// gen01 start
	DWORD dw[] = {1,101,221,341,461,581,701,821,941,1061,1181,1301,1421,1541,1661,1781,1901,2021,2141,2261,2381,2501,2621,2741,2861,2981,3101,3221,3341,3461,3581,3701,3821,3941,4061,4181,4301,4421,4541,4661,4781,4901};
	_paFrame_NextEvent = new DWORD[42];
	for (int i = 0; i < 42; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1096101", FormationCeres002, "F_Ceres002_1", "Ceres");
	orderActorFactory("ID1096221", FormationCeres002, "F_Ceres002_2", "Ceres");
	orderActorFactory("ID1096341", FormationCeres002, "F_Ceres002_3", "Ceres");
	orderActorFactory("ID1096461", FormationCeres002, "F_Ceres002_4", "Ceres");
	orderActorFactory("ID1096581", FormationCeres002, "F_Ceres002_5", "Ceres");
	orderActorFactory("ID1096701", FormationCeres002, "F_Ceres002_6", "Ceres");
	orderActorFactory("ID1096821", FormationCeres002, "F_Ceres002_7", "Ceres");
	orderActorFactory("ID1096941", FormationCeres002, "F_Ceres002_8", "Ceres");
	orderActorFactory("ID10961061", FormationCeres002, "F_Ceres002_9", "Ceres");
	orderActorFactory("ID10961181", FormationCeres002, "F_Ceres002_10", "Ceres");
	orderActorFactory("ID10961301", FormationCeres002, "F_Ceres002_11", "Ceres");
	orderActorFactory("ID10961421", FormationCeres002, "F_Ceres002_12", "Ceres");
	orderActorFactory("ID10961541", FormationCeres002, "F_Ceres002_13", "Ceres");
	orderActorFactory("ID10961661", FormationCeres002, "F_Ceres002_14", "Ceres");
	orderActorFactory("ID10961781", FormationCeres002, "F_Ceres002_15", "Ceres");
	orderActorFactory("ID10961901", FormationCeres002, "F_Ceres002_16", "Ceres");
	orderActorFactory("ID10962021", FormationCeres002, "F_Ceres002_17", "Ceres");
	orderActorFactory("ID10962141", FormationCeres002, "F_Ceres002_18", "Ceres");
	orderActorFactory("ID10962261", FormationCeres002, "F_Ceres002_19", "Ceres");
	orderActorFactory("ID10962381", FormationCeres002, "F_Ceres002_20", "Ceres");
	orderActorFactory("ID10962501", FormationCeres002, "F_Ceres002_21", "Ceres");
	orderActorFactory("ID10962621", FormationCeres002, "F_Ceres002_22", "Ceres");
	orderActorFactory("ID10962741", FormationCeres002, "F_Ceres002_23", "Ceres");
	orderActorFactory("ID10962861", FormationCeres002, "F_Ceres002_24", "Ceres");
	orderActorFactory("ID10962981", FormationCeres002, "F_Ceres002_25", "Ceres");
	orderActorFactory("ID10963101", FormationCeres002, "F_Ceres002_26", "Ceres");
	orderActorFactory("ID10963221", FormationCeres002, "F_Ceres002_27", "Ceres");
	orderActorFactory("ID10963341", FormationCeres002, "F_Ceres002_28", "Ceres");
	orderActorFactory("ID10963461", FormationCeres002, "F_Ceres002_29", "Ceres");
	orderActorFactory("ID10963581", FormationCeres002, "F_Ceres002_30", "Ceres");
	orderActorFactory("ID10963701", FormationCeres002, "F_Ceres002_31", "Ceres");
	orderActorFactory("ID10963821", FormationCeres002, "F_Ceres002_32", "Ceres");
	orderActorFactory("ID10963941", FormationCeres002, "F_Ceres002_33", "Ceres");
	orderActorFactory("ID10964061", FormationCeres002, "F_Ceres002_34", "Ceres");
	orderActorFactory("ID10964181", FormationCeres002, "F_Ceres002_35", "Ceres");
	orderActorFactory("ID10964301", FormationCeres002, "F_Ceres002_36", "Ceres");
	orderActorFactory("ID10964421", FormationCeres002, "F_Ceres002_37", "Ceres");
	orderActorFactory("ID10964541", FormationCeres002, "F_Ceres002_38", "Ceres");
	orderActorFactory("ID10964661", FormationCeres002, "F_Ceres002_39", "Ceres");
	orderActorFactory("ID10964781", FormationCeres002, "F_Ceres002_40", "Ceres");
	orderActorFactory("ID10964901", FormationCeres002, "F_Ceres002_41", "Ceres");
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
			case 221:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096221"));
				break;
			case 341:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096341"));
				break;
			case 461:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096461"));
				break;
			case 581:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096581"));
				break;
			case 701:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096701"));
				break;
			case 821:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096821"));
				break;
			case 941:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096941"));
				break;
			case 1061:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961061"));
				break;
			case 1181:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961181"));
				break;
			case 1301:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961301"));
				break;
			case 1421:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961421"));
				break;
			case 1541:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961541"));
				break;
			case 1661:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961661"));
				break;
			case 1781:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961781"));
				break;
			case 1901:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10961901"));
				break;
			case 2021:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962021"));
				break;
			case 2141:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962141"));
				break;
			case 2261:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962261"));
				break;
			case 2381:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962381"));
				break;
			case 2501:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962501"));
				break;
			case 2621:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962621"));
				break;
			case 2741:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962741"));
				break;
			case 2861:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962861"));
				break;
			case 2981:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10962981"));
				break;
			case 3101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963101"));
				break;
			case 3221:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963221"));
				break;
			case 3341:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963341"));
				break;
			case 3461:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963461"));
				break;
			case 3581:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963581"));
				break;
			case 3701:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963701"));
				break;
			case 3821:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963821"));
				break;
			case 3941:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10963941"));
				break;
			case 4061:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964061"));
				break;
			case 4181:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964181"));
				break;
			case 4301:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964301"));
				break;
			case 4421:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964421"));
				break;
			case 4541:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964541"));
				break;
			case 4661:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964661"));
				break;
			case 4781:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964781"));
				break;
			case 4901:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID10964901"));
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
