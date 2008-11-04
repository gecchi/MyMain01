#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,20,300,520,600,900,1200,1500,1800,2100,2400,2700,3000};
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
	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				MyFactory::orderActor("[106-6]300", MyFactory::createFormationJuno001First, (void*)(NEW int(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT*2)));
				MyFactory::orderActor("[109-6]300", MyFactory::createFormationCeres002, NULL);
				break;
			case 20:
				MyFactory::orderActor("[108-6]520", MyFactory::createFormationJuno001, NULL);
				break;
			case 300:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]300"));
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]300"));
				MyFactory::orderActor("[109-6]600", MyFactory::createFormationCeres002, NULL);
				break;
			case 520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]520"));
				break;
			case 600:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]600"));
				MyFactory::orderActor("[109-6]900", MyFactory::createFormationCeres002, NULL);
				break;
			case 900:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]900"));
				MyFactory::orderActor("[109-6]1200", MyFactory::createFormationCeres002, NULL);
				break;
			case 1200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]1200"));
				MyFactory::orderActor("[109-6]1500", MyFactory::createFormationCeres002, NULL);
				break;
			case 1500:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]1500"));
				MyFactory::orderActor("[109-6]1800", MyFactory::createFormationCeres002, NULL);
				break;
			case 1800:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]1800"));
				MyFactory::orderActor("[109-6]2100", MyFactory::createFormationCeres002, NULL);
				break;
			case 2100:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]2100"));
				MyFactory::orderActor("[109-6]2400", MyFactory::createFormationCeres002, NULL);
				break;
			case 2400:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]2400"));
				MyFactory::orderActor("[109-6]2700", MyFactory::createFormationCeres002, NULL);
				break;
			case 2700:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]2700"));
				MyFactory::orderActor("[109-6]3000", MyFactory::createFormationCeres002, NULL);
				break;
			case 3000:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]3000"));
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
