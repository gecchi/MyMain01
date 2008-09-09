#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,40,140,200,260,320,380,440,500,560,620,680,740,800,840,860,900,920,960,980,1020,1040,1080,1100,1140,1160,1200,1220,1260,1280,1320,1340,1380,1400,1440,1460,1500,1520,1560,1580,1620,1640,1680,1700,1740,1760,1800,1820,1860,1880,1920,1940,1980,2000,2040,2060,2100,2120,2160,2180,2220,2240,2280,2300,2340,2400,2460,2520,2580,2640,2700,2760,2820,2880,2940,3000};
	_paFrame_NextEvent = new DWORD[76];
	for (int i = 0; i < 76; i++) {
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
				MyFactory::orderActor("[109-6]40", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[110-6]200", MyFactory::createFormationCeres001, NULL);
				break;
			case 40:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]40"));
				break;
			case 140:
				MyFactory::orderActor("[106-6]840", MyFactory::createFormationJuno001First, (void*)(NEW int(GGAFDX9_PROPERTY(SCREEN_WIDTH)*LEN_UNIT*2)));
				break;
			case 200:
				MyFactory::orderActor("[108-6]900", MyFactory::createFormationJuno001, NULL);
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[110-6]200"));
				break;
			case 260:
				MyFactory::orderActor("[108-6]960", MyFactory::createFormationJuno001, NULL);
				break;
			case 320:
				MyFactory::orderActor("[108-6]1020", MyFactory::createFormationJuno001, NULL);
				break;
			case 380:
				MyFactory::orderActor("[108-6]1080", MyFactory::createFormationJuno001, NULL);
				break;
			case 440:
				MyFactory::orderActor("[108-6]1140", MyFactory::createFormationJuno001, NULL);
				break;
			case 500:
				MyFactory::orderActor("[108-6]1200", MyFactory::createFormationJuno001, NULL);
				break;
			case 560:
				MyFactory::orderActor("[108-6]1260", MyFactory::createFormationJuno001, NULL);
				break;
			case 620:
				MyFactory::orderActor("[108-6]1320", MyFactory::createFormationJuno001, NULL);
				break;
			case 680:
				MyFactory::orderActor("[108-6]1380", MyFactory::createFormationJuno001, NULL);
				break;
			case 740:
				MyFactory::orderActor("[108-6]1440", MyFactory::createFormationJuno001, NULL);
				break;
			case 800:
				MyFactory::orderActor("[108-6]1500", MyFactory::createFormationJuno001, NULL);
				break;
			case 840:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]840"));
				break;
			case 860:
				MyFactory::orderActor("[108-6]1560", MyFactory::createFormationJuno001, NULL);
				break;
			case 900:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]900"));
				break;
			case 920:
				MyFactory::orderActor("[108-6]1620", MyFactory::createFormationJuno001, NULL);
				break;
			case 960:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]960"));
				break;
			case 980:
				MyFactory::orderActor("[108-6]1680", MyFactory::createFormationJuno001, NULL);
				break;
			case 1020:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1020"));
				break;
			case 1040:
				MyFactory::orderActor("[108-6]1740", MyFactory::createFormationJuno001, NULL);
				break;
			case 1080:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1080"));
				break;
			case 1100:
				MyFactory::orderActor("[108-6]1800", MyFactory::createFormationJuno001, NULL);
				break;
			case 1140:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1140"));
				break;
			case 1160:
				MyFactory::orderActor("[108-6]1860", MyFactory::createFormationJuno001, NULL);
				break;
			case 1200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1200"));
				break;
			case 1220:
				MyFactory::orderActor("[108-6]1920", MyFactory::createFormationJuno001, NULL);
				break;
			case 1260:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1260"));
				break;
			case 1280:
				MyFactory::orderActor("[108-6]1980", MyFactory::createFormationJuno001, NULL);
				break;
			case 1320:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1320"));
				break;
			case 1340:
				MyFactory::orderActor("[108-6]2040", MyFactory::createFormationJuno001, NULL);
				break;
			case 1380:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1380"));
				break;
			case 1400:
				MyFactory::orderActor("[108-6]2100", MyFactory::createFormationJuno001, NULL);
				break;
			case 1440:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1440"));
				break;
			case 1460:
				MyFactory::orderActor("[108-6]2160", MyFactory::createFormationJuno001, NULL);
				break;
			case 1500:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1500"));
				break;
			case 1520:
				MyFactory::orderActor("[108-6]2220", MyFactory::createFormationJuno001, NULL);
				break;
			case 1560:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1560"));
				break;
			case 1580:
				MyFactory::orderActor("[108-6]2280", MyFactory::createFormationJuno001, NULL);
				break;
			case 1620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1620"));
				break;
			case 1640:
				MyFactory::orderActor("[108-6]2340", MyFactory::createFormationJuno001, NULL);
				break;
			case 1680:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1680"));
				break;
			case 1700:
				MyFactory::orderActor("[108-6]2400", MyFactory::createFormationJuno001, NULL);
				break;
			case 1740:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1740"));
				break;
			case 1760:
				MyFactory::orderActor("[108-6]2460", MyFactory::createFormationJuno001, NULL);
				break;
			case 1800:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1800"));
				break;
			case 1820:
				MyFactory::orderActor("[108-6]2520", MyFactory::createFormationJuno001, NULL);
				break;
			case 1860:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1860"));
				break;
			case 1880:
				MyFactory::orderActor("[108-6]2580", MyFactory::createFormationJuno001, NULL);
				break;
			case 1920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1920"));
				break;
			case 1940:
				MyFactory::orderActor("[108-6]2640", MyFactory::createFormationJuno001, NULL);
				break;
			case 1980:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1980"));
				break;
			case 2000:
				MyFactory::orderActor("[108-6]2700", MyFactory::createFormationJuno001, NULL);
				break;
			case 2040:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2040"));
				break;
			case 2060:
				MyFactory::orderActor("[108-6]2760", MyFactory::createFormationJuno001, NULL);
				break;
			case 2100:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2100"));
				break;
			case 2120:
				MyFactory::orderActor("[108-6]2820", MyFactory::createFormationJuno001, NULL);
				break;
			case 2160:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2160"));
				break;
			case 2180:
				MyFactory::orderActor("[108-6]2880", MyFactory::createFormationJuno001, NULL);
				break;
			case 2220:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2220"));
				break;
			case 2240:
				MyFactory::orderActor("[108-6]2940", MyFactory::createFormationJuno001, NULL);
				break;
			case 2280:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2280"));
				break;
			case 2300:
				MyFactory::orderActor("[108-6]3000", MyFactory::createFormationJuno001, NULL);
				break;
			case 2340:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2340"));
				break;
			case 2400:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2400"));
				break;
			case 2460:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2460"));
				break;
			case 2520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2520"));
				break;
			case 2580:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2580"));
				break;
			case 2640:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2640"));
				break;
			case 2700:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2700"));
				break;
			case 2760:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2760"));
				break;
			case 2820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2820"));
				break;
			case 2880:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2880"));
				break;
			case 2940:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2940"));
				break;
			case 3000:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]3000"));
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
