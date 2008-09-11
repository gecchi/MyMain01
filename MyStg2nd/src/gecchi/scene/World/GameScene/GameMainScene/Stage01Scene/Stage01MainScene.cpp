#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// 以下の gen start ～ end はマクロにより自動生成されたコードです。変更はマクロから行って下さい。
	// gen01 start
	DWORD dw[] = {1,7,9,10,11,29,49,69,89,109,129,149,169,189,209,229,249,269,289,309,329,349,369,389,409,429,449,469,489,509,529,549,569,589,609,629,649,669,689,709,729,749,769,789,809,829,849,869,889,909,929,949,969,989,1009,1029,1049,1069,1089,1109,1129,1149,1169,1189,1209,1229,1249,1269,1289,1309,1329,1349,1369,1389,1409,1429,1449,1469,1489,1509,1529,1549,1569,1589,1609,1629,1649,1669,1689,1709,1729,1749,1769,1789,1809,1829,1849,1869,1889,1909,1929,1949,1969,1989,2009,2029,2049,2069,2089,2109,2129,2149,2169,2189,2209,2229,2249,2269,2289,2309,2329,2349,2369,2389,2409,2429,2449,2469,2489,2509,2529,2549,2569,2589,2609,2629,2649,2669,2689,2709,2729,2749,2769,2789,2809,2829,2849,2869,2889,2909,2929,2949,2969,2989};
	_paFrame_NextEvent = new DWORD[154];
	for (int i = 0; i < 154; i++) {
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
				MyFactory::orderActor("[106-6]7", MyFactory::createFormationJuno001First, (void*)(NEW int(GGAFDX9_PROPERTY(SCREEN_WIDTH)*LEN_UNIT*2)));
				MyFactory::orderActor("[108-6]9", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]29", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]49", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]69", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]89", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]109", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]129", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]149", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]169", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]189", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]209", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]229", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]249", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]269", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]289", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]309", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]329", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]349", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]369", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]389", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]409", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]429", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]449", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]469", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]489", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]509", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]529", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]549", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]569", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]589", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]609", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]629", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]649", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]669", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[108-6]689", MyFactory::createFormationJuno001, NULL);
				MyFactory::orderActor("[109-6]10", MyFactory::createFormationCeres001, NULL);
				MyFactory::orderActor("[110-6]11", MyFactory::createFormationCeres001, NULL);
				break;
			case 7:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[106-6]7"));
				break;
			case 9:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]9"));
				MyFactory::orderActor("[108-6]709", MyFactory::createFormationJuno001, NULL);
				break;
			case 10:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]10"));
				break;
			case 11:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[110-6]11"));
				break;
			case 29:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]29"));
				MyFactory::orderActor("[108-6]729", MyFactory::createFormationJuno001, NULL);
				break;
			case 49:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]49"));
				MyFactory::orderActor("[108-6]749", MyFactory::createFormationJuno001, NULL);
				break;
			case 69:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]69"));
				MyFactory::orderActor("[108-6]769", MyFactory::createFormationJuno001, NULL);
				break;
			case 89:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]89"));
				MyFactory::orderActor("[108-6]789", MyFactory::createFormationJuno001, NULL);
				break;
			case 109:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]109"));
				MyFactory::orderActor("[108-6]809", MyFactory::createFormationJuno001, NULL);
				break;
			case 129:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]129"));
				MyFactory::orderActor("[108-6]829", MyFactory::createFormationJuno001, NULL);
				break;
			case 149:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]149"));
				MyFactory::orderActor("[108-6]849", MyFactory::createFormationJuno001, NULL);
				break;
			case 169:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]169"));
				MyFactory::orderActor("[108-6]869", MyFactory::createFormationJuno001, NULL);
				break;
			case 189:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]189"));
				MyFactory::orderActor("[108-6]889", MyFactory::createFormationJuno001, NULL);
				break;
			case 209:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]209"));
				MyFactory::orderActor("[108-6]909", MyFactory::createFormationJuno001, NULL);
				break;
			case 229:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]229"));
				MyFactory::orderActor("[108-6]929", MyFactory::createFormationJuno001, NULL);
				break;
			case 249:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]249"));
				MyFactory::orderActor("[108-6]949", MyFactory::createFormationJuno001, NULL);
				break;
			case 269:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]269"));
				MyFactory::orderActor("[108-6]969", MyFactory::createFormationJuno001, NULL);
				break;
			case 289:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]289"));
				MyFactory::orderActor("[108-6]989", MyFactory::createFormationJuno001, NULL);
				break;
			case 309:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]309"));
				MyFactory::orderActor("[108-6]1009", MyFactory::createFormationJuno001, NULL);
				break;
			case 329:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]329"));
				MyFactory::orderActor("[108-6]1029", MyFactory::createFormationJuno001, NULL);
				break;
			case 349:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]349"));
				MyFactory::orderActor("[108-6]1049", MyFactory::createFormationJuno001, NULL);
				break;
			case 369:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]369"));
				MyFactory::orderActor("[108-6]1069", MyFactory::createFormationJuno001, NULL);
				break;
			case 389:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]389"));
				MyFactory::orderActor("[108-6]1089", MyFactory::createFormationJuno001, NULL);
				break;
			case 409:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]409"));
				MyFactory::orderActor("[108-6]1109", MyFactory::createFormationJuno001, NULL);
				break;
			case 429:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]429"));
				MyFactory::orderActor("[108-6]1129", MyFactory::createFormationJuno001, NULL);
				break;
			case 449:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]449"));
				MyFactory::orderActor("[108-6]1149", MyFactory::createFormationJuno001, NULL);
				break;
			case 469:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]469"));
				MyFactory::orderActor("[108-6]1169", MyFactory::createFormationJuno001, NULL);
				break;
			case 489:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]489"));
				MyFactory::orderActor("[108-6]1189", MyFactory::createFormationJuno001, NULL);
				break;
			case 509:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]509"));
				MyFactory::orderActor("[108-6]1209", MyFactory::createFormationJuno001, NULL);
				break;
			case 529:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]529"));
				MyFactory::orderActor("[108-6]1229", MyFactory::createFormationJuno001, NULL);
				break;
			case 549:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]549"));
				MyFactory::orderActor("[108-6]1249", MyFactory::createFormationJuno001, NULL);
				break;
			case 569:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]569"));
				MyFactory::orderActor("[108-6]1269", MyFactory::createFormationJuno001, NULL);
				break;
			case 589:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]589"));
				MyFactory::orderActor("[108-6]1289", MyFactory::createFormationJuno001, NULL);
				break;
			case 609:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]609"));
				MyFactory::orderActor("[108-6]1309", MyFactory::createFormationJuno001, NULL);
				break;
			case 629:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]629"));
				MyFactory::orderActor("[108-6]1329", MyFactory::createFormationJuno001, NULL);
				break;
			case 649:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]649"));
				MyFactory::orderActor("[108-6]1349", MyFactory::createFormationJuno001, NULL);
				break;
			case 669:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]669"));
				MyFactory::orderActor("[108-6]1369", MyFactory::createFormationJuno001, NULL);
				break;
			case 689:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]689"));
				MyFactory::orderActor("[108-6]1389", MyFactory::createFormationJuno001, NULL);
				break;
			case 709:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]709"));
				MyFactory::orderActor("[108-6]1409", MyFactory::createFormationJuno001, NULL);
				break;
			case 729:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]729"));
				MyFactory::orderActor("[108-6]1429", MyFactory::createFormationJuno001, NULL);
				break;
			case 749:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]749"));
				MyFactory::orderActor("[108-6]1449", MyFactory::createFormationJuno001, NULL);
				break;
			case 769:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]769"));
				MyFactory::orderActor("[108-6]1469", MyFactory::createFormationJuno001, NULL);
				break;
			case 789:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]789"));
				MyFactory::orderActor("[108-6]1489", MyFactory::createFormationJuno001, NULL);
				break;
			case 809:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]809"));
				MyFactory::orderActor("[108-6]1509", MyFactory::createFormationJuno001, NULL);
				break;
			case 829:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]829"));
				MyFactory::orderActor("[108-6]1529", MyFactory::createFormationJuno001, NULL);
				break;
			case 849:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]849"));
				MyFactory::orderActor("[108-6]1549", MyFactory::createFormationJuno001, NULL);
				break;
			case 869:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]869"));
				MyFactory::orderActor("[108-6]1569", MyFactory::createFormationJuno001, NULL);
				break;
			case 889:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]889"));
				MyFactory::orderActor("[108-6]1589", MyFactory::createFormationJuno001, NULL);
				break;
			case 909:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]909"));
				MyFactory::orderActor("[108-6]1609", MyFactory::createFormationJuno001, NULL);
				break;
			case 929:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]929"));
				MyFactory::orderActor("[108-6]1629", MyFactory::createFormationJuno001, NULL);
				break;
			case 949:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]949"));
				MyFactory::orderActor("[108-6]1649", MyFactory::createFormationJuno001, NULL);
				break;
			case 969:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]969"));
				MyFactory::orderActor("[108-6]1669", MyFactory::createFormationJuno001, NULL);
				break;
			case 989:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]989"));
				MyFactory::orderActor("[108-6]1689", MyFactory::createFormationJuno001, NULL);
				break;
			case 1009:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1009"));
				MyFactory::orderActor("[108-6]1709", MyFactory::createFormationJuno001, NULL);
				break;
			case 1029:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1029"));
				MyFactory::orderActor("[108-6]1729", MyFactory::createFormationJuno001, NULL);
				break;
			case 1049:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1049"));
				MyFactory::orderActor("[108-6]1749", MyFactory::createFormationJuno001, NULL);
				break;
			case 1069:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1069"));
				MyFactory::orderActor("[108-6]1769", MyFactory::createFormationJuno001, NULL);
				break;
			case 1089:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1089"));
				MyFactory::orderActor("[108-6]1789", MyFactory::createFormationJuno001, NULL);
				break;
			case 1109:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1109"));
				MyFactory::orderActor("[108-6]1809", MyFactory::createFormationJuno001, NULL);
				break;
			case 1129:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1129"));
				MyFactory::orderActor("[108-6]1829", MyFactory::createFormationJuno001, NULL);
				break;
			case 1149:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1149"));
				MyFactory::orderActor("[108-6]1849", MyFactory::createFormationJuno001, NULL);
				break;
			case 1169:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1169"));
				MyFactory::orderActor("[108-6]1869", MyFactory::createFormationJuno001, NULL);
				break;
			case 1189:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1189"));
				MyFactory::orderActor("[108-6]1889", MyFactory::createFormationJuno001, NULL);
				break;
			case 1209:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1209"));
				MyFactory::orderActor("[108-6]1909", MyFactory::createFormationJuno001, NULL);
				break;
			case 1229:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1229"));
				MyFactory::orderActor("[108-6]1929", MyFactory::createFormationJuno001, NULL);
				break;
			case 1249:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1249"));
				MyFactory::orderActor("[108-6]1949", MyFactory::createFormationJuno001, NULL);
				break;
			case 1269:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1269"));
				MyFactory::orderActor("[108-6]1969", MyFactory::createFormationJuno001, NULL);
				break;
			case 1289:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1289"));
				MyFactory::orderActor("[108-6]1989", MyFactory::createFormationJuno001, NULL);
				break;
			case 1309:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1309"));
				MyFactory::orderActor("[108-6]2009", MyFactory::createFormationJuno001, NULL);
				break;
			case 1329:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1329"));
				MyFactory::orderActor("[108-6]2029", MyFactory::createFormationJuno001, NULL);
				break;
			case 1349:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1349"));
				MyFactory::orderActor("[108-6]2049", MyFactory::createFormationJuno001, NULL);
				break;
			case 1369:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1369"));
				MyFactory::orderActor("[108-6]2069", MyFactory::createFormationJuno001, NULL);
				break;
			case 1389:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1389"));
				MyFactory::orderActor("[108-6]2089", MyFactory::createFormationJuno001, NULL);
				break;
			case 1409:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1409"));
				MyFactory::orderActor("[108-6]2109", MyFactory::createFormationJuno001, NULL);
				break;
			case 1429:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1429"));
				MyFactory::orderActor("[108-6]2129", MyFactory::createFormationJuno001, NULL);
				break;
			case 1449:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1449"));
				MyFactory::orderActor("[108-6]2149", MyFactory::createFormationJuno001, NULL);
				break;
			case 1469:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1469"));
				MyFactory::orderActor("[108-6]2169", MyFactory::createFormationJuno001, NULL);
				break;
			case 1489:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1489"));
				MyFactory::orderActor("[108-6]2189", MyFactory::createFormationJuno001, NULL);
				break;
			case 1509:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1509"));
				MyFactory::orderActor("[108-6]2209", MyFactory::createFormationJuno001, NULL);
				break;
			case 1529:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1529"));
				MyFactory::orderActor("[108-6]2229", MyFactory::createFormationJuno001, NULL);
				break;
			case 1549:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1549"));
				MyFactory::orderActor("[108-6]2249", MyFactory::createFormationJuno001, NULL);
				break;
			case 1569:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1569"));
				MyFactory::orderActor("[108-6]2269", MyFactory::createFormationJuno001, NULL);
				break;
			case 1589:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1589"));
				MyFactory::orderActor("[108-6]2289", MyFactory::createFormationJuno001, NULL);
				break;
			case 1609:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1609"));
				MyFactory::orderActor("[108-6]2309", MyFactory::createFormationJuno001, NULL);
				break;
			case 1629:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1629"));
				MyFactory::orderActor("[108-6]2329", MyFactory::createFormationJuno001, NULL);
				break;
			case 1649:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1649"));
				MyFactory::orderActor("[108-6]2349", MyFactory::createFormationJuno001, NULL);
				break;
			case 1669:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1669"));
				MyFactory::orderActor("[108-6]2369", MyFactory::createFormationJuno001, NULL);
				break;
			case 1689:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1689"));
				MyFactory::orderActor("[108-6]2389", MyFactory::createFormationJuno001, NULL);
				break;
			case 1709:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1709"));
				MyFactory::orderActor("[108-6]2409", MyFactory::createFormationJuno001, NULL);
				break;
			case 1729:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1729"));
				MyFactory::orderActor("[108-6]2429", MyFactory::createFormationJuno001, NULL);
				break;
			case 1749:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1749"));
				MyFactory::orderActor("[108-6]2449", MyFactory::createFormationJuno001, NULL);
				break;
			case 1769:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1769"));
				MyFactory::orderActor("[108-6]2469", MyFactory::createFormationJuno001, NULL);
				break;
			case 1789:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1789"));
				MyFactory::orderActor("[108-6]2489", MyFactory::createFormationJuno001, NULL);
				break;
			case 1809:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1809"));
				MyFactory::orderActor("[108-6]2509", MyFactory::createFormationJuno001, NULL);
				break;
			case 1829:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1829"));
				MyFactory::orderActor("[108-6]2529", MyFactory::createFormationJuno001, NULL);
				break;
			case 1849:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1849"));
				MyFactory::orderActor("[108-6]2549", MyFactory::createFormationJuno001, NULL);
				break;
			case 1869:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1869"));
				MyFactory::orderActor("[108-6]2569", MyFactory::createFormationJuno001, NULL);
				break;
			case 1889:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1889"));
				MyFactory::orderActor("[108-6]2589", MyFactory::createFormationJuno001, NULL);
				break;
			case 1909:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1909"));
				MyFactory::orderActor("[108-6]2609", MyFactory::createFormationJuno001, NULL);
				break;
			case 1929:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1929"));
				MyFactory::orderActor("[108-6]2629", MyFactory::createFormationJuno001, NULL);
				break;
			case 1949:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1949"));
				MyFactory::orderActor("[108-6]2649", MyFactory::createFormationJuno001, NULL);
				break;
			case 1969:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1969"));
				MyFactory::orderActor("[108-6]2669", MyFactory::createFormationJuno001, NULL);
				break;
			case 1989:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]1989"));
				MyFactory::orderActor("[108-6]2689", MyFactory::createFormationJuno001, NULL);
				break;
			case 2009:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2009"));
				MyFactory::orderActor("[108-6]2709", MyFactory::createFormationJuno001, NULL);
				break;
			case 2029:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2029"));
				MyFactory::orderActor("[108-6]2729", MyFactory::createFormationJuno001, NULL);
				break;
			case 2049:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2049"));
				MyFactory::orderActor("[108-6]2749", MyFactory::createFormationJuno001, NULL);
				break;
			case 2069:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2069"));
				MyFactory::orderActor("[108-6]2769", MyFactory::createFormationJuno001, NULL);
				break;
			case 2089:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2089"));
				MyFactory::orderActor("[108-6]2789", MyFactory::createFormationJuno001, NULL);
				break;
			case 2109:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2109"));
				MyFactory::orderActor("[108-6]2809", MyFactory::createFormationJuno001, NULL);
				break;
			case 2129:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2129"));
				MyFactory::orderActor("[108-6]2829", MyFactory::createFormationJuno001, NULL);
				break;
			case 2149:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2149"));
				MyFactory::orderActor("[108-6]2849", MyFactory::createFormationJuno001, NULL);
				break;
			case 2169:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2169"));
				MyFactory::orderActor("[108-6]2869", MyFactory::createFormationJuno001, NULL);
				break;
			case 2189:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2189"));
				MyFactory::orderActor("[108-6]2889", MyFactory::createFormationJuno001, NULL);
				break;
			case 2209:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2209"));
				MyFactory::orderActor("[108-6]2909", MyFactory::createFormationJuno001, NULL);
				break;
			case 2229:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2229"));
				MyFactory::orderActor("[108-6]2929", MyFactory::createFormationJuno001, NULL);
				break;
			case 2249:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2249"));
				MyFactory::orderActor("[108-6]2949", MyFactory::createFormationJuno001, NULL);
				break;
			case 2269:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2269"));
				MyFactory::orderActor("[108-6]2969", MyFactory::createFormationJuno001, NULL);
				break;
			case 2289:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2289"));
				MyFactory::orderActor("[108-6]2989", MyFactory::createFormationJuno001, NULL);
				break;
			case 2309:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2309"));
				break;
			case 2329:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2329"));
				break;
			case 2349:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2349"));
				break;
			case 2369:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2369"));
				break;
			case 2389:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2389"));
				break;
			case 2409:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2409"));
				break;
			case 2429:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2429"));
				break;
			case 2449:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2449"));
				break;
			case 2469:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2469"));
				break;
			case 2489:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2489"));
				break;
			case 2509:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2509"));
				break;
			case 2529:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2529"));
				break;
			case 2549:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2549"));
				break;
			case 2569:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2569"));
				break;
			case 2589:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2589"));
				break;
			case 2609:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2609"));
				break;
			case 2629:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2629"));
				break;
			case 2649:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2649"));
				break;
			case 2669:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2669"));
				break;
			case 2689:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2689"));
				break;
			case 2709:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2709"));
				break;
			case 2729:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2729"));
				break;
			case 2749:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2749"));
				break;
			case 2769:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2769"));
				break;
			case 2789:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2789"));
				break;
			case 2809:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2809"));
				break;
			case 2829:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2829"));
				break;
			case 2849:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2849"));
				break;
			case 2869:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2869"));
				break;
			case 2889:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2889"));
				break;
			case 2909:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2909"));
				break;
			case 2929:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2929"));
				break;
			case 2949:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2949"));
				break;
			case 2969:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2969"));
				break;
			case 2989:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[108-6]2989"));
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
