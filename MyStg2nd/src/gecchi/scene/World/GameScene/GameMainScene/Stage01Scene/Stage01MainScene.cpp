#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,20,120,220,221,300,320,420,520,521,620,720,820,920,1020,1120,1220,1320,1420,1520,1620,1720,1820,1920,2020,2120,2220,2320,2420,2520,2620,2720,2820,2920};
	_paFrame_NextEvent = new DWORD[34];
	for (int i = 0; i < 34; i++) {
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
				break;
			case 20:
				MyFactory::orderActor("[108-6]520", MyFactory::createFormationJuno001, NULL);
				break;
			case 120:
				MyFactory::orderActor("[108-6]620", MyFactory::createFormationJuno001, NULL);
				break;
			case 220:
				MyFactory::orderActor("[108-6]720", MyFactory::createFormationJuno001, NULL);
				break;
			case 221:
				MyFactory::orderActor("[109-6]521", MyFactory::createFormationCeres001, NULL);
				break;
			case 300:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]300"));
				break;
			case 320:
				MyFactory::orderActor("[108-6]820", MyFactory::createFormationJuno001, NULL);
				break;
			case 420:
				MyFactory::orderActor("[108-6]920", MyFactory::createFormationJuno001, NULL);
				break;
			case 520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]520"));
				MyFactory::orderActor("[108-6]1020", MyFactory::createFormationJuno001, NULL);
				break;
			case 521:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]521"));
				break;
			case 620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]620"));
				MyFactory::orderActor("[108-6]1120", MyFactory::createFormationJuno001, NULL);
				break;
			case 720:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]720"));
				MyFactory::orderActor("[108-6]1220", MyFactory::createFormationJuno001, NULL);
				break;
			case 820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]820"));
				MyFactory::orderActor("[108-6]1320", MyFactory::createFormationJuno001, NULL);
				break;
			case 920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]920"));
				MyFactory::orderActor("[108-6]1420", MyFactory::createFormationJuno001, NULL);
				break;
			case 1020:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1020"));
				MyFactory::orderActor("[108-6]1520", MyFactory::createFormationJuno001, NULL);
				break;
			case 1120:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1120"));
				MyFactory::orderActor("[108-6]1620", MyFactory::createFormationJuno001, NULL);
				break;
			case 1220:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1220"));
				MyFactory::orderActor("[108-6]1720", MyFactory::createFormationJuno001, NULL);
				break;
			case 1320:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1320"));
				MyFactory::orderActor("[108-6]1820", MyFactory::createFormationJuno001, NULL);
				break;
			case 1420:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1420"));
				MyFactory::orderActor("[108-6]1920", MyFactory::createFormationJuno001, NULL);
				break;
			case 1520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1520"));
				MyFactory::orderActor("[108-6]2020", MyFactory::createFormationJuno001, NULL);
				break;
			case 1620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1620"));
				MyFactory::orderActor("[108-6]2120", MyFactory::createFormationJuno001, NULL);
				break;
			case 1720:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1720"));
				MyFactory::orderActor("[108-6]2220", MyFactory::createFormationJuno001, NULL);
				break;
			case 1820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1820"));
				MyFactory::orderActor("[108-6]2320", MyFactory::createFormationJuno001, NULL);
				break;
			case 1920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1920"));
				MyFactory::orderActor("[108-6]2420", MyFactory::createFormationJuno001, NULL);
				break;
			case 2020:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2020"));
				MyFactory::orderActor("[108-6]2520", MyFactory::createFormationJuno001, NULL);
				break;
			case 2120:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2120"));
				MyFactory::orderActor("[108-6]2620", MyFactory::createFormationJuno001, NULL);
				break;
			case 2220:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2220"));
				MyFactory::orderActor("[108-6]2720", MyFactory::createFormationJuno001, NULL);
				break;
			case 2320:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2320"));
				MyFactory::orderActor("[108-6]2820", MyFactory::createFormationJuno001, NULL);
				break;
			case 2420:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2420"));
				MyFactory::orderActor("[108-6]2920", MyFactory::createFormationJuno001, NULL);
				break;
			case 2520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2520"));
				break;
			case 2620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2620"));
				break;
			case 2720:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2720"));
				break;
			case 2820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2820"));
				break;
			case 2920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2920"));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {
		_TRACE_("Stage01MainScene::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
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
