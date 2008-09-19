#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,5,100,150,200,250,300,400,500,600};
	_paFrame_NextEvent = new DWORD[10];
	for (int i = 0; i < 10; i++) {
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
				MyFactory::orderActor("[104-6]5", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[105-6]100", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[105-6]150", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[105-6]200", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[105-6]250", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[105-6]300", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[106-6]300", MyFactory::createFormationJuno001First, (void*)(NEW int(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT*2)));
				MyFactory::orderActor("[108-6]400", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]500", MyFactory::createFormationJuno001, NULL);
				break;
			case 5:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[104-6]5"));
				break;
			case 100:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[105-6]100"));
				MyFactory::orderActor("[108-6]600", MyFactory::createFormationJuno001, NULL);
				break;
			case 150:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[105-6]150"));
				break;
			case 200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[105-6]200"));
				break;
			case 250:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[105-6]250"));
				break;
			case 300:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[105-6]300"));
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]300"));
				break;
			case 400:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]400"));
				break;
			case 500:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]500"));
				break;
			case 600:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]600"));
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
