#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,40,140,200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1020,1040,1060,1080,1100,1120,1140,1160,1180,1200,1220,1240,1260,1280,1300,1320,1340,1360,1380,1400,1420,1440,1460,1480,1500,1520,1540,1560,1580,1600,1620,1640,1660,1680,1700,1720,1740,1760,1780,1800,1820,1840,1860,1880,1900,1920,1940,1960,1980,2000,2020,2040,2060,2080,2100,2120,2140,2160,2180,2200,2220,2240,2260,2280,2300,2320,2340,2360,2380,2400,2420,2440,2460,2480,2500,2520,2540,2560,2580,2600,2620,2640,2660,2680,2700,2720,2740,2760,2780,2800,2820,2840,2860,2880,2900,2920,2940,2960,2980,3000};
	_paFrame_NextEvent = new DWORD[144];
	for (int i = 0; i < 144; i++) {
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
			case 220:
				MyFactory::orderActor("[108-6]920", MyFactory::createFormationJuno001, NULL);
				break;
			case 240:
				MyFactory::orderActor("[108-6]940", MyFactory::createFormationJuno001, NULL);
				break;
			case 260:
				MyFactory::orderActor("[108-6]960", MyFactory::createFormationJuno001, NULL);
				break;
			case 280:
				MyFactory::orderActor("[108-6]980", MyFactory::createFormationJuno001, NULL);
				break;
			case 300:
				MyFactory::orderActor("[108-6]1000", MyFactory::createFormationJuno001, NULL);
				break;
			case 320:
				MyFactory::orderActor("[108-6]1020", MyFactory::createFormationJuno001, NULL);
				break;
			case 340:
				MyFactory::orderActor("[108-6]1040", MyFactory::createFormationJuno001, NULL);
				break;
			case 360:
				MyFactory::orderActor("[108-6]1060", MyFactory::createFormationJuno001, NULL);
				break;
			case 380:
				MyFactory::orderActor("[108-6]1080", MyFactory::createFormationJuno001, NULL);
				break;
			case 400:
				MyFactory::orderActor("[108-6]1100", MyFactory::createFormationJuno001, NULL);
				break;
			case 420:
				MyFactory::orderActor("[108-6]1120", MyFactory::createFormationJuno001, NULL);
				break;
			case 440:
				MyFactory::orderActor("[108-6]1140", MyFactory::createFormationJuno001, NULL);
				break;
			case 460:
				MyFactory::orderActor("[108-6]1160", MyFactory::createFormationJuno001, NULL);
				break;
			case 480:
				MyFactory::orderActor("[108-6]1180", MyFactory::createFormationJuno001, NULL);
				break;
			case 500:
				MyFactory::orderActor("[108-6]1200", MyFactory::createFormationJuno001, NULL);
				break;
			case 520:
				MyFactory::orderActor("[108-6]1220", MyFactory::createFormationJuno001, NULL);
				break;
			case 540:
				MyFactory::orderActor("[108-6]1240", MyFactory::createFormationJuno001, NULL);
				break;
			case 560:
				MyFactory::orderActor("[108-6]1260", MyFactory::createFormationJuno001, NULL);
				break;
			case 580:
				MyFactory::orderActor("[108-6]1280", MyFactory::createFormationJuno001, NULL);
				break;
			case 600:
				MyFactory::orderActor("[108-6]1300", MyFactory::createFormationJuno001, NULL);
				break;
			case 620:
				MyFactory::orderActor("[108-6]1320", MyFactory::createFormationJuno001, NULL);
				break;
			case 640:
				MyFactory::orderActor("[108-6]1340", MyFactory::createFormationJuno001, NULL);
				break;
			case 660:
				MyFactory::orderActor("[108-6]1360", MyFactory::createFormationJuno001, NULL);
				break;
			case 680:
				MyFactory::orderActor("[108-6]1380", MyFactory::createFormationJuno001, NULL);
				break;
			case 700:
				MyFactory::orderActor("[108-6]1400", MyFactory::createFormationJuno001, NULL);
				break;
			case 720:
				MyFactory::orderActor("[108-6]1420", MyFactory::createFormationJuno001, NULL);
				break;
			case 740:
				MyFactory::orderActor("[108-6]1440", MyFactory::createFormationJuno001, NULL);
				break;
			case 760:
				MyFactory::orderActor("[108-6]1460", MyFactory::createFormationJuno001, NULL);
				break;
			case 780:
				MyFactory::orderActor("[108-6]1480", MyFactory::createFormationJuno001, NULL);
				break;
			case 800:
				MyFactory::orderActor("[108-6]1500", MyFactory::createFormationJuno001, NULL);
				break;
			case 820:
				MyFactory::orderActor("[108-6]1520", MyFactory::createFormationJuno001, NULL);
				break;
			case 840:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]840"));
				MyFactory::orderActor("[108-6]1540", MyFactory::createFormationJuno001, NULL);
				break;
			case 860:
				MyFactory::orderActor("[108-6]1560", MyFactory::createFormationJuno001, NULL);
				break;
			case 880:
				MyFactory::orderActor("[108-6]1580", MyFactory::createFormationJuno001, NULL);
				break;
			case 900:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]900"));
				MyFactory::orderActor("[108-6]1600", MyFactory::createFormationJuno001, NULL);
				break;
			case 920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]920"));
				MyFactory::orderActor("[108-6]1620", MyFactory::createFormationJuno001, NULL);
				break;
			case 940:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]940"));
				MyFactory::orderActor("[108-6]1640", MyFactory::createFormationJuno001, NULL);
				break;
			case 960:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]960"));
				MyFactory::orderActor("[108-6]1660", MyFactory::createFormationJuno001, NULL);
				break;
			case 980:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]980"));
				MyFactory::orderActor("[108-6]1680", MyFactory::createFormationJuno001, NULL);
				break;
			case 1000:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1000"));
				MyFactory::orderActor("[108-6]1700", MyFactory::createFormationJuno001, NULL);
				break;
			case 1020:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1020"));
				MyFactory::orderActor("[108-6]1720", MyFactory::createFormationJuno001, NULL);
				break;
			case 1040:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1040"));
				MyFactory::orderActor("[108-6]1740", MyFactory::createFormationJuno001, NULL);
				break;
			case 1060:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1060"));
				MyFactory::orderActor("[108-6]1760", MyFactory::createFormationJuno001, NULL);
				break;
			case 1080:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1080"));
				MyFactory::orderActor("[108-6]1780", MyFactory::createFormationJuno001, NULL);
				break;
			case 1100:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1100"));
				MyFactory::orderActor("[108-6]1800", MyFactory::createFormationJuno001, NULL);
				break;
			case 1120:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1120"));
				MyFactory::orderActor("[108-6]1820", MyFactory::createFormationJuno001, NULL);
				break;
			case 1140:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1140"));
				MyFactory::orderActor("[108-6]1840", MyFactory::createFormationJuno001, NULL);
				break;
			case 1160:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1160"));
				MyFactory::orderActor("[108-6]1860", MyFactory::createFormationJuno001, NULL);
				break;
			case 1180:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1180"));
				MyFactory::orderActor("[108-6]1880", MyFactory::createFormationJuno001, NULL);
				break;
			case 1200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1200"));
				MyFactory::orderActor("[108-6]1900", MyFactory::createFormationJuno001, NULL);
				break;
			case 1220:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1220"));
				MyFactory::orderActor("[108-6]1920", MyFactory::createFormationJuno001, NULL);
				break;
			case 1240:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1240"));
				MyFactory::orderActor("[108-6]1940", MyFactory::createFormationJuno001, NULL);
				break;
			case 1260:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1260"));
				MyFactory::orderActor("[108-6]1960", MyFactory::createFormationJuno001, NULL);
				break;
			case 1280:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1280"));
				MyFactory::orderActor("[108-6]1980", MyFactory::createFormationJuno001, NULL);
				break;
			case 1300:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1300"));
				MyFactory::orderActor("[108-6]2000", MyFactory::createFormationJuno001, NULL);
				break;
			case 1320:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1320"));
				MyFactory::orderActor("[108-6]2020", MyFactory::createFormationJuno001, NULL);
				break;
			case 1340:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1340"));
				MyFactory::orderActor("[108-6]2040", MyFactory::createFormationJuno001, NULL);
				break;
			case 1360:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1360"));
				MyFactory::orderActor("[108-6]2060", MyFactory::createFormationJuno001, NULL);
				break;
			case 1380:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1380"));
				MyFactory::orderActor("[108-6]2080", MyFactory::createFormationJuno001, NULL);
				break;
			case 1400:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1400"));
				MyFactory::orderActor("[108-6]2100", MyFactory::createFormationJuno001, NULL);
				break;
			case 1420:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1420"));
				MyFactory::orderActor("[108-6]2120", MyFactory::createFormationJuno001, NULL);
				break;
			case 1440:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1440"));
				MyFactory::orderActor("[108-6]2140", MyFactory::createFormationJuno001, NULL);
				break;
			case 1460:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1460"));
				MyFactory::orderActor("[108-6]2160", MyFactory::createFormationJuno001, NULL);
				break;
			case 1480:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1480"));
				MyFactory::orderActor("[108-6]2180", MyFactory::createFormationJuno001, NULL);
				break;
			case 1500:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1500"));
				MyFactory::orderActor("[108-6]2200", MyFactory::createFormationJuno001, NULL);
				break;
			case 1520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1520"));
				MyFactory::orderActor("[108-6]2220", MyFactory::createFormationJuno001, NULL);
				break;
			case 1540:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1540"));
				MyFactory::orderActor("[108-6]2240", MyFactory::createFormationJuno001, NULL);
				break;
			case 1560:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1560"));
				MyFactory::orderActor("[108-6]2260", MyFactory::createFormationJuno001, NULL);
				break;
			case 1580:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1580"));
				MyFactory::orderActor("[108-6]2280", MyFactory::createFormationJuno001, NULL);
				break;
			case 1600:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1600"));
				MyFactory::orderActor("[108-6]2300", MyFactory::createFormationJuno001, NULL);
				break;
			case 1620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1620"));
				MyFactory::orderActor("[108-6]2320", MyFactory::createFormationJuno001, NULL);
				break;
			case 1640:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1640"));
				MyFactory::orderActor("[108-6]2340", MyFactory::createFormationJuno001, NULL);
				break;
			case 1660:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1660"));
				MyFactory::orderActor("[108-6]2360", MyFactory::createFormationJuno001, NULL);
				break;
			case 1680:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1680"));
				MyFactory::orderActor("[108-6]2380", MyFactory::createFormationJuno001, NULL);
				break;
			case 1700:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1700"));
				MyFactory::orderActor("[108-6]2400", MyFactory::createFormationJuno001, NULL);
				break;
			case 1720:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1720"));
				MyFactory::orderActor("[108-6]2420", MyFactory::createFormationJuno001, NULL);
				break;
			case 1740:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1740"));
				MyFactory::orderActor("[108-6]2440", MyFactory::createFormationJuno001, NULL);
				break;
			case 1760:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1760"));
				MyFactory::orderActor("[108-6]2460", MyFactory::createFormationJuno001, NULL);
				break;
			case 1780:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1780"));
				MyFactory::orderActor("[108-6]2480", MyFactory::createFormationJuno001, NULL);
				break;
			case 1800:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1800"));
				MyFactory::orderActor("[108-6]2500", MyFactory::createFormationJuno001, NULL);
				break;
			case 1820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1820"));
				MyFactory::orderActor("[108-6]2520", MyFactory::createFormationJuno001, NULL);
				break;
			case 1840:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1840"));
				MyFactory::orderActor("[108-6]2540", MyFactory::createFormationJuno001, NULL);
				break;
			case 1860:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1860"));
				MyFactory::orderActor("[108-6]2560", MyFactory::createFormationJuno001, NULL);
				break;
			case 1880:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1880"));
				MyFactory::orderActor("[108-6]2580", MyFactory::createFormationJuno001, NULL);
				break;
			case 1900:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1900"));
				MyFactory::orderActor("[108-6]2600", MyFactory::createFormationJuno001, NULL);
				break;
			case 1920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1920"));
				MyFactory::orderActor("[108-6]2620", MyFactory::createFormationJuno001, NULL);
				break;
			case 1940:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1940"));
				MyFactory::orderActor("[108-6]2640", MyFactory::createFormationJuno001, NULL);
				break;
			case 1960:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1960"));
				MyFactory::orderActor("[108-6]2660", MyFactory::createFormationJuno001, NULL);
				break;
			case 1980:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1980"));
				MyFactory::orderActor("[108-6]2680", MyFactory::createFormationJuno001, NULL);
				break;
			case 2000:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2000"));
				MyFactory::orderActor("[108-6]2700", MyFactory::createFormationJuno001, NULL);
				break;
			case 2020:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2020"));
				MyFactory::orderActor("[108-6]2720", MyFactory::createFormationJuno001, NULL);
				break;
			case 2040:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2040"));
				MyFactory::orderActor("[108-6]2740", MyFactory::createFormationJuno001, NULL);
				break;
			case 2060:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2060"));
				MyFactory::orderActor("[108-6]2760", MyFactory::createFormationJuno001, NULL);
				break;
			case 2080:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2080"));
				MyFactory::orderActor("[108-6]2780", MyFactory::createFormationJuno001, NULL);
				break;
			case 2100:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2100"));
				MyFactory::orderActor("[108-6]2800", MyFactory::createFormationJuno001, NULL);
				break;
			case 2120:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2120"));
				MyFactory::orderActor("[108-6]2820", MyFactory::createFormationJuno001, NULL);
				break;
			case 2140:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2140"));
				MyFactory::orderActor("[108-6]2840", MyFactory::createFormationJuno001, NULL);
				break;
			case 2160:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2160"));
				MyFactory::orderActor("[108-6]2860", MyFactory::createFormationJuno001, NULL);
				break;
			case 2180:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2180"));
				MyFactory::orderActor("[108-6]2880", MyFactory::createFormationJuno001, NULL);
				break;
			case 2200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2200"));
				MyFactory::orderActor("[108-6]2900", MyFactory::createFormationJuno001, NULL);
				break;
			case 2220:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2220"));
				MyFactory::orderActor("[108-6]2920", MyFactory::createFormationJuno001, NULL);
				break;
			case 2240:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2240"));
				MyFactory::orderActor("[108-6]2940", MyFactory::createFormationJuno001, NULL);
				break;
			case 2260:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2260"));
				MyFactory::orderActor("[108-6]2960", MyFactory::createFormationJuno001, NULL);
				break;
			case 2280:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2280"));
				MyFactory::orderActor("[108-6]2980", MyFactory::createFormationJuno001, NULL);
				break;
			case 2300:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2300"));
				MyFactory::orderActor("[108-6]3000", MyFactory::createFormationJuno001, NULL);
				break;
			case 2320:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2320"));
				break;
			case 2340:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2340"));
				break;
			case 2360:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2360"));
				break;
			case 2380:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2380"));
				break;
			case 2400:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2400"));
				break;
			case 2420:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2420"));
				break;
			case 2440:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2440"));
				break;
			case 2460:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2460"));
				break;
			case 2480:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2480"));
				break;
			case 2500:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2500"));
				break;
			case 2520:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2520"));
				break;
			case 2540:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2540"));
				break;
			case 2560:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2560"));
				break;
			case 2580:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2580"));
				break;
			case 2600:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2600"));
				break;
			case 2620:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2620"));
				break;
			case 2640:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2640"));
				break;
			case 2660:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2660"));
				break;
			case 2680:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2680"));
				break;
			case 2700:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2700"));
				break;
			case 2720:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2720"));
				break;
			case 2740:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2740"));
				break;
			case 2760:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2760"));
				break;
			case 2780:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2780"));
				break;
			case 2800:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2800"));
				break;
			case 2820:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2820"));
				break;
			case 2840:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2840"));
				break;
			case 2860:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2860"));
				break;
			case 2880:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2880"));
				break;
			case 2900:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2900"));
				break;
			case 2920:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2920"));
				break;
			case 2940:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2940"));
				break;
			case 2960:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2960"));
				break;
			case 2980:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2980"));
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
